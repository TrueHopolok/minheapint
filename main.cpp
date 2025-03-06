/*
Vadim Truhanov, vt24011

Honored task:
Given array as input via stdin. Sort it using customly written heap.
Write a second program to test a heap functionality.

Made at 6.march.2025
*/
#include "./minheap_int.h"
#include <iostream>
using namespace std;
int main()
{
    cout << "Enter amount of elements in an array:\n>> ";
    int amount;
    cin >> amount;
    if (amount <= 0)
    {
        cout << "Error: entered value must be possitive" << endl;
        return 0;
    }
    cout << "Enter values in any order:\n>> ";
    int *array = new int[amount];
    for (int i = 0; i < amount; i++)
    {
        cin >> array[i];
    }
    minheap_int h(array, array + amount);
    cout << "Sorted version of your array:\n>> ";
    while (!h.empty())
    {
        cout << h.pop() << " ";
    }
    cout << endl;
    return 0;
}