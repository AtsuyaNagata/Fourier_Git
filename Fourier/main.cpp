#include <iostream>
#include <string>
#include "Fourier_Lib/Fourier.h"
#include "FileSystem/csvFile.h"
#include "Wave_Lib/CreateWave.h"
using namespace std;

#define PI 3.1415926535
#define FOR(x) for(int i = 0; i < x; ++i)

double a_Sin(double t) {
	return 2 * sin(2 * PI * t);
}
double d_Sin(double t) {
	return sin(4 * PI * t);
}

//実験資料図1の矩形波
double a_function(double t) {
	if (2.5 <= t && t < 5.0) {
		return 1;
	}
	else {
		return 0;
	}
}

//実験資料図1のノコギリ波
double b_function(double t) {
	return 1.0 / 5.0 * t;
}

//都合のいい図1波形
double s_a_function(double t) {
	if (2.56 <= t && t < 5.12) {
		return 1;
	}
	else {
		return 0;
	}
}

//波をサンプリングしたデータを生成する
Array2D<double> getWaveData(double (*func)(double), double minT, double maxT, double SamplingT) {
	//指定した範囲をサンプリング周波数で割って標本化したデータにする
	int size = (int)((maxT - minT) / SamplingT);
	Array2D<double> waveData;
	waveData.setSize(1, size);

	for (int i = 0; i < size; ++i) {
		waveData(0, i) = (*func)(minT + (i * SamplingT));
	}
	return waveData;
}

int main()
{
	//第一引数には関数ポインタを入れてやる
	Array2D<double> Data = getWaveData(s_a_function, 0.0, 5.13, 1.0 / 100);
	//Array2D<double> Data2 = getWaveData(a_function, 0.0, 5.0, 1.0 / 50);

	double* fourierData;
	fourierData = new double[Data.getHeight()];
	FOR(Data.getHeight()) {
		fourierData[i] = Data(0, i);
	}

	Fourier fourier(fourierData, Data.getHeight());

	/*FOR(Data2.getHeight()) {
		fourierData[i] = Data2(0, i);
	}
	fourier.update(fourierData, Data2.getHeight());
	*/

	double* restoreFunc = new double[fourier.size()];
	for (int i = 0; i < fourier.size(); ++i) {
		restoreFunc[i] = 0.0;
		for (int j = 0; j < fourier.size(); ++j) {
			restoreFunc[i] += fourier.CkValue()[j] * cos(fourier.CkRange()[j] + 2 * PI / (double)fourier.size() * (double)i * (double)j);
			//printf("%lf  ", fourier.CkValue()[i]);
		}
	}



	//一つづつしか今は出来ない
	//csvFile::csvWrite("outPut.csv", fourier.CkRange(), fourier.size());
	//csvFile::csvWrite("outPut.csv", fourier.CkValue(), fourier.size());
	csvFile::csvWrite("outPut.csv", restoreFunc, fourier.size());
	//csvFile::csvWrite("outPut.csv", Data2);

	return 0;
}

