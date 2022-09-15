//#############################################################################
//
//    FILENAME:          SettableGround.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for abstract class that is to provide support for getting and
//    setting the ground projection for sensor models.  By default, CSM sensor
//    models like RasterGM convert image coordinates into ECEF ground
//    coordinates.  This interface allows for client SETs to request that
//    conversion information explicitly and to give the SETs the ability to
//    request a different projection.
//
//    Models that implement this interface should add it as an additional
//    derived class and implement the interface methods:
//
//       class MyModel : public csm::RasterGM, public csm::SettableGround
//       { ... }
//
//    Client code can use C++ dynamic_cast to determine if the interface is supported:
//
//       csm::SettableGround* setgnd =
//          dynamic_cast<csm::SettableGround*>(modelPtr);
//       if (setgnd) { projinfo = setgnd->getProjectionInformation(); }
//
//    Helper methods for doing this are also provided as static methods.
//
//    LIMITATIONS: None
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     15-SEP-2022   SCM      Initial version.
//
//    NOTES:
//
//#############################################################################

#ifndef __CSM_SETTABLE_GROUND_H
#define __CSM_SETTABLE_GROUND_H

#include "csm.h"

namespace csm
{

class Model;

class CSM_EXPORT_API SettableGround
{
public:
   virtual ~SettableGround();
      //> The destructor is public and virtual, and does nothing for this
      //  interface class.
      //<

   virtual std::string getProjectionInformation() const = 0;
      //> This method returns the projection information currently being used
      //  by the model.  This will be formatted as WKT (TBD).
      //<

   virtual bool setProjectionInformation(const std::string& info) const = 0;
      //> This method allows client code to request that the model do
      //  conversions to the given projection information.  The information
      //  should be formatted as WKT (TBD).  If the model supports this mode
      //  and the change is successful, then it will return true.  Otherwise,
      //  it returns false.
      //<

   static std::string getProjection(const csm::Model* model);
      //> This method returns the projection information for the given CSM
      //  model.
      //
      //  If the model does not support the SettableGround interface, then
      //  this returns an empty string.
      //<
   static bool setProjection(const csm::Model* model,
                             const std::string& info);
      //> This method sets the projection information for the given CSM
      //  model and returns if it is successful.
      //
      //  If the model does not support the SettableGround interface, then
      //  this returns false.
      //<

protected:
   SettableGround();
      //> Constructor is protected method.
      //<
};

} // namespace csm

#endif
