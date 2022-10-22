#include "Matrix.h"
#include "MatrixIterator.h"

#include <exception>
using namespace std;

//Theta(n) = BC = WC = Total
Matrix::Matrix(int nrLines, int nrCols) {
	   
	this->line_nr = nrLines;
	this->col_nr = nrCols;
	this->col_size = 0;
	this->col_capacity = 2;
	
	this->line_elems = new TElem[this->line_nr + 1];
	for (int i = 0; i <= this->line_nr; i++)
		this->line_elems[i] = 0;
	
	this->col_elems = new TElem[this->col_nr];
	this->values = new TElem[this->col_nr];

}

//Theta(1) = BC = WC = Total
Matrix::~Matrix()
{
	delete[] this->line_elems;
	delete[] this->col_elems;
	delete[] this->values;

}


//Theta(1) = BC = WC = Total
int Matrix::nrLines() const {
	return this->line_nr;
}

//Theta(1) = BC = WC = Total
int Matrix::nrColumns() const {
	return this->col_nr;
}

//BC = Omega(1)
//WC = O(n)
//AC = Theta(n) ->where n is the number of steps in the array
//Total = O(n)
TElem Matrix::element(int i, int j) const {
	if (i >= 0 && i <= this->line_nr)
		if (j >= 0 && j <= this->col_nr)
		{
			for (int k = this->line_elems[i]; k < this->line_elems[i + 1]; k++)
				if (this->col_elems[k] == j)
					return this->values[k];
			return NULL_TELEM;
		}
	throw exception();
}

//BC = min(BC1,BC2);
//WC = max(WC1,WC2);
//Total = O(n)
TElem Matrix::modify(int i, int j, TElem e)
{
	if (e == NULL_TELEM)
	{	
		//remove elem from array
		//BC1 = Omega(n)
		//WC1= O(n)
		//AC1 = Theta(n)
		//Total1 = Theta(n) - where n is the max(col_size - line_elems[i], line_nr-i-1)
		for (int k = this->line_elems[i]; k < this->line_elems[i + 1]; k++)
			if (this->col_elems[k] == j)
			{
				int nr = this->values[k];
				for (int h = k; h < this->col_size - 1; h++)
				{
					this->col_elems[h] = this->col_elems[h + 1];
					this->values[h] = this->values[h + 1];
				}
				this->col_size--;
				for (int h = i + 1; h <= this->line_nr; h++)
					this->line_elems[h]--;
				return nr;
			}
		return NULL_TELEM;
	}
	if (i >= 0 && i <= this->line_nr)
		if (j >= 0 && j <= this->col_nr)
		{
			//add/find in the array
			//BC2 = Omega(1)
			//WC2 = O(n)
			//AC2 = Theta(n)
			//Total2 = O(n) - where n is the max(col_size - line_elems[i], line_nr-i-1)
			for (int k = this->line_elems[i]; k < this->line_elems[i + 1]; k++)
			{
				if (this->col_elems[k] == j)
				{
					int nr = this->values[k];
					this->values[k] = e;
					return nr;
				}
				else if (this->col_elems[k] > j)
				{
					if (this->col_capacity == this->col_size+1)
					{
						this->col_capacity *= 2;
						TElem* new_elem = new TElem[ this->col_capacity];
						TElem* new_elem_value = new TElem[this->col_capacity];
						for (int h = 0; h < this->col_size; h++)
						{
							new_elem[h] = this->col_elems[h];
							new_elem_value[h] = this->values[h];
						}
						
						delete[] this->col_elems;
						delete[] this->values;
						this->col_elems = new_elem;
						this->values = new_elem_value;
					}

					for (int h = this->col_size - 1; h >= k; h--)
					{
						this->col_elems[h + 1] = this->col_elems[h];
						this->values[h + 1] = this->values[h];
					}
					this->col_elems[k] = j;
					this->values[k] = e;
					for (int h = i + 1; h <= this->line_nr; h++)
						this->line_elems[h]++;
					this->col_size++;


					return NULL_TELEM;
				}
			}
			if (this->col_capacity == this->col_size+1)
			{
				
				this->col_capacity *= 2;
				TElem* new_elem = new TElem[this->col_capacity];
				TElem* new_elem_value = new TElem[this->col_capacity];
				for (int h = 0; h < this->col_size; h++)
				{
					new_elem[h] = this->col_elems[h];
					new_elem_value[h] = this->values[h];
				}

				delete[] this->col_elems;
				delete[] this->values;
				this->col_elems = new_elem;
				this->values = new_elem_value;
			}
			for (int h = this->col_size - 1; h >this->line_elems[i+1]-1; h--)
			{
				this->col_elems[h + 1] = this->col_elems[h];
				this->values[h + 1] = this->values[h];
			}
			this->col_elems[this->line_elems[i+1]] = j;
			this->values[this->line_elems[i+1]] = e;
			this->col_size++;
			for (int h = i + 1; h <= this->line_nr; h++)
				this->line_elems[h]++;
			return NULL_TELEM;
		}
	throw exception();

}

//Theta(1)
MatrixIterator Matrix::iterator(int line) const {
	return MatrixIterator(*this, line);
}


