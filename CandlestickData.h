#pragma once
#include "Candlestick.h"
#include <map>
#include <string>
#include <vector>

class CandlestickData {
public:
    std::map<std::string, std::vector<Candlestick>> processData(const std::map<std::string, std::map<std::string, std::vector<float>>>& data);
};

