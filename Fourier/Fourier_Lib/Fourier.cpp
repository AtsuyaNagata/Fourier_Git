#include "Fourier.h"
#include "FileSystem/File.h"
#include <iostream>
using namespace std;

//�l�̏�����
Fourier::Fourier(double *data):
	mData(0), mSize(0),
	mCkValue(0), mCkRange(0)
{
	//double�̃f�[�^���󂯎��
	mSize = sizeof(data);
	mData = new double[mSize];
	memcpy(mData, data, mSize);
}


Fourier::~Fourier()
{
	delete[] mData;
	delete[] mCkValue;
	delete[] mCkRange;

	mData = 0; mCkValue = 0; mCkRange = 0;
}

double Fourier::CkValue(int n) const {
	if (mSize > n) {
		return mCkValue[n];
	}
	else {
		_RPT0(_CRT_WARN, "Fourier error : �͈͊O�w��͂܂����ł���I");
	}
}

double Fourier::CkRange(int n) const {
	if (mSize > n) {
		return mCkRange[n];
	}
	else {
		_RPT0(_CRT_WARN, "Fourier error : �͈͊O�w��͂܂����ł���I");
	}
}