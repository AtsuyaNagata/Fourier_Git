#include "Wave_Lib/CreateWave.h"

CreateWave::CreateWave(double (*func)(double)):
	mFunc(0)
{
	mFunc = func;
	
}

//����͌Ăяo���������Ǘ�����
double* CreateWave::getWaveData(double minT, double maxT, double SamplingT) {
	//�w�肵���͈͂��T���v�����O���g���Ŋ����ĕW�{�������f�[�^�ɂ���
	int size = (int)((maxT - minT) / SamplingT) + 1;
	double* waveData = new double[size];

	for (int i = 0; i < size; ++i) {
		//double mFunc(T)  :  T�͎���
		waveData[i] = (*mFunc)(minT + (i * SamplingT));
	}
	return waveData;
}