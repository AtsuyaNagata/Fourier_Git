#include <iostream>
#include <string>
#include "Fourier_Lib/Fourier.h"
#include "FileSystem/csvFile.h"
#include "Wave_Lib/CreateWave.h"
using namespace std;

#define PI 3.1415926535
#define FOR(x) for(int i = 0; i < x; ++i)

double sinPlusSin(double t) {
	return sin(t) + sin(2 * t);
}

//����͌Ăяo���������Ǘ�����
Array2D<double> getWaveData(double (*func)(double), double minT, double maxT, double SamplingT) {
	//�w�肵���͈͂��T���v�����O���g���Ŋ����ĕW�{�������f�[�^�ɂ���
	int size = (int)((maxT - minT) / SamplingT) + 1;
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

	Array2D<double> Data(getWaveData(sin, 0.0, 100 * PI, PI / 3));

	double* fourierData = new double[Data.getHeight()];
	FOR(Data.getHeight()) {
		fourierData[i] = Data(0, i);
	}

	Fourier fourie(fourierData, Data.getHeight()* Data.getWidth());

	FOR(fourie.size()) {
		printf("%lf��  ", (fourie.CkRange()[i] / PI));

	}

	csvFile::csvWrite("outPut.csv", fourie.CkValue(), fourie.size());

	return 0;
}
