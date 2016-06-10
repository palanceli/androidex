#include <stdio.h>
#include "RefBase.h"
#include <string.h>
#include "meyers.h"

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

int main(int argc, char const * argv[])
{
	return tc03(argc, argv);
}