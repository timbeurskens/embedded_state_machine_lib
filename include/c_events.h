//
// Created by timbeurskens on 29-02-20.
//

#ifndef ESP_LIB_C_EVENTS_H
#define ESP_LIB_C_EVENTS_H

template<typename _event_t, _event_t...Events>
struct c_events;

namespace template_unpack {
    template<typename event_t, event_t ... Pack1, event_t ... Pack2>
    static constexpr inline auto
    join(c_events<event_t, Pack1...>, c_events<event_t, Pack2...>) noexcept -> c_events<event_t, Pack1..., Pack2...> {}

    template<typename event_t, typename ... Items>
    struct pack;

    template<typename event_t, typename Item, typename ... Items>
    struct pack<event_t, Item, Items...> {
        using unpack = decltype(join(Item{}, typename pack<event_t, Items...>::unpack{}));
    };

    template<typename event_t>
    struct pack<event_t> {
        using unpack = c_events<event_t>;
    };
}

template<typename _event_t, _event_t...Events>
struct c_events {
    using event_t = _event_t;

    template<event_t Event>
    /**
     * value == true iff Event is in Events
     * @tparam Event the event to check
     */
    struct contains {
        static constexpr bool value = ((Event == Events) || ...);
    };

    template<bool condition, event_t event>
    struct enable_event;

    template<event_t event>
    struct enable_event<true, event> {
        using value = c_events<event_t, event>;
    };

    template<event_t event>
    struct enable_event<false, event> {
        using value = c_events<event_t>;
    };

    template<typename T>
    using remove_list = typename template_unpack::pack<
            event_t,
            typename enable_event<!T::template contains<Events>::value, Events>::value...
    >::unpack;

    template<event_t ... EventsToRemove>
    using remove = remove_list<
            c_events< // create a temporary event list with all items to remove
                    event_t,
                    EventsToRemove...
            >
    >;
};

#endif //ESP_LIB_C_EVENTS_H
