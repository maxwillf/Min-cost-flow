#include <stdio.h>
#include <iterator>
#include <vector>

template <typename KeyType,typename ValueType>

class Heap{

	private:

		struct Node{
			KeyType key;
			ValueType value;

			Node(void){}

			Node(KeyType key, ValueType value){
				this->key = key;
				this->value = value;
			}

			bool operator < (Node a) const{
				if(this->key < a.key){
					return true;
				}
				else
					return false;
			}
			bool operator > (Node a) const{
				if(this->key == a.key){
					return false;
				}

				else 
					return !(*this < a);
			}
		};

	private:
		int size;
		int capacity;
		Node* heap;


		/*		void reajustPush(int index);
				void reajustPop(int index);
				void realloc(void);
				void swap(int index, int secondIndex);*/

	public:
		//		Heap(std::vector<Node> &vec);
		/*		~Heap();
				void push(KeyType key,ValueType value); 
				Node pop(); 
				void printAll(void);*/

		Heap(){

			size = 0;
			capacity = 4;
			heap = new Node [capacity];
		}
		/*
		   Heap::Heap(std::vector<Node> &vec){

		   size = std::end(vec) - std::begin(vec);
		   capacity = size;
		   heap = new Node[size];


		   auto it = vec.begin();
		   heap[0] = *it++;
		   int index = 1;

		   for(; it != vec.end();++it){

		   heap[index].key = it->key;        
		   heap[index].value = it->value;        
		   reajustPush(index);
		   index++;
		   }
		   }*/


		~Heap(){
			delete heap;
		}

		void push(KeyType key,ValueType value){
			Node node(key,value);

			if(size+1 > capacity){
				realloc();
			}
			heap[size++] = node;
			reajustPush(size-1);
		}

		ValueType pop(void){
			Node aux = heap[0];
			heap[0] = heap[--size];
			reajustPop(0);
			return Node.value;
		}

		bool isEmpty(void){
			return size == 0;
		}

		void printAll(void){

			for (int i = 0; i < size; ++i) {
				printf("%d %d \n", heap[i].key,heap[i].value);
			}
			printf("Size and capacity %d %d \n",size,capacity);
		}

		void swap(int index, int secondIndex){

			Node aux = this->heap[index];
			this->heap[index] = heap[secondIndex];
			this->heap[secondIndex] = aux;

		}
		
		// todo
		void adjustPriority(KeyType key, ValueType value){

		}

		void reajustPush(int index){

			// if it is even
			if(index <= 0) return;

			if( (index-1) % 2 == 0){
				int parentIndex = (index-1)/2;
				if(heap[parentIndex] > heap[index]){
					swap(parentIndex, index);
					reajustPush(parentIndex);
				}
			}

			else{
				int parentIndex = (index-2)/2;
				if(heap[parentIndex] > heap[index]){
					swap(parentIndex, index);
				}
			}
		}

		void reajustPop(int index){

			if(index == size-1) return;

			if(index*2 +1 < size){
				if( heap[index*2 + 1] < heap[index] ){
					int childIndex = index*2 +1;
					swap(childIndex, index);
					reajustPop(childIndex);

				}
			}

			if(index*2 +2 < size){
				if(heap[index*2 +2] < heap[index]){
					int childIndex = index*2 +2;
					swap(childIndex, index);
					reajustPop(childIndex);
				}
			}
		}

		void realloc (void){
			capacity *= 2;
			Node * aux = new Node[capacity];

			for (int i = 0; i < size; ++i) {
				aux[i] = heap[i]; 
			}
			delete heap;
			heap = aux;
		}
};


