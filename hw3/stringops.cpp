//
// Created by 6rayWa1cher on 03.10.2019.
//

#include <sstream>
#include "stringops.h"

std::vector<std::string> split(const std::string &string, const char delimiter) {
    std::vector<std::string> out;
    std::stringstream sb;
    for (char c : string) {
        if (c == delimiter) {
            out.push_back(sb.str());
            sb = std::stringstream();
        } else {
            sb << c;
        }
    }
    out.push_back(sb.str());
    return out;
}
