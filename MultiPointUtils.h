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
//     31-Sep-2023   EJR    CSM 4.0. Replace ECEF with ObjectSpace.
//
//    NOTES:
//
//##############################################################################

#ifndef _H_MULTI_POINT_UTILS_H
#define _H_MULTI_POINT_UTILS_H

#include "csmMultiPoint.h"
#include "ObjectSpaceRasterGM.h"

namespace csm
{
namespace MultiPointUnoptimized
{
CSM_EXPORT_API MultiImageCoord
objectSpaceToImage(const ObjectSpaceRasterGM&       model,
              const MultiObjectSpaceCoord& groundPts,
              double                desiredPrecision,
              MultiDbl*             achievedPrecisions,
              WarningList*          warnings);

CSM_EXPORT_API MultiImageCoordCovar
objectSpaceToImage(const ObjectSpaceRasterGM&            model,
              const MultiObjectSpaceCoordCovar& groundPts,
              double                     desiredPrecision,
              MultiDbl*                  achievedPrecisions,
              WarningList*               warnings);

CSM_EXPORT_API MultiObjectSpaceCoord
imageToObjectSpace(const ObjectSpaceRasterGM&                  model,
              const MultiImageCoordWithHeight& pts,
              const ProjectionParameters &geometry,
              double                           desiredPrecision,
              MultiDbl*                        achievedPrecisions,
              WarningList*                     warnings);

CSM_EXPORT_API MultiObjectSpaceCoordCovar
imageToObjectSpace(const ObjectSpaceRasterGM&                       model,
              const MultiImageCoordCovarWithHeight& imagePts,
              const ProjectionParametersCovar &geometry,
              double                                desiredPrecision,
              MultiDbl*                             achievedPrecisions,
              WarningList*                          warnings);

CSM_EXPORT_API MultiObjectSpaceLocus
imageToProximateImagingLocus(const ObjectSpaceRasterGM&                model,
                             const MultiImageObjectSpaceCoordPair& imageAndGroundPts,
                             double                         desiredPrecision,
                             MultiDbl*                      achievedPrecisions,
                             WarningList*                   warnings);

CSM_EXPORT_API MultiObjectSpaceLocus
imageToRemoteImagingLocus(const ObjectSpaceRasterGM&        model,
                          const MultiImageCoord& imagePts,
                          double                 desiredPrecision,
                          MultiDbl*              achievedPrecisions,
                          WarningList*           warnings);

CSM_EXPORT_API MultiObjectSpaceVector
getIlluminationDirection(const ObjectSpaceRasterGM&       model,
                         const MultiObjectSpaceCoord& groundPts);

CSM_EXPORT_API MultiDbl
getImageTime(const ObjectSpaceRasterGM&        model,
             const MultiImageCoord& imagePts);

CSM_EXPORT_API MultiObjectSpaceCoord getSensorPosition(const ObjectSpaceRasterGM&         model,
                                                const MultiImageCoord& imagePts);

CSM_EXPORT_API MultiObjectSpaceCoord getSensorPosition(const ObjectSpaceRasterGM& model,
                                                const MultiDbl& times);

CSM_EXPORT_API MultiObjectSpaceVector getSensorVelocity(const ObjectSpaceRasterGM&  model,
                                                 MultiImageCoord& imagePts);

CSM_EXPORT_API MultiObjectSpaceVector getSensorVelocity(const ObjectSpaceRasterGM& model,
                                                 const MultiDbl& times);

CSM_EXPORT_API SensorPartialsVctr
computeSensorPartials(const ObjectSpaceRasterGM&       model,
                      int                   index,
                      const MultiObjectSpaceCoord& groundPts,
                      double                desiredPrecision,
                      MultiDbl*             achievedPrecision,
                      WarningList*          warnings);

CSM_EXPORT_API SensorPartialsVctr
computeSensorPartials(const ObjectSpaceRasterGM&                model,
                      int                            index,
                      const MultiImageObjectSpaceCoordPair& imageAndGroundPts,
                      double                         desiredPrecision,
                      MultiDbl*                      achievedPrecision,
                      WarningList*                   warnings);

CSM_EXPORT_API MultiSensorPartialsVctr
computeAllSensorPartials(const ObjectSpaceRasterGM&       model,
                         const MultiObjectSpaceCoord& groundPts,
                         param::Set            pSet,
                         double                desiredPrecision,
                         MultiDbl*             achievedPrecision,
                         WarningList*          warnings);

CSM_EXPORT_API MultiSensorPartialsVctr
computeAllSensorPartials(const ObjectSpaceRasterGM&                model,
                         const MultiImageObjectSpaceCoordPair& imageAndGroundPts,
                         param::Set                     pSet,
                         double                         desiredPrecision,
                         MultiDbl*                      achievedPrecision,
                         WarningList*                   warnings);

CSM_EXPORT_API MultiDblVctr
computeObjectSpacePartials(const ObjectSpaceRasterGM&       model,
                      const MultiObjectSpaceCoord& groundPts);

CSM_EXPORT_API MultiDblVctr getUnmodeledError(const ObjectSpaceRasterGM&        model,
                                              const MultiImageCoord& imagePts);

CSM_EXPORT_API MultiDblVctr
getUnmodeledCrossCovariance(const ObjectSpaceRasterGM&            model,
                            const MultiImageCoordPair& ptsPairs);
}
}


# endif // _H_MULTI_POINT_UTILS_H
