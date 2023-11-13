//#############################################################################
//
//    FILENAME:          ConstantCorrelationFunction.cpp
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

#define CSM_LIBRARY
#include "ConstantCorrelationFunction.h"
#include "Error.h"
#include <cmath>
#include <sstream>

static const std::string CONSTANT_NAME = "Constant";
static const std::string PARAM_NAME    = "A";

namespace csm
{
     
ConstantCorrelationFunction::ConstantCorrelationFunction()
   :
      SPDCorrelationFunction (CONSTANT_NAME,0.0)
{
   std::vector<double> params(1,0.0);
   checkAndSetParameters(params);
}

ConstantCorrelationFunction::
ConstantCorrelationFunction(double corrCoeff,
                            double deltaTimeEpsilon)
   :
      SPDCorrelationFunction (CONSTANT_NAME,deltaTimeEpsilon)
{ 
   std::vector<double> params(1,corrCoeff);
   checkAndSetParameters(params);
}

ConstantCorrelationFunction::
ConstantCorrelationFunction(const std::vector<double>& params,
                            double                     deltaTimeEpsilon)
   :
      SPDCorrelationFunction (CONSTANT_NAME,deltaTimeEpsilon)
{
   checkAndSetParameters(params);
}

ConstantCorrelationFunction::~ConstantCorrelationFunction()
{}

double ConstantCorrelationFunction::
       getCorrelationCoefficient(double deltaTime) const
{
   if (std::fabs(deltaTime) < deltaTimeEpsilon())
   {
      return 1.0;
   }
   
   return theParams[0];
}

void ConstantCorrelationFunction::
     checkAndSetParameters(const std::vector<double>& params)
{
   static const std::string MODULE =
      "ConstantCorrelationFunction::checkAndSetParameters";
   
   const double A = (params.empty() ? 0.0 : params[0]);
   
   if (fabs(A) > 1.0)
   {
     std::stringstream errorStrm;

      errorStrm << "Provided correlation coefficient : "
                << theParams[0]
                << " is outside the valid range [-1.0,1.0]";
      
      throw Error(
         Error::INVALID_USE,
         errorStrm.str(),
         MODULE);
   }  
  
   std::stringstream nameStr;
   nameStr << CONSTANT_NAME
           << "-"
           << A;
   
   std::string functionName = nameStr.str();
   
   setName(functionName);

   theParams     = {A};
   theParamNames = {"A"};      
}
} // namespace csm
   
