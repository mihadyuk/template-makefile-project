#ifndef ISUBSCRIBER_H
#define ISUBSCRIBER_H
#include <string>

class ISubscriber
{
public:
    virtual void notify(const std::string &msg) = 0;
};

#endif // ISUBSCRIBER_H
