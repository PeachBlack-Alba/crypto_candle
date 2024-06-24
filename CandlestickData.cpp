#include "CandlestickData.h"
#include <numeric>
#include <limits>

std::vector<Candlestick> CandlestickData::computeCandlestickData(const std::map<std::string, std::map<std::string, std::vector<double>>>& temperatureData, const std::string& country) {
    std::vector<Candlestick> candlesticks;

    if (temperatureData.find(country) == temperatureData.end()) {
        return candlesticks;
    }

    const auto& countryData = temperatureData.at(country);

    for (const auto& [date, temps] : countryData) {
        double open = temps.front();
        double close = temps.back();
        double high = *std::max_element(temps.begin(), temps.end());
        double low = *std::min_element(temps.begin(), temps.end());

        Candlestick candle(date, open, high, low, close);
        candlesticks.push_back(candle);
    }

    return candlesticks;
}
