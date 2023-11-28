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
//     21-Nov-2023   JPK      Added correlationCoefficientFor() static method.
//     22-Nov-2023   JPK      Added checkParameters() static method.
//
//    NOTES:
//     Refer to LinearDecayCorrelationFunction.h for more information.
//#############################################################################
#define CSM_LIBRARY
#include "LinearDecayCorrelationFunction.h"
#include "Error.h"

#include <cmath>
#include <sstream>

namespace csm {

static const std::string LDCF_NAME = "LinearDecay";

LinearDecayCorrelationFunction::LinearDecayCorrelationFunction()
   :
      SPDCorrelationFunction    (LDCF_NAME,0.0),
      theSegmentRho             (1,0.0),
      theSegmentTime            (1,1000.0),
      theStrictlyDecreasingFlag (true)
{}

LinearDecayCorrelationFunction::
LinearDecayCorrelationFunction(const std::vector<double>& initialCorrsPerSegment,
                               const std::vector<double>& timesPerSegment,
                               bool                       strictlyDecreasing,
                               double                     deltaTimeEpsilon)
   :
      SPDCorrelationFunction    (LDCF_NAME,deltaTimeEpsilon),
      theSegmentRho             (initialCorrsPerSegment),
      theSegmentTime            (timesPerSegment),
      theStrictlyDecreasingFlag (strictlyDecreasing)
{
   checkParameters(theSegmentRho,theSegmentTime,theStrictlyDecreasingFlag);
}

LinearDecayCorrelationFunction::~LinearDecayCorrelationFunction()
{}

double
LinearDecayCorrelationFunction::getCorrelationCoefficient(double deltaTime) const
{
   const double dtEpsilon = deltaTimeEpsilon();

   return correlationCoefficientFor(deltaTime,
                                    theSegmentRho,
                                    theSegmentTime,
                                    dtEpsilon);
}

std::vector<SPDCorrelationFunction::Parameter>
LinearDecayCorrelationFunction::parameters() const
{
   std::vector<SPDCorrelationFunction::Parameter> paramVec;
   
   const size_t NUM_SEG = theSegmentRho.size();

   if (NUM_SEG > 0)
   {
      paramVec.reserve(2*NUM_SEG);

      static const std::string RHO_NAME  = "Rho_";
      static const std::string TIME_NAME = "Time_";
      
      for (size_t seg = 0; seg < NUM_SEG; ++seg)
      {
         std::stringstream rhoStrm;
         rhoStrm << RHO_NAME << seg;

         std::stringstream timeStrm;
         timeStrm << TIME_NAME << seg;
         
         paramVec.push_back(std::make_pair(rhoStrm.str(),theSegmentRho[seg]));
         paramVec.push_back(std::make_pair(timeStrm.str(),theSegmentTime[seg]));
      }
   }

   return paramVec;
}

void LinearDecayCorrelationFunction::
checkParameters(const std::vector<double>& initialCorrsPerSegment,
                const std::vector<double>& timesPerSegment,
                bool                       strictlyDecreasing)
{
   static const char* const METHOD_NAME =
      "LinearDecayCorrelationFunction::checkAndSetParameters";

   const size_t NUM_CORR = initialCorrsPerSegment.size();
   const size_t NUM_TIME = timesPerSegment.size();

   if (NUM_CORR != NUM_TIME)
   {
      std::stringstream errStrm;
      errStrm << "Number of correlations : "
              << NUM_CORR
              << " is not equal to number of times : "
              << NUM_TIME;
      
      throw Error(
         Error::BOUNDS,
         errStrm.str(),
         METHOD_NAME);
   }
       
   // No parameters implies a correlation coefficient of 0.0 and is a
   // valid case.
   if (NUM_CORR > 0)
   {                  
      double corr, prevCorr;
      double time, prevTime;
       
      for(size_t idx = 0; idx < NUM_CORR; ++idx)
      {
         corr = initialCorrsPerSegment[idx];
         time = timesPerSegment[idx];
         
         if (corr < 0.0 || corr > 1.0)
         {
            throw Error(
               Error::BOUNDS,
               "Correlation must be in range [0..1].",
               METHOD_NAME);
         }
         
         if (idx > 0)
         {
            const size_t prevIdx = idx - 1;
            
            prevCorr = initialCorrsPerSegment[prevIdx];
            prevTime = timesPerSegment[prevIdx];
            
            if (corr > prevCorr)
            {
               throw Error(
                  Error::BOUNDS,
                  "Correlation must not be monotonically non-increasing with time.",
                  METHOD_NAME);
            }

            if (strictlyDecreasing && (corr == prevCorr))
            {
              throw Error(
                  Error::BOUNDS,
                  "Correlation must be monotonically decreasing with time.",
                  METHOD_NAME);
            }
            
            if (time <= prevTime)
            {
               throw Error(
                  Error::BOUNDS,
                  "Time must be monotomically increasing.",
                  METHOD_NAME);
            }
         }
      }
   }
}

double LinearDecayCorrelationFunction::
       correlationCoefficientFor(double                     deltaTime,
                                 const std::vector<double>& initialCorrsPerSegment,
                                 const std::vector<double>& timesPerSegment,
                                 double                     dtEpsilon)
{
   if (deltaTime != 0.0)
   {
      const double adt = std::fabs(deltaTime);
 
      if (adt >= dtEpsilon)
      {
         const size_t NUM_C = initialCorrsPerSegment.size();
         
         if (NUM_C == 0) return 0.0;
         
         double prevCorr = initialCorrsPerSegment[0];
         double prevTime = timesPerSegment[0];
         
         double corrCoeff = prevCorr;
         
         for(size_t idx = 1; idx < NUM_C; ++idx)
         {
            const double corr = initialCorrsPerSegment[idx];
            const double time = timesPerSegment[idx];
            
            if (adt <= time)
            {
               if (time - prevTime != 0.0)
               {
                  corrCoeff =  prevCorr +
                               (adt - prevTime) /
                               (time - prevTime) * (corr - prevCorr);
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
   }
   //***
   // if delta time is bounded by epsilon, correlation coefficient is 1.0
   //***
   return 1.0;
}

} // namespace csm
