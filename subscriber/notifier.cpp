#include "notifier.h"

void Notifier::notify(const std::string &msg) {
    subscriber_.notify(msg);
}
