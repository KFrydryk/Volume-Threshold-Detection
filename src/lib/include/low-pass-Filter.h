#ifndef LOW_PASS_FILTER_H_
#define LOW_PASS_FILTER_H_

/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 1536000 Hz

fixed point precision: 16 bits

* 0 Hz - 20000 Hz
  gain = 1
  desired ripple = 5 dB
  actual ripple = n/a

* 48000 Hz - 768000 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a

*/

#define LOW_PASS_FILTER_TAP_NUM 69

typedef struct {
  int history[LOW_PASS_FILTER_TAP_NUM];
  unsigned int last_index;
} low_pass_Filter;

void low_pass_Filter_init(low_pass_Filter* f);
void low_pass_Filter_put(low_pass_Filter* f, int input);
int low_pass_Filter_get(low_pass_Filter* f);

#endif