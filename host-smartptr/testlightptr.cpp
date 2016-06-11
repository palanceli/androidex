#include <stdio.h>
#include "RefBase.h"
#include "logger.h"

class LightClass : public LightRefBase <LightClass>
{
public:
	LightClass(){}
	~LightClass(){}
};

int testlightptr(int argc, char const * argv[])
{
	LightClass * pLightClass = new LightClass();
	sp<LightClass> lpOut = pLightClass;
	Logging("Light Ref Count: %d.", pLightClass->getStrongCount());
	{
		sp<LightClass> lpInner = lpOut;
		Logging("Light Ref Count: %d.", pLightClass->getStrongCount());
	}
	Logging("Light Ref Count:%d.", pLightClass->getStrongCount());
	return 0;
}