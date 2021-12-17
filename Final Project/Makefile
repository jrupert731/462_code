LIBS = `pkg-config opencv4 --libs`
CFLAGS = `pkg-config opencv4 --cflags`

objects = *.o
binaries = compressor comparator decompressor nanpatcher

#TODO- Finish compressor, write decompressor

all: compressor comparator decompressor nanpatcher clean_objects

decompressor: decompressor_main.o compressor_decompressor.o
	g++ decompressor_main.o compressor_decompressor.o $(CFLAGS) $(LIBS) -o decompressor -g -fpermissive

compressor: compressor_main.o compressor_decompressor.o
	g++ compressor_main.o compressor_decompressor.o $(CFLAGS) $(LIBS) -o compressor -g -fpermissive

comparator: comparator_main.o error_calc_funcs.o
	g++ comparator_main.o error_calc_funcs.o $(CFLAGS) $(LIBS) -o comparator -g -fpermissive

nanpatcher: mains/nan_patcher.cpp
	g++ mains/nan_patcher.cpp -o nanpatcher $(CFLAGS) $(LIBS) -g -fpermissive

compressor_main.o: mains/compressor_main.cpp
	g++ -c mains/compressor_main.cpp $(CFLAGS) $(LIBS) -g -fpermissive

decompressor_main.o: mains/decompressor_main.cpp
	g++ -c mains/decompressor_main.cpp $(CFLAGS) $(LIBS) -g -fpermissive

compressor_decompressor.o: headers/compressor_decompressor.cpp
	g++ -c headers/compressor_decompressor.cpp $(CFLAGS) $(LIBS) -g -fpermissive

comparator_main.o: mains/comparator_main.cpp
	g++ -c mains/comparator_main.cpp $(CFLAGS) $(LIBS) -g -fpermissive

error_calc_funcs.o: headers/error_calc_funcs.cpp
	g++ -c headers/error_calc_funcs.cpp $(CFLAGS) $(LIBS) -g -fpermissive

clean_objects:
	rm -f $(objects)

clean_all:
	rm -f $(binaries) $(objects)