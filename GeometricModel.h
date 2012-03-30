//#############################################################################
//
//    FILENAME:          CSMSensorModel.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for abstract base class that is to provide a common interface from
//    which all Tactical Sensor Model (CSM) plugin models will inherit.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment   
//     -----------   ------   -------
//     27-Jun-2003   LMT    Initial version.
//     01-Jul-2003   LMT    Remove constants, error/warning
//                          and make methods pure virtual.
//                          CharType enum.
//     31-Jul-2003   LMT    Change calls with a "&" to a "*",
//                          combined CharType with ParamType
//                          to create Param_CharType, //reordered
//                          methods to match API order, added
//                          systematic error methods.
//     06-Aug-2003   LMT    Removed all Characteristic calls.
//     08-Oct 2003   LMT    Added getImageSize calls
//     06-Feb-2004   KRW    Incorporates changes approved by
//                          January and February 2004
//                          configuration control board.
//     30-Jul-2004   PW     Initail API 3.1 version
//     01-Nov-2004   PW     October 2004 CCB
//     22 Oct 2010   DSL    CCB Change add getCurrentCrossCovarianceMatrix
//                                     and getOriginalCrossCovarianceMatrix
//     22 Oct 2010   DSL    CCB Change add getCurrentCrossCovarianceMatrix
//                                     and getOriginalCrossCovarianceMatrix
//     25 Oct 2010   DSL    CCB Change add getNumGeometricCorrectionSwitches,
//                                         getGeometricCorrectionName,
//                                         getCurrentGeometricCorrectionSwitch,
//                                     and setCurrentGeometricCorrectionSwitch
//     25 Oct 2010   DSL    CCB Change add getNumGeometricCorrectionSwitches,
//                                         getGeometricCorrectionName,
//                                         getCurrentGeometricCorrectionSwitch,
//                                     and setCurrentGeometricCorrectionSwitch
//     02-Mar-2012   SCM    Refactored interface.
//
//    NOTES:
//
//#############################################################################

#ifndef __CSMSENSORMODEL_H
#define __CSMSENSORMODEL_H

#include "CSMMisc.h"
#include "CSMWarning.h"
#include "CSMParameterSharing.h"
#include "CSMModel.h"
#include <vector>
#include <string>

namespace csm {

class CovarianceModel;

class CSM_EXPORT_API SensorModel : public Model
{
public:
   SensorModel() {}
   virtual ~SensorModel() { }

   //---
   // Core Photogrammetry
   //---
   virtual ImageCoord groundToImage(const EcefCoord& groundPt,
                                    double desired_precision = 0.001,
                                    double* achieved_precision = NULL,
                                    WarningList* warnings = NULL) const = 0;
      //> The groundToImage() method converts x, y and z (meters) in ground
      //  space (ECEF) to line and sample (pixels) in image space.
      //<

   virtual ImageCoord groundToImage(const EcefCoord& groundPt,
                                    const std::vector<double> groundCovariance,
                                    std::vector<double>& imageCovariance,
                                    double desired_precision = 0.001,
                                    double* achieved_precision = NULL,
                                    WarningList* warnings = NULL) const = 0;
      //> This method converts a given ground point into line and sample
      //  (pixels) in image space and returns accuracy information
      //  associated with the image and ground coordinates.
      //<
   virtual EcefCoord imageToGround(const ImageCoord& imagePt,
                                   double height,
                                   double desired_precision = 0.001,
                                   double* achieved_precision = NULL,
                                   WarningList* warnings = NULL) const = 0;
      //> This method converts a given line and sample (pixels) in image
      //  space to a ground point.
      //<
   virtual EcefCoord imageToGround(const ImageCoord& imagePt,
                                   const std::vector<double> imageCovariance,
                                   double height, double heightVariance,
                                   std::vector<double>& groundCovariance,
                                   double desired_precision = 0.001,
                                   double* achieved_precision = NULL,
                                   WarningList* warnings = NULL) const = 0;
      //> This method converts a given line and sample (pixels) in //image space
      //  to a ground point and returns accuracy information associated with
      //  the image and ground coordinates.
      //<

   virtual std::vector<double> imageToProximateImagingLocus(
      const ImageCoord& imagePt,
      const EcefCoord& groundPt,
      double desired_precision = 0.001,
      double* achieved_precision = NULL,
      WarningList* warnings = NULL) const = 0;
      //> The imageToProximateImagingLocus() method computes a proximate
      //  imaging locus, a vector approximation of the imaging locus for the
      //  given line and sample nearest the given x, y and z or at the given
      //  height. The precision of this calculation refers to the locus's
      //  origin and does not refer to the locus's orientation.
      //<

   virtual std::vector<double> imageToRemoteImagingLocus(
      const ImageCoord& imagePt,
      double desired_precision = 0.001,
      double* achieved_precision = NULL,
      WarningList* warnings = NULL) const = 0;
      //> The imageToRemoteImagingLocus() method computes locus, a vector
      //  approximation of the imaging locus for the given line and sample.
      //  The precision of this calculation refers only to the origin of the
      //  locus vector and does not refer to the locus's orientation. For an
      //  explanation of the remote imaging locus, see the section at the
      //  beginning of this document.
      //<

   //---
   // Monoscopic Mensuration
   //---
   virtual ImageCoord getImageStart() const = 0;
      //> This method returns the starting coordinate in image space of the
      //  imaging operation.  If this is unknown, this may return (0,0).
      //<
   virtual ImageVector getImageSize() const = 0;
      //> This method returns the number of lines and samples in the imaging
      //  operation.  If this is unknown, the method may return (0,0).
      //
      //  Here the returned image vector represents the size of the image
      //  as an image space vector.  Use getValidHeightRange() to get the valid
      //  range of image coordinates for this model.
      //<
   virtual std::pair<double,double> getValidHeightRange() const = 0;
      //> The validHeightsRange() method returns the minimum and maximum
      //  heights that describe the range of validity of the model. For
      //  example, the model may not be valid at heights above the heights
      //  of the sensor for physical models.
      //
      //  The minimum height is returned as the first element of the pair and
      //  the maximum height is returned as the second element of the pair.
      //<
   virtual std::pair<ImageCoord,ImageCoord> getValidImageRange() const = 0;
      //> The validImageRange() method returns the minimum and maximum
      //  values for image position (line and sample) that describe the
      //  range of validity of the model. This range may not always match
      //  the physical size of the image as returned by getImageSize(). This
      //  method is used in conjunction with getValidHeightRange() to determine
      //  the full range of applicability of the sensor model.
      //
      //  The minimum coordinate is returned as the first element of the pair
      //  and the maximum coordinate is returned as the second element of the
      //  pair.
      //<
   virtual EcefVector getIlluminationDirection(const EcefCoord& gndPt) const = 0;
      //> The getIlluminationDirection() method calculates the direction of
      //  illumination at the given ground position x, y, z.
      //<

   //---
   // Time and Trajectory
   //---
   virtual std::string getTrajectoryIdentifier() const = 0;
      //> This method returns a unique identifer to indicate which
      //  trajectory was used to acquire the image. This ID is unique for
      //  each sensor type on an individual path.
      //<
   virtual std::string getReferenceDateAndTime() const = 0;
      //> This method returns the time in seconds at which the specified
      //  pixel was imaged. The time provide is relative to the reference
      //  date and time given by the getReferenceDateAndTime() method and
      //  can be used to represent time offsets within the trajectory
      //  associated with the given image.
      //<
   virtual double getImageTime(const ImageCoord& pt) const = 0;
      //> The getImageTime() method returns the time in seconds at which
      //  the pixel specified by line and sample was imaged. The time
      //  provided is relative to the reference date and time given by
      //  getReferenceDateAndTime.
      //<
   virtual EcefCoord getSensorPosition(const ImageCoord& pt) const = 0;
      //> The getSensorPosition() method returns the position of
      //  the physical sensor at the given position in the image.
      //<
   virtual EcefCoord getSensorPosition(double time) const = 0;
      //> The getSensorPosition() method returns the position of
      //  the physical sensor at the given time of imaging.
      //<
   virtual EcefVector getSensorVelocity(const ImageCoord& pt) const = 0;
      //> The getSensorVelocity() method returns the velocity
      //  of the physical sensor at the given position in the image.
      //
      //  The values returned in the EcefVector represent velocity rather than
      //  position.
      //<
   virtual EcefVector getSensorVelocity(double time) const = 0;
      //> The getSensorVelocity() method returns the velocity
      //  of the physical sensor at the given time of imaging.
      //
      //  The values returned in the EcefVector represent velocity rather than
      //  position.
      //<

   //---
   // Sensor Model Parameters
   //---
   virtual int getNumParameters() const = 0;
      //> This method returns the number of sensor model parameters.
      //<
   virtual std::string getParameterName(int index) const = 0;
      //> This method returns the name for the sensor model parameter
      //  indicated by the given index.
      //
      //  If the index is out of range, a CSMError may be thrown.
      //<
   virtual bool isParameterShareable(int index) const = 0;
      //> This method returns a flag to indicate whether or not a sensor
      //  model parameter adjustments are shareable across images for the
      //  sensor model adjustable parameter referenced by index.
      //<
   virtual std::vector<ParameterSharingCriteria>& getParameterSharingCriteria(
                int index) const = 0;
      //> This method returns characteristics to indicate how
      //  the sensor model adjustable parameter referenced by index
      //  may be shareable accross images.
      //<

   virtual double getOriginalParameterValue(int index) const = 0;
      //> The getOriginalParameterValue() method returns the value of the
      //  adjustable parameter given by index.
      //<
   virtual double getCurrentParameterValue(int index) const = 0;
      //> The getCurrentParameterValue() method returns the value
      //  of the adjustable parameter given by index.
      //<
   virtual void setCurrentParameterValue(int index, double value) = 0;
      //> The setCurrentParameterValue() method is used to set the
      //  value of the adjustable parameter indicated by index.
      //<
   virtual void setOriginalParameterValue(int index, double value) = 0;
      //> The setOriginalParameterValue() method is used to set the original
      //  parameter value of the indexed parameter.
      //<

   virtual ParamType getOriginalParameterType(int index) const = 0;
      //> The getOriginalParameterType() method returns the original
      //  type of the parameter given by index.
      //<
   virtual ParamType getCurrentParameterType(int index) const = 0;
      //> The getCurrentParameterType() method returns the current
      //  type of the parameter given by index.
      //<
   virtual void setOriginalParameterType(int index, ParamType pType) = 0;
      //> The setOriginalParameterType() method sets the original
      //  type of the parameter for the given by index.
      //<
   virtual void setCurrentParameterType(int index, ParamType pType) = 0;
      //> The setCurrentParameterType() method sets the current
      //  type of the parameter for the given by index.
      //<

   //---
   // Uncertainty Propagation
   //---
   virtual std::vector<double> computeGroundPartials(const EcefCoord& groundPt) = 0;
      //> The computeGroundPartials method calculates the partial
      //  derivatives (partials) of image position (both line and sample)
      //  with respect to ground coordinates at the given ground
      //  position x, y, z.
      //  Upon successful completion, computeGroundPartials() produces and
      //  returns the partial derivatives as follows:
      //
      //  partials [0] = line wrt x
      //  partials [1] = line wrt y
      //  partials [2] = line wrt z
      //  partials [3] = sample wrt x
      //  partials [4] = sample wrt y
      //  partials [5] = sample wrt z
      //<

   typedef std::pair<double, double> SensorPartials;
   virtual SensorPartials computeSensorPartials(
                int index,
                const EcefCoord& groundPt,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                WarningList* warnings = NULL) = 0;

   virtual SensorPartials computeSensorPartials(
                int index,
                const ImageCoord& imagePt,
                const EcefCoord& groundPt,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                WarningList* warnings = NULL) = 0;
      //> The computeSensorPartials() method calculates the partial
      //  derivatives of image position (both line and sample) with
      //  respect to the given sensor parameter (index) at the given
      //  ground position.
      //
      //  Two versions of the method are provided. The first method,
      //  computeSensorPartials(), takes in only necessary information.
      //  It may be implemented by calling groundToImage() on the ground
      //  coordinate and then calling the second form of the method with the
      //  obtained line and sample.
      //
      //  If the calling function has already performed groundToImage with the
      //  ground coordinate, it may call the second method directly since it
      //  may be significantly faster than the first.
      //
      //  The results are unpredictable if the line and sample provided do not
      //  correspond to the result of calling groundToImage() with the given
      //  ground position (x, y, and z).
      //
      //  The returned pair will have the line partial in the first element and
      //  the sample partial in the second element.
      //<

   virtual std::vector<SensorPartials> computeAllSensorPartials(
                const EcefCoord& groundPt,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                WarningList* warnings = NULL) = 0;
   virtual std::vector<SensorPartials> computeAllSensorPartials(
                const ImageCoord& imagePt,
                const EcefCoord& groundPt,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                WarningList* warnings = NULL) = 0;
      //> The computeAllSensorPartials() function calculates the
      //  partial derivatives of image position (both line and sample)
      //  with respect to each of the adjustable parameters at the
      //  given ground position.  The semantics for the two versions are the
      //  same as for computeSensorPartials().
      //
      //  The value returned is a vector of pairs with line partials in the
      //  first element and a sample partials in the second element.
      //<

   virtual double getCurrentParameterCovariance(int index1,
                                                int index2) const = 0;
      //> The getCurrentParameterCovariance() method
      //  returns the covariance of the specified parameter pair
      //  (index1, index2). The variance of the given parameter can be
      //  obtained by using the same value for index1 and index2.
      //<
   virtual void setCurrentParameterCovariance(int index1,
                                              int index2,
                                              double covariance) = 0;
      //> The setCurrentParameterCovariance() method is
      //  used to set the covariance value of the specified parameter pair.
      //<

   virtual double getOriginalParameterCovariance(int index1,
                                                 int index2) const = 0;
      //> The getOriginalParameterCovariance() method returns the original
      //  covariance of the specified parameter pair (index1, index2).
      //
      //  The variance of the given parameter can be obtained using the
      //  same value for index1 and index2.
      //<
   virtual void setOriginalParameterCovariance(int index1,
                                               int index2,
                                               double covariance) = 0;
      //> The setOriginalParameterCovariance() method sets the original
      //  covariance of the specified parameter pair (index1, index2).
      //
      //  The variance of the given parameter can be set using the same
      //  value for index1 and index2.
      //<

   //---
   // Error Correction
   //---
   virtual int getNumGeometricCorrectionSwitches() const = 0;
      //> The numGeometricCorrections() method returns the number
      //  of geometric corrections defined for the sensor model.
      //<
   virtual std::string getGeometricCorrectionName(int index) const = 0;
      //> This method returns the name for the sensor model parameter
      //  indicated by the given index.
      //<
   virtual void setCurrentGeometricCorrectionSwitch(int index,
                                                    bool value,
                                                    ParamType pType) = 0;
      //> The setCurrentGeometricCorrectionSwitch() is
      //  used to set the switch of the geometric correction
      //  indicated by index.
      //<
   virtual bool getCurrentGeometricCorrectionSwitch(int index) const = 0;
      //> The getCurrentGeometricCorrectionSwitch() returns the value of the
      //  geometric correction switch given by index.
      //<

   virtual std::vector<std::vector<double> > getCurrentCrossCovarianceMatrix(
          const ImageCoord imagePt,
          const SensorModel* comparisonModel,
          const ImageCoord&  comparisonModelImagePt) const = 0;
      //> The getCurrentCovarianceMatrix() function returns a matrix containing
      //  all elements of the error cross covariance matrix between the
      //  instantiated sensor model and a specified second sensor model
      //  (comparisonModel) at the two given image points.  The convariance is
      //  computed using the current model parameter values.
      //
      //  Images may be correlated because they are taken by the same sensor or
      //  from sensors on the same platform. Images may also be correlated due
      //  to post processing of the sensor models.
      //
      //  The data returned here may need to be supplemented with the single
      //  image covariance from getCurrentParameterCovariance() and
      //  getUnmodeledError().
      //<

   virtual std::vector<std::vector<double> > getOriginalCrossCovarianceMatrix(
          const ImageCoord imagePt,
          const SensorModel* comparisonModel,
          const ImageCoord&  comparisonModelImagePt) const = 0;
      //> The getCurrentCovarianceMatrix() function returns a matrix containing
      //  all elements of the error cross covariance matrix between the
      //  instantiated sensor model and a specified second sensor model
      //  (comparisonModel) at the two given image points.  The convariance is
      //  computed using the original model parameter values.
      //
      //  Images may be correlated because they are taken by the same sensor or
      //  from sensors on the same platform. Images may also be correlated due
      //  to post processing of the sensor models.
      //
      //  The data returned here may need to be supplemented with the single
      //  image covariance from getCurrentParameterCovariance() and
      //  getUnmodeledError().
      //<

   virtual CovarianceModel* getCovarianceModel() const = 0;
      //> This method returns the covariance model for this sensor model.
      //
      //  A new object is created every time this method is called.  The client
      //  is responsible for deallocating the object returned by this method.
      //<

   virtual std::vector<double> getUnmodeledError(const ImageCoord& pt) const = 0;
      //> The getUnmodeledError() function gives a sensor specific
      //  error for the given input image point. The error is reported
      //  as the four terms of a 2x2 covariance mensuration error
      //  matrix, returned as a 4 element vector.  This error term is meant to
      //  map error terms that are not modeled in the sensor model to image
      //  space for inclusion in error propagation. The extra error is added to
      //  the mensuration error that may already be in the matrix.
      //<
   virtual std::vector<double> getUnmodeledCrossCovariance(
                const ImageCoord& pt1,
                const ImageCoord& pt2) const = 0;
      //> The getUnmodeledCrossCovariance function gives the cross
      //  covariance for unmodeled error between two image points on
      //  the same image. The error is reported as the four terms of
      //  a 2x2 matrix, returned as a 4 element vector. The unmodeled cross
      //  covariance is added to any values that may already be in the cross
      //  covariance matrix.
      //<

#ifdef TESTAPIVERSION
   virtual std::string testAPIVersionSubclass() const = 0;
      //> The testAPIVersionSubclass method provides a means to
      //  demostrate and test the subclass backward compatibility
      //  for an API release. This method is not a member of a
      //  standard API compliant released sensor model, but is
      //  the sole addition to the API release that creates the
      //  API compliant subclassing test version of a sensor model
      //  release.
      //<
#endif
};

} // namespace csm

#endif

