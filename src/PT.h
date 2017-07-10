#ifndef SRC_PT_H
#define SRC_PT_H

#include <mutex>
#include <sstream>
#include <iostream>

class PT : public std::ostringstream {
public:
    PT() = default;

    static std::mutex& get_mutex() {
        static std::mutex PT_mutex;
        return PT_mutex;
    }

    ~PT() {
        std::lock_guard<std::mutex> guard(get_mutex());
        std::cout << this->str();
    }

};

#endif //SRC_PT_H
