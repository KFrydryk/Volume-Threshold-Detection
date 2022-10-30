#include "include/low-pass-Filter.h"

/*
 *
 * FIR filter designed with
 * http://t-filter.appspot.com
 *
 * sampling frequency: 1536000 Hz
 *
 * fixed point precision: 16 bits
 *
 * 0 Hz - 20000 Hz
 * gain = 1
 * desired ripple = 5 dB
 * actual ripple = n/a
 *
 * 48000 Hz - 768000 Hz
 * gain = 0
 * desired attenuation = -40 dB
 * actual attenuation = n/a
 *
 */

static int filter_taps[LOW_PASS_FILTER_TAP_NUM] = {
 -156,
  17,
  22,
  32,
  45,
  62,
  83,
  108,
  137,
  170,
  207,
  248,
  292,
  340,
  390,
  444,
  500,
  558,
  617,
  677,
  738,
  798,
  857,
  914,
  969,
  1022,
  1070,
  1115,
  1154,
  1189,
  1218,
  1241,
  1257,
  1267,
  1271,
  1267,
  1257,
  1241,
  1218,
  1189,
  1154,
  1115,
  1070,
  1022,
  969,
  914,
  857,
  798,
  738,
  677,
  617,
  558,
  500,
  444,
  390,
  340,
  292,
  248,
  207,
  170,
  137,
  108,
  83,
  62,
  45,
  32,
  22,
  17,
  -156
};

void low_pass_Filter_init(low_pass_Filter* f) {
  int i;
  for(i = 0; i < LOW_PASS_FILTER_TAP_NUM; ++i)
    f->history[i] = 0;
  f->last_index = 0;
}

void low_pass_Filter_put(low_pass_Filter* f, int input) {
  f->history[f->last_index++] = input;
  if(f->last_index == LOW_PASS_FILTER_TAP_NUM)
    f->last_index = 0;
}

int low_pass_Filter_get(low_pass_Filter* f) {
  long long acc = 0;
  int index = f->last_index, i;
  for(i = 0; i < LOW_PASS_FILTER_TAP_NUM; ++i) {
    index = index != 0 ? index-1 : LOW_PASS_FILTER_TAP_NUM-1;
    acc += (long long)f->history[index] * filter_taps[i];
  };
  return acc >> 16;
}
