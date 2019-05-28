#include "Wave_Lib/CreateWave.h"

CreateWave::CreateWave(double (*func)(double)):
	mFunc(0)
{
	mFunc = func;
}

//解放は呼び出した側が管理する
Array2D<double> CreateWave::getWaveData(double (*func)(double), double minT, double maxT, double SamplingT) {
	//指定した範囲をサンプリング周波数で割って標本化したデータにする
	int size = (int)((maxT - minT) / SamplingT) + 1;
	Array2D<double> waveData;
	waveData.setSize(2, size);

	for (int i = 0; i < size; ++i) {
		//double mFunc(T)  :  Tは時間
		waveData(0, i) = SamplingT * i;
		waveData(1, i) = (*func)(minT + (i * SamplingT));
	}
	return waveData;
}