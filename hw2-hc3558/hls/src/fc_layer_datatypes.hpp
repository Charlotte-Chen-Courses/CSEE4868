/* Copyright 2019 Columbia University, SLD Group */

//
// fc_layer_datatypes - Paolo Mantovani
//

#include "systemc.h"

#ifndef __FC_LAYER_DATATYPES_H__
#define __FC_LAYER_DATATYPES_H__

struct fc_layer_conf_t {
    // @TODO: Implement the custom data type here.
    uint32_t in_size;
    uint32_t out_size;
    uint32_t num_w_cols;
    uint32_t num_w_rows;

    // sc_trace for waveform tracing
    friend void sc_trace(sc_trace_file *tf, const fc_layer_conf_t &conf, const std::string &name) {
        sc_trace(tf, conf.in_size, name + ".in_size");
        sc_trace(tf, conf.out_size, name + ".out_size");
        sc_trace(tf, conf.num_w_cols, name + ".num_w_cols");
        sc_trace(tf, conf.num_w_rows, name + ".num_w_rows");
    }


    bool operator==(const fc_layer_conf_t& other) const {
        return in_size == other.in_size &&
               out_size == other.out_size &&
               num_w_cols == other.num_w_cols &&
               num_w_rows == other.num_w_rows;
    }



};


inline std::ostream& operator<<(std::ostream& os, const fc_layer_conf_t& conf) {
    os << "in_size: " << conf.in_size
       << ", out_size: " << conf.out_size
       << ", num_w_cols: " << conf.num_w_cols
       << ", num_w_rows: " << conf.num_w_rows;
    return os;
}

#endif // __FC_LAYER_DATATYPES_H__
