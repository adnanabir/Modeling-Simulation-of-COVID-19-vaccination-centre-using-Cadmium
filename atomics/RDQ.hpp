/*
* S M Abu Adnan Abir
*
* Atomic model
* RDQ=Reception desk Queue:
*/


#ifndef RDQ_HPP
#define RDQ_HPP

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
struct RDQ_defs{
struct RDQout1 : public out_port<int> {};
struct RDQin1 : public in_port<int> {};
struct RDQin2 : public in_port<int> {};
struct RDQin3 : public in_port<int> {};
struct RDQin4 : public in_port<int> {};
struct RDQin5 : public in_port<int> {};

};


//Atomic model class
template<typename TIME> class RDQ {
public:


//Ports definition
using input_ports = tuple<typename RDQ_defs:: RDQin1,
typename RDQ_defs:: RDQin2,
typename RDQ_defs:: RDQin3,
typename RDQ_defs:: RDQin4,
typename RDQ_defs:: RDQin5 >;
using output_ports = tuple<typename RDQ_defs:: RDQout1>;


//Model parameters to be overwritten during instantiation
struct state_type{
	int ID;
	bool queuefull;
	bool queuenull;
	bool RDbusy;
	bool RDQactive;
	int RDQsize;
	int N1;
	TIME next_internal;
	
	

//Declare the state variables here
};
state_type state;


//Default constructor without parameters
RDQ () noexcept{
	state.queuefull = false;
	state.queuenull = true;
	state.RDbusy = false;
	state.RDQactive = false;
	state.RDQsize = 1200;
	state.N1 = 0;


//Define the default constructor here
}


//Constructor with parameters if needed


void internal_transition() {
	state.RDQactive = false;
//Define internal transition here
}


void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){

	if((get_messages<typename RDQ_defs::RDQin1>(mbs).size()+get_messages<typename RDQ_defs::RDQin2>(mbs).size()+get_messages<typename RDQ_defs::RDQin3>(mbs).size()+get_messages<typename RDQ_defs::RDQin4>(mbs).size()+get_messages<typename RDQ_defs::RDQin5>(mbs).size())>5){
                    assert(false && "Accumulator (external): there is more message in the bag");
                }

	vector<int> bag_port_in;
	for(const auto &x : get_messages<typename RDQ_defs::RDQin1>(mbs)){
	
	if (!(state.N1 < state.RDQsize)) {
					state.queuefull = true;
					}
	else{
	bag_port_in=get_messages<typename RDQ_defs::RDQin1>(mbs);
	state.ID = bag_port_in[0];
            state.N1 ++;
            state.RDQactive = true;
      }}

	for(const auto &x : get_messages<typename RDQ_defs::RDQin2>(mbs)){
	
	if (!(state.N1 < state.RDQsize)) {
					state.queuefull = true;
					}
	else{
	bag_port_in=get_messages<typename RDQ_defs::RDQin2>(mbs);
	state.ID = bag_port_in[0];
            state.N1 ++;
	state.RDQactive = true;

      }
   }
			
	for(const auto &x : get_messages<typename RDQ_defs::RDQin3>(mbs)){
	state.RDbusy = true;
    state.N1 --;
	if (!(state.N1==0)) {
            state.RDQactive = true;
					}
	else{
    state.queuenull = true;
    state.RDQactive = false;
      }
   }
	for(const auto &x : get_messages<typename RDQ_defs::RDQin4>(mbs)){
	state.RDbusy = false;

      }

	for(const auto &x : get_messages<typename RDQ_defs::RDQin5>(mbs)){{
	state.RDbusy = false;

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
	if (state.RDbusy==false && (state.N1!=0)) {
	vector<int> bag_port_out;

	bag_port_out.push_back(state.ID);
	get_messages<typename RDQ_defs::RDQout1>(bags)=bag_port_out;
            }
//Define output function here
return bags;
}


TIME time_advance() const {
TIME next_internal;
        if ((state.RDQactive)||(state.N1!=0)) {
            next_internal = TIME("00:0:01:000");
        }else {
            next_internal = numeric_limits<TIME>::infinity();
        }
        return next_internal;
    }

//Define time advance function here

friend ostringstream& operator << (ostringstream& os, const typename RDQ<TIME>::state_type& i) {
	os << "Current queue Size: " << i.N1 << " & Last ID served: " << i.ID << endl;
        //Define how to log the state here
return os;
}
};
#endif //RDQ_HPP
