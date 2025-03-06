#include <stdexcept>

#define BIG_CAP 1000000
#define SMALL_CAP 10

class minheap_int
{
private:
    //* Class attributes

    int *data;  // All values
    size_t len; // Current amount of values
    size_t cap; // Current size of data array

    //* Methods required for insertion/deletion

    /**
     * @brief
     * Pushes up element till either its parent is smaller or it reached the top
     *
     * ---
     *
     * @param index the index of an element that needs to be pushed up in the heap
     *
     * ---
     *
     * ? Time complexity: `O(log[n]), n - length`
     * 
     */
    void push_up(const int &index);

    /**
     * @brief
     * Pushes down element till either its children are bigger or it reached the bottom
     *
     * ---
     *
     * @param index the index of an element that needs to be pushed down in the heap
     *
     * ---
     *
     * ? Time complexity: `O(log[n]), n - size`
     * 
     */
    void push_down(const int &index);

public:
    //* Constructos and destructor

    /**
     * @brief
     * Constructor create an empty heap with capacity 0
     *
     * ---
     *
     * @throw `std::bad_alloc` - new failed to allocate a memory
     *
     * ---
     *
     * ? Time complexity: `O(1)`
     * 
     */
    minheap_int();

    /**
     * @brief
     * Constructor create an empty heap with given capacity
     *
     * ---
     *
     * @param size_toreserve capacity of a new heap
     *
     * @throw `std::bad_alloc` - new failed to allocate a memory
     *
     * ---
     *
     * ? Time complexity: `O(n), n - size`
     * 
     */
    minheap_int(const size_t &size_toreserve);

    /**
     * @brief
     * Constructor builds heap from the given array
     *
     * ---
     *
     * The constructor copies an array into heap's data array.
     * After that all elements are pushed up starting from the end, sorting the heap in the process.
     * Does not modify the original array.
     *
     * @param array_begin pointer to the start of an integer array
     * @param array_end pointer to the end of an integer array
     *
     * @throw `std::bad_alloc` - new failed to allocate a memory
     * @throw `std::logic_error` - array's end pointer is before array's start pointer
     *
     * ---
     *
     * ? Time complexity: `O(n*log[n]), n - size`
     * 
     */
    minheap_int(int *array_begin, int *array_end);

    /**
     * @brief
     * Destructor of an heap that free allocated memory
     *
     * ---
     *
     * ? Time complexity: `O(n), n - capacity`
     * 
     */
    ~minheap_int();

    //* Memory related methods

    /**
     * @brief
     * Allocates memory for a given capacity
     *
     * ---
     *
     * @param size_toreserve capacity to which heap will be shrunk/expanded
     *
     * @throw `std::runtime_error` - realloc failed to reallocate a memory
     * @throw `std::logic_error` - size to reserve is smaller then amount of stored values in the heap
     *
     * ---
     *
     * ? Time complexity: `O(n), n - capacity`
     * 
     */
    void reserve(const size_t &size_toreserve);

    /**
     * @brief
     * Shrink heap for its capacity to match size
     *
     * ---
     *
     * Reallocates memory of the heap to match the current amount of the elements in the heap.
     *
     * @throw `std::runtime_error` - realloc failed to reallocate a memory
     *
     * ---
     *
     * ? Time complexity: `O(n), n - capacity`
     * 
     */
    void shrink();

    /**
     * @brief
     * Returns if heap is empty
     *
     * ---
     *
     * @return `empty : bool - is amount of elements in heap equal to 0`
     *
     * ---
     *
     * ? Time complexity: `O(1)`
     * 
     */
    bool empty();

    /**
     * @brief
     * Returns size of a heap
     *
     * ---
     *
     * @return `size : size_t - current amount of elements in the heap`
     *
     * ---
     *
     * ? Time complexity: `O(1)`
     * 
     */
    size_t size();

    /**
     * @brief
     * Returns capacity of a heap
     *
     * ---
     *
     * @return `cap : size_t - maximum amount of elements in the heap`
     *
     * ---
     *
     * ? Time complexity: `O(1)`
     * 
     */
    size_t capacity();

    //* Insertion/deletion

    /**
     * @brief
     * Returns top element of the heap
     *
     * ---
     *
     * @return `value : int - the smallest element in the heap`
     *
     * @throw `std::logic_error` - trying to get a top element of an empty heap
     *
     * ---
     *
     * ? Time complexity: `O(1)`
     * 
     */
    int top();

    /**
     * @brief
     * Insert element in to the heap
     *
     * ---
     *
     * Insert element into after the last placed element and then pushes it up.
     *
     * If there is not enough space, tries to allocate more memory:
     *
     * - If heap's capacity is smaller than `SMALL_CAP`, will increase its size by `SMALL_CAP` constant;
     *
     * - If heap's capacity is bigger than `BIG_CAP`, will increase its size by `BIG_CAP` constant;
     *
     * - In any other case will double the capacity.
     *
     * @param value_topush value to push into the heap
     *
     * @throw `std::runtime_error` - realloc failed to reallocate a memory
     *
     * ---
     *
     * ? Time complexity:
     *
     * - Amortized: `O(log[n]), n - size`
     *
     * - Worst case: `O(n), n - size`
     * 
     */
    void push(const int &value_topush);

    /**
     * @brief
     * Delete the top element of the heap and returns it
     *
     * ---
     *
     * Pop the top element and placing previously last element at the top's place.
     * Then new top element pushes down, so heap's properties are sustained.
     *
     * @throw `std::logic_error` - trying to delete element from an empty heap
     *
     * ---
     *
     * ? Time complexity: `O(log[n]), n - size`
     *
     */
    int pop();

    //* Debuging methods

#ifdef DEBUG
#include <cstdio>
    /**
     * @brief
     * Output into std the all class attributes of the heap and outputing all elements
     *
     * ---
     *
     * ? Time complexity: `O(n), n - size`
     * 
     */
    void debug();
#endif
};