#include "TravelExpenses.h"
#include <iomanip>

// Add expenses for each meal during the trip
void AddMealExpenses(int tripLength)
{
    double breakfast_fee;
    double lunch_fee;
    double dinner_fee;
    
    cout << "You departed on your trip at " << GetDepartureTime() << " and arrived back at " << GetArrivalTime() << endl;
    for (int tripDay = 1; tripDay <= tripLength; tripDay++)
    {
        cout << "Please enter the amount you spent on meals for day " << tripDay << endl;
        if (AllowMealExpense(BREAKFAST_MEAL, tripDay))
        {
            breakfast_fee = GetExpenseAmount("How much did you pay for breakfast? ", 0);
            AddExpense(breakfast_fee, MAX_BREAKFAST_COST);
        }
        else
        {
            cout << "You " << ((tripDay == 1) ? "departed too late" : "arrived back too early") << " to expense breakfast on this day.\n";
        }

        // Lunch
        if (AllowMealExpense(LUNCH_MEAL, tripDay))
        {
            lunch_fee = GetExpenseAmount("How much did you pay for lunch? ", 0);
            AddExpense(lunch_fee, MAX_LUNCH_COST);
        }
        else
        {
            cout << "You " << ((tripDay == 1) ? "departed too late" : "arrived back too early") << " to expense lunch on this day.\n";
        }

        // Dinner
        if (AllowMealExpense(DINNER_MEAL, tripDay))
        {
            dinner_fee = GetExpenseAmount("How much did you pay for dinner? ", 0);
            AddExpense(dinner_fee, MAX_DINNER_COST);
        }
        else
        {
            cout << "You " << ((tripDay == 1) ? "departed too late" : "arrived back too early") << " to expense dinner on this day.\n";
        }

        cout << endl;
    }
}

//Display Report
void DisplayExpenseReport()
{
    // Display a report header and ensure that dollar amounts have 2 decimals
    cout << setprecision(2) << fixed;
    cout << endl;
    cout << "************************************************\n";
    cout << "                 Expense Report                 \n";
    cout << "------------------------------------------------\n";
    cout << "TOTAL EXPENSES INCURRED: $" << GetTotalExpenses() << endl;
    cout << "EXPENSES OVER ALLOWED  : $" << GetExcessExpenses() << endl;
    cout << "MAX ALLOWED EXPENSES   : $" << GetTotalAllowed() << endl;
    cout << endl;

    // If expenses incurred is greater than reimbursable expenses then company is owed money
    if (GetTotalExpenses() < GetTotalAllowed())
    {
        cout << "Thank you! You saved the company $" << (GetTotalAllowed() - GetTotalExpenses()) << endl;
        if (GetExcessExpenses() > 0)
        {
            cout << "Although you saved the company money, you exceeded a daily maximum expense amount.\n";
            cout << "Some expenses have a maximum allowable amount. Try to keep those expenses under the cap.\n";
        }
    }
    else if (GetTotalExpenses() > GetTotalAllowed())
    {
        // More was spent then is allowed
        cout << "You exceeded the maximum allowable expenses.\n";
        cout << "Try to be more careful about your expense amounts.\n";
    }

    // Inform the user how much they need to pay back to the company
    if (GetExcessExpenses() > 0)
    {
        cout << "You need to reimburse the company $" << GetExcessExpenses();
    }
}