#include "TradeRepository.hpp"
#include <iostream>

TradeRepository::TradeRepository(const std::string& db_path) : db(nullptr) {
    open(db_path);
}

TradeRepository::~TradeRepository() {
    close();
}

bool TradeRepository::open(const std::string& db_path) {
    if (sqlite3_open(db_path.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Could not open DB: " << sqlite3_errmsg(db) << "\n";
        return false;
    }
    return true;
}

void TradeRepository::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

std::vector<Trade> TradeRepository::getAllTrades() {
    std::vector<Trade> trades;
    const char* sql = "SELECT trade_id, underlying_ticker, product_type, payoff, trade_date, "
                      "trade_maturity, dividend, option_style, structured_params, user_id, strike FROM trades;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare query: " << sqlite3_errmsg(db) << "\n";
        return trades;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Trade t;
        t.trade_id = sqlite3_column_int(stmt, 0);
        t.underlying_ticker = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        t.product_type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        t.payoff = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        t.trade_date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        t.trade_maturity = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        t.dividend = sqlite3_column_double(stmt, 6);
        t.option_style = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
        t.structured_params = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
        t.user_id = sqlite3_column_int(stmt, 9);
        t.strike = sqlite3_column_double(stmt, 10);

        trades.push_back(t);
    }

    sqlite3_finalize(stmt);
    return trades;
}