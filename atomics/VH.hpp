/*
* S M Abu Adnan Abir
*
* Atomic model
* VH=Vaccination area help desk:
*/


#ifndef VH_HPP
#define VH_HPP

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
struct VH_defs{
		struct VHout1 : public out_port<int> {};
		struct VHout2 : public out_port<int> {};
		struct VHout3 : public out_port<int> {};
		struct VHin1 : public in_port<int> {};
		struct VHin2 : public in_port<int> {};
		struct VHin3 : public in_port<int> {};
		struct VHin4 : public in_port<int> {};
		struct VHin5 : public in_port<int> {};
		struct VHin6 : public in_port<int> {};
		struct VHin7 : public in_port<int> {};

	};


//Atomic model class
template<typename TIME> class VH {
	public:


//Ports definition
	using input_ports = tuple<typename VH_defs:: VHin1,
		typename VH_defs:: VHin2,
		typename VH_defs:: VHin3,
		typename VH_defs:: VHin4,
		typename VH_defs:: VHin5,
		typename VH_defs:: VHin6,
		typename VH_defs:: VHin7 >;
	using output_ports = tuple<typename VH_defs:: VHout1,
		typename VH_defs:: VHout2,
		typename VH_defs:: VHout3>;
		


//Model parameters to be overwritten during instantiation
	struct state_type {
			int ID;
			bool VHbusy;
			int N101; 
			int N102;
			int N103;
			int N111; 
			int N112;
			int N113;

//Declare the state variables here
};
		state_type state;


//Default constructor without parameters
	VH () noexcept{

		state.VHbusy = false;
		state.N101 = 0;
		state.N102 = 0;
		state.N103 = 0;
		state.N111 = 0;
		state.N112 = 0;
		state.N113 = 0;

//Define the default constructor here
		}


//Constructor with parameters if needed


	void internal_transition() {
			state.VHbusy = false;
//Define internal transition here
		}


	void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){

	if((get_messages<typename VH_defs::VHin1>(mbs).size()+get_messages<typename VH_defs::VHin2>(mbs).size()+get_messages<typename VH_defs::VHin3>(mbs).size()+get_messages<typename VH_defs::VHin4>(mbs).size()+get_messages<typename VH_defs::VHin5>(mbs).size()+get_messages<typename VH_defs::VHin6>(mbs).size()+get_messages<typename VH_defs::VHin7>(mbs).size())>7) {
						assert(false && "Accumulator (external): there is more message in the bag");
                }		

	vector<int> bag_port_in;
	for(const auto &x : get_messages<typename VH_defs::VHin1>(mbs)){
						if(state.VHbusy == false){
						bag_port_in=get_messages<typename VH_defs::VHin1>(mbs);
						state.ID = bag_port_in[0];
						state.VHbusy = true;
						}
					}
	for(const auto &x : get_messages<typename VH_defs::VHin2>(mbs)){
					state.VHbusy = false;
					state.N101 ++;
					state.N111 ++;
					}	
	for(const auto &x : get_messages<typename VH_defs::VHin3>(mbs)){
					state.VHbusy = false;
					state.N102 ++;
					state.N112 ++;

					}
	for(const auto &x : get_messages<typename VH_defs::VHin4>(mbs)){
					state.VHbusy = false;
					state.N103 ++;
					state.N113 ++;

					}
	for(const auto &x : get_messages<typename VH_defs::VHin5>(mbs)){
					state.N111 --;
					}
	for(const auto &x : get_messages<typename VH_defs::VHin6>(mbs)){
					state.N112 --;
					}
	for(const auto &x : get_messages<typename VH_defs::VHin7>(mbs)){
					state.N113 --;
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
	if ((state.ID%10==1) && (state.N111<600)) {
		vector<int> bag_port_out;
		bag_port_out.push_back(state.ID);
		get_messages<typename VH_defs::VHout1>(bags)=bag_port_out;
    }
	else if ((state.ID%10==2) && (state.N112<600)) {
		vector<int> bag_port_out;
		bag_port_out.push_back(state.ID);
		get_messages<typename VH_defs::VHout2>(bags)=bag_port_out;
    }
	else if ((state.ID%10==3) && (state.N113<600)) {
		vector<int> bag_port_out;
		bag_port_out.push_back(state.ID);
		get_messages<typename VH_defs::VHout3>(bags)=bag_port_out;
    }
		//Define output function here
	return bags;
}


TIME time_advance() const {
TIME next_internal;
        if (state.VHbusy) {
            next_internal = TIME("00:00:10:000");
        }else {
            next_internal = numeric_limits<TIME>::infinity();
        }
        return next_internal;
    }

//Define time advance function here

friend ostringstream& operator<<(ostringstream& os, const typename VH<TIME>::state_type& i) {
	os << "Person with Oxford-AstraZeneca: " << i.N101 << "  Person with Moderna: " << i.N102<< "   Person with Pfizer: " << i.N103 << endl;
        //Define how to log the state here
return os;
}
};
#endif //VH_HPP
