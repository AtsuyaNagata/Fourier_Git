#ifndef _WAVE_LIB_CREATE_WAVE_H_
#define _WAVE_LIB_CREATE_WAVE_H_

#include "Array2D.h"

class CreateWave {
public:
	CreateWave(double (*func)(double));
	~CreateWave();

	static Array2D<double> getWaveData(double (*func)(double), double minT, double maxT, double SamplingT);

private:
	double (*mFunc)(double);
	
};

#endif