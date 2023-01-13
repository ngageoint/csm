//#############################################################################
//
//    FILENAME:          MultiFunctionCorrelationModel.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for the multi function correlation model class derived from
//    the CorrelationModel base class.  This class is used to compute the
//    correlation between model parameters in a community sensor model (CSM),
//    where each parameter group can have a unique correlation function.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     22-Nov-2021   JPK      Initial Coding 
//
//    NOTES:
//
//#############################################################################

#ifndef __CSM_MULTIFUNCTIONCORRELATIONMODEL_H_
#define __CSM_MULTIFUNCTIONCORRELATIONMODEL_H_

#include "CorrelationModel.h"
#include "SPDCorrelationFunction.h"

#include <vector>

namespace csm
{
class CSM_EXPORT_API MultiFunctionCorrelationModel : public CorrelationModel
{
public:
   
   MultiFunctionCorrelationModel(size_t numSMParams, size_t numCPGroups);
      //> Constructor.  The number of model parameters and correlation
      //  parameter groups must be provided.
      //
      // Preconditions:
      // * numSMParams must be non-negative
      // * numCPGroups must be non-negative
      //<

   virtual ~MultiFunctionCorrelationModel();

   virtual size_t getNumSensorModelParameters() const;
      //> Returns the number of model parameters. The returned value
      //  will be the same as the value of numSMParams passed to the
      //  constructor when the object was created.
      //<

   virtual int getCorrelationParameterGroup(size_t smParamIndex) const;
      //> Returns the index of the correlation parameter group to which the
      //  model parameter given by smParamIndex belongs.  If the model
      //  parameter does not belong to a group, the return value will be -1.
      //
      //  Precondition:
      //  * 0 <= smParamIndex < numSMParams
      //<

   const SPDCFPtr&
         getCorrelationGroupFunction(size_t cpGroupIndex) const;
      //> Returns the values of the correlation function for the group given
      //  by cpGroupIndex.
      //
      //  Throws an exception if cpGroupIndex is out of range.
      //<

   virtual double getCorrelationCoefficient(size_t cpGroupIndex,
                                            double deltaTime) const;
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
      //  The deltaTime argument should be positive, but the method uses the
      //  absolute value of the argument, so a negative deltaTime is acceptable.
      //
      //  If the computed correlation coefficient is outside the range [-1, 1],
      //  the method will "clamp" the returned value to the nearest number
      //  within that range.  For example, if the correlation coefficient
      //  equation evaluates to 1.1 for a given deltaTime,
      //  the value 1.0 will be returned.
      //<

   void setCorrelationParameterGroup(size_t smParamIndex,
                                     size_t cpGroupIndex);
      //> Assigns a model parameter to a correlation parameter group.
      //  The index of the model parameter is given by smParamIndex, and the
      //  index of the group to which it is assigned is given by cppGroupIndex.
      //
      //  Preconditions:
      //  * 0 <= smParamIndex < numSMParams
      //  * 0 <= cpGroupIndex < numCPGroups
      //
      //  Notes:
      //
      //  Although the getCorrelationParameterGroup method can return -1
      //  as a group index (indicating the group has not been set),
      //  it is an error to try to set the group index to -1.
      //<

   void setCorrelationGroupFunction(size_t          cpGroupIndex,
                                    const SPDCFPtr& corrFunction);
      //> Sets the correlation function for the group given by
      //  cpGroupIndex.
      //<

protected:
   std::vector<int> theGroupMapping;
      //> This data member stores the mapping between model parameter
      //  indices and correlation parameter group indices.
      //<

   std::vector<SPDCFPtr> theCorrFunctions;
      //> This data member stores the values of the correlation parameters for
      //  each parameter group.
      //<

   void checkSensorModelParameterIndex(size_t             smParamIndex,
                                       const std::string& functionName) const;
      //> This method throws a csm::Error if the given smParamIndex is not
      //  in the range [0, numSMParams).  The method name supplied to the
      //  csm::Error object is functionName.
      //<

   void checkParameterGroupIndex(size_t             groupIndex,
                                 const std::string& functionName) const;
      //> This method throws a csm::Error if the given groupIndex is not
      //  in the range [0, numCPGroups).  The method name supplied to the
      //  csm::Error object is functionName.
      //<
};

} // namespace csm

#endif
