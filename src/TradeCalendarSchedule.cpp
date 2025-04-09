#include "TradeCalendarSchedule.hpp"

using namespace QuantLib;

TradeCalendarSchedule::TradeCalendarSchedule(
    const std::string& valuationDate,
    const std::string& terminationDate,
    const std::string& calendar,
    const std::string& yearFractionConvention,
    const std::string& frequency
) :
    _valuationDate(valuationDate),
    _terminationDate(terminationDate),
    _calendar(calendar),
    _yearFractionConvention(yearFractionConvention),
    _frequency(frequency)
{
    generateSchedule(); // build initial schedule
}

void TradeCalendarSchedule::generateSchedule() {
    Date qlStart = QuantLibToolKit::stringToQLDate(_valuationDate);
    Date qlEnd = QuantLibToolKit::stringToQLDate(_terminationDate);
    DayCounter dc = QuantLibToolKit::setYearFractionConvention(_yearFractionConvention);
    Schedule schedule = QuantLibToolKit::defineSchedule(_valuationDate, _terminationDate, _frequency, _calendar, "Following");

    scheduledDates.clear();
    for (const auto& d : schedule) {
        scheduledDates.push_back(d);
    }

    yearFractions = QuantLibToolKit::consecutiveYearFractions(schedule, dc);
    daysUntilExpiration = schedule.back() - schedule.front();
}

// Getters
std::string TradeCalendarSchedule::getValuationDate() const { return _valuationDate; }
std::string TradeCalendarSchedule::getTerminationDate() const { return _terminationDate; }
std::string TradeCalendarSchedule::getCalendarName() const { return _calendar; }
std::string TradeCalendarSchedule::getYearFractionConventionName() const { return _yearFractionConvention; }
std::string TradeCalendarSchedule::getFrequency() const { return _frequency; }

std::vector<QuantLib::Date> TradeCalendarSchedule::getScheduledDates() const {
    return scheduledDates;
}

std::vector<double> TradeCalendarSchedule::getYearFractions() const {
    return yearFractions;
}

int TradeCalendarSchedule::getDaysUntilExpiration() const {
    return daysUntilExpiration;
}

// Setters with validation
void TradeCalendarSchedule::setValuationDate(const std::string& valuationDate) {
    _valuationDate = valuationDate;
    generateSchedule();
}

void TradeCalendarSchedule::setTerminationDate(const std::string& terminationDate) {
    _terminationDate = terminationDate;
    generateSchedule();
}

void TradeCalendarSchedule::setCalendar(const std::string& calendar) {
    static const std::vector<std::string> valid = {"USA", "theUK", "Switzerland", "Poland"};
    if (std::find(valid.begin(), valid.end(), calendar) == valid.end())
        throw std::invalid_argument("Invalid calendar: " + calendar);
    _calendar = calendar;
    generateSchedule();
}

void TradeCalendarSchedule::setYearFractionConvention(const std::string& conv) {
    static const std::vector<std::string> valid = {"Actual360", "Actual365", "ActualActual", "Thirty360", "Business252"};
    if (std::find(valid.begin(), valid.end(), conv) == valid.end())
        throw std::invalid_argument("Invalid year fraction convention: " + conv);
    _yearFractionConvention = conv;
    generateSchedule();
}

void TradeCalendarSchedule::setFrequency(const std::string& frequency) {
    static const std::vector<std::string> valid = {"daily", "once", "monthly", "quarterly", "annual", "semiannual"};
    if (std::find(valid.begin(), valid.end(), frequency) == valid.end())
        throw std::invalid_argument("Invalid frequency: " + frequency);
    _frequency = frequency;
    generateSchedule();
}

// Mocked data reader
std::map<std::string, std::string> TradeCalendarSchedule::processTradeInfoData(int tradeId) {
    return {
        {"trade_id", std::to_string(tradeId)},
        {"valuation_date", _valuationDate},
        {"termination_date", _terminationDate},
        {"calendar_name", _calendar},
        {"year_convention", _yearFractionConvention},
        {"year_frequency", _frequency}
    };
}