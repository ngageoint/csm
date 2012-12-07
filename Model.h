//#############################################################################
//
//    FILENAME:          Model.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for abstract base class that is to provide a common interface from
//    which all Community Sensor Model (CSM) plugin models will inherit.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment   
//     -----------   ------   -------
//     02-Mar-2012   SCM      Initial creation
//     26-Sep-2012   JPK      Removed getModelType() and reference point.
//     30-Oct-2012   SCM      Renamed to Model.h
//     31-Oct-2012   SCM      Split getSensorTypeAndMode() into getSensorType()
//                            and getSensorMode().  Removed include for
//                            SensorTypeAndMode.h.  Moved
//                            getTrajectoryIdentifier() to this class.
//     06-Dec-2012   JPK      Added pure virtual method replaceModelState()
//
//    NOTES:
//
//#############################################################################

#ifndef __CSM_MODEL_H
#define __CSM_MODEL_H

#include "csm.h"
#include "Warning.h"
#include "Version.h"
#include <string>

namespace csm
{

class CSM_EXPORT_API Model
{
public:
   Model() {}
   virtual ~Model() {}

   //---
   // Basic model information
   //---
   virtual std::string getFamily() const = 0;
      //> This method returns the family of sensor model this object is.  This
      //  is used to help determine what derived class this object is.
      //<
   virtual Version getVersion() const = 0;
      //> This method returns the version of the model code.  The Version
      //  object can be compared to other Version objects with its comparison
      //  operators.
      //<
   virtual std::string getModelName() const = 0;
      //> This method returns a string identifying the name of the senor model.
      //<
   virtual std::string getPedigree() const = 0;
      //> The getPedigree() method returns a character std::string that
      //  identifies the sensor, the model type, its mode of acquisition
      //  and processing path. For example, an image that could produce
      //  either an optical sensor model or a cubic rational polynomial
      //  model would produce different pedigrees for each case.
      //<

   //---
   // Basic collection information
   //---
   virtual std::string getImageIdentifier() const = 0;
      //> This method returns the unique identifier to indicate the imaging
      //  operation associated with this sensor model.
      //
      //  This method may return an empty string if the ID is unknown.
      //<
   virtual void setImageIdentifier(const std::string& imageId,
                                   WarningList* warnings = NULL) = 0;
      //> This method sets the unique identifier for the image to which the
      //  sensor model pertains.
      //<

   virtual std::string getSensorIdentifier() const = 0;
      //> The getSensorIdentifier() method returns sensorId to indicate
      //  which sensor was used to acquire the image. This sensorId is
      //  meant to uniquely identify the sensor used to make the image.
      //
      //  This method may return an empty string if the sensor ID is unknown.
      //<
   virtual std::string getPlatformIdentifier() const = 0;
      //> The getPlatformIdentifier() method returns platformId to indicate
      //  which platform was used to acquire the image. This platformId
      //  is meant to uniquely identify the platform used to collect the
      //  image.
      //
      //  This method may return an empty string if the sensor ID is unknown.
      //<
   virtual std::string getCollectionIdentifier() const = 0;
      //> This method returns a unique identifer that uniquely identifies
      //  a collection activity by a sensor platform. This ID will vary
      //  depending on the sensor type and platform.
      //<
   virtual std::string getSensorType() const = 0;
      //> This method returns a description of the sensor type.  See csm.h for
      //  a list of common types.  Should return CSM_SENSOR_TYPE_UNKNOWN if the
      //  sensor type is not known.
      //<
   virtual std::string getSensorMode() const = 0;
      //> This method returns a description of the sensor mode.  See csm.h for
      //  a list of common modes.  Should return CSM_SENSOR_MODE_UNKNOWN if the
      //  sensor mode is not known.
      //<

   virtual std::string getReferenceDateAndTime() const = 0;
      //> This method returns the time in seconds at which the specified
      //  pixel was imaged. The time provide is relative to the reference
      //  date and time given by the getReferenceDateAndTime() method and
      //  can be used to represent time offsets within the trajectory
      //  associated with the given image.
      //<
   virtual std::string getTrajectoryIdentifier() const = 0;
      //> This method returns a unique identifier to indicate which
      //  trajectory was used to acquire the image. This ID is unique for
      //  each sensor type on an individual path.
      //<

   //---
   // Sensor Model State
   //---
   virtual std::string getModelState() const = 0;
      //> This method returns the current state of the model in an
      //  intermediate form. This intermediate form can then processed,
      //  for example, by saving to file so that this model
      //  can be instantiated at a later date. The derived SensorModel
      //  is responsible for saving all information needed to restore
      //  itself to its current state from this intermediate form.
      //  An empty string is returned if it is not possible to save the
      //  current state.
      //<
   
   virtual void replaceModelState(const std::string& argState) = 0;
      //> This method loads the argument state string and attempts to
      //  use it to initialize the state of the current model.
      //  If the state string contains a valid state for current
      //  model, the internal state of the model is updated.
      //  If the argument state string is empty, 
      //<
 };

} // namespace csm

#endif
