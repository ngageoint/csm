//#############################################################################
//
//    FILENAME:          RasterGM.h
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
//     26-Sep-2012   SCM    Moved all sensor partials to this class.
//     30-Oct-2012   SCM    Renamed to RasterGM.h
//     31-Oct-2012   SCM    Moved getTrajectoryIdentifier() to Model.  Moved
//                          unmodeled error methods to GeometricModel.  Made
//                          compute partial methods const.
//     01-Nov-2012   SCM    Moved unmodeled error methods back to RasterGM.
//     27-Nov-2012   JPK    Cleaned up some comments, variable names and
//                          changed return type for getCovarianceModel() from
//                          pointer to const reference.  Removed unused
//                          testAPIVersionSubclass().
//     29-Nov-2012   JPK    Modified computeAllSensorPartials to return
//                          results for a specified ParamSet.
//     06-Dec-2012   JPK    Changed ParamSet to param::Set.  De-inlined
//                          destructor and getFamily() methods.
//                          Replaced vector<double> with EcefLocus for
//                          imageTo*Locus methods.  Added inline method
//                          getCovarianceMatrix().  Provided reference
//                          implementations for computeAllSensorPartials()
//                          methods.
//    NOTES:
//
//#############################################################################

#ifndef __CSM_RASTERGM_H
#define __CSM_RASTERGM_H

#include "GeometricModel.h"

#define CSM_RASTER_FAMILY "Raster"

namespace csm
{
class CovarianceModel;

class CSM_EXPORT_API RasterGM : public GeometricModel
{
public:
   RasterGM() {}
   virtual ~RasterGM();
   
   virtual std::string getFamily() const;
      //> This method returns the Family ID for the current model.
      //<
   
   //---
   // Core Photogrammetry
   //---
   virtual ImageCoord groundToImage(const EcefCoord& groundPt,
                                    double desiredPrecision = 0.001,
                                    double* achievedPrecision = NULL,
                                    WarningList* warnings = NULL) const = 0;
      //> This method converts a ground coordinate (x,y,z meters ECEF)
      //  to an image coordinate (line,sample in full image space).
      //<

   virtual ImageCoordCovar groundToImage(const EcefCoordCovar& groundPt,
                                         double desiredPrecision = 0.001,
                                         double* achievedPrecision = NULL,
                                         WarningList* warnings = NULL) const = 0;
      //> This method converts a ground coordinate (x,y,z meters ECEF) and the
      //  associated 3x3 covariance to an image coordinate (line,sample 
      //  in full image space) with associated 2x2 covariance.
      //<
   virtual EcefCoord imageToGround(const ImageCoord& imagePt,
                                   double height,
                                   double desiredPrecision = 0.001,
                                   double* achievedPrecision = NULL,
                                   WarningList* warnings = NULL) const = 0;
      //> This method converts an image coordinate (line,sample
      //  in full image space) and known height relative to the 
      //  WGS-84 Ellipsoid to a ground coordinate (x,y,z meters ECEF).
      //<
   virtual EcefCoordCovar imageToGround(const ImageCoordCovar& imagePt,
                                        double height,
                                        double heightVariance,
                                        double desiredPrecision = 0.001,
                                        double* achievedPrecision = NULL,
                                        WarningList* warnings = NULL) const = 0;
      //> This method converts an image coordinate (line,sample
      //  in full image space) and its associated 2x2 covariance and a known
      //  height relative to the WGS-84 Ellipsoid with its associated variance
      //  to a ground coordinate (x,y,z meters ECEF) and its associated 3x3
      //  covariance.
      //<   
  virtual EcefLocus imageToProximateImagingLocus(
     const ImageCoord& imagePt,
     const EcefCoord& groundPt,
     double desiredPrecision = 0.001,
     double* achievedPrecision = NULL,
     WarningList* warnings = NULL) const = 0;
      //> This method computes a vector approximation of the imaging locus
      //  for an image coordinate (line,sample in full image space) nearest 
      //  the argument ground coordinate (x,y,z meters ECEF) The "achieved 
      //  precision" refers to the finding the origin of the locus and not
      //  its orientation.
      //<

   virtual EcefLocus imageToRemoteImagingLocus(
      const ImageCoord& imagePt,
      double desiredPrecision = 0.001,
      double* achievedPrecision = NULL,
      WarningList* warnings = NULL) const = 0;
      //> This method computes a vector approximation of the imaging locus
      //  for an image coordinate (line,sample in full image space).
      //  The "achieved precision" refers to the finding the origin of the
      //  locus and not its orientation.
      //<

   //---
   // Monoscopic Mensuration
   //---
   virtual ImageCoord getImageStart() const = 0;
      //> This method returns the starting coordinate in full image space
      //  for the imaging operation.
      //<
   virtual ImageVector getImageSize() const = 0;
      //> This method returns the number of lines and samples in full image
      //  space for the imaging operation.
      //
      //  Use getValidImageRange() to get the valid range of image 
      //  coordinates for this model.
      //<
   virtual std::pair<ImageCoord,ImageCoord> getValidImageRange() const = 0;
      //> This method returns the minimum and maximum image coordinates
      //  over which the current sensor model is valid. 
      //  This range does not always match the full image coverage as
      //  returned by getImageStart() / getImageSize().
      //  Used in conjunction with getValidHeightRange(), it is possible to 
      //  determine the full range of coordinates over which the sensor model
      //  is valid.
      //
      //  The minimum coordinate is returned as the first element of the pair
      //  and the maximum coordinate is returned as the second element of the
      //  pair.
      //<
   virtual std::pair<double,double> getValidHeightRange() const = 0;
      //> This method returns the minimum and maximum
      //  heights (relative to WGS-84 Ellipsoid) over which the sensor model is
      //  valid.  For example, a sensor model for an airborne platform which is
      //  aimed at the ground shouldn't be expected to return valid coordinates
      //  for heights above the height of the aircraft.
      //
      //  The minimum height is returned as the first element of the pair and
      //  the maximum height is returned as the second element of the pair.
      //
      //  If there are no limits defined for the current model,
      //  (-99999.0,99999.0) will be returned.
      //<
   virtual EcefVector getIlluminationDirection(const EcefCoord& gndPt) const = 0;
      //> This method returns a vector defining the direction of
      //  illumination at the given ground coordinate (x,y,z meters ECEF).
      //<

   //---
   // Time and Trajectory
   //---
   virtual double getImageTime(const ImageCoord& pt) const = 0;
      //> This method returns the time in seconds at which
      //  the pixel at the argument image coordinate was captured. 
      //  The time provided is relative to the reference date and time given
      //  by getReferenceDateAndTime.
      //<
   virtual EcefCoord getSensorPosition(const ImageCoord& pt) const = 0;
      //> This method returns the position of the physical sensor
      // (x,y,z meters ECEF) for the argument image coordinate.
      //<
   virtual EcefCoord getSensorPosition(double time) const = 0;
      //> This method returns the position of the physical sensor
      //  (x,y,z meters ECEF) for the argument imaging time.
      //<
   virtual EcefVector getSensorVelocity(const ImageCoord& pt) const = 0;
      //> This method returns the velocity of the physical sensor
      // (x,y,z meters per second ) for the argument image coordinate.
      //<
   virtual EcefVector getSensorVelocity(double time) const = 0;
      //> This method returns the velocity of the physical sensor
      // (x,y,z meters per second ) for the argument image coordinate.
      //<

   //---
   // Uncertainty Propagation
   //---
   typedef std::pair<double,double> SensorPartials;
                                                             
   virtual SensorPartials computeSensorPartials(
                int index,
                const EcefCoord& groundPt,
                double desiredPrecision   = 0.001,
                double* achievedPrecision = NULL,
                WarningList* warnings     = NULL) const = 0;
      //> This method returns the partial derivatives
      //  of image position with respect to an adjustable parameter specified
      //  by index, at a specified ground location (x,y,z meters ECEF)
      //  Derived model implementations may wish to implement this method by
      //  calling groundToImage() and passing the result to the other overload
      //  of computeSensorPartials().
      //<

   virtual SensorPartials computeSensorPartials(
                int index,
                const ImageCoord& imagePt,
                const EcefCoord& groundPt,
                double desiredPrecision   = 0.001,
                double* achievedPrecision = NULL,
                WarningList* warnings     = NULL) const = 0;
      //> This method returns the partial derivatives
      //  of image position with respect to an adjustable parameter specified
      //  by index.  This method differs from the previous version because it 
      //  expects both ground and image coordinates to be provided 
      //  (corresponding to the same location) for efficiency of the computation.
      //
      //  The results are unpredictable if the line and sample provided do not
      //  correspond to the result of calling groundToImage() with the given
      //  ground coordinate (x,y,z meters ECEF).
      //<
   
   virtual std::vector<SensorPartials> computeAllSensorPartials(
                const EcefCoord& groundPt,
                param::Set pSet           = param::VALID,
                double desiredPrecision   = 0.001,
                double* achievedPrecision = NULL,
                WarningList* warnings     = NULL) const;
      //> This method calculates the partial derivatives of image position
      //  (both line and sample) with respect to each of the desired 
      //  adjustable parameters at the given ground position.  
      //  The semantics for this method are the same as for 
      //  computeSensorPartials().
      //
      //  Derived models may wish to implement this directly for efficiency,
      //  but an implementation is provided here which calls 
      //  computeSensorPartials for each desired parameter index.
      //  
      //  The value returned is a vector of pairs with line partials in the
      //  first element and a sample partials in the second element.
      //<

   virtual std::vector<SensorPartials> computeAllSensorPartials(
                const ImageCoord& imagePt,
                const EcefCoord& groundPt,
                param::Set pSet           = param::VALID,
                double desiredPrecision   = 0.001,
                double* achievedPrecision = NULL,
                WarningList* warnings     = NULL) const;
      //> This method calculates the partial derivatives of image position
      //  (both line and sample) with respect to each of the desired 
      //  adjustable parameters at the given ground and image positions.  
      //  The semantics for this method are the same as for 
      //  computeSensorPartials().
      //
      //  Derived models may wish to implement this directly for efficiency,
      //  but an implementation is provided here which calls 
      //  computeSensorPartials for each desired parameter index.
      //
      //  The value returned is a vector of pairs with line partials in the
      //  first element and a sample partials in the second element.
      //<
   
   virtual std::vector<double> computeGroundPartials(const EcefCoord& groundPt) const = 0;
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

   virtual const CovarianceModel& getCovarianceModel() const = 0;
      //> This method returns the covariance model for this sensor model.
      //
      //  A new object is created every time this method is called.  The client
      //  is responsible for deallocating the object returned by this method.
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

};

} // namespace csm

#endif
