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
//     21-Nov-2023  JPK       Added correlationCoefficientFor() static method.
//     22-Nov-2023  JPK       Added checkParameters() static method.
//
//    NOTES:
//     Refer to FourParameterCorrelationFunction.h for more information.
//
//#############################################################################

#define CSM_LIBRARY
#include "FourParameterCorrelationFunction.h"
#include "Error.h"
#include <cmath>
#include <sstream>

namespace csm {

static const std::string FPCF_NAME =
             "Four-parameter (A, alpha, beta, T)";

static const std::vector<std::string> FP_PARAM_NAMES = {"A","alpha","beta","T"};

FourParameterCorrelationFunction::FourParameterCorrelationFunction()
   :
      SPDCorrelationFunction (FPCF_NAME,0.0),
      theA                   (1.0),
      theAlpha               (0.0),
      theBeta                (0.0),
      theT                   (1.0)
{}

FourParameterCorrelationFunction::
FourParameterCorrelationFunction(double argA,
                                 double argAlpha,
                                 double argBeta,
                                 double argT,
                                 double dtEpsilon)
   :
      SPDCorrelationFunction (FPCF_NAME,dtEpsilon),
      theA                   (argA),
      theAlpha               (argAlpha),
      theBeta                (argBeta),
      theT                   (argT)
{
   checkParameters(theA,theAlpha,theBeta,theT);
}
      
FourParameterCorrelationFunction::~FourParameterCorrelationFunction()
{}

double
FourParameterCorrelationFunction::getCorrelationCoefficient(double deltaTime) const
{
   // compute the value of the correlation coefficient for
   // absolute delta time of at least deltaTimeEpsilon.  Otherwise, assume
   // correlation coefficient is exactly 1.0.
   
   const double dtEpsilon = deltaTimeEpsilon();
   
   return correlationCoefficientFor(deltaTime,
                                    theA,
                                    theAlpha,
                                    theBeta,
                                    theT,
                                    dtEpsilon);
}

std::vector<SPDCorrelationFunction::Parameter>
FourParameterCorrelationFunction::parameters() const
{
   std::vector<SPDCorrelationFunction::Parameter> paramVctr(4);
   paramVctr[0] = std::make_pair(FP_PARAM_NAMES[0],theA);
   paramVctr[1] = std::make_pair(FP_PARAM_NAMES[1],theAlpha);
   paramVctr[2] = std::make_pair(FP_PARAM_NAMES[2],theBeta);
   paramVctr[3] = std::make_pair(FP_PARAM_NAMES[3],theT);

   return paramVctr;
}

void FourParameterCorrelationFunction::setParameters(double argA,
                                                     double argAlpha,
                                                     double argBeta,
                                                     double argT,
                                                     double dtEpsilon)
{
   checkParameters(argA,
                   argAlpha,
                   argBeta,
                   argT);

   theA     = argA;
   theAlpha = argAlpha;
   theBeta  = argBeta;
   theT     = argT;
   
   setDeltaTimeEpsilon(dtEpsilon);
}

void FourParameterCorrelationFunction::checkParameters(double argA,
                                                       double argAlpha,
                                                       double argBeta,
                                                       double argT)
{
   static const std::string METHOD_NAME =
      "csm::FourParameterCorrelationFunction::checkParameters";

   // make sure the values of each correlation function parameter fall within
   // acceptable ranges
   if ((argA <= 0.0) || (argA > 1.0))
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter A must be in the range (0, 1].",
                  METHOD_NAME);
   }
    
   if ((argAlpha < 0.0) || (argAlpha >= 1.0))
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter alpha must be in the range [0, 1).",
                  METHOD_NAME);
   }
    
   if ((argBeta < 0.0) || (argBeta > 10.0))
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter beta must be in the range [0,10]",
                  METHOD_NAME);
   }
     
   if (argT <= 0.0)
   {
      throw Error(Error::BOUNDS,
                  "Correlation parameter tau must be positive.",
                  METHOD_NAME);
   }
}

double FourParameterCorrelationFunction::
       correlationCoefficientFor(double deltaTime,
                                 double argA,
                                 double argAlpha,
                                 double argBeta,
                                 double argT,
                                 double dtEpsilon)
{
   if (deltaTime != 0.0)
   {
      const double adt = std::fabs(deltaTime);

      if (adt >= dtEpsilon)
      {
         const double corrCoeff = argA *
                                  (argAlpha +
                                   ((1.0 - argAlpha) *
                                    (1.0 + argBeta) /
                                    (argBeta + std::exp(adt / argT))));
         
         return clampedCoeff(corrCoeff,false);
         
      }
   }
   
   //***
   // if delta time is bounded by epsilon, correlation coefficient is 1.0
   //***
   return 1.0;
}

} // namespace csm
