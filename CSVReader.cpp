#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

CSVReader::CSVReader() {}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename) {
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFilename};
    std::string line;
    if (csvFile.is_open()) {
        while (std::getline(csvFile, line)) {
            try {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            } catch (const std::exception& e) {
                std::cout << "CSVReader::readCSV bad data" << std::endl;
            }
        }
    }

    std::cout << "CSVReader::readCSV read " << entries.size() << " entries" << std::endl;
    return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator) {
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end)
            break;
        if (end >= 0)
            token = csvLine.substr(start, end - start);
        else
            token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    } while (end > 0);

    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens) {
    double price, amount;

    if (tokens.size() != 5) // bad
    {
        std::cout << "Bad line " << std::endl;
        throw std::exception{};
    }
    // we have 5 tokens
    try {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    } catch (const std::exception& e) {
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[3] << std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[4] << std::endl;
        throw;
    }

    OrderBookEntry obe{price,
                       amount,
                       tokens[0],
                       tokens[1],
                       OrderBookEntry::stringToOrderBookType(tokens[2])};

    return obe;
}

OrderBookEntry CSVReader::stringsToOBE(std::string priceString,
                                       std::string amountString,
                                       std::string timestamp,
                                       std::string product,
                                       OrderBookType orderType) {
    double price, amount;
    try {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    } catch (const std::exception& e) {
        std::cout << "CSVReader::stringsToOBE Bad float! " << priceString << std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << amountString << std::endl;
        throw;
    }
    OrderBookEntry obe{price,
                       amount,
                       timestamp,
                       product,
                       orderType};

    return obe;
}


std::map<std::string, std::map<std::string, std::vector<float>>> CSVReader::readTemperatureData(const std::string& filename) {
    std::map<std::string, std::map<std::string, std::vector<float>>> temperatureData;
    std::ifstream file(filename);
    std::string line;

    // Read the header line to get the columns
    std::getline(file, line);
    std::vector<std::string> columns;
    std::stringstream headerStream(line);
    std::string column;
    while (std::getline(headerStream, column, ',')) {
        columns.push_back(column);
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date;
        std::getline(ss, date, ',');

        std::string year = date.substr(0, 4);

        for (size_t i = 1; i < columns.size(); i += 3) {  // Skipping radiation columns
            std::string temp;
            std::getline(ss, temp, ',');
            std::getline(ss, column, ',');  // Skip radiation direct
            std::getline(ss, column, ',');  // Skip radiation diffuse

            if (!temp.empty()) {
                try {
                    float tempValue = std::stof(temp);
                    std::string country = columns[i].substr(0, 2);
                    temperatureData[country][year].push_back(tempValue);
                } catch (const std::exception& e) {
                    std::cout << "CSVReader::readTemperatureData: Invalid temperature value in file " << filename << " at line " << line << std::endl;
                }
            }
        }
    }

    return temperatureData;
}

// std::vector<std::string> CSVReader::readDates(const std::string& filename, const std::string& country) {
//     std::vector<std::string> dates;
//     std::ifstream file(filename);
//     std::string line;

//     // Read the header line to get the columns
//     std::getline(file, line);
//     std::vector<std::string> columns;
//     std::stringstream headerStream(line);
//     std::string column;
//     while (std::getline(headerStream, column, ',')) {
//         columns.push_back(column);
//     }

//     size_t countryColumn = std::find(columns.begin(), columns.end(), country + "_temperature") - columns.begin();

//     while (std::getline(file, line)) {
//         std::stringstream ss(line);
//         std::string date;
//         std::getline(ss, date, ',');

//         for (size_t i = 1; i < columns.size(); ++i) {
//             std::string temp;
//             std::getline(ss, temp, ',');
//             if (!temp.empty() && i == countryColumn) {
//                 dates.push_back(date);
//                 break;
//             }
//         }
//     }

//     return dates;
// }