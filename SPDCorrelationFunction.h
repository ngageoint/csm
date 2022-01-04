//##################################################################
//
//    FILENAME:          SPDCorrelationFunction.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for a class representing a symmetric positive definite
//    correlation function (SPDCF).
//
//    LIMITATIONS:       None
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     22-Nov-2021   JPK      Initial Coding
//
//    NOTES:
//
//#####################################################################

#ifndef __CSM_SPDCORRELATIONFUNCTION_H
#define __CSM_SPDCORRELATIONFUNCTION_H

#include <string>
#include <memory>

#include "csm.h"
#include "Error.h"

namespace csm
{
class CSM_EXPORT_API SPDCorrelationFunction
{
public:
   
   explicit SPDCorrelationFunction(const std::string& name)
      :
      theName (name)
   {}
   
   virtual ~SPDCorrelationFunction() {}
      //> A virtual destructor is needed so derived class destructors will
      //  be called when the base class object is destroyed.
      //<

   const std::string& name() const { return theName; }

   virtual double getCorrelationCoefficient(double deltaTime) const = 0;
      //> Computes the correlation coefficient for the given deltaTime.
      //  The deltaTime argument represents the difference in time, in seconds,
      //  for which the correlation is calculated.
      //
      //  Notes:
      //
      //  The deltaTime argument should be positive, but the method uses the
      //  absolute value of the argument, so a negative deltaTime is acceptable.
      //
      //  If the computed correlation coefficient is outside the range [-1, 1],
      //  the method will "clamp" the returned value to the nearest number
      //  within that range.  For example, if the correlation coefficient
      //  equation evaluates to 1.1 for a given deltaTime,
      //  the value 1.0 will be returned.
      //<
      
protected:
      
   void setName(const std::string& name);
 
 private:
   SPDCorrelationFunction()
      :
        theName (CSM_UNKNOWN)
   {}
   //> This is the default constructor.  It is declared private to prevent
   //  its use.
   //<

   std::string theName;
   //> This data member is a string identifying the "name" of the
   //  current derived CorrelationModel.
   //<
};
   
//***
// CLASS: NoCorrelationFunction
//> The NoCorrelationModel class is needed for sensor models that do not have
//  a covariance model because the RasterGM::getCorrelationModel() method
//  returns a const reference.
//<
//***
class CSM_EXPORT_API NoCorrelationFunction : public SPDCorrelationFunction
{
public:
   NoCorrelationFunction() : SPDCorrelationFunction("NONE") {}
   virtual ~NoCorrelationFunction() {}

   virtual double getCorrelationCoefficient(double deltaTime) const
   {
      return 0.0;
   }
};

typedef std::shared_ptr<SPDCorrelationFunction> SPDCFPtr;

} // namespace csm

#endif
