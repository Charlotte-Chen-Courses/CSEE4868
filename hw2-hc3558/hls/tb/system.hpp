/* Copyright 2019 Columbia University, SLD Group */
/* Contact: paolo@cs.columbia.edu                */

#include "utils.hpp"
#include "fc_layer.hpp"
#include "fc_layer_tb.hpp"

#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

#define FIFO_DEPTH 4

SC_MODULE(system_t) {
  public:
    // -- Ports
    // Clock signal
    sc_in<bool> clk;

    // Reset signal
    sc_in<bool> rst;

    // Performance Monitor Enable
    sc_in<bool> perf_en; 

    // -- Channels

    // @TODO Insert here the definition of the
    //  signals that are necessary to connect
    //  the testbench and the fc_layer module.

    // @TODO Insert here the definition of the
    //  TLM FIFOs that are necessary to connect
    //  the testbench and the fc_layer module.

    // -- Modules

    // @TODO Define the modules here, i.e.,
    // the testbench and the fc_layer module.

    // -- Constructor
    SC_HAS_PROCESS(system_t);
    system_t(sc_module_name name, std::string model_path, std::string image_name) {
        // @TODO Connect the modules here, i.e.,
        // the testbench and the fc_layer module.
    }
};

#endif // __SYSTEM_HPP__
