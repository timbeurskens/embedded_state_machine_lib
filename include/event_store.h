//
// Created by timbeurskens on 01-03-20.
//

#ifndef ESP_LIB_EVENT_STORE_H
#define ESP_LIB_EVENT_STORE_H

#include <tuple>
#include <unordered_map>
#include <typeinfo>
#include <any>

struct locator : public std::unordered_map<std::string, std::any> {
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

template <typename ... Components>
struct component_coupling : public std::tuple<Components...> {
    component_coupling() {
        ((Components::template set<component_coupling*>("coupling", this)),...);
    }
};

#endif //ESP_LIB_EVENT_STORE_H
