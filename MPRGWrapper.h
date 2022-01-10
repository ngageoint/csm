//#############################################################################
//
//    FILENAME:          MPRGWapper.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for a wrapper class which add the MultiPoint functionality to
//    any RasterGM (though not efficiently).  The purpose of this class is to
//    allow developers to test methods using the MultiPoint interface with
//    existing sensor models.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     
//     08-Dec-2021   JPK      Initial Coding
//
//    NOTES:
//
//#############################################################################

#ifndef __CSM_MPRGWRAPPER_H
#define __CSM_MPRGWRAPPER_H

#include "MultiPointRasterGM.h"
#include <memory>

namespace csm
{

class CSM_EXPORT_API MPRGWrapper : public MultiPointRasterGM
{
public:
   MPRGWrapper();
   
   MPRGWrapper(const std::shared_ptr<RasterGM>& rasterModel);
   
   virtual ~MPRGWrapper();
   
   void setRasterModel(const std::shared_ptr<RasterGM>& rasterModel);

   //***
   // MultiPointRasterGM methods.
   //***
   virtual MultiImageCoord multiGroundToImage(const MultiEcefCoord& groundPts,
                                             double desiredPrecision = 0.001,
                                             MultiDbl* achievedPrecisions = NULL,
                                             WarningList* warnings = NULL) const;
        //> This method converts the given vector of groundPt (vectors of x,y,z in ECEF meters) to a
        //  returned a vector of image coordinate (vector of line, sample in full image space pixels).
        //
        //  Iterative algorithms will use desiredPrecision, in meters, as the
        //  convergence criterion, otherwise it will be ignored.
        //
        //  If a non-NULL vector of achievedPrecisions argument is received, it will be
        //  populated with the actual precision, in meters, achieved by iterative
        //  algorithms and 0.0 for deterministic algorithms.
        //
        //  If a non-NULL warnings argument is received, it will be populated
        //  as applicable.
        //<
      
   virtual MultiImageCoordCovar multiGroundToImage(const MultiEcefCoordCovar& groundPts,
                                                   double desiredPrecision = 0.001,
                                                   MultiDbl* achievedPrecisions = NULL,
                                                   WarningList* warnings = NULL) const;
   //> This method converts the given vector of groundPts (vector of x,y,z in ECEF meters and
   //  corresponding 3x3 covariance in ECEF meters squared) to a returned vector of 
   //  image coordinates with covariance (line, sample in full image space
   //  pixels and corresponding 2x2 covariance in pixels squared).
   //
   //  Iterative algorithms will use desiredPrecision, in meters, as the
   //  convergence criterion, otherwise it will be ignored.
   //
   //  If a non-NULL achievedPrecision argument is received, it will be
   //  populated with the actual precision, in meters, achieved by iterative
   //  algorithms and 0.0 for deterministic algorithms.
   //
   //  If a non-NULL warnings arguments is received, it will be populated
   //  as applicable.
   //<
   
   virtual MultiEcefCoord multiImageToGround(const MultiImageCoordWithHeight& pts,
                                             double desiredPrecision = 0.001,
                                             MultiDbl* achievedPrecisions = NULL,
                                             WarningList* warnings = NULL) const;
   //> This method converts the given vector of imagePts (vector of 
   //  line,sample (full image space pixels),height (meters relative to WGS-84 Ellipsod) triplets
   ///  to a returned vector of ground coordinates (x,y,z in ECEF meters).
   //
   //  Iterative algorithms will use desiredPrecision, in meters, as the
   //  convergence criterion, otherwise it will be ignored.
   //
   //  If a non-NULL achievedPrecision argument is received, it will be
   //  populated with the actual precision, in meters, achieved by iterative
   //  algorithms and 0.0 for deterministic algorithms.
   //
   //  If a non-NULL warnings argument is received, it will be populated
   //  as applicable.
   //<
   
   virtual MultiEcefCoordCovar multiImageToGround(const MultiImageCoordCovarWithHeight& imagePts,
                                                  double desiredPrecision = 0.001,
                                                  MultiDbl* achievedPrecisions = NULL,
                                                  WarningList* warnings = NULL) const;
   //> This method converts the given vector of imagePts (vector line, sample in full image
   //  space pixels and corresponding 2x2 covariance in pixels squared)
   //  and given vector of heights (in meters relative to the WGS-84 ellipsoid) and
   //  corresponding vector of heightVariances (in meters) to a returned vector of ground
   //  coordinates with covariance (x,y,z in ECEF meters and corresponding
   //  3x3 covariance in ECEF meters squared).
   //
   //  Iterative algorithms will use desiredPrecision, in meters, as the
   //  convergence criterion, otherwise it will be ignored.
   //
   //  If a non-NULL achievedPrecision argument is received, it will be
   //  populated with the actual precision, in meters, achieved by iterative
   //  algorithms and 0.0 for deterministic algorithms.
   //
   //  If a non-NULL warnings argument is received, it will be populated
   //  as applicable.
   //<
   
   virtual MultiEcefLocus multiImageToProximateImagingLocus(const MultiImageEcefCoordPair& imageAndGroundPts,
                                                            double desiredPrecision = 0.001,
                                                            MultiDbl* achievedPrecisions = NULL,
                                                            WarningList* warnings = NULL) const;
   //> This method, for the given vector of imagePts (vector of line, sample in full image space
   //  pixels), returns a vector of position and direction of the imaging locus
   //  nearest the vector of given groundPts (vector of x,y,z in ECEF meters).
   //
   //  Note that there are two opposite directions possible.  Both are
   //  valid, so either can be returned; the calling application can convert
   //  to the other as necessary.
   //
   //  Iterative algorithms will use desiredPrecision, in meters, as the
   //  convergence criterion for the locus position, otherwise it will be
   //  ignored.
   //
   //  If a non-NULL achievedPrecision argument is received, it will be
   //  populated with the actual precision, in meters, achieved by iterative
   //  algorithms and 0.0 for deterministic algorithms.
   //
   //  If a non-NULL warnings argument is received, it will be populated
   //  as applicable.
   //<
   
   virtual MultiEcefLocus multiImageToRemoteImagingLocus(const MultiImageCoord& imagePts,
                                                         double desiredPrecision = 0.001,
                                                         MultiDbl* achievedPrecisions = NULL,
                                                         WarningList* warnings = NULL) const;
   //> This method, for the given vector of imagePts (vector of line, sample in full image space
   //  pixels), returns a vector of positions and directions of the imaging locus
   //  at the sensor.
   //
   //  Note that there are two opposite directions possible.  Both are
   //  valid, so either can be returned; the calling application can convert
   //  to the other as necessary.
   //
   //  Iterative algorithms will use desiredPrecision, in meters, as the
   //  convergence criterion for the locus position, otherwise it will be
   //  ignored.
   //
   //  If a non-NULL achievedPrecision argument is received, it will be
   //  populated with the actual precision, in meters, achieved by iterative
   //  algorithms and 0.0 for deterministic algorithms.
   //
   //  If a non-NULL warnings argument is received, it will be populated
   //  as applicable.
   //
   //  Notes:
   //
   //  The remote imaging locus is only well-defined for optical sensors.
   //  It is undefined for SAR sensors and might not be available for
   //  polynomial and other non-physical models.  The
   //  imageToProximateImagingLocus method should be used instead where
   //  possible.
   //<
   
   virtual MultiEcefVector multiGetIlluminationDirection(const MultiEcefCoord& groundPts) const;
   virtual MultiDbl multiGetImageTime(const MultiImageCoord& imagePts) const;
  
   //> This method returns the time in seconds at which the pixels at the
   //  given vector of imagePts (vector of line, sample in full image space pixels) was captured
   //
   //  The time provided is relative to the reference date and time given
   //  by the Model::getReferenceDateAndTime method.
   //<
   
   virtual MultiEcefCoord multiGetSensorPosition(const MultiImageCoord& imagePts) const;
   //> This method returns the position of the physical sensor
   // (x,y,z in ECEF meters) when the pixel at the given vector of imagePts
   // (vector of line, sample in full image space pixels) was captured.
   //
   // A csm::Error will be thrown if the sensor position is not available.
   //<
   
   virtual MultiEcefCoord multiGetSensorPosition(const MultiDbl& times) const;
   //> This method returns a vector of positions of the physical sensor
   //  (x,y,z meters ECEF) at the given times relative to the reference date
   //  and time given by the Model::getReferenceDateAndTime method.
   //<
   
   virtual MultiEcefVector multiGetSensorVelocity(MultiImageCoord& imagePts) const;
   //> This method returns a vector of velocity of the physical sensor
   // (x,y,z in ECEF meters per second) when the pixel at the given vector of imagePts
   // (line, sample in full image space pixels) was captured.
   //<
   
   virtual MultiEcefVector multiGetSensorVelocity(const MultiDbl& times) const;
   //> This method returns a vector of velocity of the physical sensor
   //  (x,y,z in ECEF meters per second ) at the given set of times relative to the
   //  reference date and time given by the Model::getReferenceDateAndTime
   //  method.
   //<
   
   virtual SensorPartialsVctr multiComputeSensorPartials(int index,
                                                         const MultiEcefCoord& groundPts,
                                                         double desiredPrecision = 0.001,
                                                         MultiDbl* achievedPrecision = NULL,
                                                         WarningList* warnings = NULL) const; 
   //>    This is the multi-point version of RasterGM::computeSensorPartials that takes only
   //     ground points as input. It returns a vector of partials for the given parameter
   //     at the given points.
   //<
   
   virtual SensorPartialsVctr multiComputeSensorPartials(int index,
                                                         const MultiImageEcefCoordPair& imageAndGroundPts,
                                                         double desiredPrecision = 0.001,
                                                         MultiDbl* achievedPrecision = NULL,
                                                         WarningList* warnings = NULL) const;
   //> This is the multi-point version of RasterGM::computeSensorPartials that takes 
   //      ground points and image points as input. It returns a vector of partials for the given parameter
   //     at the given points.
   //<
   
   virtual MultiSensorPartialsVctr multiComputeAllSensorPartials(const MultiEcefCoord& roundPts,
                                                                 param::Set pSet = param::VALID,
                                                                 double desiredPrecision = 0.001,
                                                                 MultiDbl* achievedPrecision = NULL,
                                                                 WarningList* warnings = NULL) const;
   //> This is the multi-point version of RasterGM::computeAllSensorPartials that takes
   //  ground points as input. It returns a vector of vectors (a matrix) of sensor partials.
   //  The matrix is ordered by points (outer vector) and by parameters (inner vectors).
   //<
   
   virtual MultiSensorPartialsVctr multiComputeAllSensorPartials(const MultiImageEcefCoordPair& imageAnfGroundPts,
                                                                 param::Set pSet = param::VALID,
                                                                 double desiredPrecision = 0.001,
                                                                 MultiDbl* achievedPrecision = NULL,
                                                                 WarningList* warnings = NULL) const;
   //> This is the multi-point version of RasterGM::computeAllSensorPartials that takes
   //  ground points and image points as input. It returns a vector of vectors (a matrix) of sensor partials.
   //  The matrix is ordered by points (outer vector) and by parameters (inner vectors).
   //<
   
   virtual MultiDblVctr multiComputeGroundPartials(const MultiEcefCoord& groundPts) const;
   //> This method returns the partial derivatives of line and sample at each given ground point. 
   //  The outer vector is npoints long. Each inner vector is 6 elements long ordered as follows:
   //
   //-  [0] = line wrt x
   //-  [1] = line wrt y
   //-  [2] = line wrt z
   //-  [3] = sample wrt x
   //-  [4] = sample wrt y
   //-  [5] = sample wrt z
   //<
   
   virtual MultiDblVctr multiGetUnmodeledError(const MultiImageCoord& imagePts) const;
   //> This method returns the 2x2 line and sample covariance (in pixels
   //  squared) at each given imagePt for any model error not accounted for
   //  by the model parameters.
   //
   //  The outer vector returned has one element per point.
   //  The inner vector returned is a vector of four elements as follows:
   //
   //-  [0] = line variance
   //-  [1] = line/sample covariance
   //-  [2] = sample/line covariance
   //-  [3] = sample variance
   //<
   
   virtual MultiDblVctr multiGetUnmodeledCrossCovariance(const MultiImageCoordPair& ptsPairs) const;
   //> This method returns the 2x2 line and sample unmodeled error cross covariance
   //  (in pixels squared) between the every combination of the points
   //  in the two input vectors.
   //  The return is a vector of vectors. There is one vector of vectors for each point in
   //  imagepts1. The inner vector is the set of cross-covariances between the point and all
   //  of the other points.
   //  The covariance between each point and itself is not given.
   //<
   //---
   // RasterGM methods
   //---
   virtual ImageCoord groundToImage(const EcefCoord& groundPt,
                                    double desiredPrecision = 0.001,
                                    double* achievedPrecision = NULL,
                                    WarningList* warnings = NULL) const;
      //> This method converts the given groundPt (x,y,z in ECEF meters) to a
      //  returned image coordinate (line, sample in full image space pixels).
      //
      //  Iterative algorithms will use desiredPrecision, in meters, as the
      //  convergence criterion, otherwise it will be ignored.
      //
      //  If a non-NULL achievedPrecision argument is received, it will be
      //  populated with the actual precision, in meters, achieved by iterative
      //  algorithms and 0.0 for deterministic algorithms.
      //
      //  If a non-NULL warnings argument is received, it will be populated
      //  as applicable.
      //<

   virtual ImageCoordCovar groundToImage(const EcefCoordCovar& groundPt,
                                         double desiredPrecision = 0.001,
                                         double* achievedPrecision = NULL,
                                         WarningList* warnings = NULL) const;
      //> This method converts the given groundPt (x,y,z in ECEF meters and
      //  corresponding 3x3 covariance in ECEF meters squared) to a returned
      //  image coordinate with covariance (line, sample in full image space
      //  pixels and corresponding 2x2 covariance in pixels squared).
      //
      //  Iterative algorithms will use desiredPrecision, in meters, as the
      //  convergence criterion, otherwise it will be ignored.
      //
      //  If a non-NULL achievedPrecision argument is received, it will be
      //  populated with the actual precision, in meters, achieved by iterative
      //  algorithms and 0.0 for deterministic algorithms.
      //
      //  If a non-NULL warnings argument is received, it will be populated
      //  as applicable.
      //<

   virtual EcefCoord imageToGround(const ImageCoord& imagePt,
                                   double height,
                                   double desiredPrecision = 0.001,
                                   double* achievedPrecision = NULL,
                                   WarningList* warnings = NULL) const;
      //> This method converts the given imagePt (line,sample in full image
      //  space pixels) and given height (in meters relative to the WGS-84
      //  ellipsoid) to a returned ground coordinate (x,y,z in ECEF meters).
      //
      //  Iterative algorithms will use desiredPrecision, in meters, as the
      //  convergence criterion, otherwise it will be ignored.
      //
      //  If a non-NULL achievedPrecision argument is received, it will be
      //  populated with the actual precision, in meters, achieved by iterative
      //  algorithms and 0.0 for deterministic algorithms.
      //
      //  If a non-NULL warnings argument is received, it will be populated
      //  as applicable.
      //<

   virtual EcefCoordCovar imageToGround(const ImageCoordCovar& imagePt,
                                        double height,
                                        double heightVariance,
                                        double desiredPrecision = 0.001,
                                        double* achievedPrecision = NULL,
                                        WarningList* warnings = NULL) const;
      //> This method converts the given imagePt (line, sample in full image
      //  space pixels and corresponding 2x2 covariance in pixels squared)
      //  and given height (in meters relative to the WGS-84 ellipsoid) and
      //  corresponding heightVariance (in meters) to a returned ground
      //  coordinate with covariance (x,y,z in ECEF meters and corresponding
      //  3x3 covariance in ECEF meters squared).
      //
      //  Iterative algorithms will use desiredPrecision, in meters, as the
      //  convergence criterion, otherwise it will be ignored.
      //
      //  If a non-NULL achievedPrecision argument is received, it will be
      //  populated with the actual precision, in meters, achieved by iterative
      //  algorithms and 0.0 for deterministic algorithms.
      //
      //  If a non-NULL warnings argument is received, it will be populated
      //  as applicable.
      //<

   virtual EcefLocus imageToProximateImagingLocus(
      const ImageCoord& imagePt,
      const EcefCoord& groundPt,
      double desiredPrecision = 0.001,
      double* achievedPrecision = NULL,
      WarningList* warnings = NULL) const;
      //> This method, for the given imagePt (line, sample in full image space
      //  pixels), returns the position and direction of the imaging locus
      //  nearest the given groundPt (x,y,z in ECEF meters).
      //
      //  Note that there are two opposite directions possible.  Both are
      //  valid, so either can be returned; the calling application can convert
      //  to the other as necessary.
      //
      //  Iterative algorithms will use desiredPrecision, in meters, as the
      //  convergence criterion for the locus position, otherwise it will be
      //  ignored.
      //
      //  If a non-NULL achievedPrecision argument is received, it will be
      //  populated with the actual precision, in meters, achieved by iterative
      //  algorithms and 0.0 for deterministic algorithms.
      //
      //  If a non-NULL warnings argument is received, it will be populated
      //  as applicable.
      //<

   virtual EcefLocus imageToRemoteImagingLocus(
      const ImageCoord& imagePt,
      double desiredPrecision = 0.001,
      double* achievedPrecision = NULL,
      WarningList* warnings = NULL) const;
      //> This method, for the given imagePt (line, sample in full image space
      //  pixels), returns the position and direction of the imaging locus
      //  at the sensor.
      //
      //  Note that there are two opposite directions possible.  Both are
      //  valid, so either can be returned; the calling application can convert
      //  to the other as necessary.
      //
      //  Iterative algorithms will use desiredPrecision, in meters, as the
      //  convergence criterion for the locus position, otherwise it will be
      //  ignored.
      //
      //  If a non-NULL achievedPrecision argument is received, it will be
      //  populated with the actual precision, in meters, achieved by iterative
      //  algorithms and 0.0 for deterministic algorithms.
      //
      //  If a non-NULL warnings argument is received, it will be populated
      //  as applicable.
      //
      //  Notes:
      //
      //  The remote imaging locus is only well-defined for optical sensors.
      //  It is undefined for SAR sensors and might not be available for
      //  polynomial and other non-physical models.  The
      //  imageToProximateImagingLocus method should be used instead where
      //  possible.
      //<````````````````````````````````````````````````````````1111111111111111111111111111111111111111111111111111111111111111111111111111

   virtual ImageCoord getImageStart() const;
      //> This method returns the starting coordinate (line, sample in full
      //  image space pixels) for the imaging operation.  Typically (0,0).
      //<

   virtual ImageVector getImageSize() const;
      //> This method returns the number of lines and samples in full image
      //  space pixels for the imaging operation.
      //
      //  Note that the model might not be valid over the entire imaging
      //  operation.  Use getValidImageRange() to get the valid range of image
      //  coordinates.
      //<

   virtual std::pair<ImageCoord,ImageCoord> getValidImageRange() const;
      //> This method returns the minimum and maximum image coordinates
      //  (line, sample in full image space pixels), respectively, over which
      //  the current model is valid.  The image coordinates define opposite
      //  corners of a rectangle whose sides are parallel to the line and
      //  sample axes.
      //
      //  The valid image range does not always match the full image
      //  coverage as returned by the getImageStart and getImageSize methods.
      //
      //  Used in conjunction with the getValidHeightRange method, it is
      //  possible to determine the full range of ground coordinates over which
      //  the model is valid.
      //<

   virtual std::pair<double,double> getValidHeightRange() const;
      //> This method returns the minimum and maximum heights (in meters
      //  relative to WGS-84 ellipsoid), respectively, over which the model is
      //  valid.  For example, a model for an airborne platform might not be
      //  designed to return valid coordinates for heights above the aircraft.
      //
      //  If there are no limits defined for the model, (-99999.0,99999.0)
      //  will be returned.
      //<

   virtual EcefVector getIlluminationDirection(const EcefCoord& groundPt) const;
      //> This method returns a vector defining the direction of
      //  illumination at the given groundPt (x,y,z in ECEF meters).
      //  Note that there are two opposite directions possible.  Both are
      //  valid, so either can be returned; the calling application can convert
      //  to the other as necessary.
      //<

   virtual double getImageTime(const ImageCoord& imagePt) const;
      //> This method returns the time in seconds at which the pixel at the
      //  given imagePt (line, sample in full image space pixels) was captured
      //
      //  The time provided is relative to the reference date and time given
      //  by the Model::getReferenceDateAndTime method.
      //<

   virtual EcefCoord getSensorPosition(const ImageCoord& imagePt) const;
      //> This method returns the position of the physical sensor
      // (x,y,z in ECEF meters) when the pixel at the given imagePt
      // (line, sample in full image space pixels) was captured.
      //
      // A csm::Error will be thrown if the sensor position is not available.
      //<

   virtual EcefCoord getSensorPosition(double time) const;
      //> This method returns the position of the physical sensor
      //  (x,y,z meters ECEF) at the given time relative to the reference date
      //  and time given by the Model::getReferenceDateAndTime method.
      //<

   virtual EcefVector getSensorVelocity(const ImageCoord& imagePt) const;
      //> This method returns the velocity of the physical sensor
      // (x,y,z in ECEF meters per second) when the pixel at the given imagePt
      // (line, sample in full image space pixels) was captured.
      //<

   virtual EcefVector getSensorVelocity(double time) const;
      //> This method returns the velocity of the physical sensor
      //  (x,y,z in ECEF meters per second ) at the given time relative to the
      //  reference date and time given by the Model::getReferenceDateAndTime
      //  method.
      //<

   typedef std::pair<double,double> SensorPartials;
      //> This type is used to hold the partial derivatives of line and
      //  sample, respectively, with respect to a model parameter.
      //  The units are pixels per the model parameter units.
      //<

   virtual SensorPartials computeSensorPartials(
                int index,
                const EcefCoord& groundPt,
                double desiredPrecision   = 0.001,
                double* achievedPrecision = NULL,
                WarningList* warnings     = NULL) const;
      //> This is one of two overloaded methods.  This method takes only
      //  the necessary inputs.  Some effieciency can be obtained by using the
      //  other method.  Even more efficiency can be obtained by using the
      //  computeAllSensorPartials method.
      //
      //  This method returns the partial derivatives of line and sample
      //  (in pixels per the applicable model parameter units), respectively,
      //  with respect to the model parameter given by index at the given
      //  groundPt (x,y,z in ECEF meters).
      //
      //  Derived model implementations may wish to implement this method by
      //  calling the groundToImage method and passing the resulting image
      //  coordinate to the other computeSensorPartials method.
      //
      //  If a non-NULL achievedPrecision argument is received, it will be
      //  populated with the highest actual precision, in meters, achieved by
      //  iterative algorithms and 0.0 for deterministic algorithms.
      //
      //  If a non-NULL achievedPrecision argument is received, it will be
      //  populated with the actual precision, in meters, achieved by iterative
      //  algorithms and 0.0 for deterministic algorithms.
      //
      //  If a non-NULL warnings argument is received, it will be populated
      //  as applicable.
      //<

   virtual SensorPartials computeSensorPartials(
                int index,
                const ImageCoord& imagePt,
                const EcefCoord& groundPt,
                double desiredPrecision   = 0.001,
                double* achievedPrecision = NULL,
                WarningList* warnings     = NULL) const;
      //> This is one of two overloaded methods.  This method takes
      //  an input image coordinate for efficiency.  Even more efficiency can
      //  be obtained by using the computeAllSensorPartials method.
      //
      //  This method returns the partial derivatives of line and sample
      //  (in pixels per the applicable model parameter units), respectively,
      //  with respect to the model parameter given by index at the given
      //  groundPt (x,y,z in ECEF meters).
      //
      //  The imagePt, corresponding to the groundPt, is given so that it does
      //  not need to be computed by the method.  Results are unpredictable if
      //  the imagePt provided does not correspond to the result of calling the
      //  groundToImage method with the given groundPt.
      //
      //  Implementations with iterative algorithms (typically ground-to-image
      //  calls) will use desiredPrecision, in meters, as the convergence
      //  criterion, otherwise it will be ignored.
      //
      //  If a non-NULL achievedPrecision argument is received, it will be
      //  populated with the highest actual precision, in meters, achieved by
      //  iterative algorithms and 0.0 for deterministic algorithms.
      //
      //  If a non-NULL warnings argument is received, it will be populated
      //  as applicable.
      //<

   virtual std::vector<SensorPartials> computeAllSensorPartials(
                const EcefCoord& groundPt,
                param::Set pSet           = param::VALID,
                double desiredPrecision   = 0.001,
                double* achievedPrecision = NULL,
                WarningList* warnings     = NULL) const;
      //> This is one of two overloaded methods.  This method takes only
      //  the necessary inputs.  Some effieciency can be obtained by using the
      //  other method.
      //
      //  This method returns the partial derivatives of line and sample
      //  (in pixels per the applicable model parameter units), respectively,
      //  with respect to to each of the desired model parameters at the given
      //  groundPt (x,y,z in ECEF meters).  Desired model parameters are
      //  indicated by the given pSet.
      //
      //  Implementations with iterative algorithms (typically ground-to-image
      //  calls) will use desiredPrecision, in meters, as the convergence
      //  criterion, otherwise it will be ignored.
      //
      //  If a non-NULL achievedPrecision argument is received, it will be
      //  populated with the highest actual precision, in meters, achieved by
      //  iterative algorithms and 0.0 for deterministic algorithms.
      //
      //  If a non-NULL warnings argument is received, it will be populated
      //  as applicable.
      //
      //  The value returned is a vector of pairs with line and sample partials
      //  for one model parameter in each pair.  The indices of the
      //  corresponding model parameters can be found by calling the
      //  getParameterSetIndices method for the given pSet.
      //
      //  Derived models may wish to implement this directly for efficiency,
      //  but an implementation is provided here that calls the
      //  computeSensorPartials method for each desired parameter index.
      //<

   virtual std::vector<SensorPartials> computeAllSensorPartials(
                const ImageCoord& imagePt,
                const EcefCoord& groundPt,
                param::Set pSet           = param::VALID,
                double desiredPrecision   = 0.001,
                double* achievedPrecision = NULL,
                WarningList* warnings     = NULL) const;
      //> This is one of two overloaded methods.  This method takes
      //  an input image coordinate for efficiency.
      //
      //  This method returns the partial derivatives of line and sample
      //  (in pixels per the applicable model parameter units), respectively,
      //  with respect to to each of the desired model parameters at the given
      //  groundPt (x,y,z in ECEF meters).  Desired model parameters are
      //  indicated by the given pSet.
      //
      //  The imagePt, corresponding to the groundPt, is given so that it does
      //  not need to be computed by the method.  Results are unpredictable if
      //  the imagePt provided does not correspond to the result of calling the
      //  groundToImage method with the given groundPt.
      //
      //  Implementations with iterative algorithms (typically ground-to-image
      //  calls) will use desiredPrecision, in meters, as the convergence
      //  criterion, otherwise it will be ignored.
      //
      //  If a non-NULL achievedPrecision argument is received, it will be
      //  populated with the highest actual precision, in meters, achieved by
      //  iterative algorithms and 0.0 for deterministic algorithms.
      //
      //  If a non-NULL warnings argument is received, it will be populated
      //  as applicable.
      //
      //  The value returned is a vector of pairs with line and sample partials
      //  for one model parameter in each pair.  The indices of the
      //  corresponding model parameters can be found by calling the
      //  getParameterSetIndices method for the given pSet.
      //
      //  Derived models may wish to implement this directly for efficiency,
      //  but an implementation is provided here that calls the
      //  computeSensorPartials method for each desired parameter index.
      //<

   virtual std::vector<double> computeGroundPartials(const EcefCoord& groundPt) const;
      //> This method returns the partial derivatives of line and sample
      //  (in pixels per meter) with respect to the given groundPt
      //  (x,y,z in ECEF meters).
      //
      //  The value returned is a vector with six elements as follows:
      //
      //-  [0] = line wrt x
      //-  [1] = line wrt y
      //-  [2] = line wrt z
      //-  [3] = sample wrt x
      //-  [4] = sample wrt y
      //-  [5] = sample wrt z
      //<

   virtual const CorrelationModel& getCorrelationModel() const;
      //> This method returns a reference to a CorrelationModel.
      //  The CorrelationModel is used to determine the correlation between
      //  the model parameters of different models of the same type.
      //  These correlations are used to establish the "a priori" cross-covariance
      //  between images. While some applications (such as generation of a 
      //  replacement sensor model) may wish to call this method directly,
      //  it is reccommended that the inherited method 
      //  GeometricModel::getCrossCovarianceMatrix() be called instead.
      //<

   virtual std::vector<double> getUnmodeledCrossCovariance(
                const ImageCoord& pt1,
                const ImageCoord& pt2) const;
      //> This method returns the 2x2 line and sample cross covariance
      //  (in pixels squared) between the given imagePt1 and imagePt2 for any
      //  model error not accounted for by the model parameters.  The error is
      //  reported as the four terms of a 2x2 matrix, returned as a 4 element
      //  vector.
      //<
      
   //---
   // GeometricModel methods
   //***
   virtual EcefCoord getReferencePoint() const;
      //> This method returns the ground point indicating the general
      //  location of the image.
      //<

   virtual void setReferencePoint(const EcefCoord& groundPt);
      //> This method sets the ground point indicating the general location
      //  of the image.
      //<

   virtual int getNumParameters() const;
      //> This method returns the number of adjustable parameters.
      //<

   virtual std::string getParameterName(int index) const;
      //> This method returns the name for the adjustable parameter
      //  indicated by the given index.
      //
      //  If the index is out of range, a csm::Error may be thrown.
      //<

   virtual std::string getParameterUnits(int index) const;
      //> This method returns the units for the adjustable parameter
      //  indicated by the given index.  This string is intended for human
      //  consumption, not automated analysis.  Preferred unit names are:
      //
      //-    meters                "m"
      //-    centimeters           "cm"
      //-    millimeters           "mm"
      //-    micrometers           "um"
      //-    nanometers            "nm"
      //-    kilometers            "km"
      //-    inches-US             "inch"
      //-    feet-US               "ft"
      //-    statute miles         "mi"
      //-    nautical miles        "nmi"
      //-
      //-    radians               "rad"
      //-    microradians          "urad"
      //-    decimal degrees       "deg"
      //-    arc seconds           "arcsec"
      //-    arc minutes           "arcmin"
      //-
      //-    seconds               "sec"
      //-    minutes               "min"
      //-    hours                 "hr"
      //-
      //-    steradian             "sterad"
      //-
      //-    none                  "unitless"
      //-
      //-    lines per second      "lines/sec"
      //-    samples per second    "samples/sec"
      //-    frames per second     "frames/sec"
      //-
      //-    watts                 "watt"
      //-
      //-    degrees Kelvin        "K"
      //-
      //-    gram                  "g"
      //-    kilogram              "kg"
      //-    pound - US            "lb"
      //-
      //-    hertz                 "hz"
      //-    megahertz             "mhz"
      //-    gigahertz             "ghz"
      //
      //  Units may be combined with "/" or "." to indicate division or
      //  multiplication.  The caret symbol "^" can be used to indicate
      //  exponentiation.  Thus "m.m" and "m^2" are the same and indicate
      //  square meters.  The return "m/sec^2" indicates an acceleration in
      //  meters per second per second.
      //
      //  Derived classes may choose to return additional unit names, as
      //  required.
      //<

   virtual bool hasShareableParameters() const;
      //> This method returns true if there exists at least one adjustable
      //  parameter on the model that is shareable.  See the
      //  isParameterShareable() method.  This method should return false if
      //  all calls to isParameterShareable() return false.
      //<

   virtual bool isParameterShareable(int index) const;
      //> This method returns a flag to indicate whether or not the adjustable
      //  parameter referenced by index is shareable across models.
      //<

   virtual csm::SharingCriteria getParameterSharingCriteria(int index) const;
      //> This method returns characteristics to indicate how the adjustable
      //  parameter referenced by index is shareable across models.
      //<

   virtual double getParameterValue(int index) const;
      //> This method returns the value of the adjustable parameter
      //  referenced by the given index.
      //<

   virtual void setParameterValue(int index, double value);
      //> This method sets the value for the adjustable parameter referenced by
      //  the given index.
      //<

   virtual param::Type getParameterType(int index) const;
      //> This method returns the type of the adjustable parameter
      //  referenced by the given index.
      //<

   virtual void setParameterType(int index, param::Type pType);
      //> This method sets the type of the adjustable parameter
      //  reference by the given index.
      //<

   virtual Parameter getParameter(int index) const;
      //> This method returns a Parameter object for the given index.
      //  If the index is out of range, a csm::Error may be thrown.
      //  The default implementation simply calls the methods for each of
      //  the components of the Parameter. This method is declared virtual so
      //  derived classes may opt to provide their own (more efficient)
      //  implementation.
      //<

   virtual void setParameter(int index, const Parameter& parameter);
      //>  This method sets all of the properties of the Parameter indicated by
      //   the given index to those of the given parameter.
      //   If the index is out of range, a csm::Error may be thrown.
      //   The default implementation simply calls the methods for each of
      //   the components of the Parameter.  Note that this precludes setting of
      //   name, units,  and sharing criteria as these are set only by the
      //   derived classes. This method is declared virtual so derived classes
      //   may opt to provide their own (more efficient) implementation.
      //<

   std::vector<int> getParameterSetIndices(param::Set pSet = param::VALID) const;
      //> This method returns a vector of indices of the parameters contained in
      //  the given pSet.
      //<

   std::vector<Parameter> getParameters(param::Set pSet = param::VALID) const;
      //> This method returns a vector containing all parameters in the
      //  given pSet.  The default is all parameters marked as VALID.
      //<

   virtual double getParameterCovariance(int index1,
                                         int index2) const;
      //> This method returns the covariance between the parameters
      //  referenced by index1 and index2.  Variance of a single parameter
      //  is indicated by specifying the samve value for index1 and index2.
      //<

   virtual void setParameterCovariance(int index1,
                                       int index2,
                                       double covariance);
      //> This method is used to set the covariance between the parameters
      //  referenced by index1 and index2.  Variance of a single parameter
      //  is indicated by specifying the samve value for index1 and index2.
      //<

   virtual int getNumGeometricCorrectionSwitches() const;
      //> This method returns the number of geometric correction switches
      //  implemented for the current model.
      //<

   virtual std::string getGeometricCorrectionName(int index) const;
      //> This method returns the name for the geometric correction switch
      //  referenced by the given index.
      //<

   virtual void setGeometricCorrectionSwitch(int index,
                                             bool value,
                                             param::Type pType);
      //> This method is used to enable/disable the geometric correction switch
      //  referenced by the given index.
      //<

   virtual bool getGeometricCorrectionSwitch(int index) const;
      //> This method returns the value of the geometric correction switch
      //  referenced by the given index.
      //<

   
   virtual std::vector<double> getCrossCovarianceMatrix(
          const GeometricModel& comparisonModel,
          param::Set pSet = param::VALID,
          const GeometricModelList& otherModels = GeometricModelList()) const;
      //> This method returns a matrix containing the elements of the error
      //  cross covariance between this model and a given second model
      //  (comparisonModel).  The set of cross covariance elements returned is
      //  indicated by pSet, which, by default, is all VALID parameters.
      //
      //  If comparisonModel is the same as this model, the covariance for
      //  this model will be returned.  It is equivalent to calling
      //  getParameterCovariance() for the same set of elements.  Note that
      //  even if the cross covariance for a particular model type is always
      //  zero, the covariance for this model must still be supported.
      //
      //  The otherModels list contains all of the models in the current
      //  photogrammetric process; some cross-covariance implementations are
      //  influenced by other models.  It can be omitted if it is not needed
      //  by any models being used.
      //
      //  The returned vector will logically be a two-dimensional matrix of
      //  covariances, though for simplicity it is stored in a one-dimensional
      //  vector (STL has no two-dimensional structure).  The height (number of
      //  rows) of this matrix is the number of parameters on the current model,
      //  and the width (number of columns) is the number of parameters on
      //  the comparison model.  Thus, the covariance between p1 on this model
      //  and p2 on the comparison model is found in index (N*p1 + p2)
      //  in the returned vector.  N is the size of the vector returned by
      //  getParameterSetIndices() on the comparison model for the given pSet).
      //
      //  Note that cross covariance is often zero.  Non-zero cross covariance
      //  can occur for models created from the same sensor (or different
      //  sensors on the same platform).  While cross covariances can result
      //  from a bundle adjustment involving multiple models, no mechanism 
      //  currently exists within csm to "set" the cross covariance between 
      //  models.  It should thus be assumed that the returned cross covariance
      //  reflects the "un-adjusted" state of the models.
      //<
      
   //***
   // Model methods
   //***
   virtual Version getVersion() const;
      //> This method returns the version of the model code.  The Version
      //  object can be compared to other Version objects with its comparison
      //  operators.  Not to be confused with the CSM API version.
      //<

   virtual std::string getModelName() const;
      //> This method returns a string identifying the name of the model.
      //<

   virtual std::string getPedigree() const;
      //> This method returns a string that identifies the sensor,
      //  the model type, its mode of acquisition and processing path.
      //  For example, an optical sensor model or a cubic rational polynomial
      //  model created from the same sensor's support data would produce
      //  different pedigrees for each case.
      //<

   //---
   // Basic collection information
   //---
   virtual std::string getImageIdentifier() const;
      //> This method returns an identifier to uniquely indicate the imaging
      //  operation associated with this model.
      //  This is the primary identifier of the model.
      //
      //  This method may return an empty string if the ID is unknown.
      //<

   virtual void setImageIdentifier(const std::string& imageId,
                                   WarningList* warnings = NULL);
      //> This method sets an identifier to uniquely indicate the imaging
      //  operation associated with this model.  Typically used for models
      //  whose initialization does not produce an adequate identifier.
      //
      //  If a non-NULL warnings argument is received, it will be populated
      //  as applicable.
      //<

   virtual std::string getSensorIdentifier() const;
      //> This method returns an identifier to indicate the specific sensor
      //  that was used to acquire the image.  This ID must be unique among
      //  sensors for a given model name.  It is used to determine parameter
      //  correlation and sharing.  Equivalent to camera or mission ID.
      //
      //  This method may return an empty string if the sensor ID is unknown.
      //<

   virtual std::string getPlatformIdentifier() const;
      //> This method returns an identifier to indicate the specific platform
      //  that was used to acquire the image.  This ID must unique among
      //  platforms for a given model name.  It is used to determine parameter
      //  correlation sharing.  Equivalent to vehicle or aircraft tail number.
      //
      //  This method may return an empty string if the platform ID is unknown.
      //<

   virtual std::string getCollectionIdentifier() const;
      //> This method returns an identifer to indicate a collection activity
      //  common to a set of images.  This ID must be unique among collection
      //  activities for a given model name.  It is used to determine parameter
      //  correlation and sharing.
      //<

   virtual std::string getTrajectoryIdentifier() const;
      //> This method returns an identifier to indicate a trajectory common
      //  to a set of images.  This ID must be unique among trajectories
      //  for a given model name.  It is used to determine parameter
      //  correlation and sharing.
      //<

   virtual std::string getSensorType() const;
      //> This method returns a description of the sensor type (EO, IR, SAR,
      //  etc).  See csm.h for a list of common types.  Should return
      //  CSM_SENSOR_TYPE_UNKNOWN if the sensor type is unknown.
      //<

   virtual std::string getSensorMode() const;
      //> This method returns a description of the sensor mode (FRAME,
      //  PUSHBROOM, SPOT, SCAN, etc).  See csm.h for a list of common modes.
      //  Should return CSM_SENSOR_MODE_UNKNOWN if the sensor mode is unknown.
      //<

   virtual std::string getReferenceDateAndTime() const;
      //> This method returns an approximate date and time at which the
      //  image was taken.  The returned string follows the ISO 8601 standard.
      //
      //-    Precision   Format           Example
      //-    year        yyyy             "1961"
      //-    month       yyyymm           "196104"
      //-    day         yyyymmdd         "19610420"
      //-    hour        yyyymmddThh      "19610420T20"
      //-    minute      yyyymmddThhmm    "19610420T2000"
      //-    second      yyyymmddThhmmss  "19610420T200000"
      //<

   //---
   // Sensor Model State
   //---
   virtual std::string getModelState() const;
      //> This method returns a string containing the data to exactly recreate
      //  the current model.  It can be used to restore this model to a
      //  previous state with the replaceModelState method or create a new
      //  model object that is identical to this model.
      //  The string could potentially be saved to a file for later use.
      //  An empty string is returned if it is not possible to save the
      //  current state.
      //<

   virtual void replaceModelState(const std::string& argState);
      //> This method attempts to initialize the current model with the state
      //  given by argState.  The argState argument can be a string previously
      //  retrieved from the getModelState method.
      //
      //  If argState contains a valid state for the current model,
      //  the internal state of the model is updated.
      //
      //  If the model cannot be updated to the given state, a csm::Error is
      //  thrown and the internal state of the model is undefined.
      //
      //  If the argument state string is empty, the model remains unchanged.
      //<
      
private:
   
   const std::shared_ptr<RasterGM>& rasterModel() const;
   //> This method returns a const reference to the owned model.
   //<
   
   std::shared_ptr<RasterGM> theRasterModel;
   //> This data member is the model which is called for ALL implemented methods.
   //  This classs is just a wrapper for "theRasterModel"
   //<
};

} // namespace csm

#endif
