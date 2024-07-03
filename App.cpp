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
    // Task 1:
    // displayCandlestickData();
    displayTextCandlestickData();

}

void App::loadData() {
    CSVReader reader;
    std::string filename = "weather_data.csv";
    // Example country code for Great Britain
    country = "GB"; 

    temperatureData = reader.readTemperatureData(filename);
    // Debug porpuses: Print loaded data
    // std::cout << "Loaded temperature data for country: " << country << std::endl;
    // for (const auto& yearData : temperatureData[country]) {
    //     std::cout << "Year/Month: " << yearData.first << " - Temperatures: ";
    //     for (const auto& temp : yearData.second) {
    //         std::cout << temp << " ";
    //     }
    //     std::cout << std::endl;
    // }
}
// Task 1:
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


void App::processCandlestickData() {
    if (temperatureData.find(country) != temperatureData.end()) {
        const auto& countryData = temperatureData[country];
        std::vector<float> previousMonthTemperatures;

        for (const auto& yearData : countryData) {
            const std::string& year = yearData.first;
            const auto& temperatures = yearData.second;

            std::vector<float> monthTemps;
            for (size_t i = 0; i < temperatures.size(); ++i) {
                monthTemps.push_back(temperatures[i]);
                if (monthTemps.size() == 30) { 
                    // Assuming 30 days per month for simplicity
                    const std::string month = std::to_string((i / 30) + 1);
                    Candlestick candlestick = Candlestick::computeMonthlyCandlestick(monthTemps, previousMonthTemperatures, year, month);
                    candlesticks.push_back(candlestick);
                    previousMonthTemperatures = monthTemps;
                    monthTemps.clear();
                }
            }
        }

        // Debug porpuses: Print processed candlestick data
        // std::cout << "Processed candlestick data:" << std::endl;
        // for (const auto& candle : candlesticks) {
        //     std::cout << "Date: " << candle.date << ", Open: " << candle.open << ", High: " << candle.high << ", Low: " << candle.low << ", Close: " << candle.close << std::endl;
        // }
    }
}

void App::displayTextCandlestickData() {
    std::vector<Candlestick> filteredCandlesticks;
    for (const auto& candle : candlesticks) {
        if (candle.date == "2000-06" || candle.date == "2000-07" || candle.date == "2000-08" || candle.date == "2000-09") {
            filteredCandlesticks.push_back(candle);
        }
    }

    if (!filteredCandlesticks.empty()) {
        Candlestick::computeTextPlot(filteredCandlesticks);
    } else {
        std::cout << "No candlestick data available for the specified months." << std::endl;
    }
}