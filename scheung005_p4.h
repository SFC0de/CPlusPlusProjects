///////////////////////////////////////////////////////////////
// I UNDERSTAND THAT COPYING PROGRAMS FROM OTHERS WILL BE DEALT
// WITH DISCIPLINARY RULES OF CCNY.
// NAME: Sing Fung Cheung
// LOGIN: scheung005
// PROJECT NUMBER: 4
///////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

// declare the output file
  ofstream output_file("out.4",ios::out);

  class OVERLOADED_PHONE_BILL{

   public:      // public interfaces for this class

        OVERLOADED_PHONE_BILL(char *, int); 
			// example: g.OVERLOADED_PHONE_BILL("i_f_name",3);
			// first constructor reads information from in_file_name;
			// for first threee customers;		
                       	// returns nothing (void) 

        OVERLOADED_PHONE_BILL(void); // example: g.OVERLOADED_PHONE_BILL();
			// second constructor;
                       	// initializes n to zero;	
			// returns nothing (void) 
        
	void PRINT_CUSTOMERS(int, int); // example: g.PRINT_CUSTOMERS(x, y); 
			// interface to print information;
			// where x is customer phone number, and y is the pin.
			// if x and y are -1 and -1, print all customers;
			// if x and y are -2 and -2, sort the customers
			// in alphabetical order based on last names
			// and then print them;  sorted names are stored in
			// private data;
                        // returns no values;
	
	void CHANGE_NAME(int, int, char *, char *); 
			// example: g.CHANGE_NAME(x, y, "FRED","LAKER");
			// update the first and last names for phone number x
			// with pin y as FRED LAKER.
			// returns no values;

	int operator > (OVERLOADED_PHONE_BILL &);
			// example: if (g1 > g2)
			// returns 1 if the maximum number of outgoing calls
			// in g1 is graeter than the maximum in g2;
			// returns 0 otherwise;

	int operator == (OVERLOADED_PHONE_BILL &);
			// example: if (g1 == g2)
			// returns 1 if the number of customers in g1 
			// and g2 are equal;
			// returns 0 otherwise;

	void operator += (OVERLOADED_PHONE_BILL &); // example: g1 += g2;
			// append the customers in g2 to g1;
			// assume that all customers are unique;
			// returns no values;

	void operator -= (OVERLOADED_PHONE_BILL &); // example: g1 -= g2;
			// delete the customers of g2 from g1 if they exist
			// in g1 (phone number, first and last names must match); 
			// g2 does not change;
			// returns no values;
 
   private: // private var to be used by this class only (not from main)

        int n;  // no of customers;
	int customer_phone_num[10]; // customers' phone numbers;
	int customer_pin[10]; // customers' pin numbers;
        int noof_incoming_calls[10];  // no of incoming calls to a customer;
	int noof_outgoing_calls[10]; // no of outgoing calls from a customer;
	char first_names[10][15]; // customers' first names (15 char max);
	char last_names[10][15]; // customers' last names (15 char max);
	char in_file_name[10]; // input file name:  

};

OVERLOADED_PHONE_BILL::OVERLOADED_PHONE_BILL(char* i_f_name, int x)
{
	// code for constructor goes here


	int i;
	n = x;

	output_file << "++++++++++++++++ START ++++++++++++++++++++++" << endl;
	output_file << "CONSTRUCTOR SUCCESSFULLY INITIATED AN OBJECT." << endl;

	    for(i=0;i<10;i++)
        {
        	customer_phone_num[i]=0;
        	customer_pin[i]=0;
        	noof_incoming_calls[i]=0;
        	noof_outgoing_calls[i]=0;
        	strcpy(first_names[i]," ");
        	strcpy(last_names[i]," ");
        	strcpy(in_file_name," ");
        }

	// Copy the input file name to in_file_name
        strcpy(in_file_name, i_f_name);

        // declare the input file
        ifstream input_file(in_file_name,ios::in);
        
	// read private data elements from in.4 file for n customers

        for(i=0;i<n;i++)
        {
        	input_file >> last_names[i] >> first_names[i] >> customer_phone_num[i]
        			   >> customer_pin[i] >> noof_incoming_calls[i] >> noof_outgoing_calls[i];
        }
		
		output_file << "THIS OVERLOADED_PHONE_BILL FROM " << i_f_name << " FILE HAS " 
					<< n <<" CUSTOMERS." << endl; 
		output_file << "++++++++++++++++  END  ++++++++++++++++++++++" << endl;
}

	
OVERLOADED_PHONE_BILL::OVERLOADED_PHONE_BILL(void)
{
	// code for second constructor goes here
	// This constructor sets n to 0
	
	n=0;

}

void
OVERLOADED_PHONE_BILL:: PRINT_CUSTOMERS(int x, int y)
{
	// code for PRINT_CUSTOMERS goes here
	int i,j,min_pos,temp_num = 0, temp_pin = 0, temp_incoming = 0, temp_outgoing = 0, 
		found = 0, found_pos = 0;
	char min_name[15],temp_last[15],temp_first[15];

	output_file << "++++++++++++++++ START ++++++++++++++++++++++" << endl;
	output_file << "OUTPUT FROM PRINT_CUSTOMERS INTERFACE:" << endl;
	output_file << "THIS OVERLOADED_PHONE_BILL HAS " << n << " CUSTOMERS." << endl;
       	
	if(x == -1 && y == -1)
	{
		for(i=0;i<n;i++)
		{
			output_file << "CUSTOMER NAME: " << last_names[i] << ", " << first_names[i] 
						<< " PHONE NUMBER: " << customer_phone_num[i] << " PIN: " 
						<< customer_pin[i] << " INCOMING: " << noof_incoming_calls[i]
						<< " OUTGOING: " << noof_outgoing_calls[i] << endl;
		}
     
	}
	else if(x == -2 && y == -2)
	{
		for(i=0;i<n;i++)
		{
			strcpy(min_name,last_names[i]);
			min_pos = i;

			for(j=i;j<n;j++)
			{
				if(strcmp(last_names[j],min_name)<0)
				{
					strcpy(min_name,last_names[j]);
					min_pos = j;
				}
				else{}
			}

		strcpy(temp_last,last_names[min_pos]);
		strcpy(last_names[min_pos],last_names[i]);
		strcpy(last_names[i],temp_last);

		strcpy(temp_first,first_names[min_pos]);
		strcpy(first_names[min_pos],first_names[i]);
		strcpy(first_names[i],temp_first);

		temp_num = customer_phone_num[min_pos];
		customer_phone_num[min_pos] = customer_phone_num[i];
		customer_phone_num[i] = temp_num;

		temp_pin = customer_pin[min_pos];
		customer_pin[min_pos] = customer_pin[i];
		customer_pin[i] = temp_pin;

		temp_incoming = noof_incoming_calls[min_pos];
		noof_incoming_calls[min_pos] = noof_incoming_calls[i];
		noof_incoming_calls[i] = temp_incoming;

		temp_outgoing = noof_outgoing_calls[min_pos];
		noof_outgoing_calls[min_pos] = noof_outgoing_calls[i];
		noof_outgoing_calls[i] = temp_outgoing;
		}

		for(i=0;i<n;i++)
		{
			output_file << "CUSTOMER NAME: " << last_names[i] << ", " << first_names[i] 
						<< " PHONE NUMBER: " << customer_phone_num[i] << " PIN: " 
						<< customer_pin[i] << " INCOMING: " << noof_incoming_calls[i]
						<< " OUTGOING: " << noof_outgoing_calls[i] << endl;
		}
	}
	else if(x<0 || x>9999999 || y<0 || y>1000)
	{
		output_file << "INPUT ERROR." << endl;
	}
	else
	{
		for(i=0;i<n && found == 0;i++)
		{
			if(customer_phone_num[i] == x && customer_pin[i] == y)
			{
				found = 1;
				found_pos = i;
			}
			else{}
		}

		if(found == 1)
		{
			output_file << "CUSTOMER NAME: " << last_names[found_pos] << ", " << first_names[found_pos] 
						<< " PHONE NUMBER: " << x << " PIN: " << y << " INCOMING: " << noof_incoming_calls[found_pos]
						<< " OUTGOING: " << noof_outgoing_calls[found_pos] << endl;
		}
		else
		{
			output_file << "CUSTOMER NOT IN DATABASE." << endl;
		}

	}
	
	output_file << "++++++++++++++++  END  ++++++++++++++++++++++" << endl;
}

void	
OVERLOADED_PHONE_BILL:: CHANGE_NAME(int x, int y, char *FIRST, char *LAST) 
{
	// code for CHANGE_NAME goes here
	int i,found = 0, found_pos = 0;
	output_file << "++++++++++++++++ START ++++++++++++++++++++++" << endl;
	output_file << "OUTPUT FROM CHANGE_NAME INTERFACE:" << endl;
    
	if(x<0 || x>9999999 || y<0 || y>1000)
	{
		output_file << "INPUT ERROR." << endl;
	}
	else
	{
		for(i=0;i<n && found == 0;i++)
		{
			if(customer_phone_num[i] == x && customer_pin[i] == y)
			{
				found = 1;
				found_pos = i;
			}
			else{}
		}

		if(found == 1)
		{
			output_file << "CUSTOMER NAME HAS BEEN CHANGED." << endl;

			strcpy(first_names[found_pos],FIRST);
			strcpy(last_names[found_pos],LAST);
		}
		else
		{
			output_file << "CUSTOMER " << x << " NOT IN DATABASE." << endl;
		}
	}
	
	output_file << "++++++++++++++++  END  ++++++++++++++++++++++" << endl;
}

int
OVERLOADED_PHONE_BILL:: operator > (OVERLOADED_PHONE_BILL & second_bill) 
{
	// code for operator > goes here
	int i, found_pos = 0, max = 0;
	
	output_file << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	output_file << "+++ OUTPUT FROM OVERLOADED OPERATOR > INTERFACE:" << endl;

	for(i=0;i<n;i++)
	{
		if(noof_outgoing_calls[i]>max)
		{
			max = noof_outgoing_calls[i];
			found_pos = i;
		}
		else{}
	}

	if(noof_outgoing_calls[found_pos]>second_bill.noof_outgoing_calls[found_pos])
	{
		output_file << "+++ RETURNS TRUE." << endl;
		output_file << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		return 1;
	}
	else
	{
		output_file << "+++ RETURNS FALSE." << endl;
		output_file << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		return 0;
	}
	
}


int
OVERLOADED_PHONE_BILL:: operator == (OVERLOADED_PHONE_BILL & second_bill) 
{
	// code for operator == goes here

	output_file << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	output_file << "+++ OUTPUT FROM OVERLOADED OPERATOR == INTERFACE:" << endl;
	
	if(n == second_bill.n)
	{
		output_file << "+++ RETURNS TRUE." << endl;
		output_file << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		return 1;
	}
	
	else
	{
		output_file << "+++ RETURNS FALSE." << endl;
		output_file << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		return 0;
	}


}

void
OVERLOADED_PHONE_BILL:: operator += (OVERLOADED_PHONE_BILL & second_bill) 
{
	// code for operator += goes here
	int i, counter = 0;
	
	output_file << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	output_file << "+++ OUTPUT FROM OVERLOADED OPERATOR += INTERFACE:" << endl;

	counter = n + second_bill.n;

	if(counter>10)
	{
		output_file << "+++ INPUT ERROR." << endl;
	}
	else
	{
		for(i=0;i<second_bill.n;i++)
		{
			strcpy(last_names[n+i],second_bill.last_names[i]);
			strcpy(first_names[n+i],second_bill.first_names[i]);
			customer_phone_num[n+i] = second_bill.customer_phone_num[i];
			customer_pin[n+i] = second_bill.customer_pin[i];
			noof_incoming_calls[n+i] = second_bill.noof_incoming_calls[i];
			noof_outgoing_calls[n+i] = second_bill.noof_outgoing_calls[i];
		}

		n += second_bill.n;
		
		output_file << "+++ CUSTOMERS FROM "<< second_bill.in_file_name 
					<< " HAVE BEEN ADDED IN DATABASE." << endl;
	}

	output_file << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void
OVERLOADED_PHONE_BILL:: operator -= (OVERLOADED_PHONE_BILL & second_bill) 
{
	// code for operator -= goes here
	int i, j, k, found = 0, found_pos = 0, counter = 0, start_phone = 0;
	char start_last[15], start_first[15];

	output_file << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	output_file << "+++ OUTPUT FROM OVERLOADED OPERATOR -= INTERFACE:" << endl;

	for(i=0;i<second_bill.n;i++)
	{
		found = 0;
		strcpy(start_last,second_bill.last_names[i]);
		strcpy(start_first,second_bill.first_names[i]);
		start_phone = second_bill.customer_phone_num[i];

		for(j=0;j<n && found == 0;j++)
		{
			if (strcmp(start_last,last_names[j]) == 0 && strcmp(start_first,first_names[j]) == 0
				&& start_phone == customer_phone_num[j])
			{
				found = 1;
				found_pos = j;
			}
			else{}
		}

		if(found == 1)
		{
			for(k=found_pos;k<n;k++)
			{
				strcpy(last_names[k],last_names[k+1]);
				strcpy(first_names[k],first_names[k+1]);
				customer_phone_num[k] = customer_phone_num[k+1];
				customer_pin[k] = customer_pin[k+1];
				noof_incoming_calls[k] = noof_incoming_calls[k+1];
				noof_outgoing_calls[k] = noof_outgoing_calls[k+1];
			}

			counter++;
			n--;
		}
		else{}
	}
	
	if(counter == 0)
	{
		output_file << "+++ NO CUSTOMERS DELETED." << endl;
	}
	else
	{
		output_file << "+++ " << counter << " CUSTOMERS DELETED." << endl;
	}
	
	output_file << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}
