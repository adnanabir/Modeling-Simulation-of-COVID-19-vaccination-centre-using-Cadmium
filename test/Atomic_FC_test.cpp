//Cadmium Simulator headers
#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/dynamic_model.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>
#include <cadmium/engine/pdevs_dynamic_runner.hpp>
#include <cadmium/logger/common_loggers.hpp>

//Time class header
#include <NDTime.hpp>

//Data structures
#include "../data_structures/message.hpp"


//Atomic model headers
#include <cadmium/basic_model/pdevs/iestream.hpp> //Atomic model for inputs
#include "../atomics/FC.hpp"



//C++ libraries
#include <iostream>
#include <string>

using namespace std;
using namespace cadmium;
using namespace cadmium::basic_models::pdevs;

using TIME = NDTime;

//FCa Port definition

		
		struct FCaout1 : public out_port<int> {};
		struct FCaout2 : public out_port<int> {};



/****** Input Reader atomic model declaration *******************/
template<typename T>
class InputReader_int : public iestream_input<int, T> {
public:
		InputReader_int() = default;
		InputReader_int(const char* file_path) : iestream_input<int,T>(file_path) {}
};



   /****** Input Reader atomic model instantiation *******************/
int main() {
    const char * i_input_data = "../input_data/input_FC_01.txt";
		shared_ptr <dynamic::modeling::model> input_reader1;
		input_reader1= dynamic::translate::make_dynamic_atomic_model<InputReader_int, TIME, const char* >("input_reader1" , move(i_input_data));

	
	
//****** FC atomic model instantiations ****************
shared_ptr<dynamic::modeling::model> FC1;
    FC1 = dynamic::translate::make_dynamic_atomic_model<FC, TIME>("FC1");



/*******FCa MODEL********/
		dynamic::modeling::Ports iports_FCa = {};
		dynamic::modeling::Ports oports_FCa = {typeid(FCaout1),typeid(FCaout2)};
		dynamic::modeling::Models submodels_FCa = {input_reader1, FC1};
		dynamic::modeling::EICs eics_FCa = {};
		dynamic::modeling::EOCs eocs_FCa = {
			dynamic::translate::make_EOC< FC_defs::FCout1,FCaout1>("FC1"),
			dynamic::translate::make_EOC< FC_defs::FCout2,FCaout2>("FC1")
		};
		dynamic::modeling::ICs ics_FCa = {
			dynamic::translate::make_IC <iestream_input_defs<int>::out,FC_defs::FCin1>("input_reader1","FC1"),
			dynamic::translate::make_IC <FC_defs::FCout1,FC_defs::FCin2>("FC1","FC1"),
			dynamic::translate::make_IC <FC_defs::FCout2,FC_defs::FCin3>("FC1","FC1")
		};
	
shared_ptr<cadmium::dynamic::modeling::coupled<TIME>> FCa;
    FCa = make_shared<dynamic::modeling::coupled<TIME>>(
        "FCa", submodels_FCa, iports_FCa, oports_FCa, eics_FCa, eocs_FCa, ics_FCa
    );

    /*************** Loggers *******************/
    static ofstream out_messages("../simulation_results/FC_output_messages.txt");
    struct oss_sink_messages{
        static ostream& sink(){
            return out_messages;
        }
    };
    static ofstream out_state("../simulation_results/FC_output_state.txt");
    struct oss_sink_state{
        static ostream& sink(){
            return out_state;
        }
    };

    using state=logger::logger<logger::logger_state, dynamic::logger::formatter<TIME>, oss_sink_state>;
    using log_messages=logger::logger<logger::logger_messages, dynamic::logger::formatter<TIME>, oss_sink_messages>;
    using global_time_mes=logger::logger<logger::logger_global_time, dynamic::logger::formatter<TIME>, oss_sink_messages>;
    using global_time_sta=logger::logger<logger::logger_global_time, dynamic::logger::formatter<TIME>, oss_sink_state>;

    using logger_top=logger::multilogger<state, log_messages, global_time_mes, global_time_sta>;

    /************** Runner call ************************/
    dynamic::engine::runner<NDTime, logger_top> r(FCa, {0});
    r.run_until_passivate();
    return 0;
}
