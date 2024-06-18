#pragma once

#include <string>

class Candlestick {
public:
    Candlestick(const std::string& date, double open, double high, double low, double close);

    std::string date;
    double open;
    double high;
    double low;
    double close;
};
