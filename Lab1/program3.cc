#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;


int main(){

	// declarling variables for stream, string and int
	
	string textline{};
	double temp_avg{0.0};
	double avg_length{0.0};
	int word_count{0};
	
	string short_word{};
	string long_word{};
	
	int short_word_length{200};
	int long_word_length{0};

	int length{0};

	ifstream text_file{"program3.cpp"};
	
	while(text_file >> textline)
	{
		length = textline.length();
		if(length <= short_word_length){
			short_word = textline;
			short_word_length = length;
		}
		
		if(length >= long_word_length){
			long_word = textline;
			long_word_length = length;
		}
		
		word_count++;
		temp_avg = temp_avg + length;
	}
	
	avg_length = temp_avg / word_count;
	
	if( word_count > 0)
	{
		cout << "There are " << word_count << " words in this file." << endl
			<< "The shortest word was \"" << short_word 
			<< "\" with " << short_word_length << " character(s)." << endl
			<< "The longest word was \"" << long_word 
			<< "\" with "<<long_word_length << " character(s)." << endl
			<< "The average length was " << fixed << setprecision(3) 
			<< avg_length << " character(s)." << endl;
	}
	else{
		cout << "Warning!! File is Empty!" << endl;
	}

	return 0;
}
