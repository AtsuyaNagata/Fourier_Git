#include "Fourier.h"
#include <iostream>

#define PI 3.14159265

using namespace std;

///iは普通のインデックスで、mはビット数
int reverseIndex(int index, int m) {
	int t = 0;
	//ビット反転処理
	for (int i = m - 1; i >= 0; --i) {
		t |= (0x00000001 & (index >> i)) << (m - 1) - i;
	}
	return t;
}

Fourier::Fourier() :
	mSize(0), mDifference(0),
	mCkValue(0), mCkRange(0),
	CkSin(0), CkCos(0),
	Wsin(0), Wcos(0) {}


//FFTの関数。この関数を用いて振幅スペクトラムや周波数スペクトラムを構築する
void Fourier::FFT(const double* data, int size) {
	//Mはデータ数上限の時のビット数。-1によって、例えば128個の要素があった時に0から127の数字だと出来る
	unsigned int M = log2(mSize - 1) + 1; int r = 0;
	//dataの中身をクラスの中に取り入れる(インデックスをビット逆順で格納)
	for (int i = 0; i < mSize; ++i) {
		CkSin[i] = 0;
		if ((r = reverseIndex(i, M)) > size) {
			CkCos[i] = 0;
		}
		else {
			CkCos[i] = data[r];
		}
		//初期値はビット逆順な値
	}

	//stepは2をステップ数分乗算したもの
	int step = 1;
	//MはNを表現するのに必要なビット数。このループ表現がO(logN * N)になる所以である
	for (int i = 0; i < M; ++i) {
		//このタイミングでstepを倍にすることで係数の数を一致させつつ、最初が2、次は4、8、16、...となる表現を実現してる
		step *= 2;
		//予め必要な係数を計算しておく。係数の数はstepの1/2倍
		for (int j = 0; j < step / 2; ++j) {
			//計算 W(kn N) = exp(-j2π/N * kn)を参考にW(j step)を実装
			Wsin[j] = sin(2 * PI * (double)j / step);
			Wcos[j] = cos(2 * PI * (double)j / step);
		}

		//ここでfor文を2重にしているので、o(N^2)の処理をしている様に見えるが、
		//実際は段階を縦に区切る処理が入ってるだけなので、O(N)分の計算量である
		for (int k = 0; k < mSize; k += step) {
			for (int j = step / 2; j < step; ++j) {
				//バタフライの上側を示すインデックス値
				int upBuff = k + j - (step / 2);
				//バタフライの下側を示すインデックス値
				int downBuff = k + j;
				//掛ける係数を示すインデックス
				int Wbuff = j - (step / 2);

				//＊バタフライ的な計算の開始地点 (cosは実成分、sinは虚数成分を示している)
				//4回の掛け算と2回の加算
				double WXcosBuf = CkCos[downBuff] * Wcos[Wbuff] - CkSin[downBuff] * Wsin[Wbuff];
				double WXsinBuf = CkCos[downBuff] * Wsin[Wbuff] + CkSin[downBuff] * Wcos[Wbuff];

				//2つの要素を用いて2つの要素を更新する
				CkSin[downBuff] = CkSin[upBuff] - WXsinBuf;
				CkCos[downBuff] = CkCos[upBuff] - WXcosBuf;
				CkSin[upBuff] = CkSin[upBuff] + WXsinBuf;
				CkCos[upBuff] = CkCos[upBuff] + WXcosBuf;
			}
		}
	}

	for (int i = 0; i < mSize; ++i) {
		CkSin[i] /= (double)mSize;
		CkCos[i] /= (double)mSize;
		mCkValue[i] = sqrt(CkSin[i] * CkSin[i] + CkCos[i] * CkCos[i]);	//√(Cksin^2 + Ckcos^2)
		mCkRange[i] = atan2(CkSin[i], CkCos[i]);	//tan^-1(y/x)
	}
}



//値の初期化
//このコードを読む際には、バタフライの図を参照しながら見る事をおすすめするゾ！
Fourier::Fourier(const double* data, int size) :
	mSize(0), mDifference(0),
	mCkValue(0), mCkRange(0),
	CkSin(0), CkCos(0),
	Wsin(0), Wcos(0)
{
	mSize = pow(2, (int)(log2(size - 1) + 1));
	mDifference = mSize - size;

	//doubleのデータを受け取る
	mCkValue = new double[mSize];
	mCkRange = new double[mSize];

	//Ckをsin成分とcos成分に分けて計算する (＊実質的な意味は虚数成分と実成分ってことなんで注意してね！)
	CkSin = new double[mSize];
	CkCos = new double[mSize];

	//計算数を省略するために必要な配列を予め宣言しておく[W(kn N) = exp(-j2π/N * kn)]
	Wsin = new double[mSize / 2];
	Wcos = new double[mSize / 2];

	FFT(data, size);
}

Fourier::Fourier(int size) :
	mSize(0), mDifference(0),
	mCkValue(0), mCkRange(0),
	CkSin(0), CkCos(0),
	Wsin(0), Wcos(0)
{
	mSize = pow(2, (int)(log2(size - 1) + 1));
	mDifference = mSize - size;

	//doubleのデータを受け取る
	mCkValue = new double[mSize];
	mCkRange = new double[mSize];

	//Ckをsin成分とcos成分に分けて計算する (＊実質的な意味は虚数成分と実成分ってことなんで注意してね！)
	CkSin = new double[mSize];
	CkCos = new double[mSize];

	//計算数を省略するために必要な配列を予め宣言しておく[W(kn N) = exp(-j2π/N * kn)]
	Wsin = new double[mSize / 2];
	Wcos = new double[mSize / 2];

}

Fourier::~Fourier()
{
	delete[] mCkValue;
	delete[] mCkRange;
	delete[] CkSin;
	delete[] CkCos;
	delete[] Wsin;
	delete[] Wcos;

	mCkValue = 0; mCkRange = 0; CkSin = 0; CkCos = 0; Wsin = 0; Wcos = 0;
}

void Fourier::update(const double* data, int size)
{
	if (mSize == pow(2, (int)(log2(size - 1) + 1))) {
		FFT(data, size);
	}
	else {
		//リサイズが必要
		//一度すべて破壊
		delete[] mCkValue;
		delete[] mCkRange;
		delete[] CkSin;
		delete[] CkCos;
		delete[] Wsin;
		delete[] Wcos;
		mCkValue = 0; mCkRange = 0; CkSin = 0; CkCos = 0; Wsin = 0; Wcos = 0;

		//リサイズ
		mSize = pow(2, (int)(log2(size - 1) + 1));
		mDifference = mSize - size;

		//doubleのデータの受け皿の獲得
		mCkValue = new double[mSize];
		mCkRange = new double[mSize];

		//Ckをsin成分とcos成分に分けて計算する (＊実質的な意味は虚数成分と実成分ってことなんで注意してね！)
		CkSin = new double[mSize];
		CkCos = new double[mSize];

		//計算数を省略するために必要な配列を予め宣言しておく[W(kn N) = exp(-j2π/N * kn)]
		Wsin = new double[mSize / 2];
		Wcos = new double[mSize / 2];

		FFT(data, size);
	}
}

//与えられた番号の値を返す
double Fourier::CkValue(int n) const {
	if (mSize > n) {
		return mCkValue[n];
	}
	else {
		_RPT0(_CRT_WARN, "Fourier error : 範囲外指定はまずいですよ！");
	}
	return 0;
}

double Fourier::CkRange(int n) const {
	if (mSize > n) {
		return mCkRange[n];
	}
	else {
		_RPT0(_CRT_WARN, "Fourier error : 範囲外指定はまずいですよ！");
	}
	return 0;
}

void Fourier::operator=(Fourier &f) {
	if(mSize == f.mSize){

	}
	else {
		mSize = f.mSize;

		//リサイズが必要
		//一度すべて破壊
		delete[] mCkValue;
		delete[] mCkRange;
		delete[] CkSin;
		delete[] CkCos;
		delete[] Wsin;
		delete[] Wcos;
		mCkValue = 0; mCkRange = 0; CkSin = 0; CkCos = 0; Wsin = 0; Wcos = 0;

		//再構築
		mCkValue = new double[mSize];
		mCkRange = new double[mSize];
		CkSin = new double[mSize];
		CkCos = new double[mSize];
		Wsin = new double[mSize / 2];
		Wcos = new double[mSize / 2];
	}

	mDifference = f.mDifference;

	memcpy(mCkValue, f.mCkValue, (mSize * 8));
	memcpy(mCkRange, f.mCkRange, (mSize * 8));
	memcpy(CkSin, f.mCkValue, (mSize * 8));
	memcpy(CkCos, f.mCkRange, (mSize * 8));
	memcpy(Wsin, f.mCkValue, (mSize * 4));
	memcpy(Wcos, f.mCkRange, (mSize * 4));

	return;
}


/*	DFTプログラム
	for (int i = 0; i < mSize; ++i) {
		CkSin[i] = 0;
		CkCos[i] = 0;
		for (int j = 0; j < mSize; ++j) {
			CkSin[i] += data[j] * -(sin((2 * PI / mSize) * i * j));
			CkCos[i] += data[j] * cos((2 * PI / mSize) * i * j);
		}
		CkSin[i] /= mSize;
		CkCos[i] /= mSize;
		mCkValue[i] = sqrt(CkSin[i] * CkSin[i] + CkCos[i] * CkCos[i]);	//√(Cksin^2 + Ckcos^2)
		mCkRange[i] = atan2(CkSin[i], CkCos[i]);	//tan^-1(y/x)
	}
	*/