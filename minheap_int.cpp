#include "./minheap_int.h"

void minheap_int::push_up(const int &index)
{
    if (index <= 0)
        return;
    const int parent = (index - 1) >> 1;
    if (data[index] >= data[parent])
        return;
    else
    {
        const int tmp = data[index];
        data[index] = data[parent];
        data[parent] = tmp;
    }
    push_up(parent);
}

void minheap_int::push_down(const int &index)
{
    const int left = (index << 1) + 1;
    if (left >= len)
        return;
    const int right = (left + 1 < len) && (data[left + 1] < data[left]) ? left + 1 : left;
    if (data[right] >= data[index])
        return;
    else
    {
        const int tmp = data[index];
        data[index] = data[right];
        data[right] = tmp;
    }
    push_down(right);
}

minheap_int::minheap_int()
{
    data = new int[0];
    len = 0;
    cap = 0;
}

minheap_int::minheap_int(const size_t &size_toreserve)
{
    data = new int[size_toreserve];
    len = 0;
    cap = size_toreserve;
}

minheap_int::minheap_int(int *array_begin, int *array_end)
{
    cap = array_end - array_begin;
    if (cap < 0)
        throw std::logic_error("array's end pointer is before array's start pointer");
    len = cap;
    data = new int[cap];
    for (int i = 0; i < cap; i++)
        data[i] = *(array_begin + i);
    for (int i = cap - 1; i >= 0; i--)
        push_up(i);
}

minheap_int::~minheap_int()
{
    delete[] data;
}

void minheap_int::reserve(const size_t &size_toreserve)
{
    if (cap == size_toreserve)
        return;
    if (len > size_toreserve)
        throw std::logic_error("size to reserve is smaller then amount of stored values in the heap");
    int *tmp = (int *)realloc(data, size_toreserve);
    if (tmp == nullptr)
        throw std::runtime_error("realloc failed to reallocate a memory");
    data = tmp;
    cap = size_toreserve;
}

void minheap_int::shrink()
{
    if (len == cap)
        return;
    if (len == 0) {
        delete[] data;
        data = new int[0];
        cap = 0;
        return;
    }
    int *tmp = (int *)realloc(data, len);
    if (tmp == nullptr)
        throw std::runtime_error("realloc failed to reallocate a memory");
    data = tmp;
    cap = len;
}

bool minheap_int::empty()
{
    return len == 0;
}

size_t minheap_int::size()
{
    return len;
}

size_t minheap_int::capacity()
{
    return cap;
}

int minheap_int::top()
{
    if (len == 0)
        throw std::logic_error("trying to get a top element of an empty heap");
    return data[0];
}

void minheap_int::push(const int &value_topush)
{
    if (len == cap)
    {
        if (cap >= BIG_CAP)
            reserve(cap + BIG_CAP);
        else if (cap < SMALL_CAP)
            reserve(cap + SMALL_CAP);
        else
            reserve(cap << 1);
    }
    data[len] = value_topush;
    push_up(len++);
}

int minheap_int::pop()
{
    if (len == 0)
        throw std::logic_error("trying to delete element from an empty heap");
    const int value = data[0];
    data[0] = data[--len];
    push_down(0);
    return value;
}

#ifdef DEBUG
void minheap_int::debug()
{
    std::printf("\nlen = %3lu  |  cap = %3lu\n", len, cap);
    if (len != 0)
    {
        std::printf("values: ");
        for (int i = 0; i < len; i++)
            std::printf("%d; ", data[i]);
        std::printf("\n\n");
    }
}
#endif
