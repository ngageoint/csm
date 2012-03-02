//#############################################################################
//
//    FILENAME:   CSMPlugin.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for abstract base class that is to provide a common interface from
//    which all Tactical Sensor Model (CSM) plugin factories shall inherit.
//
//    LIMITATIONS:       None
//
//    SOFTWARE HISTORY:
//
//     Date          Author   Comment
//     -----------   ------   -------
//     May-2003          J. Olson Received initial version from BAE.
//     20-Jun-2003   KFM      Revised to incorporate plugin list and automatic
//                            registration for derived types.
//     01-Jul-2003   KFM      Updated signatures.
//     06-Feb-2004   KRW      Incorporates changes approved by
//                        the January and February 2004
//                        configuration control board.
//     08-JUN-2004   TWC      API 3.1
//     19-Aug-2004   PW       Add throws
//
//    NOTES:
//
//    Initial coding of this class was accomplished by BAE Corporation. This
//    version contains modifications by Harris Corporation with the primary
//    goal of altering the method by which derived factories are "registered"
//    with the base plugin class.
//
//    To use this for a plugin, the developer must simply inherit from this
//    class providing, at least, implementation for each pure virtual function.
//    In order to allow the plugin to self-register itself and be recognized
//    by the system as a "plugin", a static instance of the derived class must
//    invoke the CSMPlugin constructor.
//
//#############################################################################
#ifndef __CSMPLUGIN_H
#define __CSMPLUGIN_H
#ifdef _WIN32
#pragma warning( disable : 4290 )
#endif
#include <list>
#include <string>
#include "CSMImageSupportData.h"
#include "CSMMisc.h"
#include "CSMError.h"
class CSMWarning;
class CSMSensorModel;
class csm_ISD;
//-----------------------------------------------------------------------------
// This is an example factory for plug ins. In the real world, we might have
// multiple different classes in each shared library that are made to work
// together. All these classes must be created by this factory class.
//-----------------------------------------------------------------------------
class CSM_EXPORT_API CSMPlugin
{
public:
   //--------------------------------------------------------------------------
   // Types
   //--------------------------------------------------------------------------
   typedef std::list < const CSMPlugin* > CSMPluginList;
   class Impl;
   //--------------------------------------------------------------------------
   // Constructors/Destructor
   //--------------------------------------------------------------------------
   virtual ~CSMPlugin() {}
   //--------------------------------------------------------------------------
   // List Managing Methods
   //--------------------------------------------------------------------------
   static CSMWarning* getList(CSMPluginList*& aCSMPluginList)
      throw (CSMError);
      //>This method provides access to the list of all plugins that are
      // currently registered.
      //<
   static CSMWarning* findPlugin(
      const std::string& pluginName,
      CSMPlugin*& aCSMPlugin)
      throw (CSMError);
      // pre: None.
      // post: Returns a pointer to the first plugin found whose name is
      //    aName; returns NULL if no such plugin found.
   static CSMWarning* removePlugin(
      const std::string& pluginName)
      throw (CSMError);
   //--------------------------------------------------------------------------
   // Plugin Interface
   //--------------------------------------------------------------------------
virtual CSMWarning* getPluginName(
   std::string& pluginName)
   const throw (CSMError) = 0;
   //>This method returns the character std::string that identifies the plugin.
   //<
//---
// CSM Plugin Descriptors
//---
virtual CSMWarning* getManufacturer(
   std::string& manufacturer_name)
   const throw (CSMError) = 0;
virtual CSMWarning* getReleaseDate(
   std::string& release_date)
   const throw (CSMError) = 0;
//This method returns the CSM API version that the plug-in was written to.
//
virtual CSMWarning* getCSMVersion(
   int& csmVersion) const
   // implementation must include the following code:
      // csmVersion = CURRENT_CSM_VERSION; //CURRENT_CSM_VERSION is defined in CSMMisc.h
   throw (CSMError) = 0;
//---
// Sensor Model Availability
//---
virtual CSMWarning* getNSensorModels(int& n_sensor_models) const throw (CSMError) = 0;
virtual CSMWarning* getSensorModelName(
   const int& sensor_model_index,
   std::string& sensor_model_name)
   const throw (CSMError) = 0;
//---
// Sensor Model Descriptors
//---
virtual CSMWarning* getSensorModelVersion(
   const std::string &sensor_model_name,
   int& version)
   const throw (CSMError) = 0;
//---
// Sensor Model Construction
//---
virtual CSMWarning* canSensorModelBeConstructedFromState(
   const std::string& sensor_model_name,
   const std::string& sensor_model_state,
   bool& constructible)
   const throw (CSMError) = 0;
virtual CSMWarning* canSensorModelBeConstructedFromISD(
   const csm_ISD& Image_support_data,
   const std::string& sensor_model_name,
      bool& constructible)
      const throw (CSMError) = 0;
   virtual CSMWarning* constructSensorModelFromState(
      const std::string& sensor_model_state,
      CSMSensorModel*& sensor_model)
      const throw (CSMError) = 0;
   virtual CSMWarning* constructSensorModelFromISD(
      const csm_ISD&   image_support_data,
      const std::string& sensor_model_name,
      CSMSensorModel*& sensor_model)
      const throw (CSMError) = 0;
   virtual CSMWarning* getSensorModelNameFromSensorModelState(
      const std::string& sensor_model_state,
      std::string& sensor_model_name)
      const throw (CSMError) = 0;
   //---
   // Image Support Data Conversions
   //---
   virtual CSMWarning* canISDBeConvertedToSensorModelState(
      const csm_ISD&   image_support_data,
      const std::string& sensor_model_name,
      bool& convertible)
      const throw (CSMError) = 0;
   virtual CSMWarning* convertISDToSensorModelState(
      const csm_ISD& image_support_data,
      const std::string& sensor_model_name,
      std::string& sensor_model_state)
      const throw (CSMError) = 0;
protected:
   //--------------------------------------------------------------------------
   // Constructors
   //--------------------------------------------------------------------------
   CSMPlugin();
      //>This special constructor is responsible for registering each plugin
      // by adding it to theList. It is invoked by a special derived class
      // constructor that is only used by the static instance of the derived
      // class. (Refer to the example plugins to see how this is accomplished.)
      //<
private:
   //--------------------------------------------------------------------------
   // Data Members
   //--------------------------------------------------------------------------
   static CSMPluginList* theList;
   static Impl*          theImpl;
}; // CSMPlugin
#endif // __CSMPLUGIN_H

