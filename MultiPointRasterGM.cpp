//##############################################################################
//
//    FILENAME:          MultiPointRasterGM.cpp
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
//     31-Dec-2021  JPK    Initial version.
//
//    NOTES:
//
//##############################################################################

#define CSM_LIBRARY

#include "MultiPointRasterGM.h"

namespace csm
{
	//*****************************************************************************
	// MultiPointRasterGM::~MultiRasterPointGM
	//*****************************************************************************
	MultiPointRasterGM::~MultiPointRasterGM()
	{}

	//*****************************************************************************
	// MultiPointRasterGM::getFamily()
	//*****************************************************************************
	std::string MultiPointRasterGM::getFamily() const
	{
		return (ObjectSpaceRasterGM::getFamily() + CSM_MPR_FAMILY);
	}

} // namespace csm
