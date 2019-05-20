#ifndef INCLUDED_ARRAY_2D_H
#define INCLUDED_ARRAY_2D_H

//二次元配列クラス
//これを使う時にはTのところにintとかboolとか入れて使う。自作のオブジェクトを入れてもよい
template< class T > class Array2D {
public:
	Array2D() : mArray(0), mSize0(0), mSize1(0) {}
	Array2D(const Array2D& other) {
		mSize0 = other.mSize0;
		mSize1 = other.mSize1;
		mArray = new T[mSize0 * mSize1];
		for (int i = 0; i < mSize0 * mSize1; ++i) {
			mArray[i] = other.mArray[i];
		}
	}
	~Array2D() {
		delete[] mArray;
		mArray = 0;
	}
	void setSize(int size0, int size1) {
		delete[] mArray;
		mArray = 0;
		mSize0 = size0;
		mSize1 = size1;
		mArray = new T[size0 * size1];
	}
	T& operator()(int index0, int index1) {
		return mArray[index1 * mSize0 + index0];
	}
	const T& operator()(int index0, int index1) const {
		return mArray[index1 * mSize0 + index0];
	}
private:
	T* mArray;
	int mSize0;
	int mSize1;
};

#endif
