#include "notifier.h"

void Notifier::notify(const std::string &msg) {
    for (auto &item : subscribers_) {
        item->notify(msg);
    }
}

void Notifier::addSubscriber(ISubscriber &subscriber) {
    if (isSubscriberExist(subscriber) == true) {
        printf("subscriber %p already exist\r\n", static_cast<void *>(&subscriber));
        return;
    }
    subscribers_.push_back(&subscriber);
}

void Notifier::removeSubscriber(ISubscriber &subscriber) {
    if (isSubscriberExist(subscriber) == false) {
        printf("subscriber %p already removed\r\n", static_cast<void *>(&subscriber));
        return;
    }
    subscribers_.remove(&subscriber);
}

bool Notifier::isSubscriberExist(ISubscriber &subscriber) const {
    for (auto &item : subscribers_) {
        if (item == &subscriber)
            return true;
    }
    return false;
}
