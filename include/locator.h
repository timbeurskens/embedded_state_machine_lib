//
// Created by timbeurskens on 06-04-20.
//

#ifndef EMBEDDEDSTATEMACHINELIB_LOCATOR_H
#define EMBEDDEDSTATEMACHINELIB_LOCATOR_H

#include <map>
#include <string>
#include <any>

struct locator : private std::map<std::string, std::any> {
    template <typename T>
    void set(const std::string& key, const T& value) {
        (*this)[key] = value;
    }

    template <typename T>
    void set(const std::string& key, T value) {
        (*this)[key] = value;
    }

    template <typename T>
    const T& get(const std::string& key) {
        return std::get<T>((*this)[key]);
    }

    template <typename T>
    T& get(const std::string& key) {
        return std::get<T>((*this)[key]);
    }
};

#endif //EMBEDDEDSTATEMACHINELIB_LOCATOR_H
