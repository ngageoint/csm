//#############################################################################
//
//    FILENAME:          ModelProperties.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    This file provides implementation for virtual methods declared in the
//    ModelProperties interface.
//
//    SOFTWARE HISTORY:
//>
//     Date          Author   Comment
//     -----------   ------   -------
//     24-Jan-2022   SCM      Initial creation
//<
//#############################################################################

#define CSM_LIBRARY

#include "ModelProperties.h"

namespace csm {

//*****************************************************************************
// ModelProperties::~ModelProperties
//*****************************************************************************
ModelProperties::~ModelProperties()
{
}

//*****************************************************************************
// ModelProperties::setProperty
//*****************************************************************************
bool ModelProperties::setProperty(const std::string& name,
                                  const std::string& value)
{
   return false;
}

//*****************************************************************************
// ModelProperties::hasProperty
//*****************************************************************************
bool ModelProperties::hasProperty(const std::string& name) const
{
   return false;
}

//*****************************************************************************
// ModelProperties::allProperties
//*****************************************************************************
std::vector<std::string> ModelProperties::allProperties() const
{
   static const std::vector<std::string> EMPTY;
   return EMPTY;
}

}
