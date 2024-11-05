#ifndef __FC_LAYER_FUNCTIONS_H__
#define __FC_LAYER_FUNCTIONS_H__

#include <cmath>

void fc_compute(float *dst, float *src, float *w, float *b, int w_cols, int w_rows) {
    // @TODO: Implement the function fc_compute.
    //  hint: as indicated in the assignment, you
    //  should check out the code in pv/mojo/dwarf.h.

    for (int j = 0; j < w_rows; j++) {
        const int w_index = j * w_cols;
        dst[j] = 0;
        for (int i = 0; i < w_cols; i++) {
            dst[j] += src[i] * w[w_index + i];
        }
        
        if (dst[j] + b[j] < 0)
            dst[j] = 0;
        else
            dst[j] += b[j];
    }
}

#endif // __FC_LAYER_FUNCTIONS_H__
