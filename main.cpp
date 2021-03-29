#include <iostream>
#include <string.h>

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct Node{
	string name, age, bp; //bp = blood pressure
	Node *next;
	
};

struct QueueLinkedList{
	int value, x;
	int count = 0;
	int size = 0;
	Node *front, *front1, *rear, *rear1, *head, *head1;
	
	void init(){
		front = front1 = rear = rear1 = head = head1 = NULL;
	}
	
	bool is_empty(){
		return (front == NULL && rear == NULL);
	}
	
	void make_empty(){
		Node *p = front;
		while(p != NULL){
			delete p;
			p = p->next;
		}
	}
	
	void set_size(int x){
		size = x;
	}
	
	int get_size(){
		return size;
	}
	
	void enqueue(string x, int y, int z){
		Node *tmp = new Node;
		tmp->name = x;
		tmp->age = y;
		tmp->bp = z;
		tmp->next = NULL;
		
		if(is_empty()){
			front = rear = tmp;
		} else if(count >= size) {
			if(front1 = NULL){
				front1 = rear1 = tmp;	
			} else {
				rear1->next = tmp;
				rear1 = tmp;
			}
		} else {
			rear->next = tmp;
			rear = tmp;
		}
		count++;
	}
	
	void dequeue(){
		if(count <= size){
			Node *tmp = front;
			tmp = tmp->next;
			delete tmp;
		} else if(count > size){
			Node *tmp = front;
			tmp = tmp->next;
			delete tmp;
			
			if(size == 2){
				Node *tmp  = front1;
				Node *done = front1;
				tmp = front1->next;
				front = rear;
				front->next = tmp;
				rear = done;
				rear->next = NULL;
			} else if(size > 2){
				Node *tmp = front1;
				tmp = tmp->next;
				rear = front->next;
				rear->next = tmp;
				rear = tmp;
				rear->next = NULL;
			}
		}
		count--;
	}
	
	void skip(){
		
	}
	
	void print(){
		if(is_empty()){
			cout << "-" << endl;
		} else {
			Node *p = front;
			while(p != NULL){
				cout << "ANTRE " << p->name << endl;
				p = p->next;
			}
		}
	}
};
int main(int argc, char** argv) {
	QueueLinkedList qll;
	string x;
	int y, z;
	getline(cin, x);
	string a = x.substr(0, 4);
	string b = x.substr(0, 6);
	string c = x.substr(0, 7);
	
	if(a == "BARU"){
		if(qll.size > qll.count){
			cout << "ANTRE "; 
		} else {
			cout << "TUNGGU ";
		}
		
		string name;
		string e = x.substr(5, sizeof(x));
		name = e;
		
		
	}
	
	if(b >= 60){
		cout << "TOLAK ";
	}
	
	qll.init();
	 
	qll.enqueue(x, y, z);
	qll.print();
	
	
	return 0;
}
