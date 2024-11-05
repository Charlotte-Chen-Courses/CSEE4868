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

    //  Insert here the definition of the
    //  signals that are necessary to connect
    //  the testbench and the fc_layer module.
    sc_signal<fc_layer_conf_t> conf_info;
    sc_signal<bool> conf_done;
    sc_signal<bool> irq;

    //  Insert here the definition of the
    //  TLM FIFOs that are necessary to connect
    //  the testbench and the fc_layer module.
    tlm_fifo<float> data_fifo;
    tlm_fifo<float> output_fifo;

    // -- Modules

    // Define the modules here, i.e.,
    // the testbench and the fc_layer module.
    fc_layer_tb* tb;
    fc_layer* dut;

    // -- Constructor
    SC_HAS_PROCESS(system_t);
    system_t(sc_module_name name, std::string model_path, std::string image_name) :
        sc_module(name),
        clk("clk"),
        rst("rst"),
        perf_en("perf_en"),
        conf_info("conf_info"),
        conf_done("conf_done"),
        irq("irq"),
        data_fifo("data_fifo", FIFO_DEPTH),
        output_fifo("output_fifo", FIFO_DEPTH)
        
        
        

      { 
        // Connect the modules here, i.e.,
        // the testbench and the fc_layer module.
        tb = new fc_layer_tb("fc_layer_tb", model_path, image_name);
        dut = new fc_layer("fc_layer");
        // Connect testbench
        tb->perf_en(perf_en);
        tb->clk(clk);
        tb->rst(rst);
        
        tb->conf_info_o(conf_info);
        tb->conf_done_o(conf_done);
        tb->irq_i(irq);
        tb->data_o(data_fifo);
        tb->data_i(output_fifo);

        // Connect DUT
        dut->clk(clk);
        dut->rst(rst);
        dut->perf_en(perf_en);

        dut->conf_info_i(conf_info);
        dut->conf_done_i(conf_done);
        dut->irq_o(irq);


        dut->data_i(data_fifo);
        dut->data_o(output_fifo);
      }
};

#endif // __SYSTEM_HPP__
