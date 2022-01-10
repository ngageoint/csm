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
MultiPointUnoptimized::groundToImage(const RasterGM& model,
                                     const MultiEcefCoord& groundPts,
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
         coords[i] = model.groundToImage(groundPts[i],
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
MultiPointUnoptimized::groundToImage(const RasterGM& model,
                                     const MultiEcefCoordCovar& groundPts,
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
         coords[i] = model.groundToImage(groundPts[i],
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
MultiEcefCoord
MultiPointUnoptimized::imageToGround(const RasterGM& model,
                                     const MultiImageCoordWithHeight& pts,
                                     double desiredPrecision,
                                     MultiDbl* achievedPrecisions,
                                     WarningList* warnings)
{
   
   MultiEcefCoord coords;

   const size_t NUM_P = pts.size();
   
   if (NUM_P > 0)
   {
      const bool passPrec = achievedPrecisions &&
                            (achievedPrecisions->size() >= NUM_P);
      
      coords.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         const ImageCoordWithHeight& ptI = pts[i];
         
         coords[i] = model.imageToGround(ptI.imageCoord,
                                         ptI.height,
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
MultiEcefCoordCovar
MultiPointUnoptimized::imageToGround(const RasterGM& model,
                                     const MultiImageCoordCovarWithHeight& pts,
                                     double desiredPrecision,
                                     MultiDbl* achievedPrecisions,
                                     WarningList* warnings)
{
   MultiEcefCoordCovar coords;
   
   const size_t NUM_P = pts.size();

   if (NUM_P > 0)
   {
      const bool passPrec = achievedPrecisions &&
                            (achievedPrecisions->size() >= NUM_P);
      
      coords.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         const ImageCoordCovarWithHeight& ptI = pts[i];
         
         coords[i] = model.imageToGround(ptI.imageCoord,
                                         ptI.height,
                                         ptI.heightVariance,
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
MultiEcefLocus
MultiPointUnoptimized::
imageToProximateImagingLocus(const RasterGM&                model,
                             const MultiImageEcefCoordPair& imageAndGroundPts,
                             double desiredPrecision,
                             MultiDbl* achievedPrecisions,
                             WarningList* warnings)
{
   MultiEcefLocus loci;
   
   const size_t NUM_P = imageAndGroundPts.size();

   if (NUM_P > 0)
   {
      const bool passPrec = achievedPrecisions &&
                            (achievedPrecisions->size() >= NUM_P);
      
      loci.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         const ImageEcefCoordPair& pairI = imageAndGroundPts[i];
         
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
MultiEcefLocus
MultiPointUnoptimized::
imageToRemoteImagingLocus(const RasterGM& model,
                          const MultiImageCoord& imagePts,
                          double desiredPrecision,
                          MultiDbl* achievedPrecisions,
                          WarningList* warnings)
{
   MultiEcefLocus loci;
   
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
MultiEcefVector
MultiPointUnoptimized::
getIlluminationDirection(const RasterGM&       model,
                         const MultiEcefCoord& groundPts)
{
   MultiEcefVector vec;
   
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
MultiPointUnoptimized::getImageTime(const RasterGM&        model,
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
MultiEcefCoord
MultiPointUnoptimized::getSensorPosition(const RasterGM&        model,
                                         const MultiImageCoord& imagePts)
{
  MultiEcefCoord coords;

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
MultiEcefCoord
MultiPointUnoptimized::getSensorPosition(const RasterGM& model,
                                         const MultiDbl& times)
{
  MultiEcefCoord coords;

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
MultiEcefVector
MultiPointUnoptimized::getSensorVelocity(const RasterGM&  model,
                                         MultiImageCoord& imagePts)
{
   MultiEcefVector vctrs;

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
MultiEcefVector
MultiPointUnoptimized::getSensorVelocity(const RasterGM& model,
                                         const MultiDbl& times)
{
  MultiEcefVector vctrs;

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
MultiPointUnoptimized::computeSensorPartials(const RasterGM& model,
                                             int index,
                                             const MultiEcefCoord& groundPts,
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
computeSensorPartials(const RasterGM& model,
                      int index,
                      const MultiImageEcefCoordPair& imageAndGroundPts,
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
         const ImageEcefCoordPair& pairI = imageAndGroundPts[i];
         
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
computeAllSensorPartials(const RasterGM& model,
                         const MultiEcefCoord& groundPts,
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
computeAllSensorPartials(const RasterGM& model,
                         const MultiImageEcefCoordPair& imageAndGroundPts,
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
         const ImageEcefCoordPair& pairI = imageAndGroundPts[i];
         
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
// MultiPointUnoptimized::computeGroundPartials
//*****************************************************************************
MultiDblVctr
MultiPointUnoptimized::
computeGroundPartials(const RasterGM&       model,
                      const MultiEcefCoord& groundPts)
{
   MultiDblVctr partialsVec;
   
   const size_t NUM_P = groundPts.size();

   if (NUM_P > 0)
   {
      partialsVec.resize(NUM_P);
      
      for (size_t i = 0; i < NUM_P; ++i)
      {
         partialsVec[i] = model.computeGroundPartials(groundPts[i]);
      }
   }

   return partialsVec;
}
   
//*****************************************************************************
// MultiPointUnoptimized::getUnmodeledError
//*****************************************************************************
MultiDblVctr
MultiPointUnoptimized::
getUnmodeledError(const RasterGM&        model,
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
getUnmodeledCrossCovariance(const RasterGM& model,
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
