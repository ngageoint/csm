//####################################################################
//
//    FILENAME:          WGS84ReferenceFrame.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for WGS84 reference frame realization and epoch.
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

#ifndef __CSM_WGS84REFERENCEFRAME_H
#define __CSM_WGS84REFERENCEFRAME_H

#include "csm.h"
#include <string>

#define WGS84_ORIGINAL "WGS84 ORIGINAL"
#define WGS84_G730 "G730"
#define WGS84_G873 "G873"
#define WGS84_G1150 "G1150"
#define WGS84_G1674 "G1674"
#define WGS84_G1762 "G1762"

namespace csm
{

class CSM_EXPORT_API WGS84ReferenceFrame
{
public:
        
    struct CSM_EXPORT_API RealizationDefinition 
    {
    public:
        RealizationDefinition() : m_name("WGS84_ORIGINAL"), m_epoch(1984.0) {};
        RealizationDefinition(const std::string &name, float epoch) : m_name(name), m_epoch(epoch) {};
        std::string m_name;
        float m_epoch;
    };
    //> Realizations are defined by a string name and a float epoch which is in terms of years since 0AD.
    // The default realization is the original one from 1984.0
    //<

    WGS84ReferenceFrame() {};
    //> construct default realization
    //<

    WGS84ReferenceFrame(const std::string &name, const float epoch) : m_realization(name,epoch) {};
    //> construct custom realization
    //<

    void setDefinition(const std::string &name, const float epoch);
    //> convenience to set the internal structure (it is public)
    //<
    
    void setDefinition(const RealizationDefinition& rd);
    //> convenience to set the internal structure (it is public)
    //<

    RealizationDefinition getDefinition() const;
    //> convenience to get the internal structure (it is public)
    //<
        
private:
    RealizationDefinition m_realization;
    //> the name and epoch of the realization are here
    //<

};

} // namespace csm

#endif // __CSM_WGS84REFERENCEFRAME_H

