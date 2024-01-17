#include <iostream>
#include <string>
#include <limits>
#include <bits/stdc++.h>
using namespace std;


int main()
{
	//variable declaration
	int integer_variable{0};

	double double_variable{0.0};
	
	char character_variable{};
	
	string string_variable{};

	//skeleton to print an integer
	
	cout <<"Enter one integer: ";
	cin >> integer_variable;
	cin.clear();
	cin.ignore(100, '\n');
	cout << "You entered the number: " << integer_variable
		<< endl << "\n" << flush;
	

	//skeleton to enter four integers
	
	cout << "Enter four integers: ";
	
	cin >> integer_variable;
	cout << "You entered the numbers: " << integer_variable << " ";
	
	cin >> integer_variable;
	cout << integer_variable << " ";
	
	cin >> integer_variable;
	cout << integer_variable << " ";
	
	cin >> integer_variable;
	cout << integer_variable << endl << "\n" << flush;
	

	//skeleton to print one integer and one real numbers
	
	cout << "Enter one integer and one real number: ";
	cin >> integer_variable >> double_variable;
	cin.clear();
	cin.ignore(50, '\n');
	cout << "The real is: " << setprecision(4) 
		<< double_variable << endl
		<< "The integer is: " << integer_variable 
		<< endl << "\n" << flush;
	
	//skeleton to print one real and one integer
	
	cout << "Enter one real and one integer number: ";
	cin >> double_variable >> integer_variable;
	cin.clear();
	cin.ignore(50, '\n');
	cout << "The real is: " << fixed << setprecision(3) 
		<< double_variable << endl
		<< "The integer is: " << integer_variable 
		<< endl << "\n" << flush;
	
	//skeleton to print a character
	
	cout << "Enter a character: ";
	cin >> character_variable;
	cin.clear();
	cin.ignore(50, '\n');
	cout << "You entered: " << character_variable 
		<< endl << "\n" << flush;
	
	//skeleton to print a word
	
	cout << "Enter a word: ";
	cin >> string_variable;
	cin.clear();
	cin.ignore(50, '\n');
	cout << "The word '" << string_variable << "' has "	
		<< string_variable.size() << " character(s)." 
		<< endl << "\n" << flush;
	
	//to print an integer and a word
	
	cout << "Enter an integer and a word: ";
	cin >> integer_variable	>> string_variable;
	cin.clear();
	cin.ignore(50, '\n');
	cout << "You entered '" << integer_variable 
		<< "' and '" << string_variable << "'." 
		<< endl << "\n" << flush;
	
	//to print a character and a word
	
	cout << "Enter an character and a word: ";
	cin >> character_variable >> string_variable;
	cin.clear();
	cin.ignore(50, '\n');
	cout << "You entered the string \"" << string_variable 
		<< "\" and the character '" << character_variable << "'." 
		<< endl << "\n" << flush;
	
	//to print a word and a real number
	
	cout << "Enter a word and a real number: ";
	cin >> string_variable >> double_variable;
	cin.clear();
	cin.ignore(50, '\n');
	cout << "You entered \"" << string_variable 
		<< "\" and \"" << setprecision(3) << double_variable 
		<< "\"." << endl << "\n" << flush;
	
	//to print a text-line
	
	cout << "Enter a text-line: ";
	cin.clear();
	getline(cin, string_variable);
	cout << "You entered: \"" << string_variable << "\"" 
		<< endl << "\n" << flush;
	
	//to print a second line of text
	
	cout <<"Enter a second line of text: ";
	getline(cin, string_variable);
	cout << "You entered: \"" << string_variable << "\"" 
		<< endl << "\n" << flush;
	
	//to print three words
	
	cout << "Enter three words: ";
	
	cin >> string_variable;
	cout << "You entered: '" << string_variable << " ";
	
	cin >> string_variable;
	cout << string_variable << " ";
	
	cin >> string_variable;
	cout << string_variable << "'" << endl;
	
return 0;
}

