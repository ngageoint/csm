//##############################################################################
//
//    FILENAME:          MultiPointRasterGM.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     31-Dec-2021   EJR    Initial version.
//
//    NOTES:
//
//##############################################################################

#ifndef _H_MULTI_RASTER_GM_H
#define _H_MULTI_RASTER_GM_H

#include "csmMultiPoint.h"
#include "RasterGM.h"

namespace csm
{
class CSM_EXPORT_API MultiPointRasterGM : public RasterGM
{
public:
   MultiPointRasterGM() {}
   
   virtual ~MultiPointRasterGM();
   
   virtual std::string getFamily() const;
   //> This method returns the family name for this class.
   //<
   
   virtual MultiImageCoord multiGroundToImage(const MultiEcefCoord& groundPts,
                                             double desiredPrecision = 0.001,
                                             MultiDbl* achievedPrecisions = NULL,
                                             WarningList* warnings = NULL) const = 0;
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
                                                   WarningList* warnings = NULL) const = 0;
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
                                             WarningList* warnings = NULL) const = 0;
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
                                                  WarningList* warnings = NULL) const = 0;
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
                                                            WarningList* warnings = NULL) const = 0;
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
                                                         WarningList* warnings = NULL) const = 0;
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
   
   virtual MultiEcefVector multiGetIlluminationDirection(const MultiEcefCoord& groundPts) const = 0;
   virtual MultiDbl multiGetImageTime(const MultiImageCoord& imagePts) const = 0;
  
   //> This method returns the time in seconds at which the pixels at the
   //  given vector of imagePts (vector of line, sample in full image space pixels) was captured
   //
   //  The time provided is relative to the reference date and time given
   //  by the Model::getReferenceDateAndTime method.
   //<
   
   virtual MultiEcefCoord multiGetSensorPosition(const MultiImageCoord& imagePts) const = 0;
   //> This method returns the positions of the physical sensor
   // (x,y,z in ECEF meters) when the pixel at the given vector of imagePts
   // (vector of line, sample in full image space pixels) was captured.
   //
   // A csm::Error will be thrown if the sensor position is not available.
   //<
   
   virtual MultiEcefCoord multiGetSensorPosition(const MultiDbl& times) const = 0;
   //> This method returns a vector of positions of the physical sensor
   //  (x,y,z meters ECEF) at the given times relative to the reference date
   //  and time given by the Model::getReferenceDateAndTime method.
   //<
   
   virtual MultiEcefVector multiGetSensorVelocity(MultiImageCoord& imagePts) const = 0;
   //> This method returns a vector of velocity of the physical sensor
   // (x,y,z in ECEF meters per second) when the pixel at the given vector of imagePts
   // (line, sample in full image space pixels) was captured.
   //<
   
   virtual MultiEcefVector multiGetSensorVelocity(const MultiDbl& times) const = 0;
   //> This method returns a vector of velocity of the physical sensor
   //  (x,y,z in ECEF meters per second ) at the given set of times relative to the
   //  reference date and time given by the Model::getReferenceDateAndTime
   //  method.
   //<
   
   virtual SensorPartialsVctr multiComputeSensorPartials(int index,
                                                         const MultiEcefCoord& groundPts,
                                                         double desiredPrecision = 0.001,
                                                         MultiDbl* achievedPrecision = NULL,
                                                         WarningList* warnings = NULL) const = 0; 
   //>    This is the multi-point version of RasterGM::computeSensorPartials that takes only
   //     ground points as input. It returns a vector of partials for the given parameter
   //     at the given points.
   //<
   
   virtual SensorPartialsVctr multiComputeSensorPartials(int index,
                                                         const MultiImageEcefCoordPair& imageAndGroundPts,
                                                         double desiredPrecision = 0.001,
                                                         MultiDbl* achievedPrecision = NULL,
                                                         WarningList* warnings = NULL) const = 0;
   //> This is the multi-point version of RasterGM::computeSensorPartials that takes 
   //      ground points and image points as input. It returns a vector of partials for the given parameter
   //     at the given points.
   //<
   
   virtual MultiSensorPartialsVctr multiComputeAllSensorPartials(const MultiEcefCoord& roundPts,
                                                                 param::Set pSet = param::VALID,
                                                                 double desiredPrecision = 0.001,
                                                                 MultiDbl* achievedPrecision = NULL,
                                                                 WarningList* warnings = NULL) const = 0;
   //> This is the multi-point version of RasterGM::computeAllSensorPartials that takes
   //  ground points as input. It returns a vector of vectors (a matrix) of sensor partials.
   //  The matrix is ordered by points (outer vector) and by parameters (inner vectors).
   //<
   
   virtual MultiSensorPartialsVctr multiComputeAllSensorPartials(const MultiImageEcefCoordPair& imageAnfGroundPts,
                                                                 param::Set pSet = param::VALID,
                                                                 double desiredPrecision = 0.001,
                                                                 MultiDbl* achievedPrecision = NULL,
                                                                 WarningList* warnings = NULL) const = 0;
   //> This is the multi-point version of RasterGM::computeAllSensorPartials that takes
   //  ground points and image points as input. It returns a vector of vectors (a matrix) of sensor partials.
   //  The matrix is ordered by points (outer vector) and by parameters (inner vectors).
   //<
   
   virtual MultiDblVctr multiComputeGroundPartials(const MultiEcefCoord& groundPts) const = 0;
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
   
   virtual MultiDblVctr multiGetUnmodeledError(const MultiImageCoord& imagePts) const = 0;
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
   
   virtual MultiDblVctr multiGetUnmodeledCrossCovariance(const MultiImageCoordPair& ptsPairs) const= 0;
   //> This method returns the 2x2 line and sample unmodeled error cross covariance
   //  (in pixels squared) between the every combination of the points
   //  in the two input vectors.
   //  The return is a vector of vectors. There is one vector of vectors for each point in
   //  imagepts1. The inner vector is the set of cross-covariances between the point and all
   //  of the other points.
   //  The covariance between each point and itself is not given.
   //<
};
}
# endif // _H_MULTI_RASTER_GM_H


