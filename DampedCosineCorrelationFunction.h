//#############################################################################
//
//    FILENAME:          DampedCosineCorrelationFunction.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header the damped cosine correlation function class derived from
//    the SPDCorrelationFunction base class.  This class is used to compute the
//    correlation coefficient for a given delta time.
//
//    The class is a wrapper around the equation
//
//    rho = A * exp(-deltaT / T) * cos( 2 Pi * deltaT / P);
//
//    where A, T, and P are the correlation parameters, deltaT is
//    the difference in time in seconds, and rho is the correlation coefficient.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     22-Nov-2021   JPK      Initial Coding.
//     12-Nov-2023   JPK      Updates to simplify acessibility of
//                            parameters.
//     22-Nov-2023   JPK      Added static methods checkParameters() and
//                            correlationCoefficientFor().
//    NOTES:
//
//#############################################################################

#ifndef CSM_DAMPEDCOSINECORRELATIONFUNCTION_HEADER
#define CSM_DAMPEDCOSINECORRELATIONFUNCTION_HEADER

#include "SPDCorrelationFunction.h"

#include <vector>

namespace csm
{

class CSM_EXPORT_API DampedCosineCorrelationFunction :
                     public SPDCorrelationFunction
{
public:
   
   DampedCosineCorrelationFunction();
   //> This is the default constructor
   //<

   DampedCosineCorrelationFunction(double argA,
                                   double argT,
                                   double argP,
                                   double dtEpsilon = 0.0);
   //> This constructor insiantiates the correlation function with the
   //  argument parameters.
   //<

   virtual ~DampedCosineCorrelationFunction();
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
                      double argT,
                      double argP,
                      double deltaTimEpsilon = 0.0);

   static void checkParameters(double argA,
                               double argT,
                               double argP);

   static double correlationCoefficientFor(double deltaTime,
                                           double argA,
                                           double argT,
                                           double argP,
                                           double dtEpsilon);
   
private:

   double theA;
   double theT;
   double theP;
   //> These data members are the parameters for the correlation function.
   //<
};
using DCCFPtr = std::shared_ptr<DampedCosineCorrelationFunction>;
   
} // namespace csm

#endif
