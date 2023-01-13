//#############################################################################
//
//    FILENAME:          FourParameterCorrelationFunction.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header the four-parameter correlation function class derived from
//    the SPDCorrelationFunction base class.  This class is used to compute the
//    correlation coefficient for a given delta time.
//
//    The class is a wrapper around the equation
//
//    rho = a * (alpha + ((1 - alpha)*(1 + beta)/(beta + exp(deltaT / tau)))),
//
//    where a, alpha, beta, and tau are the correlation parameters, deltaT is
//    the difference in time in seconds, and rho is the correlation coefficient.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     01-Dec-2021   JPK      Adapted from FourParameterCorrelationModel
//
//    NOTES:
//
//#############################################################################

#ifndef __CSM_FOURPARAMETERCORRELATIONFUNCTION_H_
#define __CSM_FOURPARAMETERCORRELATIONFUNCTION_H_

#include "SPDCorrelationFunction.h"
#include "FourParameterCorrelationModel.h"
#include <vector>

namespace csm
{

class CSM_EXPORT_API FourParameterCorrelationFunction :
                     public SPDCorrelationFunction
{
public:
  
   FourParameterCorrelationFunction();
   //> This is the default constructor
   //<
   
   FourParameterCorrelationFunction(double a,
                                    double alpha,
                                    double beta,
                                    double tau);
   //> This constructor instantiates the correlation function with the
   //  argument parameters.
   //<
   FourParameterCorrelationFunction(const FourParameterCorrelationModel::
                                          Parameters& params);
   //> This constructor insiantiates the correlation function with the
   //  argument parameters.
   //<
   
   virtual ~FourParameterCorrelationFunction();
   //> This is the destructor
   //<
   virtual double getCorrelationCoefficient(double deltaTime) const;
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
   void setCorrelationParameters(double a,
                                 double alpha,
                                 double beta,
                                 double tau);
   //> Sets the correlation parameter values.  
   //  The correlation parameters a, alpha, and beta are
   //  unitless, and tau is in seconds.
   //
   //  Precondition:
   //  * 0 <= cpGroupIndex < numCPGroups
   //  * 0.0 <= a <= 1.0
   //  * 0.0 <= alpha <= 1.0
   //  * 0.0 <= beta <= 10.0
   //  * 0.0 < tau
   //<
   
   void setCorrelationParameters(const FourParameterCorrelationModel::
                                       Parameters& params);
   //> Sets the values of the correlation parameters in params for the group
   //  given by cpGroupIndex.
   //
   //  Precondition:
   //  * 0 <= cpGroupIndex < numCPGroups
   //
   //  Throws a csm::Error if cpGroupIndex or any of the correlation
   //  parameters is out of range.
   //<
   
   const FourParameterCorrelationModel::
         Parameters& getCorrelationParameters() const {return theCorrParams;}
   //> This method returns the current parameters.
   //<
   static double correlationCoefficientFor(const FourParameterCorrelationModel::
                                           Parameters& params,
                                           double      deltaTime);
   //> This static method computes the correlation coefficient for the given
   //  parameters and delta time.
   //<
   static void checkParameters(const FourParameterCorrelationModel::
                                     Parameters& params);
   //> This static method verifies the given parameters are all within acceptable
   //  value ranges.  If not, an exception is thrown.
   //<
   
protected:
   
   FourParameterCorrelationModel::Parameters theCorrParams;
   //> This data member stores the values of the correlation parameters
   //<
};

typedef std::shared_ptr<FourParameterCorrelationFunction> FPCFPtr;

} // namespace csm

#endif
