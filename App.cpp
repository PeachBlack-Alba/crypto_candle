#include "App.h"
#include <iostream>

void App::init() {
    loadData();
    processCandlestickData();
    displayCandlestickData();
}

void App::loadData() {
    CSVReader reader;
    std::string filename = "weather_data.csv";
    country = "GB"; // Example country code for Great Britain

    temperatureData = reader.readTemperatureData(filename);
}

void App::processCandlestickData() {
    CandlestickData candlestickData;
    candlesticks = candlestickData.computeCandlestickData(temperatureData, country);
}

void App::displayCandlestickData() {
    for (const auto& candle : candlesticks) {
        std::cout << "Date: " << candle.date << " Open: " << candle.open 
                  << " High: " << candle.high << " Low: " << candle.low 
                  << " Close: " << candle.close << std::endl;
    }
}
