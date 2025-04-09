#ifndef TRADE_HPP
#define TRADE_HPP

#include <string>

struct Trade {
    int trade_id;
    std::string underlying_ticker;
    std::string product_type;
    std::string payoff;
    std::string trade_date;
    std::string trade_maturity;
    double dividend;
    std::string option_style;
    std::string structured_params;
    int user_id;
    double strike;
};

#endif // TRADE_HPP