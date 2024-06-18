#include "CandlestickData.h"
#include <algorithm>
#include <numeric>

std::vector<Candlestick> CandlestickData::computeCandlestickData(const std::map<std::string, 
std::map<std::string, std::vector<double>>>& temperatureData, const std::string& country) {
    std::vector<Candlestick> candlesticks;
    std::string previousYear = "";
    double previousClose = 0.0;

    for (const auto& yearData : temperatureData) {
        const std::string& year = yearData.first;
        const auto& countryData = yearData.second;

        if (countryData.find(country) != countryData.end()) {
            const std::vector<double>& temperatures = countryData.at(country);

            if (!temperatures.empty()) {
                double open = previousYear.empty() ? temperatures.front() : previousClose;
                double close = temperatures.back();
                double high = *std::max_element(temperatures.begin(), temperatures.end());
                double low = *std::min_element(temperatures.begin(), temperatures.end());

                candlesticks.emplace_back(year + "-01-01", open, high, low, close);
                previousClose = close;
            }
        }

        previousYear = year;
    }

    return candlesticks;
}

double CandlestickData::calculateMean(const std::vector<double>& data) {
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}
