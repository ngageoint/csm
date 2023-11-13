//#############################################################################
//
//    FILENAME:          ConstantCorrelationFunction.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header the constant correlation function class derived from
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

   ConstantCorrelationFunction(const std::vector<double>& params,
                               double               deltaTimeEpsilon = 0.0);
   //> This constructor instantiates the correlation function with the
   //  argument parameters, if valid.
   //<
   virtual ~ConstantCorrelationFunction();   
   virtual double getCorrelationCoefficient(double deltaTime) const;
   //> This method returns the correlation coefficient for the argument
   //  delta time.
   //<
   virtual void checkAndSetParameters(const std::vector<double>& params);
   //> This method sets the correlation coefficent.  If the value is outside the
   //  allowable range [-1.0,1.0] a csm::Error is issued.  If the provided vector
   //  is empty, the correlation coefficient is assumed to be 0.0.  If the vector
   //  contains more than one element, only the first element is checked
   //  and copied.
   //<   
};
} // namespace csm

#endif
