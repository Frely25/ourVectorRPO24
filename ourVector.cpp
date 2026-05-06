#include <iostream>

template <typename T>
class Vector {
    private:
        T* _data;
        size_t _size;
        size_t _capacity;
    public:
        // Базовые конструкторы с делегированием
        Vector(size_t capacity, size_t size) : _size(size), _capacity(capacity) {
            _data = new T[_capacity];
        }
        Vector(size_t size) : Vector(size, size) {}
        Vector() : Vector(0, 0) {}

        // Конструктор копирования
        Vector(const Vector& other) : _size(other._size), _capacity(other._capacity) {
            _data = new T[_capacity];
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = other._data[i];
            }
        }

        // Конструктор из массива
        Vector(const T* array, size_t size) : Vector(size, size) {
            for (size_t i = 0; i < size; ++i) {
                _data[i] = array[i];
            }
        }
        
        // Деструктор
        ~Vector() {
            delete[] _data;
        }

        // Методы изменения массива
        void push_back(const T& value) {
            if (_size >= _capacity) {
                size_t new_capacity = _capacity == 0 ? 1 : _capacity * 2;
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
        // void pop_back();
        // void clear();
        // void resize(size_t new_size);
        // void reserve(size_t new_capacity);
        // void shrink_to_fit();
        // void erase(!!!);

        // Методы доступа
        const T& at(size_t index) const {
            if (index >= _size) {
                throw std::out_of_range("Index out of range");
            }
            return _data[index];
        }
        size_t size() const { return _size; }
        size_t capacity() const { return _capacity; }
};

void f(size_t a)
{
    std::cout << "Function f called with argument: " << a << std::endl;
}

int main() {
    Vector<int> vec(new int[5]{1, 2, 3, 4, 5}, 5);
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec.at(i) << " ";
    }
    std::cout << std::endl;
    return 0;
}