#include "Test.h"
namespace android
{
    // IMPLEMENT_META_INTERFACE(TestService, "android.TestServer.ITestService");
    const android::String16 ITestService::descriptor("android.TestServer.ITestService");
    const android::String16& ITestService::getInterfaceDescriptor() const {
        return ITestService::descriptor;
	}
    android::sp< ITestService > ITestService::asInterface(
            const android::sp<android::IBinder>& obj)
    {
        android::sp< ITestService > intr;
        if (obj != NULL) {
            intr = static_cast< ITestService *>( 
                obj->queryLocalInterface(ITestService::descriptor).get());
            if (intr == NULL) {
                intr = new BpTestService(obj);
            }
        }
        return intr;
    }
    ITestService::ITestService() { }
    ITestService::~ITestService() { }
}
