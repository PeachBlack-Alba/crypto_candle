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
using namespace std; 

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
        // For the first year, use the first temperature
        open = temperatures.front(); 
    }
    float close = computeAverage(temperatures);
    float high = *std::max_element(temperatures.begin(), temperatures.end());
    float low = *std::min_element(temperatures.begin(), temperatures.end());
    return Candlestick(year, open, high, low, close);
}

Candlestick Candlestick::computeMonthlyCandlestick(const std::vector<float>& temperatures, const std::vector<float>& previousMonthTemperatures, const std::string& year, const std::string& month) {
    float open;
    if (!previousMonthTemperatures.empty()) {
        open = computeAverage(previousMonthTemperatures);
    } else {
        // For the first month, use the first temperature
        open = temperatures.front(); 
    }
    float close = computeAverage(temperatures);
    float high = *std::max_element(temperatures.begin(), temperatures.end());
    float low = *std::min_element(temperatures.begin(), temperatures.end());
    return Candlestick(year + "-" + (month.size() == 1 ? "0" + month : month), open, high, low, close); // Format date as "YYYY-MM"
}

void Candlestick::computeTextPlot(const std::vector<Candlestick>& candlesticks) {
    double highestHigh = Candlestick::getHighestHigh(candlesticks);
    double lowestLow = Candlestick::getLowestLow(candlesticks);
    double scale = (highestHigh - lowestLow) * 1.3;

    int levels = 30;
    double rangePerLevel = scale / levels;
    double currentRange = highestHigh + rangePerLevel;
    double previousRange = highestHigh + (2 * rangePerLevel);

    std::cout << "Levels: " << levels << std::endl;
    std::cout << std::fixed << std::setprecision(1) << "Range per level: " << rangePerLevel << std::endl;
    std::cout << "highestHigh: " << highestHigh << std::endl;
    std::cout << "lowestLow: " << lowestLow << std::endl;
    std::cout << "=====================================================" << std::endl;

    for (int i = 0; i < levels; i++) {
        std::cout << std::setw(5) << currentRange << "│";
        for (const Candlestick& candlestick : candlesticks) {
            Candlestick::drawCandlestick(candlestick.open, candlestick.close, candlestick.high, candlestick.low, currentRange, previousRange);
        }
        currentRange -= rangePerLevel;
        previousRange -= rangePerLevel;
        std::cout << std::endl;
    }

    std::cout << std::setw(7) << "Time" << "│";
    for (const Candlestick& candle : candlesticks) {
        // Display month only
        std::cout << std::setw(5) << candle.date.substr(5, 2); 
    }
    std::cout << std::endl;
}

void Candlestick::drawCandlestick(float open, float close, float high, float low, double currentRange, double previousRange) {
    std::string character = "       ";
    std::string wickCharacter = "   │   ";
    std::string bodyCharacter = "   ┃   ";
    std::string openCloseCharacter = "   ─   ";

    if (high >= currentRange && high < previousRange) {
        character = wickCharacter;
    } else if (low >= currentRange && low < previousRange) {
        character = openCloseCharacter;
    } else if (open >= currentRange && open < previousRange) {
        character = openCloseCharacter;
    } else if (close >= currentRange && close < previousRange) {
        character = wickCharacter;
    } else if ((currentRange > open && currentRange < close) || (currentRange > close && currentRange < open)) {
        character = bodyCharacter;
    } else if ((currentRange > low && currentRange < open) || (currentRange > low && currentRange < close)) {
        character = wickCharacter;
    } else if ((currentRange > open && currentRange < high) || (currentRange > close && currentRange < high)) {
        character = wickCharacter;
    }

    if (close < open) std::cout << RED_TEXT << std::setw(3) << character << RESET_TEXT;
    else std::cout << GREEN_TEXT << std::setw(3) << character << RESET_TEXT;
}

double Candlestick::getHighestHigh(const std::vector<Candlestick>& candlesticks) {
    if (candlesticks.empty()) return 0.0;
    double highestHigh = candlesticks[0].high;
    for (const Candlestick& candlestick : candlesticks) {
        if (candlestick.high > highestHigh) highestHigh = candlestick.high;
    }
    return highestHigh;
}

double Candlestick::getLowestLow(const std::vector<Candlestick>& candlesticks) {
    if (candlesticks.empty()) return 0.0;
    double lowestLow = candlesticks[0].low;
    for (const Candlestick& candlestick : candlesticks) {
        if (candlestick.low < lowestLow) lowestLow = candlestick.low;
    }
    return lowestLow;
}

/// Task 3: Filter Data and Plotting using text

void Candlestick::filterAndPlotData(const std::vector<Candlestick>& data, const std::string& startDate, const std::string& endDate, double minTemp, double maxTemp) {
    std::vector<Candlestick> filteredData;
    for (const auto& candle : data) {
        if (candle.date >= startDate && candle.date <= endDate && candle.high <= maxTemp && candle.low >= minTemp) {
            filteredData.push_back(candle);
        }
    }

    if (!filteredData.empty()) {
        computeTextPlot(filteredData);
    } else {
        std::cout << "No candlestick data available for the specified filters." << std::endl;
    }
}

std::pair<double, double> Candlestick::linearRegression(const std::vector<double>& x, const std::vector<double>& y) {
    double n = x.size();
    double sum_x = std::accumulate(x.begin(), x.end(), 0.0);
    double sum_y = std::accumulate(y.begin(), y.end(), 0.0);
    double sum_xx = std::inner_product(x.begin(), x.end(), x.begin(), 0.0);
    double sum_xy = std::inner_product(x.begin(), x.end(), y.begin(), 0.0);

    double slope = (n * sum_xy - sum_x * sum_y) / (n * sum_xx - sum_x * sum_x);
    double intercept = (sum_y - slope * sum_x) / n;
    std::cout << "Slope: " << slope << ", Intercept: " << intercept << std::endl;
    return {slope, intercept};
}