/*
* S M Abu Adnan Abir
*
* Atomic model
* OB=Observation room:
*/


#ifndef OB_HPP
#define OB_HPP

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
struct OB_defs{
struct OBout1 : public out_port<int> {};
struct OBin1 : public in_port<int> {};
struct OBin2 : public in_port<int> {};
struct OBin3 : public in_port<int> {};
struct OBin4 : public in_port<int> {};
struct OBin5 : public in_port<int> {};
struct OBin6 : public in_port<int> {};
};


//Atomic model class
template<typename TIME> class OB {
public:


//Ports definition
using input_ports = tuple<typename OB_defs:: OBin1,
typename OB_defs:: OBin2,
typename OB_defs:: OBin3,
typename OB_defs:: OBin4,
typename OB_defs:: OBin5,
typename OB_defs:: OBin6 >;
using output_ports = tuple<typename OB_defs:: OBout1>;


//Model parameters to be overwritten during instantiation
struct state_type{
	int ID;
	bool queuefull;
	bool queuenull;
	bool FCbusy;
	bool OBactive;
	int OBsize;
	int N600;
	TIME next_internal;

//Declare the state variables here
};
state_type state;


//Default constructor without parameters
OB () noexcept{
	state.queuefull = false;
	state.queuenull = true;
	state.FCbusy = false;
	state.OBactive = false;
	state.OBsize = 3000;
	state.N600 = 0;


//Define the default constructor here
}


//Constructor with parameters if needed


void internal_transition() {
	state.OBactive = false;
//Define internal transition here
}


void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){

	if((get_messages<typename OB_defs::OBin1>(mbs).size()+get_messages<typename OB_defs::OBin2>(mbs).size()+get_messages<typename OB_defs::OBin3>(mbs).size()+get_messages<typename OB_defs::OBin4>(mbs).size()+get_messages<typename OB_defs::OBin5>(mbs).size()+get_messages<typename OB_defs::OBin6>(mbs).size())>6){
                    assert(false && "Accumulator (external): there is more message in the bag");
                }

	vector<int> bag_port_in;
	for(const auto &x : get_messages<typename OB_defs::OBin1>(mbs)){
	
	
				if (!(state.N600 < state.OBsize)) {
					state.queuefull = true;
					}
	else{
	bag_port_in=get_messages<typename OB_defs::OBin1>(mbs);
	state.ID = bag_port_in[0];
            state.N600 ++;
            state.OBactive = true;
      }}

	for(const auto &x : get_messages<typename OB_defs::OBin2>(mbs)){
	
	
                     if (!(state.N600 < state.OBsize)) {
					state.queuefull = true;
					}
	else{
	bag_port_in=get_messages<typename OB_defs::OBin2>(mbs);
	state.ID = bag_port_in[0];
            state.N600 ++;
	state.OBactive = true;

      }
   }
			
for(const auto &x : get_messages<typename OB_defs::OBin3>(mbs)){
	
	
                     if (!(state.N600 < state.OBsize)) {
					state.queuefull = true;
					}
	else{
	bag_port_in=get_messages<typename OB_defs::OBin3>(mbs);
	state.ID = bag_port_in[0];
            state.N600 ++;
	state.OBactive = true;

      }
   }
			
	for(const auto &x : get_messages<typename OB_defs::OBin4>(mbs)){
	state.FCbusy = true;
    state.N600 --;
	if (!(state.N600==0)) {
            state.OBactive = true;
					}
	else{
    state.queuenull = true;
    state.OBactive = false;
      }
   }
	for(const auto &x : get_messages<typename OB_defs::OBin5>(mbs)){
	state.FCbusy = false;

      }

	for(const auto &x : get_messages<typename OB_defs::OBin6>(mbs)){{
	state.FCbusy = false;

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
	if (state.FCbusy==false && (state.N600!=0)) {
	vector<int> bag_port_out;

	bag_port_out.push_back(state.ID);
	get_messages<typename OB_defs::OBout1>(bags)=bag_port_out;
            }
//Define output function here
return bags;
}


TIME time_advance() const {
TIME next_internal;
        if ((state.OBactive)||(state.N600!=0)) {
            next_internal = TIME("00:00:01:000");
        }else {
            next_internal = numeric_limits<TIME>::infinity();
        }
        return next_internal;
    }

//Define time advance function here

friend ostringstream& operator << (ostringstream& os, const typename OB<TIME>::state_type& i) {
	os << "Current queue Size: " << i.N600 << " & Last ID served: " << i.ID << endl;
        //Define how to log the state here
return os;
}
};
#endif //OB_HPP
