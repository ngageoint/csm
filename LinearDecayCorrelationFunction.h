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
//     12-Nov-2023   JPK      Updates to simplify acessibility of parameters
//     21-Nov-2023   JPK      Added correlationCoefficientFor() static method.
//     22-Nov-2023   JPK      Added checkParameters() static method.
//    NOTES:
//
//#############################################################################

#ifndef CSM_LINEARDECAYCORRELATIONFUNCTION_HEADER
#define CSM_LINEARDECAYCORRELATIONFUNCTION_HEADER

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
                                  const std::vector<double>& timesPerSegment,
                                  bool   strictlyDecreasing = true,
                                  double deltaTimeEpsilon   = 0.0);
   //> This constructor instantiates from the provided parameters.
   //<
      
   virtual ~LinearDecayCorrelationFunction();   
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
   virtual std::vector<SPDCorrelationFunction::Parameter> parameters() const;
      //> This method return the parameters for the current function.
      //<

   void setParameters(const std::vector<double>& initialCorrsPerSegment,
                      const std::vector<double>& timesPerSegment,
                      bool   strictlyDecreasing = true,
                      double deltaTimeEpsilon   = 0.0);
   
     
   static void checkParameters(const std::vector<double>& initialCorrsPerSegment,
                               const std::vector<double>& timesPerSegment,
                               bool                       strictlyDecreasing);
      
                                           
   static double correlationCoefficientFor(double                     deltaTime,
                                           const std::vector<double>& initialCorrsPerSegment,
                                           const std::vector<double>& timesPerSegment,
                                           double                     dtEpsilon);
   //> This static method computes the correlation coefficent from the
   //  passed in arguments without performing any range checking.
   //<
   
private:

   std::vector<double> theSegmentRho;
   std::vector<double> theSegmentTime;
   
   bool theStrictlyDecreasingFlag;
   //> This flag is used to indicate if the correlation coefficients are
   //  required to be strictly descreasing (default).
   //<
};

using LDCFPtr  = std::shared_ptr<LinearDecayCorrelationFunction>;

} // namespace csm

#endif
