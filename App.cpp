#include "App.h"
#include <iostream>
#include <limits>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <iomanip>

void App::init() {
    loadData();
    processCandlestickData();
    // displayCandlestickData();
    displayTextCandlestickData();

}

void App::loadData() {
    CSVReader reader;
    std::string filename = "weather_data.csv";
    country = "GB"; // Example country code for Great Britain

    temperatureData = reader.readTemperatureData(filename);
}

// void App::processCandlestickData() {
//     CandlestickData candlestickData;
//     auto processedData = candlestickData.processData(temperatureData);

//     if (processedData.find(country) != processedData.end()) {
//         candlesticks = processedData[country];
//     }
// }

// void App::displayCandlestickData() {
//     for (const auto& candle : candlesticks) {
//         std::cout << "Date: " << candle.date << " Open: " << candle.open 
//                   << " High: " << candle.high << " Low: " << candle.low 
//                   << " Close: " << candle.close << std::endl;
//     }
// }


/////////
void App::processCandlestickData() {
    if (temperatureData.find(country) != temperatureData.end()) {
        const auto& countryData = temperatureData[country];
        std::vector<float> previousYearTemperatures;

        for (const auto& yearData : countryData) {
            const std::string& year = yearData.first;
            const auto& temperatures = yearData.second;
            Candlestick candlestick = Candlestick::computeYearlyCandlestick(temperatures, previousYearTemperatures, year);
            candlesticks.push_back(candlestick);
            previousYearTemperatures = temperatures;
        }
    }
}

void App::displayTextCandlestickData() {
    Candlestick::computeTextPlot(candlesticks);
}