//
// Created by timbeurskens on 06-04-20.
//
#include <state_machine.h>
#include <states/led_off.hpp>
#include <states/led_on.hpp>
#include <blinking_events.h>

using basic_state_machine_t = state_machine<
        // initial state:
        led_off,
        // specify all possible states in the machine
        LIST_STATES(
            led_off,
            led_on
        ),
        // specify all events in the machine
        LIST_EVENTS(
            // enum type
            BlinkingEvents,
            BlinkingEvents::Timer_Tick,
            BlinkingEvents::LED_Toggle
        )
>;

int main(int argc, char **argv) {
    basic_state_machine_t basicStateMachine {};

    std::cout << "current state is " << basicStateMachine.get_state() << std::endl;
    basicStateMachine.trigger<BlinkingEvents::Timer_Tick>();
    std::cout << "current state is " << basicStateMachine.get_state() << std::endl;
    basicStateMachine.trigger<BlinkingEvents::LED_Toggle>();
    std::cout << "current state is " << basicStateMachine.get_state() << std::endl;
    basicStateMachine.trigger<BlinkingEvents::Timer_Tick>();
    std::cout << "current state is " << basicStateMachine.get_state() << std::endl;
    basicStateMachine.trigger<BlinkingEvents::LED_Toggle>();
    std::cout << "current state is " << basicStateMachine.get_state() << std::endl;
    basicStateMachine.trigger<BlinkingEvents::Timer_Tick>();
    std::cout << "current state is " << basicStateMachine.get_state() << std::endl;

    return 0;
}