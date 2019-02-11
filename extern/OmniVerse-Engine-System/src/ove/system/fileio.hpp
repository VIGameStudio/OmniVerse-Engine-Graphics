#pragma once

#include <string>

namespace ove {
namespace file {

    void read(const std::string& path, std::string& out);
    void write(const std::string& path, const std::string& out);

}
}
