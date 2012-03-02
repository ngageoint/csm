//#############################################################################
//
//    FILENAME:   csm_ISDNITF21.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for the NITF 2.1 ISD class derived from the csm_ISD base class.
//    ISD is encapsulated in a C++ class for transfer through the CSM
//    interface. ISD is passed as a pointer to a simple ISD base class
//    (for example, csm_ISD *isd).
//
//    LIMITATIONS:       None
//
//                       Date          Author   Comment
//    SOFTWARE HISTORY: 01-Jul-2003    LMT      Initial version.
//                       06-Feb-2004   KRW      Incorporates changes approved by
//                                               January and February 2004
//                                               Configuration control board.
//                       01-Nov-2004   KRW      October 2004 CCB
//                        08-Jan-2005  KRW      Multi Image/Frame ? Administrative changes
//
//    NOTES:
//
//#############################################################################
#ifndef __CSM_ISDNITF21_H
#define __CSM_ISDNITF21_H
#include "CSMImageSupportData.h"
#include "CSMISDNITF20.h"
#include "CSMMisc.h"
class CSM_EXPORT_API NITF_2_1_ISD : public csm_ISD
{
  public:
  NITF_2_1_ISD()
    { _format = "NITF2.1"; numTREs = 0; numImages = 0;
    fileTREs = NULL; images = NULL; numDESs = 0; fileDESs = NULL; }
  ~NITF_2_1_ISD()
    { delete [] images; delete [] fileTREs; delete [] fileDESs;}
  std::string filename; // full path filename of NITF file. This is an optional field.
  std::string fileHeader;
  int     numTREs;
  tre    *fileTREs;
  int    numDESs;
  des    *fileDESs;
  int     numImages;
  image *images;
};
#endif

