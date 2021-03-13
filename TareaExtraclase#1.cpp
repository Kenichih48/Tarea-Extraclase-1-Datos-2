#include <iostream>
#include<stdlib.h>
#include<cstdlib>
using namespace std;

class Node {
    public:
        int value; //Stores the value of the node
        Node* pointer; //Stores the next element´s memory location
        int get_value(){ //gets the value of the node
            return value;            
        };
        void set_value(int new_value){ //sets the value of the node to the new value specified
            value = new_value;
        };
        Node* get_pointer(){ //gets the pointer of the node next to this one
            return pointer;
        };
        void set_pointer(Node* new_pointer){ //sets the pointer of the node next to this one
            pointer = new_pointer;
        }; 
};

class List {
    public:
        Node* start; //contains the memory position of the first element in the list        
        int length = 0; //length of the list
        int i = 0;
        Node* current_node;
        Node* old_start;
        void insert_node(Node* node){ //inserts a node to the list
            if (length != 0){                
                node->set_pointer(start);
                }
            start = node;
            length += 1;
        };
        Node* get_start_pointer(){ //gets the pointer of the first element of the list
            return start;
        };
        void modify_element(int position, int new_value){ //modifies the value of a specified element in the list
            if (position >= 0 && position < length){
                current_node = start; 
                while(i < position){
                    current_node = current_node->get_pointer();
                    i++;
                }
                current_node->set_value(new_value);
                i = 0;
            } 
            else{
                cout<<"Please indicate a valid position"<<endl;
            }
        };
        void remove_node(){ //deletes the first element of the list
            if (length > 0){
                old_start = start;
                if (length > 1){
                    start = start->get_pointer();
                }
                length -= 1;
                std::cout<<"removed element is:"<<old_start->get_value()<<endl;
            }      
            else{
                cout<<"The list is empty!!"<<endl;
            }   
        };
        void view_list(){ //Prints the values that are stored in list
            if (length > 0){
                current_node = start; 
                cout<<"Current state of the list: [";
                while(i < length-1){
                    cout<<current_node->get_value()<<", ";
                    current_node = current_node->get_pointer();
                    i++;
                }
                cout<<current_node->get_value();
                current_node = current_node->get_pointer();
                cout<<"]"<<endl;
                i = 0;
            }
            else{
                cout<<"Current state of the list: []"<<endl;
            }
        };
};

class Collector{ //Elements are added at the start of the list, when an element is removed, its removed from the beginning, and the element it points to becomes the new start. LIFO
    public:
        Node* start; //contains the memory position of the first element in the list
        int length = 0; //length of the collector
        Node* old_start;
        Node* current_node;
        int i = 0;
        void insert_memory_address(Node* memory_address){ //Takes the memory address of the node that's being deleted and stores it in collector
            if (length != 0){                
                memory_address->set_pointer(start);
            }
            start = memory_address;
            length += 1;
        };
        bool verify_recycled(){ //verifies if there is a memory address that can be recycled
            if (length > 0){
                return true;
            }
            else{
                return false;
            }
        };
        Node* get_recycled_memory_address(){ //returns a reusable memory address, and removes it from collector
            old_start = start;
            if (length > 1){
                start = start->get_pointer();
            }
            length -= 1;
            std::cout<<"removed memory address is:"<<old_start<<endl;
            return old_start;            
        };
        void view_collector(){ //shows the memory addresses stored in collector
            if (length > 0){
                current_node = start; 
                cout<<"Current state of the collector: [";
                std::cout<<start;
                while(i < length-1){
                    cout<<", "<<current_node->get_pointer();
                    current_node = current_node->get_pointer();
                    i++;
                }
                cout<<"]"<<endl;
                i = 0;
            }
            else{
                cout<<"Current state of the collector: []"<<endl;
            }
        };

};

//global variables
List list;
Collector collector;

void * operator new(size_t size){ //overloaded the method new
    if (collector.verify_recycled() == true){
    	cout<<"A memory address has been reused"<<endl;
        void * pointer = collector.get_recycled_memory_address();
        return pointer;
    } 
    else{
    	cout<<"A new memory slot has been called"<<endl;
        void * pointer = malloc(size);
        return pointer;
    }
}

void operator delete(void * pointer){ //overloaded the method delete
    cout<<"Delete has been called"<<endl;
    list.remove_node(); 
    collector.insert_memory_address((Node*) pointer);
}

int main(){
    bool on = true;
	int option;
	int value;
	int position;
    Node* starter;
	
	while(on){
		cout<<"Welcome to the memory management app! What would you like to do?"<<endl;
	    cout<<"Type the number corresponding to the option you'd like to pick"<<endl;
	    cout<<"1. Insert a Node to the list"<<endl;
	    cout<<"2. Modify a Node in the list"<<endl;
	    cout<<"3. Delete the first Node in the list"<<endl;
	    cout<<"4. Close the app"<<endl;
	    list.view_list();
	    collector.view_collector();
	    cin>>option;
		
		switch(option){
	    		case 1: 
                    {
                        cout<<"What number would you like to add to the list?"<<endl; 
                        Node* node = new Node;
                        cin>>value;
                        node->set_value(value);
                        list.insert_node(node);
                        break;
                    }
	    		case 2:
                    if (list.length > 0){
                        cout<<"Please specify which position of the list you would like to modify (Starting from 0)"<<endl;
                        cin>>position;
                        cout<<"Please specify the new value you would like it to have"<<endl;
                        cin>>value;
                        list.modify_element(position,value);
                    } else {
                        cout<<"The list is empty!!"<<endl;
                    }
	    			break;
	    		case 3:
                    if (list.length > 0){
                        delete list.get_start_pointer();
                        cout<<"The first element has been deleted from the list"<<endl;
                    } else {
                        cout<<"The list is empty!!"<<endl;
                    }
                    break;
	    		case 4:
	    			on = false;
	    			break;	
                default:
                    cout<<"Please choose a valid option"<<endl;
                    break;			
		}

        cout<<"\n"<<endl;
	}
	cout<<"The program will now shut down"<<endl;
	return 0;
}