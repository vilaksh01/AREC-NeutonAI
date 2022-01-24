#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	uint16_t rowsCount;         // Rows count in result
	uint16_t taskType;          // Task type
}
ModelInfo;

typedef struct
{
	float usSampleMin;      // Minimum calculating time per sample
	float usSampleMax;      // Maximum calculating time per sample
	float usSampleAvg;      // Average calculating time per sample
	uint32_t ramUsageCur;   // Current RAM usage, bytes
	uint32_t ramUsage;      // Total RAM usage, bytes
	uint32_t bufferSize;    // IO buffer size, bytes
	uint32_t flashUsage;    // Model size in flash, bytes
	uint32_t freq;          // CPU frequency, Hz
}
PerformanceReport;

#ifdef __cplusplus
}
#endif

#endif // PROTOCOL_H
