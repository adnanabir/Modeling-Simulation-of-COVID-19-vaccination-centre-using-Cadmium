/*
* S M Abu Adnan Abir
*
* Atomic model
* VP1=Vaccination pushing counter1:
*/


#ifndef VP1_HPP
#define VP1_HPP

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
struct VP1_defs{
			struct VP1out1 : public out_port<int> {};
			struct VP1in1 : public in_port<int> {};
			struct VP1in2 : public in_port<int> {};
			};


//Atomic model class
template<typename TIME> 
		class VP1{
		public:


//Ports definition
		using input_ports = tuple<typename VP1_defs:: VP1in1,
					typename VP1_defs:: VP1in2>;
		using output_ports = tuple<typename VP1_defs:: VP1out1>;


//Model parameters to be overwritten during instantiation
	struct state_type{
					int ID;
					bool VP1busy;
					int N121;
	

//Declare the state variables here
					};
			state_type state;


//Default constructor without parameters
	VP1 () noexcept{
					state.VP1busy = false;
					state.N121=0;
//Define the default constructor here
}


//Constructor with parameters if needed


void internal_transition() {
					state.VP1busy = false;
//Define internal transition here
						}


void external_transition(TIME e, typename make_message_bags<input_ports>::type (mbs)){

	if((get_messages<typename VP1_defs::VP1in1>(mbs).size()+get_messages<typename VP1_defs::VP1in2>(mbs).size())>2){
                    assert(false && "Accumulator (external): there is more than one message in the bag");
                }

	vector<int> bag_port_in;
	for(const auto &x : get_messages<typename VP1_defs::VP1in1>(mbs)){
	if(state.VP1busy == false){
		bag_port_in=get_messages<typename VP1_defs::VP1in1>(mbs);
		state.ID = bag_port_in[0];
        state.VP1busy = true;
		state.N121++;

      }
	for(const auto &x : get_messages<typename VP1_defs::VP1in2>(mbs)){
					state.VP1busy = false;
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
	if (state.VP1busy == true) {
	vector<int> bag_port_out;
	bag_port_out.push_back(state.ID);
	get_messages<typename VP1_defs::VP1out1>(bags)=bag_port_out;
            }

//Define output function here
return bags;
}


TIME time_advance() const {
TIME next_internal;
        if ((state.VP1busy)==true) {
            next_internal = TIME("00:00:10:000");
        }else {
            next_internal = numeric_limits<TIME>::infinity();
        }
        return next_internal;
    }

//Define time advance function here

friend ostringstream& operator<<(ostringstream& os, const typename VP1<TIME>::state_type& i) {
	os << "Person completed Vaccination with Oxford-AstraZeneca: " << i.N121<< " Last served ID: " << i.ID << endl;
        //Define how to log the state here
return os;
}
};
#endif //VP1_HPP
