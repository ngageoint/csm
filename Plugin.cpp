//#############################################################################
//
//    FILENAME:   CSMPlugin.cpp
//
//    DESCRIPTION:
//
//    This file provides implementation for methods declared in the
//    CSMPlugin class.
//
//    NOTES:
//
//
//    Refer to CSMPlugin.h for more information.
//
//#############################################################################
#define CSM_LIBRARY
#include <algorithm>
#include <iostream>
#ifdef _WIN32          //exports the symbols to be used (KJR)
# include <windows.h>
# include "CSMPlugin.h"
# include "CSMSensorModel.h"
# include "CSMISDFilename.h"
# include "CSMISDByteStream.h"
# include "CSMISDNITF20.h"
# include "CSMISDNITF21.h"
#else
# include <pthread.h>
#endif
#include "CSMPlugin.h"
#include "CSMWarning.h"
#include "CSMError.h"
//***************************************************************************
CSMPlugin::CSMPluginList* CSMPlugin::theList = NULL;
CSMPlugin::Impl*          CSMPlugin::theImpl = NULL;
//***************************************************************************
// CSMPlugin::Impl
//***************************************************************************
class CSMPlugin::Impl
{
public:
   //---
   // Modifiers
   //---
   void initializeMutex();
      // pre: None.
      // post: The mutex has been initialized.
   CSMWarning * lockList(void);
      // pre: The list is unlocked.
      // post: The list has been locked.
   CSMWarning * unlockList(void);
      // pre: The list is locked.
      // post: The list has been unlocked.
   //---
   // Data Members
   //---
#ifdef _WIN32
   typedef HANDLE          Mutex;
#else
   typedef pthread_mutex_t Mutex;
#endif
   Mutex mutex;
};
//***************************************************************************
// CSMPlugin::Impl::initializeMutex
//***************************************************************************
void CSMPlugin::Impl::initializeMutex()
{
#ifdef _WIN32
   mutex = CreateMutex(NULL, FALSE, NULL); // TBD: handle errors
#else
   pthread_mutex_init(&mutex, NULL); // TBD: handle errors
#endif
}
//***************************************************************************
// CSMPlugin::Impl::lockList
//***************************************************************************
CSMWarning *CSMPlugin::Impl::lockList(void)
{
#ifdef _WIN32
  WaitForSingleObject(mutex, INFINITE);
#else
   pthread_mutex_lock(&mutex); // TBD: handle error returns
#endif
   return NULL;
}
//***************************************************************************
// CSMPlugin::Impl::unlockList
//***************************************************************************
CSMWarning *CSMPlugin::Impl::unlockList(void)
{
#ifdef _WIN32
   ReleaseMutex(mutex); // TBD: handle errors
#else
   pthread_mutex_unlock(&mutex); // TBD: handle error returns
#endif
   return NULL;
}
//***************************************************************************
// CSMPlugin::getList
//***************************************************************************
CSMWarning * CSMPlugin::getList(CSMPluginList*& aCSMPluginList) throw (CSMError)
{
   aCSMPluginList = theList;
   return NULL;
}
//***************************************************************************
// CSMPlugin::findPlugin
//***************************************************************************
CSMWarning *CSMPlugin::findPlugin(const std:: string& pluginName,
                           CSMPlugin*& aCSMPlugin) throw (CSMError)
{
  CSMWarning* csmWarn = NULL;
  CSMPlugin::CSMPluginList* models = NULL;
  theImpl->lockList();
  try {
    csmWarn = CSMPlugin::getList(models);
  }
  catch (CSMError *err) {
     std::cout << err->getError() << '\n';
     std::cout << err->getMessage() << '\n';
   }
   catch (...) {
     std::cout << "&&&&& UNKNOWN error thrown by getList\n";
   }
  if (!models)
     return csmWarn;
  bool found = false;
  for (CSMPluginList::const_iterator i = models->begin();
       i != models->end();
       ++i)
  {
    std::string apluginName;
    try {
      csmWarn = (*i)->getPluginName(apluginName);
    }
    catch (CSMError *err) {
      std::cout << err->getError() << '\n';
      std::cout << err->getMessage() << '\n';
    }
    catch (...) {
      std::cout << "&&&&& UNKNOWN error thrown by getPluginName\n";
    }
    if (std::string(apluginName) == std::string(pluginName))
      {
       aCSMPlugin = const_cast < CSMPlugin* > (*i);
       found = true;
       break;
      }
  }
  try {
    csmWarn = theImpl->unlockList();
  }
  catch (...) {
    std::cout << "&&&&& ERROR thrown by unlockList\n";
  }
  if (!found)
  {
    if(!csmWarn)
       csmWarn = new CSMWarning();
    csmWarn->setCSMWarning (CSMWarning::DATA_NOT_AVAILABLE,
                       "No matching plugin found\n",
                       "CSMPlugin::findPlugin");
  }
  return csmWarn;
}
//***************************************************************************
// CSMPlugin::removePlugin
//***************************************************************************
CSMWarning *CSMPlugin::removePlugin(const std::string& pluginName) throw (CSMError)
{
   CSMWarning *csmWarn = NULL;
   CSMPlugin* pluginPtr = NULL;
   CSMError csmErr;
   std::string myName("removePlugin");
   try {
     csmWarn = findPlugin(pluginName, pluginPtr);
   }
   catch (CSMError *err) {
     std::cout << err->getError() << '\n';
     std::cout << err->getMessage() << '\n';
   }
   catch (...) {
     std::cout << "&&&&& UNKNOWN error thrown by findPlugin\n";
   }
   if (pluginPtr !=NULL)
   {
      try {
        csmWarn = theImpl->lockList();
      }
      catch (...) {
        std::cout << "&&&&& ERROR thrown by lockList\n";
      }
      // find and remove pointer-to-plugin from theList
      CSMPluginList::iterator pos = std::find(theList->begin(),
                                        theList->end(),
                                        pluginPtr);
      if (theList->end() != pos)
      {
       theList->erase(pos);
      }
      else
      {
       std::cout << "CSMPlugin::removePlugin: Plugin " << pluginName
                << " not found" << std::endl;
       // THROW A NOT FOUND EXCEPTION
       csmErr.setCSMError (
                         CSMError::UNKNOWN_ERROR,
                         "Plugin Name Not Found",
                         myName);
       throw csmErr;
      }
      try {
       csmWarn = theImpl->unlockList();
      }
      catch (...) {
        std::cout << "&&&&& ERROR thrown by unlockList\n";
      }
   }
   else
   {
     std::cout << "CSMPlugin::removePlugin: Plugin " << pluginName
              << " not found" << std::endl;
     // THROW A NOT FOUND EXCEPTION
     csmErr.setCSMError (
                      CSMError::UNKNOWN_ERROR,
                      "Plugin Name Not Found",
                      myName);
     throw csmErr;
   }
   return csmWarn;
} // removePlugin
//***************************************************************************
// CSMPlugin::CSMPlugin
//***************************************************************************
CSMPlugin::CSMPlugin()
{
   //---
   // If the list of registered sensor model factories does not exist yet, then
   // create it.
   //---
   if (!theList)
   {
      theList = new CSMPluginList;
   }
   if (!theImpl)
   {
      theImpl = new Impl;
      theImpl->initializeMutex();
   }
   //---
   // If the list of registered sensor model factories exists now (i.e., no
   // error occurred while creating it), then register the plugin factory in
   // theList by adding a pointer to this list.
   //    The pointer points to the static instance of the derived sensor
   // model plugin.
   //---
  if (theList)
  {
    CSMWarning *csmWarn = NULL;
    try {
      csmWarn = theImpl->lockList();
    }
    catch (...) {
      std::cout << "&&&&& ERROR thrown by lockList\n";
    }
    if (csmWarn == NULL)
      {
         theList->push_back(this);
       try {
          csmWarn = theImpl->unlockList();
       }
       catch (...) {
          std::cout << "&&&&& ERROR thrown by unlockList\n";
       }
      }
  }
}

