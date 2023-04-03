CC=g++
CFLAGS=-std=c++17

INCLUDECADMIUM=-I ../../cadmium/include
INCLUDEDESTIMES=-I ../../DESTimes/include

#CREATE BIN AND BUILD FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
results_folder := $(shell mkdir -p simulation_results)

#TARGET TO COMPILE ALL TEST 

Atomic_FC_test.o: test/Atomic_FC_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) test/Atomic_FC_test.cpp -o build/Atomic_FC_test.o

Vaccination_Centre_main_test.o: test/Vaccination_Centre_main_test.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDECADMIUM) $(INCLUDEDESTIMES) test/Vaccination_Centre_main_test.cpp -o build/Vaccination_Centre_main_test.o
	

tests: Atomic_FC_test.o Vaccination_Centre_main_test.o 
		
	$(CC) -g -o bin/Atomic_FC_test build/Atomic_FC_test.o 
	
	$(CC) -g -o bin/Vaccination_Centre_main_test build/Vaccination_Centre_main_test.o
	
#TARGET TO COMPILE EVERYTHING
all: tests

#CLEAN COMMANDS
clean:
	rm -f bin/* build/*
