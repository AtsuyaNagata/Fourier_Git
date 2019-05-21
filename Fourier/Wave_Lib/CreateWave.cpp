#include "Wave_Lib/CreateWave.h"

CreateWave::CreateWave(double (*func)(double)):
	mFunc(0)
{
	mFunc = func;
	
}

//解放は呼び出した側が管理する
double* CreateWave::getWaveData(double minT, double maxT, double SamplingT) {
	//指定した範囲をサンプリング周波数で割って標本化したデータにする
	int size = (int)((maxT - minT) / SamplingT) + 1;
	double* waveData = new double[size];

	for (int i = 0; i < size; ++i) {
		//double mFunc(T)  :  Tは時間
		waveData[i] = (*mFunc)(minT + (i * SamplingT));
	}
	return waveData;
}