#ifndef SRC_CALCULATOR_USER_APP_H_
#define SRC_CALCULATOR_USER_APP_H_

#include <stdint.h>
#include "protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

uint8_t app_init();
uint32_t app_inputs_size();
uint32_t app_model_size();
ModelInfo app_model_info();
void app_nn_free();
float* app_run_inference(float* sample);

#ifdef __cplusplus
}
#endif

#endif /* SRC_CALCULATOR_USER_APP_H_ */
