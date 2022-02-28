# Task 1.
#### Version 1
 быстрее оператора% так как нет инструкций деления, но менее понятный и менее читабельный
 ```
bool isEven(int x) 
{
    return !(x & 1);
}
```
 #### Version 2
 читабельный, понятный, но медленее побитового
```
bool isEven(int value)
{
    return value%2==0;
} 
 ```
#
#
#
# Task 2.
#### Ring buffer 1:
Минусом можно назвать фиксированный размер, но зато плюс в том, что данные хранятся на стеке (если сам объект был создан на стэке), что позволяет избежать динамической аллокации и освобождения.
```
#include <iostream>
#include <cstring>
 
using namespace std;
 
template<typename T, size_t N>
class ring_buf
{
    T buf[N];
public:
    ring_buf()
    {
        memset(buf, 0, N * sizeof(T));
    }
 
    const T& operator[](int idx) const
    {
        return buf[idx % N];
    }
    
    T& operator[](int idx)
    {
        return buf[idx % N];
    }
};
```
#
#
#
#### Ring buffer 2: 
Минусом является то, что данные хранятся в хипе, а это значительно медленее варианта со стэком, но зато плюсом является изменяемый размер буффера.
```
#include <iostream>
#include <vector>
 
using namespace std;
 
template<typename T>
class dyn_ring_buf
{
    std::vector<T> buf;
public:
 
    dyn_ring_buf() = default;
    dyn_ring_buf(size_t n)
        : buf(n)
    {
    }
 
    const T& operator[](int idx) const
    {
        return buf[idx % buf.size()];
    }
    
    T& operator[](int idx)
    {
        return buf[idx % buf.size()];
    }
    
    void push_back(const T& val)
    {
        buf.push_back(val);
    }
    
    void push_back(T&& val)
    {
        buf.push_back(val);
    }
    
    size_t size() const
    {
        return buf.size();
    }
};
```
#
#
#
# Task 3.
#### Radix sort: 
1. Из всех сортировок что мне известны лучшим для сортировки чисел является радикс, так как его сложность даже лучше чем O(n*log(n)). 
2. Если сложность алгоритма ниже то соответсвенно кол-во инструкций, а значит и кол-во тиков, будет меньше.
3. Компилятор может оптимизировать некоторые из циклов используя анролинг или векторные инструкции благодаря чему снизится кол-во тиков.
4. Постарался избежать инструкций деления там где это возможно так как они довольно дорогие для процессора. 
5. Я выбрал основание b = 16 так как это позволит немного снизить кол-во итераций внешнего цикла по сравнению с b = 10, а так же облегчит осуществлять деление и умножение используя побитовые операции.
7. Нет лишнего O(n) копирования после обработки каждого порядка. Можно было бы так же ввести параметры int max, bool given_max и если given_max == true то можно было бы избежать линейного поиска максимума, но это не вписывается в контекст общего случая. 

```
int find_max(const int* arr, int len)
{
    int max = arr[0];
    for(int i = 1; i < len; i++)
    {
        if(arr[i] > max)
            max = arr[i];
    }
    return max;
}

// O(log_b(max) * (n + b)), where b is the base
// O(log_16(max) * (n + 16)), where b = 16
void radix_sort_b16(int* const arr, int len)
{
    int res_buf[len];
    int digits[16];
    
    int* a = arr;
    int* res = res_buf;
    
    int max = find_max(a, len);
    for(int order = 1; max > 0; order <<= 4, max >>= 4)
    {
        memset(digits, 0, sizeof(digits));
        
        for(int i = 0; i < len; ++i)
        {
            int digit = (a[i] / order) & 15;
            ++digits[digit];
        }
        
        for(int i = 1; i < 16; ++i)
        {
            digits[i] += digits[i - 1];
        }
        
        for (int i = len - 1; i >= 0; --i)
        {
            res[--digits[(a[i] / order) & 15]] = a[i];
        }
        
        int* tmp = a;
        a = res;
        res = tmp;
    }
    if(a == res_buf) 
    {
        for(int i = 0; i < len; ++i)
        {
            arr[i] = res_buf[i];
        }
    }
}
```

