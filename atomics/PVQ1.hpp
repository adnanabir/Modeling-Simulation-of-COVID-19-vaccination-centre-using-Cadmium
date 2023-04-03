/*
* S M Abu Adnan Abir
*
* Atomic model
* PVQ1=Pre-Vaccination Queue 1:
*/


#ifndef PVQ1_HPP
#define PVQ1_HPP

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
struct PVQ1_defs{
struct PVQ1out1 : public out_port<int> {};
struct PVQ1in1 : public in_port<int> {};
struct PVQ1in2 : public in_port<int> {};
struct PVQ1in3 : public in_port<int> {};

};


//Atomic model class
template<typename TIME> class PVQ1 {
public:


//Ports definition
using input_ports = tuple<typename PVQ1_defs:: PVQ1in1,
typename PVQ1_defs:: PVQ1in2,
typename PVQ1_defs:: PVQ1in3>;
using output_ports = tuple<typename PVQ1_defs:: PVQ1out1>;

//Model parameters to be overwritten during instantiation
struct state_type{
	int ID;
	bool queuefull;
	bool queuenull;
	bool VP1busy;
	bool PVQ1active;
	int PVQ1size;
	int N104;

//Declare the state variables here
};
state_type state;


//Default constructor without parameters
PVQ1 () noexcept{
	state.queuefull = false;
	state.queuenull = true;
	state.VP1busy = false;
	state.PVQ1active = false;
	state.N104 = 0;
	state.PVQ1size = 600;


//Define the default constructor here
}


//Constructor with parameters if needed


void internal_transition() {
	state.PVQ1active = false;
//Define internal transition here
}


void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){

	if((get_messages<typename PVQ1_defs::PVQ1in1>(mbs).size()+get_messages<typename PVQ1_defs::PVQ1in2>(mbs).size()+get_messages<typename PVQ1_defs::PVQ1in3>(mbs).size())>3){
                    assert(false && "Accumulator (external): there is more message in the bag");
                }

	vector<int> bag_port_in;
	for(const auto &x : get_messages<typename PVQ1_defs::PVQ1in1>(mbs)){
	if(state.PVQ1active == false)
	bag_port_in=get_messages<typename PVQ1_defs::PVQ1in1>(mbs);
				if (!(state.N104 < state.PVQ1size)) {
					state.queuefull = true;
					}
	else{
	state.ID = bag_port_in[0];
            state.N104 ++;
	state.PVQ1active = true;
        }
	}
	for(const auto &x : get_messages<typename PVQ1_defs::PVQ1in2>(mbs)){
	state.VP1busy = true;
	state.N104 --;
		}
	for(const auto &x : get_messages<typename PVQ1_defs::PVQ1in3>(mbs))
	state.VP1busy = false;
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
	if ((state.VP1busy==false) && (state.N104!=0)) {
	vector<int> bag_port_out;

	bag_port_out.push_back(state.ID);
	get_messages<typename PVQ1_defs::PVQ1out1>(bags)=bag_port_out;
            }
//Define output function here
return bags;
}


TIME time_advance() const {
TIME next_internal;
        if ((state.PVQ1active==true)||(state.N104!=0)) {
            next_internal = TIME("00:00:01:000");
        }else {
            next_internal = numeric_limits<TIME>::infinity();
        }
        return next_internal;
    }

//Define time advance function here

friend ostringstream& operator<<(ostringstream& os, const typename PVQ1<TIME>::state_type& i) {
	os << "Current Queue Size of Oxford-AstraZeneca: " << i.N104 << " & Last served ID: " << i.ID << endl;
        //Define how to log the state here
return os;
}
};
#endif //PVQ1_HPP
