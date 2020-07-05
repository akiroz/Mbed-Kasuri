#ifndef Kasuri_h
#define Kasuri_h

#include <stdint.h>
#include <set>
#include "mbed.h"

namespace Kasuri {

    template <typename T> struct Value {
        uint64_t updateTime;
        T value;
        inline Value(uint64_t t, T v): updateTime(t), value(v) {}
    };

    template <typename T> struct Subscription {
        Callback<void(Value<T>, Value<T>)> callback;
        bool once;
    };
    
    template <typename T> struct State : public Value<T> {
        EventQueue* queue;
        std::set<Subscription<T>> subscription;

        inline State(EventQueue* q, T initVal): Value<T>(0, initVal), queue(q) {}

        void set(T val);

        inline void subscribe(Callback<void(Value<T>, Value<T>)> callback, bool once = false) {
            this->subscription.insert({ callback, once });
        }
    };

}

#endif
