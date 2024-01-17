#include "sortlist.h"
#include <iostream>
using namespace std;

//constructor to initialize head of list
List::List() : head(nullptr) {}

List::Node:: Node(int value) : data(value), next(nullptr){}

List::Node:: Node() : data{0}, next(nullptr){}

//destructor deletes all nodes in list to prevent memory leaks
List::~List()
{
    Node* current = head;
    while (current != nullptr){
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

//Insert function that adds a value to the list (in sorted order)
//Recursive function -> calls rec function insert_recursive to insert value in sorted list
void List::insert(int value)
{
    head = insert_recursive(value, head); //takes arguments to the rec function and updates head
}

List::Node* List::insert_recursive(int value, Node* node)
{
    if (node == nullptr || value <= node->data){//inserts value at the new node before node in list
        Node* new_node = new Node(value);
        new_node->next = node;
        return new_node;
    } else { //recusively calls rec function to search for correct position and insert new node
        node->next = insert_recursive(value, node->next); //ensures next pointer of nodes in list is sorted ok
        return node;
    }
}

//Remove function that removes a value by index
//Iterative function -> loop for
void List::remove_by_index(int index)
{
    if( (index < 0) || (head == nullptr)){ //if empty list / index less than 0, do nothing
        return ;
    }

    else if(index == 0) { //if index 0, remove head node and updates head pointer to new first node
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    else{
        Node* current = head; //initialize pointer at head of list
        Node* prev{nullptr};
        
        for(int i = 0;  current != nullptr && i < index - 1 ; i++) {
            //loop that updates current to the node before the node to remove
            prev = current;
            current = current->next;
        }

        if (current == nullptr){
        //if no node in list to remove do nothing
            return;
        }

        else if (current->next == nullptr){
            delete current;
            prev->next = nullptr;
        }
        else{
            prev->next = current->next;
            delete current;
        }
    }
}

//Remove function that removes a value by value
//Iterative function -> loop while
void List::remove_by_value(int value)
{
    if (head == nullptr){ //if empty list, do nothing
        return;
    }

    while (head != nullptr && head->data == value){ //if index value = head node, remove head node and updates head pointer to new first node
        Node* temp = head;
        head = head-> next;
        delete temp;
    }

    Node* prev = head; //initialize node at head of list
    while (prev->next != nullptr && prev->next->data != value){ //loop that updates current to the node before the node to remove
        prev = prev->next;
    }

    if (prev->next == nullptr){ //if no node in list, nothing to remove
        return;
    }

    Node* temp = prev->next; //temporary node to remove wanted node
    prev->next = prev->next->next; // updates the pointed node
    delete temp; //deletes temporary node
}

//Function that prints all the values in the list
void List::print_list() const
{
    Node* temp = head; //initialize temporary pointer to head list
    while (temp != nullptr){ //loop until end of list
        std::cout << temp->data << ", "; //prints the value of current node
        temp = temp->next; //updates temporary pointer to next node
    }
    std::cout << std::endl; //prints new line to end list
}

//function that return the value stored at a specified index
int List::return_value_by_index(int index) const
{
    int data{};
    if( index <= 0)
    {
        data = 0;
    }

    else if (head == nullptr){ //if list is empty return error
        data = 0;
    }

    else
    {
        Node* current = head;
        int currentIndex{0};
        Node* prev{nullptr};

        while(current && currentIndex < index){
            prev = current;
            current = current->next;
            currentIndex++;
        }

        if(prev){
            data = prev->data;
        }
    }
    return data;
}

//function to check if a list is empty
bool List::is_empty() const
{
    return head == nullptr;
}

int List::size() const{
    int count{0};
    Node* current = head;
    while(current){
        count++;
        current = current->next;
    }
    return count;
}

//copy constructor

List::List(const List& otherList):head(nullptr)
{
    copyListNodes(otherList);
}

//move constructor
List::List(List&& otherList)
{
    head = otherList.head;

    otherList.head = nullptr;
}

//copy assignment operator
List& List::operator=(const List& otherList)
{
    if(this != &otherList){

        clear();
        copyListNodes(otherList);
    }
    return *this;
}

//move assignment operator
List& List::operator=(List&& otherList)
{
    if(this != &otherList){
        clear();

        head = otherList.head;

        otherList.head = nullptr;
    }

    return *this;
}

void List::clear()
{
    Node * current = head;
    while(current != nullptr)
    {
        Node* temp_next = current->next;
        delete current;
        current = temp_next; 
    }
    head = nullptr;
}

// function to avoid repetition of copy list
void List::copyListNodes(const List& source)
{
    Node* newCurrent = source.head;
    Node* current = nullptr;

    while(newCurrent != nullptr){
        Node* newNode = new Node(newCurrent->data);

        if(head == nullptr){
            head = newNode;
        }
        else{
            current->next = newNode;
        }

        current = newNode;
        newCurrent = newCurrent->next;
    }
}