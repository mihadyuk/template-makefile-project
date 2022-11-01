/*
 * templateCallback.h
 *
 *  Created on: Nov 1, 2022
 *      Author: amihadyuk
 */

#ifndef TEMPLATES_TEMPLATECALLBACK_H_
#define TEMPLATES_TEMPLATECALLBACK_H_
#include <mutex>
#include <list>
#include <functional>
#include <stdio.h>

template<typename F, typename... Fparams>
class Callback {
public:
    void add(const F callback)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        for (const F &item : _callbacks)
        {
            auto callback_ptr = callback.template target<void(*)(Fparams...)>();
            auto item_ptr     = item.template target<void(*)(Fparams...)>();
            if (callback_ptr && item_ptr && *callback_ptr == *item_ptr)
            {
                printf("callback %p is already added\n", *callback_ptr);
                return;
            }

        }
        _callbacks.push_back(callback);
    }

    void remove(const F callback)
    {
        std::lock_guard<std::mutex> lock(_mutex);

        for (auto it = _callbacks.begin(); it != _callbacks.end(); ++it) {
            auto callback_ptr = callback.template target<void(*)(Fparams...)>();
            auto item_ptr     = (*it).template target<void(*)(Fparams...)>();
            if (callback_ptr && item_ptr && *callback_ptr == *item_ptr)
            {
                _callbacks.erase(it);
                printf("callback %p is removed\n", *callback_ptr);
                return;
            }
        }
    }

    void call(Fparams... args)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        for (const auto & callback : _callbacks)
        {
            callback(args...);
        }
    }
private:
    std::mutex _mutex;
    std::list<F> _callbacks;
};




#endif /* TEMPLATES_TEMPLATECALLBACK_H_ */
