#include "TravelExpenses.h"

// Pseudo-Constants
int FIRST_DAY_BREAKFAST_TIME[TIME_SIZE]{ 7, 0 };    // 7am
int FIRST_DAY_LUNCH_TIME[TIME_SIZE]{ 12,0 };        // Noon
int FIRST_DAY_DINNER_TIME[TIME_SIZE]{ 20,0 };       // 8pm
int LAST_DAY_BREAKFAST_TIME[TIME_SIZE]{ 8,0 };      // 8am
int LAST_DAY_LUNCH_TIME[TIME_SIZE]{ 13,0 };         // 1pm
int LAST_DAY_DINNER_TIME[TIME_SIZE]{ 19,0 };        // 7pm

void AddMealExpenses(int tripLength)
{
    cout << "FUNCTION: AddMealExpenses - " << "tripLength = " << tripLength << endl;
}
void GetMealExpense(string meal, int time[])
{
    cout << "FUNCTION: GetMealExpense - " << endl <<
        "meal = " << meal << endl <<
        "time = " << ToTimeString(time, TIME_SIZE) << endl;
}
void DisplayExpenseReport(int tripLength)
{
    cout << "FUNCTION: DisplayExpenseReport - " << "tripLength = " << tripLength << endl;
}

void TestNghiaParts()
{
    ResetGlobalValues();
    //AddMealExpenses(int days);
    //GetMealExpense(string meal, int* time);
    //DisplayExpenseReport(int lengthOfTrip);
    ResetGlobalValues();
}