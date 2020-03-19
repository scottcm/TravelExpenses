// TravelExpenses.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "TravelExpenses.h"
#include <iomanip>

/************ Pre-processor directives to make testing easier ***************/
// Change any value to 1 to enable running the test code
#define TEST_SCOTT_PARTS 0
#define TEST_NGHIA_PARTS 0
#define TEST_SEAM_PARTS 0
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

    // Add flight expense
    if (AskYesNo("Did you take a flight?"))
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

// Set's *time to the hour and minute specified. Does no validation
void SetTime(int hour, int minute, int* time)
{
    time[HOURS] = hour;
    time[MINUTES] = minute;
}

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

void SetArrivalTime(int hour, int minute)
{
    _arrivalTime[HOURS] = hour;
    _arrivalTime[MINUTES] = minute;
}

void SetDepartureTime(int hour, int minute)
{
    _departureTime[HOURS] = hour;
    _departureTime[MINUTES] = minute;
}

// Code for testing time functionality
void TestTime()
{
    cout << "**** START TESTING TIME ****\n";

    cout << "Testing IsValidHour(int)\n";
    // Test hour < 0, hour > 23, minute < 0, minute > 59
    // Test valid hour & invalid minute
    // Test invalid hour & valid minute
    cout << "Hour -1 : " << (IsValidHour(-1) ? "FAIL" : "PASS") << endl;    // Hour < 0 - fail
    cout << "Hour  0 : " << (IsValidHour(0) ? "PASS" : "FAIL") << endl;     // 0 hour - pass
    cout << "Hour 23 : " << (IsValidHour(23) ? "PASS" : "FAIL") << endl;    // 23 hour - pass
    cout << "Hour 24 : " << (IsValidHour(24) ? "FAIL" : "PASS") << endl;    // Hour > 23 - fail

    cout << "Testing IsValidMinute(int)\n";
    cout << "Minute -1 : " << (IsValidMinute(-1) ? "FAIL" : "PASS") << endl;    // Minute < 0 - fail
    cout << "Minute  0 : " << (IsValidMinute(0) ? "PASS" : "FAIL") << endl;     // 0 min - pass
    cout << "Minute 59 : " << (IsValidMinute(0) ? "PASS" : "FAIL") << endl;     // 0 min - pass
    cout << "Minute 60 : " << (IsValidMinute(-1) ? "FAIL" : "PASS") << endl;    // Minute > 59 - fail

    // Test ToTimeString
    cout << "\nTest ToTimeString(int[])\n";
    int testTime[TIME_SIZE];
    string returnedTime;

    SetTime(7, 0, testTime);
    returnedTime = ToTimeString(testTime, TIME_SIZE);
    cout << "07:00 == " << returnedTime << " -> " <<
        ((returnedTime == "07:00") ? "PASS" : "FAIL") << endl;

    SetTime(0, 0, testTime);
    returnedTime = ToTimeString(testTime, TIME_SIZE);
    cout << "00:00 == " << returnedTime << " -> " <<
        ((returnedTime == "00:00") ? "PASS" : "FAIL") << endl;

    SetTime(23, 9, testTime);
    returnedTime = ToTimeString(testTime, TIME_SIZE);
    cout << "23:09 == " << returnedTime << " -> " <<
        ((returnedTime == "23:09") ? "PASS" : "FAIL") << endl;

    SetTime(10, 10, testTime);
    returnedTime = ToTimeString(testTime, TIME_SIZE);
    cout << "10:10 == " << returnedTime << " -> " <<
        ((returnedTime == "10:10") ? "PASS" : "FAIL") << endl;

    // Test IsTimeBefore
    cout << "\nTest IsTimeBefore(int[2], int[2]\n";
    int t1[TIME_SIZE], t2[TIME_SIZE];

    SetTime(7, 0, t1);
    SetTime(8, 0, t2);
    cout << ToTimeString(t1, TIME_SIZE) << " < " << ToTimeString(t2, TIME_SIZE) << " -> " <<  // Hour before
        (IsTimeBefore(t1, t2, TIME_SIZE) ? "PASS" : "FAIL") << endl;

    SetTime(7, 14, t1);
    SetTime(7, 15, t2);
    cout << ToTimeString(t1, TIME_SIZE) << " < " << ToTimeString(t2, TIME_SIZE) << " -> " <<  // Hour same, minute before
        (IsTimeBefore(t1, t2, TIME_SIZE) ? "PASS" : "FAIL") << endl;

    SetTime(8, 0, t1);
    SetTime(7, 0, t2);
    cout << ToTimeString(t1, TIME_SIZE) << " < " << ToTimeString(t2, TIME_SIZE) << " -> " <<  // Hour after
        (IsTimeBefore(t1, t2, TIME_SIZE) ? "FAIL" : "PASS") << endl;

    SetTime(7, 1, t1);
    SetTime(7, 0, t2);
    cout << ToTimeString(t1, TIME_SIZE) << " < " << ToTimeString(t2, TIME_SIZE) << " -> " <<  // Hour same, minute before
        (IsTimeBefore(t1, t2, TIME_SIZE) ? "FAIL" : "PASS") << endl;

    SetTime(23, 59, t1);
    SetTime(23, 59, t2);
    cout << ToTimeString(t1, TIME_SIZE) << " < " << ToTimeString(t2, TIME_SIZE) << " -> " <<  // Same time
        (IsTimeBefore(t1, t2, TIME_SIZE) ? "FAIL" : "PASS") << endl;

    // Test IsTimeAfter
    cout << "\nTest IsTimeAfter(int[2], int[2]\n";

    SetTime(8, 0, t1);
    SetTime(7, 0, t2);
    cout << ToTimeString(t1, TIME_SIZE) << " < " << ToTimeString(t2, TIME_SIZE) << " -> " <<  // Hour is after
        (IsTimeAfter(t1, t2, TIME_SIZE) ? "PASS" : "FAIL") << endl;

    SetTime(8, 15, t1);
    SetTime(8, 14, t2);
    cout << ToTimeString(t1, TIME_SIZE) << " < " << ToTimeString(t2, TIME_SIZE) << " -> " <<  // Hour same, minute is after
        (IsTimeAfter(t1, t2, TIME_SIZE) ? "PASS" : "FAIL") << endl;

    SetTime(7, 0, t1);
    SetTime(8, 0, t2);
    cout << ToTimeString(t1, TIME_SIZE) << " < " << ToTimeString(t2, TIME_SIZE) << " -> " <<  // Hour is before
        (IsTimeAfter(t1, t2, TIME_SIZE) ? "FAIL" : "PASS") << endl;

    SetTime(8, 0, t1);
    SetTime(8, 1, t2);
    cout << ToTimeString(t1, TIME_SIZE) << " < " << ToTimeString(t2, TIME_SIZE) << " -> " <<  // Hour same, minute before
        (IsTimeAfter(t1, t2, TIME_SIZE) ? "FAIL" : "PASS") << endl;

    SetTime(23, 59, t1);
    SetTime(23, 59, t2);
    cout << ToTimeString(t1, TIME_SIZE) << " < " << ToTimeString(t2, TIME_SIZE) << " -> " <<  // Same time
        (IsTimeAfter(t1, t2, TIME_SIZE) ? "FAIL" : "PASS") << endl;

    // Test User Input
    if (AskYesNo("\nTest user input?"))
    {
        cout << "\nTest Time User Input\n";
        GetTime("What time did you depart for your destination?", _arrivalTime);
        GetTime("What time did you arrive back?", _departureTime);
    }

    cout << "\n\n**** END TESTING TIME ****\n";
}

// Code for testing expense helper functionality
void TestExpenses()
{
    double cost1, cost2;
    double total, reimbursed, allowed;

    cout << "\n\n**** START TESTING EXPENSES ****\n";

    // Test AddExpense(double)
    cout << "\nTest AddExpense(double)\n";
    // Test negative cost
    ShowExpenses(0, 0, 0);
    AddExpense(-1);
    cout << "Add -$1.00\n";
    ShowExpenses(0, 0, 0);

    // Test cost is 0
    cost1 = 0;
    cout << "Add $0\n";
    AddExpense(cost1);
    ShowExpenses(cost1, cost1, cost1);

    // Test positive cost
    cost1 = 1.5;
    cout << "Add $1.50\n";
    AddExpense(cost1);
    ShowExpenses(cost1, cost1, cost1);

    cout << "\nResetting expenses\n";
    ResetGlobalValues();
    ShowExpenses(0, 0, 0);

    // Test AddExpense(double, double)
    // Test negative cost
    cout << "\nTest AddExpense(double, double)\n";
    cout << "Add -$1.00, max $0\n";
    AddExpense(-1, 0);
    ShowExpenses(0, 0, 0);

    // Test cost > max
    cost1 = 1.5;
    cost2 = 1;
    total = _expenses[TOTAL_EXPENSES] + cost1;
    reimbursed = _expenses[REIMBURSEMENT] + cost2;
    allowed = _expenses[TOTAL_ALLOWED] + cost2;
    cout << "Add $1.50, max $1\n";
    AddExpense(cost1, cost2);
    ShowExpenses(total, reimbursed, allowed);

    // Test cost < max
    cost1 = 1.25;
    cost2 = 5.5;
    total = _expenses[TOTAL_EXPENSES] + cost1;
    reimbursed = _expenses[REIMBURSEMENT] + cost1;
    allowed = _expenses[TOTAL_ALLOWED] + cost2;
    cout << "Add $1.25, max $5.50\n";
    AddExpense(cost1, cost2);
    ShowExpenses(total, reimbursed, allowed);

    // Test cost and max is same
    cost1 = 3;
    cost2 = 3;
    total = _expenses[TOTAL_EXPENSES] + cost1;
    reimbursed = _expenses[REIMBURSEMENT] + cost2;
    allowed = _expenses[TOTAL_ALLOWED] + cost2;
    cout << "Add $3.30, max $2.70\n";
    AddExpense(cost1, cost2);
    ShowExpenses(total, reimbursed, allowed);

    if (AskYesNo("\nTest user input?"))
    {
        ResetGlobalValues();
        cost1 = GetExpenseAmount("Expense 1: ", 0);
        cost2 = GetExpenseAmount("Expense 2 (max $50): ", 0);
        AddExpense(cost1);
        AddExpense(cost2, 50.00);
    }
}

// Driver function for testing Scott's code areas
// Has to be in same code file as the global variables
void TestScottParts()
{
    int lengthOfTrip;

    // Test Length of Trip
    if (AskYesNo("Test Length of Trip?"))
    {
        lengthOfTrip = GetLengthOfTrip();
    }
    else
    {
        lengthOfTrip = 3;
    }

    // Test Time functions
    if (AskYesNo("Test Time?"))
    {
        TestTime();
    }

    if (AskYesNo("Test Expenses?"))
    {
        TestExpenses();
    }

    ResetGlobalValues();

    // Should have end to end testing. Possibly put here.
}