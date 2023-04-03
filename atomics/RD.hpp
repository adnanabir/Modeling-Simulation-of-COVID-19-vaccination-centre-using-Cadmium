/*
* S M Abu Adnan Abir
*
* Atomic model
* RD=Reception desk:
*/


#ifndef RD_HPP
#define RD_HPP

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
struct RD_defs{
		struct RDout1 : public out_port<int> {};
		struct RDout2 : public out_port<int> {};
		struct RDin1 : public in_port<int> {};
		struct RDin2 : public in_port<int> {};
		struct RDin3 : public in_port<int> {};
		struct RDin4 : public in_port<int> {};
		struct RDin5 : public in_port<int> {};

	};


//Atomic model class
template<typename TIME> class RD {
	public:


//Ports definition
	using input_ports = tuple<typename RD_defs:: RDin1,
		typename RD_defs:: RDin2,
		typename RD_defs:: RDin3,
		typename RD_defs:: RDin4,
		typename RD_defs:: RDin5 >;
	using output_ports = tuple<typename RD_defs:: RDout1,
		typename RD_defs:: RDout2>;
		


//Model parameters to be overwritten during instantiation
	struct state_type {
			int ID;
			bool RDbusy;
			int N2; 
			int N3;
			int N31;
			int N21;

//Declare the state variables here
};
		state_type state;


//Default constructor without parameters
	RD () noexcept{

		state.RDbusy = false;
		state.N2 = 0;
		state.N3 = 0;
		state.N21 = 0;
		state.N31 = 0;

//Define the default constructor here
		}


//Constructor with parameters if needed


	void internal_transition() {
			state.RDbusy = false;
//Define internal transition here
		}


	void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){

	if((get_messages<typename RD_defs::RDin1>(mbs).size()+get_messages<typename RD_defs::RDin2>(mbs).size()+get_messages<typename RD_defs::RDin3>(mbs).size()+get_messages<typename RD_defs::RDin4>(mbs).size()+get_messages<typename RD_defs::RDin5>(mbs).size())>5) {
						assert(false && "Accumulator (external): there is more message in the bag");
                }		

	vector<int> bag_port_in;
	for(const auto &x : get_messages<typename RD_defs::RDin1>(mbs)){
						if(state.RDbusy == false){
						bag_port_in=get_messages<typename RD_defs::RDin1>(mbs);
						state.ID = bag_port_in[0];
						state.RDbusy = true;
						}
					}
	for(const auto &x : get_messages<typename RD_defs::RDin2>(mbs)){
					state.RDbusy = false;
					state.N3 ++;
					state.N31 ++;
					}	
	for(const auto &x : get_messages<typename RD_defs::RDin3>(mbs)){
					state.RDbusy = false;
					state.N2 ++;
					state.N21 ++;

					}
	for(const auto &x : get_messages<typename RD_defs::RDin4>(mbs)){
					state.N3 --;
					}
	for(const auto &x : get_messages<typename RD_defs::RDin5>(mbs)){
					state.N2 --;
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
	if ((state.ID%10!=0) && (state.N2<2000)) {
		vector<int> bag_port_out;
		bag_port_out.push_back(state.ID);
		get_messages<typename RD_defs::RDout2>(bags)=bag_port_out;
    }
	else if ((state.ID%10==0) && (state.N3<1200)) {
		vector<int> bag_port_out;
		bag_port_out.push_back(state.ID);
		get_messages<typename RD_defs::RDout1>(bags)=bag_port_out;
    }
		//Define output function here
	return bags;
}


TIME time_advance() const {
TIME next_internal;
        if (state.RDbusy) {
            next_internal = TIME("00:00:10:000");
        }else {
            next_internal = numeric_limits<TIME>::infinity();
        }
        return next_internal;
    }

//Define time advance function here

friend ostringstream& operator<<(ostringstream& os, const typename RD<TIME>::state_type& i) {
	os << "Person with completed registration: " << i.N21 << "  Person without registration: " << i.N31<< "   & Last ID served: " << i.ID << endl;
        //Define how to log the state here
return os;
}
};
#endif //RD_HPP
