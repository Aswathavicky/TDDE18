#ifndef SORTLIST_H
#define SORTLIST_H

class List
{

    private:
            struct Node
            {
                public:
                        int data;
                        Node* next;

                        Node();
                        
                        Node(int value);
            };
            
            Node* insert_recursive(int value, Node* node);
            void clear();
            void copyListNodes(const List& source);
            
            Node* head;

    public:
        List();
        ~List(); //destructor
        List(const List& otherList); //copy constructor;
        List(List&& otherList); //move constructor
        List& operator=(const List& otherList); //copy assignment operator
        List& operator=(List&& otherList); //move assignment operator
        void insert(int value);
        void print_list() const;
        void remove_by_value(int value);
        void remove_by_index(int index);
        int return_value_by_index(int index) const;
        bool is_empty() const;
        int size() const;
    
};
#endif
