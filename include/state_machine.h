//
// Created by timbeurskens on 24-02-20.
//

#ifndef ESP_LIB_STATE_MACHINE_H
#define ESP_LIB_STATE_MACHINE_H

#include <variant>
#include <transition_macros.h>
#include <state_machine_state.h>
#include <c_events.h>
#include <event_store.h>

template<template<typename> typename ... States>
struct c_states {
    constexpr c_states() noexcept = default;

    template<typename state_machine_t>
    using state_container_t = std::variant<States<state_machine_t>...>;
};

template<template<typename> typename Initial_State,
        typename StateContainer, typename EventContainer>
struct state_machine : locator {
    using Events = typename EventContainer::event_t;
    using StateMachineEventList = EventContainer;
    using StateMachineStateList = StateContainer;

    using current_state_container_t = typename StateContainer::template state_container_t<state_machine>;

    state_machine() : current_state(Initial_State<state_machine>{this}) {}

    state_machine(const state_machine &) = delete;

    state_machine(state_machine &&) = delete;

    state_machine &operator=(const state_machine &) = delete;

    state_machine &operator=(state_machine &&) = delete;

    template<template<typename> typename T>
    constexpr inline void transition() noexcept {
        if (!std::holds_alternative<T<state_machine>>(current_state)) {
            current_state.template emplace<T<state_machine>>(this);
        }
    }

    template<Events E>
    constexpr inline void trigger() {
        trigger_proxy<E>(StateContainer{});
    }

    constexpr inline void runtime_trigger(Events e) {
        runtime_trigger_proxy(e, EventContainer{});
    }

    constexpr inline auto get_state() const {
        return current_state.index();
    }

private:

    template<Events ... all_events>
    constexpr inline void runtime_trigger_proxy(Events e, const c_events<Events, all_events...> &) {
        runtime_trigger<all_events...>(e);
    }

    template<Events first_event, Events ... other_events, typename = std::enable_if_t<sizeof...(other_events), void>>
    constexpr inline void runtime_trigger(Events e) {
        if (e == first_event) {
            trigger<first_event>();
        } else {
            runtime_trigger<other_events...>(e);
        }
    }

    template<Events first_event>
    constexpr inline void runtime_trigger(Events e) {
        if (e == first_event) {
            trigger<first_event>();
        }
    }

    template<Events E, template<typename> typename ...States>
    constexpr inline void trigger_proxy(const c_states<States...> &) {
        trigger<E, States<state_machine>...>();
    }

    template<Events E, typename CState>
    constexpr inline void trigger() {
        if (std::holds_alternative<CState>(current_state)) {
            process_trigger<E, CState>();
        }
    }

    template<Events E, typename CState, typename ... Remaining>
    constexpr inline auto trigger() -> typename std::enable_if_t<sizeof...(Remaining)> {
        if (std::holds_alternative<CState>(current_state)) {
            process_trigger<E, CState>();
        } else {
            trigger<E, Remaining...>();
        }
    }

    template<Events E, typename CState>
    constexpr inline void process_trigger() {
        std::get<CState>(current_state).template on<E>();
    }

    current_state_container_t current_state;
};

#endif //ESP_LIB_STATE_MACHINE_H
