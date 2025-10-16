#include<iostream>
#include<sstream>
#include<fstream>
using namespace std;

class Node
{
	public:
		string ip;
		Node *next;
		Node *prev;
	
		Node(string ip)
		{
			this->ip = ip;
			this->next = nullptr;
			this->prev = nullptr;
		}		
};

class doublyLinkedList
{
	private:
		Node *head;
		Node *tail;
		int length;
	
	public:
		doublyLinkedList()
		{
			head = nullptr;
			tail = nullptr;
			length = 0;
		}
		
		void insertAtBeginning(string ip)
		{
			Node *n = new Node(ip);
			
			if(head == nullptr)
			{
				head = tail = n;
			}
			else
			{
				n->next = head;
				head->prev = n;
				head = n;
			}					
		}
		
		void loadFromFile(string filename)
		{
		    ifstream file(filename);
		    if (!file)
		    {
		        cout << "Error: Could not open file!" << endl;
		        return;
		    }
		
		    string line;
		    getline(file, line);
		    file.close();
		    
		    stringstream ss(line);
		    string ip;
		
		    while (getline(ss, ip, ','))
		    {    
			    insertAtBeginning(ip);
		    }
		
		    cout<<"All IP addresses are added successfully\n";
		}
		    
		void dispalyForward()
		    {
		    	Node *curr = head;
		    	while(curr != nullptr)
		    	{
		    		cout<<curr->ip<<endl;
		    		curr = curr->next;
				}
			}
			
		void displayBackward()
		{
			Node *temp = tail;
			while(temp != nullptr)
			{
				cout<<temp->ip<<endl;
				temp = temp->prev;
			}
		}
			
		void clear()
		{
			Node *curr = head;
			while(curr != nullptr)
			{
				Node *temp = curr;
				curr = curr->next;
				delete temp;
			}
			head = nullptr;
			tail = nullptr;
			length = 0; 
		}
		
		~doublyLinkedList()
		{
			clear();
		}
			
			
					
};

int main(){
	doublyLinkedList *ipAddresses = new doublyLinkedList();
	
	ipAddresses->loadFromFile("Addresses.txt");
	cout<<"\n*********Forward********\n\n";
	ipAddresses->dispalyForward();
	cout<<"\n************************\n";
	
	cout<<"\n*********Backward*******\n\n";
	ipAddresses->displayBackward();
	cout<<"\n************************\n\n";
	
	delete ipAddresses;
	return 0;
}
