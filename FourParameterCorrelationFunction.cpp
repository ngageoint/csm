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
//     28Sep-2022   JPK       Updated valid parameter values. Added check
//                            against "deltaTimeEpsilon"
//     12-Nov-2023  JPK       More updates to simplify acessibility of
//                            parameters.
//    NOTES:
//     Refer to FourParameterCorrelationFunction.h for more information.
//
//#############################################################################

#define CSM_LIBRARY
#include "FourParameterCorrelationFunction.h"
#include "Error.h"
#include <cmath>
#include <sstream>

static const std::string FP_NAME =
             "Four-parameter function (A, alpha, beta, T)";
  
namespace csm {
     
FourParameterCorrelationFunction::FourParameterCorrelationFunction()
   :
      SPDCorrelationFunction(FP_NAME,0.0)
{
   std::vector<double> params = {1.0,0.0,0.0,1.0};

   checkAndSetParameters(params);
}

FourParameterCorrelationFunction::
FourParameterCorrelationFunction(double argA,
                                 double argAlpha,
                                 double argBeta,
                                 double argT,
                                 double deltaTimeEpsilon)
   :
      SPDCorrelationFunction(FP_NAME,deltaTimeEpsilon)
{
   std::vector<double> params = {argA,argAlpha,argBeta,argT};
   
   checkAndSetParameters(params);
}
      
FourParameterCorrelationFunction::
FourParameterCorrelationFunction(const std::vector<double>& params,
                                 double                     deltaTimeEpsilon)
   :
      SPDCorrelationFunction(FP_NAME,deltaTimeEpsilon)
{
  checkAndSetParameters(params); 
}

FourParameterCorrelationFunction::~FourParameterCorrelationFunction()
{}

double
FourParameterCorrelationFunction::getCorrelationCoefficient(double deltaTime) const
{
   // compute the value of the correlation coefficient for
   // absolute delta time of at least deltaTimeEpsilon.  Otherwise, assume
   // correlation coefficient is exactly 1.0.
   
   const double adt = std::fabs(deltaTime);

   if (adt < deltaTimeEpsilon())
   {
      return 1.0;
   }

   const double A     = theParams[0];
   const double alpha = theParams[1];
   const double beta  = theParams[2];
   const double T     = theParams[3];
   
   const double corrCoeff = A *
                            (alpha +
                             ((1.0 - alpha) *
                              (1.0 + beta) /
                              (beta + std::exp(adt / T))));
   
   return clampedCoeff(corrCoeff,false);
}

void FourParameterCorrelationFunction::
checkAndSetParameters(const std::vector<double>& params)
{
   static const std::string MODULE =
      "csm::FourParameterCorrelationFunction::checkParameters";

   if (params.size() != 4)
   {
      std::stringstream errorStrm;

      errorStrm << "Required 4 Parameters but found : "
                << params.size();
      
      throw Error(Error::INVALID_USE,
                  errorStrm.str(),
                  MODULE);
   }

   const double A = params[0];
   
   // make sure the values of each correlation function parameter fall within
   // acceptable ranges
   if ((A <= 0.0) || (A > 1.0))
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter A must be in the range (0, 1].",
                  MODULE);
   }
   
   const double alpha = params[1];
   
   if ((alpha < 0.0) || (alpha >= 1.0))
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter alpha must be in the range [0, 1).",
                  MODULE);
   }
   
   const double beta = params[2];
   
   if ((beta < 0.0) || (beta > 10.0))
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter beta must be in the range [0,10]",
                  MODULE);
   }
   
   const double T = params[3];
   
   if (T <= 0.0)
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter tau must be positive.",
                  MODULE);
   }

   theParams = {A,alpha,beta,T};
   theParamNames = {"A","alpha","beta","T"};
}

} // namespace csm
