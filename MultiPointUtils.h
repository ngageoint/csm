//##############################################################################
//
//    FILENAME:          MultiPointUtils.h
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
//     14-Dec-2021   JPK    Initial version.
//
//    NOTES:
//
//##############################################################################

#ifndef _H_MULTI_POINT_UTILS_H
#define _H_MULTI_POINT_UTILS_H

#include "csmMultiPoint.h"
#include "RasterGM.h"

namespace csm
{
namespace MultiPointUnoptimized
{
CSM_EXPORT_API MultiImageCoord
groundToImage(const RasterGM&       model,
              const MultiEcefCoord& groundPts,
              double                desiredPrecision,
              MultiDbl*             achievedPrecisions,
              WarningList*          warnings);

CSM_EXPORT_API MultiImageCoordCovar
groundToImage(const RasterGM&            model,
              const MultiEcefCoordCovar& groundPts,
              double                     desiredPrecision,
              MultiDbl*                  achievedPrecisions,
              WarningList*               warnings);

CSM_EXPORT_API MultiEcefCoord
imageToGround(const RasterGM&                  model,
              const MultiImageCoordWithHeight& pts,
              double                           desiredPrecision,
              MultiDbl*                        achievedPrecisions,
              WarningList*                     warnings);

CSM_EXPORT_API MultiEcefCoordCovar
imageToGround(const RasterGM&                       model,
              const MultiImageCoordCovarWithHeight& imagePts,
              double                                desiredPrecision,
              MultiDbl*                             achievedPrecisions,
              WarningList*                          warnings);

CSM_EXPORT_API MultiEcefLocus
imageToProximateImagingLocus(const RasterGM&                model,
                             const MultiImageEcefCoordPair& imageAndGroundPts,
                             double                         desiredPrecision,
                             MultiDbl*                      achievedPrecisions,
                             WarningList*                   warnings);

CSM_EXPORT_API MultiEcefLocus
imageToRemoteImagingLocus(const RasterGM&        model,
                          const MultiImageCoord& imagePts,
                          double                 desiredPrecision,
                          MultiDbl*              achievedPrecisions,
                          WarningList*           warnings);

CSM_EXPORT_API MultiEcefVector
getIlluminationDirection(const RasterGM&       model,
                         const MultiEcefCoord& groundPts);

CSM_EXPORT_API MultiDbl
getImageTime(const RasterGM&        model,
             const MultiImageCoord& imagePts);

CSM_EXPORT_API MultiEcefCoord getSensorPosition(const RasterGM&         model,
                                                const MultiImageCoord& imagePts);

CSM_EXPORT_API MultiEcefCoord getSensorPosition(const RasterGM& model,
                                                const MultiDbl& times);

CSM_EXPORT_API MultiEcefVector getSensorVelocity(const RasterGM&  model,
                                                 MultiImageCoord& imagePts);

CSM_EXPORT_API MultiEcefVector getSensorVelocity(const RasterGM& model,
                                                 const MultiDbl& times);

CSM_EXPORT_API SensorPartialsVctr
computeSensorPartials(const RasterGM&       model,
                      int                   index,
                      const MultiEcefCoord& groundPts,
                      double                desiredPrecision,
                      MultiDbl*             achievedPrecision,
                      WarningList*          warnings);

CSM_EXPORT_API SensorPartialsVctr
computeSensorPartials(const RasterGM&                model,
                      int                            index,
                      const MultiImageEcefCoordPair& imageAndGroundPts,
                      double                         desiredPrecision,
                      MultiDbl*                      achievedPrecision,
                      WarningList*                   warnings);

CSM_EXPORT_API MultiSensorPartialsVctr
computeAllSensorPartials(const RasterGM&       model,
                         const MultiEcefCoord& groundPts,
                         param::Set            pSet,
                         double                desiredPrecision,
                         MultiDbl*             achievedPrecision,
                         WarningList*          warnings);

CSM_EXPORT_API MultiSensorPartialsVctr
computeAllSensorPartials(const RasterGM&                model,
                         const MultiImageEcefCoordPair& imageAndGroundPts,
                         param::Set                     pSet,
                         double                         desiredPrecision,
                         MultiDbl*                      achievedPrecision,
                         WarningList*                   warnings);

CSM_EXPORT_API MultiDblVctr
computeGroundPartials(const RasterGM&       model,
                      const MultiEcefCoord& groundPts);

CSM_EXPORT_API MultiDblVctr getUnmodeledError(const RasterGM&        model,
                                              const MultiImageCoord& imagePts);

CSM_EXPORT_API MultiDblVctr
getUnmodeledCrossCovariance(const RasterGM&            model,
                            const MultiImageCoordPair& ptsPairs);
}
}


# endif // _H_MULTI_POINT_UTILS_H
