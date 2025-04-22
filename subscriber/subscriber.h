#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
#include "isubscriber.h"

class Subscriber : public ISubscriber
{
public:
    Subscriber() = default;
    Subscriber(const Subscriber &) = delete;
    Subscriber(Subscriber &&) = delete;
    Subscriber &operator=(const Subscriber &) = delete;
    Subscriber &operator=(Subscriber &&) = delete;

    virtual ~Subscriber() = default;

    virtual void notify(const std::string &msg) override;
private:

};

#endif // NOTIFIER_H
