#include "Fourier.h"
#include "FileSystem/File.h"
#include <iostream>

#define PI 3.14159265

using namespace std;

//値の初期化
Fourier::Fourier(double *data, int size):
	mData(0), mSize(0),
	mCkValue(0), mCkRange(0)
{
	//doubleのデータを受け取る
	mSize = size;
	mData		=	new double[mSize];
	mCkValue	=	new double[mSize];
	mCkRange	=	new double[mSize];
	memcpy(mData, data, mSize);			//dataの中身をクラスの中に取り入れる

	//Ckをsin成分とcos成分に分けて計算する
	double *CkSin = new double[mSize];
	double* CkCos = new double[mSize];

	for (int i = 0; i < mSize; ++i) {
		CkSin[i] = 0;
		CkCos[i] = 0;
		for (int j = 0; j < mSize; ++j) {
			CkSin[i] += mData[j] * -(sin(2 * PI / mSize * i * j));
			CkCos[i] += mData[j] * cos(2 * PI / mSize * i * j);
		}
		CkSin[i] /= mSize;
		CkCos[i] /= mSize;

		mCkValue[i] = sqrt(CkSin[i] * CkSin[i] + CkCos[i] * CkCos[i]);	//√(Cksin^2 + Ckcos^2)
		mCkRange[i] = atan2(CkSin[i], CkCos[i]);	//tan^-1(y/x)
	}

	
}


Fourier::~Fourier()
{
	delete[] mData;
	delete[] mCkValue;
	delete[] mCkRange;

	mData = 0; mCkValue = 0; mCkRange = 0;
}

//与えられた番号の値を返す
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