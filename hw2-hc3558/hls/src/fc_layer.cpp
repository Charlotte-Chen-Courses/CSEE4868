/* Copyright 2019 Columbia University, SLD Group */
/* Contact: paolo@cs.columbia.edu                */

// Class header file
#include "fc_layer.hpp"

// -- Functions (kernel)

#include "fc_layer_functions.hpp"

void fc_layer::process_config(void) {
    // @TODO: Implement the reset here.

    // @TODO: Read the configuration parameters:
    //  - conf_info_i: contains the config. parameters.
    //  - conf_done_i: tells you when they are ready.

    // Allocate necessary memory
    // Note that this is not possible in hardware!
    data_in = new float[cfg.in_size];
    weights_in = new float[cfg.num_w_cols * cfg.num_w_rows];
    bias_in = new float[cfg.out_size];
    data_out = new float[cfg.out_size];

    REPORT_INFO("CONFIG DONE");

    // @TODO: Flag that the process_config is done.

    // Reset restarts SC_THREAD
    do {
        wait();
    } while (true);
}

void fc_layer::process_load(void) {
    // @TODO: Implement the reset here.

    // @TODO: Wait for the process_config to be done.

    // @TODO: Flag to the increment counter process through internal flag signal
    // that load functionality started and synchronize by waiting
   
    // @TODO: Send the data by using the function get()
    //  on the input channel of the fc_layer module.

    wait();

    // @TODO: Flag to the increment counter process through internal flag
    // signal that load functionality is done

    REPORT_INFO("LOAD DONE");

    // @TODO: Flag that the process_load is done.

    // Reset restarts the SC_THREAD.
    do {
        wait();
    } while (true);
}

void fc_layer::process_compute(void) {
    // @TODO: Implement the reset here.

    // @TODO: Wait for the process_config to be done.

    // @TODO: --> Wait for the process_load to be done.
    
    // @TODO: Flag to the increment counter process through an 
    // internal flag signal that the compute functionality has started 
    

    // @TODO: Call the function fc_compute() (fc_layer_functions.hpp).
    //  note: this can be done because we have access to the entire data
    //  set. Start thinking about how you would have to split computation
    //  when only portions of the dataset can be accessed by the compute
    //  process. It will become very useful later in the semester.

    wait();

    // @TODO: Flag to the increment counter process through internal flag signal
    // that compute functionality is done
    
    REPORT_INFO("COMPUTE DONE");

    // @TODO: Flag that the process_compute is done.

    // Reset restarts the SC_THREAD.
    do {
        wait();
    } while (true);
}

void fc_layer::process_store(void) {
    // @TODO: Implement the reset here.

    // @TODO: Wait for the process_config to be done.

    // @TODO: --> Wait for the process_compute to be done.
    
    // @TODO: Flag to the increment counter process through internal flag signal
    // that store functionality started and syncronize by waiting

    // @TODO: Send the data by using the function put()
    //  on the output channel of the fc_layer module. 

    wait();

    // @TODO: Flag to the increment counter process through internal flag signal
    // that store functionality is done

    REPORT_INFO("STORE DONE");
 
    // @TODO: If performance monitoring is enabled, then report the performance counter values for all 3 counters
    
  
    // @TODO: Flag that the module is done (irq_o).
  
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
