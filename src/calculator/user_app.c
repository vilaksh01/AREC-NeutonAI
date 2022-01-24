#include "neuton/calculator.h"
#include <string.h>
#include "user_app.h"
#include "timer.h"

static NeuralNet neuralNet = { 0 };
static uint32_t memUsage = 0;
static float usSample = 0;

extern const unsigned char model_bin[];
extern const unsigned int model_bin_len;

#if defined(NEUTON_MEMORY_BENCHMARK)
uint32_t _NeutonExtraMemoryUsage()
{
	return memUsage;
}
#endif


uint8_t app_init()
{
	return (ERR_NO_ERROR != CalculatorInit(&neuralNet, NULL));
}



inline Err CalculatorOnInit(NeuralNet* neuralNet)
{
	memUsage += sizeof(*neuralNet);
	timer_init();
	return CalculatorLoadFromMemory(neuralNet, model_bin, model_bin_len, 0);
}

inline void app_nn_free()
{
	CalculatorFree(&neuralNet);
} 

inline void CalculatorOnFree(NeuralNet* neuralNet)
{

}


inline Err CalculatorOnLoad(NeuralNet* neuralNet)
{
	return ERR_NO_ERROR;
}


inline Err CalculatorOnRun(NeuralNet* neuralNet)
{
	return ERR_NO_ERROR;
}


inline void CalculatorOnInferenceStart(NeuralNet* neuralNet)
{
	timer_start();

}


inline void CalculatorOnInferenceEnd(NeuralNet* neuralNet)
{
	timer_stop();
	usSample = timer_value_us();

}

inline uint32_t app_model_size()
{
	return model_bin_len;
}

inline uint32_t app_inputs_size()
{
	return neuralNet.inputsDim;
}

inline ModelInfo app_model_info()
{
	ModelInfo info;

	info.rowsCount = neuralNet.outputsDim;
	info.taskType = neuralNet.taskType;

	return info;
}

inline float* app_run_inference(float* sample)
{
	/**if (!sample || !size_out)
		return NULL;

	if (size_in / sizeof(float) != app_inputs_size())
		return NULL;

	*size_out = sizeof(float) * neuralNet.outputsDim;**/

	return CalculatorRunInference(&neuralNet, sample);
}


inline void CalculatorOnInferenceResult(NeuralNet* neuralNet, float* result)
{
	
}
