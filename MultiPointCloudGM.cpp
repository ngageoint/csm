//##############################################################################
//
//    FILENAME:          MultiPointCloudGM.cpp
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
//     09-Nov-20221  EJR    Initial version.
//
//    NOTES:
//
//##############################################################################

#define CSM_LIBRARY

#include "MultiPointCloudGM.h"

namespace csm
{
	//*****************************************************************************
	// MultiPointCloudGM::~MultiPointCloudGM
	//*****************************************************************************
	MultiPointCloudGM::~MultiPointCloudGM()
	{}

	//*****************************************************************************
	// MultiPointCloudGM::getFamily()
	//*****************************************************************************
	std::string MultiPointCloudGM::getFamily() const
	{
		return (ObjectSpacePointCloudGM::getFamily() + CSM_MPR_FAMILY);
	}
}