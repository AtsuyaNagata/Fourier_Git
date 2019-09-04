#ifndef GRAND_FOURIER_H_
#define GRAND_FOURIER_H_

class Fourier
{
public:
	//double�̃f�[�^���󂯎���Ă�����g���ig(n)���󂯎��j
	Fourier(const double* data, int size);
	Fourier(int size);
	Fourier();
	~Fourier();

	//�t�[���G�ϊ�����f�[�^�̍X�V
	void update(const double* data, int size);

	//FFT�֐�
	void FFT(const double* data, int size);

	//�ʒu�w������ē���̃f�[�^���󂯎��
	double CkValue(int) const;
	double CkRange(int) const;

	//�|�C���^�ł�������󂯎��
	const double* const CkValue() const {
		return mCkValue;
	}
	const double* const CkRange() const {
		return mCkRange;
	}
	const int difference() const {
		return mDifference;
	}

	//�u=�v�̏���
	void operator=(Fourier &f);

	int size() {
		return mSize;
	}

private:
	//�f�[�^�Ɋւ���ϐ�
	int mSize;
	//2�ׂ̂���Ǝ󂯎�����f�[�^�̍���
	int mDifference;

	//mCk�̒l�Ɗp�x
	double* mCkValue;
	double* mCkRange;

	//�Ԃ����Ƃ͖������ǁA�v�Z���ԒZ�k�̂��߂ɂ����Ő錾���Ă��������o�ϐ��Q
	double* CkSin;
	double* CkCos;
	double* Wsin;
	double* Wcos;
};

#endif