#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>
#include <map>



class CSVReader
{
    public:
     CSVReader();   

     static std::vector<OrderBookEntry> readCSV(std::string csvFile);
     static std::vector<std::string> tokenise(std::string csvLine, char separator);
    
     static OrderBookEntry stringsToOBE(std::string price, 
                                        std::string amount, 
                                        std::string timestamp, 
                                        std::string product, 
                                        OrderBookType OrderBookType);
    
    std::map<std::string, std::map<std::string, std::vector<double>>> readTemperatureData(const std::string& filename);
    std::vector<std::string> readDates(const std::string& filename, const std::string& country);
    private:
     static OrderBookEntry stringsToOBE(std::vector<std::string> strings);

};