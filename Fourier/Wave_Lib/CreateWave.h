#ifndef WAVE_LIB_CREATE_WAVE_H_
#define WAVE_LIB_CREATE_WAVE_H_

class CreateWave {
public:
	CreateWave(double (*func)(double));
	~CreateWave();

	double* getWaveData(double minT, double maxT, double SamplingT);

private:
	double (*mFunc)(double);
	
};

#endif