#include <iostream>
#include <fstream>

using namespace std;

// declare the input file
  ifstream input_file("in.0",ios::in);
// declare the output file
  ofstream output_file("out.0",ios::out);

  class SIMPLEST{

   public:      // public interfaces for this class

        SIMPLEST(void); // example: g.SIMPLEST();
				// constructor;
                        	// returns nothing (void) 

        void READ_CUSTOMERS(void); 
			// example: g.READ_CUSTOMERS(void);
			// interface to read customer information
                        // returns no values;

		void PRINT_CUSTOMERS(void); 
			// example: g.PRINT_CUSTOMERS(void); 
			// interface to print customer information;
                        // returns no values;

   private: // private var to be used by this class only (not from main)

        int n;  // no of customers;
		int customer_phone_num[10]; // customer's phone numbers;
        int noof_incoming_calls[10];  // no of incoming calls to a customer;
		int noof_outgoing_calls[10]; // no of outgoing calls from a customer;
   };

SIMPLEST::SIMPLEST()
{
	// your code goes here
	n = 0;
	int i;
	for(i=0;i<10;i++)
	{
		customer_phone_num[i]=0;
		noof_incoming_calls[i]=0;
		noof_outgoing_calls[i]=0;
	}
	
}

void
SIMPLEST::READ_CUSTOMERS()
{
	// your code goes here
	int i;
	input_file>>n;
	for(i=0;i<n;i++)
	{
		input_file>>customer_phone_num[i];
		input_file>>noof_incoming_calls[i];
		input_file>>noof_outgoing_calls[i];
	}
	output_file << "CONTSTRUCTOR SUCCESSFULLY INITIATED AN OBJECT." <<endl;
	output_file << "THERE ARE " << n << " CUSTOMERS IN THIS SIMPLEST"<<endl;
}

void
SIMPLEST::PRINT_CUSTOMERS()
{
	// your code goes here
	int i;
	output_file << "OUTPUT FROM PRINT_CUSTOMERS INTERFACE:" <<endl;
	output_file << "THIS SIMPLEST HAS " << n << " CUSTOMERS" <<endl;
	for(i=0;i<n;i++)
	{
		output_file << "CUSTOMER WITH PHONE NUMBER " << customer_phone_num[i] << " HAS:" <<endl;
		output_file << "NO OF INCOMING CALLS: " << noof_incoming_calls[i] << " NO OF OUTGOING CALLS: " << noof_outgoing_calls[i] <<endl;
	}
}