#ifndef TRADE_REPOSITORY_HPP
#define TRADE_REPOSITORY_HPP

#include "Trade.hpp"
#include <vector>
#include <string>
#include <sqlite3.h>

class TradeRepository {
public:
    explicit TradeRepository(const std::string& db_path);
    ~TradeRepository();

    std::vector<Trade> getAllTrades();

private:
    sqlite3* db;
    bool open(const std::string& db_path);
    void close();
};

#endif // TRADE_REPOSITORY_HPP