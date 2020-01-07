#include "gpio.hpp"

#include <fcntl.h>
#include <poll.h>
#include <unistd.h>

#include <cctype>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

#include "fmt/format.h"
#include "magic_enum.hpp"

using fmt::format;
using std::ofstream;

Pin::Pin(unsigned int num) : num_(num) {
    // Export pin
    auto ostrm = file(SYSFS_GPIO_PATH_, "export");
    ostrm << num_;
}

Pin::~Pin() {
    // Unexport pin
    auto ostrm = file(SYSFS_GPIO_PATH_, "unexport");
    ostrm << num_;
}

void Pin::direction(Dir dir) {
    auto ostrm = file("direction");

    switch (dir) {
        case Dir::IN:
            ostrm << "in";
            break;

        case Dir::OUT:
            ostrm << "out";
            break;
    }
}

Dir Pin::direction() {
    auto ostrm = file("direction");

    std::string dir;
    ostrm >> dir;

    if (dir == "in")
        return Dir::IN;
    else if (dir == "out")
        return Dir::OUT;
    else
        throw std::runtime_error("Unknown direction!");
}

void Pin::value(Val val) {
    value_ << format("{}", magic_enum::enum_integer<val>());
}

Val Pin::value() {}

std::ofstream Pin::file(std::string_view elem) { return file(PIN_PATH_, elem); }

std::ofstream Pin::file(std::string_view base, std::string_view elem) {
    return std::ofstream(fmt::format("{}/{}", base, elem), std::ios::binary);
}
