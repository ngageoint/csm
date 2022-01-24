//#############################################################################
//
//    FILENAME:          ModelProperties.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    This files defines an interface for getting and setting generic
//    properties on a csm::Model derived object.
//
//    SOFTWARE HISTORY:
//>
//     Date          Author   Comment
//     -----------   ------   -------
//     24-Jan-2022   SCM      Initial creation
//<
//#############################################################################

#ifndef __CSM_MODEL_IDENTIFIER_H
#define __CSM_MODEL_IDENTIFIER_H

#include "csm.h"

#include <string>
#include <vector>

namespace csm {

//*****************************************************************************
// CLASS:  ModelProperties
//> This class is an optional interface that classes derived from csm::Model
//  may implement.  If they implement this interface, they should do it using
//  multiple inheritence, as in:
//
//-   class SomeRealModel : pubilc csm::RasterGM, public csm::ModelProperties
//-   {
//-      // ...
//-   };
//
//  SET code that wants to make use of a model implementing this interface
//  should use the C++ dynamic_cast operation to determine if the interface is
//  supported and to get a pointer to it.  For example:
//
//-   csm::ModelProperties* modelProps =
//-      dynamic_cast<csm::ModelProperties*>(rasterModel);
//-   const string value = modelProps->getProperty("some_property_name");
//
//  The property names are implementation dependent.  A proprty name can be
//  checked to see if the model supports it with the hasProperty() method and a
//  list of all property names can be retrieved with the allProperties()
//  method.  However, both of those methods are optional to implement, so a
//  model may have properties that it does not publically enumerate through
//  hose methods.  Model implementations sould strive to be consistent in the
//  properties they support through the methods on this interface.
//<
//*****************************************************************************
class CSM_EXPORT_API ModelProperties
{
public:
   virtual ~ModelProperties();
      //> This is the destructor.
      //<

   virtual std::string getProperty(const std::string& name) const = 0;
      //> This method must be implemented on any class that derives from
      //  ModelProperties.  It should be implemented to return the value
      //  associated with the requested property, or an empty string if the
      //  property is not set or applicable for the derived model object.
      //<
   virtual bool setProperty(const std::string& name, const std::string& value);
      //> This method may be implemented on classes that derive from
      //  ModelProperties.  If a class implements this method, it should return
      //  true if setting the property to the given value is allowed and
      //  successful.  If the property name is not recognized, or the value is
      //  invalid, then the implementation should return false.
      //
      //  The default implementation always returns false.
      //<
   virtual bool hasProperty(const std::string& name) const;
      //> This method should teturn true if the derived model object supports
      //  the given proprty name.  IOW, if getProperty(name) would return a
      //  non-empty value or if setProperty(name) has the potential to return
      //  true, then this method should return true.  Otherwise it should
      //  return false.
      //
      //  The default implementation returns false.
      //
      //  Note that since model implementations are not required to implement
      //  this method, a return value of false does not mean that the property
      //  is unequivocally not supported.  However, a return value if true DOES
      //  mean that the property is supported.
      //<
   virtual std::vector<std::string> allProperties() const;
      //> This method returns a list of all the supported properties of the
      //  derived model.  Calling hasProperty() for any value returned in the
      //  vector will return true.
      //
      //  Note that the return value is not a reference, so it should be stored
      //  in a local variable and SETs should avoid calling it more than once,
      //  as the vectors returned will be different.
      //
      //  The default implementation returns an empty vector.
      //<

protected:
   ModelProperties();
      //> This is the default constructor.  It is only called from derived
      //  classes.  Constructing an indepenedent instance of this object is not
      //  allowed.
      //<

private:
   // this base class is an interface and has no data members
};

}

#endif
