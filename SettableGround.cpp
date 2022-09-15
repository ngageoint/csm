//#############################################################################
//
//    FILENAME:          SettableGround.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    This file provides implementation for methods declared in the
//    SettableGround class.
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment
//     -----------   ------   -------
//     15-Sep-2022   SCM      Initial Coding
//
//#############################################################################

#ifndef CSM_LIBRARY
#define CSM_LIBRARY
#endif

#include "SettableGround.h"
#include "Model.h"

namespace csm
{

//*****************************************************************************
// SettableGround::SettableGround
//*****************************************************************************
SettableGround::SettableGround()
{
}

//*****************************************************************************
// SettableGround::~SettableGround
//*****************************************************************************
SettableGround::~SettableGround()
{
}

//*****************************************************************************
// SettableGround::getProjection
//*****************************************************************************
std::string SettableGround::getProjection(const csm::Model* model)
{
   const SettableGround* setmdl = dynamic_cast<const SettableGround*>(model);
   if (setmdl) return setmdl->getProjectionInformation();

   // return default
   return "";
}

//*****************************************************************************
// SettableGround::setProjection
//*****************************************************************************
bool SettableGround::setProjection(const csm::Model* model,
                                   const std::string& info)
{
   const SettableGround* setmdl = dynamic_cast<const SettableGround*>(model);
   if (setmdl) return setmdl->setProjectionInformation(info);

   // cannot set
   return false;
}

} // namespace csm
