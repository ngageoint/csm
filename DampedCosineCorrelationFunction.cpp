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
//     28-Sep-2022   JPK      Updated valid parameter values.Added check
//                            against "deltaTimeEpsilon"
//     12-Nov-2023   JPK      More updates to simplify acessibility of
//                            parameters.
//    NOTES:
//     Refer to DampedCosineCorrelationFunction.h for more information.
//
//#############################################################################

#define CSM_LIBRARY
#include "DampedCosineCorrelationFunction.h"
#include "Error.h"
#include <cmath>
#include <sstream>

namespace csm {
     
DampedCosineCorrelationFunction::DampedCosineCorrelationFunction()
   :
      SPDCorrelationFunction("DampedCosineCorrelation",0.0)
{
   std::vector<double> params = {1.0e-6,1.0e-6,1.0e-6};
   
   checkAndSetParameters(params);
}

DampedCosineCorrelationFunction::DampedCosineCorrelationFunction(double argA,
                                                                 double argT,
                                                                 double argP,
                                                                 double deltaTimeEpsilon)
   :
      SPDCorrelationFunction("DampedCosineCorrelation",deltaTimeEpsilon)
{
   std::vector<double> params = {argA,argT,argP};
   
   checkAndSetParameters(params);
}
      
DampedCosineCorrelationFunction::
DampedCosineCorrelationFunction(const std::vector<double>& params,
                                const             double deltaTimeEpsilon)
   :
      SPDCorrelationFunction("DampedCosineCorrelation",deltaTimeEpsilon)
{
   checkAndSetParameters(params);
}

DampedCosineCorrelationFunction::~DampedCosineCorrelationFunction()
{}

void
DampedCosineCorrelationFunction::
checkAndSetParameters(const std::vector<double>& params)
{
   static const std::string MODULE =
      "csm::DampedCosineCorrelationFunction::checkAndSetParameters";
   
   if (params.size() != 3)
   {
      std::stringstream errorStrm;

      errorStrm << "Required 3 Parameters but found : "
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
                  "Correlation parameter A must be in the range [1.0e-6, 1].",
                  MODULE);
   }
   
   const double T = params[1];
   
   if (T <= 0.0)
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter T must be >= 1.0e-6.",
                  MODULE);
   }

   const double P = params[2];
   
   if (P <= 0.0)
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter P must be >= 1.0e-6.",
                  MODULE);
   }
   
   // store the correlation parameter values
   theParams     = {A,T,P};
   theParamNames = {"A","T","P"};
}

double
DampedCosineCorrelationFunction::getCorrelationCoefficient(double deltaTime) const
{
   const double adt = std::fabs(deltaTime);

   if (adt < deltaTimeEpsilon())
   {
      return 1.0;
   }
   
   // compute the value of the correlation coefficient
   constexpr double pi = 3.14159265358979323846;

   const double A = theParams[0];
   const double T = theParams[1];
   const double P = theParams[2];
   
   const double corrCoeff = A * std::exp(-adt/T)*cos(2.0 * pi * adt / P);
   
   return clampedCoeff(corrCoeff,true);
}

} // namespace csm
