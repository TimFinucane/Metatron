#pragma once

#include <string>
#include <map>

struct Mapping
{
    std::map<std::string, unsigned int> symbols;
    std::map<std::string, unsigned int> links;
};