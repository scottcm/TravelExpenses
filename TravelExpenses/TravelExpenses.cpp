// TravelExpenses.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "TravelExpenses.h"
#include <iomanip>

/************ Pre-processor directives to make testing easier ***************/
// Change any value to 1 to enable running the test code
#define TEST_SCOTT_PARTS 0
#define TEST_NGHIA_PARTS 0
#define TEST_SEAN_PARTS 0
#define DO_NOT_RUN_APP 0

// Prototypes for testing
#if TEST_SCOTT_PARTS == 1
void TestScottParts();
#endif // TEST_SCOTT_PARTS == 1

#if TEST_NGHIA_PARTS == 1
void TestNghiaParts();
#endif // TEST_NGHIA_PARTS == 1

#if TEST_SEAN_PARTS == 1
void TestSeanParts();
#endif // TEST_SEAN_PARTS == 1

// Global variables
int _arrivalTime[TIME_SIZE];      // Arrival time. Index 0 = hours, 1 = minutes. 24-hour clock
int _departureTime[TIME_SIZE];    // Departure time. Index 0 = hours, 1 = minutes. 24-hour clock
double _expenses[EXPENSE_SIZE];   // Travel expenses. Index 0 = total, 1 = reimbursed, 2 = total allowed


// Runs test code
void RunTestCode()
{
#if TEST_SCOTT_PARTS == 1
    TestScottParts();
#endif // TEST_SCOTT_PARTS == 1

#if TEST_NGHIA_PARTS == 1
    TestNghiaParts();
#endif // TEST_NGHIA_PARTS == 1

#if TEST_SEAN_PARTS == 1
    TestSeanParts();
#endif TEST_SEAN_PARTS == 1
}


int main()
{
#if DO_NOT_RUN_APP == 1
    RunTestCode();
    return 0;
#endif // DO_NOT_RUN_APP = 1

    int tripLength;

    // Get global data needed by the rest of the app
    tripLength = GetLengthOfTrip();
    GetTime("What time did you depart for your destination?", _departureTime);
    GetTime("What time did you arrive back home?", _arrivalTime);

    // Add vehicle expenses
    if (AskYesNo("Did you use a personal vehicle?"))
    {
        AddMileageExpense(MILEAGE_RATE);
    }
    else if (AskYesNo("Did you rent a car?"))
    {
        AddCarRentalExpense();
    }

    //Add taxi expenses
    if (AskYesNo("Did you use a taxi?"))
    {
        AddTaxiFees(tripLength, MAX_TAXI_FEE_PER_DAY);
    }

    // Add flight expense
    if (AskYesNo("Did you take a round trip flight?"))
    {
        AddFlightExpense();
    }

    // Add hotel expenses
    if (AskYesNo("Did you stay at a hotel?"))
    {
        AddHotelExpense(tripLength, MAX_HOTEL_FEE_PER_NIGHT);
    }

    // Add conference fee
    if (AskYesNo("Was there a conference fee?"))
    {
        AddConferenceFee();
    }

    // Add parking fees
    if (AskYesNo("Did you pay any parking fees?"))
    {
        AddParkingFees(tripLength, MAX_PARKING_FEE_PER_DAY);
    }

    // Add meal expenses
    if (AskYesNo("Did you pay for any meals?"))
    {
        AddMealExpenses(tripLength);
    }

    DisplayExpenseReport(tripLength);
}

//Display Report
void DisplayExpenseReport(int tripLength)
{
    cout << "FUNCTION: DisplayExpenseReport - " << "tripLength = " << tripLength << endl;
}

// Adds expense to total, reimbursement, and total allowed
void AddExpense(double expenseAmount)
{
    if (expenseAmount >= 0)
    {
        _expenses[TOTAL_EXPENSES] += expenseAmount;
        _expenses[REIMBURSEMENT] += expenseAmount;
        _expenses[TOTAL_ALLOWED] += expenseAmount;
    }
}

// Adds expense to total. Up to maxAmount is added to reimbursement. maxAmount is added to total allowed
void AddExpense(double expenseAmount, double maxAmount)
{
    if (expenseAmount >= 0)
    {
        _expenses[TOTAL_EXPENSES] += expenseAmount;
        _expenses[REIMBURSEMENT] += ((expenseAmount > maxAmount) ? maxAmount : expenseAmount);
        _expenses[TOTAL_ALLOWED] += maxAmount;
    }
}

// Returns true if time is before the departure time, otherwise false
bool IsBeforeDepartureTime(int time[], int size)
{
    if (size != TIME_SIZE)
    {
        return false;
    }

    return IsTimeBefore(_departureTime, time, TIME_SIZE);
}

// Returns true if time is after the arrival time, otherwise false
bool IsAfterArrivalTime(int time[], int size)
{
    if (size != TIME_SIZE)
    {
        return false;
    }
    return IsTimeAfter(_arrivalTime, time, TIME_SIZE);
}

// Sets global variables to all zeros
void ResetGlobalValues()
{
    _arrivalTime[HOURS] = 0;
    _arrivalTime[MINUTES] = 0;
    _expenses[TOTAL_ALLOWED] = 0;
    _expenses[TOTAL_EXPENSES] = 0;
    _expenses[REIMBURSEMENT] = 0;
}

/****************************************************************/
/******** ALL CODE AFTER THIS POINT IS FOR TESTING ONLY *********/
/****************************************************************/

// Displays expense information and verifies it equals the expected amount
void ShowExpenses(double expectedTotal, double expectedReimbursement, double expectedAllowed)
{
    cout << setprecision(2) << fixed << showpoint;
    cout << "TOTAL $" << _expenses[TOTAL_EXPENSES] << " == $" << expectedTotal << "\t" <<
        " : " << ((_expenses[TOTAL_EXPENSES] == expectedTotal) ? "PASS" : "FAIL") << endl;
    cout << "REIMB $" << _expenses[REIMBURSEMENT] << " == $" << expectedReimbursement << "\t" <<
        " : " << ((_expenses[REIMBURSEMENT] == expectedReimbursement) ? "PASS" : "FAIL") << endl;
    cout << "ALLOW $" << _expenses[TOTAL_ALLOWED] << " == $" << expectedAllowed << "\t" <<
        " : " << ((_expenses[TOTAL_ALLOWED] == expectedAllowed) ? "PASS" : "FAIL") << endl << endl;;
}

// Displays expense information by itself - no verification
void ShowExpenses()
{
    cout << setprecision(2) << fixed << showpoint;
    cout << "Total Expenses  : $" << _expenses[TOTAL_EXPENSES] << endl;
    cout << "Reimbursement   : $" << _expenses[REIMBURSEMENT] << endl;
    cout << "Allowed Expenses: $" << _expenses[TOTAL_ALLOWED] << endl;
}

// Sets the arrival time
void SetArrivalTime(int hour, int minute)
{
    _arrivalTime[HOURS] = hour;
    _arrivalTime[MINUTES] = minute;
}

// Sets the departure time
void SetDepartureTime(int hour, int minute)
{
    _departureTime[HOURS] = hour;
    _departureTime[MINUTES] = minute;
}

void TestScottParts()
{

}