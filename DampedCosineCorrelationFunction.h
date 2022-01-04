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
//
//    NOTES:
//
//#############################################################################

#ifndef __CSM_DAMPEDCOSINECORRELATIONFUNCTION_H_
#define __CSM_DAMPEDCOSINECORRELATIONFUNCTION_H_

#include "SPDCorrelationFunction.h"

#include <vector>

namespace csm
{

class CSM_EXPORT_API DampedCosineCorrelationFunction :
                                                  public SPDCorrelationFunction
{
public:
   // represents a set of four correlation parameters
   
   struct CSM_EXPORT_API Parameters
   {
      Parameters() : A(1.0e-6), T(1.0e-6), P(1.0e-6) {}
      Parameters(double argA, double argT, double argP)
         : A(argA), T(argT), P(argP) {}

      double A;     // unitless
      double T;   // seconds
      double P;     // unitless
       
   };
   
   DampedCosineCorrelationFunction();
   //> This is the default constructor
   //<

   DampedCosineCorrelationFunction(double argA,
                                   double argT,
                                   double argP);
   //> This constructor insiantiates the correlation function with the
   //  argument parameters.
   //<
   DampedCosineCorrelationFunction(const Parameters& params);
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

   void setCorrelationParameters(double argA,
                                 double argT,
                                 double argP);
      //> Sets the correlation parameter values for the group given by
      //  cpGroupIndex.  The correlation parameters a, alpha, and beta are
      //  unitless, and tau is in seconds.
      //
      //  Precondition:
      //  * 0 <= cpGroupIndex < numCPGroups
      //  * 0.0 <= a <= 1.0
      //  * 0.0 <= alpha <= 1.0
      //  * 0.0 <= beta <= 10.0
      //  * 0.0 < tau
      //<
      
   void setCorrelationParameters(const Parameters& params);
      //> Sets the values of the correlation parameters in params for the group
      //  given by cpGroupIndex.
      //
      //  Precondition:
      //  * 0 <= cpGroupIndex < numCPGroups
      //
      //  Throws a csm::Error if cpGroupIndex or any of the correlation
      //  parameters is out of range.
      //<
      
   const Parameters& getCorrelationParameters() const {return theCorrParams;}
      
      
protected:

   Parameters theCorrParams;
      //> This data member stores the values of the correlation parameters
      //<
 };

} // namespace csm

#endif
