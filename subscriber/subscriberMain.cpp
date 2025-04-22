#include "subscriberMain.h"
#include "subscriber.h"
#include "notifier.h"

void subscriberMain() {

    Subscriber subscriber;
    Notifier notifier(subscriber);
    notifier.notify("test notification");
}
