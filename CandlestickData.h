#pragma once
#include <vector>
#include <map>
#include <string>
#include "Candlestick.h"

class CandlestickData {
public:
    std::vector<Candlestick> computeCandlestickData(const std::map<std::string, std::map<std::string, std::vector<double>>>& temperatureData, const std::string& country);
};
