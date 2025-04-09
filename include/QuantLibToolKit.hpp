#ifndef QUANT_DEV_QUANTLIBTOOLKIT_HPP
#define QUANT_DEV_QUANTLIBTOOLKIT_HPP

#include <ql/quantlib.hpp>
#include <string>
#include <vector>
#include <map>

class QuantLibToolKit {
public:
    static QuantLib::Date stringToQLDate(const std::string& date);
    static QuantLib::Date dateObjectToQLDate(int year, int month, int day);

    static QuantLib::Calendar setCalendar(const std::string& country);
    static QuantLib::BusinessDayConvention setDateCorrectionRule(const std::string& rule);
    static QuantLib::DateGeneration::Rule setDateGenerationRule(const std::string& rule);
    static QuantLib::Frequency setFrequency(const std::string& freq);
    static QuantLib::DayCounter setYearFractionConvention(const std::string& conv);

    static QuantLib::Schedule defineSchedule(const std::string& start,
                                             const std::string& end,
                                             const std::string& freq = "monthly",
                                             const std::string& calendar = "theUK",
                                             const std::string& correctionRule = "Following");

    static void displaySchedule(const QuantLib::Schedule& schedule);
    static std::vector<double> consecutiveYearFractions(const QuantLib::Schedule& schedule,
                                                        const QuantLib::DayCounter& dc = QuantLib::Actual365Fixed());
    static std::vector<double> cumulativeYearFractions(const QuantLib::Schedule& schedule,
                                                       const QuantLib::DayCounter& dc = QuantLib::Actual365Fixed());
};

#endif //QUANT_DEV_QUANTLIBTOOLKIT_HPP