#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{

    //variable declaration
	float first_price{} , last_price{} , stride{} , tax_percent{} , tax{} , total{} , fixed_first_price{}; 
    int iterations = 0;
    
   //input table format
   cout << "INPUT PART" << endl; 
   cout << string(10,'=') << endl;

   //user enters inputs
   //loops do while check for accepted values
   //loops if/else if give error messages and get back in the loop to enter again an accepted value
   
   //First price
   do{
    cout << "Enter first price: ";
    cin >> first_price;
    if(first_price < 0){
        cerr << "ERROR: First price must be at least 0 (zero) SEK" << endl;
    }
    else if (first_price > 100000.00){
        cerr << "ERROR: First price must be less than 100,000 SEK" << endl;
    }
   } while((first_price < 0)||(first_price > 100000.00));
   
   //Last price
   do{
    cout << "Enter last price : ";
    cin >> last_price;
    if(last_price <= first_price){
        cerr << "ERROR: Last price must be greater than the first price" << endl;
    }
    else if (last_price > 100000.00){
        cerr << "ERROR: Last price must be less than 100,000 SEK" << endl;
    }
   } while((last_price <= first_price)||(last_price > 100000.00));
   
   //Stride
   do{
    cout << "Enter stride     : ";
    cin >> stride;
    if(stride < 0.01){
        cerr << "ERROR: Stride must be at least 0.01" << endl;
    }
    else if (stride > 100000.00){
        cerr << "ERROR: Stride must be less than 100,000" << endl;
    }
   } while((stride < 0.01)||(stride > 100000.00));
   
   //Tax percentage
   do{
    cout << "Enter tax percent: ";
    cin >> tax_percent;
    if(tax_percent < 0){
        cerr << "ERROR: Tax percentage must be at least 0%" << endl;
    }
    else if (tax_percent > 100.00){
        cerr << "ERROR: Tax percentage must be less than 100%" << endl;
    }
   } while((tax_percent < 0)||(tax_percent > 100.00));

   //tax table format
   cout << "\n" << "TAX TABLE" << endl
        << string(9,'=') << endl
        << setw(12) << "Price" << setw(17) << "Tax" << setw(21) << "Price with tax" << endl
        << string(50,'-') << endl;
   
   //calculate iterations
   iterations = ((last_price - first_price) / stride) + 1;

   //Fix first price
   fixed_first_price = first_price;

   //loop to prind data in table
   for(int i = 1; i <= iterations; i++){
    //two decimal format
    cout << fixed << setprecision(2);
    //operations
    tax = (first_price * tax_percent) / 100;
    total = first_price + tax;
    //print table
    cout << setw(12) << first_price << setw(17) << tax << setw(21) << total << endl;
    first_price = fixed_first_price + ( i * stride );
   }
   
   
return 0;
}