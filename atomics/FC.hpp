/*
* S M Abu Adnan Abir
*
* Atomic model
* FC=Final Check Up:
*/


#ifndef FC_HPP
#define FC_HPP

//Include simulator headers
#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>


//Include other headers needed for the C++ implementation of the model
#include <iostream>
#include <math.h>
#include <assert.h>
#include <string>
#include <random>
#include <list>
#include <cmath>


//Include the relative path to the message types
#include "../data_structures/message.hpp"
using namespace cadmium;
using namespace std;


//Port definition
struct FC_defs{
		struct FCout1 : public out_port<int> {};
		struct FCout2 : public out_port<int> {};
		struct FCin1 : public in_port<int> {};
		struct FCin2 : public in_port<int> {};
		struct FCin3 : public in_port<int> {};
		

	};


//Atomic model class
template<typename TIME> class FC {
	public:


//Ports definition
	using input_ports = tuple<typename FC_defs:: FCin1,
				typename FC_defs:: FCin2,
				typename FC_defs:: FCin3>;
	using output_ports = tuple<typename FC_defs:: FCout1,
		typename FC_defs:: FCout2>;
		


//Model parameters to be overwritten during instantiation
	struct state_type {
			int ID;
			bool FCbusy;
			int N501; 
			int N502;
			int N503; 
			int N504;
			int N505; 
			int N506;
			int N507; 
			int N508;

//Declare the state variables here
};
		state_type state;


//Default constructor without parameters
	FC () noexcept{

		state.FCbusy = false;
		state.N501 = 0;
		state.N502 = 0;
		state.N503 = 0;
		state.N504 = 0;
		state.N505 = 0;
		state.N506 = 0;
		state.N507 = 0;
		state.N508 = 0;
		

//Define the default constructor here
		}


//Constructor with parameters if needed


	void internal_transition() {
			state.FCbusy = false;
//Define internal transition here
		}


	void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){

	if((get_messages<typename FC_defs::FCin1>(mbs).size())>1) {
						assert(false && "Accumulator (external): there is more message in the bag");
                }		

	vector<int> bag_port_in;
	for(const auto &x : get_messages<typename FC_defs::FCin1>(mbs)){
						if(state.FCbusy == false){
						bag_port_in=get_messages<typename FC_defs::FCin1>(mbs);
						state.ID = bag_port_in[0];
						state.FCbusy = true;
						}
					}
	for(const auto &x : get_messages<typename FC_defs::FCin2>(mbs)){
					state.FCbusy = false;
					state.N501 ++;
					if (state.ID%10==1) {
						state.N503 ++;
						}
					else if (state.ID%10==2) {
							state.N504 ++;
						}
					else if (state.ID%10==3) {
							state.N505 ++;
						}
					
					}	
	for(const auto &x : get_messages<typename FC_defs::FCin3>(mbs)){
					state.FCbusy = false;
					state.N502 ++;
					if (state.ID%10==1) {
						state.N506 ++;
						}
						else if (state.ID%10==2) {
						state.N507 ++;
						}
						else if (state.ID%10==3) {
						state.N508 ++;
						}

					}
	


//Define external transition here
	}
void confluence_transition(TIME e,typename make_message_bags<input_ports>::type mbs){
//Define confluence transition here
//Default definition
internal_transition();
external_transition(TIME(), std::move(mbs));
}


typename make_message_bags<output_ports>::type output() const {
typename make_message_bags<output_ports>::type bags;
if (state.FCbusy == true)
	{if ((double)rand() / (double) RAND_MAX  < 0.95) {
		vector<int> bag_port_out;
		bag_port_out.push_back(state.ID);
		get_messages<typename FC_defs::FCout1>(bags)=bag_port_out;
		
    }
	else {
		vector<int> bag_port_out;
		bag_port_out.push_back(state.ID);
		get_messages<typename FC_defs::FCout2>(bags)=bag_port_out;
		
    }
	}
		//Define output function here
	return bags;
}



TIME time_advance() const {
TIME next_internal;
        if (state.FCbusy) {
            next_internal = TIME("00:0:10:000");
        }else {
            next_internal = numeric_limits<TIME>::infinity();
        }
        return next_internal;
    }

//Define time advance function here

friend ostringstream& operator<<(ostringstream& os, const typename FC<TIME>::state_type& i) {
	os << "Person went home: " << i.N501 << " (Oxford-AstraZeneca= " << i.N503 << ", Moderna= " << i.N504 << ", Pfizer= " << i.N505 << ") Person admitted to hospital: " << i.N502 << " (Oxford-AstraZeneca= " << i.N506 << ", Moderna= " << i.N507 << ", Pfizer= " << i.N508 << ") & Last ID served: " << i.ID << endl;
        //Define how to log the state here
return os;
}
};
#endif //FC_HPP
