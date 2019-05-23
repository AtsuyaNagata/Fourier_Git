#ifndef GRAND_FOURIER_H_
#define GRAND_FOURIER_H_

class Fourier
{
public:
	//doubleのデータを受け取ってそれを使う（g(n)を受け取る）
	Fourier(const double *data, int size);
	~Fourier();

	//位置指定をして特定のデータを受け取る
	double CkValue(int) const;
	double CkRange(int) const;

	//ポインタでごっそり受け取る
	const double* const CkValue() const {
		return mCkValue;
	}
	const double* const CkRange() const {
		return mCkRange;
	}

	int size() {
		return mSize;
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