#ifndef GRAND_FOURIER_H_
#define GRAND_FOURIER_H_

class Fourier
{
public:
	//double�̃f�[�^���󂯎���Ă�����g���ig(n)���󂯎��j
	Fourier(const double* data, int size);
	Fourier();
	~Fourier();

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

	//�u=�v�̏���
	void operator=(Fourier f);

	int size() {
		return mSize;
	}

private:
	//�f�[�^�Ɋւ���ϐ�
	double* mData;
	int mSize;

	//mCk�̒l�Ɗp�x
	double *mCkValue;
	double *mCkRange;
};

#endif