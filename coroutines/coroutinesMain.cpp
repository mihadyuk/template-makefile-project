#include <stdio.h>
#include <coroutine>
#include <stdint.h>
#include<thread>
#include <stdexcept>
#include <format>

#include "timeElapsed.h"

struct MyPromise;

struct MyCoroutine : std::coroutine_handle<MyPromise>
{
    using promise_type = ::MyPromise;
    ~MyCoroutine() {
        printf("called %s() from 0x%p\n", __func__, static_cast<void *>(this));
    }
};

struct MyPromise
{

    ~MyPromise() {
        printf("called %s() from 0x%p\n", __func__, static_cast<void *>(this));
    }
    MyCoroutine get_return_object() {
        printf("called %s() from 0x%p\n", __func__, static_cast<void *>(this));
        return {MyCoroutine::from_promise(*this)};
    }
    std::suspend_always initial_suspend() noexcept {
        printf("called %s() from 0x%p\n", __func__, static_cast<void *>(this));
        return std::suspend_always(); }
    std::suspend_always final_suspend() noexcept {
        printf("called %s() from 0x%p\n", __func__, static_cast<void *>(this));
        return std::suspend_always();
    }

#if 1
    int32_t yielded_val_ = 0;
    std::suspend_always yield_value(int32_t val) {
        printf("called %s(%d) from 0x%p\n", __func__, val, static_cast<void *>(this));
        yielded_val_ = val;
        return {};
    }
#else
    std::suspend_always yield_value() {
        printf("called %s() from 0x%p\n", __func__, static_cast<void *>(this));
        return {};
    }
#endif

#if 0
    void return_void() {
        printf("called %s() from 0x%p\n", __func__, static_cast<void *>(this));
    }
#else
    int32_t retval_ = 0;
    void return_value(int32_t val) {
        printf("called %s() from 0x%p\n", __func__, static_cast<void *>(this));
        retval_ = val;
    }
#endif

    void unhandled_exception() {
        printf("called %s() from 0x%p\n", __func__, static_cast<void *>(this));
    }
};

struct MyAwait {
    //operator co_await() {}
    bool await_ready() {
        printf("called %s() from 0x%p\n", __func__, static_cast<void *>(this));
        return false;
    }
    void await_suspend(std::coroutine_handle<> h) {
        printf("called %s() from 0x%p\n", __func__, static_cast<void *>(this));
    }
    void await_resume() {
        printf("called %s() from 0x%p\n", __func__, static_cast<void *>(this));
    }
};

static TimeElapsed timer;

MyCoroutine coroutineF(int32_t val) {

    printf("%ums, called %s(%d)\n", timer.elapsedMs().count(), __func__, val);

    if (val < 0)
        throw std::out_of_range(std::format("val {} is out of range", val));
    for (int32_t i = 0; i < val; i++)
    {
        printf("%ums, before sleep %d\n", timer.elapsedMs().count(), i);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        printf("%ums, after sleep %d\n", timer.elapsedMs().count(), i);
        //co_await MyAwait();
        co_yield i;
        //co_yield void;
    }
    printf("%ums, co_return\n", timer.elapsedMs().count());
    co_return val;
}

void func(int32_t val) {
    printf("called %s(%d)\n", __func__, val);
    for (int32_t i = 0; i < val; i++)
    {
        printf("sleep %d\n", i);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        //co_await;
    }
}

void coroutinesMain() {
    printf("begin coroutines\n");
    //func(3);
    timer.start();
    int32_t iterations = 5;
    MyCoroutine result = coroutineF(iterations);

    for (int32_t i = 0; i < iterations; i++) {
        printf("done() == %s\n", result.done() == true ? "true" : "false");
        printf("%ums, result.resume() called\n", timer.elapsedMs().count());
        result.resume();
        printf("done() == %s\n", result.done() == true ? "true" : "false");
        printf("%ums, retval: %d\n", timer.elapsedMs().count(), result.promise().retval_);
        printf("yielded_val: %d\n", result.promise().yielded_val_);
    }
    printf("wait for coroutine finish\n");
    while (result.done() == false) {
        printf("%ums, result.resume() called\n", timer.elapsedMs().count());
        result.resume();
        printf("done() == %s\n", result.done() == true ? "true" : "false");
        printf("%ums, retval: %d\n", timer.elapsedMs().count(), result.promise().retval_);
        printf("yielded_val: %d\n", result.promise().yielded_val_);
    }
    printf("result.destroy() called\n");
    result.destroy();

    result = coroutineF(2);
    printf("result.resume() called\n");
    result.resume();
    printf("result.destroy() called\n");
    result.destroy();

    result = coroutineF(-1);
    printf("result.resume() called\n");
    result.resume();
    printf("result.destroy() called\n");
    result.destroy();


    printf("end coroutines\n");
}
