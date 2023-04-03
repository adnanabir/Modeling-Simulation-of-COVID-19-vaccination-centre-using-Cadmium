/*
* S M Abu Adnan Abir
*
* Atomic model
* RGD=Registration desk:
*/


#ifndef RGD_HPP
#define RGD_HPP

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
struct RGD_defs{
struct RGDout1 : public out_port<int> {};
struct RGDin1 : public in_port<int> {};
struct RGDin2 : public in_port<int> {};
};


//Atomic model class
template<typename TIME> 
class RGD{
public:


//Ports definition
using input_ports = tuple<typename RGD_defs:: RGDin1,
			typename RGD_defs:: RGDin2>;
using output_ports = tuple<typename RGD_defs:: RGDout1>;


//Model parameters to be overwritten during instantiation
struct state_type{
	int ID;
	bool RGDbusy;
	int N5;
	int N51;

//Declare the state variables here
};
state_type state;


//Default constructor without parameters
RGD () noexcept{

	state.RGDbusy = false;
	state.N51=0;


//Define the default constructor here
}


//Constructor with parameters if needed


void internal_transition() {
	state.RGDbusy = false;
//Define internal transition here
}


void external_transition(TIME e, typename make_message_bags<input_ports>::type (mbs)){

	if((get_messages<typename RGD_defs::RGDin1>(mbs).size()+get_messages<typename RGD_defs::RGDin1>(mbs).size())>2){
                    assert(false && "Accumulator (external): there is more than one message in the bag");
                }
vector<int> bag_port_in;
	
for(const auto &x : get_messages<typename RGD_defs::RGDin1>(mbs)){
	if(state.RGDbusy == false){
	state.N5 = (rand() % 3) + 1;
	
	bag_port_in=get_messages<typename RGD_defs::RGDin1>(mbs);
	state.ID = bag_port_in[0]+ state.N5;
        state.RGDbusy = true;
	state.N51++;

}
}
for(const auto &x : get_messages<typename RGD_defs::RGDin2>(mbs)){
	state.RGDbusy = false;
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
	if (state.RGDbusy == true) {
	vector<int> bag_port_out;

	bag_port_out.push_back(state.ID);
	get_messages<typename RGD_defs::RGDout1>(bags)=bag_port_out;
            }

//Define output function here
return bags;
}


TIME time_advance() const {
TIME next_internal;
        if ((state.RGDbusy)==true) {
            next_internal = TIME("00:00:10:000");
        }else {
            next_internal = numeric_limits<TIME>::infinity();
        }
        return next_internal;
    }

//Define time advance function here

friend ostringstream& operator<<(ostringstream& os, const typename RGD<TIME>::state_type& i) {
	os << "Person completed new registration: " << i.N51<< "Last served ID: " << i.ID << endl;
        //Define how to log the state here
return os;
}
};
#endif //RGD_HPP
