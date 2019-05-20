#ifndef GRAND_FOURIER_H_
#define GRAND_FOURIER_H_

class Fourier
{
public:
	//doubleのデータを受け取ってそれを使う
	Fourier(double *data);
	~Fourier();

	//位置指定をして特定のデータを受け取る
	double CkValue(int) const;
	double CkRange(int) const;

	//ポインタでごっそり受け取る
	const double const * CkValue() const {
		return mCkValue;
	}
	const double const * CkRange() const {
		return mCkRange;
	}

private:
	//データに関する変数
	double* mData;
	int mSize;

	//mCkの値と角度
	double *mCkValue;
	double *mCkRange;
};

#endif