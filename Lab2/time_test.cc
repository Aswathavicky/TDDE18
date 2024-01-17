
#include "catch.hpp"
#include "Time.hpp"

//Check for a valid time and invalid hour, minutes or seconds in a 24-hour clock format
TEST_CASE("is_valid")
{
    Time valid_time{7, 47, 25};
    Time valid_low_edge{0, 0, 0};
    Time valid_up_edge{23, 59, 59};
    Time valid_seconds{12, 11, 59};
    Time valid_minutes{12, 59, 11};
    Time invalid_hour{32, 18, 33};
    Time invalid_minutes{9, 79, 58};
    Time invalid_seconds{22, 20, 95};
    Time negative_hour{-4, 15, 33};
    Time negative_minute{4, -15, 33};
    Time negative_second{4, 15, -33};

    CHECK(is_valid(valid_time) == true);
    CHECK(is_valid(valid_low_edge) == true);
    CHECK(is_valid(valid_up_edge)== true);
    CHECK(is_valid(valid_seconds)== true);
    CHECK(is_valid(valid_minutes)== true);
    CHECK(is_valid(invalid_hour)== false);
    CHECK(is_valid(invalid_minutes)== false);
    CHECK(is_valid(invalid_seconds)== false);
    CHECK(is_valid(negative_hour)== false);
    CHECK(is_valid(negative_minute)== false);
    CHECK(is_valid(negative_second)== false);
}

TEST_CASE("to_string")
{
    Time t1{12, 05, 30};
    Time t2{15, 18, 45};
    Time t3{20, 28, 12};
    Time t4{0, 0, 0};
    Time t5{12, 0, 0};
    Time t6{8, 8, 03};

    CHECK(to_string(t1, 12) == "12:05:30 pm");
    CHECK(to_string(t2,12) == "03:18:45 pm");
    CHECK(to_string(t3,24) == "20:28:12");
    CHECK(to_string(t4,12) == "12:00:00 am");
    CHECK(to_string(t5,12) == "12:00:00 pm");
    CHECK(to_string(t6,12) == "08:08:03 am");
}

//Check if the time is am or pm in the 12-hour clock format
TEST_CASE("is_am")
{
    Time am_time{9, 35, 47};
    Time am_low_edge{0, 0, 0};
    Time am_up_edge{11, 59, 59};
    Time midnight{0, 0, 0};
    
    Time pm_time{19, 42, 7};
    Time pm_low_edge{13, 0, 0};
    Time pm_up_edge{23, 59, 59};
    Time noon{12, 0, 0};

    CHECK(is_am(am_time) == true);
    CHECK(is_am(am_low_edge) == true);
    CHECK(is_am(am_up_edge) == true);
    CHECK(is_am(midnight) == true);

    CHECK(is_am(pm_time) == false);
    CHECK(is_am(pm_low_edge) == false);
    CHECK(is_am(pm_up_edge) == false);
    CHECK(is_am(noon) == false);
}

//Verifies correct result for adding or subtracting seconds to the time in 24-hour clock format
TEST_CASE("operator + and -")
{
    Time t1{17, 15, 35};
    Time t2{00, 00, 15};
    Time t3 = t1+5;
    Time t4 = t2-1;
	Time t5 = t2 + (86400 * 2);
    Time t6 = t2 + (86400 * 3);
    Time t7 = t2 - (86400 * 2);
    Time t8 = t2 - (86400 * 3);
    Time t9 = t1 + (86400 * 3);
    Time t10 = t1 - (86400 * 3);
    Time t11{23, 59, 59};
    Time t12 = t11 + 1;
    Time t13 = t11 - 1;
	    
    CHECK(t3 == Time{17,15,40});
    CHECK(t4 == Time{00,00,14});
	CHECK(t5 == Time{00,00,15});
    CHECK(t6 == Time{00,00,15});
    CHECK(t7 == Time{00,00,15});
    CHECK(t8 == Time{00,00,15});
    CHECK(t9 == Time{17,15,35});
    CHECK(t10 == Time{17,15,35});
    CHECK(t12 == Time{0, 0, 0});
    CHECK(t13 == Time{23, 59, 58});
}


//Verifies correct result for adding 1 second to the time in 24-hour clock format (prefix and postfix)
TEST_CASE("operator Prefix & Postfix ++")
{
    Time t{17, 15, 35};
	Time t1{18, 15, 35};
	
	
	CHECK(++t == Time{17, 15, 36});
	CHECK(t1++ == Time{18, 15, 35});

    Time t2 = ++t;
    Time t3 = t1++;
	
	CHECK(t2 == Time{17, 15, 37});
	CHECK(t3 == Time{18, 15, 36});
}
 

//Verifies correct result for subtracting 1 second to the time in 24-hour clock format (prefix and postfix)
TEST_CASE("operator Prefix & Postfix --")
{
    Time t{17, 15, 35};
    Time t1{18, 15, 35};

    
    
    CHECK(--t == Time{17, 15, 34});
    CHECK(t1-- == Time{18, 15, 35});

    Time t2 = --t;
    Time t3 = t1--;

    CHECK(t2 == Time{17, 15, 33});
    CHECK(t3 == Time{18, 15, 34});
}

//Verifies correct result for comparing to times in 24-hour clock format
TEST_CASE("comparison operators")
{
    Time t1{17, 15, 35};
    Time t2{17, 15, 35};
    Time t3{11, 25, 47};

    CHECK(t1 == t2);
    CHECK_FALSE(t1 != t2);
    CHECK_FALSE(t1 == t3);

    CHECK(t1 <= t2);
    CHECK_FALSE(t1 < t2);

    CHECK(t1 >= t2);
    CHECK_FALSE(t1 < t2);
    CHECK_FALSE(t1 < t3);

    CHECK(t1 != t3);
    CHECK(t1 > t3);
    CHECK(t3 < t1);
}

TEST_CASE("Input and Output Formats")
{
    Time ioput{};
    std::istringstream input("15:05:18");
    input >> ioput;
    std::ostringstream output;
    output << ioput;
    CHECK(output.str() == "15:05:18");
    

    Time t1{};
    std::istringstream input1("15:05:18:36");
    input1 >> t1;
    std::cout << input1.fail();
    CHECK(input1.fail());

    Time t2{};
    std::istringstream input2("30:77:77");
    input2 >> t2;
    CHECK(input2.fail());

    Time t3{};
    std::istringstream input3("307777");
    input3 >> t3;
    CHECK(input3.fail());

    Time t4{14,21,10};
    std::istringstream input4("307777");
    input4 >> t4;
    CHECK(input3.fail());
    CHECK_FALSE(t4.hour == 00);
    CHECK(t4.hour == 14);
    CHECK_FALSE(t4.minutes == 00);
    CHECK(t4.minutes == 21);
    CHECK_FALSE(t4.seconds == 0);
    CHECK(t4.seconds == 10);
}
