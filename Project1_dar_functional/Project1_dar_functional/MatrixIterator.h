#pragma once
#include "Matrix.h"

class MatrixIterator
{
	friend class Matrix;

private:
	const Matrix& m;
	int c,current;

public:
	MatrixIterator(const Matrix& mat,int col);

	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};


