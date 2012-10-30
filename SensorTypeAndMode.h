//#############################################################################
//
//    FILENAME:          SensorTypeAndMode.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for the sensor type and mode information.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment   
//     -----------   ------   -------
//     02-Mar-2012   SCM      Initial version
//     30-Oct-2012   SCM      Renamed to SensorTypeAndMode.h
//
//    NOTES:
//
//#############################################################################

#ifndef __CSM_SENSORTYPEANDMODE_H
#define __CSM_SENSORTYPEANDMODE_H

#include <string>

namespace csm
{

class SensorTypeAndMode
{
public:
   SensorTypeAndMode() : theSensorType(), theSensorMode() {}
   SensorTypeAndMode(const std::string sensorType,
                     const std::string sensorMode)
      : theSensorType(sensorType), theSensorMode(sensorMode) {}

   const std::string& type() const {return theSensorType;}
   const std::string& mode() const {return theSensorMode;}

private:
   std::string theSensorType;
   std::string theSensorMode;
};

#define TYPE_UNK           "UNKNOWN"
#define TYPE_EO            "EO"
#define TYPE_IR            "IR"
#define TYPE_MWIR          "MWIR"
#define TYPE_LWIR          "LWIR"
#define TYPE_SAR           "SAR"
#define TYPE_EOIRSC        "EO_IR_SPECIAL_CASE"
#define MODE_FRAME         "FRAME"
#define MODE_PULSE         "PULSE"
#define MODE_PB            "PUSHBROOM"
#define MODE_WB            "WHISKBROOM"
#define MODE_SPOT          "SPOT"
#define MODE_STRIP         "STRIP"
#define MODE_SCAN          "SCAN"
#define MODE_VIDEO         "VIDEO"
#define MODE_BODY_POINTING "BODY_POINTING"

} // namespace csm

#endif
