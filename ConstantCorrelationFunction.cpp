//#############################################################################
//
//    FILENAME:          ConstantCorrelationFunction.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    The constant correlation function class is derived from
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
//     22-Nov-2023   JPK      Added checkParameter() static method.
//
//    NOTES:
//
//#############################################################################

#define CSM_LIBRARY
#include "ConstantCorrelationFunction.h"
#include "Error.h"
#include <cmath>
#include <sstream>

namespace csm
{
static const std::string COCF_NAME  = "Constant";
static const std::string PARAM_NAME = "Rho";
    
ConstantCorrelationFunction::ConstantCorrelationFunction()
   :
      SPDCorrelationFunction (COCF_NAME,0.0),
      theRho                 (0.0)
{}

ConstantCorrelationFunction::
ConstantCorrelationFunction(double corrCoeff,
                            double deltaTimeEpsilon)
   :
      SPDCorrelationFunction (COCF_NAME,deltaTimeEpsilon),
      theRho                 (corrCoeff)
{ 
   checkParameter(theRho);
}

void ConstantCorrelationFunction::setCorrelationCoefficient(double argRho)
{
   theRho = argRho;

   checkParameters(theRho);
}

ConstantCorrelationFunction::~ConstantCorrelationFunction()
{}

double ConstantCorrelationFunction::
       getCorrelationCoefficient(double deltaTime) const
{
   if (deltaTime != 0.0)
   {
      if (std::fabs(deltaTime) >= deltaTimeEpsilon())
      {
         return theRho;   
      }
   }
   //***
   // if delta time is bounded by epsilon, correlation coefficient is 1.0
   //***
   return 1.0;
}

std::vector<SPDCorrelationFunction::Parameter>
ConstantCorrelationFunction::parameters() const
{
   return std::vector<SPDCorrelationFunction::
                      Parameter>(1,
                                 std::make_pair(PARAM_NAME,theRho));
}

void ConstantCorrelationFunction::checkParameter(double corrCoeff)
{
   static const std::string METHOD_NAME =
      "ConstantCorrelationFunction::checkParameter";
   
   if (fabs(corrCoeff) > 1.0)
   {
      std::stringstream errorStrm;
      
      errorStrm << "Provided correlation coefficient : "
                << corrCoeff
                << " is outside the valid range [-1.0,1.0]";
      
      throw Error(
         Error::INVALID_USE,
         errorStrm.str(),
         METHOD_NAME);
   }     
}
} // namespace csm
   
