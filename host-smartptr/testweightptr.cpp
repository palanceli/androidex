#include <stdio.h>
#include "RefBase.h"
#include "logger.h"

#define INITIAL_STRONG_VALUE (1<<28)

class WeightClass : public RefBase
{
public:
	void printRefCount();
};

void WeightClass::printRefCount()
{
	int32_t strong = getStrongCount();
	weakref_type* ref = getWeakRefs();
	Logging("Strong Ref Count:%d.\n", (strong == INITIAL_STRONG_VALUE ? 0 :strong));
	Logging("Weak Ref Count:%d.\n", ref->getWeakCount());
}

// ---------------------------------------------------------------------------

class StrongClass :public WeightClass
{
public:
	StrongClass(){Logging("StrongClass::StrongClass()");}
	virtual ~StrongClass(){Logging("StrongClass::~StrongClass()");}
};


// ---------------------------------------------------------------------------
class WeakClass : public WeightClass
{
public:
	WeakClass(){Logging("WeakClass::WeakClass()");}
	virtual ~WeakClass(){Logging("WeakClass::~WeakClass()");}
};
// ---------------------------------------------------------------------------

class ForeverClass : public WeightClass
{
public:
	ForeverClass(){Logging("ForeverClass::ForeverClass()");}
	virtual ~ForeverClass(){Logging("ForeverClass::~ForeverClass()");}
};
// ---------------------------------------------------------------------------

void TestStrongClass(StrongClass* pStrongClass)
{
	wp<StrongClass> wpOut = pStrongClass;
	pStrongClass->printRefCount();
	{
		sp<StrongClass> spInner = pStrongClass;
		pStrongClass->printRefCount();;
	}
	sp<StrongClass> spOut = wpOut.promote();
	Logging("spOut: %p.", spOut.get());
}

void TestWeakClass(WeakClass* pWeakClass)
{
	wp<WeakClass> wpOut = pWeakClass;
	pWeakClass->printRefCount();
	{
		sp<WeakClass> spInner = pWeakClass;
		pWeakClass->printRefCount();
	}
	pWeakClass->printRefCount();
	sp<WeakClass> spOut = wpOut.promote();
	Logging("spOut: %p.", spOut.get());
}

void TestForeverClass(ForeverClass* pForeverClass)
{
	wp<ForeverClass> wpOut = pForeverClass;
	pForeverClass->printRefCount();
	{
		sp<ForeverClass> spInner = pForeverClass;
		pForeverClass->printRefCount();
	}
}

int testweightptr(int argc, char const * argv[])
{
	Logging("Test Strong Class:");
	StrongClass* pStrongClass = new StrongClass();
	TestStrongClass(pStrongClass);

	Logging("Test Weak Class:");
	WeakClass* pWeakClass = new WeakClass();
	TestWeakClass(pWeakClass);

	Logging("Test Forever Class:");
	ForeverClass* pForeverClass = new ForeverClass();
	TestForeverClass(pForeverClass);
	pForeverClass->printRefCount();
	delete pForeverClass;

	return 0;
}