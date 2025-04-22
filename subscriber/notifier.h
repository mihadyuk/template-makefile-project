#ifndef NOTIFIER_H
#define NOTIFIER_H
#include "isubscriber.h"

class Notifier
{
public:
    Notifier(ISubscriber &subscriber) :
        subscriber_(subscriber)
    {}
    virtual ~Notifier() {}

    void notify(const std::string &msg);
private:
    ISubscriber &subscriber_;
};

#endif // NOTIFIER_H
