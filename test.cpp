#include <iostream>

template <typename T>
class ourVector
{
private:
    int a, b;
public:
    ourVector(int a, int b);
    void push_back();
};

template <typename T>
void ourVector<T>::push_back() {

}

template <typename T>
ourVector<T>::ourVector(int a, int b)
{
    this->a = (a < 0 ? 0 : a);
    if (b < a) {
        this->b = a;
    } else {
        this->b = b;
    }
    std::cout << "A: " << this->a << ", B: " << this->b << std::endl;

}

void f(size_t a)
{
    std::cout << "Function f called with argument: " << a << std::endl;
}

int main() {
    std::cout << "Starting main function" << std::endl;
    ourVector<int> v1(-5, -50); // a will be set to 0, b will be set to 10
    return 0;
}