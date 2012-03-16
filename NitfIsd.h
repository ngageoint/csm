//#############################################################################
//
//    FILENAME:   CSMISDNITF20.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for the NITF 2.0 ISD class derived from the csm_ISD base class.
//    ISD is encapsulated in a C++ class for transfer through the CSM
//    interface. ISD is passed as a pointer to a simple ISD base class
//    (for example, csm_ISD *isd).
//
//    LIMITATIONS:       None
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment   
//     -----------   ------   ------- 
//     01-Jul-2003   LMT      Initial version.
//     06-Feb-2004   KRW      Incorporated changes approved by
//                             January and February configuration
//                             control board.
//     01-Oct-2004   KRW      October 2004 CCB
//     02-Mar-2012   SCM      Refactored interfaces.
//
//    NOTES:
//
//#############################################################################

#ifndef __csm_ISDNITF20_H
#define __csm_ISDNITF20_H

#include "CSMImageSupportData.h"
#include "CSMMisc.h"

#include <vector>
#include <string>

namespace csm {

class CSM_EXPORT_API Des
{
public:
   Des() : subHeader(), data() {}
   Des(const std::string& aSubHeader, const std::string& aData)
      : subHeader(aSubHeader), data(aData) {}
   ~Des() {}

   void clear() { subHeader = data = ""; }

   std::string subHeader;
   std::string data;
};

class CSM_EXPORT_API Tre
{
public:
   Tre() : name(), length(0), data() {}
   explicit Tre(const std::string& treData)
      : name(), length(0), data() { setTRE(treData); }
   Tre(const std::string& aName, unsigned int aLength, const std::string& aData)
      : name(aName), length(aLength), data(aData) {}
   ~Tre() {}

   // treData includes TRE name, length and data
   void setTRE(const std::string& treData)
   {
      if (treData.length() < 11) return;
      name = treData.substr(0, 6);
      length = atoi(treData.substr(6, 5).c_str());
      data = treData.substr(11);
   }

   void clear() { name = ""; length = 0; data = ""; }

   std::string name;
      //> This contains the 6 character TRE name.
      //<
   unsigned int length;
      //> This contains the tag length, which will be data.length() + 11.
      //<
   std::string data;
      //> This contains the TRE data.
      //<
};

class CSM_EXPORT_API Image
{
public:
   Image() : subHeader(), imageTREs() {}
   Image(const std::string& aSubHeader, const std::vector<Tre>& tres)
      : subHeader(aSubHeader), imageTREs(tres) {}
   ~Image() {}

   std::string      subHeader;
      //> This string contains the entire image subheader, including a copy of
      //  the TRE data.
      //<
   std::vector<Tre> imageTREs;
};

// this is an intermediary class -- do not construct
class CSM_EXPORT_API NitfIsd : public Isd
{
public:
   virtual ~NitfIsd() {}

   std::string filename;
      //> full path filename of NITF file. This is an optional field.
      //<

   std::string fileHeader;
      //> This string contains the full file header text, including a copy of
      //  the file level TRE data.
      //<

   std::vector<Tre> fileTREs;
   std::vector<Des> fileDESs;
   std::vector<Image> images;

protected:
   NitfIsd(const std::string& format)
      : Isd(format),filename(),fileHeader(),fileTREs(),fileDESs(),images() {}
};

class CSM_EXPORT_API Nitf20Isd : public NitfIsd
{
public:
   Nitf20Isd() : NitfIsd("NITF2.0") {}
   virtual ~Nitf20Isd() {}
};

} // namespace csm

#endif

