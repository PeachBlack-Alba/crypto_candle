#pragma once
#include <string>

class Candlestick {
public:
    std::string date;
    double open;
    double high;
    double low;
    double close;

    Candlestick(const std::string& date, double open, double high, double low, double close);
};
