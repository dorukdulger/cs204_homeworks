#include "ActivityBST.h"
#include <iostream>
using namespace std;

int main() {
    ActivityBST uni_calendar;
    uni_calendar.add(1000, "meeting");
    uni_calendar.add(1200, "class");
    uni_calendar.add(1100, "lecture");
    uni_calendar.add(2400, "all-nighter"); // not added because
    // time value is illegal
    ActivityBST sport_calendar;
    sport_calendar.add(930, "walk");
    sport_calendar.add(2100, "walk");
    cout << "Uni calendar: \n" << uni_calendar << "Sport calendar: \n" << sport_calendar;
    ActivityBST personal_calendar;
    personal_calendar.add(900, "breakfast");
    personal_calendar.add(2300, "sleep");
    personal_calendar.add(1600, "nap");
    personal_calendar.add(1230, "lunch");
    cout << "Personal calendar: \n" << personal_calendar;
    ActivityBST overall_calendar = sport_calendar + personal_calendar;
    cout << "Overall calendar: \n" << overall_calendar;
    ActivityBST extended_calendar(uni_calendar);
    extended_calendar.add(1500, "homework");
    cout << "Extended calendar: \n" << extended_calendar;
    extended_calendar+=personal_calendar+= sport_calendar;
    cout << "Personal calendar: \n" << personal_calendar;
    cout << "Extended calendar: \n" << extended_calendar;
    return 0;
}
