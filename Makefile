GCC := gcc
LIB := -lcurl
TARGET := download
OBJECTS := download.o

download.o : download.c
	$(GCC) -c download.c
all : $(OBJECTS)
	$(GCC) $(OBJECTS) -o $(TARGET) $(LIB)

clean :
	rm -f *.o;
	rm -f download
