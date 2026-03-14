#include "Template.h"
#include <iostream>

template <typename T>
Template<T>::Template(T data) {
    this->data = data;
}


template <typename T>
void Template<T>::print() const {
    std::cout << data << std::endl;
}