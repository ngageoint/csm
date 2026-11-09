//#############################################################################
//
//    FILENAME:          BistaticRGM.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    This file provides implementation for methods declared in the
//    BistaticRGM class.
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     05-Nov-2026   SCM      Initial version.
//
//    NOTES:
//
//    Refer to BistaticRGM.h for more information.
//
//#############################################################################

#define CSM_LIBRARY

#include "BistaticRGM.h"

namespace csm {

//*****************************************************************************
// BistaticRGM::getFamily()
//*****************************************************************************
std::string BistaticRGM::getFamily() const
{
   return (RasterGM::getFamily() + CSM_BISTATIC_FAMILY);
}

//*****************************************************************************
// BistaticRGM::getReceiverPosition()
//*****************************************************************************
EcefCoord BistaticRGM::getReceiverPosition(const ImageCoord& imagePt) const
{
   return getSensorPosition(imagePt);
}

//*****************************************************************************
// BistaticRGM::getReceiverPosition()
//*****************************************************************************
EcefCoord BistaticRGM::getReceiverPosition(double time) const
{
   return getSensorPosition(time);
}

//*****************************************************************************
// BistaticRGM::getSensorPosition()
//*****************************************************************************
EcefVector BistaticRGM::getReceiverVelocity(const ImageCoord& imagePt) const
{
   return getReceiverVelocity(imagePt);
}

//*****************************************************************************
// BistaticRGM::getReceiverVelocity()
//*****************************************************************************
EcefVector BistaticRGM::getReceiverVelocity(double time) const
{
   return getSensorVelocity(time);
}

//*****************************************************************************
// BistaticRGM::getReceiverIlluminationDirection()
//*****************************************************************************
EcefVector BistaticRGM::getReceiverIlluminationDirection(
   const EcefCoord& groundPt) const
{
   return getIlluminationDirection(groundPt);
}

} // namespace csm
