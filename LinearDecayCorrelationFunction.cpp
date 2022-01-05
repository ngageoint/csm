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
   return correlationCoefficientFor(theCorrParams,deltaTime);
}

double LinearDecayCorrelationFunction::
       correlationCoefficientFor(const LinearDecayCorrelationModel::
                                       Parameters& params,
                                 double            deltaTime)
{
   const size_t size = params.theInitialCorrsPerSegment.size();
   
   if (size == 0) return 0.0;
   
   const double adt = fabs(deltaTime);
   double prevCorr = params.theInitialCorrsPerSegment[0];
   double prevTime = params.theTimesPerSegment[0];

   double correlation = prevCorr;

   for(size_t s = 1; s < size; ++s)
   {
      const double currentCorr = params.theInitialCorrsPerSegment[s];
      const double currTime = params.theTimesPerSegment[s];
      if (adt <= currTime)
      {
         if (currTime - prevTime != 0.0)
         {
            correlation =
               prevCorr +
               (adt - prevTime) / (currTime    - prevTime) *
                                  (currentCorr - prevCorr);
         }
         break;
      }
      prevCorr = currentCorr;
      prevTime = currTime;
      correlation = prevCorr;
   }

   // if necessary, clamp the coefficient value to the acceptable range
   if (correlation < 0.0)
   {
      correlation =  0.0;
   }
   else if (correlation > 1.0)
   {
      correlation = 1.0;
   }
   
   return correlation;
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

   double currentCorr, prevCorr;
   double currTime, prevTime;

   if (size > 1)
   {
      for(size_t i = 0; i < size; ++i)
      {
         currentCorr = params.theInitialCorrsPerSegment[i];
         currTime = params.theTimesPerSegment[i];
         if (currentCorr < 0.0 || currentCorr > 1.0)
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
            if (currentCorr > prevCorr)
            {
               throw Error(
                  Error::BOUNDS,
                  "Correlation must be monotomically decreasing.",
                  MODULE);
            }
            if (currTime < prevTime)
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
