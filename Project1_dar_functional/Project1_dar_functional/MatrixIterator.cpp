#include "MatrixIterator.h"
#include <exception>

//Theta(1)
MatrixIterator::MatrixIterator(const Matrix& mat,int col) :m{ mat },c{col}
{
	this->current = 0;
}

//Theta(1)
void MatrixIterator::first()
{
	this->current = 0;
}

//Theta(1)
void MatrixIterator::next()
{
	if (!this->valid())
		throw std::exception();
	else
		this->current++;
}

//Total complexity: O(n) --> BC Omega(1), WC O(n), AC O(n)
TElem MatrixIterator::getCurrent()
{
	if (!this->valid())
		throw std::exception();
	return m.element(this->current, this->c);
}

//Theta(1)
bool MatrixIterator::valid() const
{
	if (this->current < 0 || this->current >= m.line_nr - 1)
		return false;

	return true;
}
