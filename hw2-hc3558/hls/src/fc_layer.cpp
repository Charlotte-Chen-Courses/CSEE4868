/* Copyright 2019 Columbia University, SLD Group */
/* Contact: paolo@cs.columbia.edu                */

// Class header file
#include "fc_layer.hpp"

// -- Functions (kernel)

#include "fc_layer_functions.hpp"

void fc_layer::process_config(void) {
    // Implement the reset here.
    if(!rst.read()) {
        reset();
        config_done.write(false);
        wait();
    }


    //  Read the configuration parameters:
    //  - conf_info_i: contains the config. parameters.
    //  - conf_done_i: tells you when they are ready.
    while(!conf_done_i.read()){
        wait();
    }
    cfg = conf_info_i.read();
    

    // Allocate necessary memory
    // Note that this is not possible in hardware!
    data_in = new float[cfg.in_size];
    weights_in = new float[cfg.num_w_cols * cfg.num_w_rows];
    bias_in = new float[cfg.out_size];
    data_out = new float[cfg.out_size];

    REPORT_INFO("CONFIG DONE");

    // Flag that the process_config is done.
    config_done.write(true);

    // Reset restarts SC_THREAD
    do {
        wait();
    } while (true);
}

void fc_layer::process_load(void) {
    // Implement the reset here.
    if(!rst.read()) {
        reset();
        load_done.write(false);
        load_flag.write(false);
        wait();
    }

    // Wait for the process_config to be done.
    while(!config_done.read()) {
        wait();
    }
    

    // Flag to the increment counter process through internal flag signal
    // that load functionality started and synchronize by waiting
    load_flag.write(true);
    wait();
   
    //  Send the data by using the function get()
    //  on the input channel of the fc_layer module.
    
    data_in = new float[cfg.in_size];
    weights_in = new float[cfg.num_w_cols * cfg.num_w_rows];
    bias_in = new float[cfg.out_size];

    
    for (uint32_t i = 0; i < cfg.in_size; i++) {
       data_in[i] = data_i->get();
    }
    for (uint32_t i = 0; i < cfg.num_w_cols * cfg.num_w_rows; i++) {
        
        weights_in[i] = data_i->get();
    }

    for (uint32_t i = 0; i < cfg.out_size; i++) {
       bias_in[i] = data_i->get();
    }
    // Flag to the increment counter process through internal flag
    // signal that load functionality is done
    load_flag.write(false);

    REPORT_INFO("LOAD DONE");

    // Flag that the process_load is done.
    load_done.write(true);

    // Reset restarts the SC_THREAD.
    do {
        wait();
    } while (true);
}

void fc_layer::process_compute(void) {
    // Implement the reset here.
    if(!rst.read()) {
        reset();
        compute_done.write(false);
        compute_flag.write(false);
        wait();
    }

    // Wait for the process_config to be done.
    while(!config_done.read()) {
        wait();
    }

    // --> Wait for the process_load to be done.
    while(!load_done.read()) {
        wait();
    }
    
    // Flag to the increment counter process through an 
    // internal flag signal that the compute functionality has started 
    compute_flag.write(true); 
    wait();
    

    //  Call the function fc_compute() (fc_layer_functions.hpp).
    //  note: this can be done because we have access to the entire data
    //  set. Start thinking about how you would have to split computation
    //  when only portions of the dataset can be accessed by the compute
    //  process. It will become very useful later in the semester.
    fc_compute(data_out, data_in, weights_in, bias_in, cfg.num_w_cols, cfg.num_w_rows);

    // Flag to the increment counter process through internal flag signal
    // that compute functionality is done

    compute_flag.write(false);


    
    
    REPORT_INFO("COMPUTE DONE");

    // Flag that the process_compute is done.
    compute_done.write(true);
    wait();

    // Reset restarts the SC_THREAD.
    do {
        wait();
    } while (true);
}

void fc_layer::process_store(void) {
    // Implement the reset here.
    if(!rst.read()) {
        reset();
        store_flag.write(false);
        irq_o.write(false);
        wait();
    }

    // Wait for the process_config to be done.
    while(!config_done.read()) {
        wait();
    }
    
    // --> Wait for the process_compute to be done.
   
    while (!compute_done.read()) {
        wait();  // Wait for the next clock cycle or signal update
    }

    
    // Flag to the increment counter process through internal flag signal
    // that store functionality started and syncronize by waiting
    store_flag.write(true);
    wait();

    // Send the data by using the function put()
    //  on the output channel of the fc_layer module. 
    
    for (uint32_t i = 0; i < cfg.out_size; i++) {
        data_o->put(data_out[i]);
    }

    // Flag to the increment counter process through internal flag signal
    // that store functionality is done
    store_flag.write(false);

    REPORT_INFO("STORE DONE");

 
    // If performance monitoring is enabled, then report the performance counter values for all 3 counters
    if (perf_en.read()) {
        REPORT_INFO("Performance Counters: Load Count = %u, Compute Count = %u, Store Count = %u",*load_count, *compute_count, *store_count);
    }
    
    
    
  
    // Flag that the module is done (irq_o).
    irq_o.write(true);
    



    // Free up the memory with "delete[]".
    //  note: this is meaningless in hardware!
    delete[] data_in;
    delete[] weights_in;
    delete[] bias_in;
    delete[] data_out;
    delete[] load_count; 
    delete[] compute_count;
    delete[] store_count; 
    // Reset restarts the SC_THREAD.
    
    do {
        wait();
    } while (true);
}

void fc_layer:: process_inc_count (void) {
    // Reset
    wait();

    // -- Allocate memory and initialize performance counters to 0
    load_count    = new uint32_t(0);
    compute_count = new uint32_t(0);
    store_count   = new uint32_t(0);

    while(true) {
        if (perf_en.read() && load_flag.read()) {
    	    *load_count+=1; 
        }

       	if (perf_en.read() && compute_flag.read()) {
       	    *compute_count+=1;
       	}
	  
       	if (perf_en.read() && store_flag.read()) {
            *store_count+=1;
       	}
        wait();
    } 
}



void fc_layer::reset(void) {
    // Free allocated memory
    
    if (data_in) {
        delete[] data_in;
        data_in = NULL;  // Avoid double-free
    }
    if (weights_in) {
        delete[] weights_in;
        weights_in = NULL;  // Avoid double-free
    }
    if (bias_in) {
        delete[] bias_in;
        bias_in = NULL;  // Avoid double-free
    }
    if (data_out) {
        delete[] data_out;
        data_out = NULL;  // Avoid double-free
    }    
}
