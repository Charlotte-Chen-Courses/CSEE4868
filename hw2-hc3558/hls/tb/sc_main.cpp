/* Copyright 2019 Columbia University, SLD Group */
/* Contact: paolo@cs.columbia.edu                */

#include "system.hpp"

#define CLOCK_PERIOD 10
#define RESET_PERIOD 51

system_t *sys = NULL;
std::string model_path = "../../models/dwarf7.mojo"; // path of the model
std::string image_name = "airplane";                 // input image (preprocessed)

int sc_main(int argc, char *argv[]) {
    // Kills a Warning when using SC_THREADS
    sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);

    if (argc > 1) {
        image_name = std::string(argv[1]);
    }

    // @TODO Define the clock signal
    // and the reset signal here. Use
    // the define above to define the
    // clock period of the clock signal.

    // @TODO: Define a signal perf_en to 
    // enable/disable performance monitors in the DUT

    // @TODO Instantiate the module system_t:
    //   -- specify as parameter model_path
    //   -- specify as parameter image_name

    SC_REPORT_INFO("sc_main()", STR("Running DWARF7 for input image ", image_name));
    SC_REPORT_INFO("sc_main()", STR("Clock period is ", CLOCK_PERIOD, " ns\n"));

    // @TODO Connect the clock and reset
    // signal to the module system_t.

    // @TODO Connect the performance enable
    // signal to the module system_t.

    // @TODO Reset the simulation here.
    //  -- hint: use the rst signal and
    //   the function sc_start
   
    // TODO: Enable perofrmance by writing true to the signal

    // -- Starting the simulation here

    sc_start();

    return 0;
}
