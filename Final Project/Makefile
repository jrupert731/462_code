LIBS = `pkg-config opencv4 --libs`
CFLAGS = `pkg-config opencv4 --cflags`

objects = *.o
binaries = compressor comparator nanpatcher

#TODO- Finish compressor, write decompressor

all: compressor comparator nanpatcher clean_objects

compressor: compressor_main.o compressor_decompressor.o
	g++ compressor_main.o compressor_decompressor.o $(CFLAGS) $(LIBS) -o compressor -g

comparator: comparator_main.o error_calc_funcs.o
	g++ comparator_main.o error_calc_funcs.o $(CFLAGS) $(LIBS) -o comparator -g

nanpatcher: nan_patcher.cpp
	g++ nan_patcher.cpp -o nanpatcher $(CFLAGS) $(LIBS) -g

compressor_main.o: compressor_main.cpp
	g++ -c compressor_main.cpp $(CFLAGS) $(LIBS) -g

compressor_decompressor.o: headers/compressor_decompressor.cpp
	g++ -c headers/compressor_decompressor.cpp $(CFLAGS) $(LIBS) -g

comparator_main.o: comparator_main.cpp
	g++ -c comparator_main.cpp $(CFLAGS) $(LIBS) -g

error_calc_funcs.o: headers/error_calc_funcs.cpp
	g++ -c headers/error_calc_funcs.cpp $(CFLAGS) $(LIBS) -g

clean_objects:
	rm -f $(objects)

clean_all:
	rm -f $(binaries) $(objects)