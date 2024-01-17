
#ifndef TIME_HPP
#define TIME_HPP
#include <string>
#include <iostream>

struct Time
{
	int hour{};
	int minutes{};
	int seconds{};
};

bool is_valid(Time const& my_time);

std::string to_string(Time const& my_time, int format);

bool is_am(Time const& my_time);

Time operator+(Time const& my_time, int value);

Time operator-(Time const& my_time, int value);

Time& operator++(Time& my_time);

Time& operator--(Time& my_time);

Time operator++(Time& my_time, int); //postfix incrementer

Time operator--(Time& my_time, int); //postfix decrementer

bool operator==(Time const& lhs_time , Time const& rhs_time);

bool operator!=(Time const& lhs_time , Time const& rhs_time);

bool operator<(Time const& lhs_time , Time const& rhs_time);

bool operator<=(Time const& lhs_time , Time const& rhs_time);

bool operator>(Time const& lhs_time , Time const& rhs_time);

bool operator>=(Time const& lhs_time , Time const& rhs_time);

std::string string_format(Time const& my_time); 

std::ostream& operator<<(std::ostream& os, Time const& my_time);

// Operator>> takes the input for time with three integers and two characters though the values are incorrect.

std::istream& operator>>(std::istream& is, Time& time);

#endif
