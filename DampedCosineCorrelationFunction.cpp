//#############################################################################
//
//    FILENAME:          DampedCosineCorrelationFunction.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    This class is used to compute the correlation coefficient for a given
//    delta time.
//
//    LIMITATIONS:       None
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     22-Nov-2021   JPK      Copied from DampedCosineCorrelationModel
//
//    NOTES:
//     Refer to DampedCosineCorrelationFunction.h for more information.
//
//#############################################################################

#define CSM_LIBRARY
#include "DampedCosineCorrelationFunction.h"
#include "Error.h"
#include <cmath>

namespace csm {
     
DampedCosineCorrelationFunction::DampedCosineCorrelationFunction()
   :
      SPDCorrelationFunction("DampedCosineCorrelation"),
      theCorrParams         ()
{}

DampedCosineCorrelationFunction::DampedCosineCorrelationFunction(double argA,
                                                                 double argT,
                                                                 double argP)
   :
      SPDCorrelationFunction("DampedCosineCorrelation"),
      theCorrParams         ()
{
   setCorrelationParameters(argA,argT,argP);
}
      
DampedCosineCorrelationFunction::
DampedCosineCorrelationFunction(const Parameters& params)
   :
      SPDCorrelationFunction("DampedCosineCorrelation"),
      theCorrParams         ()
{
   setCorrelationParameters(params);
}

DampedCosineCorrelationFunction::~DampedCosineCorrelationFunction()
{}

void DampedCosineCorrelationFunction::setCorrelationParameters(double argA,
                                                               double argT,
                                                               double argP)
{
   setCorrelationParameters(Parameters(argA,argT,argP));
}

void
DampedCosineCorrelationFunction::setCorrelationParameters(const Parameters& params)
{
   static const char* const MODULE =
      "csm::DampedCosineCorrelationFunction::setCorrelationParameters";

   // make sure the values of each correlation function parameter fall within
   // acceptable ranges
   if ((params.A < 1.0e-6) || (params.A > 1.0))
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter A must be in the range [1.0e-6, 1].",
                  MODULE);
   }

   if (params.T < 1.0e-6)
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter T must be >= 1.0e-6.",
                  MODULE);
   }
   
   if (params.P < 1.0e-6)
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter P must be >= 1.0e-6.",
                  MODULE);
   }
   // store the correlation parameter values
   theCorrParams = params;
}

double
DampedCosineCorrelationFunction::getCorrelationCoefficient(double deltaTime) const
{
   // compute the value of the correlation coefficient
   constexpr double pi = 3.14159265358979323846;
   
   double corrCoeff = theCorrParams.A *
                      std::exp(-deltaTime/theCorrParams.T)*
                      cos(2.0 * pi * deltaTime / theCorrParams.P);
   
   
   // if necessary, clamp the coefficient value to the acceptable range
   if (corrCoeff < -1.0)
   {
      corrCoeff = -1.0;
   }
   else if (corrCoeff > 1.0)
   {
      corrCoeff = 1.0;
   }
   
   return corrCoeff;
}

} // namespace csm
