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
    void insert(const T& value, size_t index);
    void pop_back();
    void erase(size_t index);
    void erase(size_t start_index, size_t end_index);
    void clear();

    const T& at(size_t index) const;
    T& at(size_t index);

    size_t size() const;
    size_t capacity() const;

    void showInfo() { std::cout << "Info: " << "\t_size = " << _size << "\n\t_capacity: " << _capacity << std::endl; }
};

// Конструктор по размеру и емкости
template <typename T>
Vector<T>::Vector(size_t size, size_t capacity) : _size(size), _capacity(capacity < size ? size : capacity) {
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = T();
    }
}

// Конструктор по данному массиву
template <typename T>
Vector<T>::Vector(const T* array, size_t size) : Vector(size, size) {
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = array[i];
    }
}

// Конструктор копирования
template <typename T>
Vector<T>::Vector(const Vector& other) : _size(other._size), _capacity(other._capacity) {
    //std::cout << "Конструктор копирования" << std::endl;
    _data = new T[other._capacity];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
}

// Перегрузка оператора присваивания
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    //std::cout << "Перегрузка равно" << std::endl;
    
    // Проверка является новый вектор текущим
    if (this == &other) 
        return *this;

    delete[] _data;

    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];

    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }

    return *this;
}

// Отработает при: Vector<int> newVec = std::move(vec);
template <typename T>
Vector<T>::Vector(Vector&& other) noexcept : _data(other._data), _size(other._size), _capacity(other._capacity) {
    //std::cout << "Смещение копирования" << std::endl;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}
    
// Отработает при: vec = std::move(vec2);
template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    //std::cout << "Смещение равенства" << std::endl;

    // Проверка является новый вектор текущим
    if (this == &other) 
        return *this;

    delete[] _data;

    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;

    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;

    return *this;
}

// Деструктор
template <typename T>
Vector<T>::~Vector() {
    delete[] _data;
}

// Добавить элемент в конце массива
template <typename T>
void Vector<T>::push_back(const T& value) {
    // Определяемся нужно ли увеличивать емкость массива
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

// Добавляет элмент в конкретный индекс
template <typename T> 
void Vector<T>::insert(const T& value, size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    // Определяемся нужно ли увеличивать емкость массива
    if (_size >= _capacity) {
        _capacity = (_capacity == 0 ? 1 : _capacity * 2);
    }

    T* new_data = new T[_capacity];
    
    // Заполняем новый массив старыми значениями (if и else), а в else if кладем новый элемент
    for (size_t i = 0; i < (_size + 1); i++) {
        if (i < index){
            new_data[i] = _data[i];
        } else if (i == index) {
            new_data[i] = value;
        } else {
            new_data[i + 1] = _data[i]; 
        }
    }

    delete[] _data;
    _data = new_data;
    _size++;
}

// Удалить последний элемент
template <typename T>
void Vector<T>::pop_back() {
    if (_size == 0) {
        throw std::out_of_range("Vector is empty");
    }

    // выделение нового участка оперативно памяти 
    T* new_data = new T[--_size];
    // Копирование старго массива кроме последнего элемента
    for (size_t i = 0; i < _size; i++) {
        new_data[i] = _data[i];
    }
    // Удаление старой ячейки и присвоение новой
    delete[] _data;
    _data = new_data;
}

// Удалить элемент по индексу
template <typename T>
void Vector<T>::erase(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }

    T* new_data = new T[--_size];
    
    for (size_t i = 0; i < _size; i++) {
        if (i < index) {
            new_data[i] = _data[i];
        } else if (i >= index) {
            new_data[i] = _data[i + 1];
        }
    }

    delete[] _data;
    _data = new_data;
}

// Очищает все эелементы
template <typename T>
void Vector<T>::clear() {
    _size = 0;
}

// Возвращает не изменяемый элемент по индексу. Пример использования: int value = vec.at(1)
template <typename T>
const T& Vector<T>::at(size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

// Возвращает элемент по индексу. Пример использования: int& ref = vec.at(1)
template <typename T>
T& Vector<T>::at(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

// Возвращает кол-во элементов
template <typename T>
size_t Vector<T>::size() const {
    return _size;
}

// Возвращает емкость массива
template <typename T>
size_t Vector<T>::capacity() const {
    return _capacity;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T> vec) {
    os << "[ ";
    for (int i = 0; i < vec.size(); i++) {
        os << vec.at(i) << " ";
    }
    os << "]\n";
    return os;
}

int main() {
    Vector<int> vec(new int[5]{1, 2, 3, 4, 5}, 5);
    
    std::cout << vec;
    vec.showInfo();

    vec.push_back(25); //
    std::cout << vec;
    vec.showInfo();

    vec.erase(2);
    std::cout << vec;
    vec.showInfo();
    
    return 0;
}