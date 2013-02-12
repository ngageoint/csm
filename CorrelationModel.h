//##################################################################
//
//    FILENAME:          CorrelationModel.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for the covariance model base class used in the CSM interface.
//    Intended for replacement models to recreate cross covariance calculations;
//    most calling applications will use the CSM cross covariance method.
//    The covariance model is passed as the base class and cast to the
//    appropriate derived class for use.
//
//    LIMITATIONS:       None
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     29-Mar-2012   SCM      Refactored interface
//     30-Oct-2012   SCM      Renamed to CorrelationModel.h
//     14-Nov-2012   SCM      Added NoCorrelationModel.
//     06-Dec 2012   JPK      Replaced "UNKNOWN" with CSM_UNKNOWN
//     17-Dec-2012   BAH      Documentation updates.
//     12-Feb-2013   JPK      Renamed CovarianceModel to
//                            CorrelationModel
//
//    NOTES:
//
//#####################################################################

#ifndef __CSM_CORRELATIONMODEL_H
#define __CSM_CORRELATIONMODEL_H

#include <string>
#include "csm.h"
#include "Error.h"

namespace csm
{

class CSM_EXPORT_API CorrelationModel
{
public:
   CorrelationModel() : theFormat(CSM_UNKNOWN) {}
   virtual ~CorrelationModel() {}
      //> A virtual destructor is needed so derived class destructors will
      //  be called when the base class object is destroyed.
      //<

   const std::string& format() const { return theFormat; }

   virtual size_t getNumSensorModelParameters() const = 0;
      //> Returns the number of model parameters. The returned value
      //  will be the same as the value of numSMParams passed to the
      //  constructor when the derived object was created.
      //<

   virtual size_t getNumCorrelationParameterGroups() const = 0;
      //> Returns the number of correlation parameter groups. The returned
      //  value will be the same as the value of numCPGroups passed to the
      //  constructor when the derived object was created.
      //<

   virtual int getCorrelationParameterGroup(size_t smParamIndex) const = 0;
      //> Returns the index of the correlation parameter group to which the
      //  model parameter given by smParamIndex belongs.  If the model
      //  parameter does not belong to a group, the return value will be -1.
      //
      //  The smParamIndex must be less than getNumSensorModelParameters().
      //<

   virtual double getCorrelationCoefficient(size_t cpGroupIndex,
                                            double deltaTime) const = 0;
      //> Computes the correlation coefficient for the correlation parameter
      //  group given by cpGroupIndex for the given deltaTime.
      //  The deltaTime argument represents the difference in time, in seconds,
      //  for which the correlation is calculated.
      //
      //  The cpGroupIndex must be less than getNumCorrelationParameterGroups().
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

protected:
   CorrelationModel(const std::string& format) : theFormat(format) {}

   std::string theFormat;
};

//***
// CLASS: NoCorrelationModel
//> The NoCorrelationModel class is needed for sensor models that do not have
//  a covariance model because the RasterGM::getCorrelationModel() method
//  returns a const reference.
//<
//***
class CSM_EXPORT_API NoCorrelationModel : public CorrelationModel
{
public:
   NoCorrelationModel() : CorrelationModel("NONE") {}
   virtual ~NoCorrelationModel() {}

   virtual size_t getNumSensorModelParameters() const { return 0; }
   virtual size_t getNumCorrelationParameterGroups() const { return 0; }

   virtual int getCorrelationParameterGroup(size_t smParamIndex) const
   {
      // there can be no smParamIndex that is less than getNumSensorModelParameters()
      throw Error(Error::INDEX_OUT_OF_RANGE,
                  "Invalid index parameter",
                  "csm::NoCorrelationModel::getNumSensorModelParameters");
   }

   virtual double getCorrelationCoefficient(size_t cpGroupIndex, double deltaTime) const
   {
      // there can be no cpGroupIndex that is less than getNumCorrelationParameterGroups()
      throw Error(Error::INDEX_OUT_OF_RANGE,
                  "Invalid index parameter",
                  "csm::NoCorrelationModel::getCorrelationCoefficient");
   }
};

} // namespace csm

#endif
