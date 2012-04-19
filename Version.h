//#############################################################################
//
//    FILENAME:          CSMModel.h
//
//    CLASSIFICATION:    Unclassified
//
//    DESCRIPTION:
//
//    This class represents a CSM version.  A version is a series of integers,
//    like "1.2.3".  Versions can be compared for equality or for relative
//    position.
//
//    LIMITATIONS:       None
//
//
//    SOFTWARE HISTORY:
//     Date          Author   Comment   
//     -----------   ------   -------
//     19-Apr-2012   SCM      Initial creation
//
//    NOTES:
//
//#############################################################################

#ifndef __CSMVERSION_H
#define __CSMVERSION_H

#include "CSMMisc.h"

#include <string>
#include <iosfwd>
#include <vector>

namespace csm
{

class CSM_EXPORT_API Version
{
public:
   explicit Version(const std::string& version);
      //> This constructs a CSM version object with the given string
      //  version.  The string should be a sequence of numbers separated by
      //  periods (".").
      //<
   Version(int major, int minor, int revision = -1);
      //> This constructs a CSM version object with the given major, minor, and
      //  revision version information.  The major and minor versions must be
      //  greater than or equal to 0, or an exception will be thrown.  If the
      //  revision is less than zero, it will be omitted from the object.
      //
      //  The resulting version string will look like "major.minor.revision".
      //<
   ~Version();
      //> This is the destructor.  This class has no virtual methods, and
      //  should not be derived from.
      //<

   std::ostream& print(std::ostream& os) const;
      //> This method renders the version as a string to the given output
      //  stream.
      //<

   bool operator==(const Version& rhs);
      //> This method returns true if the two versions are equal.
      //<
   bool operator<(const Version& rhs);
      //> This method returns true if this version is earler than the given
      //  version.
      //<

private:
   std::vector<int> theVersions;
};

} // namespace csm

inline std::ostream& operator<<(std::ostream& os, const csm::Version& vsrn)
{
   return vsrn.print(os);
}

#endif
