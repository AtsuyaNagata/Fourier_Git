#include "Fourier.h"
#include "FileSystem/File.h"
#include <iostream>
using namespace std;

//値の初期化
Fourier::Fourier(double *data):
	mData(0), mSize(0),
	mCkValue(0), mCkRange(0)
{
	//doubleのデータを受け取る
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
		_RPT0(_CRT_WARN, "Fourier error : 範囲外指定はまずいですよ！");
	}
}

double Fourier::CkRange(int n) const {
	if (mSize > n) {
		return mCkRange[n];
	}
	else {
		_RPT0(_CRT_WARN, "Fourier error : 範囲外指定はまずいですよ！");
	}
}