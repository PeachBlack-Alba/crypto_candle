#pragma once

#include <vector>
#include <string>
#include <map>
#include "Candlestick.h"

class CandlestickData {
public:
    std::vector<Candlestick> computeCandlestickData(const std::map<std::string,
     std::map<std::string, std::vector<double>>>& temperatureData, const std::string& country);

private:
    double calculateMean(const std::vector<double>& data);
};
