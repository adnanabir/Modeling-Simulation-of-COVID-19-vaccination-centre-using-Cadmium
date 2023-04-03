/*
* S M Abu Adnan Abir
*
* Atomic model
* RGDQ=Registration desk Queue:
*/


#ifndef RGDQ_HPP
#define RGDQ_HPP

//Include simulator headers
#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>


//Include other headers needed for the C++ implementation of the model
#include <limits>
#include <math.h>
#include <assert.h>
#include <string>
#include <random>
#include <list>


//Include the relative path to the message types
#include "../data_structures/message.hpp"
using namespace cadmium;
using namespace std;


//Port definition
struct RGDQ_defs{
struct RGDQout1 : public out_port<int> {};
struct RGDQin1 : public in_port<int> {};
struct RGDQin2 : public in_port<int> {};
struct RGDQin3 : public in_port<int> {};

};


//Atomic model class
template<typename TIME> class RGDQ {
public:


//Ports definition
using input_ports = tuple<typename RGDQ_defs:: RGDQin1,
typename RGDQ_defs:: RGDQin2,
typename RGDQ_defs:: RGDQin3>;
using output_ports = tuple<typename RGDQ_defs:: RGDQout1>;

//Model parameters to be overwritten during instantiation
struct state_type{
	int ID;
	bool queuefull;
	bool queuenull;
	bool RGDbusy;
	bool RGDQactive;
	int RGDqueuesize;
	int N4;

//Declare the state variables here
};
state_type state;


//Default constructor without parameters
RGDQ () noexcept{
	state.queuefull = false;
	state.queuenull = true;
	state.RGDbusy = false;
	state.RGDQactive = false;
	state.N4 = 0;
	state.RGDqueuesize = 1200;


//Define the default constructor here
}


//Constructor with parameters if needed


void internal_transition() {
	state.RGDQactive = false;
//Define internal transition here
}


void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){

	if((get_messages<typename RGDQ_defs::RGDQin1>(mbs).size()+get_messages<typename RGDQ_defs::RGDQin2>(mbs).size()+get_messages<typename RGDQ_defs::RGDQin3>(mbs).size())>3){
                    assert(false && "Accumulator (external): there is more message in the bag");
                }

	vector<int> bag_port_in;
	for(const auto &x : get_messages<typename RGDQ_defs::RGDQin1>(mbs)){
	if(state.RGDQactive == false)
	bag_port_in=get_messages<typename RGDQ_defs::RGDQin1>(mbs);
				if (!(state.N4 < state.RGDqueuesize)) {
					state.queuefull = true;
					}
	else{
	state.ID = bag_port_in[0];
            state.N4 ++;
	state.RGDQactive = true;
        }
	}
	for(const auto &x : get_messages<typename RGDQ_defs::RGDQin2>(mbs)){
	state.RGDbusy = true;
	state.N4 --;
		}
	for(const auto &x : get_messages<typename RGDQ_defs::RGDQin3>(mbs))
	state.RGDbusy = false;
        }



//Define external transition here

void confluence_transition(TIME e,typename make_message_bags<input_ports>::type (mbs)){
//Define confluence transition here
//Default definition
internal_transition();
external_transition(TIME(), std::move(mbs));
}


typename make_message_bags<output_ports>::type output() const {
typename make_message_bags<output_ports>::type bags;
	if ((state.RGDbusy==false) && (state.N4!=0)) {
	vector<int> bag_port_out;

	bag_port_out.push_back(state.ID);
	get_messages<typename RGDQ_defs::RGDQout1>(bags)=bag_port_out;
            }
//Define output function here
return bags;
}


TIME time_advance() const {
TIME next_internal;
        if ((state.RGDQactive==true)||(state.N4!=0)) {
            next_internal = TIME("00:00:01:000");
        }else {
            next_internal = numeric_limits<TIME>::infinity();
        }
        return next_internal;
    }

//Define time advance function here

friend ostringstream& operator<<(ostringstream& os, const typename RGDQ<TIME>::state_type& i) {
	os << "Current Queue Size: " << i.N4 << " & Last served ID: " << i.ID << endl;
        //Define how to log the state here
return os;
}
};
#endif //RGDQ_HPP
