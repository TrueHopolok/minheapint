#include "./minheap_int.h"
#include <format>
#include <iostream>
#include <stdexcept>
using namespace std;

////-----------------------------------------------------------------
//* Supporting functions

// Throw error if size does not equal expected value
void check_size(minheap_int &tested_heap, const size_t &expected_size)
{
    if (tested_heap.size() != expected_size)
        throw logic_error(__func__ + string(": unexpected size value"));
}

// Throw error if capcity does not equal expected value
void check_capacity_exact(minheap_int &tested_heap, const size_t &expected_capacity)
{
    if (tested_heap.capacity() != expected_capacity)
        throw logic_error(__func__ + string(": unexpected capacity value"));
}

// Throw error if capacity is smaller then expected value
void check_capacity_min(minheap_int &tested_heap, const size_t &expected_capacity)
{
    if (tested_heap.capacity() < expected_capacity)
        throw logic_error(__func__ + string(": unexpected capacity value"));
}

// Throw error if pushed element does not become top element
void check_push_top(minheap_int &tested_heap, const int &value_topush)
{
    tested_heap.push(value_topush);
    if (tested_heap.top() != value_topush)
        throw logic_error(__func__ + string(": unexpected top value"));
}

// Throw error if top element does not equal expected value
void check_push_any(minheap_int &tested_heap, const int &value_topush, const int &expected_top)
{
    tested_heap.push(value_topush);
    if (tested_heap.top() != expected_top)
        throw logic_error(__func__ + string(": unexpected top value"));
}

// Throw error if poped value does not equal expected value
void check_pop(minheap_int &tested_heap, const int &expected_pop)
{
    if (tested_heap.pop() != expected_pop)
        throw logic_error(__func__ + string(": unexpected poped value"));
}

// Throw error if capacity value does not equal expected value
void check_shrink(minheap_int &h, const int &expected_capacity)
{
    h.shrink();
    if (h.capacity() != expected_capacity)
        throw logic_error(__func__ + string(": unexpected capacity value"));
}

////-----------------------------------------------------------------
//* Test functions

/*
Definition of testing functions type
At start - output in stdin the name of the test
On error - throw exception
*/  
typedef void (*UnitTestFunction)();

// All tests cases in form of functions are realised in this array and then executed in the main function
UnitTestFunction tests[] = {
    []() //! All initializations of heap
    {
        cout << "init: ";
        minheap_int h1;
        check_size(h1, 0);
        check_capacity_exact(h1, 0);

        minheap_int h2(5);
        check_size(h2, 0);
        check_capacity_exact(h2, 5);

        int nums[5] = {3, 6, -2, 7, 1};
        minheap_int h3(nums, nums + 5);
        check_capacity_exact(h3, 5);
        int order[5] = {-2, 1, 3, 6, 7};
        for (int i = 5; i > 0; i--)
        {
            check_size(h3, i);
            check_pop(h3, order[5 - i]);
        }
        check_size(h3, 0);
        check_capacity_exact(h3, 5);
    },
    []() //! Memory expanding and shrinking
    {
        cout << "memory: ";
        minheap_int h(3);
        check_size(h, 0);
        check_capacity_exact(h, 3);
        h.reserve(5);
        check_size(h, 0);
        check_capacity_exact(h, 5);
        h.shrink();
        check_size(h, 0);
        check_capacity_exact(h, 0);
        h.reserve(10);
        check_push_top(h, 5);
        check_size(h, 1);
        check_capacity_exact(h, 10);
        h.reserve(5);
        check_size(h, 1);
        check_capacity_exact(h, 5);
        h.shrink();
        check_size(h, 1);
        check_capacity_exact(h, 1);
    },
    []() //! Pushing both regular and with expansion
    {
        cout << "push: ";
        minheap_int h(3);
        check_push_top(h, 2);
        check_push_any(h, 3, 2);
        check_push_top(h, -5);
        check_size(h, 3);
        check_capacity_exact(h, 3);
        check_push_any(h, 7, -5);
        check_push_top(h, -5);
        check_size(h, 5);
        check_capacity_min(h, 5);
    },
    []() //! Poping both regular and on empty
    {
        cout << "pop: ";
        int nums[3] = {3, -5, 2};
        minheap_int h(nums, nums + 3);
        check_pop(h, -5);
        check_pop(h, 2);
        check_pop(h, 3);
        check_size(h, 0);
        check_capacity_exact(h, 3);
        try
        {
            h.pop();
            throw logic_error("test_func: unexpected success");
        }
        catch (...)
        {
        }
    },
};

// Main functions that runs all tests in the array and counts results, outputing all needed tests
int main()
{
    cout << "------------------------------" << endl
         << "TESTING STARTED" << endl
         << endl;
    const int tests_amount = sizeof(tests) / sizeof(tests[0]);
    int tests_failed = 0;
    for (int i = 0; i < tests_amount; i++)
    {
        try
        {
            tests[i]();
            cout << "pass" << endl;
        }
        catch (logic_error e)
        {
            cout << "failed: " << e.what() << endl;
            tests_failed++;
        }
        catch (...)
        {
            cout << "failed: exception unknown or lacking implementation" << endl;
            tests_failed++;
        }
    }
    cout << endl;
    if (tests_failed)
        cout << "TESTING FAILED" << endl;
    else
        cout << "TESTING SUCCEEDED" << endl;
    cout << "pass/fail | " << (tests_amount - tests_failed) << "/" << tests_failed << endl
         << "------------------------------" << endl;
}