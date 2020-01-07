#pragma once

#include <fstream>
#include <string>

#include "fmt/format.h"

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
    unsigned int num_;

    const int MAX_BUF_ = 64;
    const std::string SYSFS_GPIO_PATH_ = "/sys/class/gpio";
    const std::string PIN_PATH_ =
        fmt::format("{}/gpio{}", SYSFS_GPIO_PATH_, num_);

    [[nodiscard]] std::ofstream file(std::string_view elem);
    [[nodiscard]] std::ofstream file(std::string_view base,
                                     std::string_view elem);

    std::ofstream value_ = file("value");
};
