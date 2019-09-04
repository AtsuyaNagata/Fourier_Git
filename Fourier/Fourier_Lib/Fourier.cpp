#include "Fourier.h"
#include <iostream>

#define PI 3.14159265

using namespace std;

///i�͕��ʂ̃C���f�b�N�X�ŁAm�̓r�b�g��
int reverseIndex(int index, int m) {
	int t = 0;
	//�r�b�g���]����
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


//FFT�̊֐��B���̊֐���p���ĐU���X�y�N�g��������g���X�y�N�g�������\�z����
void Fourier::FFT(const double* data, int size) {
	//M�̓f�[�^������̎��̃r�b�g���B-1�ɂ���āA�Ⴆ��128�̗v�f������������0����127�̐������Əo����
	unsigned int M = log2(mSize - 1) + 1; int r = 0;
	//data�̒��g���N���X�̒��Ɏ������(�C���f�b�N�X���r�b�g�t���Ŋi�[)
	for (int i = 0; i < mSize; ++i) {
		CkSin[i] = 0;
		if ((r = reverseIndex(i, M)) > size) {
			CkCos[i] = 0;
		}
		else {
			CkCos[i] = data[r];
		}
		//�����l�̓r�b�g�t���Ȓl
	}

	//step��2���X�e�b�v������Z��������
	int step = 1;
	//M��N��\������̂ɕK�v�ȃr�b�g���B���̃��[�v�\����O(logN * N)�ɂȂ鏊�Ȃł���
	for (int i = 0; i < M; ++i) {
		//���̃^�C�~���O��step��{�ɂ��邱�ƂŌW���̐�����v�����A�ŏ���2�A����4�A8�A16�A...�ƂȂ�\�����������Ă�
		step *= 2;
		//�\�ߕK�v�ȌW�����v�Z���Ă����B�W���̐���step��1/2�{
		for (int j = 0; j < step / 2; ++j) {
			//�v�Z W(kn N) = exp(-j2��/N * kn)���Q�l��W(j step)������
			Wsin[j] = sin(2 * PI * (double)j / step);
			Wcos[j] = cos(2 * PI * (double)j / step);
		}

		//������for����2�d�ɂ��Ă���̂ŁAo(N^2)�̏��������Ă���l�Ɍ����邪�A
		//���ۂ͒i�K���c�ɋ�؂鏈���������Ă邾���Ȃ̂ŁAO(N)���̌v�Z�ʂł���
		for (int k = 0; k < mSize; k += step) {
			for (int j = step / 2; j < step; ++j) {
				//�o�^�t���C�̏㑤�������C���f�b�N�X�l
				int upBuff = k + j - (step / 2);
				//�o�^�t���C�̉����������C���f�b�N�X�l
				int downBuff = k + j;
				//�|����W���������C���f�b�N�X
				int Wbuff = j - (step / 2);

				//���o�^�t���C�I�Ȍv�Z�̊J�n�n�_ (cos�͎������Asin�͋��������������Ă���)
				//4��̊|���Z��2��̉��Z
				double WXcosBuf = CkCos[downBuff] * Wcos[Wbuff] - CkSin[downBuff] * Wsin[Wbuff];
				double WXsinBuf = CkCos[downBuff] * Wsin[Wbuff] + CkSin[downBuff] * Wcos[Wbuff];

				//2�̗v�f��p����2�̗v�f���X�V����
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
		mCkValue[i] = sqrt(CkSin[i] * CkSin[i] + CkCos[i] * CkCos[i]);	//��(Cksin^2 + Ckcos^2)
		mCkRange[i] = atan2(CkSin[i], CkCos[i]);	//tan^-1(y/x)
	}
}



//�l�̏�����
//���̃R�[�h��ǂލۂɂ́A�o�^�t���C�̐}���Q�Ƃ��Ȃ��猩�鎖���������߂���]�I
Fourier::Fourier(const double* data, int size) :
	mSize(0), mDifference(0),
	mCkValue(0), mCkRange(0),
	CkSin(0), CkCos(0),
	Wsin(0), Wcos(0)
{
	mSize = pow(2, (int)(log2(size - 1) + 1));
	mDifference = mSize - size;

	//double�̃f�[�^���󂯎��
	mCkValue = new double[mSize];
	mCkRange = new double[mSize];

	//Ck��sin������cos�����ɕ����Čv�Z���� (�������I�ȈӖ��͋��������Ǝ��������Ă��ƂȂ�Œ��ӂ��ĂˁI)
	CkSin = new double[mSize];
	CkCos = new double[mSize];

	//�v�Z�����ȗ����邽�߂ɕK�v�Ȕz���\�ߐ錾���Ă���[W(kn N) = exp(-j2��/N * kn)]
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

	//double�̃f�[�^���󂯎��
	mCkValue = new double[mSize];
	mCkRange = new double[mSize];

	//Ck��sin������cos�����ɕ����Čv�Z���� (�������I�ȈӖ��͋��������Ǝ��������Ă��ƂȂ�Œ��ӂ��ĂˁI)
	CkSin = new double[mSize];
	CkCos = new double[mSize];

	//�v�Z�����ȗ����邽�߂ɕK�v�Ȕz���\�ߐ錾���Ă���[W(kn N) = exp(-j2��/N * kn)]
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
		//���T�C�Y���K�v
		//��x���ׂĔj��
		delete[] mCkValue;
		delete[] mCkRange;
		delete[] CkSin;
		delete[] CkCos;
		delete[] Wsin;
		delete[] Wcos;
		mCkValue = 0; mCkRange = 0; CkSin = 0; CkCos = 0; Wsin = 0; Wcos = 0;

		//���T�C�Y
		mSize = pow(2, (int)(log2(size - 1) + 1));
		mDifference = mSize - size;

		//double�̃f�[�^�̎󂯎M�̊l��
		mCkValue = new double[mSize];
		mCkRange = new double[mSize];

		//Ck��sin������cos�����ɕ����Čv�Z���� (�������I�ȈӖ��͋��������Ǝ��������Ă��ƂȂ�Œ��ӂ��ĂˁI)
		CkSin = new double[mSize];
		CkCos = new double[mSize];

		//�v�Z�����ȗ����邽�߂ɕK�v�Ȕz���\�ߐ錾���Ă���[W(kn N) = exp(-j2��/N * kn)]
		Wsin = new double[mSize / 2];
		Wcos = new double[mSize / 2];

		FFT(data, size);
	}
}

//�^����ꂽ�ԍ��̒l��Ԃ�
double Fourier::CkValue(int n) const {
	if (mSize > n) {
		return mCkValue[n];
	}
	else {
		_RPT0(_CRT_WARN, "Fourier error : �͈͊O�w��͂܂����ł���I");
	}
	return 0;
}

double Fourier::CkRange(int n) const {
	if (mSize > n) {
		return mCkRange[n];
	}
	else {
		_RPT0(_CRT_WARN, "Fourier error : �͈͊O�w��͂܂����ł���I");
	}
	return 0;
}

void Fourier::operator=(Fourier &f) {
	if(mSize == f.mSize){

	}
	else {
		mSize = f.mSize;

		//���T�C�Y���K�v
		//��x���ׂĔj��
		delete[] mCkValue;
		delete[] mCkRange;
		delete[] CkSin;
		delete[] CkCos;
		delete[] Wsin;
		delete[] Wcos;
		mCkValue = 0; mCkRange = 0; CkSin = 0; CkCos = 0; Wsin = 0; Wcos = 0;

		//�č\�z
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


/*	DFT�v���O����
	for (int i = 0; i < mSize; ++i) {
		CkSin[i] = 0;
		CkCos[i] = 0;
		for (int j = 0; j < mSize; ++j) {
			CkSin[i] += data[j] * -(sin((2 * PI / mSize) * i * j));
			CkCos[i] += data[j] * cos((2 * PI / mSize) * i * j);
		}
		CkSin[i] /= mSize;
		CkCos[i] /= mSize;
		mCkValue[i] = sqrt(CkSin[i] * CkSin[i] + CkCos[i] * CkCos[i]);	//��(Cksin^2 + Ckcos^2)
		mCkRange[i] = atan2(CkSin[i], CkCos[i]);	//tan^-1(y/x)
	}
	*/