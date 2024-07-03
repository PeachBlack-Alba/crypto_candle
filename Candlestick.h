#pragma once
#include <string>
#include <vector>

class Candlestick {
public:
    Candlestick(const std::string& date, float open, float high, float low, float close);

    std::string date;
    float open;
    float high;
    float low;
    float close;
    
    static Candlestick computeYearlyCandlestick(const std::vector<float>& temperatures, const std::vector<float>& previousYearTemperatures, const std::string& year);
    static Candlestick computeMonthlyCandlestick(const std::vector<float>& temperatures, const std::vector<float>& previousMonthTemperatures, const std::string& year, const std::string& month);
    static void computeTextPlot(const std::vector<Candlestick>& candlesticks);
    static void filterAndPlotData(const std::vector<Candlestick>& data, const std::string& startDate, const std::string& endDate, double minTemp, double maxTemp);

private:
    static void drawCandlestick(float open, float close, float high, float low, double lowerRange, double higherRange);
    static double getHighestHigh(const std::vector<Candlestick>& candlesticks);
    static double getLowestLow(const std::vector<Candlestick>& candlesticks);
    static std::pair<double, double> linearRegression(const std::vector<double>& x, const std::vector<double>& y);

};