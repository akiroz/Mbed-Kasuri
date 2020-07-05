
#include <kasuri.h>

template <typename T> void Kasuri::State<T>::set(T val) {
    Kasuri::Value<T> prev = { this->updateTime, this->value };
    this->updateTime = Kernel::get_ms_count();
    this->value = val;
    Kasuri::Value<T> curr = { this->updateTime, this->value };
    auto sub = this->subscription;
    for(auto it = sub.begin(); it != sub.end(); it++) {
        this->queue->call(it->callback, prev, curr);
        if(it->once) sub.erase(it);
    }
}
