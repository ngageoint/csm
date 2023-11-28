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
//    rho = A * (alpha + ((1 - alpha)*(1 + beta)/(beta + exp(deltaTime / T))),
//
//    where A, alpha, beta, and T are the correlation parameters, deltaTime is
//    the difference in time in seconds, and rho is the correlation coefficient.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     01-Dec-2021   JPK      Adapted from FourParameterCorrelationModel
//     12-Nov-2023   JPK      Updates to simplify acessibility of parameters
//     21-Nov-2023  JPK       Added correlationCoefficientFor() static method.
//     22-Nov-2023   JPK      Added checkParameters() static method.
//
//    NOTES:
//
//#############################################################################

#ifndef CSM_FOURPARAMETERCORRELATIONFUNCTION_HEADER
#define CSM_FOURPARAMETERCORRELATIONFUNCTION_HEADER

#include "SPDCorrelationFunction.h"
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
   
   FourParameterCorrelationFunction(double argA,
                                    double argAlpha,
                                    double argBeta,
                                    double argT,
                                    double dtEpsilon = 0.0);
   //> This constructor instantiates the correlation function with the
   //  argument individual parameters and delta time epsilon.
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
      
   virtual std::vector<SPDCorrelationFunction::Parameter> parameters() const;
   //> This method return the parameters for the current function.
   //<
      
   void setParameters(double argA,
                      double argAlpha,
                      double argBeta,
                      double argT,
                      double dtEpsilon = 0.0);
   //> This method checks the passed in parameter values.  If valid,
   //  the internal parameters are set to the argument values.
   //  Otherwise, a csm::Error is thrown.
   //<
   
   static double correlationCoefficientFor(double deltaTime,
                                           double argA,
                                           double argAlpha,
                                           double argBeta,
                                           double argT,
                                           double dtEpsilon);
   //> This static method computes the correlation coefficent for the given
   //  arguments
   //<
      
   static void checkParameters(double argA,
                               double argAlpha,
                               double argBeta,
                               double argT);
   //> This static method checks the argument parameters and throws an exception if
   //  they are out of range.
   //<
      
private:

   double theA;
   double theAlpha;
   double theBeta;
   double theT;
   //> This data members are the parameters for the function
   //<
};

using FPCFPtr = std::shared_ptr<FourParameterCorrelationFunction>;

} // namespace csm

#endif
