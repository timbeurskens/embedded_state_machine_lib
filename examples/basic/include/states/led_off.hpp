//
// Created by timbeurskens on 06-04-20.
//

#ifndef EMBEDDEDSTATEMACHINELIB_LED_OFF_HPP
#define EMBEDDEDSTATEMACHINELIB_LED_OFF_HPP

#include <state_machine.h>
#include <blinking_events.h>
#include <iostream>

PRESTATE(led_on);

STATE(led_off) {
    HANDLES_EVENTS(BlinkingEvents::LED_Toggle)

    ON_ENTER(led_off) {
        std::cout << "entering state led_off" << std::endl;
    }

    ON_LEAVE(led_off) {
        std::cout << "exiting state led_off" << std::endl;
    }

    ON(BlinkingEvents::LED_Toggle) {
        std::cout << "led_off received event LED_Toggle" << std::endl;

        GOTO(led_on);
    }
};

#endif //EMBEDDEDSTATEMACHINELIB_LED_OFF_HPP
