//#############################################################################
//
//    FILENAME:          LinearDecayCorrelationFunction.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    This class is used to compute the correlation between model
//    parameters in a community sensor model (CSM).
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     01-Dec-2021   JPK      Adapted from LinearDecayCorrelationModel
//     28-Sep-2022   JPK      Updated valid parameter values.Added check
//                            against "deltaTimeEpsilon"
//     12-Nov-2023   JPK      More updates to simplify acessibility of
//                            parameters.
//    NOTES:
//     Refer to LinearDecayCorrelationFunction.h for more information.
//#############################################################################
#define CSM_LIBRARY
#include "LinearDecayCorrelationFunction.h"
#include "Error.h"

#include <cmath>
#include <sstream>

namespace csm {

LinearDecayCorrelationFunction::LinearDecayCorrelationFunction()
   :
      SPDCorrelationFunction    ("LinearDecayCorrelation",0.0),
      theStrictlyDecreasingFlag (true)
{
   std::vector<double> params;
   
   params.push_back(0.0);
   params.push_back(1000.0);

   checkAndSetParameters(params);
}

LinearDecayCorrelationFunction::
LinearDecayCorrelationFunction(const std::vector<double>& initialCorrsPerSegment,
                               const std::vector<double>& timesPerSegment,
                               bool                       strictlyDecreasing,
                               double                     deltaTimeEpsilon)
   :
      SPDCorrelationFunction    ("LinearDecayCorrelation",deltaTimeEpsilon),
      theStrictlyDecreasingFlag (strictlyDecreasing)
{
   static const std::string MODULE =
      "LinearDecayCorrelationFunction::LinearDecayCorrelationFunction";
   
    // make sure the values of each correlation model parameter
   // fall within acceptable ranges
   size_t NC = initialCorrsPerSegment.size();
   if (NC != timesPerSegment.size())
   {
      throw Error(
         Error::BOUNDS,
         "Must have equal number of correlations and times.",
         MODULE);
   }

   std::vector<double> params;
   
   for (size_t c = 0; c < NC; ++c)
   {
      params.push_back(initialCorrsPerSegment[c]);
      params.push_back(timesPerSegment[c]);
   }

   checkAndSetParameters(params);
}

LinearDecayCorrelationFunction::
LinearDecayCorrelationFunction(const std::vector<double>& params,
                               bool                       strictlyDecreasing,
                               double                     deltaTimeEpsilon)
   :
      SPDCorrelationFunction    ("LinearDecayCorrelation",deltaTimeEpsilon),
      theStrictlyDecreasingFlag (strictlyDecreasing)
{
   checkAndSetParameters(params);
}

LinearDecayCorrelationFunction::~LinearDecayCorrelationFunction()
{}

double
LinearDecayCorrelationFunction::getCorrelationCoefficient(double deltaTime) const
{
   const double adt = std::fabs(deltaTime);
   if (adt < deltaTimeEpsilon())
   {
      return 1.0;
   }
  
   const size_t NUM_C = theParams.size() / 2;
   
   if (NUM_C == 0) return 0.0;
   
   double prevCorr = theParams[0];
   double prevTime = theParams[1];
   
   double corrCoeff = prevCorr;
   
   for(size_t c = 1; c < NUM_C; ++c)
   {
      const size_t corrIdx = c*2;
      const size_t timeIdx = corrIdx + 1;
      
      const double corr = theParams[corrIdx];
      const double time = theParams[timeIdx];
      
      if (adt <= time)
      {
         if (time - prevTime != 0.0)
         {
            corrCoeff =  prevCorr +
               (adt - prevTime) / (time - prevTime) * (corr - prevCorr);
         }
         break;
      }
      
      prevCorr  = corr;
      prevTime  = time;
      corrCoeff = prevCorr;
   }
   
      // if necessary, clamp the coefficient value to the acceptable range
  return clampedCoeff(corrCoeff,false);    
}

void LinearDecayCorrelationFunction::
checkAndSetParameters(const std::vector<double>& params)
{
   static const char* const MODULE =
      "LinearDecayCorrelationFunction::checkAndSetParameters";
   
   // make sure the values of each correlation model parameter
   // fall within acceptable ranges
   const size_t NUM_P = params.size();
   theParams.clear();
   theParamNames.clear();
   
   static const std::string CORR_NAME = "rho_";
   static const std::string TIME_NAME = "time_";
   
   // No parameters implies a correlation coefficient of 0.0 and is a
   // valid case.
   if (NUM_P > 0)
   {                  
      const size_t NUM_C = NUM_P / 2;
      
      if (NUM_C * 2 != NUM_P)
      {
         throw Error(
            Error::BOUNDS,
            "Must have equal number of correlations and times.",
            MODULE);
      }
      
      double corr, prevCorr;
      double time, prevTime;
    
      for(size_t c = 0; c < NUM_C; ++c)
      {
         const size_t corrIdx = c*2;
         const size_t timeIdx = corrIdx + 1;
      
         corr = theParams[corrIdx];
         time = theParams[timeIdx];
         
         if (corr < 0.0 || corr > 1.0)
         {
            throw Error(
               Error::BOUNDS,
               "Correlation must be in range [0..1].",
               MODULE);
         }
         
         if (c > 0)
         { 
            prevCorr = params[corrIdx - 2];
            prevTime = params[corrIdx - 1];

            
            if (corr > prevCorr)
            {
               throw Error(
                  Error::BOUNDS,
                  "Correlation must not be monotonically non-increasing with time.",
                  MODULE);
            }

            if (theStrictlyDecreasingFlag && (corr == prevCorr))
            {
              throw Error(
                  Error::BOUNDS,
                  "Correlation must be monotonically decreasing with time.",
                  MODULE);
            }
            
            if (time <= prevTime)
            {
               throw Error(
                  Error::BOUNDS,
                  "Time must be monotomically increasing.",
                  MODULE);
            }
         }
         theParams.push_back(params[corrIdx]);
         theParams.push_back(params[timeIdx]);

         std::stringstream corrStrm;
         corrStrm << CORR_NAME << c;
         theParamNames.push_back(corrStrm.str());
         
         std::stringstream timeStrm;
         timeStrm << TIME_NAME << c;
         theParamNames.push_back(timeStrm.str());
      }
   }
}

} // namespace csm
