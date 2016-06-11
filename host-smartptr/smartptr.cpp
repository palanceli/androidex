#include <stdio.h>
#include "RefBase.h"
#include <string.h>
#include "meyers.h"
#include "logger.h"

#define ADDTC(tcname)	{ #tcname, tcname},
#define END_TESTSUITE	{0, 0}

typedef int(*testcasefunc)(int argc, char const *argv[]);
struct TESTCASE
{
	char const * tcname;
	testcasefunc pFunc;
};


int testlightptr(int argc, char const * argv[]);
int testweightptr(int argc, char const * argv[]);

int tc01(int argc, char const *argv[])
{
	return testlightptr(argc, argv);
}

int tc02(int argc, char const *argv[])
{
	meyers::String s1("abc");
	meyers::String s2("123");
	return 0;
}

int tc03(int argc, char const *argv[])
{
	return testweightptr(argc, argv);
}

TESTCASE testsuite[] = {
	ADDTC(tc01)
	ADDTC(tc02)
	ADDTC(tc03)
	END_TESTSUITE
};

// ./smartptr <tcname>，如：
// ./smartptr tc01
int main(int argc, char const * argv[])
{
	if(argc <= 1){
		Logging("usage: smartptr <tcname>");
		return -1;
	}
	TESTCASE* ptc = testsuite;
	while(ptc->pFunc != 0){
		if(strcmp(ptc->tcname, argv[1]) == 0)
			return ptc->pFunc(argc, argv);
		++ptc;
	}
	Logging("tc %s not found!", argv[1]);
	return -1;
}