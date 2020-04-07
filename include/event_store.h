//
// Created by timbeurskens on 01-03-20.
//

#ifndef ESP_LIB_EVENT_STORE_H
#define ESP_LIB_EVENT_STORE_H

#include <tuple>
#include <map>
#include <typeinfo>
#include <any>

template <typename ... Components>
struct component_coupling : public std::tuple<Components...> {
    component_coupling() {
        ((Components::template set<component_coupling*>("coupling", this)),...);
    }
};

#endif //ESP_LIB_EVENT_STORE_H
