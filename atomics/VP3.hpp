/*
* S M Abu Adnan Abir
*
* Atomic model
* VP3=Vaccination pushing counter3:
*/


#ifndef VP3_HPP
#define VP3_HPP

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
struct VP3_defs{
			struct VP3out1 : public out_port<int> {};
			struct VP3in1 : public in_port<int> {};
			struct VP3in2 : public in_port<int> {};
			};


//Atomic model class
template<typename TIME> 
		class VP3{
		public:


//Ports definition
		using input_ports = tuple<typename VP3_defs:: VP3in1,
					typename VP3_defs:: VP3in2>;
		using output_ports = tuple<typename VP3_defs:: VP3out1>;


//Model parameters to be overwritten during instantiation
	struct state_type{
					int ID;
					bool VP3busy;
					int N123;
	

//Declare the state variables here
					};
			state_type state;


//Default constructor without parameters
	VP3 () noexcept{
					state.VP3busy = false;
					state.N123=0;
//Define the default constructor here
}


//Constructor with parameters if needed


void internal_transition() {
					state.VP3busy = false;
//Define internal transition here
						}


void external_transition(TIME e, typename make_message_bags<input_ports>::type (mbs)){

	if((get_messages<typename VP3_defs::VP3in1>(mbs).size()+get_messages<typename VP3_defs::VP3in2>(mbs).size())>2){
                    assert(false && "Accumulator (external): there is more than one message in the bag");
                }

	vector<int> bag_port_in;
	for(const auto &x : get_messages<typename VP3_defs::VP3in1>(mbs)){
	if(state.VP3busy == false){
		bag_port_in=get_messages<typename VP3_defs::VP3in1>(mbs);
		state.ID = bag_port_in[0];
        state.VP3busy = true;
		state.N123++;

      }
	for(const auto &x : get_messages<typename VP3_defs::VP3in2>(mbs)){
					state.VP3busy = false;
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
	if (state.VP3busy == true) {
	vector<int> bag_port_out;
	bag_port_out.push_back(state.ID);
	get_messages<typename VP3_defs::VP3out1>(bags)=bag_port_out;
            }

//Define output function here
return bags;
}


TIME time_advance() const {
TIME next_internal;
        if ((state.VP3busy)==true) {
            next_internal = TIME("00:00:10:000");
        }else {
            next_internal = numeric_limits<TIME>::infinity();
        }
        return next_internal;
    }

//Define time advance function here

friend ostringstream& operator<<(ostringstream& os, const typename VP3<TIME>::state_type& i) {
	os << "Person completed Vaccination with Pfizer: " << i.N123<< " Last served ID: " << i.ID << endl;
        //Define how to log the state here
return os;
}
};
#endif //VP3_HPP
