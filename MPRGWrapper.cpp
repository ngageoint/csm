//#############################################################################
//
//    FILENAME:          MPRGWrapperr.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    This file provides implementation for the MPRGWrapper (allows a
//    RasterGM to exploit the MultiPointRasterGM interface).
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//      08-Dec-2021   JPK  Initial Coding
//
//#############################################################################

#define CSM_LIBRARY

#include "MPRGWrapper.h"
#include "MultiPointUtils.h"
#include "Error.h"
namespace csm {

using Parameter = GeometricModel::Parameter;
using ParameterVctr = std::vector<Parameter>;

//*****************************************************************************
// MPRGWrapper::MPRGWrapper
//*****************************************************************************
MPRGWrapper::MPRGWrapper()
   :
      MultiPointRasterGM (),
      theRasterModel     ()
{}
//*****************************************************************************
// MPRGWrapper::~MPRGWrapper
//*****************************************************************************
MPRGWrapper::~MPRGWrapper()
{}
//*****************************************************************************
// MPRGWrapper::setRasterModel
//*****************************************************************************
void MPRGWrapper::setRasterModel(const std::shared_ptr<RasterGM>& rasterModel)
{
   theRasterModel = rasterModel;
}

//*****************************************************************************
// MPRGWrapper::rasterModel
//*****************************************************************************
const std::shared_ptr<RasterGM>& MPRGWrapper::rasterModel() const
{
   if (!theRasterModel)
   {
      throw Error(Error::INVALID_SENSOR_MODEL_STATE,
                  "RasterGM not initialized!",
                  "MPRGWrapper::rasterModel");
   }
   
   return theRasterModel;
}

//*****************************************************************************
// MPRGWrapper::multiGroundToImage
//*****************************************************************************
MultiImageCoord
MPRGWrapper::multiGroundToImage(const MultiEcefCoord& groundPts,
                                       double desiredPrecision,
                                       MultiDbl* achievedPrecisions,
                                       WarningList* warnings) const
{
   return MultiPointUnoptimized::groundToImage(*rasterModel(),
                                               groundPts,
                                               desiredPrecision,
                                               achievedPrecisions,
                                               warnings);
}

//*****************************************************************************
// MPRGWrapper::multiGroundtoImage
//*****************************************************************************
MultiImageCoordCovar
MPRGWrapper::multiGroundToImage(const MultiEcefCoordCovar& groundPts,
                                       double desiredPrecision,
                                       MultiDbl* achievedPrecisions,
                                       WarningList* warnings) const
{
  return MultiPointUnoptimized::groundToImage(*rasterModel(),
                                              groundPts,
                                              desiredPrecision,
                                              achievedPrecisions,
                                              warnings);
}

//*****************************************************************************
// MPRGWrapper::multiImageToGround
//*****************************************************************************
MultiEcefCoord
MPRGWrapper::multiImageToGround(const MultiImageCoordWithHeight& pts,
                                       double desiredPrecision,
                                       MultiDbl* achievedPrecisions,
                                       WarningList* warnings) const
{
   return MultiPointUnoptimized::imageToGround(*rasterModel(),
                                               pts,
                                               desiredPrecision,
                                               achievedPrecisions,
                                               warnings);
}

 //*****************************************************************************
// MPRGWrapper::multiImageToGround
//*****************************************************************************
MultiEcefCoordCovar
MPRGWrapper::multiImageToGround(const MultiImageCoordCovarWithHeight& pts,
                                       double desiredPrecision,
                                       MultiDbl* achievedPrecisions,
                                       WarningList* warnings) const
{
   return MultiPointUnoptimized::imageToGround(*rasterModel(),
                                               pts,
                                               desiredPrecision,
                                               achievedPrecisions,
                                               warnings);
}

//*****************************************************************************
// MPRGWrapper::multiImageToProximateImagingLocus
//*****************************************************************************
MultiEcefLocus
MPRGWrapper::
multiImageToProximateImagingLocus(const MultiImageEcefCoordPair& imageAndGroundPts,
                                  double desiredPrecision,
                                  MultiDbl* achievedPrecisions,
                                  WarningList* warnings) const
{
   return MultiPointUnoptimized::
      imageToProximateImagingLocus(*rasterModel(),
                                   imageAndGroundPts,
                                   desiredPrecision,
                                   achievedPrecisions,
                                   warnings);
}

//*****************************************************************************
// MPRGWrapper::multiImageToRemoteImagingLocus
//*****************************************************************************
MultiEcefLocus
MPRGWrapper::
multiImageToRemoteImagingLocus(const MultiImageCoord& imagePts,
                               double desiredPrecision,
                               MultiDbl* achievedPrecisions,
                               WarningList* warnings) const
{
   return MultiPointUnoptimized::
      imageToRemoteImagingLocus(*rasterModel(),
                                imagePts,
                                desiredPrecision,
                                achievedPrecisions,
                                warnings); 
}

//*****************************************************************************
// MPRGWrapper:: multiGetIlluminationDirection
//*****************************************************************************
MultiEcefVector
MPRGWrapper::
multiGetIlluminationDirection(const MultiEcefCoord& groundPts) const
{
   return MultiPointUnoptimized::getIlluminationDirection(*rasterModel(),
                                                          groundPts);
}

//*****************************************************************************
// MPRGWrapper::multiGetImageTime
//*****************************************************************************
MultiDbl
MPRGWrapper::multiGetImageTime(const MultiImageCoord& imagePts) const
{
   return MultiPointUnoptimized::getImageTime(*rasterModel(),
                                              imagePts);
}

 //*****************************************************************************
// MPRGWrapper::multiGetSensorPosition
//******************************************************************************
MultiEcefCoord
MPRGWrapper::multiGetSensorPosition(const MultiImageCoord& imagePts) const
{
   return MultiPointUnoptimized::getSensorPosition(*rasterModel(),
                                                   imagePts);
}

//*****************************************************************************
// MPRGWrapper::multiGetSensorPosition
//*****************************************************************************
MultiEcefCoord
MPRGWrapper::multiGetSensorPosition(const MultiDbl& times) const
{
   return MultiPointUnoptimized::getSensorPosition(*rasterModel(),
                                                    times);
}

 //*****************************************************************************
// MPRGWrapper::multiGetSensorVelocity
//*****************************************************************************
MultiEcefVector
MPRGWrapper::multiGetSensorVelocity(MultiImageCoord& imagePts) const
{
   return MultiPointUnoptimized::getSensorVelocity(*rasterModel(),
                                                   imagePts);
}

//*****************************************************************************
// MPRGWrapper::multiGetSensorVelocity
//*****************************************************************************
MultiEcefVector
MPRGWrapper::multiGetSensorVelocity(const MultiDbl& times) const
{
   return MultiPointUnoptimized::getSensorVelocity(*rasterModel(),
                                                   times);
}

//*****************************************************************************
// MPRGWrapper::getFamily()
//*****************************************************************************
SensorPartialsVctr
MPRGWrapper::multiComputeSensorPartials(int index,
                                        const MultiEcefCoord& groundPts,
                                        double desiredPrecision,
                                        MultiDbl* achievedPrecisions,
                                        WarningList* warnings) const
{
   return MultiPointUnoptimized::
      computeSensorPartials(*rasterModel(),
                            index,
                            groundPts,
                            desiredPrecision,
                            achievedPrecisions,
                            warnings);
}

//*****************************************************************************
// MPRGWrapper::multiComputeSensorPartials
//*****************************************************************************
SensorPartialsVctr
MPRGWrapper::
multiComputeSensorPartials(int index,
                           const MultiImageEcefCoordPair& imageAndGroundPts,
                           double desiredPrecision,
                           MultiDbl* achievedPrecisions,
                           WarningList* warnings) const
{
   return MultiPointUnoptimized::computeSensorPartials(*rasterModel(),
                                                       index,
                                                       imageAndGroundPts,
                                                       desiredPrecision,
                                                       achievedPrecisions,
                                                       warnings);
}

//*****************************************************************************
// MPRGWrapper::multiComputeAllSensorPartials
//*****************************************************************************
MultiSensorPartialsVctr
MPRGWrapper::
multiComputeAllSensorPartials(const MultiEcefCoord& groundPts,
                              param::Set pSet,
                              double desiredPrecision,
                              MultiDbl* achievedPrecisions,
                              WarningList* warnings) const
{
   return MultiPointUnoptimized::
      computeAllSensorPartials(*rasterModel(),
                               groundPts,
                               pSet,
                               desiredPrecision,
                               achievedPrecisions,
                               warnings);
}

//*****************************************************************************
// MPRGWrapper::multiComputeAllSensorPartials
//*****************************************************************************
MultiSensorPartialsVctr
MPRGWrapper::
multiComputeAllSensorPartials(const MultiImageEcefCoordPair& imageAndGroundPts,
                              param::Set pSet,
                              double desiredPrecision,
                              MultiDbl* achievedPrecisions,
                              WarningList* warnings) const

{
   return MultiPointUnoptimized::
      computeAllSensorPartials(*rasterModel(),
                               imageAndGroundPts,
                               pSet,
                               desiredPrecision,
                               achievedPrecisions,
                               warnings);
}

//*****************************************************************************
// MPRGWrapper::multiComputeGroundPartials
//*****************************************************************************
MultiDblVctr
MPRGWrapper::
multiComputeGroundPartials(const MultiEcefCoord& groundPts) const
{
   return MultiPointUnoptimized::
      computeGroundPartials(*rasterModel(),
                            groundPts);
}
   
//*****************************************************************************
// MPRGWrapper::multiGetUnmodeledError
//*****************************************************************************
MultiDblVctr
MPRGWrapper::
multiGetUnmodeledError(const MultiImageCoord& imagePts) const
{
   return MultiPointUnoptimized::getUnmodeledError(*rasterModel(),
                                                   imagePts);
}

//*****************************************************************************
// MPRGWrapper::multiGetUnmodeledCrossCovariance
//*****************************************************************************
MultiDblVctr
MPRGWrapper::
multiGetUnmodeledCrossCovariance(const MultiImageCoordPair& ptsPairs) const
{
   return MultiPointUnoptimized::
      getUnmodeledCrossCovariance(*rasterModel(),
                                  ptsPairs);
}

//*****************************************************************************
// MPRGWrapper::groundToImage
//*****************************************************************************
ImageCoord MPRGWrapper::groundToImage(const EcefCoord& groundPt,
                                    double desiredPrecision,
                                    double* achievedPrecision,
                                      WarningList* warnings) const
{
   return rasterModel()->groundToImage(groundPt,
                                        desiredPrecision,
                                        achievedPrecision,
                                        warnings);
}
//*****************************************************************************
// MPRGWrapper::groundToImage
//*****************************************************************************
ImageCoordCovar MPRGWrapper::groundToImage(const EcefCoordCovar& groundPt,
                                         double desiredPrecision,
                                         double* achievedPrecision,
                                           WarningList* warnings) const
{
   return rasterModel()->groundToImage(groundPt,
                                        desiredPrecision,
                                        achievedPrecision,
                                        warnings);
   
}
//*****************************************************************************
// MPRGWrapper::imageToGround
//*****************************************************************************
EcefCoord MPRGWrapper::imageToGround(const ImageCoord& imagePt,
                                     double height,
                                     double desiredPrecision,
                                     double* achievedPrecision,
                                     WarningList* warnings) const
{
   return rasterModel()->imageToGround(imagePt,
                                        height,
                                        desiredPrecision,
                                        achievedPrecision,
                                        warnings);
}
//*****************************************************************************
// MPRGWrapper::imageToGround
//*****************************************************************************
EcefCoordCovar MPRGWrapper::imageToGround(const ImageCoordCovar& imagePt,
                                          double height,
                                          double heightVariance,
                                          double desiredPrecision,
                                          double* achievedPrecision,
                                          WarningList* warnings) const
{
   return rasterModel()->imageToGround(imagePt,
                                        height,
                                        heightVariance,
                                        desiredPrecision,
                                        achievedPrecision,
                                        warnings);
}
//*****************************************************************************
// MPRGWrapper::imageToProximateImagingLocus
//*****************************************************************************
EcefLocus MPRGWrapper::imageToProximateImagingLocus(const ImageCoord& imagePt,
                                                    const EcefCoord& groundPt,
                                                    double desiredPrecision,
                                                    double* achievedPrecision,
                                                    WarningList* warnings) const
{
   return rasterModel()->imageToProximateImagingLocus(imagePt,
                                                       groundPt,
                                                       desiredPrecision,
                                                       achievedPrecision,
                                                       warnings);
}
//*****************************************************************************
// MPRGWrapper::imageToRemoteImagingLocus
//*****************************************************************************
EcefLocus MPRGWrapper::imageToRemoteImagingLocus(
   const ImageCoord& imagePt,
   double desiredPrecision,
   double* achievedPrecision,
   WarningList* warnings) const
{
   return rasterModel()->imageToRemoteImagingLocus(imagePt,
                                                    desiredPrecision,
                                                    achievedPrecision,
                                                    warnings);
}
//*****************************************************************************
// MPRGWrapper::getImageStart
//*****************************************************************************
ImageCoord MPRGWrapper::getImageStart() const
{
   return rasterModel()->getImageStart();
}
//*****************************************************************************
// MPRGWrapper::getImageSize
//*****************************************************************************
ImageVector MPRGWrapper::getImageSize() const
{
   return rasterModel()->getImageSize();
}
//*****************************************************************************
// MPRGWrapper::getValidImageRange
//*****************************************************************************
std::pair<ImageCoord,ImageCoord> MPRGWrapper::getValidImageRange() const
{
   return rasterModel()->getValidImageRange();
}
//*****************************************************************************
// MPRGWrapper::getValidHeightRange
//*****************************************************************************

std::pair<double,double> MPRGWrapper::getValidHeightRange() const
{
   return rasterModel()->getValidHeightRange();
}
//*****************************************************************************
// MPRGWrapper::getIlluminationDirection
//*****************************************************************************
EcefVector MPRGWrapper::getIlluminationDirection(const EcefCoord& groundPt) const
{
   return rasterModel()->getIlluminationDirection(groundPt);
}
//*****************************************************************************
// MPRGWrapper::getImageTime
//*****************************************************************************
double MPRGWrapper::getImageTime(const ImageCoord& imagePt) const
{
   return rasterModel()->getImageTime(imagePt);
}
//*****************************************************************************
// MPRGWrapper::getSensorPosition
//*****************************************************************************
EcefCoord MPRGWrapper::getSensorPosition(const ImageCoord& imagePt) const
{
   return rasterModel()->getSensorPosition(imagePt);
}
//*****************************************************************************
// MPRGWrapper::getSensorPosition
//*****************************************************************************
EcefCoord MPRGWrapper::getSensorPosition(double time) const
{
   return rasterModel()->getSensorPosition(time);
}
//*****************************************************************************
// MPRGWrapper::getSensorVelocity
//*****************************************************************************
EcefVector MPRGWrapper::getSensorVelocity(const ImageCoord& imagePt) const
{
   return rasterModel()->getSensorVelocity(imagePt);
}
//*****************************************************************************
// MPRGWrapper::getSensorVelocity
//*****************************************************************************
EcefVector MPRGWrapper::getSensorVelocity(double time) const
{
   return rasterModel()->getSensorVelocity(time);
}
//*****************************************************************************
// MPRGWrapper::computeSensorPartials
//*****************************************************************************
RasterGM::SensorPartials
MPRGWrapper::computeSensorPartials(int index,
                                   const EcefCoord& groundPt,
                                   double desiredPrecision,
                                   double* achievedPrecision,
                                   WarningList* warnings) const
{
   return rasterModel()->computeSensorPartials(index,
                                                groundPt,
                                                desiredPrecision,
                                                achievedPrecision,
                                                warnings);
}
//*****************************************************************************
// MPRGWrapper::computeSensorPartials
//*****************************************************************************
RasterGM::SensorPartials
MPRGWrapper::computeSensorPartials(int index,
                                   const ImageCoord& imagePt,
                                   const EcefCoord& groundPt,
                                   double desiredPrecision,
                                   double* achievedPrecision,
                                   WarningList* warnings) const
{
   return rasterModel()->computeSensorPartials(index,
                                                imagePt,
                                                groundPt,
                                                desiredPrecision,
                                                achievedPrecision,
                                                warnings);
}
//*****************************************************************************
// MPRGWrapper::computeAllSensorPartials
//*****************************************************************************
SensorPartialsVctr
MPRGWrapper::computeAllSensorPartials(const EcefCoord& groundPt,
                                      param::Set pSet,
                                      double desiredPrecision,
                                      double* achievedPrecision,
                                      WarningList* warnings) const
{
   return rasterModel()->computeAllSensorPartials(groundPt,
                                                   pSet,
                                                   desiredPrecision,
                                                   achievedPrecision,
                                                   warnings);
}
//*****************************************************************************
// MPRGWrapper::computeAllSensorPartials
//*****************************************************************************
SensorPartialsVctr
MPRGWrapper::computeAllSensorPartials(const ImageCoord& imagePt,
                                      const EcefCoord& groundPt,
                                      param::Set pSet,
                                      double desiredPrecision,
                                      double* achievedPrecision,
                                      WarningList* warnings) const
{
   return rasterModel()->computeAllSensorPartials(imagePt,
                                                   groundPt,
                                                   pSet,
                                                   desiredPrecision,
                                                   achievedPrecision,
                                                   warnings);
}
//*****************************************************************************
// MPRGWrapper::computeGroundPartials
//*****************************************************************************
MultiDbl MPRGWrapper::computeGroundPartials(const EcefCoord& groundPt) const
{
   return rasterModel()->computeGroundPartials(groundPt);
}
//*****************************************************************************
// MPRGWrapper::getCorrelationMode;
//*****************************************************************************
const CorrelationModel& MPRGWrapper::getCorrelationModel() const
{
   return rasterModel()->getCorrelationModel();
}
//*****************************************************************************
// MPRGWrapper::getUnmoideledCrossCovariance
//*****************************************************************************
MultiDbl MPRGWrapper::getUnmodeledCrossCovariance(const ImageCoord& pt1,
                                                 const ImageCoord& pt2) const
{
   return rasterModel()->getUnmodeledCrossCovariance(pt1,pt2);
}
//*****************************************************************************
// MPRGWrapper::getReferencePoint
//*****************************************************************************
EcefCoord MPRGWrapper::getReferencePoint() const
{
   return rasterModel()->getReferencePoint();
}
//*****************************************************************************
// MPRGWrapper::setReferencePoint
//*****************************************************************************
void MPRGWrapper::setReferencePoint(const EcefCoord& groundPt)
{
   rasterModel()->setReferencePoint(groundPt);
}
//*****************************************************************************
// MPRGWrapper::getNumParameters
//*****************************************************************************
int MPRGWrapper::getNumParameters() const
{
   return rasterModel()->getNumParameters();
}
//*****************************************************************************
// MPRGWrapper::getParameterName
//*****************************************************************************
std::string MPRGWrapper::getParameterName(int index) const
{
   return rasterModel()->getParameterName(index);
}
//*****************************************************************************
// MPRGWrapper::getParameterUnits
//*****************************************************************************
std::string MPRGWrapper::getParameterUnits(int index) const
{
   return rasterModel()->getParameterUnits(index);
}
//*****************************************************************************
// MPRGWrapper::hasShareableParameters
//*****************************************************************************
bool MPRGWrapper::hasShareableParameters() const
{
   return rasterModel()->hasShareableParameters();
}
//*****************************************************************************
// MPRGWrapper::isParameterShareable
//*****************************************************************************
bool MPRGWrapper::isParameterShareable(int index) const
{
   return rasterModel()->isParameterShareable(index);
}
//*****************************************************************************
// MPRGWrapper::getParameterSharingCriteria
//*****************************************************************************
SharingCriteria MPRGWrapper::getParameterSharingCriteria(int index) const
{
   return rasterModel()->getParameterSharingCriteria(index);
}
//*****************************************************************************
// MPRGWrapper::getparameterValue
//*****************************************************************************
double MPRGWrapper::getParameterValue(int index) const
{
   return rasterModel()->getParameterValue(index);
}
//*****************************************************************************
// MPRGWrapper::setParameterValue
//*****************************************************************************
void MPRGWrapper::setParameterValue(int index, double value)
{
   return rasterModel()->setParameterValue(index,value);
}
//*****************************************************************************
// MPRGWrapper::getParameterType
//*****************************************************************************
param::Type MPRGWrapper::getParameterType(int index) const
{
   return rasterModel()->getParameterType(index);
}
//*****************************************************************************
// MPRGWrapper::setParameterType
//*****************************************************************************
void MPRGWrapper::setParameterType(int index, param::Type pType)
{
   rasterModel()->setParameterType(index,pType);
}
//*****************************************************************************
// MPRGWrapper::getParameter
//*****************************************************************************
Parameter MPRGWrapper::getParameter(int index) const
{
   return rasterModel()->getParameter(index);
}
//*****************************************************************************
// MPRGWrapper::setParameter
//*****************************************************************************
void MPRGWrapper::setParameter(int index, const Parameter& parameter)
{
   rasterModel()->setParameter(index,parameter);
}
//*****************************************************************************
// MPRGWrapper::getParameterSetIndices
//*****************************************************************************
std::vector<int> MPRGWrapper::getParameterSetIndices(param::Set pSet) const
{
   return rasterModel()->getParameterSetIndices(pSet);
}
//*****************************************************************************
// MPRGWrapper::getParameters
//*****************************************************************************
ParameterVctr MPRGWrapper::getParameters(param::Set pSet) const
{
   return rasterModel()->getParameters(pSet);
}
//*****************************************************************************
// MPRGWrapper::getParameterCovariance
//*****************************************************************************
double MPRGWrapper::getParameterCovariance(int index1,
                                           int index2) const
{
   return rasterModel()->getParameterCovariance(index1,index2);
}
//*****************************************************************************
// MPRGWrapper::setParameterCovariance
//*****************************************************************************
void MPRGWrapper::setParameterCovariance(int index1,
                                         int index2,
                                         double covariance)
{
   rasterModel()->setParameterCovariance(index1,
                                          index2,
                                          covariance);
}
//*****************************************************************************
// MPRGWrapper::getNumGeometricCorrectionSwitches
//*****************************************************************************
int MPRGWrapper::getNumGeometricCorrectionSwitches() const
{
   return rasterModel()->getNumGeometricCorrectionSwitches();
}
//*****************************************************************************
// MPRGWrapper::getGeometricCorrectionName
//*****************************************************************************
std::string MPRGWrapper::getGeometricCorrectionName(int index) const
{
   return rasterModel()->getGeometricCorrectionName(index);
}
//*****************************************************************************
// MPRGWrapper::setGeometricCorrectionSwitch
//*****************************************************************************
void MPRGWrapper::setGeometricCorrectionSwitch(int index,
                                               bool value,
                                               param::Type pType) 
{
   rasterModel()->setGeometricCorrectionSwitch(index,value,pType);
}
//*****************************************************************************
// MPRGWrapper::getGeometricCorrectionSwitch
//*****************************************************************************
bool MPRGWrapper::getGeometricCorrectionSwitch(int index) const
{
   return rasterModel()->getGeometricCorrectionSwitch(index);
}
//*****************************************************************************
// MPRGWrapper::getCrossCovarianceMatrix
//*****************************************************************************
MultiDbl
MPRGWrapper::getCrossCovarianceMatrix(const GeometricModel& comparisonModel,
                                      param::Set pSet,
                                      const GeometricModelList& otherModels) const
{
   return rasterModel()->getCrossCovarianceMatrix(comparisonModel,
                                                   pSet,
                                                   otherModels);
}
//*****************************************************************************
// MPRGWrapper::getVersion
//*****************************************************************************
Version MPRGWrapper::getVersion() const
{
   return rasterModel()->getVersion();
}
//*****************************************************************************
// MPRGWrapper::getModelName
//*****************************************************************************
std::string MPRGWrapper::getModelName() const
{
   return std::string("MultiPoint_") + rasterModel()->getModelName();
}
//*****************************************************************************
// MPRGWrapper::getPedigree
//*****************************************************************************
std::string MPRGWrapper::getPedigree() const
{
   return rasterModel()->getPedigree();
}
//*****************************************************************************
// MPRGWrapper::getImageIdentifier
//*****************************************************************************
std::string MPRGWrapper::getImageIdentifier() const
{
   return rasterModel()->getImageIdentifier();
}
//*****************************************************************************
// MPRGWrapper::setImageIdentifier
//*****************************************************************************
void MPRGWrapper::setImageIdentifier(const std::string& imageId,
                                     WarningList* warnings)
{
   rasterModel()->setImageIdentifier(imageId,
                                      warnings);
}
//*****************************************************************************
// MPRGWrapper::getSensorIdentifier
//*****************************************************************************
std::string MPRGWrapper::getSensorIdentifier() const
{
   return rasterModel()->getSensorIdentifier();
}
//*****************************************************************************
// MPRGWrapper::getPlatformIdentifier
//*****************************************************************************
std::string MPRGWrapper::getPlatformIdentifier() const
{
   return rasterModel()->getPlatformIdentifier();
}
//*****************************************************************************
// MPRGWrapper::getcollectionIdentifier
//*****************************************************************************
std::string MPRGWrapper::getCollectionIdentifier() const
{
   return rasterModel()->getCollectionIdentifier();
}
//*****************************************************************************
// MPRGWrapper::getTrajectoryIdentifier
//*****************************************************************************
std::string MPRGWrapper::getTrajectoryIdentifier() const
{
   return rasterModel()->getTrajectoryIdentifier();
}
//*****************************************************************************
// MPRGWrapper::getSensorType
//*****************************************************************************
std::string MPRGWrapper::getSensorType() const
{
   return rasterModel()->getSensorType();
}
//*****************************************************************************
// MPRGWrapper::getSensorMode
//*****************************************************************************
std::string MPRGWrapper::getSensorMode() const
{
   return rasterModel()->getSensorMode();
}
//*****************************************************************************
// MPRGWrapper::getReferenceDateAndTime
//*****************************************************************************
std::string MPRGWrapper::getReferenceDateAndTime() const
{
   return rasterModel()->getReferenceDateAndTime();
}
//*****************************************************************************
// MPRGWrapper::getModelState
//*****************************************************************************
std::string MPRGWrapper::getModelState() const
{
   return rasterModel()->getModelState();
}
//*****************************************************************************
// MPRGWrapper::replaceModelState
//*****************************************************************************
void MPRGWrapper::replaceModelState(const std::string& argState)
{
   return rasterModel()->replaceModelState(argState);
}

} // namespace csm