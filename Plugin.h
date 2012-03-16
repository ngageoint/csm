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
//     02-Mar-2012   SCM      Refactor interface.
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

#include "CSMImageSupportData.h"
#include "CSMMisc.h"
#include "CSMError.h"
#include "CSMWarning.h"

#include <list>
#include <string>

namespace csm {

class SensorModel;
class Plugin;

typedef std::list<const Plugin*> PluginList;

//-----------------------------------------------------------------------------
// This is an example factory for plug ins. In the real world, we might have
// multiple different classes in each shared library that are made to work
// together. All these classes must be created by this factory class.
//-----------------------------------------------------------------------------
class CSM_EXPORT_API Plugin
{
public:
   virtual ~Plugin() {}
   //--------------------------------------------------------------------------
   // List Managing Methods
   //--------------------------------------------------------------------------
   static const PluginList& getList();
      //> This method provides access to the list of all plugins that are
      //  currently registered.
      //<
   static const Plugin* findPlugin(const std::string& pluginName,
                                   WarningList* warnings = NULL);
      //> Returns a pointer to the first plugin found whose name is
      //  pluginName; returns NULL if no such plugin found.
      //
      //  Warnings may be gerenated and put in the given list, if specified.
      //<
   static void removePlugin(const std::string& pluginName,
                            WarningList* warnings = NULL);
      //> This method attempts to remove the plugin from the list.  This does
      //  not actually unload the plugin library.
      //
      //  Warnings may be gerenated and put in the given list, if specified.
      //<

   //--------------------------------------------------------------------------
   // Plugin Interface
   //--------------------------------------------------------------------------
   virtual std::string getPluginName() const = 0;
      //> This method returns the character std::string that identifies the
      //  plugin.
      //<

   //---
   // CSM Plugin Descriptors
   //---
   virtual std::string getManufacturer() const = 0;
   virtual std::string getReleaseDate() const = 0;
   virtual int getCSMVersion() const = 0;
      //> This method returns the CSM API version that the plug-in was written
      //  to.
      //<

   //---
   // Sensor Model Availability
   //---
   virtual int getNSensorModels() const = 0;
   virtual std::string getSensorModelName(int sensor_model_index) const = 0;

   //---
   // Sensor Model Descriptors
   //---
   virtual int getSensorModelVersion(const std::string& sensor_model_name) const = 0;

   //---
   // Sensor Model Construction
   //---
   virtual bool canSensorModelBeConstructedFromState(
      const std::string& sensor_model_name,
      const std::string& sensor_model_state,
      WarningList* warnings = NULL) const = 0;
   virtual bool canSensorModelBeConstructedFromISD(
      const Isd& image_support_data,
      const std::string& sensor_model_name,
      WarningList* warnings = NULL) const = 0;

   virtual SensorModel* constructSensorModelFromState(
      const std::string& sensor_model_state,
      WarningList* warnings = NULL) const = 0;
   virtual SensorModel* constructSensorModelFromISD(
      const Isd& image_support_data,
      const std::string& sensor_model_name,
      WarningList* warnings = NULL) const = 0;

   virtual std::string getSensorModelNameFromSensorModelState(
      const std::string& sensor_model_state,
      WarningList* warnings = NULL) const = 0;

   //---
   // Image Support Data Conversions
   //---
   virtual bool canISDBeConvertedToSensorModelState(
      const Isd& image_support_data,
      const std::string& sensor_model_name,
      WarningList* warnings = NULL) const = 0;
   virtual std::string convertISDToSensorModelState(
      const Isd& image_support_data,
      const std::string& sensor_model_name,
      WarningList* warnings = NULL) const = 0;

protected:
   Plugin();
      //>This special constructor is responsible for registering each plugin
      // by adding it to theList. It is invoked by a special derived class
      // constructor that is only used by the static instance of the derived
      // class. (Refer to the example plugins to see how this is accomplished.)
      //<

private:
   class Impl;

   static Impl* impl();
      //> This method returns the static implementation singleton.
      //<

   static PluginList* theList;
   static Impl*       theImpl;
};

} // namespace csm

#endif // __CSMPLUGIN_H

