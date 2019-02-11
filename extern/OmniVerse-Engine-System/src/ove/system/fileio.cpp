#include "fileio.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

namespace ove {
namespace file {

    void read(const std::string& path, std::string& out)
    {
        std::ifstream ifs(path, std::ios::in);

        if (!ifs.is_open()) {
            std::cerr << "Could not read file " << path << ". File does not exist.\n";
            out = "";
        } else {
            std::string line = "";
            while (!ifs.eof()) {
                std::getline(ifs, line);
                out.append(line + "\n");
            }
        }

        ifs.close();
    }

    void write(const std::string& path, const std::string& out) {}

}
}
