//#############################################################################
//
//    FILENAME:          LinearDecayCorrelationFunction.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for the piecewise linear decay correlation function class derived
//    from the SPDCorrelationFunction base class.  This class is used to
//    compute the correlation coefficient given a delta time.
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     01-Dec-2021   JPK      Adapted from LinearDecayCorrelationModel
//
//    NOTES:
//
//#############################################################################

#ifndef __CSM_LINEARDECAYCORRELATIONFUNCTION_H_
#define __CSM_LINEARDECAYCORRELATIONFUNCTION_H_

#include "SPDCorrelationFunction.h"
#include "LinearDecayCorrelationModel.h"

#include <vector>

namespace csm
{
class CSM_EXPORT_API LinearDecayCorrelationFunction : public SPDCorrelationFunction
{
public:
 
   LinearDecayCorrelationFunction();
      //> This is the default contructor
      //<
      
   LinearDecayCorrelationFunction(const std::vector<double>& initialCorrsPerSegment,
                                  const std::vector<double>& timesPerSegment);
   //> This constructor instantiates from the provided parameters.
   //<

   LinearDecayCorrelationFunction(const LinearDecayCorrelationModel::
                                        Parameters& corrParams);
   //> This constructor instantiates from the provided parameters.
   //<
   
   virtual ~LinearDecayCorrelationFunction();

   const LinearDecayCorrelationModel::
         Parameters& getCorrelationParameters() const {return theCorrParams;}
      //> Returns the values of the correlation parameters for the group
      //  given by cpGroupIndex.
      //
      //  Throws an exception if cpGroupIndex is out of range.
      //<

   virtual double getCorrelationCoefficient(double deltaTime) const;
      //> Computes the correlation coefficient for the correlation parameter
      //  group given by cpGroupIndex for the given deltaTime.
      //  The deltaTime argument represents the difference in time, in seconds,
      //  for which the correlation is calculated.
      //
      //  Preconditions:
      //  * 0 <= cpGroupIndex < numCPGroups
      //
      //  Notes:
      //
      //  The deltaTime argument should be positive, but the methods uses the
      //  absolute value of the argument, so a negative deltaTime is acceptable.
      //
      //  If the computed correlation coefficient is outside the range [-1, 1],
      //  the methods will "clamp" the returned value to the nearest number
      //  within that range.  For example, if the correlation coefficient
      //  equation evaluates to 1.1 for a given deltaTime,
      //  the value 1.0 will be returned.
      //<

  
   void setCorrelationParameters(const std::vector<double>& initialCorrsPerSegment,
                                 const std::vector<double>& timesPerSegment);
   //> Sets the correlation parameter values.
   //  The correlations in initialCorrsPerSegment are
   //  unitless; the times in timesPerSegment are in seconds.
   //
   //  Precondition:
   //  * initialCorrsPerSegment and timesPerSegment are the same size
   //  * timesPerSegment[i] < timesPerSegment[i+1]
   //  * initialCorrsPerSegment[i] >= initialCorrsPerSegment[i+1]
   //  * 1 >= initialCorrsPerSegment[i] >= 0
   //<
   
   void setCorrelationParameters(const LinearDecayCorrelationModel::
                                       Parameters& params);
      //> Sets the values of the correlation parameters in params
      //  Throws an exception if  any of the correlation parameters
      //  is out of range.
      //<
      
   static double correlationCoefficientFor(const LinearDecayCorrelationModel::
                                           Parameters& params,
                                           double      deltaTime);
   //> This static method computes the correlation coefficient for the given
   //  parameters and delta time.
   //<
   static void checkParameters(const LinearDecayCorrelationModel::
                                     Parameters& params);
   //> This static method verifies the given parameters are all within acceptable
   //  value ranges.  If not, an exception is thrown.
   //< 
protected:

      LinearDecayCorrelationModel::Parameters theCorrParams;
      //> This data member stores the values of the correlation parameters.
      //<

};

typedef std::shared_ptr<LinearDecayCorrelationFunction> LDCFPtr;

} // namespace csm

#endif
