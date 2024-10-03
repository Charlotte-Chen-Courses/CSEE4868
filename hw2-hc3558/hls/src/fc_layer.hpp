/* Copyright 2019 Columbia University, SLD Group */
/* Contact: paolo@cs.columbia.edu                */

#ifndef __FC_LAYER_H__
#define __FC_LAYER_H__

#include "utils.hpp"
#include "fc_layer_datatypes.hpp"

SC_MODULE(fc_layer) {
    public :
    // @TODO: Implement the module fc_layer here.
    sc_in<bool> perf_en;            // Performance counter enable signal

    // -- Constructor
    SC_CTOR(fc_layer)
    {
        // @TODO: fc_layer thread
        SC_THREAD(process_inc_count);
        sensitive << clk.pos();
        reset_signal_is(rst, false);   
    }

    // @TODO
    void process_inc_count(void);    // -- SystemC Process to increment performance counters

    // @TODO: Use sc_signal based flags to keep track of performance counters
    // -- Performance Counter Registers
    uint32_t *load_count;
    uint32_t *compute_count;
    uint32_t *store_count;
};

#endif // __FC_LAYER_H__
