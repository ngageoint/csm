//##############################################################################
//
//    FILENAME:          MultiPointUtils.cpp
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
//     14-Dec-2021  JPK    Initial version.
//
//    NOTES:
//
//##############################################################################

#define CSM_LIBRARY

#include "MultiPointUtils.h"

namespace csm
{
//*****************************************************************************
// MultiPointUnoptimized::groundToImage
//*****************************************************************************
MultiImageCoord
MultiPointUnoptimized::objectSpaceToImage(const ObjectSpaceRasterGM& model,
                                     const MultiObjectSpaceCoord& groundPts,
                                     double desiredPrecision,
                                     MultiDbl* achievedPrecisions,
                                     WarningList* warnings)
{
   MultiImageCoord coords;
   
   const size_t NUM_P = groundPts.size();

   if (NUM_P > 0)
   {
      const bool passPrec = achievedPrecisions &&
                            (achievedPrecisions->size() >= NUM_P);
      
      coords.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         coords[i] = model.objectSpaceToImage(groundPts[i],
                                         desiredPrecision,
                                         (passPrec                  ?
                                          &(*achievedPrecisions)[i] :
                                          nullptr),
                                         warnings);
      }
   }
   
   return coords;
}

//*****************************************************************************
// MultiPointUnoptimized::groundtoImage
//*****************************************************************************
MultiImageCoordCovar
MultiPointUnoptimized::objectSpaceToImage(const ObjectSpaceRasterGM& model,
                                     const MultiObjectSpaceCoordCovar& groundPts,
                                     double desiredPrecision,
                                     MultiDbl* achievedPrecisions,
                                     WarningList* warnings)
{
   MultiImageCoordCovar coords;
   
   const size_t NUM_P = groundPts.size();

   if (NUM_P > 0)
   {
      const bool passPrec = achievedPrecisions &&
                            (achievedPrecisions->size() >= NUM_P);
      
      coords.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         coords[i] = model.objectSpaceToImage(groundPts[i],
                                         desiredPrecision,
                                         (passPrec                  ?
                                          &(*achievedPrecisions)[i] :
                                          nullptr),
                                         warnings);
      }
   }
   
   return coords; 
}

//*****************************************************************************
// MultiPointUnoptimized::imageToGround
//*****************************************************************************
MultiObjectSpaceCoord
MultiPointUnoptimized::imageToObjectSpace(const ObjectSpaceRasterGM& model,
                                     const MultiImageCoordWithHeight& pts,
                                     const ProjectionParameters &geometry,
                                     double desiredPrecision,
                                     MultiDbl* achievedPrecisions,
                                     WarningList* warnings)
{
   
   MultiObjectSpaceCoord coords;

   const size_t NUM_P = pts.size();
   
   if (NUM_P > 0)
   {
      const bool passPrec = achievedPrecisions &&
                            (achievedPrecisions->size() >= NUM_P);
      
      coords.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         const ImageCoordWithHeight& ptI = pts[i];
         
         coords[i] = model.imageToObjectSpace(ptI.imageCoord,
                                         geometry,
                                         desiredPrecision,
                                         (passPrec                  ?
                                          &(*achievedPrecisions)[i] :
                                          nullptr),
                                         warnings);
      }
   }
   
   return coords;
}

//*****************************************************************************
// MultiPointUnoptimized::imageToGround
//*****************************************************************************
MultiObjectSpaceCoordCovar
MultiPointUnoptimized::imageToObjectSpace(
    const ObjectSpaceRasterGM& model,
    const MultiImageCoordCovarWithHeight& pts,
    const ProjectionParametersCovar &geometry,
    double desiredPrecision,
    MultiDbl* achievedPrecisions,
    WarningList* warnings)
{
   MultiObjectSpaceCoordCovar coords;
   
   const size_t NUM_P = pts.size();

   if (NUM_P > 0)
   {
      const bool passPrec = achievedPrecisions &&
                            (achievedPrecisions->size() >= NUM_P);
      
      coords.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         const ImageCoordCovarWithHeight& ptI = pts[i];
         
         coords[i] = model.imageToObjectSpace(ptI.imageCoord,
                                         geometry,
                                         desiredPrecision,
                                         (passPrec                  ?
                                          &(*achievedPrecisions)[i] :
                                          nullptr),
                                         warnings);
      }
   }
   
   return coords;
}

//*****************************************************************************
// MultiPointUnoptimized:imageToProximateImagingLocus
//*****************************************************************************
MultiObjectSpaceLocus
MultiPointUnoptimized::
imageToProximateImagingLocus(const ObjectSpaceRasterGM&                model,
                             const MultiImageObjectSpaceCoordPair& imageAndGroundPts,
                             double desiredPrecision,
                             MultiDbl* achievedPrecisions,
                             WarningList* warnings)
{
   MultiObjectSpaceLocus loci;
   
   const size_t NUM_P = imageAndGroundPts.size();

   if (NUM_P > 0)
   {
      const bool passPrec = achievedPrecisions &&
                            (achievedPrecisions->size() >= NUM_P);
      
      loci.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         const ImageObjectSpaceCoordPair& pairI = imageAndGroundPts[i];
         
         loci[i] = model.
                   imageToProximateImagingLocus(pairI.first,
                                                pairI.second,
                                                desiredPrecision,
                                                (passPrec                  ?
                                                 &(*achievedPrecisions)[i] :
                                                 nullptr),
                                                warnings);
      }
   }
   
   return loci;
}

//*****************************************************************************
// MultiPointUnoptimized::imageToRemoteImagingLocus
//*****************************************************************************
MultiObjectSpaceLocus
MultiPointUnoptimized::
imageToRemoteImagingLocus(const ObjectSpaceRasterGM& model,
                          const MultiImageCoord& imagePts,
                          double desiredPrecision,
                          MultiDbl* achievedPrecisions,
                          WarningList* warnings)
{
   MultiObjectSpaceLocus loci;
   
   const size_t NUM_P = imagePts.size();

   if (NUM_P > 0)
   {
      const bool passPrec = achievedPrecisions &&
                            (achievedPrecisions->size() >= NUM_P);
      
      loci.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         loci[i] = model.imageToRemoteImagingLocus(imagePts[i],
                                                   desiredPrecision,
                                                   (passPrec                  ?
                                                    &(*achievedPrecisions)[i] :
                                                    nullptr),
                                                   warnings);
      }
   }
   
   return loci;
}

//*****************************************************************************
// MultiPointUnoptimized:: getIlluminationDirection
//*****************************************************************************
MultiObjectSpaceVector
MultiPointUnoptimized::
getIlluminationDirection(const ObjectSpaceRasterGM&       model,
                         const MultiObjectSpaceCoord& groundPts)
{
   MultiObjectSpaceVector vec;
   
   const size_t NUM_P = groundPts.size();

   if (NUM_P > 0)
   {
      vec.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         vec[i] = model.getIlluminationDirection(groundPts[i]);
      }
   }
   
   return vec;
}

//*****************************************************************************
// MultiPointUnoptimized::getImageTime
//*****************************************************************************
MultiDbl
MultiPointUnoptimized::getImageTime(const ObjectSpaceRasterGM&        model,
                                    const MultiImageCoord& imagePts)
{
   MultiDbl times;

   const size_t NUM_P = imagePts.size();

   if (NUM_P > 0)
   {
      times.resize(NUM_P);

      for (size_t i = 0; i < NUM_P; ++i)
      {
         times[i] = model.getImageTime(imagePts[i]);
      }
   }

   return times;
}

 //*****************************************************************************
// MultiPointUnoptimized::getSensorPosition
//******************************************************************************
MultiObjectSpaceCoord
MultiPointUnoptimized::getSensorPosition(const ObjectSpaceRasterGM&        model,
                                         const MultiImageCoord& imagePts)
{
  MultiObjectSpaceCoord coords;

   const size_t NUM_P = imagePts.size();

   if (NUM_P > 0)
   {
      coords.resize(NUM_P);

      for (size_t i = 0; i < NUM_P; ++i)
      {
         coords[i] = model.getSensorPosition(imagePts[i]);
      }
   }

   return coords;
}

//*****************************************************************************
// MultiPointUnoptimized::getSensorPosition
//*****************************************************************************
MultiObjectSpaceCoord
MultiPointUnoptimized::getSensorPosition(const ObjectSpaceRasterGM& model,
                                         const MultiDbl& times)
{
  MultiObjectSpaceCoord coords;

   const size_t NUM_TIMES = times.size();

   if (NUM_TIMES > 0)
   {
      coords.resize(NUM_TIMES);

      for (size_t i = 0; i < NUM_TIMES; ++i)
      {
         coords[i] = model.getSensorPosition(times[i]);
      }
   }

   return coords;
}

 //*****************************************************************************
// MultiPointUnoptimized::getSensorVelocity
//*****************************************************************************
MultiObjectSpaceVector
MultiPointUnoptimized::getSensorVelocity(const ObjectSpaceRasterGM&  model,
                                         MultiImageCoord& imagePts)
{
   MultiObjectSpaceVector vctrs;

   const size_t NUM_P = imagePts.size();

   if (NUM_P > 0)
   {
      vctrs.resize(NUM_P);

      for (size_t i = 0; i < NUM_P; ++i)
      {
         vctrs[i] = model.getSensorVelocity(imagePts[i]);
      }
   }

   return vctrs;
}

//*****************************************************************************
// MultiPointUnoptimized::getSensorVelocity
//*****************************************************************************
MultiObjectSpaceVector
MultiPointUnoptimized::getSensorVelocity(const ObjectSpaceRasterGM& model,
                                         const MultiDbl& times)
{
  MultiObjectSpaceVector vctrs;

   const size_t NUM_TIMES = times.size();

   if (NUM_TIMES > 0)
   {
      vctrs.resize(NUM_TIMES);

      for (size_t i = 0; i < NUM_TIMES; ++i)
      {
         vctrs[i] = model.getSensorVelocity(times[i]);
      }
   }

   return vctrs;
}

//*****************************************************************************
// MultiPointUnoptimized::computeSensorPartials
//*****************************************************************************
SensorPartialsVctr
MultiPointUnoptimized::computeSensorPartials(const ObjectSpaceRasterGM& model,
                                             int index,
                                             const MultiObjectSpaceCoord& groundPts,
                                             double desiredPrecision,
                                             MultiDbl* achievedPrecisions,
                                             WarningList* warnings)
{
   SensorPartialsVctr partials;
   
   const size_t NUM_P = groundPts.size();

   if (NUM_P > 0)
   {
      const bool passPrec = achievedPrecisions &&
                            (achievedPrecisions->size() >= NUM_P);
      
      partials.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         partials[i] = model.computeSensorPartials(index,
                                                   groundPts[i],
                                                   desiredPrecision,
                                                   (passPrec                  ?
                                                    &(*achievedPrecisions)[i] :
                                                    nullptr),
                                                   warnings);
      }
   }

   return partials;
}

//*****************************************************************************
// MultiPointUnoptimized::computeSensorPartials
//*****************************************************************************
SensorPartialsVctr
MultiPointUnoptimized::
computeSensorPartials(const ObjectSpaceRasterGM& model,
                      int index,
                      const MultiImageObjectSpaceCoordPair& imageAndGroundPts,
                      double desiredPrecision,
                      MultiDbl* achievedPrecisions,
                      WarningList* warnings)
{
   SensorPartialsVctr partials;
   
   const size_t NUM_P = imageAndGroundPts.size();

   if (NUM_P > 0)
   {
      const bool passPrec = achievedPrecisions &&
                            (achievedPrecisions->size() >= NUM_P);
      
      partials.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         const ImageObjectSpaceCoordPair& pairI = imageAndGroundPts[i];
         
         partials[i] = model.computeSensorPartials(index,
                                                   pairI.first,
                                                   pairI.second,
                                                   desiredPrecision,
                                                   (passPrec                  ?
                                                    &(*achievedPrecisions)[i] :
                                                    nullptr),
                                                   warnings);
      }
   }

   return partials;
}

//*****************************************************************************
// MultiPointUnoptimized::computeAllSensorPartials
//*****************************************************************************
MultiSensorPartialsVctr
MultiPointUnoptimized::
computeAllSensorPartials(const ObjectSpaceRasterGM& model,
                         const MultiObjectSpaceCoord& groundPts,
                         param::Set pSet,
                         double desiredPrecision,
                         MultiDbl* achievedPrecisions,
                         WarningList* warnings)
{
   MultiSensorPartialsVctr partialsVec;
   
   const size_t NUM_P = groundPts.size();

   if (NUM_P > 0)
   {
      const bool passPrec = achievedPrecisions &&
                            (achievedPrecisions->size() >= NUM_P);
      
      partialsVec.resize(NUM_P);
      for (size_t i = 0; i < NUM_P; ++i)
      {
         ImageCoord ic = model.objectSpaceToImage(groundPts[i]);
         partialsVec[i] = model.
                          computeAllSensorPartials(groundPts[i],
                                                   pSet,
                                                   desiredPrecision,
                                                   (passPrec                  ?
                                                    &(*achievedPrecisions)[i] :
                                                    nullptr),
                                                   warnings);
      }
   }
   
   return partialsVec;
}


//*****************************************************************************
// MultiPointUnoptimized::computeAllSensorPartials
//*****************************************************************************
MultiSensorPartialsVctr
MultiPointUnoptimized::
computeAllSensorPartials(const ObjectSpaceRasterGM& model,
                         const MultiImageObjectSpaceCoordPair& imageAndGroundPts,
                         param::Set pSet,
                         double desiredPrecision,
                         MultiDbl* achievedPrecisions,
                         WarningList* warnings)
{
   
   MultiSensorPartialsVctr partialsVec;
   
   const size_t NUM_P = imageAndGroundPts.size();
   
   if (NUM_P > 0)
   {
      const bool passPrec = achievedPrecisions &&
                            (achievedPrecisions->size() >= NUM_P);
      
      partialsVec.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         const ImageObjectSpaceCoordPair& pairI = imageAndGroundPts[i];
         
         partialsVec[i] = model.
                          computeAllSensorPartials(pairI.first,
                                                   pairI.second,
                                                   pSet,
                                                   desiredPrecision,
                                                   (passPrec                  ?
                                                    &(*achievedPrecisions)[i] :
                                                    nullptr),
                                                   warnings);
      }
   }
   
   return partialsVec;
}

//*****************************************************************************
// MultiPointUnoptimized::computeobjectSpacePartials
//*****************************************************************************
MultiDblVctr
MultiPointUnoptimized::
computeObjectSpacePartials(const ObjectSpaceRasterGM&       model,
                      const MultiObjectSpaceCoord& groundPts)
{
   MultiDblVctr partialsVec;
   
   const size_t NUM_P = groundPts.size();

   if (NUM_P > 0)
   {
      partialsVec.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         partialsVec[i] = model.computeObjectSpacePartials(groundPts[i]);
      }
   }

   return partialsVec;
}
   
//*****************************************************************************
// MultiPointUnoptimized::getUnmodeledError
//*****************************************************************************
MultiDblVctr
MultiPointUnoptimized::
getUnmodeledError(const ObjectSpaceRasterGM&        model,
                  const MultiImageCoord& imagePts)
{
  MultiDblVctr partialsVec;
  
  const size_t NUM_P = imagePts.size();

   if (NUM_P > 0)
   {
      partialsVec.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         partialsVec[i] = model.getUnmodeledError(imagePts[i]);
      }
   }

   return partialsVec;
}

//*****************************************************************************
// MultiPointUnoptimized::getUnmodeledCrossCovariance
//*****************************************************************************
MultiDblVctr
MultiPointUnoptimized::
getUnmodeledCrossCovariance(const ObjectSpaceRasterGM& model,
                            const MultiImageCoordPair& ptsPairs)
{
 MultiDblVctr partialsVec;
  
  const size_t NUM_P = ptsPairs.size();

  if (NUM_P > 0)
  {
     partialsVec.resize(NUM_P);
     
     for (size_t i = 0; i < NUM_P; ++i)
     {
        const ImageCoordPair& pairI = ptsPairs[i];

        partialsVec[i] = model.
                         getUnmodeledCrossCovariance(pairI.first,
                                                     pairI.second);
     }
  }

  return partialsVec;
}
}
