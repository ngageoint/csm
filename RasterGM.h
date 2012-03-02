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
//                       Date          Author Comment
//    SOFTWARE HISTORY: 27-Jun-2003    LMT    Initial version.
//                       01-Jul-2003   LMT    Remove constants, error/warning
//                                            and make methods pure virtual.
//                                            CharType enum.
//                       31-Jul-2003   LMT    Change calls with a "&" to a "*",
//                                            combined CharType with ParamType
//                                            to create Param_CharType, //reordered
//                                            methods to match API order, added
//                                            systematic error methods.
//                       06-Aug-2003   LMT    Removed all Characteristic calls.
//                       08-Oct 2003   LMT    Added getImageSize calls
//                       06-Feb-2004   KRW    Incorporates changes approved by
//                                            January and February 2004
//                                            configuration control board.
//                       30-Jul-2004   PW     Initail API 3.1 version
//                       01-Nov-2004   PW     October 2004 CCB
//                       22 Oct 2010   DSL    CCB Change add getCurrentCrossCovarianceMatrix
//                                                       and getOriginalCrossCovarianceMatrix
//                       22 Oct 2010   DSL    CCB Change add getCurrentCrossCovarianceMatrix
//                                                       and getOriginalCrossCovarianceMatrix
//                       25 Oct 2010   DSL    CCB Change add getNumGeometricCorrectionSwitches,
//                                                           getGeometricCorrectionName,
//                                                           getCurrentGeometricCorrectionSwitch,
//                                                       and setCurrentGeometricCorrectionSwitch
//                       25 Oct 2010   DSL    CCB Change add getNumGeometricCorrectionSwitches,
//                                                           getGeometricCorrectionName,
//                                                           getCurrentGeometricCorrectionSwitch,
//                                                       and setCurrentGeometricCorrectionSwitch
//    NOTES:
//
//#############################################################################
#ifdef _WIN32
#pragma warning( disable : 4290 )
#endif
// remove ";" from end of each #define
#ifndef __CSMSENSORMODEL_H
#define __CSMSENSORMODEL_H
#include <vector>
#include "CSMMisc.h"
#include "CSMWarning.h"
#include "CSMError.h"
#include "CSMParameterSharing.h"
#include <string>
class CSMSensorTypeAndMode
{
public:
  CSMSensorTypeAndMode() {}
  CSMSensorTypeAndMode (const std::string sensorType,
                        const std::string sensorMode)
  {
    theSensorType = sensorType;
    theSensorMode = sensorMode;
  }
  CSMSensorTypeAndMode & operator=(const CSMSensorTypeAndMode& x)
  {
      this->theSensorType = x.type();
      this->theSensorMode = x.mode();
      return *this;
  }
  const std::string& type() const {return theSensorType;}
  const std::string& mode() const {return theSensorMode;}
private:
   std::string theSensorType;
   std::string theSensorMode;
};
#define TYPE_UNK "UNKNOWN"
#define TYPE_EO "EO"
#define TYPE_IR "IR"
#define TYPE_MWIR "MWIR"
#define TYPE_LWIR "LWIR"
#define TYPE_SAR "SAR"
#define TYPE_EOIRSC "EO_IR_SPECIAL_CASE"
#define MODE_FRAME "FRAME"
#define MODE_PULSE "PULSE"
#define MODE_PB "PUSHBROOM"
#define MODE_WB "WHISKBROOM"
#define MODE_SPOT "SPOT"
#define MODE_STRIP "STRIP"
#define MODE_SCAN "SCAN"
#define MODE_VIDEO "VIDEO"
#define MODE_BODY_POINTING "BODY_POINTING"
  static const CSMSensorTypeAndMode EO_FRAME(TYPE_EO, MODE_FRAME);
  static const CSMSensorTypeAndMode EO_PUSHBROOM(TYPE_EO, MODE_PB); //EO_ -> EO,
  static const CSMSensorTypeAndMode EO_WHISKBROOM(TYPE_EO, MODE_WB); //EO_ -> EO,
  static const CSMSensorTypeAndMode EO_VIDEO(TYPE_EO, MODE_VIDEO);
  static const CSMSensorTypeAndMode MWIR_FRAME(TYPE_MWIR, MODE_FRAME);
  static const CSMSensorTypeAndMode LWIR_WHISKBROOM(TYPE_LWIR, MODE_WB);
  static const CSMSensorTypeAndMode SAR_SPOT(TYPE_SAR, MODE_SPOT);
  static const CSMSensorTypeAndMode SAR_STRIP(TYPE_SAR, MODE_STRIP);
  static const CSMSensorTypeAndMode SAR_SCAN(TYPE_SAR, MODE_SCAN);
  static const CSMSensorTypeAndMode BODY_POINTING(TYPE_EO, MODE_BODY_POINTING);
class CSM_EXPORT_API CSMSensorModel
{
public:
   //--------------------------------------------------------------
   // Constructors/Destructor
   //--------------------------------------------------------------
   CSMSensorModel()
   {
     //EO_FRAME = CSMSensorTypeAndMode(TYPE_EO, MODE_PB);
   }
   virtual ~CSMSensorModel() { }
   //--------------------------------------------------------------
   // Modifier
   //--------------------------------------------------------------
   //---
   // Core Photogrammetry
   //---
   virtual CSMWarning* groundToImage(
                   const double& x,
                   const double& y,
                   const double& z,
                   double& line,
                   double& sample,
                   double& achieved_precision,
                   const double& desired_precision = 0.001)
      const throw (CSMError) = 0;
      //> The groundToImage() method converts x, y and z (meters) in ground
      // space (ECEF) to line and sample (pixels) in image space.
      //<
   virtual CSMWarning* groundToImage(
                   const double& x,
                   const double& y,
                   const double& z,
                   const double groundCovariance[9],
                   double& line,
                   double& sample,
                   double imageCovariance[4],
                   double& achieved_precision,
                   const double& desired_precision = 0.001)
      const throw (CSMError) = 0;
   //> This method converts a given ground point into line and sample
   // (pixels) in image space and returns accuracy information
   // associated with the image and ground coordinates.
   //<
 virtual CSMWarning* imageToGround(
                const double& line,
                const double& sample,
                const double& height,
                double& x,
                double& y,
                double& z,
                double& achieved_precision,
                const double& desired_precision = 0.001)
   const throw (CSMError) = 0;
   //> This method converts a given line and sample (pixels) in image
   // space to a ground point.
   //<
virtual CSMWarning* imageToGround(
                const double& line,
                const double& sample,
                const double imageCovariance[4],
                const double& height,
                const double& heightVariance,
                double& x,
                double& y,
                double& z,
                double groundCovariance[9],
                double& achieved_precision,
                const double& desired_precision = 0.001)
   const throw (CSMError) = 0;
   //> This method converts a given line and sample (pixels) in //image space
   // to a ground point and returns accuracy information associated with
   // the image and ground coordinates.
   //<
virtual CSMWarning* imageToProximateImagingLocus(
                const double& line,
                const double& sample,
                const double& x,
                const double& y,
                const double& z,
                double locus[6],
                double& achieved_precision,
                const double& desired_precision = 0.001)
   const throw (CSMError) = 0;
   //> The imageToProximateImagingLocus() method computes a proximate
   //  imaging locus, a vector approximation of the imaging locus for the
   //  given line and sample nearest the given x, y and z or at the given
   //  height. The precision of this calculation refers to the locus's
   //  origin and does not refer to the locus's orientation.
   //<
virtual CSMWarning* imageToRemoteImagingLocus(
                const double& line,
                const double& sample,
                double locus[6],
                double& achieved_precision,
                const double& desired_precision = 0.001)
   const throw (CSMError) = 0;
   //> The imageToRemoteImagingLocus() method computes locus, a vector
   //  approximation of the imaging locus for the given line and sample.
   //  The precision of this calculation refers only to the origin of the
   //  locus vector and does not refer to the locus's orientation. For an
   //  explanation of the remote imaging locus, see the section at the
   //  beginning of this document.
   //<
//---
// Uncertainty Propagation
//---
virtual CSMWarning* computeGroundPartials(
                const double& x,
                const double& y,
                const double& z,
                double partials[6])
    throw (CSMError) = 0;
   //> The computeGroundPartials method calculates the partial
   //  derivatives (partials) of image position (both line and sample)
   //  with respect to ground coordinates at the given ground
   //  position x, y, z.
   //  Upon successful completion, computeGroundPartials() produces the
   //  partial derivatives as follows:
   //
   //  partials [0] = line wrt x
   //  partials [1] = line wrt y
   //  partials [2] = line wrt z
   //  partials [3] = sample wrt x
   //  partials [4] = sample wrt y
   //  partials [5] = sample wrt z
   //<
virtual CSMWarning* computeSensorPartials(
                const int& index,
                const double& x,
                const double& y,
                const double& z,
                double& line_partial,
                double& sample_partial,
                double& achieved_precision,
                const double& desired_precision = 0.001)
    throw (CSMError) = 0;
virtual CSMWarning* computeSensorPartials(
                const int& index,
                const double& line,
                const double& sample,
                const double& x,
                const double& y,
                const double& z,
                double& line_partial,
                double& sample_partial,
                double& achieved_precision,
                const double& desired_precision = 0.001)
    throw (CSMError) = 0;
   //> The computeSensorPartials() method calculates the partial
   //  derivatives of image position (both line and sample) with
   //  respect to the given sensor parameter (index) at the given
   //  ground position.
   //  Two versions of the method are provided. The first method,
   //  computeSensorPartials(), takes in only necessary information.
   //  It performs groundToImage() on the ground coordinate and then
   //  calls the second form of the method with the obtained line
   //  and sample. If the calling function has already performed
   //  groundToImage with the ground coordinate, it may call the second
   //  method directly since it may be significantly faster than the
   //  first. The results are unpredictable if the line and sample
   //  provided do not correspond to the result of calling // //groundToImage()
   //  with the given ground position (x, y, and z).
   //<
virtual CSMWarning* computeAllSensorPartials(
                const double&        x,
                const double&        y,
                const double&        z,
                std::vector<double>& line_partials,
                std::vector<double>& sample_partials,
                double&         achieved_precision,
                const double&        desired_precision = 0.001)
    throw (CSMError) = 0;
virtual CSMWarning* computeAllSensorPartials(
                const double&        line,
                const double&        sample,
                const double&        x,
                const double&        y,
                const double&        z,
                std::vector<double>& line_partials,
                std::vector<double>& sample_partials,
                double&              achieved_precision,
                const double&        desired_precision = 0.001)
    throw (CSMError) = 0;
   //> The computeAllSensorPartials() function calculates the
   //  partial derivatives of image position (both line and sample)
   //  with respect to each of the adjustable parameters at the
   //  given ground position.
   //>
virtual CSMWarning* getCurrentParameterCovariance(
                const int& index1,
                const int& index2,
             double& covariance)
   const throw (CSMError) = 0;
   //> The getCurrentParameterCovariance() method
   //  returns the covariance of the specified parameter pair
   //  (index1, index2). The variance of the given parameter can be
   //  obtained by using the same value for index1 and index2.
   //<
virtual CSMWarning* setCurrentParameterCovariance(
                const int& index1,
                const int& index2,
                const double& covariance)
   throw (CSMError) = 0;
   //> The setCurrentParameterCovariance() method is
   // used to set the covariance value of the specified parameter pair.
   //<
virtual CSMWarning* setOriginalParameterCovariance(
                const int& index1,
                const int& index2,
                const double& covariance)
   throw (CSMError) = 0;
virtual CSMWarning* getOriginalParameterCovariance(
             const int& index1,
             const int& index2,
             double& covariance)
   const throw (CSMError) = 0;
   //> The first form of originalParameterCovariance() method sets
   //  the covariance of the specified parameter pair (index1, index2).
   //  The variance of the given parameter can be set using the same
   //  value for index1 and index2.
   //  The second form of originalParameterCovariance() method gets
   //  the covariance of the specified parameter pair (index1, index2).
   //  The variance of the given parameter can be obtained using the
   //  same value for index1 and index2.
   //<
//---
// Time and Trajectory
//---
virtual CSMWarning* getTrajectoryIdentifier(
                std::string &trajectoryId)
   const throw (CSMError) = 0;
   //> This method returns a unique identifer to indicate which
   // trajectory was used to acquire the image. This ID is unique for
   // each sensor type on an individual path.
   //<
virtual CSMWarning* getReferenceDateAndTime(
                std::string &date_and_time)
   const throw (CSMError) = 0;
   //> This method returns the time in seconds at which the specified
   //  pixel was imaged. The time provide is relative to the reference
   //  date and time given by the getReferenceDateAndTime() method and
   //  can be used to represent time offsets within the trajectory
   //  associated with the given image.
   //<
virtual CSMWarning* getImageTime(
                const double& line,
                const double& sample,
                double& time)
   const throw (CSMError) = 0;
   //> The getImageTime() method returns the time in seconds at which
   // the pixel specified by line and sample was imaged. The time
   // provided is relative to the reference date and time given by
   // getReferenceDateAndTime.
   //<
virtual CSMWarning* getSensorPosition(
                const double& line,
                const double& sample,
                double& x,
                double& y,
                double& z)
   const throw (CSMError) = 0;
   //> The getSensorPosition() method returns the position of
   // the physical sensor at the given position in the image.
   //<
virtual CSMWarning* getSensorPosition(
                const double& time,
                double& x,
                double& y,
                double& z)
   const throw (CSMError) = 0;
   //> The getSensorPosition() method returns the position of
   // the physical sensor at the given time of imaging.
   //<
virtual CSMWarning* getSensorVelocity(
                const double& line,
                const double& sample,
                double& vx,
                double& vy,
                double &vz)
   const throw (CSMError) = 0;
   //> The getSensorVelocity() method returns the velocity
   // of the physical sensor at the given position in the image.
   //<
virtual CSMWarning* getSensorVelocity(
                const double& time,
                double& vx,
                double& vy,
                double &vz)
   const throw (CSMError) = 0;
   //> The getSensorVelocity() method returns the velocity
   // of the physical sensor at the given time of imaging.
   //<
//---
// Sensor Model Parameters
//---
virtual CSMWarning* setCurrentParameterValue(
                const int& index,
                const double& value)
   throw (CSMError) = 0;
   //> The setCurrentParameterValue() is used to set the
   // value of the adjustable parameter indicated by index.
   //<
virtual CSMWarning* getCurrentParameterValue(
                const int& index,
               double& value)
   const throw (CSMError) = 0;
   //> The getCurrentParameterValue()returns the value
   // of the adjustable parameter given by index.
   //<
virtual CSMWarning* getParameterName(
                const int& index,
                std::string& name)
   const throw (CSMError) = 0;
   //> This method returns the name for the sensor model parameter
   // indicated by the given index.
   //<
virtual CSMWarning* getNumParameters(
                int& numParams)
   const throw (CSMError) = 0;
   //> This method returns the number of sensor model parameters.
   //<
virtual CSMWarning* setOriginalParameterValue(
                const int& index,
                const double& value)
   throw (CSMError) = 0;
   //> The setOriginalParameterValue() method is
   // used to set the original parameter value of the indexed
   // parameter.
   //<
virtual CSMWarning* getOriginalParameterValue(
                const int& index,
             double& value)
   const throw (CSMError) = 0;
   //> The getOriginalParameterValue() method
   // returns the value of the adjustable parameter given by
   // index.
   //<
virtual CSMWarning* getOriginalParameterType(
                const int& index,
             CSMMisc::Param_CharType &pType)
   const throw (CSMError) = 0;
   //> The getOriginalParameterType() method returns the original
   // type of the parameter given by index.
   //<
virtual CSMWarning* getCurrentParameterType(
                const int& index,
             CSMMisc::Param_CharType &pType)
   const throw (CSMError) = 0;
   //> The getCurrentParameterType() method returns the current
   // type of the parameter given by index.
   //<
virtual CSMWarning* setOriginalParameterType(
                const int& index,
             const CSMMisc::Param_CharType &pType)
   throw (CSMError) = 0;
   //> The setOriginalParameterType() method sets the original
   // type of the parameter for the given by index.
   //<
virtual CSMWarning* setCurrentParameterType(
                const int& index,
             const CSMMisc::Param_CharType &pType)
   throw (CSMError) = 0;
   //> The setCurrentParameterType() method sets the current
   // type of the parameter for the given by index.
   //<
//---
// Sensor Model Information
//---
virtual CSMWarning* getPedigree(
                    std::string &pedigree)
   const throw (CSMError) = 0;
   //> The getPedigree() method returns a character std::string that
   //  identifies the sensor, the model type, its mode of acquisition
   //  and processing path. For example, an image that could produce
   //  either an optical sensor model or a cubic rational polynomial
   //  model would produce different pedigrees for each case.
   //<
virtual CSMWarning* getImageIdentifier(
                std::string &imageId)
   const throw (CSMError) = 0;
   //> This method returns the unique identifier to indicate the imaging
   // operation associated with this sensor model.
   //<
virtual CSMWarning* setImageIdentifier(
                const std::string &imageId)
   throw (CSMError) = 0;
   //> This method sets the unique identifier for the image to which the
   // sensor model pertains.
   //<
virtual CSMWarning* getSensorIdentifier(
               std::string &sensorId)
   const throw (CSMError) = 0;
   //> The getSensorIdentifier() method returns sensorId to indicate
   // which sensor was used to acquire the image. This sensorId is
   // meant to uniquely identify the sensor used to make the image.
   //<
virtual CSMWarning* getPlatformIdentifier(
                std::string &platformId)
   const throw (CSMError) = 0;
   //> The getPlatformIdentifier() method returns platformId to indicate
   // which platform was used to acquire the image. This platformId
   // is meant to uniquely identify the platform used to collect the // //image.
   //<
virtual CSMWarning* setReferencePoint(
                const double &x,
                const double &y,
                const double &z)
   throw (CSMError) = 0;
   //> This method returns the ground point indicating the general
   // location
   // of the image.
   //<
virtual CSMWarning* getReferencePoint(
                double &x,
                double &y,
                double &z)
   const throw (CSMError) = 0;
   //> This method sets the ground point indicating the general location
   // of the image.
   //<
virtual CSMWarning* getSensorModelName(
                std::string &name)
   const throw (CSMError) = 0;
   //> This method returns a string identifying the name of the senor model.
   //<
virtual CSMWarning* getImageSize(
                int& num_lines,
                int& num_samples)
   const throw (CSMError) = 0;
//> This method returns the number of lines and samples in the imaging
// operation.
//<
//---
// Sensor Model State
//---
virtual CSMWarning* getSensorModelState(
                std::string& state)
   const throw (CSMError) = 0;
   //> This method returns the current state of the model in an
   //  intermediate form. This intermediate form can then processed,
   //  for example, by saving to file so that this model
   //  can be instantiated at a later date. The derived SensorModel
   //  is responsible for saving all information needed to restore
   //  itself to its current state from this intermediate form.
   //  A NULL pointer is returned if it is not possible to save the
   //  current state.
   //<
//---
// Monoscopic Mensuration
//---
virtual CSMWarning* getValidHeightRange(
                double& minHeight,
                double& maxHeight)
   const throw (CSMError) = 0;
   //> The validHeightsRange() method returns the minimum and maximum
   // heights that describe the range of validity of the model. For
   // example, the model may not be valid at heights above the heights
   // of the sensor for physical models.
   //<
virtual CSMWarning *getValidImageRange(
                double& minRow,
                double& maxRow,
                double& minCol,
                double& maxCol)
   const throw (CSMError) = 0;
   //> The validImageRange() method returns the minimum and maximum
   //  values for image position (row and column) that describe the
   //  range of validity of the model. This range may not always match
   //  the physical size of the image. This method is used in
   //  conjunction with getValidHeightRange() to determine the full
   //  range of applicability of the sensor model.
   //<
virtual CSMWarning* getIlluminationDirection(
                const double& x,
                const double& y,
                const double& z,
                double& direction_x,
                double& direction_y,
                double& direction_z)
   const throw (CSMError) = 0;
   //> The getIlluminationDirection() method calculates the direction of
   // illumination at the given ground position x, y, z.
   //<
//---
// Error Correction
//---
virtual CSMWarning* getNumGeometricCorrectionSwitches(
                int& numSec)
   const throw (CSMError) = 0;
   //> The numGeometricCorrections() method returns the number
   // of geometric corrections defined for the sensor model.
   //<
virtual CSMWarning* getGeometricCorrectionName(
                const int& index,
                std::string &name)
   const throw (CSMError) = 0;
   //> This method returns the name for the sensor model parameter
   // indicated by the given index.
   //<
virtual CSMWarning* setCurrentGeometricCorrectionSwitch(
                const int& index,
                const bool &value,
                const CSMMisc::Param_CharType& parameterType)
   throw (CSMError) = 0;
   //> The setCurrentGeometricCorrectionSwitch() is
   // used to set the switch of the geometric correction
   // indicated by index.
   //<
virtual CSMWarning* getCurrentGeometricCorrectionSwitch(
                const int& index,
                bool &value)
   const throw (CSMError) = 0;
   //> The getCurrentGeometricCorrectionSwitch()
   // returns the value of the geometric correction switch
   // given by index.
   //<
virtual CSMWarning* getCurrentCrossCovarianceMatrix(
          const int numSM,
          const CSMSensorModel** SMs,
          const double line1,
          const double sample1,
          const double* lines,
          const double* samples,
          double **&crossCovarianceMatrix,
          int &M)
   const throw (CSMError) = 0;
   //> The getCurrentCovarianceMatrix() function returns a matrix
   //  containing all elements of the error cross covariance matrix
   //  between the instantiated sensor model and a specified second
   //  sensor model (SM2). This data supplies the data to compute
   //  cross covariance between images. Images may be correlated
   //  because they are taken by the same sensor or from sensors on
   //  the same platform. Images may also be correlated due to post
   //  processing of the sensor models. The data returned here may
   //  need to be supplemented with the single image covariance from
   //  getCurrentParameterCovariance() and getUnmodeledError().
   //<
virtual CSMWarning* getOriginalCrossCovarianceMatrix(
          const int numSM,
          const CSMSensorModel** SMs,
          const double line1,
          const double sample1,
          const double* lines,
          const double* samples,
          double **&crossCovarianceMatrix,
          int &M)
   const throw    (CSMError) = 0;
   //> The getOriginalCovarianceMatrix() function returns a matrix
   //  containing all elements of the error cross covariance matrix
   //  between the instantiated sensor model and a specified second
   //  sensor model (SM2). Images may be correlated because they
   //  are taken by the same sensor or from sensors on the same
   //  platform. Images may also be correlated due to post
   //  processing of the sensor models. The data returned here may
   //  need to be supplemented with the single image covariance from
   //  getOriginalParameterCovariance() and getUnmodeledError().
   //<
virtual CSMWarning* getUnmodeledError(
                const double line,
                const double sample,
                double covariance[4])
   const throw (CSMError) = 0;
   //> The getUnmodeledError() function gives a sensor specific
   //  error for the given input image point. The error is reported
   //  as the four terms of a 2x2 covariance mensuration error
   //  matrix. This error term is meant to map error terms that are
   //  not modeled in the sensor model to image space for inclusion
   //  in error propagation. The extra error is added to the
   //  mensuration error that may already be in the matrix.
   //<
virtual CSMWarning* getUnmodeledCrossCovariance(
                const double pt1Line,
                const double pt1Sample,
                const double pt2Line,
                const double pt2Sample,
                double crossCovariance[4])
   const throw (CSMError) = 0;
   //> The getUnmodeledCrossCovariance function gives the cross
   //  covariance for unmodeled error between two image points on
   //  the same image. The error is reported as the four terms of
   //  a 2x2 matrix. The unmodeled cross covariance is added to
   //  any values that may already be in the cross covariance matrix.
   //<
virtual CSMWarning* getCollectionIdentifier(
                std::string &collectionId)
   const throw (CSMError) = 0;
   //> This method returns a unique identifer that uniquely identifies
   // a collection activity by a sensor platform. This ID will vary
   // depending on the sensor type and platform.
   //<
virtual CSMWarning* isParameterShareable(
                const int& index,
                bool& shareable)
   const throw (CSMError) = 0;
   //> This method returns a flag to indicate whether or not a sensor
   // model parameter adjustments are shareable across images for the
      // sensor model adjustable parameter referenced by index.
      //<
/*
   virtual CSMWarning* getParameterSharingCriteria(
                   const int& index,
                   bool& requireModelNameMatch,
                   bool& requireSensorIDMatch,
                   bool& requirePlatformIDMatch,
                   bool& requireCollectionIDMatch,
                   bool& requireTrajectoryIDMatch,
                   bool& requireDateTimeMatch,
                   double& allowableTimeDelta)
      const throw (CSMError) = 0;
*/
   virtual CSMWarning* getParameterSharingCriteria(
                   const int& index,
                              std::vector<CSM_SHARING::csm_ParameterSharingCriteria>&
criteria)
      const throw (CSMError) = 0;
      //> This method returns characteristics to indicate how
      // the sensor model adjustable parameter referenced by index
      // may be shareable accross images.
      //<
   virtual CSMWarning* getSensorTypeAndMode(
                   CSMSensorTypeAndMode &sensorTypeAndMode)
      const throw (CSMError) = 0;
      //> This method returns a flag to indicate whether or not a sensor
      // ...
      //<
   virtual CSMWarning* getVersion( int &version )
      // implementation must include the following code:
         // version = CURRENT_CSM_VERSION; //CURRENT_CSM_VERSION is defined in CSMMisc.h
      const throw (CSMError) = 0;
#ifdef TESTAPIVERSION
   virtual CSMWarning* testAPIVersionSubclass(
                   std::string &text)
      const throw (CSMError) = 0;
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
#endif

