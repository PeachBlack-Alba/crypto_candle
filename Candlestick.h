#ifndef CANDLESTICK_H
#define CANDLESTICK_H

#include <string>

class Candlestick {
public:
    std::string date;
    double open;
    double high;
    double low;
    double close;

    Candlestick(const std::string& d, double o, double h, double l, double c);
};

#endif
