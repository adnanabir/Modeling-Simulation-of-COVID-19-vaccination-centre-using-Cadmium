/*
* S M Abu Adnan Abir
*
* Atomic model
* VW=Vaccination area waiting room:
*/


#ifndef VW_HPP
#define VW_HPP

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
struct VW_defs{
				struct VWout1 : public out_port<int> {};
				struct VWin1 : public in_port<int> {};
				struct VWin2 : public in_port<int> {};
				struct VWin3 : public in_port<int> {};
				struct VWin4 : public in_port<int> {};
				struct VWin5 : public in_port<int> {};

};


//Atomic model class
template<typename TIME> class VW {
public:


//Ports definition
		using input_ports = tuple<typename VW_defs:: VWin1,
								typename VW_defs:: VWin2,
								typename VW_defs:: VWin3,
								typename VW_defs:: VWin4,
								typename VW_defs:: VWin5>;
		using output_ports = tuple<typename VW_defs:: VWout1>;

//Model parameters to be overwritten during instantiation
struct state_type{
					int ID;
					bool queuefull;
					bool queuenull;
					bool VHbusy;
					bool VWactive;
					int VWareasize;
					int N10;
					TIME next_internal;

//Declare the state variables here
					};
					state_type state;


//Default constructor without parameters
VW () noexcept{
				state.queuefull = false;
				state.queuenull = true;
				state.VHbusy = false;
				state.VWactive = false;
				state.VWareasize = 2000;
				state.N10 = 0;
				

//Define the default constructor here
				}


//Constructor with parameters if needed


void internal_transition() {
	state.VWactive = false;
//Define internal transition here
}


void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){

	if((get_messages<typename VW_defs::VWin1>(mbs).size()+get_messages<typename VW_defs::VWin2>(mbs).size()+get_messages<typename VW_defs::VWin3>(mbs).size()+get_messages<typename VW_defs::VWin4>(mbs).size()+get_messages<typename VW_defs::VWin5>(mbs).size())>5){
                    assert(false && "Accumulator (external): there is more  message in the bag");
                }

	vector<int> bag_port_in;
	for(const auto &x : get_messages<typename VW_defs::VWin1>(mbs)){
	
	if (!(state.N10 < state.VWareasize)) {
					state.queuefull = true;
					}
	else{
		bag_port_in=get_messages<typename VW_defs::VWin1>(mbs);	
		state.ID = bag_port_in[0];
            state.N10 ++;
			state.VWactive = true;
        }
	}
	for(const auto &x : get_messages<typename VW_defs::VWin2>(mbs)){
					state.VHbusy = true;
					state.N10 --;
		if (!(state.N10==0)) {
            		state.VWactive = true;
					}
		else{
    			state.queuenull = true;
    			state.VWactive = false;
      }
		}
	for(const auto &x : get_messages<typename VW_defs::VWin3>(mbs)){
	state.VHbusy = false;
        }
		for(const auto &x : get_messages<typename VW_defs::VWin4>(mbs)){
	state.VHbusy = false;
        }
		for(const auto &x : get_messages<typename VW_defs::VWin5>(mbs)){
	state.VHbusy = false;
        }
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
	if (state.VHbusy==false && (state.N10!=0)) {
	vector<int> bag_port_out;

	bag_port_out.push_back(state.ID);
	get_messages<typename VW_defs::VWout1>(bags)=bag_port_out;
            }
//Define output function here
return bags;
}


TIME time_advance() const {
TIME next_internal;
        if ((state.VWactive)||(state.N10!=0)) {
            next_internal = TIME("00:0:01:000");
        }else {
            next_internal = numeric_limits<TIME>::infinity();
        }
        return next_internal;
    }

//Define time advance function here

friend ostringstream& operator<<(ostringstream& os, const typename VW<TIME>::state_type& i) {
	os << "Current Queue Size: " << i.N10 << " & Last served ID: " << i.ID << endl;
        //Define how to log the state here
return os;
}
};
#endif //VW_HPP
