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
    /// Task 2: Create a text-based plot of the candlestick data
    // void displayCandlestickData();
    void displayTextCandlestickData();  
    /// Task 3: Filter Data and Plotting using text
    void filterAndDisplayData(const std::string& startDate, const std::string& endDate, double minTemp, double maxTemp);


    std::map<std::string, std::map<std::string, std::vector<float>>> temperatureData;
    std::vector<Candlestick> candlesticks;
    std::string country;
};
