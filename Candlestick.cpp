// #include "Candlestick.h"

// Candlestick::Candlestick(const std::string& date, double open, double high, double low, double close)
//     : date(date), open(open), high(high), low(low), close(close) {}

#include "Candlestick.h"
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iomanip>

#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>
#include <iomanip>

// ANSI escape codes for text color
#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define RESET_TEXT "\033[0m"

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

////////
void Candlestick::computeTextPlot(const std::vector<Candlestick>& candlesticks) {
    float minVal = std::numeric_limits<float>::max();
    float maxVal = std::numeric_limits<float>::min();

    for (const auto& candle : candlesticks) {
        minVal = std::min(minVal, candle.low);
        maxVal = std::max(maxVal, candle.high);
    }

    int plotHeight = 20;
    int plotWidth = candlesticks.size();

    std::vector<std::string> plotLines(plotHeight, std::string(plotWidth * 2, ' '));

    for (int i = 0; i < plotHeight; ++i) {
        float level = maxVal - (maxVal - minVal) * i / (plotHeight - 1);
        for (size_t j = 0; j < candlesticks.size(); ++j) {
            const auto& candle = candlesticks[j];
            std::string color = (candle.close >= candle.open) ? GREEN_TEXT : RED_TEXT;

            if (level <= candle.high && level >= candle.low) {
                if (level == candle.open || level == candle.close) {
                    plotLines[i].replace(j * 2, 1, color + '#' + RESET_TEXT);
                } else if ((level < candle.open && level > candle.close) || (level > candle.open && level < candle.close)) {
                    plotLines[i].replace(j * 2, 1, "|");
                } else {
                    plotLines[i].replace(j * 2, 1, "|");
                }
            }
        }
    }

    // Print vertical axis labels
    for (int i = 0; i < plotHeight; ++i) {
        float level = maxVal - (maxVal - minVal) * i / (plotHeight - 1);
        std::cout << std::setw(5) << std::fixed << std::setprecision(1) << level << " | " << plotLines[i] << std::endl;
    }

    // Print horizontal axis
    std::cout << "      " << std::string(plotWidth * 2, '-') << std::endl;
    std::cout << "      ";
    for (const auto& candle : candlesticks) {
        std::cout << candle.date.substr(2, 2) << " ";
    }
    std::cout << std::endl;
}