CPP=g++

CPPFLAGS=-std=c++0x -c -g3 #-Wall -Wno-sign-compare
CPPFLAGS2=-std=c++0x -g3  #-Wall -Wno-sign-compare
LIBCDS=../libcds
OBJECTS_DIR=objects/
LIB=lib/all_lib.a
INCLUDES_LIBCDS=-I$(LIBCDS)/includes/
INCLUDES_TREES=-I../trees/*.h
SRC_LIBCDS=../libcds/src/static/sequence/*.cpp ../libcds/src/static/bitsequence/*.cpp ../libcds/src/static/mapper/*.cpp ../libcds/src/static/coders/*.cpp ../libcds/src/static/permutation/*.cpp ../libcds/src/utils/*.cpp ../libcds/src/static/textindex/*.cpp ../libcds/src/static/suffixtree/*.cpp 
INCLUDES=-I. -I../trees/ -I$(LIBCDS)/includes/ 
SRC_TREES= ../trees/*.cpp
SRC_RMQ=rmq.cpp

code:
	$(CPP) $(CPPFLAGS2) $(INCLUDES) test_wt.cpp -o test_wt lib/all_lib.a
program:
	$(CPP) $(CPPFLAGS2) $(INCLUDES) main.cpp -o main lib/all_lib.a
libcds:
	rm -rf lib/libcds.a
	$(CPP) $(CPPFLAGS) $(INCLUDES_LIBCDS) $(SRC_LIBCDS)
	mv *.o objects/
	ar -rcs lib/libcds.a objects/*.o
	rm -rf objects/*.o
trees:
	rm -rf lib/libtrees.a
	$(CPP) $(CPPFLAGS) $(INCLUDES_TREES) $(SRC_TREES)
	mv *.o objects/
	ar -rcs lib/libtrees.a objects/*.o
	rm -rf objects/*.o

rmq:libcds trees
	$(CPP) $(CPPFLAGS) $(INCLUDES_LIBCDS) $(INCLUDES_TREES) $(SRC_RMQ) lib/libcds.a lib/libtrees.a

all: 
	rm -rf ../libcds/includes/*.h
	cp ../libcds/src/static/sequence/*.h ../libcds/includes/
	cp ../libcds/src/static/bitsequence/*.h ../libcds/includes/
	cp ../libcds/src/static/mapper/*.h ../libcds/includes/	
	cp ../libcds/src/static/coders/*.h ../libcds/includes/
	cp ../libcds/src/static/permutation/*.h ../libcds/includes/
	cp ../libcds/src/utils/*.h ../libcds/includes/
	cp ../libcds/src/static/suffixtree/*.h ../libcds/includes/
	cp ../libcds/src/static/textindex/*.h ../libcds/includes/
	$(CPP) $(CPPFLAGS) $(INCLUDES)   $(SRC_TREES) $(SRC_RMQ) $(SRC_LIBCDS)  
	rm -rf lib/all_lib.a
	ar -rcs lib/all_lib.a *.o
	rm -rf *.o
	$(CPP) $(CPPFLAGS2) $(INCLUDES) test_wt.cpp -o test_wt lib/all_lib.a
clean:
	rm -rf objects/*.o lib/*.a test  

