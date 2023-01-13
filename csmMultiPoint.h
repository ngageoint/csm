//#############################################################################
//
//    FILENAME:          csmMultiPoint.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Additions were made to the CSM API in CSM 3.0.2 to handle point clouds.
//    The previous API did not change. Previously this code was in a separate
//    library, but has now been migrated into a single library as of
//    CSM3.0.3
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//
//    22FEB2018     JPK       Modified to use existing csm macros (since
//                            point cloud is no longer in a separate library).
//    NOTES:
//
//#############################################################################

#ifndef __CSM_MULTI_POINT_H
#define __CSM_MULTI_POINT_H

#include "csmPointCloud.h"
#include "ObjectSpace.h"
#include "ObjectSpaceRasterGM.h"
#include "ObjectSpacePointCloudGM.h"

#define CSM_MPR_FAMILY "MultiPoint"
namespace csm
{
//***
// STRUCT: ImageCoordWithHeight
   //> This structure represents a two-dimensional image coordinate
   //  (line, sample in pixels) and a height in meters above the WGS-84 ellipsoid 
   //  It typically represents an absolute coordinate.
   //<
//***
struct ImageCoordWithHeight
{
   ImageCoord imageCoord;
   double     height;
   
   ImageCoordWithHeight() : imageCoord(), height(0.0) {}
   
   ImageCoordWithHeight(double aLine,
                        double aSamp,
                        double aHeight)
      : imageCoord (aLine,aSamp),
        height     (aHeight)
   {}
};

//***
// STRUCT: ImageCoordCovarWithHeight
//> This structure represents an image coordinate with a corresponding
//  2x2 covariance matrix, and a height above the WGS-84 ellipsoid and
//  its associated variance.
//  The image covariance is stored as an array of four elements that can
//  be accessed directly or through the two-dimensional covar2d methods.
//<
//***
struct ImageCoordCovarWithHeight
{
   ImageCoordCovar imageCoord;
   double          height;
   double          heightVariance;
      
   ImageCoordCovarWithHeight()
      :
         imageCoord     (),
         height         (0.0),
         heightVariance (0.0)
   {}
      //> Default Constructor
      //<
   
   ImageCoordCovarWithHeight(double aLine,
                             double aSamp,
                             double aHeight,
                             double aHeightVariance)
      : imageCoord     (aLine, aSamp),
        height         (aHeight),
        heightVariance (aHeightVariance)
   {}
   
   ImageCoordCovarWithHeight(double aLine,
                             double aSamp,
                             double aCovar[4],
                             double aHeight,
                             double aHeightVariance)
      : imageCoord     (aLine, aSamp, aCovar),
        height         (aHeight),
        heightVariance (aHeightVariance)
   {}
   
   ImageCoordCovarWithHeight(double aLine,
                             double aSamp,
                             double aCovar00,
                             double aCovar01,
                             double aCovar11,
                             double aHeight,
                             double aHeightVariance)
      : imageCoord     (aLine,
                        aSamp,
                        aCovar00,
                        aCovar01,
                        aCovar11),
        height         (aHeight),
        heightVariance (aHeightVariance)
   {}
         //> This constructor takes a line and sample in pixels and the
         //  upper-triangular portion of a covariance matrix in pixels squared.
         //  It is assumed that the covariance matrix is symmetric.  It also takes
         //  a height above the WGS-84 ellipsoid and its variance.
         //<
};

using ImageCoordPair                 = std::pair<ImageCoord,ImageCoord>;

using ImageEcefCoordPair             = std::pair<ImageCoord,EcefCoord>;
using ImageObjectSpaceCoordPair = std::pair<ImageCoord, ObjectSpaceCoord>;
   
using MultiImageCoord                = std::vector<ImageCoord>;

using MultiImageCoordCovar           = std::vector<ImageCoordCovar>;

using MultiImageCoordWithHeight      = std::vector<ImageCoordWithHeight>;

using MultiImageCoordCovarWithHeight = std::vector<ImageCoordCovarWithHeight>;

using MultiEcefCoord                 = std::vector<EcefCoord>;
using MultiObjectSpaceCoord = std::vector<ObjectSpaceCoord>;

using MultiEcefCoordCovar            = std::vector<EcefCoordCovar>;
using MultiObjectSpaceCoordCovar = std::vector<ObjectSpaceCoordCovar>;

using MultiEcefLocus                 = std::vector<EcefLocus>;
using MultiObjectSpaceLocus = std::vector<ObjectSpaceLocus>;

using MultiEcefVector                = std::vector<EcefVector>;
using MultiObjectSpaceVector = std::vector<ObjectSpaceVector>;

using MultiImageCoordPair            = std::vector<ImageCoordPair>;

using MultiImageEcefCoordPair        = std::vector<ImageEcefCoordPair>;
using MultiImageObjectSpaceCoordPair = std::vector<ImageObjectSpaceCoordPair>;

using SensorPartialsVctr             = std::vector<ObjectSpaceRasterGM::SensorPartials>;
using ModelPartialsVctr = std::vector<csm::ObjectSpacePointCloudGM::SensorPartials>;

using MultiSensorPartialsVctr        = std::vector<SensorPartialsVctr>;
using MultiModelSensorPartialsVctr = std::vector<ModelPartialsVctr>;

using ModelCoordPair                 = std::pair<ModelCoord,ModelCoord>;

using MultiModelCoordPair            = std::vector<ModelCoordPair>;

using ModelEcefCoordPair             = std::pair<ModelCoord,EcefCoord>;

using MultiModelCoord                = std::vector<ModelCoord>;

using MultiModelCoordCovar           = std::vector<ModelCoordCovar>;

using MultiModelEcefCoordPair        = std::vector<ModelEcefCoordPair>;

using MultiDbl                       = std::vector<double>;

using MultiDblVctr                   = std::vector<MultiDbl>;
}

#endif
