#ifndef GRAND_FOURIER_H_
#define GRAND_FOURIER_H_

class Fourier
{
public:
	//doubleのデータを受け取ってそれを使う（g(n)を受け取る）
	Fourier(const double* data, int size);
	Fourier(int size);
	Fourier();
	~Fourier();

	//フーリエ変換するデータの更新
	void update(const double* data, int size);

	//FFT関数
	void FFT(const double* data, int size);

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
	const int difference() const {
		return mDifference;
	}

	//「=」の処理
	void operator=(Fourier &f);

	int size() {
		return mSize;
	}

private:
	//データに関する変数
	int mSize;
	//2のべき乗と受け取ったデータの差分
	int mDifference;

	//mCkの値と角度
	double* mCkValue;
	double* mCkRange;

	//返すことは無いけど、計算時間短縮のためにここで宣言しておくメンバ変数群
	double* CkSin;
	double* CkCos;
	double* Wsin;
	double* Wcos;
};

#endif