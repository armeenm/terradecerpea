#include "gpio.hpp"

#include <fcntl.h>
#include <poll.h>
#include <unistd.h>

#include <cctype>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include "fmt/format.h"

Pin::Pin(unsigned int num) : num_(num) {
    // Export pin
    std::ofstream ostrm(
        fmt::format("{}/{}", SYSFS_GPIO_PATH_, "export").c_str(),
        std::ios::binary);
    ostrm << num_;

    for (auto n : dir_names) {
        fmt::print("{} ", );
    }

    fd_ = open(fmt::format("{}/gpio{}/value", SYSFS_GPIO_PATH_, num_).c_str(),
               O_RDONLY | O_NONBLOCK);
    // if (fd_ < 0) throw std::runtime_error("Failed to open file :(");
}

Pin::~Pin() {
    // Unexport pin
    std::ofstream ostrm(fmt::format("{}/{}", SYSFS_GPIO_PATH_, "unexport"),
                        std::ios::binary);
    ostrm << num_;

    close(fd_);
}

void Pin::direction(Dir dir) {}
