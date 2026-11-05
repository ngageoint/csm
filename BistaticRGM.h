//#############################################################################
//
//    FILENAME:          BistaticRGM.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for abstract class that is to provide a common interface from
//    which CSM bistatic models will inherit.  It is derived from the
//    RasterGM class.
//
//    This interface adds position, velocity, and illumination directions for
//    both the transmitter and receiver vehicles.  By default, the receiver
//    methods return the equivalent to the base class RasterGM interface
//    "getSesnor" equivalent methods.  Actual implementations of this interface
//    may choose to return different values for "receiver" and "sensor".
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     05-Nov-2026   SCM      Initial version.
//
//    NOTES:
//
//#############################################################################

#ifndef __CSM_BISTATICRGM_H
#define __CSM_BISTATICRGM_H

#include "RasterGM.h"

#define CSM_BISTATIC_FAMILY "Bistatic"

namespace csm
{
class CSM_EXPORT_API BistaticRGM : public RasterGM
{
public:
   BistaticRGM() = default;
   ~BistaticRGM() override = default;

   std::string getFamily() const override;
      //> This method returns the Family ID for the current model.  This will
      //  be the family of RasterGM concatenated with CSM_BISTATIC_FAMILY.
      //<

   //---
   // Transmitter methods
   //---
   virtual EcefCoord getTransmitterPosition(const ImageCoord& imagePt) const = 0;
      //> This method returns the position of the physical transmitter
      //  (x,y,z in ECEF meters) when the pixel at the given imagePt
      //  (line, sample in full image space pixels) was captured.
      //
      //  A csm::Error will be thrown if the transmitter position is not
      //  available.
      //<

   virtual EcefCoord getTransmitterPosition(double time) const = 0;
      //> This method returns the position of the physical transmitter
      //  (x,y,z meters ECEF) at the given time relative to the reference date
      //  and time given by the Model::getReferenceDateAndTime method.
      //
      //  A csm::Error will be thrown if the transmitter position is not
      //  available.
      //<

   virtual EcefVector getTransmitterVelocity(const ImageCoord& imagePt) const = 0;
      //> This method returns the velocity of the physical transmitter
      //  (x,y,z in ECEF meters per second) when the pixel at the given imagePt
      //  (line, sample in full image space pixels) was captured.
      //
      //  A csm::Error will be thrown if the transmitter velocity is not
      //  available.
      //<

   virtual EcefVector getTransmitterVelocity(double time) const = 0;
      //> This method returns the velocity of the physical transmitter
      //  (x,y,z in ECEF meters per second ) at the given time relative to the
      //  reference date and time given by the Model::getReferenceDateAndTime
      //  method.
      //
      //  A csm::Error will be thrown if the transmitter velocity is not
      //  available.
      //<

   virtual EcefVector getTransmitterIlluminationDirection(
      const EcefCoord& groundPt) const = 0;
      //> This method returns a vector defining the direction of
      //  illumination at the given groundPt (x,y,z in ECEF meters) from the
      //  transmitter's point of view.
      //
      //  Note that there are two opposite directions possible.  Both are
      //  valid, so either can be returned; the calling application can convert
      //  to the other as necessary.
      //
      //  A csm::Error will be thrown if the transmitter illumination direction
      //  is not available.
      //<

   //---
   // Receiver methods
   //---
   virtual EcefCoord getReceiverPosition(const ImageCoord& imagePt) const;
      //> This method returns the position of the physical receiver
      //  (x,y,z in ECEF meters) when the pixel at the given imagePt
      //  (line, sample in full image space pixels) was captured.
      //
      //  A csm::Error will be thrown if the receiver position is not
      //  available.
      //
      //  By default, this returns getSensorPosition().
      //<

   virtual EcefCoord getReceiverPosition(double time) const;
      //> This method returns the position of the physical receiver
      //  (x,y,z meters ECEF) at the given time relative to the reference date
      //  and time given by the Model::getReferenceDateAndTime method.
      //
      //  A csm::Error will be thrown if the receiver position is not
      //  available.
      //
      //  By default, this returns getSensorPosition().
      //<

   virtual EcefVector getReceiverVelocity(const ImageCoord& imagePt) const;
      //> This method returns the velocity of the physical receiver
      //  (x,y,z in ECEF meters per second) when the pixel at the given imagePt
      //  (line, sample in full image space pixels) was captured.
      //
      //  A csm::Error will be thrown if the receiver velocity is not
      //  available.
      //
      //  By default, this returns getSensorVelocity().
      //<

   virtual EcefVector getReceiverVelocity(double time) const;
      //> This method returns the velocity of the physical receiver
      //  (x,y,z in ECEF meters per second ) at the given time relative to the
      //  reference date and time given by the Model::getReferenceDateAndTime
      //  method.
      //
      //  A csm::Error will be thrown if the receiver velocity is not
      //  available.
      //
      //  By default, this returns getSensorVelocity().
      //<

   virtual EcefVector getReceiverIlluminationDirection(
      const EcefCoord& groundPt) const;
      //> This method returns a vector defining the direction of
      //  illumination at the given groundPt (x,y,z in ECEF meters) from the
      //  receiver's point of view.
      //
      //  Note that there are two opposite directions possible.  Both are
      //  valid, so either can be returned; the calling application can convert
      //  to the other as necessary.
      //
      //  A csm::Error will be thrown if the receiver illumination direction is
      //  not available.
      //
      //  By default, this returns getIlluminationDirection().
      //<
};

} // namespace csm

#endif
