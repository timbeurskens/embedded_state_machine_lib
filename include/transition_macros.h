//
// Created by timbeurskens on 24-02-20.
//

#ifndef ESP_LIB_MACROS_H
#define ESP_LIB_MACROS_H

#define ON(EVENT) \
template <typename T::Events E> \
auto on() -> typename std::enable_if_t<E == EVENT>

#define STATE_INIT \
using state_machine_state<T>::state_machine_state;

#define HANDLES(EVENTS) \
STATE_INIT \
template<typename T::Events E> \
auto on() -> typename std::enable_if_t<state_machine_state<T>::StateMachineEventList::template remove_list<EVENTS>::template contains<E>::value> {}

#define ON_ENTER(STATE) \
explicit constexpr STATE(T* m) : state_machine_state<T>{m}

#define ON_LEAVE(STATE) \
~STATE()

#define GOTO(STATE) \
state_machine_state<T>::template transition<STATE>()

#define STATE(NAME) \
template <typename T> \
struct NAME : public state_machine_state<T>

#define PRESTATE(NAME) \
template <typename> struct NAME

#define LIST_STATES(...) c_states<__VA_ARGS__>

#define LIST_EVENTS(...) c_events<__VA_ARGS__>

#define EVENTS(...) LIST_EVENTS(typename state_machine_state<T>::event_t, __VA_ARGS__)

#define NIL LIST_EVENTS(typename state_machine_state<T>::event_t)

#define HANDLES_EVENTS(...) HANDLES(EVENTS(__VA_ARGS__))

#define NO_EVENTS LIST_EVENTS(int)

#define TRIGGER(EVENT) \
state_machine_state<T>::template trigger<EVENT>()

#endif //ESP_LIB_MACROS_H
