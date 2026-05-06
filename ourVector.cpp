#include <iostream>

template <typename T>
class Vector {
private:
    T* _data;
    size_t _size;
    size_t _capacity;

public:
    // Конструкторы
    Vector(size_t size = 0, size_t capacity = 0);
    Vector(const T* array, size_t size);

    // Rule of 5
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;

    ~Vector();

    // Методы
    void push_back(const T& value);
    void pop_back();
    void clear();

    const T& at(size_t index) const;
    T& at(size_t index);

    size_t size() const;
    size_t capacity() const;
};
template <typename T>
Vector<T>::Vector(size_t size, size_t capacity)
    : _size(size),
      _capacity(capacity < size ? size : capacity),
      _data(new T[_capacity])
{
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = T();
    }
}

template <typename T>
Vector<T>::Vector(const T* array, size_t size)
    : Vector(size, size)
{
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = array[i];
    }
}

template <typename T>
Vector<T>::Vector(const Vector& other)
    : _size(other._size),
      _capacity(other._capacity),
      _data(new T[_capacity])
{
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this == &other) return *this;

    delete[] _data;

    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];

    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }

    return *this;
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : _data(other._data),
      _size(other._size),
      _capacity(other._capacity)
{
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this == &other) return *this;

    delete[] _data;

    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;

    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;

    return *this;
}

template <typename T>
Vector<T>::~Vector() {
    delete[] _data;
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (_size >= _capacity) {
        size_t new_capacity = (_capacity == 0 ? 1 : _capacity * 2);

        T* new_data = new T[new_capacity];

        for (size_t i = 0; i < _size; ++i) {
            new_data[i] = _data[i];
        }

        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

    _data[_size++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
    if (_size == 0) {
        throw std::out_of_range("Vector is empty");
    }
    --_size;
}

template <typename T>
void Vector<T>::clear() {
    _size = 0;
}

template <typename T>
const T& Vector<T>::at(size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

template <typename T>
T& Vector<T>::at(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

template <typename T>
size_t Vector<T>::size() const {
    return _size;
}

template <typename T>
size_t Vector<T>::capacity() const {
    return _capacity;
}
int main() {
    Vector<int> vec(new int[5]{53, 62, 72, 7, 4}, 5);
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec.at(i) << " ";
    }
    std::cout << std::endl;
    return 0;
}