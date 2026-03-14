#include <iostream>

template <typename T>
class Template {
    public:
        Template(T data);
        void print() const;
    private:
        T data;
};

template <typename T>
Template<T>::Template(T data) {
    this->data = data;
}


template <typename T>
void Template<T>::print() const {
    std::cout << data << std::endl;
}