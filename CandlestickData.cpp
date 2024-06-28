// #include "CandlestickData.h"
// #include <numeric>
// #include <limits>

// std::vector<Candlestick> CandlestickData::computeCandlestickData(const std::map<std::string, std::map<std::string, std::vector<double>>>& temperatureData, const std::string& country) {
//     std::vector<Candlestick> candlesticks;

//     if (temperatureData.find(country) == temperatureData.end()) {
//         return candlesticks;
//     }

//     const auto& countryData = temperatureData.at(country);

//     for (const auto& [date, temps] : countryData) {
//         double open = temps.front();
//         double close = temps.back();
//         double high = *std::max_element(temps.begin(), temps.end());
//         double low = *std::min_element(temps.begin(), temps.end());

//         Candlestick candle(date, open, high, low, close);
//         candlesticks.push_back(candle);
//     }

//     return candlesticks;
// }


#include "CandlestickData.h"

std::map<std::string, std::vector<Candlestick>> CandlestickData::processData(const std::map<std::string, std::map<std::string, std::vector<float>>>& data) {
    std::map<std::string, std::vector<Candlestick>> result;
    for (const auto& country : data) {
        std::vector<Candlestick> candlesticks;
        std::vector<float> previousTemperatures;
        for (const auto& yearData : country.second) {
            candlesticks.push_back(Candlestick::computeYearlyCandlestick(yearData.second, previousTemperatures, yearData.first));
            previousTemperatures = yearData.second;
        }
        result[country.first] = candlesticks;
    }
    return result;
}