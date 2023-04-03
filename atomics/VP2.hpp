/*
* S M Abu Adnan Abir
*
* Atomic model
* VP2=Vaccination pushing counter2:
*/


#ifndef VP2_HPP
#define VP2_HPP

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
#include <cstdlib>
#include <ctime>
#include <cmath>

//Include the relative path to the message types
#include "../data_structures/message.hpp"
using namespace cadmium;
using namespace std;


//Port definition
struct VP2_defs{
			struct VP2out1 : public out_port<int> {};
			struct VP2in1 : public in_port<int> {};
			struct VP2in2 : public in_port<int> {};
			};


//Atomic model class
template<typename TIME> 
		class VP2{
		public:


//Ports definition
		using input_ports = tuple<typename VP2_defs:: VP2in1,
					typename VP2_defs:: VP2in2>;
		using output_ports = tuple<typename VP2_defs:: VP2out1>;


//Model parameters to be overwritten during instantiation
	struct state_type{
					int ID;
					bool VP2busy;
					int N122;
	

//Declare the state variables here
					};
			state_type state;


//Default constructor without parameters
	VP2 () noexcept{
					state.VP2busy = false;
					state.N122=0;
//Define the default constructor here
}


//Constructor with parameters if needed


void internal_transition() {
					state.VP2busy = false;
//Define internal transition here
						}


void external_transition(TIME e, typename make_message_bags<input_ports>::type (mbs)){

	if((get_messages<typename VP2_defs::VP2in1>(mbs).size()+get_messages<typename VP2_defs::VP2in2>(mbs).size())>2){
                    assert(false && "Accumulator (external): there is more than one message in the bag");
                }

	vector<int> bag_port_in;
	for(const auto &x : get_messages<typename VP2_defs::VP2in1>(mbs)){
	if(state.VP2busy == false){
		bag_port_in=get_messages<typename VP2_defs::VP2in1>(mbs);
		state.ID = bag_port_in[0];
        state.VP2busy = true;
		state.N122++;

      }
	for(const auto &x : get_messages<typename VP2_defs::VP2in2>(mbs)){
					state.VP2busy = false;
					}


	}
//Define external transition here
}
void confluence_transition(TIME e,typename make_message_bags<input_ports>::type (mbs)){
//Define confluence transition here
//Default definition
internal_transition();
external_transition(TIME(), std::move(mbs));
}


typename make_message_bags<output_ports>::type output() const {
typename make_message_bags<output_ports>::type bags;
	if (state.VP2busy == true) {
	vector<int> bag_port_out;
	bag_port_out.push_back(state.ID);
	get_messages<typename VP2_defs::VP2out1>(bags)=bag_port_out;
            }

//Define output function here
return bags;
}


TIME time_advance() const {
TIME next_internal;
        if ((state.VP2busy)==true) {
            next_internal = TIME("00:00:10:000");
        }else {
            next_internal = numeric_limits<TIME>::infinity();
        }
        return next_internal;
    }

//Define time advance function here

friend ostringstream& operator<<(ostringstream& os, const typename VP2<TIME>::state_type& i) {
	os << "Person completed Vaccination with Moderna: " << i.N122<< " Last served ID: " << i.ID << endl;
        //Define how to log the state here
return os;
}
};
#endif //VP2_HPP
