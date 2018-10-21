///////////////////////////////////////////////////////////////
// I UNDERSTAND THAT COPYING PROGRAMS FROM OTHERS WILL BE DEALT
// WITH DISCIPLINARY RULES OF CCNY.
// NAME: Sing Fung Cheung
// LOGIN: scheung005
// PROJECT NUMBER: 3 
///////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>


using namespace std;

// declare the input file
  ifstream input_file("in.3",ios::in);
// declare the output file
  ofstream output_file("out.3",ios::out);

  class PHONE_BILL{

   public:      // public methods for this class

        PHONE_BILL(void); // example: g.PHONE_BILL();
			// constructor;
                       	// returns nothing (void) 

        void READ_CUSTOMERS(int); // example: g.READ_CUSTOMERS(3);
			// method to read information;
			// for first threee customers;		
                        // returns no values;

	void PRINT_CUSTOMERS(int, int); // example: g.PRINT_CUSTOMERS(x, y); 
			// method to print information;
			// where x is customer phone number, and y is the pin.
			// if x and y are -1 and -1, print all customers;
                        // returns no values;
	
	void SORT_NAMES(int); // example: g.SORT_NAMES(x); 
			// method to sort customer names;
			// if x=1, then sort in alphabetical order;
			// if x=-1, then sort in reverse alphabetical order;
        	        // returns no values;

	void CHANGE_PIN(int, int, int); // g.CHANGE_PIN(x, y, z);
			// change pin number of customer x from y (old pin);
			//  to z (new pin);
			// returns no values;

	void ADD_CUSTOMER(char *, char *, int, int); 
			// g.ADD_CUSTOMER("LAST", "FIRST", x, y);
			// add a customer to the database;
			// where x and y are the customer phone;
			// number and pin, respectively; 
			// returns no values;

	void DELETE_CUSTOMER(char *, char *, int, int);
			// g.DELETE_CUSTOMER("LAST", "FIRST", x, y);
			// remove a customer from the database;
			// where x and y are the customer phone;
			// number and pin, respectively; 
			// returns no values;
 
   private: // private var to be used by this class only (not from main)

        int n;  // no of customers;
	int customer_phone_num[10]; // customers' phone numbers;
	int customer_pin[10]; // customers' pin numbers;
        int noof_incoming_calls[10];  // no of incoming calls to a customer;
	int noof_outgoing_calls[10]; // no of outgoing calls from a customer;
	char first_names[10][15]; // customers' first names (15 char max);
	char last_names[10][15]; // customers' last names (15 char max);
   };

PHONE_BILL::PHONE_BILL(void)
{
	// code for constructor goes below:
	int i;
	output_file<<"++++++++++++++++ START ++++++++++++++++++++++"<<endl;
	for(i=0;i<10;i++)
	{
		customer_phone_num[i]=0;
		customer_pin[i]=0;
		noof_incoming_calls[i]=0;
		noof_outgoing_calls[i]=0;
		strcpy(first_names[i],"");
		strcpy(last_names[i], "");

	}
	output_file<<"CONSTRUCTOR SUCCESSFULLY INITIATED AN OBJECT."<<endl;
	output_file<<"++++++++++++++++  END  ++++++++++++++++++++++"<<endl;

}


void 
PHONE_BILL:: READ_CUSTOMERS(int x)
{
	// code for READ_CUSTOMERS goes below:
	n = x;
	int i;
	output_file<<"++++++++++++++++ START ++++++++++++++++++++++"<<endl;
	
	for(i=0;i<n;i++)
	{
		input_file>>last_names[i]>>first_names[i]>>customer_phone_num[i]>>customer_pin[i];
	}
	output_file<<"THERE ARE "<< n <<" CUSTOMERS IN THIS PHONE_BILL"<<endl;
	output_file<<"++++++++++++++++  END  ++++++++++++++++++++++"<<endl;
}

void
PHONE_BILL:: PRINT_CUSTOMERS(int x, int y)
{
	// code for PRINT_CUSTOMERS goes below:
	int i,FOUND = 0,FOUND_POS = 0;

	output_file<<"++++++++++++++++ START ++++++++++++++++++++++"<<endl;
	output_file<<"OUTPUT FROM PRINT_CUSTOMERS INTERFACE:"<<endl;
	output_file<<"THIS PHONE_BILL HAS "<< n <<" CUSTOMERS." << endl;

	if(x == -1 && y == -1)
	{
		for(i=0;i<n;i++)
		{
			output_file << "CUSTOMER NAME: " << last_names[i] << ", " << first_names[i]
						<< " PHONE NUMBER: " << customer_phone_num[i] << " PIN: " << customer_pin[i]<<endl;
		}
	}
	else if(x<0 || x>9999999 || y<0 || y>1000)
	{
       	output_file<<"INPUT ERROR."<<endl;
	}
	else
	{
		for(i=0;i<n && FOUND == 0;i++)
		{
			if(customer_phone_num[i]==x && customer_pin[i]==y)
			{
				FOUND = 1;
				FOUND_POS = i;
			}
			else{}
		}
		if(FOUND == 1)
		{
			output_file << "CUSTOMER NAME: " << last_names[FOUND_POS] << ", " << first_names[FOUND_POS]
						<< " PHONE NUMBER: " << x << " PIN: " << y << endl;
		}
		else
		{
			output_file << "CUSTOMER NOT IN DATABASE." << endl;
		}
	}
	output_file << "++++++++++++++++  END  ++++++++++++++++++++++" << endl;
}

void	
PHONE_BILL:: SORT_NAMES(int x)
{
	// code for SORT_CUSTOMERS goes below:
	int i,j,min_pos = 0, max_pos = 0, temp_num = 0, temp_pin = 0;
	char min[15], max[15], temp_last[15], temp_first[15];
	output_file << "++++++++++++++++ START ++++++++++++++++++++++" << endl;        
	output_file << "OUTPUT FROM SORT_NAMES INTERFACE:" << endl;

	if(x == 1)
	{
		output_file << "CUSTOMER NAMES ARE SORTED IN ALPHABETICAL ORDER." << endl;

		for(i=0;i<n;i++)
		{
			strcpy(min,last_names[i]);
			min_pos = i;


			for(j=i;j<n;j++)
			{
				if(strcmp(last_names[j],min)<0)
				{
					strcpy(min,last_names[j]);
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
		}

	}
	else if(x == -1)
	{
		output_file << "CUSTOMER NAMES ARE SORTED IN REVERSE ALPHABETICAL ORDER." << endl;

		for(i=0;i<n;i++)
		{
			strcpy(max,last_names[i]);
			max_pos = i;

			for(j=i;j<n;j++)
			{
				if(strcmp(last_names[j],max)>0)
				{
					strcpy(max,last_names[j]);
					max_pos = j;
				}
				else{}
			}
		strcpy(temp_last,last_names[max_pos]);
		strcpy(last_names[max_pos],last_names[i]);
		strcpy(last_names[i],temp_last);

		strcpy(temp_first,first_names[max_pos]);
		strcpy(first_names[max_pos],first_names[i]);
		strcpy(first_names[i],temp_first);

		temp_num = customer_phone_num[max_pos];
		customer_phone_num[max_pos] = customer_phone_num[i];
		customer_phone_num[i] = temp_num;

		temp_pin = customer_pin[max_pos];
		customer_pin[max_pos] = customer_pin[i];
		customer_pin[i] = temp_pin;
		}
	}
	else
	{
		output_file << "INPUT ERROR." << endl;
	}        
	output_file << "++++++++++++++++  END  ++++++++++++++++++++++" << endl;
}

void	
PHONE_BILL:: CHANGE_PIN(int x, int y, int z) 
{
	// code for CHANGE_PIN goes below:
	int i,FOUND = 0, FOUND_POS = 0;
	output_file<<"++++++++++++++++ START ++++++++++++++++++++++"<<endl;
	output_file<<"OUTPUT FROM CHANGE_PIN INTERFACE:"<<endl;
	
	if(x<0 || x>9999999 || y<0 || y>1000 || z<0 || z>1000)
	{
		output_file<<"INPUT ERROR."<<endl;
	}
	else
	{
		for(i=0;i<n && FOUND == 0;i++)
		{
			if(customer_phone_num[i] == x && customer_pin[i] == y)
			{
				FOUND = 1;
				FOUND_POS = i;
			}
			else{}
		}
		
		if(FOUND == 1)
		{
			output_file << "CUSTOMER PIN NUMBER HAS BEEN CHANGED."<<endl;
			customer_pin[FOUND_POS] = z;
		}
		else
		{
			output_file << "CUSTOMER " << x << " NOT IN DATABASE." << endl;
		}

	}

	output_file<<"++++++++++++++++  END  ++++++++++++++++++++++"<<endl;
}


void
PHONE_BILL:: ADD_CUSTOMER(char* LAST, char* FIRST, int x, int y) 
{
	// code for ADD_CUSTOMER goes below:
	int i,j;
	j=n;

	output_file<<"++++++++++++++++ START ++++++++++++++++++++++"<<endl;
	output_file<<"OUTPUT FROM ADD_CUSTOMER INTERFACE:"<<endl;
	
	if(x<0 || x>9999999 || y<0 || y>1000)
	{
		output_file<<"INPUT ERROR."<<endl;
	}
	else
	{
		output_file<<"NEW CUSTOMER ADDED."<<endl;

		strcpy(last_names[j],LAST);
		strcpy(first_names[j],FIRST);
		customer_phone_num[j]= x;
		customer_pin[j] = y;

		n++;
	}

	output_file<<"++++++++++++++++  END  ++++++++++++++++++++++"<<endl;
}

void 
PHONE_BILL:: DELETE_CUSTOMER(char* LAST, char* FIRST, int x, int y) 
{
	// code for DELETE_CUSTOMER goes below:
	int i,FOUND=0,FOUND_POS=0;
	output_file<<"++++++++++++++++ START ++++++++++++++++++++++"<<endl;
	output_file<<"OUTPUT FROM DELETE_CUSTOMER INTERFACE:"<<endl;

	if(x<0 || x>9999999 || y<0 || y>1000)
	{
		output_file<<"INPUT ERROR."<<endl;
	}
	else
	{
		for(i=0;i<n && FOUND == 0;i++)
		{
			if((strcmp(LAST,last_names[i]) == 0) && strcmp(FIRST,first_names[i]) == 0 && 
				customer_phone_num[i] == x && customer_pin[i] == y)
			{
				FOUND = 1;
				FOUND_POS = i;
			}
			else{}
		}
		
		if(FOUND == 1)
		{
			output_file<<"CUSTOMER DELETED."<<endl;

			for(i=FOUND_POS;i<n;i++)
			{
				strcpy(last_names[i],last_names[i+1]);
				strcpy(first_names[i],first_names[i+1]);
				customer_phone_num[i] = customer_phone_num[i+1];
				customer_pin[i] = customer_pin[i+1];

			}
			n--;
		}
		else
		{
			output_file<<"CUSTOMER NOT IN DATABASE."<<endl;
		}
	}

	output_file<<"++++++++++++++++  END  ++++++++++++++++++++++"<<endl;
}
