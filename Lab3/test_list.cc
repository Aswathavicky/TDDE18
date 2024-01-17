#include "catch.hpp"
#include "sortlist.h"
#include <random>

//=======================================================================
// Test cases
//=======================================================================

TEST_CASE( "Create an empty list" )
{
  List l{};

  REQUIRE( l.is_empty() == true );
  REQUIRE( l.size() == 0 );
}

TEST_CASE("List Insertion")
{
  List list1{};

  REQUIRE(list1.is_empty() == true);
  list1.insert(9);
  list1.insert(3);
  list1.insert(4);
  list1.insert(10);
  list1.insert(1);

  //list1.print_list();

  REQUIRE(list1.is_empty() == false);
  REQUIRE(list1.size() == 5);
}

TEST_CASE("List Deletion")
{

  List list1{};

  list1.insert(5);
  list1.insert(4);
  list1.insert(8);
  list1.insert(7);
  list1.insert(9);
  list1.insert(2);

  //list1.print_list();

  REQUIRE(list1.is_empty() == false);
  REQUIRE(list1.size()== 6);

  list1.remove_by_value(8);
  REQUIRE(list1.is_empty() == false);
  REQUIRE(list1.size()== 5);

  list1.remove_by_value(2);
  REQUIRE(list1.is_empty() == false);
  REQUIRE(list1.size()== 4);
  
  //list1.print_list();

  list1.remove_by_index(4);
  REQUIRE(list1.is_empty() == false);
  //list1.print_list();
  REQUIRE(list1.size()== 3);
  
  list1.remove_by_value(10);
  REQUIRE(list1.size()== 3);

  //list1.print_list();
  list1.remove_by_index(0);
  //list1.print_list();
  REQUIRE(list1.size()==2);

  list1.remove_by_index(-1);
  REQUIRE(list1.size()==2);
}

TEST_CASE("Fetch Element in List")
{
  List list1{};

  list1.insert(10);
  list1.insert(1);
  list1.insert(5);
  list1.insert(7);
  list1.insert(6);
  list1.insert(3);

  //list1.print_list();

  REQUIRE(list1.is_empty() == false);
  REQUIRE(list1.size() == 6);
  REQUIRE(list1.return_value_by_index(4) == 6);
  REQUIRE(list1.return_value_by_index(1) == 1);
  REQUIRE(list1.return_value_by_index(0) == 0);

}

TEST_CASE("Copy and Move Constructor")
{
  List originalList{};
  originalList.insert(20);
  originalList.insert(2);
  originalList.insert(10);
  originalList.insert(5);
  originalList.insert(1);
  originalList.insert(15);

  REQUIRE(originalList.is_empty() == false);
  REQUIRE(originalList.size()==6);
  REQUIRE(originalList.return_value_by_index(5)==15);
  //originalList.print_list();

  List copyList(originalList);
  REQUIRE(copyList.is_empty() == false);
  REQUIRE(copyList.size() == 6);
  
  copyList.insert(12);
  REQUIRE(copyList.is_empty() == false);
  REQUIRE(copyList.size() == 7);
  //copyList.print_list();

  originalList.insert(7);

  List moveList(std::move(originalList));
  REQUIRE(moveList.is_empty() == false);
  REQUIRE(moveList.size() == 7);
  REQUIRE(originalList.is_empty() == true);
  REQUIRE(originalList.size() == 0);
  //moveList.print_list();

}

TEST_CASE("Copy Assignment Operator")
{
  List originalList{};
  originalList.insert(20);
  originalList.insert(2);
  originalList.insert(10);
  originalList.insert(5);
  originalList.insert(1);
  originalList.insert(15);

  REQUIRE(originalList.is_empty() == false);
  REQUIRE(originalList.size()==6);
  //originalList.print_list();

  List copyAssignmentList{};
  copyAssignmentList = originalList;

  REQUIRE(copyAssignmentList.is_empty() == false);
  REQUIRE(copyAssignmentList.size() == 6);
  //copyAssignmentList.print_list();
  REQUIRE(copyAssignmentList.return_value_by_index(6)==20);
  REQUIRE(originalList.is_empty() == false);
  REQUIRE(originalList.size() == 6);
  //copyAssignmentList.print_list();

  copyAssignmentList = copyAssignmentList;
  REQUIRE(copyAssignmentList.is_empty() == false);
  REQUIRE(copyAssignmentList.size() == 6);

}

TEST_CASE("Move Assignment Operator")
{
  List originalList{};
  originalList.insert(4);
  originalList.insert(7);
  originalList.insert(1);
  originalList.insert(5);
  originalList.insert(10);

  REQUIRE(originalList.is_empty() == false);
  REQUIRE(originalList.size() == 5);

  List moveAssignmentList{};
  moveAssignmentList = std::move(originalList);

  REQUIRE(moveAssignmentList.is_empty() == false);
  REQUIRE(moveAssignmentList.size() == 5);
  REQUIRE(originalList.is_empty() == true);
  REQUIRE(originalList.size() == 0);
  //moveAssignmentList.print_list();
  REQUIRE(moveAssignmentList.return_value_by_index(3) == 5);

  List assignmentList{};
  moveAssignmentList = std::move(assignmentList);
  REQUIRE(moveAssignmentList.size()== 0);
  REQUIRE(assignmentList.size() == 0);

  originalList.insert(10);
  REQUIRE(originalList.is_empty() == false);
  REQUIRE(originalList.size() == 1);
  
  assignmentList.insert(10);
  assignmentList.insert(5);
  REQUIRE(assignmentList.is_empty() == false);
  REQUIRE(assignmentList.size() == 2);


  assignmentList = std::move(originalList);
  REQUIRE(originalList.is_empty() == true);
  REQUIRE(originalList.size() == 0);
  REQUIRE(assignmentList.is_empty() == false);
  REQUIRE(assignmentList.size() == 1);

}

// It is your job to create new test cases and fully test your Sorted_List class
