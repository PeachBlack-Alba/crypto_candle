#pragma once

#include <vector>
#include <string>
#include <map>
#include "Candlestick.h"
#include "CandlestickData.h"
#include "CSVReader.h"

class App {
public:
    void init();
private:
    void loadData();
    void processCandlestickData();
    void displayCandlestickData();

    std::map<std::string, std::map<std::string, std::vector<double>>> temperatureData;
    std::vector<Candlestick> candlesticks;
    std::string country;
};
