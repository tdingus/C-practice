/*
  heap sort of an array in n log n time
 */
#include <iostream>

struct ArraySort {
  static void heapSort(int array[], int size); //O(n logn)
  static void heapify(int array[], int index, int size); //O(log n)
  static void createMaxHeap(int array[], int size); //O(n), it's magical
};

void ArraySort::createMaxHeap(int array[], int size) {
  for (int i = size/2 - 1; i >= 0; i--) {
    ArraySort::heapify(array, i, size);
  }
}

void ArraySort::heapify(int array[], int index, int size) { //assume left/child root subtrees are heaps
  int leftChild = 2*(index+1)-1; // heap def
  int rightChild = 2*(index+1);
  int largest = index;
  if (leftChild < size && array[leftChild] > array[largest])
    largest = leftChild;
  if (rightChild < size && array[rightChild] > array[largest])
    largest = rightChild;
  if (largest != index) { // swap
    int tmp = array[index];
    array[index] = array[largest];
    array[largest] = tmp;
    ArraySort::heapify(array, largest, size); // continue down, max log n times
  }
}

void ArraySort::heapSort(int array[], int size) {
  if (size < 2) return;

  ArraySort::createMaxHeap(array, size); // max element is index 0, move to end
  int done = 0; // number to ignore at the end
  for (int i = 0; i < size; i++) {
    int tmp = array[size - done - 1];
    array[size - done - 1] = array[0];
    array[0] = tmp;
    done++;
    heapify(array,0,size-done);
  }
}

int main() {
  int test1[] = {22, 20, 14, 26, 13, 14, 10, 0};
  int size1 = 8;
  ArraySort::heapSort(test1, size1);
  for (int i = 0; i < size1; i++)
    std::cout << test1[i] << std::endl;
};
