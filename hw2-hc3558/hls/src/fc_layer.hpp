/* Copyright 2019 Columbia University, SLD Group */
/* Contact: paolo@cs.columbia.edu                */

#ifndef __FC_LAYER_H__
#define __FC_LAYER_H__

#include "utils.hpp"
#include "fc_layer_datatypes.hpp"
#include <systemc>

SC_MODULE(fc_layer) {
    public :
    sc_in<bool> perf_en;            // Performance counter enable signal
    sc_in<bool> clk;                // Clock signal
    sc_in<bool> rst;                // Reset signal  


    sc_in<fc_layer_conf_t> conf_info_i;     // Structure for input configuration
    sc_in<bool> conf_done_i;                // Signal for configuration sent
    sc_out<bool> irq_o;                     // Signal for DUT part done

    sc_signal<bool> config_done;            // DUT inner signal for process_config done
    sc_signal<bool> load_done;              // DUT inner signal for process_load done
    sc_signal<bool> compute_done;           // DUT inner signal for process_compute done


    // TLM port
    sc_port<tlm_blocking_put_if<float> > data_o;        // TLM block send output data
    sc_port<tlm_blocking_get_if<float> > data_i;        // TLM block get input data


    // -- Constructor
    SC_CTOR(fc_layer)
    {
        // Thread to increment performance counters
        SC_THREAD(process_inc_count);
        sensitive << clk.pos();
        reset_signal_is(rst, false);  

        // Thread to handle configuration
        SC_THREAD(process_config);
        sensitive << clk.pos();
        reset_signal_is(rst, false);  

        // Thread to handle loading
        SC_THREAD(process_load);
        sensitive << clk.pos();
        reset_signal_is(rst, false);  

        // Thread to handle computation
        SC_THREAD(process_compute);
        sensitive << clk.pos();
        reset_signal_is(rst, false);

        // Thread to handle storing
        SC_THREAD(process_store);
        sensitive << clk.pos();
        reset_signal_is(rst, false);
    }


    void process_inc_count(void);    // -- SystemC Process to increment performance counters


    void process_config(void);      // -- SystemC Process to handle configuration


    void process_load(void);        // -- SystemC Process to handle loading


    void process_compute(void);     // -- SystemC Process to handle computation


    void process_store(void);       // -- SystemC Process to handle storing

    void reset(void);               // Reset function



    // -- Member Variables
    float *data_in;
    float *weights_in;
    float *bias_in;
    float *data_out;
    fc_layer_conf_t cfg;




    // -- Use sc_signal based flags to keep track of performance counters
    sc_signal<bool> load_flag;
    sc_signal<bool> compute_flag;
    sc_signal<bool> store_flag;

    // -- Performance Counter Registers
    uint32_t *load_count;
    uint32_t *compute_count;
    uint32_t *store_count;
};

#endif // __FC_LAYER_H__
