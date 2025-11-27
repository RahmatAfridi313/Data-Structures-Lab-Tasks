#include<iostream>
using namespace std;

class Queue{
	private:
		int *arr;
		int capacity;
		int frontIdx;
		int rearIdx;
		int currentSize;
		
		void resize()
		{
			int newCapacity = capacity*2;
			int *newArr = new int[newCapacity];
			
			for(int i=0; i<currentSize; i++)
			{
				newArr[i] = arr[(frontIdx + i) % capacity];
			}
			delete[] arr;
			arr = newArr;
			capacity = newCapacity;
			frontIdx = 0;
			rearIdx = currentSize;
			
		}
	
	public:
		Queue(int initialCapacity = 4)
		{
			capacity = initialCapacity;
			arr = new int[capacity];
			frontIdx = 0;
			rearIdx = 0;
			currentSize = 0;
		}
		
		~Queue()
		{
			delete[] arr;
		}
		
		bool isEmpty() const {
			if(currentSize == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
		int size() const {
			return currentSize;
		}
		
		void enqueue(int value)
		{
			if(currentSize == capacity)
			{
				resize();
			}
			
			arr[rearIdx] = value;
			rearIdx = (rearIdx + 1) % capacity;
			currentSize++;
		}
		
		void dequeue()
		{
			if(isEmpty())
			{
				cout<<"Queue underflow"<<endl;
				return;
			}
			
			frontIdx = (frontIdx + 1) % capacity;
			currentSize--;
		}
		
		int front() const {
			if(isEmpty())
			{
				cout<<"Queue is Empty! No front element.\n";
				return -1;
			}
			
			return arr[frontIdx];
			
		}
		
		void print() const {
			cout<<"Queue Elements : ";
			
			for(int i=0; i<currentSize; i++)
			{
				int index = (frontIdx + i) % capacity;
				cout<<arr[index]<<" ";
			}
			cout<<"\n";
		}
};


int main(){
	
	Queue q;
	
	cout<<"Enqueue 10, 20, 30, 40\n";
	q.enqueue(10);
	q.enqueue(20);
	q.enqueue(30);
	q.enqueue(40);
	q.print();
	
	cout<<"Front element : "<<q.front()<<"\n";
	
	cout<<"Dequeue two elements\n";
	q.dequeue();
	q.dequeue();
	q.print();
	cout<<"The front element now : "<<q.front()<<"\n";
	
	cout<<"Enqueue 50, 60, 70 (This will cause resize internally)\n";
	q.enqueue(50);
	q.enqueue(60);
	q.enqueue(70);
	q.print();
	
	cout<<"Dequeuing all elements: \n";
	while(!q.isEmpty())
	{
		cout<<"Front : "<<q.front()<<" --> dequeued\n";
		q.dequeue();
	}
	
	q.dequeue();
	
	
	
	return 0;
}
