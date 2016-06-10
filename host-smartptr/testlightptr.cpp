#include <stdio.h>
#include "RefBase.h"
#include <string.h>

class LightClass : public LightRefBase <LightClass>
{
public:
	LightClass(){printf("%s:%d\tConstruct LightClass Object.\n", __FILE__, __LINE__);}
	~LightClass(){printf("%s:%d\tDestroy LightClass Object.\n", __FILE__, __LINE__);}
};

int testlightptr(int argc, char const * argv[])
{
	LightClass * pLightClass = new LightClass();
	sp<LightClass> lpOut = pLightClass;
	printf("%s:%d\tLight Ref Count: %d.\n", __FILE__, __LINE__, pLightClass->getStrongCount());
	{
		sp<LightClass> lpInner = lpOut;
		printf("%s:%d\tLight Ref Count: %d.\n", __FILE__, __LINE__, pLightClass->getStrongCount());
	}
	printf("%s:%d\tLight Ref Count:%d.\n", __FILE__, __LINE__, pLightClass->getStrongCount());
	return 0;
}