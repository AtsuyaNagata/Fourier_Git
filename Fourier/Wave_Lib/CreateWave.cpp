#include "Wave_Lib/CreateWave.h"

CreateWave::CreateWave(double (*func)(double)):
	mFunc(0)
{
	mFunc = func;
}

//����͌Ăяo���������Ǘ�����
Array2D<double> CreateWave::getWaveData(double (*func)(double), double minT, double maxT, double SamplingT) {
	//�w�肵���͈͂��T���v�����O���g���Ŋ����ĕW�{�������f�[�^�ɂ���
	int size = (int)((maxT - minT) / SamplingT) + 1;
	Array2D<double> waveData;
	waveData.setSize(2, size);

	for (int i = 0; i < size; ++i) {
		//double mFunc(T)  :  T�͎���
		waveData(0, i) = SamplingT * i;
		waveData(1, i) = (*func)(minT + (i * SamplingT));
	}
	return waveData;
}