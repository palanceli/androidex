objects = smartptr.o testlightptr.o RefBase.o testweightptr.o

smartptr : $(objects)
	g++ -o smartptr $(objects)

$(object) : RefBase.h StrongPointer.h meyers.h
	
.PHONY: clean
clean :
	rm smartptr  $(objects)