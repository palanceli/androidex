objects = smartptr.o testlightptr.o RefBase.o testweightptr.o

smartptr : $(objects)
	g++ -o smartptr $(objects)

$(objects) : logger.h RefBase.h StrongPointer.h meyers.h

# smartptr.o : logger.h RefBase.h StrongPointer.h meyers.h
# 	g++ -c -g smartptr.cpp

# testlightptr.o : logger.h RefBase.h StrongPointer.h
# 	g++ -c -g testlightptr.cpp

# RefBase.o : logger.h RefBase.h
# 	g++ -c -g RefBase.cpp

# testweightptr.o : logger.h RefBase.h StrongPointer.h
# 	g++ -c -g testweightptr.cpp

.PHONY: clean
clean :
	rm smartptr  $(objects)