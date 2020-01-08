#include <fmt/format.h>

#include <gpiod.hpp>

int main() {
    for (const auto& chip : gpiod::make_chip_iter()) {
        fmt::print("{} [{}], Num. Lines: {}\n", chip.name(), chip.label(),
                   chip.num_lines());
    }
}
