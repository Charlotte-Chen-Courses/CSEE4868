/* Copyright 2019 Columbia University, SLD Group */

#ifndef __FC_LAYER_TB_H__
#define __FC_LAYER_TB_H__

#include "utils.hpp"
#include "fc_layer.hpp"
#include <systemc>

SC_MODULE(fc_layer_tb) {
    // -- Ports

    // @TODO Insert here the definition of the
    //  ports of the testbench (fc_layer_tb).


    sc_in<bool> perf_en;
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_out<fc_layer_conf_t> conf_info_o;

    sc_out<bool> conf_done_o;
    sc_in<bool> irq_i;


    // TLM port
    sc_port<tlm_blocking_get_if<float> > data_i;
    sc_port<tlm_blocking_put_if<float> > data_o;



    // -- Constructor
    SC_HAS_PROCESS(fc_layer_tb);
    fc_layer_tb(sc_module_name name, std::string model_path, std::string image_name)
        // Initialize other ports and member variables.
        : sc_module(name),
        perf_en("perf_en"),
        clk("clk"),
        rst("rst"),
        conf_info_o("conf_info_o"),
        conf_done_o("conf_done_o"),
        irq_i("irq_i"),
        data_o("data_o"),
        tot_errors(0),
        model_path(model_path),
        image_name(image_name)
    {
        tot_errors = 0;

        // Define the SC_THREAD process_tb.
        SC_THREAD(process_tb);
        sensitive << clk.pos();
        reset_signal_is(rst, false);
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
