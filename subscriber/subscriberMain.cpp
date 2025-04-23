#include "subscriberMain.h"
#include "subscriber.h"
#include "notifier.h"

void subscriberMain() {

    Subscriber subscriber1, subscriber2;
    Notifier notifier;
    notifier.notify("test notification before register");
    notifier.addSubscriber(subscriber1);
    notifier.notify("test notification after registering subscriber1");
    notifier.addSubscriber(subscriber2);
    notifier.notify("test notification after registering subscriber2");
    notifier.removeSubscriber(subscriber1);
    notifier.notify("test notification after unregistering subscriber1");
    notifier.removeSubscriber(subscriber2);
    notifier.notify("test notification after unregistering subscriber2");
}
