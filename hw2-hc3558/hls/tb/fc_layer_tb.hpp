/* Copyright 2019 Columbia University, SLD Group */

#ifndef __FC_LAYER_TB_H__
#define __FC_LAYER_TB_H__

#include "utils.hpp"
#include "fc_layer.hpp"

SC_MODULE(fc_layer_tb) {
    // -- Ports

    // @TODO Insert here the definition of the
    //  ports of the testbench (fc_layer_tb).

    // -- Constructor
    SC_HAS_PROCESS(fc_layer_tb);
    fc_layer_tb(sc_module_name name, std::string model_path, std::string image_name)
        // @TODO Initialize other ports and member variables.
    {
        tot_errors = 0;

        // @TODO Define the SC_THREAD process_tb.
    }

    // -- SystemC process
    void process_tb();

    // -- Methods
    void set_configuration_param();
    void run_pv(int layer, bool fully_connected);
    void load_memory();
    void dump_memory();
    void validate();
    void end_simulation();

    // -- Memeber variables
    unsigned int tot_errors;
    fc_layer_conf_t config;
    std::string model_path;
    std::string image_name;
};

#endif // __FC_LAYER_TB_H__
