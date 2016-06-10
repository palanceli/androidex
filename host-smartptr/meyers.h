#ifndef __MEYERS_H__
#define __MEYERS_H__

namespace meyers{

template <class T>
class RCPtr
{
public:
	RCPtr(T* realPtr = 0);
	RCPtr(const RCPtr& rhs);
	~RCPtr();

	RCPtr& operator=(const RCPtr& rhs);
	T* operator->() const;
	T& operator*() const;
private:
	T *mPointee;
	void init();
};

template <class T>
void RCPtr<T>::init()
{
	if(mPointee == 0)
		return;
	if(!mPointee->isShareable()){
		mPointee = new T(*mPointee);
	}
	mPointee->addReference();
}

template <class T>
RCPtr<T>::RCPtr(T* realPtr) : mPointee(realPtr)
{
	init();
}

template <class T>
RCPtr<T>::RCPtr(const RCPtr& rhs) : mPointee(rhs.mPointee)
{
	init();
}

template <class T>
RCPtr<T>::~RCPtr()
{
	if(mPointee)
		mPointee->removeReference();
}

template <class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr& rhs)
{
	if(mPointee != rhs.mPointee){
		if(mPointee)
			mPointee->removeReference();
		mPointee = rhs.mPointee;
		init();
	}
	return *this;
}

template <class T>
T& RCPtr<T>::operator *() const 
{
	return *mPointee;
}

template <class T>
T* RCPtr<T>::operator ->() const
{
	return mPointee;
}

class RCObject
{
public:
	void addReference(){++mRefCount;}
	void removeReference(){if(--mRefCount == 0) delete this;}
	void markUnshareable(){mShareable = false;}
	bool isShareable() const{return mShareable;}
	bool isShared() const{return mRefCount > 1;}
protected:
	RCObject() : mRefCount(0), mShareable(true){}
	RCObject(const RCObject& rhs) : mRefCount(0), mShareable(true){}
	RCObject& operator=(const RCObject& rhs){return *this;}
	virtual ~RCObject()=0;
private:
	int 	mRefCount;
	bool 	mShareable;
};

RCObject::~RCObject()
{}

class String
{
public:
	String(const char *value="") : mValue(new StringValue(value)){}
	const char& operator[](int index)const{return mValue->mData[index];}
	char& operator[](int index);
private:
	struct StringValue : public RCObject
	{
		char* mData;
		StringValue(const char* initValue);
		StringValue(const StringValue& rhs);
		void init(const char* initValue);
		~StringValue();
	};
	RCPtr<StringValue> mValue;
};

void String::StringValue::init(const char* initValue)
{
	mData = new char[strlen(initValue) + 1];
	strcpy(mData, initValue);
}

String::StringValue::StringValue(const char* initValue)
{	init(initValue);}

String::StringValue::StringValue(const StringValue& rhs)
{	init(rhs.mData);}

String::StringValue::~StringValue()
{	delete [] mData;}

char& String::operator[](int index)
{
	if(mValue->isShared()){
		mValue = new StringValue(mValue->mData);
	}
	mValue->markUnshareable();
	return mValue->mData[index];	
}

};

#endif