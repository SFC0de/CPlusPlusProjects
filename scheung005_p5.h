#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "/ee259/tools/pro_5/inversion.h"

using namespace std;

ofstream output_file("out.5", ios::out);

class MATRIX: public PROGRAM_BANK{

	friend MATRIX operator / (int, MATRIX); 
				// FRIEND FUNCTION; example: 5 / X;
				// Compute inverse of X using INHERITANCE;
				// Multiply each element of inverted matrix
				// by 5; 
				// store the results into a temp MATRIX;
				// return the temp MATRIX;
	
	friend MATRIX operator * (int, MATRIX); 
				// FRIEND FUNCTION; example: 5 * X;
				// each element of the matrix X is 
				// multiplied by 5;
				// store the results into a temp MATRIX;
				// return the temp MATRIX;

	public:	// public interfaces for this class
	
	  MATRIX (int, int); 	// constructor;
				// example: MATRIX X(d1,d2);
			   	// creates a matrix object with
			   	// private variables dim1 = d1 and dim2 = d2
			  	// and initializes each element to 0;
  
	  MATRIX(int, int, char *); 
	  			// constructor;
				// example: MATRIX X(d1,d2,"in_name");
				// read the elements of the matrix
				// from a given file in_name; d1 and d2 are 
				// the two dimensions of the matrix;
				

	  void PRINT();		// example: X.PRINT();
				// print the elements of the matrix X
				// into out.5 file;
				// returns no values;

	  int  operator < (int); //example: if( X < b)
				// check if the minimum element of the matrix X
				// is less than b
				// returns 1 if so; returns 0 otherwise;
		
	  void operator = (MATRIX );
	  			// example X = Y;
				// Copy Y to X;
				// returns no values;		
		
	  void operator += (MATRIX);  
	  			// example: X += Y;
                        	// matrix addition;
                        	// store the results in X;
				// values of Y remain unchanged;
				// returns no values;
		
	  void operator *= (MATRIX); 
	  			// example: X *= Y;
				// matrix multiplication;
				// store the results in X;
				// values of Y remain unchanged;
				// returns no values;

	  MATRIX operator + (MATRIX); 
	  			// example: X + Y;
				// Create a temp matrix object; 
				// add each element of Y to each element of X;
				// return this temp matrix object;
				// values of X and Y remain unchanged;

	  MATRIX operator * (MATRIX); 
	  			// example: X * Y;
				// matrix multiplication;
				// store the results into a temp matrix
				// and return this temp matrix;
				// values of Y remain unchanged;

	  MATRIX operator / (MATRIX); 
	  			// example: X / Y;
				// get inverse of Y and multiply it with X;
				// put the results into a temp MATRIX
				// and return temp MATRIX;
				// X and Y remain unchanged;
				// USE INHERITENCE FOR MATRIX INVERSION;
	
	private:

  	  int dim1, dim2; 	// dimensions of the matrix;
				// if dim2 is 1, a vector (no need for special
				// handling of vectors; everything should work
				// for both matrices and vectors)

  	  double A[20][20]; 	// 2 dimensional array for the matrix elements;
	  char in_file[11]; 	// hold the input file name
 };


// FIRST CONSTRUCTOR
MATRIX::MATRIX(int d1, int d2)
        :PROGRAM_BANK(d1) // CALL THE CONSTRUCTOR FOR BASE CLASS
{
	int i, j;

	dim1 = d1;
	dim2 = d2;

	for(i=0;i<dim1;i++)
	{
		for(j=0;j<dim2;j++)
		{
			A[i][j] = 0;
		}
	}
}

// SECOND CONSTRUCTOR
MATRIX::MATRIX(int d1, int d2, char * file_name)
        :PROGRAM_BANK(d1, file_name) // CALL THE CONSTRUCTOR FOR BASE CLASS
{
	 // your constructor code goes here
	
	
	 // store the input file name:
	 strcpy(in_file, file_name);

	 // define the input file
 	 ifstream input_file(in_file,ios::in);

 	 int i, j;

 	 output_file << "+++ P5 START +++++++++++++++++++++++++++++++++++++++++" << endl;

 	 if(d1<0 || d1>20 || d2<0 || d2>20)
 	 {
 	 	output_file << "+++ P5_OUTPUT >>> INPUT ERROR" << endl;
		output_file << "+++ P5_OUTPUT >>> UNABLE TO CREATE MATRIX" << endl;
		output_file << "+++ P5_OUTPUT >>> EXITING PROGRAM" << endl;
		output_file << "+++ P5 END +++++++++++++++++++++++++++++++++++++++++++" << endl;
		exit(1); 
 	 }
 	 else
 	 {
 	 	dim1 = d1;
		dim2 = d2;
 	 	for(i=0;i<dim1;i++)
 	 	{
 	 		for(j=0;j<dim2;j++)
 	 		{
 	 			input_file >> A[i][j];
 	 		}
 	 	}
 	 	output_file << "+++ P5_OUTPUT >>> CREATED A " << dim1 << " X " 
 	 				<< dim2 << " MATRIX FROM " << file_name << endl;
 	 	output_file << "+++ P5 END +++++++++++++++++++++++++++++++++++++++++++" << endl;
 	 }
 	 

}

MATRIX operator / (int c, MATRIX a_matrix)
{
		a_matrix.PROGRAM_BANK::INVERT_MATRIX("OUT_5_TEMP");
        MATRIX temp_matrix(a_matrix.dim1, a_matrix.dim2);
        ifstream input_file("OUT_5_TEMP",ios::in);

        int i,j;

        output_file << "+++ P5 START +++++++++++++++++++++++++++++++++++++++++" << endl;

        for(i=0;i<temp_matrix.dim1;i++)
        {
        	for(j=0;j<temp_matrix.dim2;j++)
        	{
        		input_file >> temp_matrix.A[i][j];
        		temp_matrix.A[i][j]*=c;
        	}
        }
		output_file << "+++ P5_OUTPUT >>> THE RESULT OF " << c << " / X OPERATION IS:" << endl;
		
		for(i=0;i<temp_matrix.dim1;i++)
		{
			for(j=0;j<temp_matrix.dim2;j++)
			{
				output_file << fixed << showpoint << setprecision(2) << temp_matrix.A[i][j] << " ";
			}

			output_file << endl;
		} 

      	output_file << "+++ P5 END +++++++++++++++++++++++++++++++++++++++++++" << endl;

        return temp_matrix;
}

MATRIX operator * (int c, MATRIX a_matrix)
{
        MATRIX temp_matrix(a_matrix.dim1, a_matrix.dim2);

        int i,j;
        output_file << "+++ P5 START +++++++++++++++++++++++++++++++++++++++++" << endl;
		output_file << "+++ P5_OUTPUT >>> THE RESULT OF " << c << " * X OPERATION IS:" << endl;

		for(i=0;i<temp_matrix.dim1;i++)
		{
			for(j=0;j<temp_matrix.dim2;j++)
			{
				temp_matrix.A[i][j] = c*a_matrix.A[i][j];
			}
		}

		for(i=0;i<temp_matrix.dim1;i++)
		{
			for(j=0;j<temp_matrix.dim2;j++)
			{
				output_file << fixed << showpoint << setprecision(2) << temp_matrix.A[i][j] << " ";
			}

			output_file << endl;
		} 

      	output_file << "+++ P5 END +++++++++++++++++++++++++++++++++++++++++++" << endl;

        return temp_matrix;
}

void
MATRIX::PRINT( )
{
	int i, j;

	output_file << "+++ P5 START +++++++++++++++++++++++++++++++++++++++++" << endl;
	output_file << "+++ P5_OUTPUT >>> CONTENTS OF MATRIX IS:" << endl;
	
	for(i=0;i<dim1;i++)
	{
		for(j=0;j<dim2;j++)
		{
			output_file << fixed << showpoint << setprecision(2) << A[i][j] << " ";

		}

		output_file << endl;
	} 

	output_file << "+++ P5 END +++++++++++++++++++++++++++++++++++++++++++" << endl;
}

int
MATRIX::operator < (int b)
{
	int i, j, min;

    output_file << "+++ P5 START +++++++++++++++++++++++++++++++++++++++++" << endl;
	
	min = A[0][0];
	
	for(i=0;i<dim1;i++)
	{
		for(j=0;j<dim2;j++)
		{
			if(A[i][j]<min)
			{
				min = A[i][j];
			}
			else{}
		}
	}
	if(min<b)
	{
	output_file << "+++ P5_OUTPUT >>> OVERLOADED OPERATOR < RETURNING TRUE" << endl;
	output_file << "+++ P5 END +++++++++++++++++++++++++++++++++++++++++++" << endl;
	return 1;
	}
	else
	{
	output_file << "+++ P5_OUTPUT >>> OVERLOADED OPERATOR < RETURNING FALSE" << endl;
	output_file << "+++ P5 END +++++++++++++++++++++++++++++++++++++++++++" << endl;
    return 0;
	}
}


void
MATRIX::operator = (MATRIX  a_matrix)
{
	int i, j;
	output_file << "+++ P5 START +++++++++++++++++++++++++++++++++++++++++" << endl;

	if(dim1 == a_matrix.dim1 && dim2 == a_matrix.dim2)
	{
		for(i=0;i<dim1;i++)
		{
			for(j=0;j<dim2;j++)
			{
				A[i][j] = a_matrix.A[i][j];
			}
		}
		output_file << "+++ P5_OUTPUT >>> OVERLOADED OPERATOR = COMPLETED" << endl;
	}
	else
	{
		output_file << "+++ P5_OUTPUT >>> ERROR" << endl;
		output_file << "+++ P5_OUTPUT>>> INCOMPATIBLE MATRICES" << endl;
	}
	
	output_file << "+++ P5 END +++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void
MATRIX::operator += (MATRIX a_matrix)
{
	int i, j;
	MATRIX temp_matrix(dim1, dim2);

	output_file << "+++ P5 START +++++++++++++++++++++++++++++++++++++++++" << endl;
	
	if(dim1 != a_matrix.dim1 || dim2 != a_matrix.dim2)
	{
		output_file << "+++ P5_OUTPUT >>> ERROR" << endl;
		output_file << "+++ P5_OUTPUT >>> INCOMPATIBLE MATRICES" << endl;
	}
	else
	{
		for(i=0;i<dim1;i++)
		{
			for(j=0;j<dim2;j++)
			{
				temp_matrix.A[i][j] = A[i][j] + a_matrix.A[i][j];
			}
		}

		for(i=0;i<dim1;i++)
		{
			for(j=0;j<dim2;j++)
			{
				A[i][j] = temp_matrix.A[i][j];
			}
		}

		output_file << "+++ P5_OUTPUT >>> OVERLOADED OPERATOR += COMPLETED" << endl;
	}
	output_file << "+++ P5 END +++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void
MATRIX::operator *= (MATRIX a_matrix)
{
	int i, j , k;
	MATRIX temp_matrix(dim1, dim2);
	
	output_file << "+++ P5 START +++++++++++++++++++++++++++++++++++++++++" << endl;
	
	if(dim2 != a_matrix.dim1)
	{
		output_file << "+++ P5_OUTPUT >>> ERROR" << endl;
		output_file << "+++ P5_OUTPUT >>> INCOMPATIBLE MATRICES" << endl;
	}
	else
	{
		for(i=0;i<dim1;i++)
		{
			for(j=0;j<a_matrix.dim2;j++)
			{
				for(k=0;k<dim2;k++)
				{
					temp_matrix.A[i][j] += A[i][k] * a_matrix.A[k][j];
				}
			}
		}

		for(i=0;i<dim1;i++)
		{
			for(j=0;j<dim2;j++)
			{
				A[i][j] = temp_matrix.A[i][j];
			}
		}

		output_file << "+++ P5_OUTPUT >>> OVERLOADED OPERATOR *= COMPLETED" << endl;
	}

	output_file << "+++ P5 END +++++++++++++++++++++++++++++++++++++++++++" << endl;
}

MATRIX
MATRIX::operator + (MATRIX a_matrix)
{
    int i, j;
    MATRIX temp_matrix(dim1, dim2);
	
	output_file << "+++ P5 START +++++++++++++++++++++++++++++++++++++++++" << endl;
	
	if(dim1 != a_matrix.dim1 || dim2 != a_matrix.dim2)
	{
		output_file << "+++ P5_OUTPUT >>> ERROR" << endl;
		output_file << "+++ P5_OUTPUT >>> INCOMPATIBLE MATRICES" << endl;
	}
	else
	{
		for(i=0;i<dim1;i++)
		{
			for(j=0;j<dim2;j++)
			{
				temp_matrix.A[i][j] = A[i][j] + a_matrix.A[i][j];
			}
		}
		output_file << "+++ P5_OUTPUT >>> OVERLOADED OPERATOR + COMPLETED" << endl;
	}
	
	output_file << "+++ P5 END +++++++++++++++++++++++++++++++++++++++++++" << endl;


    return temp_matrix;
}

MATRIX
MATRIX::operator * (MATRIX a_matrix)
{
    int i, j, k;
    MATRIX temp_matrix(dim1, dim2);

    output_file << "+++ P5 START +++++++++++++++++++++++++++++++++++++++++" << endl;

    if(dim2 != a_matrix.dim1)
	{
		output_file << "+++ P5_OUTPUT >>> ERROR" << endl;
		output_file << "+++ P5_OUTPUT >>> INCOMPATIBLE MATRICES" << endl;
	}
	else
	{
		
		for(i=0;i<dim1;i++)
		{
			for(j=0;j<a_matrix.dim2;j++)
			{
				for(k=0;k<dim2;k++)
				{
					temp_matrix.A[i][j] += A[i][k] * a_matrix.A[k][j];
				}
			}
		}
	
		output_file << "+++ P5_OUTPUT >>> OVERLOADED OPERATOR * COMPLETED" << endl;

	}

	output_file << "+++ P5 END +++++++++++++++++++++++++++++++++++++++++++" << endl;

    return temp_matrix;
}

MATRIX
MATRIX::operator / (MATRIX a_matrix)
{
        a_matrix.PROGRAM_BANK::INVERT_MATRIX("OUT_5_TEMP");
        MATRIX inv_matrix(20,20);
        MATRIX temp_matrix(dim1, dim2);
        ifstream input_file("OUT_5_TEMP",ios::in);

        inv_matrix.dim1 = a_matrix.dim1;
        inv_matrix.dim2 = a_matrix.dim2;

        int i,j,k;

        output_file << "+++ P5 START +++++++++++++++++++++++++++++++++++++++++" << endl;

        for(i=0;i<inv_matrix.dim1;i++)
        {
        	for(j=0;j<inv_matrix.dim2;j++)
        	{
        		input_file >> inv_matrix.A[i][j];
        	}
        }

        if(dim2 != inv_matrix.dim1)
        {
        	output_file << "+++ P5_OUTPUT >>> ERROR" << endl;
			output_file << "+++ P5_OUTPUT >>> INCOMPATIBLE MATRICES" << endl;
        }
        else
        {
			output_file << "+++ P5_OUTPUT >>> OVERLOADED OPERATOR / COMPLETED" << endl;
			output_file << "+++ P5_OUTPUT >>> THE RESULT OF X/Y OPERATION IS:" << endl;
		
			for(i=0;i<dim1;i++)
			{
				for(j=0;j<inv_matrix.dim2;j++)
				{
					for(k=0;k<dim2;k++)
					{
						temp_matrix.A[i][j] += A[i][k] * inv_matrix.A[k][j];
					}
				}
			} 

			for(i=0;i<temp_matrix.dim1;i++)
			{
				for(j=0;j<temp_matrix.dim2;j++)
				{
					output_file << fixed << showpoint << setprecision(2) << temp_matrix.A[i][j] << " ";
				}
				output_file << endl;
			}
		}
      	output_file << "+++ P5 END +++++++++++++++++++++++++++++++++++++++++++" << endl;

        return temp_matrix;
}
