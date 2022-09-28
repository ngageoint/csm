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
//
//    NOTES:
//     Refer to LinearDecayCorrelationFunction.h for more information.
//#############################################################################
#define CSM_LIBRARY
#include "LinearDecayCorrelationFunction.h"
#include "Error.h"

#include <cmath>

namespace csm {

LinearDecayCorrelationFunction::LinearDecayCorrelationFunction()
   :
      SPDCorrelationFunction ("LinearDecayCorrelation"),
      theCorrParams          ()
{}

LinearDecayCorrelationFunction::
LinearDecayCorrelationFunction(const std::vector<double>& initialCorrsPerSegment,
                               const std::vector<double>& timesPerSegment)
   :
      SPDCorrelationFunction ("LinearDecayCorrelation"),
      theCorrParams          ()
{
   setCorrelationParameters(initialCorrsPerSegment,timesPerSegment);
}

LinearDecayCorrelationFunction::
LinearDecayCorrelationFunction(const LinearDecayCorrelationModel::
                                     Parameters& corrParams)
   :
      SPDCorrelationFunction ("LinearDecayCorrelation"),
      theCorrParams          (corrParams)
{
   setCorrelationParameters(corrParams);
}

LinearDecayCorrelationFunction::~LinearDecayCorrelationFunction()
{
}

void LinearDecayCorrelationFunction::setCorrelationParameters(
   const std::vector<double>& initialCorrsPerSegment,
   const std::vector<double>& timesPerSegment)
{
   setCorrelationParameters(LinearDecayCorrelationModel::
                            Parameters(initialCorrsPerSegment,
                                       timesPerSegment));
}

void
LinearDecayCorrelationFunction::
setCorrelationParameters(const LinearDecayCorrelationModel::Parameters& params)
{
   checkParameters(params);
   
   // store the correlation parameter values
   theCorrParams = params;
}

double
LinearDecayCorrelationFunction::getCorrelationCoefficient(double deltaTime) const
{
   if ((deltaTime == 0.0) ||
       (std::fabs(deltaTime) < deltaTimeEpsilon())) return 1.0;

   return correlationCoefficientFor(theCorrParams,deltaTime);
}

double LinearDecayCorrelationFunction::
       correlationCoefficientFor(const LinearDecayCorrelationModel::
                                       Parameters& params,
                                 double            deltaTime)
{
   const double adt = std::fabs(deltaTime);
   
   // compute the value of the correlation coefficient
   
   if (adt > 0.0)
   {
      const size_t size = params.theInitialCorrsPerSegment.size();
      
      if (size == 0) return 0.0;
      
      
      double prevCorr = params.theInitialCorrsPerSegment[0];
      double prevTime = params.theTimesPerSegment[0];
      
      double correlation = prevCorr;
      
      for(size_t s = 1; s < size; ++s)
      {
         const double corr = params.theInitialCorrsPerSegment[s];
         const double time = params.theTimesPerSegment[s];
         if (adt <= time)
         {
            if (time - prevTime != 0.0)
            {
               correlation =
                  prevCorr +
                  (adt - prevTime) / (time - prevTime) * (corr - prevCorr);
            }
            break;
         }
         prevCorr = corr;
         prevTime = time;
         correlation = prevCorr;
      }
      
      // if necessary, clamp the coefficient value to the acceptable range
      if (correlation < 0.0)
      {
         correlation =  0.0;
      }
  
      if (correlation < 1.0)
      {
         return correlation;
      }
   }
   
   return 1.0;
}

void LinearDecayCorrelationFunction::
     checkParameters(const LinearDecayCorrelationModel::Parameters& params)
{
   static const char* const MODULE = "LinearDecayCorrelationFunction::checkParameters";
   
   // make sure the values of each correlation model parameter
   // fall within acceptable ranges
   size_t size = params.theInitialCorrsPerSegment.size();
   if (size != params.theTimesPerSegment.size())
   {
      throw Error(
         Error::BOUNDS,
         "Must have equal number of correlations and times.",
         MODULE);
   }

   double corr, prevCorr;
   double time, prevTime;

   if (size > 1)
   {
      for(size_t i = 0; i < size; ++i)
      {
         corr = params.theInitialCorrsPerSegment[i];
         time = params.theTimesPerSegment[i];
         if (corr < 0.0 || corr > 1.0)
         {
            throw Error(
               Error::BOUNDS,
               "Correlation must be in range [0..1].",
               MODULE);
         }

         if (i > 0)
         {
            prevCorr = params.theInitialCorrsPerSegment[i-1];
            prevTime = params.theTimesPerSegment[i-1];
            if (corr >= prevCorr)
            {
               throw Error(
                  Error::BOUNDS,
                  "Correlation must be monotomically decreasing.",
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
      }
   }
}

} // namespace csm
