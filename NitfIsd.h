//#############################################################################
//
//    FILENAME:   CSMISDNITF.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    Header for the NITF 2.0 and 2.1 ISD classes derived from the csm::Isd
//    base class.  ISD is encapsulated in a C++ class for transfer through the
//    CSM interface. ISD is passed as a pointer to a simple ISD base class (for
//    example, csm::Isd* isd).
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

#ifndef __csm_ISDNITF_H
#define __csm_ISDNITF_H

#include "CSMImageSupportData.h"
#include "CSMMisc.h"

#include <vector>
#include <string>

namespace csm
{

class CSM_EXPORT_API Des
{
public:
   Des() : theSubHeader(), theData() {}
   Des(const std::string& aSubHeader, const std::string& aData)
      : theSubHeader(aSubHeader), theData(aData) {}
   ~Des() {}

   void clear() { theSubHeader = theData = ""; }

   const std::string& subHeader() const { return theSubHeader; }
   const std::string& data() const { return theData; }

   void setSubHeader(const std::string& sh) { theSubHeader = sh; }
   void setData(const std::string& data) { theData = data; }

private:
   std::string theSubHeader;
   std::string theData;
};

class CSM_EXPORT_API Tre
{
public:
   Tre() : theName(), theLength(0), theData() {}
   explicit Tre(const std::string& treData)
      : theName(), theLength(0), theData() { setTRE(treData); }
   Tre(const std::string& aName, unsigned int aLength, const std::string& aData)
      : theName(aName), theLength(aLength), theData(aData) {}
   ~Tre() {}

   const std::string& name() const   { return theName; }
   const unsigned int length() const { return theLength; }
   const std::string& data() const   { return theData; }

   const void setName(const std::string& aName) { theName = aName; }
   const void setLength(unsigned int aLength)   { theLength = aLength; }
   const void setData(const std::string& aData) { theData = aData; }

   // treData includes TRE name, length and data
   void setTRE(const std::string& treData)
   {
      if (treData.length() < 11) return;
      theName = treData.substr(0, 6);
      theLength = atoi(treData.substr(6, 5).c_str());
      theData = treData.substr(11);
   }

   void clear() { theName = ""; theLength = 0; theData = ""; }

private:
   std::string theName;
      //> This contains the 6 character TRE name.
      //<
   unsigned int theLength;
      //> This contains the tag length, which will be data.length() + 11.
      //<
   std::string theData;
      //> This contains the TRE data.
      //<
};

class CSM_EXPORT_API Image
{
public:
   Image() : theSubHeader(), theImageTres() {}
   Image(const std::string& aSubHeader, const std::vector<Tre>& tres)
      : theSubHeader(aSubHeader), theImageTres(tres) {}
      //> This method constructs the Image object with the given image
      //  subheader data and list of parsed tagged record extensions (TREs).
      //
      //  The image subheader data should include a copy of the TRE data.
      //<
   ~Image() {}

   const std::string& subHeader() const { return theSubHeader; }
      //> This method returns the entire image subheader, including a copy of
      //  the TRE data.
      //<
   const std::vector<Tre>& imageTREs() const { return theImageTres; }
      //> This method returns the list of image subheader tagged record
      //  extensions (TREs).
      //<

   void setSubHeader(const std::string& sh) { theSubHeader = sh; }
      //> This method sets the entire image subheader, including a copy of
      //  the TRE data.  When using this method, it is important to keep the
      //  list of TREs in sync using the list modification methods below.
      //<

   void clearImageTREs() { theImageTres.clear(); }
      //> This method remvoes all existing Tre objects from the list.
      //<
   void addImageTRE(const Tre& tre) { theImageTres.push_back(tre); }
      //> This method adds the given Tre object to the list.
      //<
   void setImageTREs(const std::vector<Tre>& tres) { theImageTres = tres; }
      //> This method sets the TRE list to the given vector.
      //<

private:
   std::string      theSubHeader;
      //> This string contains the entire image subheader, including a copy of
      //  the TRE data.
      //<
   std::vector<Tre> theImageTres;
};

// this is an intermediary class -- do not construct
class CSM_EXPORT_API NitfIsd : public Isd
{
public:
   virtual ~NitfIsd() {}

protected:
   NitfIsd(const std::string& format, const std::string& filename)
      : Isd(format,filename),theFileHeader(),theFileTREs(),theFileDESs(),theImages() {}

   const std::string& fileHeader() const { return theFileHeader; }
      //> This method returns the entire image subheader, including a copy of
      //  the TRE data.
      //<

   void setFileHeader(const std::string& head) { theFileHeader = head; }
      //> This method sets the entire file header, including a copy of
      //  the TRE data.  When using this method, it is important to keep the
      //  list of TREs in sync using the list modification methods below.
      //<

   void clearFileTREs() { theFileTREs.clear(); }
      //> This method remvoes all existing Tre objects from the list.
      //<
   void addFileTRE(const Tre& tre) { theFileTREs.push_back(tre); }
      //> This method adds the given Tre object to the list.
      //<
   void setFileTREs(const std::vector<Tre>& tres) { theFileTREs = tres; }
      //> This method sets the TRE list to the given vector.
      //<

   void clearFileDESs() { theFileDESs.clear(); }
      //> This method remvoes all existing Des objects from the list.
      //<
   void addFileDES(const Des& des) { theFileDESs.push_back(des); }
      //> This method adds the given Des object to the list.
      //<
   void setFileDESs(const std::vector<Des>& dess) { theFileDESs = dess; }
      //> This method sets the DES list to the given vector.
      //<

   void clearImages() { theImages.clear(); }
      //> This method remvoes all existing Des objects from the list.
      //<
   void addImage(const Image& image) { theImages.push_back(image); }
      //> This method adds the given Des object to the list.
      //<
   void setImages(const std::vector<Image>& images) { theImages = images; }
      //> This method sets the DES list to the given vector.
      //<

private:
   std::string theFileHeader;
      //> This string contains the full file header text, including a copy of
      //  the file level TRE data.
      //<

   std::vector<Tre> theFileTREs;
   std::vector<Des> theFileDESs;
   std::vector<Image> theImages;
};

class CSM_EXPORT_API Nitf20Isd : public NitfIsd
{
public:
   Nitf20Isd(const std::string& filename) : NitfIsd("NITF2.0", filename) {}
   virtual ~Nitf20Isd() {}
};

class CSM_EXPORT_API Nitf21Isd : public NitfIsd
{
public:
   Nitf21Isd(const std::string& filename) : NitfIsd("NITF2.1", filename) {}
   virtual ~Nitf21Isd() {}
};

} // namespace csm

#endif

