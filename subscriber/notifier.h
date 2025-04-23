#ifndef NOTIFIER_H
#define NOTIFIER_H
#include <list>
#include "isubscriber.h"

class Notifier
{
public:
    Notifier() = default;

    virtual ~Notifier() {}

    void notify(const std::string &msg);
    void addSubscriber(ISubscriber &subscriber);
    void removeSubscriber(ISubscriber &subscriber);
private:
    bool isSubscriberExist(ISubscriber &subscriber) const;

    std::list<ISubscriber *> subscribers_;
};

#endif // NOTIFIER_H
