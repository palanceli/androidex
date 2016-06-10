smartptr : smartptr.o testlightptr.o RefBase.o testweightptr.o
	g++ -o smartptr smartptr.o testlightptr.o RefBase.o testweightptr.o

smartptr.o : smartptr.cpp RefBase.h StrongPointer.h meyers.h
	g++ -c -g smartptr.cpp

testlightptr.o : testlightptr.cpp RefBase.h StrongPointer.h
	g++ -c -g testlightptr.cpp

RefBase.o : RefBase.cpp RefBase.h
	g++ -c -g RefBase.cpp

testweightptr.o : testweightptr.cpp RefBase.h StrongPointer.h
	g++ -c -g testweightptr.cpp

clean :
	rm smartptr  *.o