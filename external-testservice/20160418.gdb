# main
#  BpServiceManager::getService
#   BpServiceManager::checkService
#    Parcel::readStrongBinder
#     Parcel::unflatten_binder
define sm_binder
	target remote :1234
	b main
	# 停在main函数
	c 

	set solib-absolute-prefix out/debug/target/product/generic/symbols/

	# 停在sp < IBinder > binder = sm->getService(String16("service.testservice"));
	b TestClient.cpp:16 
	c

	b Parcel.cpp:301
	b Parcel.cpp:304
	commands
		echo 'flat->handle:'
		p flat->handle
	end
	c
end

define sm2
	target remote :1234
	b main
	c
	set solib-absolute-prefix out/debug/target/product/generic/symbols/

	# ProcessState::getStrongProxyForHandle
	break ProcessState.cpp:193 if handle != 0
	commands
		p handle
		bt
	end
	c		
	
end

define query
	target remote :1234
	b main
	# 停在main函数
	c 

	set solib-absolute-prefix out/debug/target/product/generic/symbols/
	
end

define common
	target remote :1234
	b main
	c
	set solib-absolute-prefix out/debug/target/product/generic/symbols/
end

define sm
	target remote :1234
	b main
	c
	set solib-absolute-prefix out/debug/target/product/generic/symbols/
	b service_manager.c:309
	c
end

define 160428a
	b IPCThreadState.cpp:934
	c
end