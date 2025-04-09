#ifndef TRADE_CALENDAR_SCHEDULE_HPP
#define TRADE_CALENDAR_SCHEDULE_HPP

#include "QuantLibToolKit.hpp"
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

class TradeCalendarSchedule {
public:
    TradeCalendarSchedule(
        const std::string& valuationDate = "2023-04-22",
        const std::string& terminationDate = "2023-07-22",
        const std::string& calendar = "theUK",
        const std::string& yearFractionConvention = "Actual365",
        const std::string& frequency = "monthly"
    );

    // Getters
    std::string getValuationDate() const;
    std::string getTerminationDate() const;
    std::string getCalendarName() const;
    std::string getYearFractionConventionName() const;
    std::string getFrequency() const;

    std::vector<QuantLib::Date> getScheduledDates() const;
    std::vector<double> getYearFractions() const;
    int getDaysUntilExpiration() const;

    // Setters (with validation)
    void setValuationDate(const std::string& valuationDate);
    void setTerminationDate(const std::string& terminationDate);
    void setCalendar(const std::string& calendar);
    void setYearFractionConvention(const std::string& conv);
    void setFrequency(const std::string& frequency);

private:
    std::string _valuationDate;
    std::string _terminationDate;
    std::string _calendar;
    std::string _yearFractionConvention;
    std::string _frequency;

    std::vector<QuantLib::Date> scheduledDates;
    std::vector<double> yearFractions;
    int daysUntilExpiration;

    std::map<std::string, std::string> processTradeInfoData(int tradeId = 1);
    void generateSchedule();  // internal logic reused by setters
};

#endif // TRADE_CALENDAR_SCHEDULE_HPP