#ifndef GRAND_FOURIER_H_
#define GRAND_FOURIER_H_

class Fourier
{
public:
	//double�̃f�[�^���󂯎���Ă�����g��
	Fourier(double *data);
	~Fourier();

	//�ʒu�w������ē���̃f�[�^���󂯎��
	double CkValue(int) const;
	double CkRange(int) const;

	//�|�C���^�ł�������󂯎��
	const double const * CkValue() const {
		return mCkValue;
	}
	const double const * CkRange() const {
		return mCkRange;
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