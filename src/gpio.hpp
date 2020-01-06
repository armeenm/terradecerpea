#pragma once

#include <string>

#include "magic_enum.hpp"

enum class Dir { IN, OUT };

enum class Val { LOW, HIGH };

class Pin {
   public:
    Pin(unsigned int num);
    ~Pin();

    void direction(Dir dir);
    Dir direction();

    void value(Val val);
    Val value();

   private:
    const int MAX_BUF_ = 64;
    const std::string SYSFS_GPIO_PATH_ = "/sys/class/gpio";

    unsigned int num_;
    int fd_;
};
