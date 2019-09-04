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

//���������}1�̋�`�g
double a_function(double t) {
	if (2.5 <= t && t < 5.0) {
		return 1;
	}
	else {
		return 0;
	}
}

//���������}1�̃m�R�M���g
double b_function(double t) {
	return 1.0 / 5.0 * t;
}

//�s���̂����}1�g�`
double s_a_function(double t) {
	if (2.56 <= t && t < 5.12) {
		return 1;
	}
	else {
		return 0;
	}
}

//�g���T���v�����O�����f�[�^�𐶐�����
Array2D<double> getWaveData(double (*func)(double), double minT, double maxT, double SamplingT) {
	//�w�肵���͈͂��T���v�����O���g���Ŋ����ĕW�{�������f�[�^�ɂ���
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
	//�������ɂ͊֐��|�C���^�����Ă��
	Array2D<double> Data = getWaveData(a_Sin, 0.0, 5.12, 1.0 / 50);
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
	for (int i = 0; i < fourier.size() - fourier.difference(); ++i) {
		restoreFunc[i] = 0.0;
		for (int j = 0; j < fourier.size(); ++j) {
			restoreFunc[i] += fourier.CkValue()[j] * cos(fourier.CkRange()[j] + 2 * PI / (double)fourier.size() * (double)i * (double)j);
			//printf("%lf  ", fourier.CkValue()[i]);
		}
	}



	//��Â������͏o���Ȃ�
	//csvFile::csvWrite("outPut.csv", fourier.CkRange(), fourier.size());
	//csvFile::csvWrite("outPut.csv", fourier.CkValue(), fourier.size());
	csvFile::csvWrite("outPut.csv", restoreFunc, fourier.size());
	//csvFile::csvWrite("outPut.csv", Data2);

	return 0;
}

