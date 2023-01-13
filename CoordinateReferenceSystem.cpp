//####################################################################
//    FILENAME:          CoordinateReferenceSystem.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Implementation for CSM coordinate system definitions.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author    Comment
//     -----------   ------    -------
//     31-December-2023    Eugene Rose CCB Change CSM 4.0
//
//    NOTES: 
//    Three types of coordinate systems are supported:
//    ECEF
//    ECI
//    LSR
// 
//    ECEF coordinate sysetms are identified by EPSG code and epoch.
//       Examples are:
//       "EPSG:9988", "2020"    (ITRF)
//       "EPSG:4326", "2019"    (WGS84)
// 
//    ECI coordinate systems are identified by an IERS name and an epoch.
//       Examples are:
//       "J2000", "2018"
//       "ICRF",  "2020"
// 
//    LSR coordinates systems do not need sub-types.
// 
//    LIMITATIONS:       None
// 
//    SOFTWARE HISTORY:
//     Date          Author    Comment
//     -----------   ------    -------
//     31-Sep-2023   EJR    CSM 4.0.
//
//###################################################################
#define CSM_LIBRARY

#include "csm.h"
#include "CoordinateReferenceSystem.h"

namespace csm
{
	CoordinateReferenceSystem::CoordinateReferenceSystem()
	{
		crsType = ECEF;
		crsCode = "EPSG:4326";  // WGS84
		crsEpoch = "2023";
	}

	CoordinateReferenceSystem::CoordinateReferenceSystem(const CRS_TYPE type,
		const std::string& code, const std::string& epoch)
	{
		crsType = type;
		crsCode = code;
		crsEpoch = epoch;
	}

	void CoordinateReferenceSystem::setType(const CRS_TYPE type)
	{
		crsType = type;
	}
	void CoordinateReferenceSystem::setCode(const std::string& code)
	{
		crsCode = code;
	}
	void CoordinateReferenceSystem::setEpoch(const std::string& epoch)
	{
		crsEpoch = epoch;
	}
	CRS_TYPE CoordinateReferenceSystem::getType() const
	{
		return crsType;
	}
	std::string CoordinateReferenceSystem::getCode() const
	{
		return crsCode;
	}
	std::string CoordinateReferenceSystem::getEpoch() const
	{
		return crsEpoch;
	}
};  // namespace csm