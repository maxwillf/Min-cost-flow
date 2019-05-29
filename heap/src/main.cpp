#include "heap.cpp"
#include <iostream>
int main(int argc, char *argv[])
{
    Heap<int,int> heap;
	std::cout << heap.isEmpty() << std::endl;
    heap.push(5,6);
    heap.push(7,8);
    heap.push(9,2);
    heap.push(9,9);
    heap.push(9,9);
    heap.printAll();
    heap.pop();
    heap.push(2,9);
    heap.pop();
    heap.push(27,4);
    heap.push(100,5);
    heap.push(70,7);
    heap.push(30,19);
    heap.pop();
    heap.pop();
    heap.push(10,29);
    heap.pop();
    heap.push(30,79);
    heap.push(10,39);
    heap.push(60,9);
    heap.pop();
    heap.push(30,9);
    heap.pop();
    heap.pop();
    heap.printAll();
    return 0;
}
