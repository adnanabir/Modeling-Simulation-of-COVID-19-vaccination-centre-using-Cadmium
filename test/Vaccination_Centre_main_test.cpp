//Cadmium Simulator headers
#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/dynamic_model.hpp>
#include <cadmium/modeling/dynamic_coupled.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>
#include <cadmium/engine/pdevs_dynamic_runner.hpp>
#include <cadmium/logger/common_loggers.hpp>

//Time class header
#include <NDTime.hpp>

//Data structures
#include "../data_structures/message.hpp"


//Atomic model headers
#include <cadmium/basic_model/pdevs/iestream.hpp> //Atomic model for inputs
#include "../atomics/RGD.hpp"
#include "../atomics/RGDQ.hpp"
#include "../atomics/RD.hpp"
#include "../atomics/RDQ.hpp"
#include "../atomics/VW.hpp"
#include "../atomics/VP1.hpp"
#include "../atomics/VP2.hpp"
#include "../atomics/VP3.hpp"
#include "../atomics/FC.hpp"
#include "../atomics/OB.hpp"
#include "../atomics/PVQ1.hpp"
#include "../atomics/PVQ2.hpp"
#include "../atomics/PVQ3.hpp"
#include "../atomics/VH.hpp"


//C++ libraries
#include <iostream>
#include <string>

using namespace std;
using namespace cadmium;
using namespace cadmium::basic_models::pdevs;

using TIME = NDTime;

//Top Port definition

		
		struct Topout1 : public out_port<int> {};
		struct Topout2 : public out_port<int> {};

/****** Input Reader atomic model declaration *******************/
template<typename T>
class InputReader_int : public iestream_input<int, T> {
public:
		InputReader_int() = default;
		InputReader_int(const char* file_path) : iestream_input<int,T>(file_path) {}
};



   /****** Input Reader atomic model instantiation *******************/
int main() {
    const char * i_input_data = "../input_data/input_VC_main_01.txt";
		shared_ptr <dynamic::modeling::model> input_reader1;
		input_reader1= dynamic::translate::make_dynamic_atomic_model<InputReader_int, TIME, const char* >("input_reader1" , move(i_input_data));

	
//****** RDQ atomic model instantiations ****************
shared_ptr<dynamic::modeling::model> RDQ1;
    RDQ1 = dynamic::translate::make_dynamic_atomic_model<RDQ, TIME>("RDQ1");

//****** RD atomic model instantiations ****************
shared_ptr<dynamic::modeling::model> RD1;
    RD1 = dynamic::translate::make_dynamic_atomic_model<RD, TIME>("RD1");
//****** RGDQ atomic model instantiations ****************
shared_ptr<dynamic::modeling::model> RGDQ1;
    RGDQ1 = dynamic::translate::make_dynamic_atomic_model<RGDQ, TIME>("RGDQ1");
//****** RDQ atomic model instantiations ****************
shared_ptr<dynamic::modeling::model> RGD1;
    RGD1 = dynamic::translate::make_dynamic_atomic_model<RGD, TIME>("RGD1");
	
//****** VW atomic model instantiations ****************
shared_ptr<dynamic::modeling::model> VW1;
    VW1 = dynamic::translate::make_dynamic_atomic_model<VW, TIME>("VW1");

//****** VH atomic model instantiations ****************
shared_ptr<dynamic::modeling::model> VH1;
    VH1 = dynamic::translate::make_dynamic_atomic_model<VH, TIME>("VH1");

//****** PVQ1 atomic model instantiations ****************
shared_ptr<dynamic::modeling::model> PVQ11;
    PVQ11 = dynamic::translate::make_dynamic_atomic_model<PVQ1, TIME>("PVQ11");

//****** PVQ2 atomic model instantiations ****************
shared_ptr<dynamic::modeling::model> PVQ21;
    PVQ21 = dynamic::translate::make_dynamic_atomic_model<PVQ2, TIME>("PVQ21");	

//****** PVQ3 atomic model instantiations ****************
shared_ptr<dynamic::modeling::model> PVQ31;
    PVQ31 = dynamic::translate::make_dynamic_atomic_model<PVQ3, TIME>("PVQ31");

//****** VP1 atomic model instantiations ****************
shared_ptr<dynamic::modeling::model> VP11;
    VP11 = dynamic::translate::make_dynamic_atomic_model<VP1, TIME>("VP11");

//****** VP2 atomic model instantiations ****************
shared_ptr<dynamic::modeling::model> VP21;
    VP21 = dynamic::translate::make_dynamic_atomic_model<VP2, TIME>("VP21");

//****** VP3 atomic model instantiations ****************
shared_ptr<dynamic::modeling::model> VP31;
    VP31 = dynamic::translate::make_dynamic_atomic_model<VP3, TIME>("VP31");

//****** OB atomic model instantiations ****************
shared_ptr<dynamic::modeling::model> OB1;
    OB1 = dynamic::translate::make_dynamic_atomic_model<OB, TIME>("OB1");

//****** FC atomic model instantiations ****************
shared_ptr<dynamic::modeling::model> FC1;
    FC1 = dynamic::translate::make_dynamic_atomic_model<FC, TIME>("FC1");	

/*******Top MODEL********/
		dynamic::modeling::Ports iports_Top = {};
		dynamic::modeling::Ports oports_Top = {typeid(Topout1), typeid(Topout2)};
		dynamic::modeling::Models submodels_Top = {input_reader1, RDQ1, RD1, RGDQ1, RGD1, VW1, VH1, PVQ11, PVQ21, PVQ31, VP11, VP21, VP31, OB1,FC1};
		dynamic::modeling::EICs eics_Top = {};
		dynamic::modeling::EOCs eocs_Top = {
			dynamic::translate::make_EOC< FC_defs::FCout1,Topout1>("FC1"),
			dynamic::translate::make_EOC< FC_defs::FCout2,Topout2>("FC1")
		};
		dynamic::modeling::ICs ics_Top = {
			dynamic::translate::make_IC <iestream_input_defs<int>::out,RDQ_defs::RDQin1>("input_reader1","RDQ1"),
			dynamic::translate::make_IC <RDQ_defs::RDQout1,RD_defs::RDin1>("RDQ1","RD1"),		
			dynamic::translate::make_IC <RDQ_defs::RDQout1,RDQ_defs::RDQin3>("RDQ1","RDQ1"),
			dynamic::translate::make_IC <RD_defs::RDout2,RDQ_defs::RDQin4>("RD1","RDQ1"),
			dynamic::translate::make_IC <RD_defs::RDout2,RD_defs::RDin3>("RD1","RD1"),			
			dynamic::translate::make_IC <RD_defs::RDout1,RGDQ_defs::RGDQin1>("RD1","RGDQ1"),
			dynamic::translate::make_IC <RD_defs::RDout1,RDQ_defs::RDQin5>("RD1","RDQ1"),
			dynamic::translate::make_IC <RD_defs::RDout1,RD_defs::RDin2>("RD1","RD1"),
			dynamic::translate::make_IC <RGDQ_defs::RGDQout1,RGD_defs::RGDin1>("RGDQ1","RGD1"),
			dynamic::translate::make_IC <RGDQ_defs::RGDQout1,RD_defs::RDin4>("RGDQ1","RD1"),
			dynamic::translate::make_IC <RGDQ_defs::RGDQout1,RGDQ_defs::RGDQin2>("RGDQ1","RGDQ1"),
			dynamic::translate::make_IC <RGD_defs::RGDout1,RDQ_defs::RDQin2>("RGD1","RDQ1"),
			dynamic::translate::make_IC <RGD_defs::RGDout1,RGDQ_defs::RGDQin3>("RGD1","RGDQ1"),
			dynamic::translate::make_IC <RGD_defs::RGDout1,RGD_defs::RGDin2>("RGD1","RGD1"),
			dynamic::translate::make_IC <RD_defs::RDout2,VW_defs::VWin1>("RD1","VW1"),
			dynamic::translate::make_IC <VW_defs::VWout1,VH_defs::VHin1>("VW1","VH1"),	
			dynamic::translate::make_IC <VW_defs::VWout1,RD_defs::RDin5>("VW1","RD1"),
			dynamic::translate::make_IC <VW_defs::VWout1,VW_defs::VWin2>("VW1","VW1"),
			dynamic::translate::make_IC <VH_defs::VHout1,VW_defs::VWin3>("VH1","VW1"),
			dynamic::translate::make_IC <VH_defs::VHout1,PVQ1_defs::PVQ1in1>("VH1","PVQ11"),
			dynamic::translate::make_IC <VH_defs::VHout1,VH_defs::VHin2>("VH1","VH1"),
			dynamic::translate::make_IC <VH_defs::VHout2,VH_defs::VHin3>("VH1","VH1"),
			dynamic::translate::make_IC <VH_defs::VHout2,PVQ2_defs::PVQ2in1>("VH1","PVQ21"),
			dynamic::translate::make_IC <VH_defs::VHout2,VW_defs::VWin4>("VH1","VW1"),
			dynamic::translate::make_IC <VH_defs::VHout3,VH_defs::VHin4>("VH1","VH1"),
			dynamic::translate::make_IC <VH_defs::VHout3,PVQ3_defs::PVQ3in1>("VH1","PVQ31"),
			dynamic::translate::make_IC <VH_defs::VHout3,VW_defs::VWin5>("VH1","VW1"),
			dynamic::translate::make_IC <PVQ1_defs::PVQ1out1,VP1_defs::VP1in1>("PVQ11","VP11"),
			dynamic::translate::make_IC <PVQ1_defs::PVQ1out1,PVQ1_defs::PVQ1in2>("PVQ11","PVQ11"),
			dynamic::translate::make_IC <PVQ1_defs::PVQ1out1,VH_defs::VHin5>("PVQ11","VH1"),
			dynamic::translate::make_IC <PVQ2_defs::PVQ2out1,VP2_defs::VP2in1>("PVQ21","VP21"),
			dynamic::translate::make_IC <PVQ2_defs::PVQ2out1,PVQ2_defs::PVQ2in2>("PVQ21","PVQ21"),
			dynamic::translate::make_IC <PVQ2_defs::PVQ2out1,VH_defs::VHin6>("PVQ21","VH1"),
			dynamic::translate::make_IC <PVQ3_defs::PVQ3out1,VP3_defs::VP3in1>("PVQ31","VP31"),
			dynamic::translate::make_IC <PVQ3_defs::PVQ3out1,PVQ3_defs::PVQ3in2>("PVQ31","PVQ31"),
			dynamic::translate::make_IC <PVQ3_defs::PVQ3out1,VH_defs::VHin7>("PVQ31","VH1"),
			dynamic::translate::make_IC <VP1_defs::VP1out1,OB_defs::OBin1>("VP11","OB1"),
			dynamic::translate::make_IC <VP1_defs::VP1out1,VP1_defs::VP1in2>("VP11","VP11"),
			dynamic::translate::make_IC <VP1_defs::VP1out1,PVQ1_defs::PVQ1in3>("VP11","PVQ11"),
			dynamic::translate::make_IC <VP2_defs::VP2out1,OB_defs::OBin2>("VP21","OB1"),
			dynamic::translate::make_IC <VP2_defs::VP2out1,VP2_defs::VP2in2>("VP21","VP21"),
			dynamic::translate::make_IC <VP2_defs::VP2out1,PVQ2_defs::PVQ2in3>("VP21","PVQ21"),
			dynamic::translate::make_IC <VP3_defs::VP3out1,OB_defs::OBin3>("VP31","OB1"),
			dynamic::translate::make_IC <VP3_defs::VP3out1,VP3_defs::VP3in2>("VP31","VP31"),
			dynamic::translate::make_IC <VP3_defs::VP3out1,PVQ3_defs::PVQ3in3>("VP31","PVQ31"),
			dynamic::translate::make_IC <OB_defs::OBout1,FC_defs::FCin1>("OB1","FC1"),
			dynamic::translate::make_IC <OB_defs::OBout1,OB_defs::OBin4>("OB1","OB1"),
			dynamic::translate::make_IC <FC_defs::FCout1,FC_defs::FCin2>("FC1","FC1"),
			dynamic::translate::make_IC <FC_defs::FCout1,OB_defs::OBin5>("FC1","OB1"),
			dynamic::translate::make_IC <FC_defs::FCout2,FC_defs::FCin3>("FC1","FC1"),
			dynamic::translate::make_IC <FC_defs::FCout2,OB_defs::OBin6>("FC1","OB1")
		};
	
 shared_ptr<cadmium::dynamic::modeling::coupled<TIME>> Top;
    Top = make_shared<dynamic::modeling::coupled<TIME>>(
        "Top", submodels_Top, iports_Top, oports_Top, eics_Top, eocs_Top, ics_Top
    );

    /*************** Loggers *******************/
    static ofstream out_messages("../simulation_results/Top_output_messages.txt");
    struct oss_sink_messages{
        static ostream& sink(){
            return out_messages;
        }
    };
    static ofstream out_state("../simulation_results/Top_output_state.txt");
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
    dynamic::engine::runner<NDTime, logger_top> r(Top, {0});
    r.run_until_passivate();
    return 0;
	
}
