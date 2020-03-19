#include "TravelExpenses.h"

// Pseudo-Constants
int FIRST_DAY_BREAKFAST_TIME[TIME_SIZE]{ 7, 0 };    // 7am
int FIRST_DAY_LUNCH_TIME[TIME_SIZE]{ 12,0 };        // Noon
int FIRST_DAY_DINNER_TIME[TIME_SIZE]{ 18,0 };       // 6pm
int LAST_DAY_BREAKFAST_TIME[TIME_SIZE]{ 8,0 };      // 8am
int LAST_DAY_LUNCH_TIME[TIME_SIZE]{ 13,0 };         // 1pm
int LAST_DAY_DINNER_TIME[TIME_SIZE]{ 19,0 };        // 7pm

void AddMealExpenses(int tripLength)
{
    double breakfast_fee;
    double lunch_fee;
    double dinner_fee;
    double maxBreakfast;
    double maxLunch;
    double maxDinner;
    double total = 0, reimburse = 0, allowed = 0;
    
    for (int days = 1; days <= tripLength; days++)
    {
        cout << "Please enter the amount you spent on meals for day " << days << endl;
        breakfast_fee = GetExpenseAmount("How much did you pay for breakfast? ", 0);
        lunch_fee = GetExpenseAmount("How much did you pay for lunch? ", 0);
        dinner_fee = GetExpenseAmount("How much did you pay for dinner? ", 0);
        cout << endl;

        maxBreakfast = 0;
        maxLunch = 0;
        maxDinner = 0;

        if (days == 1)
        {
            //Check the departure time before 7am
            if (IsBeforeDepartureTime(FIRST_DAY_BREAKFAST_TIME, TIME_SIZE))
            {
                maxBreakfast = MAX_BREAKFAST_COST;
                maxLunch = MAX_LUNCH_COST;
                maxDinner = MAX_DINNER_COST;
                //Expense breakfast, lunch, and dinner
                reimburse += breakfast_fee + lunch_fee + dinner_fee;
            }
            else if (IsBeforeDepartureTime(FIRST_DAY_LUNCH_TIME, TIME_SIZE))
            {
                maxLunch = MAX_LUNCH_COST;
                maxDinner = MAX_DINNER_COST;
                //Check the departure time before Noon
                //Expense lunch, and dinner
                reimburse += lunch_fee + dinner_fee;
            }
            else if (IsBeforeDepartureTime(FIRST_DAY_DINNER_TIME, TIME_SIZE))
            {
                maxDinner = MAX_DINNER_COST;
                //Check the departure time before 6pm
                //Expense dinner
                reimburse += dinner_fee;
            }
        }
        else if (days == tripLength)
        {
            //Check the arrival time after 7pm
            if (IsAfterArrivalTime(LAST_DAY_DINNER_TIME,TIME_SIZE))
            {
                maxBreakfast = MAX_BREAKFAST_COST;
                maxLunch = MAX_LUNCH_COST;
                maxDinner = MAX_DINNER_COST;
                //Expense breakfast, lunch, and dinner
                reimburse += breakfast_fee + lunch_fee + dinner_fee;
            }
            else if (IsAfterArrivalTime(LAST_DAY_LUNCH_TIME, TIME_SIZE))
            {
                maxBreakfast = MAX_BREAKFAST_COST;
                maxLunch = MAX_LUNCH_COST;
                //Expense breakfast, and lunch
                reimburse += breakfast_fee + lunch_fee;
            }
            else if (IsAfterArrivalTime(LAST_DAY_BREAKFAST_TIME, TIME_SIZE))
            {
                maxBreakfast = MAX_BREAKFAST_COST;
                //Expense breakfast
                reimburse += breakfast_fee;
            }
        }
        else
        {
            maxBreakfast = MAX_BREAKFAST_COST;
            maxLunch = MAX_LUNCH_COST;
            maxDinner = MAX_DINNER_COST;
            reimburse += breakfast_fee + lunch_fee + dinner_fee;
        }
        AddExpense(breakfast_fee, maxBreakfast);
        AddExpense(lunch_fee, maxLunch);
        AddExpense(dinner_fee, maxDinner);
        total += breakfast_fee + lunch_fee + dinner_fee;
        allowed += maxBreakfast + maxLunch + maxDinner;
    }
    ShowExpenses(total, reimburse, allowed);
}



void TestNghiaParts()
{
    ResetGlobalValues();
    SetArrivalTime(7, 0);
    SetDepartureTime(20, 0);
    AddMealExpenses(3);
    //GetMealExpense(string meal, int* time);
    //DisplayExpenseReport(int lengthOfTrip);
    ResetGlobalValues();
}