#include "Time.hpp"
#include <string>
#include <iomanip>
using namespace std;

//to check the time is valid
bool is_valid(Time const& time_variable)
{

	return ( ((time_variable.hour >= 0) && (time_variable.hour <= 23)) &&
			((time_variable.minutes >= 0) && (time_variable.minutes <= 59)) &&
			((time_variable.seconds >= 0) && (time_variable.seconds <= 59)));

}

//Function implementation to print the time in string
string to_string(Time const& my_time, int const format)
{
	string time{};

	if(format == 12)
	{
		//morning time calculations
		if ( (my_time.hour > 0 && my_time.hour < 12) && 
			(my_time.minutes >= 0 && my_time.minutes <= 59) && 
			(my_time.seconds >=0 && my_time.seconds <= 59) )
		{
			time = string_format(my_time) + " am";
		}
		// time calculations for Hour at 12 and minutes,seconds greater than 0
		else if((my_time.hour == 12) && 
			(my_time.minutes > 0 && my_time.minutes <= 59) && 
			(my_time.seconds > 0 && my_time.seconds <= 59))
			{
				time = string_format(my_time) + " pm";
			}
		// afternoon time calculations
		else if( (my_time.hour > 12 && my_time.hour <= 24)){
			int t_hour = my_time.hour - 12;
			
			Time T{};
			T.hour = t_hour;
			T.minutes = my_time.minutes;
			T.seconds = my_time.seconds;
			
			time = string_format(T) + " pm";
		}
		//Noon and Midnight Time calculations
		else if ( (my_time.hour == 12 || my_time.hour == 00) && my_time.minutes == 00 && my_time.seconds == 00)
		{
			int t_hour = 12;
			Time t{};

			t.hour = t_hour;
			t.minutes = my_time.minutes;
			t.seconds = my_time.seconds;

			if(my_time.hour == 12)
			{
				time = string_format(t) + " pm";
			}
			else
				time = string_format(t) + " am";
		}		
	}
	// 24 hour time calculations
	else{
		time = string_format(my_time);
	}
	return time;
}

//function to return time in format
string string_format(Time const& my_time)
{
	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(2) << my_time.hour << ":"
		<< std::setw(2) << my_time.minutes << ":"
		<< std::setw(2) << my_time.seconds;

	return oss.str();
}

//function to check the time is am or pm
bool is_am(Time const& my_time)
{

	return ((my_time.hour >=0 && my_time.hour < 12) && 
	(my_time.minutes >= 0 && my_time.minutes <= 59) &&
	(my_time.seconds >=0 && my_time.seconds <=59));

}
//function to make an addition
Time operator+(Time const& my_time, int value)
{
	
	int t_seconds{0};
	int sec{0}, mins{0}, hr{0};

	t_seconds = my_time.hour*3600 + my_time.minutes*60 + my_time.seconds + value;

	while(t_seconds < 0)
	{
		t_seconds += 86400;
	}

	if(t_seconds < 0)
	{
		t_seconds = 0;
	}

	hr = t_seconds / 3600;

	while(hr >= 24)
	{
		hr -= 24;
	}

	t_seconds %= 3600;
	
	mins = t_seconds / 60;
	
	sec = t_seconds % 60;
	
	Time t{hr,mins,sec};
	
	return t;
}
//function to make an subtraction
Time operator-(Time const& my_time, int value)
{
	Time t = my_time + (-value);
	
	return t;
}
//function to implement Prefix incrementer
Time& operator++(Time& my_time)
{
	my_time = my_time + 1;
	
	return my_time;
}
//function to implement Prefix decrementer
Time& operator--(Time& my_time)
{
	my_time = my_time - 1;
	
	return my_time;
}
//function to implement Postfix incrementer
Time operator++(Time& my_time, int)
{	
	Time t = my_time;
	my_time = my_time + 1;
	
	return t;
}
//function to implement Postfix decrementer
Time operator--(Time& my_time, int)
{
	Time t = my_time;
	my_time = my_time - 1;

	return t;
}
//implemention for Equals-to operator
bool operator==(Time const& lhs_time , Time const& rhs_time)
{
    return (lhs_time.hour == rhs_time.hour && 
            lhs_time.minutes == rhs_time.minutes &&
            lhs_time.seconds == rhs_time.seconds);          
}
//implemention for Not Equals-to operator
bool operator!=(Time const& lhs_time , Time const& rhs_time)
{
    return !(lhs_time == rhs_time);
}
//implemention for less-than operator
bool operator<(Time const& lhs_time , Time const& rhs_time)
{
	bool flag{false};
	
    if (lhs_time.hour < rhs_time.hour) {
        flag = true;
    } else if (lhs_time.hour == rhs_time.hour) {
        if (lhs_time.minutes < rhs_time.minutes) {
            flag = true;
        } else if ( lhs_time.minutes == rhs_time.minutes) {
            flag = (lhs_time.seconds < rhs_time.seconds);
        }
    }
	return flag;
}
//implemention for less-than equals-to operator
bool operator<=(Time const& lhs_time , Time const& rhs_time)
{
    return ( (lhs_time < rhs_time) || (lhs_time == rhs_time) );
}
//implemention for greater-than operator
bool operator>(Time const& lhs_time , Time const& rhs_time)
{
	return !(lhs_time <= rhs_time);
}
//implemention for greater-than equals-to operator
bool operator>=(Time const& lhs_time , Time const& rhs_time)
{
    return !( (lhs_time < rhs_time));
}
//implemention for output operator
ostream& operator<<(ostream& os, Time const& my_time)
{
	os << string_format(my_time);
	return os;
}
//implemention for input operator
istream& operator>>(istream& is, Time& in_time)
{
	Time temp_time{};
	char colon{}, colon1{};

	//Here the Hour, minutes and seconds for Time from input stream. 
	is >> temp_time.hour >> colon >> temp_time.minutes >> colon1 >> temp_time.seconds; 
	
	//Check for extraction failure or invalid time
	if (is.fail() || is.peek() != EOF || !is_valid(temp_time) || (colon != ':' && colon1 != ':'))
	{
		//If any of above conditions fail, set the state of stream to failbit.
		is.setstate(std::ios::failbit);
	} else
	{
		// Update Time object, if extraction is successful
		in_time = temp_time;
	}
	return is;
}
