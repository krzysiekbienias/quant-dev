#include "QuantLibToolKit.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace QuantLib;

namespace {
    const std::map<std::string, BusinessDayConvention> weekdayCorrections = {
        {"Following", Following},
        {"ModifiedFollowing", ModifiedFollowing},
        {"Preceding", Preceding},
        {"ModifiedPreceding", ModifiedPreceding},
        {"Unadjusted", Unadjusted}
    };

    const std::map<std::string, DateGeneration::Rule> dateGenRules = {
        {"forward", DateGeneration::Forward},
        {"backward", DateGeneration::Backward}
    };

    const std::map<std::string, Frequency> freqMap = {
        {"daily", Daily},
        {"once", Once},
        {"monthly", Monthly},
        {"quarterly", Quarterly},
        {"semiannual", Semiannual},
        {"annual", Annual}
    };
}

Date QuantLibToolKit::stringToQLDate(const std::string& date) {
    int year, month, day;
    char delim;
    std::istringstream iss(date);
    iss >> year >> delim >> month >> delim >> day;
    return Date(day, static_cast<Month>(month), year);
}

Date QuantLibToolKit::dateObjectToQLDate(int year, int month, int day) {
    return Date(day, static_cast<Month>(month), year);
}

Calendar QuantLibToolKit::setCalendar(const std::string& country) {
    if (country == "USA") return UnitedStates(UnitedStates::NYSE);
    if (country == "theUK") return UnitedKingdom();
    if (country == "Switzerland") return Switzerland();
    if (country == "Poland") return Poland();
    throw std::invalid_argument("Invalid country for calendar");
}

BusinessDayConvention QuantLibToolKit::setDateCorrectionRule(const std::string& rule) {
    return weekdayCorrections.at(rule);
}

DateGeneration::Rule QuantLibToolKit::setDateGenerationRule(const std::string& rule) {
    return dateGenRules.at(rule);
}

Frequency QuantLibToolKit::setFrequency(const std::string& freq) {
    return freqMap.at(freq);
}

DayCounter QuantLibToolKit::setYearFractionConvention(const std::string& conv) {
    if (conv == "Actual360") return Actual360();
    if (conv == "Actual365") return Actual365Fixed();
    if (conv == "ActualActual") return ActualActual(ActualActual::ISDA);
    if (conv == "Thirty360") return Thirty360(Thirty360::USA);
    if (conv == "Business252") return Business252();
    throw std::invalid_argument("Invalid year fraction convention");
}

Schedule QuantLibToolKit::defineSchedule(const std::string& start,
                                         const std::string& end,
                                         const std::string& freq,
                                         const std::string& calendar,
                                         const std::string& correctionRule) {
    return MakeSchedule()
        .from(stringToQLDate(start))
        .to(stringToQLDate(end))
        .withFrequency(setFrequency(freq))
        .withCalendar(setCalendar(calendar))
        .withConvention(setDateCorrectionRule(correctionRule))
        .endOfMonth(true);
}

void QuantLibToolKit::displaySchedule(const Schedule& schedule) {
    for (auto const& d : schedule)
        std::cout << d << std::endl;
}

std::vector<double> QuantLibToolKit::consecutiveYearFractions(const Schedule& schedule, const DayCounter& dc) {
    std::vector<double> result;
    for (Size i = 1; i < schedule.size(); ++i)
        result.push_back(dc.yearFraction(schedule[i - 1], schedule[i]));
    return result;
}

std::vector<double> QuantLibToolKit::cumulativeYearFractions(const Schedule& schedule, const DayCounter& dc) {
    std::vector<double> result;
    for (Size i = 1; i < schedule.size(); ++i)
        result.push_back(dc.yearFraction(schedule[0], schedule[i]));
    return result;
}