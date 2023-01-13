#ifndef _H_MULTIPOINT_CAPABILITIES_
#define _H_MULTIPOINT_CAPABILITIES_
#include "csm.h"
#include "Warning.h"
#include <map>

// problems:
// client can add function that does not exist
// client can get function name wrong
// client is assuming a certain interface when the setting is true. the
//    actual interface is not known here.
namespace csm
{
	class MultiPointCapabilities
	{
	public:
		bool isCapable(std::string funcName)
		{
			return (m_capabilityMap.find(funcName) != m_capabilityMap.end());
		}
		MultiPointCapabilities() {

		}

		void setCapability(std::string funcName, bool cap)
		{
			m_capabilityMap.insert(make_pair(funcName, cap));
		}
	private:
		std::map<std::string, bool>m_capabilityMap;
		
	protected:
	};

}

#endif
