//####################################################################
//
//    FILENAME:          CoordinateReferenceSystem.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for CSM coordinate system definitions.
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
//###################################################################
#ifndef _H_COORDINATE_REF_SYSTEM_H_
#define _H_COORDINATE_REF_SYSTEM_H_

#include "csm.h"
namespace csm
{
	enum CSM_EXPORT_API CRS_TYPE
	{
		ECEF,
		ECI,
		LSR
	};

	class CSM_EXPORT_API CoordinateReferenceSystem
	{
	public:
		CoordinateReferenceSystem();
		CoordinateReferenceSystem(const CRS_TYPE type,
			const std::string& code, const std::string& epoch);
		~CoordinateReferenceSystem() {};
		void setType(const CRS_TYPE type);
		void setCode(const std::string &code);
		void setEpoch(const std::string &epoch);

		CRS_TYPE getType() const;
		std::string getCode() const;
		std::string getEpoch() const;

	private:
		CRS_TYPE crsType;
		std::string crsCode;
		std::string crsEpoch;
	};

} // namespace csm

#endif // _H_COORDINATE_REF_SYSTEM_H_
