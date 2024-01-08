//####################################################################
//
//    FILENAME:          WGS84ReferenceFrame.cpp
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Implementation for WGS84 reference frame realization and epoch.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author    Comment
//     -----------   ------    -------
//     31-December-2021   Eugene Rose CCB Change
//
//    NOTES: 
//    As of writing this, these are the WGS84 realizations to date.
//    WGS84 ORIGINAL 1984.0
//    G730           1994.0
//    G873           1997.0
//    G1150          2001.0
//    G1674          2005.0
//    G1762          2005.0
//
//###################################################################
#define CSM_LIBRARY

#include "csm.h"
#include "WGS84ReferenceFrame.h"

namespace csm
{
//****************************************************************************
// WGS84ReferenceFrame::setDefinition()
//****************************************************************************
void WGS84ReferenceFrame::setDefinition(const std::string &name, const float epoch)
{
    m_realization = RealizationDefinition(name, epoch);
}

//****************************************************************************
// WGS84ReferenceFrame::setDefinition()
//****************************************************************************
void WGS84ReferenceFrame::setDefinition(const RealizationDefinition& rd)
{
    m_realization = rd;
}

//****************************************************************************
// WGS84ReferenceFrame::getDefinition()
//****************************************************************************
csm::WGS84ReferenceFrame::RealizationDefinition WGS84ReferenceFrame::getDefinition() const
{
    return m_realization;
}
}
