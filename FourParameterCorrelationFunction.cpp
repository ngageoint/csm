//#############################################################################
//
//    FILENAME:          FourParameterCorrelationFunction.cpp
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
//     01Dec-2021   JPK       Adapted from FourParameterCorrelationModel
//
//    NOTES:
//     Refer to FourParameterCorrelationFunction.h for more information.
//
//#############################################################################

#define CSM_LIBRARY
#include "FourParameterCorrelationFunction.h"
#include "Error.h"
#include <cmath>

namespace csm {
     
FourParameterCorrelationFunction::FourParameterCorrelationFunction()
   :
      SPDCorrelationFunction("Four-parameter function (A, alpha, beta, tau)"),
      theCorrParams         ()
{}

FourParameterCorrelationFunction::FourParameterCorrelationFunction(double a,
                                                                   double alpha,
                                                                   double beta,
                                                                   double tau)
   :
      SPDCorrelationFunction("Four-parameter function (A, alpha, beta, tau)"),
      theCorrParams         ()
{
   setCorrelationParameters(a,alpha,beta,tau);
}
      
FourParameterCorrelationFunction::
FourParameterCorrelationFunction(const FourParameterCorrelationModel::
                                       Parameters& params)
   :
      SPDCorrelationFunction("Four-parameter function (A, alpha, beta, tau)"),
      theCorrParams         ()
{
   setCorrelationParameters(params);
}

FourParameterCorrelationFunction::~FourParameterCorrelationFunction()
{}

void FourParameterCorrelationFunction::setCorrelationParameters(double a,
                                                             double alpha,
                                                             double beta,
                                                             double tau)
{
   setCorrelationParameters(FourParameterCorrelationModel::
                            Parameters(a, alpha, beta, tau));
}

void
FourParameterCorrelationFunction::
setCorrelationParameters(const FourParameterCorrelationModel::Parameters& params)
{
   checkParameters(params);
   
   // store the correlation parameter values
   theCorrParams = params;
}

double
FourParameterCorrelationFunction::getCorrelationCoefficient(double deltaTime) const
{
   // compute the value of the correlation coefficient

   return correlationCoefficientFor(theCorrParams,deltaTime);
}

double
FourParameterCorrelationFunction::
correlationCoefficientFor(const FourParameterCorrelationModel::
                                Parameters& params,
                          double            deltaTime)
{
   // compute the value of the correlation coefficient

   if (params.a == 0.0)  return 0.0;
   
   double corrCoeff = params.a *
                      (params.alpha +
                       ((1.0 - params.alpha) *
                        (1.0 + params.beta) /
                        (params.beta +
                         std::exp(std::fabs(deltaTime) /
                                  params.tau))));
   
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

void FourParameterCorrelationFunction::
checkParameters(const FourParameterCorrelationModel::Parameters& params)
{
  static const char* const MODULE =
      "csm::FourParameterCorrelationFunction::checkParameters";

   // make sure the values of each correlation function parameter fall within
   // acceptable ranges
   if ((params.a < 0.0) || (params.a > 1.0))
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter A must be in the range [-1, 1].",
                  MODULE);
   }

   if ((params.alpha < 0.0) || (params.alpha > 1.0))
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter alpha must be in the range [0, 1].",
                  MODULE);
   }

   if ((params.beta < 0.0) || (params.beta > 10.0))
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter beta must be non-negative.",
                  MODULE);
   }

   if (params.tau <= 0.0)
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter tau must be positive.",
                  MODULE);
   }
}

} // namespace csm
