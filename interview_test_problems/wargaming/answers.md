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
2. Если сложность алгоритма ниже то соответсвенно кол-во инструкций, а значит и кол-во тиков будет меньше.
3. Компилятор может оптимизировать некоторые из циклов используя анролинг или векторные инструкции благодаря чему снизится кол-во тиков.
4. Можно было бы принимать в качестве параметра указатель (int* res) на заранее выделеную память для того, чтобы не производить копирование отсортированого массива обратно в исходный массив за линейное время.

```
void radix_sort_b16(int* a, int len)
{
    int max = find_max(a, len);
    int res[len];
    int digits[16];
    
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
        
        for(int i = 0; i < len; ++i)
        {
            a[i] = res[i];
        }
    }
}
```

