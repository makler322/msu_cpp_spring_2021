#include <cassert>
#include <iostream>
#include <vector>

template < class T >
class Allocator
{
public:
    T* allocate(size_t count);
    void deallocate(T* ptr);
};


template < class Iter >
class Iterator
{
public:
    Iterator(Iter pointer_cur, Iter pointer_end, bool rev = false);
    Iterator(const Iterator& I);
    Iterator(Iterator&& I);
    Iterator& operator = (const Iterator& I);
    Iterator& operator = (Iterator&& I);
    
    bool operator == (const Iterator& I) const;
    bool operator != (const Iterator& I) const;
    void operator ++ ();
    auto operator * () const;

private:
    Iter _current = nullptr;
    Iter _end = nullptr;
    bool _rev = false;
};


template < class T, class Alloc = Allocator<T> >
class Vector
{
public:
    typedef T* iterator;
    typedef T value_type;

    Vector(size_t count = 0);
    Vector(size_t count, const T& value);
    Vector(std::initializer_list<T> lst);
    Vector(const Vector& V);
    Vector(Vector&& V);
    Vector& operator = (const Vector& V);
    Vector& operator = (Vector&& V);
    ~Vector();
    
    const T& operator [] (size_t index) const;
    T& operator [] (size_t index);
    
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    
    void emplace_back(T&& value);
    template < class... VT >
    void emplace_back(T&& value, VT&&... values);
    
    bool empty() const;
    size_t size() const;
    void clear();
    
    Iterator<iterator> begin();
    Iterator<iterator> rbegin();
    Iterator<iterator> end();
    Iterator<iterator> rend();
    
    void resize(size_t count);
    void resize(size_t count, const T& value);
    void reserve(size_t count);
    size_t capacity() const;
    
private:
    size_t _size = 0;
    size_t _capacity = 0;
    T* _vect = nullptr;
    Alloc _Alloc;
};


template < class T >
T* Allocator<T> :: allocate(size_t count)
{
    if (count == 0)
    {
        return nullptr;
    }
    return new T [count];
}

template < class T >
void Allocator<T> :: deallocate(T* ptr)
{
    delete [] ptr;
}

template < class Iter >
Iterator<Iter> :: Iterator(Iter pointer_cur, Iter pointer_end, bool rev)
    : _current(pointer_cur), _end(pointer_end), _rev(rev){}

template < class Iter >
Iterator<Iter> :: Iterator(const Iterator& I)
{
    _current = I._current;
    _end = I._end;
    _rev = I._rev;
}

template < class Iter >
Iterator<Iter> :: Iterator(Iterator&& I)
{
    _current = std::move(I._current);
    _end = std::move(I._end);
    _rev = I._rev;
    I._current = nullptr;
    I._end = nullptr;
    I._rev = false;
}

template < class Iter >
Iterator<Iter>& Iterator<Iter> :: operator = (const Iterator& I)
{
    if (_current == I._current)
    {
        return *this;
    }
    _current = I._current;
    _end = I._end;
    _rev = I._rev;
    return *this;
}

template < class Iter >
Iterator<Iter>& Iterator<Iter> :: operator = (Iterator&& I)
{
    if (_current == I._current)
    {
        return *this;
    }
    _current = std::move(I._current);
    _end = std::move(I._end);
    _rev = I._rev;
    I._current = nullptr;
    I._end = nullptr;
    I._rev = false;
    return *this;
}

template < class Iter >
bool Iterator<Iter> :: operator == (const Iterator& I) const
{
    return _current == I._current;
}

template < class Iter >
bool Iterator<Iter> :: operator != (const Iterator& I) const
{
    return !(_current == I._current);
}

template < class Iter >
void Iterator<Iter> :: operator ++ ()
{
    if (_current != _end)
    {
        if (!_rev)
        {
            ++_current;
        }
        else
        {
            --_current;
        }
    }
}

template < class Iter >
auto Iterator<Iter> :: operator * () const
{
    return *_current;
}


template < class T, class Alloc >
Vector<T, Alloc> :: Vector(size_t count) :
    _size(count), _capacity(2*_size), _vect(_Alloc.allocate(_capacity)){}

template < class T, class Alloc >
Vector<T, Alloc> :: Vector(size_t count, const T& value) :
    _size(count), _capacity(2*_size), _vect(_Alloc.allocate(_capacity))
{
    for (size_t i = 0; i < _size; i++)
    {
        _vect[i] = value;
    }
}

template < class T, class Alloc >
Vector<T, Alloc> :: Vector(std::initializer_list<T> lst) :
    _size(lst.size()), _capacity(2*_size), 
    _vect(_Alloc.allocate(_capacity))
{
    size_t i = 0;
    auto current = lst.begin();
    const auto end = lst.end();
    while (current != end)
    {
        _vect[i++] = *current++;
    }
}

template < class T, class Alloc >
Vector<T, Alloc> :: Vector(const Vector& V) :
    _size(V._size), _capacity(V._capacity), 
    _vect(_Alloc.allocate(_capacity))
{
    for (size_t i = 0; i < _size; i++)
    {
        _vect[i] = V._vect[i];
    }
}

template < class T, class Alloc >
Vector<T, Alloc> :: Vector(Vector&& V) :
    _size(std::move(V._size)), _capacity(std::move(V._capacity))
{
    _vect = V._vect;
    V._vect = nullptr;
    V._size = 0;
    V._capacity = 0;
}

template < class T, class Alloc >
Vector<T, Alloc>& Vector<T, Alloc> :: operator = (const Vector& V)
{
    if (this == &V)
    {
        return *this;
    }
    _Alloc.deallocate(_vect);
    _size = V._size;
    _capacity = V._capacity;
    _vect = _Alloc.allocate(_capacity);
    for (size_t i = 0; i < _size; i++)
    {
        _vect[i] = V._vect[i];
    }
    return *this;
}

template < class T, class Alloc >
Vector<T, Alloc>& Vector<T, Alloc> :: operator = (Vector&& V)
{
    if (this == &V)
    {
        return *this;
    }
    _Alloc.deallocate(_vect);
    _size = std::move(V._size);
    _capacity = std::move(V._capacity);
    _vect = V._vect;
    V._vect = nullptr;
    V._size = 0;
    V._capacity = 0;
    return *this;
}

template < class T, class Alloc >
Vector<T, Alloc> :: ~Vector()
{
    _Alloc.deallocate(_vect);
}

template < class T, class Alloc >
const T& Vector<T, Alloc> :: operator [] (size_t index) const
{
    if (index < _size)
    {
        return _vect[index];
    }
    throw std::out_of_range("Wrong index");
}

template < class T, class Alloc >
T& Vector<T, Alloc> :: operator [] (size_t index)
{
    if (index < _size)
    {
        return _vect[index];
    }
    throw std::out_of_range("Wrong index");
}

template < class T, class Alloc >
void Vector<T, Alloc> :: push_back(const T& value)
{
    if (_size == _capacity)
    {
        resize(_size + 1);
        _size--;
    }
    _vect[_size++] = value;
}

template < class T, class Alloc >
void Vector<T, Alloc> :: push_back(T&& value)
{
    if (_size == _capacity)
    {
        resize(_size + 1);
        _size--;
    }
    _vect[_size++] = std::move(value);
}

template < class T, class Alloc >
void Vector<T, Alloc> :: pop_back()
{
    if (_size > 0)
    {
        _size--;
    }
}

template < class T, class Alloc >
void Vector<T, Alloc> :: emplace_back(T&& value)
{
    push_back(std::forward<T>(value));
}

template < class T, class Alloc >
template < class... VT >
void Vector<T, Alloc> :: emplace_back(T&& value, VT&&... values)
{
    push_back(std::forward<T>(value));
    emplace_back(std::forward<VT>(values)...);
}

template < class T, class Alloc >
bool Vector<T, Alloc> :: empty() const
{
    return _size == 0;
}

template < class T, class Alloc >
size_t Vector<T, Alloc> :: size() const
{
    return _size;
}

template < class T, class Alloc >
void Vector<T, Alloc> :: clear()
{
    _size = 0;
}

template < class T, class Alloc >
Iterator<typename Vector<T, Alloc>::iterator> 
    Vector<T, Alloc> :: begin()
{
    return Iterator<typename Vector<T, Alloc>::iterator>
        (_vect, _vect + _size);
}

template < class T, class Alloc >
Iterator<typename Vector<T, Alloc>::iterator> 
    Vector<T, Alloc> :: rbegin()
{
    return Iterator<typename Vector<T, Alloc>::iterator> 
        (_vect + _size - 1, _vect - 1, true);
}

template < class T, class Alloc >
Iterator<typename Vector<T, Alloc>::iterator> 
    Vector<T, Alloc> :: end()
{
    return Iterator<typename Vector<T, Alloc>::iterator>
        (_vect + _size, _vect + _size);
}

template < class T, class Alloc >
Iterator<typename Vector<T, Alloc>::iterator>
    Vector<T, Alloc> :: rend()
{
    return Iterator<typename Vector<T, Alloc>::iterator> 
        (_vect - 1, _vect - 1, true);
}

template < class T, class Alloc >
void Vector<T, Alloc> :: resize(size_t count)
{
    _capacity = 2 * count;
    T* tmp = _Alloc.allocate(_capacity);
    for (size_t i = 0; i < std::min(_size, count); i++)
    {
        tmp[i] = _vect[i];
    }
    _Alloc.deallocate(_vect);
    _size = count;
    _vect = std::move(tmp);
}

template < class T, class Alloc >
void Vector<T, Alloc> :: resize(size_t count, const T& value)
{
    _capacity = 2 * count;
    T* tmp = _Alloc.allocate(_capacity);
    for (size_t i = 0; i < std::min(_size, count); i++)
    {
        tmp[i] = _vect[i];
    }
    for (size_t i = std::min(_size, count); i < count; i++)
    {
        tmp[i] = value;
    }
    _Alloc.deallocate(_vect);
    _size = count;
    _vect = std::move(tmp);
}

template < class T, class Alloc >
void Vector<T, Alloc> :: reserve(size_t count)
{
    if (count > _capacity)
    {
        _capacity = count;
        T* tmp = _Alloc.allocate(_capacity);
        for (size_t i = 0; i < _size; i++)
        {
            tmp[i] = _vect[i];
        }
        _Alloc.deallocate(_vect);
        _vect = tmp;
    }
}

template < class T, class Alloc >
size_t Vector<T, Alloc> :: capacity() const
{
    return _capacity;
}
