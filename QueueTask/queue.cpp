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
		
		int dequeue()
		{
			if(isEmpty())
			{
				cout<<"Queue underflow"<<endl;
				return -1;
			}
			
			int value = arr[frontIdx];
			frontIdx = (frontIdx + 1) % capacity;
			currentSize--;
			
			return value;
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
		
		void firingSize(int sizeArr1, int sizeArr2)
		{
		    Queue q;
		
		    cout<<"loading the magazine of 100 bullets capacity"<<endl;
		    for (int i = 0; i < sizeArr1; i++)
		    {
		        cout<<"loading bullet : "<<i + 1<<endl;
		        q.enqueue(i + 1);
		    }
		
		    int *arr2 = new int[sizeArr2];
		
		    cout<<"\n\ndequeuing bullets and loading in another magazine of capacity 20"<<endl;
		    for (int i = 0; i < sizeArr2; i++)
		    {
		        arr2[i] = q.dequeue();
		        cout<<"dequeued and loaded again : "<<arr2[i]<<endl;
		    }
		
		    int current20 = sizeArr2;
		    int queueRemaining = sizeArr1 - sizeArr2;
		
		    cout<<"\n\nStarting firing cycle...\n\n";
		
		    while(queueRemaining > 0)
		    {
		        int firedFromArr2 = arr2[current20 - 1];
		        cout<<"Fired from arr2: "<<firedFromArr2<<endl;
		        current20--;
		        
		        int newBullet = q.dequeue();
		        cout<< "Taken from queue: "<< newBullet<<endl;
		        queueRemaining--;

		        arr2[current20] = newBullet;
		        current20++;
		
		        cout<<"arr2 refilled back to 20 bullets\n\n";
		    }
		
		    delete[] arr2;
		}


};


int main(){
	
	Queue q;
	q.firingSize(100, 20);
//	q.firingSize(100, 20);
//	
//	cout<<"Enqueue 10, 20, 30, 40\n";
//	q.enqueue(10);
//	q.enqueue(20);
//	q.enqueue(30);
//	q.enqueue(40);
//	q.print();
//	
//	cout<<"Front element : "<<q.front()<<"\n";
//	
//	cout<<"Dequeue two elements\n";
//	q.dequeue();
//	q.dequeue();
//	q.print();
//	cout<<"The front element now : "<<q.front()<<"\n";
//	
//	cout<<"Enqueue 50, 60, 70 (This will cause resize internally)\n";
//	q.enqueue(50);
//	q.enqueue(60);
//	q.enqueue(70);
//	q.print();
//	
//	cout<<"Dequeuing all elements: \n";
//	while(!q.isEmpty())
//	{
//		cout<<"Front : "<<q.front()<<" --> dequeued\n";
//		q.dequeue();
//	}
//	
//	q.dequeue();
//	
	
	
	return 0;
}
