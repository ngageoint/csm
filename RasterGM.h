//#############################################################################
//
//    FILENAME:          CSMRasterGM.h
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
//     02-Jul-2012   SCM    Made getUnmodeledError() be implemented inline.
//     26-Sep-2012   JPK    Split SensorModel class into GeometricModel and
//                          RasterGM classes.  RasterGM is now the
//                          equivalent class to the previous SensorModel class.
//
//    NOTES:
//
//#############################################################################

#ifndef __CSMRASTERGM_H
#define __CSMRASTERGM_H

#include "CSMGeometricModel.h"

#define CSM_RASTER_FAMILY "Raster"

namespace csm
{

class CovarianceModel;

class CSM_EXPORT_API RasterGM : public GeometricModel
{
public:
   RasterGM() {}
   virtual ~RasterGM() { }

   virtual std::string getFamily() const { return (GeometricModel::getFamily() +
                                                   CSM_RASTER_FAMILY); }

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

   virtual ImageCoordCovar groundToImage(const EcefCoordCovar& groundPt,
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
   virtual EcefCoordCovar imageToGround(const ImageCoordCovar& imagePt,
                                        double height,
                                        double heightVariance,
                                        double desired_precision = 0.001,
                                        double* achieved_precision = NULL,
                                        WarningList* warnings = NULL) const = 0;
      //> This method converts a given line and sample (pixels) in image space
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
      //  imaging operation.
      //<
   virtual ImageVector getImageSize() const = 0;
      //> This method returns the number of lines and samples in the imaging
      //  operation.
      //
      //  Here the returned image vector represents the size of the image
      //  as an image space vector.  Use getValidImageRange() to get the valid
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
      //
      //  If there are no limits defined for the current model,
      //  (-99999,99999) will be returned.
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
   // Uncertainty Propagation
   //---
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
      
   inline std::vector<double> getUnmodeledError(const ImageCoord& pt) const
   { return getUnmodeledCrossCovariance(pt, pt); }
      //> The getUnmodeledError() function gives the image-space covariance for
      //  any unmodeled sensor error for the given input image point. The error
      //  is reported as the four terms of a 2x2 covariance matrix, returned as
      //  a 4 element vector.  This covariance is meant to account for errors
      //  that are not modeled by the sensor model parameters.
      //<

   virtual std::vector<double> getUnmodeledCrossCovariance(
      const ImageCoord& pt1,
      const ImageCoord& pt2) const = 0;
      //> The getUnmodeledCrossCovariance function gives the image-space cross
      //  covariance for any unmodeled sensor error between two image points on
      //  the same image. The error is reported as the four terms of a 2x2
      //  matrix, returned as a 4 element vector.  This covariance is meant to
      //  account for errors that are not modeled by the sensor model
      //  parameters.
      //<

   virtual CovarianceModel* getCovarianceModel() const = 0;
      //> This method returns the covariance model for this sensor model.
      //
      //  A new object is created every time this method is called.  The client
      //  is responsible for deallocating the object returned by this method.
      //<

#ifdef TESTAPIVERSION
   virtual std::string testAPIVersionSubclass() const = 0;
      //> The testAPIVersionSubclass method provides a means to
      //  demonstrate and test the subclass backward compatibility
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

