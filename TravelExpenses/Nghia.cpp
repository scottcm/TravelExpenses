#include "TravelExpenses.h"
#include <iomanip>

void AddMealExpenses(int tripLength)
{
    double breakfast_fee;
    double lunch_fee;
    double dinner_fee;
    
    for (int days = 1; days <= tripLength; days++)
    {
        cout << "Please enter the amount you spent on meals for day " << days << endl;
        if (AllowMealExpense(BREAKFAST_MEAL, days))
        {
            breakfast_fee = GetExpenseAmount("How much did you pay for breakfast? ", 0);
            AddExpense(breakfast_fee, MAX_BREAKFAST_COST);
        }
        if (AllowMealExpense(LUNCH_MEAL, days))
        {
            lunch_fee = GetExpenseAmount("How much did you pay for lunch? ", 0);
            AddExpense(lunch_fee, MAX_LUNCH_COST);
        }
        if (AllowMealExpense(DINNER_MEAL, days))
        {
            dinner_fee = GetExpenseAmount("How much did you pay for dinner? ", 0);
            AddExpense(dinner_fee, MAX_DINNER_COST);
        }
        cout << endl;
    }
}

//Display Report
void DisplayExpenseReport()
{
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

    if (GetExcessExpenses() > 0)
    {
        cout << "You need to reimburse the company $" << GetExcessExpenses();
    }
}



void TestNghiaParts()
{
    ResetGlobalValues();
    SetArrivalTime(7, 0);
    SetDepartureTime(20, 0);
    AddMealExpenses(3);
    //GetMealExpense(string meal, int* time);
    //DisplayExpenseReport();
    ResetGlobalValues();
}