#include "Candlestick.h"

Candlestick::Candlestick(const std::string& d, double o, double h, double l, double c)
    : date(d), open(o), high(h), low(l), close(c) {}
