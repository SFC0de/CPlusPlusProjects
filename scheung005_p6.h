#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "/ee259/tools/pro_5/sample_p5.h"

using namespace std;

ofstream output("out.6", ios::out);

class LINEAR_SOLVER: public MATRIX{
   public:
	LINEAR_SOLVER(int);  
			// constructor; example: s.LINEAR_SOLVER(5);
			// there are 5 equations and 5 variables;

	void SOLVE_LINEAR_EQUATION(char *); 
			// example: s.SOLVE_LINEAR_EQUATION("ASCEND");
			// solve the linear equations and
			// sort the output in ascending order;
			// if the input is "DESCEND" then the order
			// of the output is descending;
			// returns no values;

	void SOLVE_BY_MATLAB(void); 
			// example: s.SOLVE_BY_MATLAB();
			// generate and run a MATLAB program to 
			// solve a set of linear equations;
			// returns no values;

	void INHERITED_INVERT(void); 
			// example: s.INHERITED_INVERT();
			// perform matrix inversion on
			// the input system by inheriting
			// from PROGRAM_BANK class;
			// returns no values;

	void INVERT_BY_MATLAB(void); 
			// example: s.INVERT_BY_MATLAB();
			// generate and run a MATLAB program to 
			// invert a matrix;
			// returns no values;
   private:
	int n; 		// max of n is 50
	float A[50][50];
	float B[50];
};

LINEAR_SOLVER::LINEAR_SOLVER(int x)
  	:MATRIX(x, x, "in.6") 	// instantiate MATRIX with input file in.6 and 
  				// dim1=x, dim2=x;
{
	int i,j;

	ifstream input_file("in.6",ios::in);
	// your code for LINEAR_SOLVER constructor goes here
	n = x;
	//cout << dim1 << " " << dim2;
        // read the elements of A and B from in.6
	output << "********** P6 BEGIN *************" << endl;
	output << "*** OUTPUT FROM P6_LINEAR_SOLVER:" << endl;

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			input_file >> A[i][j];
		}
	}

	for(i=0;i<n;i++)
	{
		input_file >> B[i];
	}
	output << "*** INSTANTIATED AN OBJECT WITH " << n << " EQUATIONS" << endl;
	output << "*********** P6 END **************" << endl;
}
 
void 
LINEAR_SOLVER::SOLVE_LINEAR_EQUATION(char * commd)
{
	int column, row, i, j, var, z, end = 1;
	float temp;

	output << "********** P6 BEGIN *************" << endl;

	for(column=0;column<n;column++)
	{
		if(A[column][column] == 0) //pivot if it's zero
		{
			int k;
			end = 0;
			for(k=column+1;k<n && end == 0;k++)
			{
				if(A[k][column] != 0) // found non-zero element
				{
					temp = B[column]; //Swap right side matrix
					B[column] = B[k];
					B[k] = temp;
					for(z = 0;z<n;z++)
					{
						temp = A[column][z]; //Swap left side matrix
						A[column][z] = A[k][z];
						A[k][z] = temp;
					}
					end = 1;
				}
				else{}
			}
		}
		else{}



		for(row=column+1; row<n && end!=0; row++) //making a diagonal matrix
		{
			float multiplier;
			multiplier = (-A[row][column])/(A[column][column]);
			for(i=column;i<n;i++)
			{
				A[row][i] += multiplier*A[column][i];
			}
			B[row] += multiplier * B[column];
		}
	}

	if(end == 0) // singularity
			{
				output << "*** MY GAUSSIAN ELIMINATION SOLUTION:" << endl;
				output << "*** EQUATION IS SINGULAR" << endl;
			}
	else{}
	
	float X[50];
	for(row =n-1; row>=0 && end!= 0; row--) // solving for unknowns
	{
		float accumulation = 0;
		for(var = n-1; var>row; var--)
		{
			accumulation += A[row][var] * X[var];
		}
		X[row] = (B[row] - accumulation)/(A[row][row]);
	}

	if(end != 0)
	{
		if(strcmp(commd,"DESCEND") == 0)
		{
			int temp_m1[50];
			float temp_m2[50];
			for(i=0;i<n;i++)
			{
				temp_m1[i] = i;
				temp_m2[i] = X[i];
			}

			int max_pos, temp1;
			float max,temp2;
			for(i=0;i<n;i++)
			{
				max = temp_m2[i];
				max_pos = i;

				for(j=i;j<n;j++)
				{
					if(temp_m2[j] > max)
					{
						max = temp_m2[j];
						max_pos = j;
					}
					else{}
				}

			temp1 = temp_m1[i];
			temp_m1[i] = temp_m1[max_pos];
			temp_m1[max_pos] = temp1;

			temp2 = temp_m2[i];
			temp_m2[i] = temp_m2[max_pos];
			temp_m2[max_pos] = temp2;
			}
			output << "*** MY GAUSSIAN ELIMINATION SOLUTION (SORTED IN DESCENDING ORDER):" << endl;

			for(i=0;i<n;i++)
			{
				output << "X[" << temp_m1[i] <<"]= " << fixed << showpoint 
							<< setprecision(2) << temp_m2[i] << endl;
			}
		}
		else{}

		if(strcmp(commd,"ASCEND") == 0)
		{
			int temp_m1[50];
			float temp_m2[50];
			for(i=0;i<n;i++)
			{
				temp_m1[i] = i;
				temp_m2[i] = X[i];
			}

			int min_pos, temp1;
			float min,temp2;
			for(i=0;i<n;i++)
			{
				min = temp_m2[i];
				min_pos = i;

				for(j=i;j<n;j++)
				{
					if(temp_m2[j] < min)
					{
						min = temp_m2[j];
						min_pos = j;
					}
					else{}
				}

			temp1 = temp_m1[i];
			temp_m1[i] = temp_m1[min_pos];
			temp_m1[min_pos] = temp1;

			temp2 = temp_m2[i];
			temp_m2[i] = temp_m2[min_pos];
			temp_m2[min_pos] = temp2;
			}
			output << "*** MY GAUSSIAN ELIMINATION SOLUTION (SORTED IN ASCENDING ORDER):" << endl;

			for(i=0;i<n;i++)
			{
				output << "X[" << temp_m1[i] <<"]= " << fixed << showpoint 
							<< setprecision(2) << temp_m2[i] << endl;
			}
		}
		else{}
	}

	output << "*********** P6 END **************" << endl;
}

void
LINEAR_SOLVER::SOLVE_BY_MATLAB()
{
	int i,j,k;
	ofstream england("out_62.m", ios::out);
	cout << "A=[";
	england << "A=[";
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout << A[i][j];
			england << A[i][j];

			if(j==(n-1))
			{}
			else
			{
				cout << ",";
				england << ",";
			}
		}

		if(i==(n-1))
		{}
		else
		{
			cout << ";";
			england << ";";
		}

	}
	england << "];" << endl;
	cout << "];" << endl;
	cout << "B=[";
	england << "B=["; 
	for(k=0;k<n;k++)
	{
		cout << B[k];
		england << B[k];

		if(k==(n-1))
		{}
		else
		{
			cout << ";";
			england << ";";
		}
	}
	england << "];" << endl;
	cout << "];" << endl;
	england << "X=inv(A)*B;" << endl;
	england << "fid=fopen('out.6','a');" << endl;
	england << "fprintf(fid,'********** P6 BEGIN *************\\n');" << endl;
	england << "fprintf(fid,'*** RESULT FROM MATLAB (UNSORTED):\\n');" << endl;
	england << "for k=1:" << n << endl;
	england << "fprintf(fid,'X[%d]=%6.2f\\n',k-1,X(k));" << endl;
	england << "end" << endl;
	england << "fprintf(fid,'*********** P6 END **************\\n');" << endl;

	system("/bin/csh /ee259/tools/pro_6/run_out_62");
}

void 
LINEAR_SOLVER::INHERITED_INVERT()
{
	// ...
	int counter=0;
	output << "********** P6 BEGIN *************" << endl;

	ifstream in("out.5",ios::in);

	MATRIX temp_m(n, n,"in.6"); // create a temp matrix from in.6 file;

	// ...
	1/temp_m; // use the friend function in MATRIX for inversion;
	// ...
	output << "*** AFTER INHERITING FROM MATRIX CLASS, MY RESULT IS:" << endl;

	string str;
    while(getline(in,str))
    {
    	if(counter>2)
    	{
    		output<<str<< endl;
    	}
    	else
    	{}
    	counter++;
    }


	output << "*********** P6 END **************" << endl;
}

void
LINEAR_SOLVER::INVERT_BY_MATLAB()
{
	int i,j,k;
	ofstream litty("out_63.m", ios::out);
	cout << "A=[";
	litty << "A=[";
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout << A[i][j];
			litty << A[i][j];

			if(j==(n-1))
			{}
			else
			{
				cout << ",";
				litty << ",";
			}
		}

		if(i==(n-1))
		{}
		else
		{
			cout << ";";
			litty << ";";
		}

	}
	litty << "];" << endl;
	cout << "];" << endl;

	litty << "X=inv(A);" << endl;
    litty << "fid=fopen('out.6','a');" << endl;
    litty << "fprintf(fid,'********** P6 BEGIN *************\\n');" << endl;
    litty << "fprintf(fid,'*** INVERSION RESULT FROM MATLAB:\\n');" << endl;
    litty << "for i=1:" << n << endl;
    litty << "for j=1:" << n << endl;
    litty << "fprintf(fid,'X[%d][%d]=%6.2f ',i-1,j-1,X(i,j));" << endl;
	litty << "end" << endl;
	litty << "fprintf(fid,'\\n');" << endl;
    litty << "end" << endl;
    litty << "fprintf(fid,'*********** P6 END **************\\n');" << endl;
 	
 	system("/bin/csh /ee259/tools/pro_6/run_out_63");
	
}
