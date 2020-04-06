//
// Created by timbeurskens on 06-04-20.
//

#ifndef EMBEDDEDSTATEMACHINELIB_LED_ON_HPP
#define EMBEDDEDSTATEMACHINELIB_LED_ON_HPP

#include <state_machine.h>
#include <blinking_events.h>

PRESTATE(led_off);

STATE(led_on) {
    HANDLES_EVENTS(BlinkingEvents::Timer_Tick, BlinkingEvents::LED_Toggle)

    ON_ENTER(led_on) {
        std::cout << "entering state led_on" << std::endl;
    }

    ON_LEAVE(led_on) {
        std::cout << "exiting state led_on" << std::endl;
    }

    ON(BlinkingEvents::Timer_Tick) {
        std::cout << "led_on received event Timer_Tick" << std::endl;
    }

    ON(BlinkingEvents::LED_Toggle) {
        std::cout << "led_on received event LED_Toggle" << std::endl;

        GOTO(led_off);
    }
};

#endif //EMBEDDEDSTATEMACHINELIB_LED_ON_HPP
