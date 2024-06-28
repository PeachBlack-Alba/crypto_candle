// #include "Candlestick.h"

// Candlestick::Candlestick(const std::string& date, double open, double high, double low, double close)
//     : date(date), open(open), high(high), low(low), close(close) {}

#include "Candlestick.h"
#include <algorithm>
#include <numeric>

Candlestick::Candlestick(const std::string& date, float open, float high, float low, float close)
    : date(date), open(open), high(high), low(low), close(close) {}

float computeAverage(const std::vector<float>& temperatures) {
    return std::accumulate(temperatures.begin(), temperatures.end(), 0.0) / temperatures.size();
}

Candlestick Candlestick::computeYearlyCandlestick(const std::vector<float>& temperatures, const std::vector<float>& previousYearTemperatures, const std::string& year) {
    float open;
    if (!previousYearTemperatures.empty()) {
        open = computeAverage(previousYearTemperatures);
    } else {
        open = temperatures.front(); // For the first year, use the first temperature
    }
    float close = computeAverage(temperatures);
    float high = *std::max_element(temperatures.begin(), temperatures.end());
    float low = *std::min_element(temperatures.begin(), temperatures.end());
    return Candlestick(year, open, high, low, close);
}

std::string Candlestick::toTextRepresentation(int height) const {
    std::string result = date + " ";
    result += (close >= open ? "Green " : "Red ");
    result += "|";
    for (int i = 0; i < height; ++i) {
        result += (i == height / 2 ? "-" : " ");
    }
    result += "|";
    return result;
}