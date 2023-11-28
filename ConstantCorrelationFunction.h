//#############################################################################
//
//    FILENAME:          ConstantCorrelationFunction.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header: The constant correlation function class is derived from
//    the SPDCorrelationFunction base class.  This class is used to represent
//    a correlation function which has a value of 1.0 for deltaTime within
//    "delta time epsilon" of 0.0, and a user defined constant value elsewhere.
//
//    The class is a wrapper around the equation
//
//    rho(deltaTime) = A
// 
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     12-Nov-2023   JPK      Initial Coding
//     22-Nov-2023   JPK      Added checkParameter() static method.
//
//    NOTES:
//
//#############################################################################

#ifndef CONSTANT_CORRELATIONFUNCTION_HEADER
#define CONSTANT_CORRELATIONFUNCTION_HEADER

#include "SPDCorrelationFunction.h"

namespace csm
{

class CSM_EXPORT_API ConstantCorrelationFunction : public SPDCorrelationFunction
{
public:

   ConstantCorrelationFunction();
   
   ConstantCorrelationFunction(double corrCoeff,
                               double deltaTimeEpsilon = 0.0);
   
   void setCorrelationCoefficient(double argRho);
     
   virtual ~ConstantCorrelationFunction();   
   virtual double getCorrelationCoefficient(double deltaTime) const;
   //> This method returns the correlation coefficient for the argument
   //  delta time.
   //<
   virtual std::vector<SPDCorrelationFunction::Parameter> parameters() const;   

   static void checkParameter(double corrCoeff);
   
private:

   double theRho;
   //> This data member is the correlation coefficient and must be a value
   //  in the range [-1.0,1.0]
   //<
};
} // namespace csm

#endif
