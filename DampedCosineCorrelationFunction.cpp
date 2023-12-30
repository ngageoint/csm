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
//     22-Nov-2023   JPK      Added static methods correlationCoefficientFor()
//                            and checkParameters()
//    NOTES:
//     Refer to DampedCosineCorrelationFunction.h for more information.
//
//#############################################################################

#define CSM_LIBRARY
#include "DampedCosineCorrelationFunction.h"
#include "Error.h"
#include <cmath>
#include <vector>

namespace csm {

static const std::string DCCF_NAME = "DampedCosine";

static const std::vector<std::string> PARAM_NAMES = {"A","T","P"};

DampedCosineCorrelationFunction::DampedCosineCorrelationFunction()
   :
      SPDCorrelationFunction (DCCF_NAME,0.0),
      theA                   (1.0e-6),
      theT                   (1.0e-6),
      theP                   (1.0e-6)
{}

DampedCosineCorrelationFunction::DampedCosineCorrelationFunction(double argA,
                                                                 double argT,
                                                                 double argP,
                                                                 double dtEpsilon)
   :
      SPDCorrelationFunction (DCCF_NAME,dtEpsilon),
      theA                   (argA),
      theT                   (argT),
      theP                   (argP)
      
{ 
   checkParameters(theA,theT,theP);
}

DampedCosineCorrelationFunction::~DampedCosineCorrelationFunction()
{}

double
DampedCosineCorrelationFunction::getCorrelationCoefficient(double deltaTime) const
{
   const double dtEpsilon = deltaTimeEpsilon();
   
   return correlationCoefficientFor(deltaTime,theA,theT,theP,dtEpsilon);
}

std::vector<SPDCorrelationFunction::Parameter>
DampedCosineCorrelationFunction::parameters() const
{
   std::vector<SPDCorrelationFunction::Parameter> paramVec(3);

   paramVec[0] = std::make_pair(PARAM_NAMES[0],theA);
   paramVec[1] = std::make_pair(PARAM_NAMES[1],theT);
   paramVec[2] = std::make_pair(PARAM_NAMES[2],theP);

   return paramVec;
}

void
DampedCosineCorrelationFunction::setParameters(double argA,
                                               double argT,
                                               double argP,
                                               double dtEpsilon)
{
   checkParameters(argA,argT,argP);

   theA = argA;
   theT = argT;
   theP = argP;

   setDeltaTimeEpsilon(dtEpsilon);
}

void
DampedCosineCorrelationFunction::checkParameters(double argA,
                                                 double argT,
                                                 double argP)
{
   static const std::string METHOD_NAME =
      "csm::DampedCosineCorrelationFunction::checkAndSetParameters";
    
   // make sure the values of each correlation function parameter fall within
   // acceptable ranges
   if ((argA <= 0.0) || (argA > 1.0))
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter A must be in the range [1.0e-6, 1].",
                  METHOD_NAME);
   }
   
   if (argT <= 0.0)
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter T must be >= 1.0e-6.",
                  METHOD_NAME);
   }
  
   if (argP <= 0.0)
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter P must be >= 1.0e-6.",
                  METHOD_NAME);
   }
}

double
DampedCosineCorrelationFunction::correlationCoefficientFor(double deltaTime,
                                                           double argA,
                                                           double argT,
                                                           double argP,
                                                           double dtEpsilon)
{
   if (deltaTime != 0.0)
   {
      const double adt = std::fabs(deltaTime);
      
      if (adt >= dtEpsilon)
      {
         // compute the value of the correlation coefficient
         constexpr double pi = 3.14159265358979323846;
         
         const double corrCoeff = argA * std::exp(-adt/argT)*
                                  cos(2.0 * pi * adt / argP);
         
         return clampedCoeff(corrCoeff,true);
      }
   }
   
   //***
   // if delta time is bounded by epsilon, correlation coefficient is 1.0
   //***
   return 1.0;
}


} // namespace csm
