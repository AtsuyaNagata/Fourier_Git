#include <iostream>
#include <string>
#include "Fourier_Lib/Fourier.h"
#include "FileSystem/csvFile.h"
#include "Wave_Lib/CreateWave.h"
using namespace std;

#define MAX_FUNC 5
#define PI 3.1415926535
#define FOR(x) for(int i = 0; i < x; ++i)

double a_Sin(double t) {
	return sin(2 * PI * t);
}
double b_Sin(double t) {
	return sin(2 * PI * t);
}
double c_Sin(double t) {
	return sin(2 * PI * t);
}
double d_Sin(double t) {
	return sin(4 * PI * t);
}
double e_Sin(double t) {
	return sin(2 * PI * t);
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
	csvFile f("SampleCsv.csv");

	if (!f.data()) {
		return 1;
	}

	double (*func[5])(double t) = { a_Sin , b_Sin , c_Sin , d_Sin , e_Sin };
	//第一引数には関数ポインタを入れてやる
	Array2D<double> Data = getWaveData(func[0], 0.0, 5.0, 1.0 / 10);

	double* fourierData;
	fourierData = new double[Data.getHeight()];
	FOR(Data.getHeight()) {
		fourierData[i] = Data(0, i);
	}

	Fourier fourier(fourierData, Data.getHeight()* Data.getWidth());

	double* restoreFunc = new double[fourier.size()];
	for (int i = 0; i < fourier.size(); ++i) {
		restoreFunc[i] = 0.0;
		const double* CkVal = fourier.CkValue(), *CkRang = fourier.CkValue();
		for (int j = 0; j < fourier.size(); ++j) {
			restoreFunc[i] += CkVal[j] * cos(CkRang[j] + 2 * PI / fourier.size() * i * j);
			printf("%lf  ", restoreFunc[i]);
		}
	}
	csvFile::csvWrite("outPut.csv", fourierData, fourier.size());

	return 0;
}
