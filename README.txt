This folder contains the VCSM model implemented in Cadmium

/**************************/
/****FILES ORGANIZATION****/
/**************************/

README.txt	
Modeling & Simulation of COVID-19 vaccination centre using Cadmium_Project.pdf
DEVSmodelsForm_VCSM.doc
Modeling & Simulation of COVID-19 vaccination centre using Cadmium_Project.xml
Modeling & Simulation of COVID-19 vaccination centre using Cadmium_Project.ppt
makefile

atomics [This folder contains atomic models implemented in Cadmium]
	RD.hpp
	RDQ.hpp
	RGD.hpp
	RGDQ.hpp
	VW.hpp
	VH.hpp
	PVQ1.hpp
	PVQ2.hpp
	PVQ3.hpp
	VP1.hpp
	VP2.hpp
	VP3.hpp
	OB.hpp
	FC.hpp
	
bin [This folder will be created automatically the first time you compile the poject.
	 It will contain all the executables]
	 
build [This folder will be created automatically the first time you compile the poject.
       It will contain all the build files (.o) generated during compilation]


data_structures [This folder contains message data structure, but it isn't used in the model]
	message.hpp
	message.cpp
	
	
input_data [This folder contains all the input data to run the tests]
	input_FC_01.txt
	input_VC_main_01.txt
	
	
	
simulation_results [This folder will be created automatically the first time you compile the poject.
                    It will store the outputs from your simulations and tests]

test [This folder contains tests of atomic models and coupled models]
	Atomic_FC_test.cpp
	Vaccination_Centre_main_test.cpp
	
top_model [This folder contains the VCSM top model]	
	Vaccination_Centre_main.cpp
	
/*************/
/****STEPS****/
/*************/

0 - Modeling & Simulation of COVID-19 vaccination centre using Cadmium.pdf contains the explanation of this model

1 - Compile the project and the tests
	1 - Open the terminal (Ubuntu terminal for Linux and Cygwin for Windows) in the VCSM_cadmium folder
	2 - To compile the project and the tests, type in the terminal:
			make clean; make all
			
2 - Run Station Arrival Generator test
	1 - Open the terminal in the bin folder. 
	2 - To run the test, type in:
			./"test file name" (or ./"test file name".exe for Windows)
		OR
			select the executable test file "test file name".exe from the bin folder
	3 - To check the output of the test, go to the folder simulation_results and open:
			""test file name"_output_messages.txt" and ""test file name"_output_state.txt"
	
	
3 - Run step 3 for the atomic tests.
	The output and state logs can be found in simulation_results with the same naming convention shown in step 3
	Atomic model test logs will have the prefix of the ATOMIC model name
	Select executable tests from bin folder or in terminal type:
	./Atomic_FC_test
	
	

			
4 - Run the top model
	1 - Open the terminal (Ubuntu terminal for Linux and Cygwin for Windows) in the bin folder.
	2 - To run the test, type in:
			./Vaccination_Centre_main_test (or ./Vaccination_Centre_main_test.exe for Windows)
		OR
			select te executable main simulation file Vaccination_Centre_main_test.exe from the bin folder
	3 - To check the output of the model, go to the folder simulation_results and open:
			"Top_output_messages.txt" 
			"Top_output_state.txt"
	