//
// Created by Konstantin Grigoriev on 04/10/2019.
//

#ifndef EDUSANDBOX_FUNCTIONALPROG_H
#define EDUSANDBOX_FUNCTIONALPROG_H

#include <vector>

template<typename T>
std::vector<T> map(std::vector<T> v, T(&fn)(T));


template<typename T>
std::vector<T> map(std::vector<T> v, T(&fn)(T)) {
    //std::vector<T> out;
    for (T &elem : v) {
        elem = fn(elem);
        //out.push_back(fn(elem));
    }
    return v;
}

#endif //EDUSANDBOX_FUNCTIONALPROG_H
