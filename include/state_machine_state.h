//
// Created by timbeurskens on 24-02-20.
//

#ifndef ESP_LIB_STATE_MACHINE_STATE_H
#define ESP_LIB_STATE_MACHINE_STATE_H

template<typename T>
struct state_machine_state {
    using StateMachine = T;
    using StateMachineEventList = typename T::StateMachineEventList;
    using StateMachineStateList = typename T::StateMachineStateList;
    using event_t = typename T::Events;

    explicit state_machine_state(T *m) : state_machine(m) {}

    template<template<typename> typename T2>
    constexpr inline void transition() noexcept {
        state_machine->template transition<T2>();
    }

    template<event_t E>
    constexpr inline void trigger() {
        state_machine->template trigger<E>();
    }

    constexpr inline void trigger(event_t e) {
        state_machine->template trigger(e);
    }

    T *state_machine;
};

#endif //ESP_LIB_STATE_MACHINE_STATE_H
