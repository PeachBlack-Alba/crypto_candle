#pragma once
#include <string>

class Candlestick {
public:
    Candlestick(const std::string& date, float open, float high, float low, float close);

    std::string date;
    float open;
    float high;
    float low;
    float close;
    
    static Candlestick computeYearlyCandlestick(const std::vector<float>& temperatures, const std::vector<float>& previousYearTemperatures, const std::string& year);
    
    
    /// @brief //
    /// @param candlesticks 
    static void computeTextPlot(const std::vector<Candlestick>& candlesticks);


};
