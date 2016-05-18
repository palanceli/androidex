#include "Test.h"
namespace android {
BpTestService::BpTestService(const sp<IBinder>& impl) :
		BpInterface<ITestService>(impl) {
}
void BpTestService::test() {
	printf("BpTestService::test()\n");
	Parcel data, reply;
	data.writeInterfaceToken(ITestService::getInterfaceDescriptor());
	remote()->transact(TEST, data, &reply);
	printf("reply: %d\n", reply.readInt32());
}
}
int main() {
	sp < IServiceManager > sm = defaultServiceManager();
	sp < IBinder > binder = sm->getService(String16("service.testservice"));
	sp<ITestService> cs = interface_cast < ITestService > (binder);
	cs->test();
	return 0;
}
