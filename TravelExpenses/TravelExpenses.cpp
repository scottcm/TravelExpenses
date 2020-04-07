// TravelExpenses.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "TravelExpenses.h"

// Global variables
int _tripLength;                    // Length of the business trip in days
int _arrivalTime[TIME_SIZE];        // Arrival time. Index 0 = hours, 1 = minutes. 24-hour clock
int _departureTime[TIME_SIZE];      // Departure time. Index 0 = hours, 1 = minutes. 24-hour clock
double _expenses[EXPENSE_SIZE];     // Travel expenses. Index 0 = total, 1 = total allowed

int main()
{
    // Assign length, departure time, and arrival time for the trip
    AssignTripDetails();
    cout << endl;

    // Add vehicle expenses
    if (AskYesNo("Did you use a personal vehicle?"))
    {
        AddMileageExpense(MILEAGE_RATE);
        cout << endl;
    }
    else if (AskYesNo("Did you rent a car?"))
    {
        AddCarRentalExpense();
        cout << endl;
    }

    // Add parking fees
    if (AskYesNo("Did you pay any parking fees?"))
    {
        AddParkingFees(_tripLength, MAX_PARKING_FEE_PER_DAY);
        cout << endl;
    }

    //Add taxi expenses
    if (AskYesNo("Did you use a taxi?"))
    {
        AddTaxiFees(_tripLength, MAX_TAXI_FEE_PER_DAY);
        cout << endl;
    }

    // Add flight expense
    if (AskYesNo("Did you take a round trip flight?"))
    {
        AddFlightExpense();
        cout << endl;
    }

    cout << endl;
    // Add hotel expenses
    if (AskYesNo("Did you stay at a hotel?"))
    {
        AddHotelExpense(_tripLength, MAX_HOTEL_FEE_PER_NIGHT);
    }

    // Add conference fee
    if (AskYesNo("Was there a conference fee?"))
    {
        AddConferenceFee();
        cout << endl;
    }

    // Add meal expenses
    if (AskYesNo("Did you pay for any meals?"))
    {
        AddMealExpenses(_tripLength);
        cout << endl;
    }

    DisplayExpenseReport();
}

// Assigns the details for the business trip
void AssignTripDetails()
{
    // Get the length of the trip in days
    _tripLength = GetLengthOfTrip();

    // Get the departure and arrival times
    GetTime("What time did you depart for your destination?", _departureTime);
    GetTime("What time did you arrive back home?", _arrivalTime);
}

// Returns the arrival time, in 24-hour format, as a string
string GetArrivalTime()
{
    return ToTimeString(_arrivalTime, TIME_SIZE);
}

// Returns the departure time, in 24-hour format, as a string
string GetDepartureTime()
{
    return ToTimeString(_departureTime, TIME_SIZE);
}

// Returns the total expenses amount
double GetTotalExpenses()
{
    return _expenses[TOTAL_EXPENSES];
}

// Returns the total allowed amount
double GetTotalAllowed()
{
    return _expenses[TOTAL_ALLOWED];
}

// Returns the reimbursable amount
double GetExcessExpenses()
{
    return _expenses[EXCESS_EXPENSE];
}

// Adds an expense. Use when there is no maximum allowed expense
// - expenseAmount: the amount to add to total and total allowed expenses
void AddExpense(double expenseAmount)
{
    if (expenseAmount >= 0)
    {
        _expenses[TOTAL_EXPENSES] += expenseAmount;
        _expenses[TOTAL_ALLOWED] += expenseAmount;
    }
}

// Add an expense. Use when there is a maximum expense amount
// - expenseAmount: The amount to add to total expenses
// - allowedAmount: The amount that is allowed to be expenced
void AddExpense(double expenseAmount, double allowedAmount)
{
    if (expenseAmount >= 0)
    {
        _expenses[TOTAL_EXPENSES] += expenseAmount;
        _expenses[TOTAL_ALLOWED] += allowedAmount;
        if (expenseAmount > allowedAmount)
        {
            _expenses[EXCESS_EXPENSE] += (expenseAmount - allowedAmount);
        }
    }
}

// Returns true if a meal expense is allowed, otherwise false
// - meal: The meal identifier as an int
// - cutoffTime: The cutoff hour for determinining if a meal is allowed
// - tripDay: The day of the trip for which the meal occurred
bool AllowMealExpense(int meal, int tripDay)
{
    bool isAllowed;
    int cutoffTime;

    if (tripDay == 1)
    {
        switch (meal)
        {
        case BREAKFAST_MEAL:
            cutoffTime = FIRST_DAY_BREAKFAST_CUTOFF;
            break;
        case LUNCH_MEAL:
            cutoffTime = FIRST_DAY_LUNCH_CUTOFF;
            break;
        case DINNER_MEAL:
            cutoffTime = FIRST_DAY_DINNER_CUTOFF;
            break;
        default:    // Not a valid meal, so use an impossible time
            cutoffTime = -1;
        }

        isAllowed = _departureTime[HOURS] < cutoffTime;
    }
    else if (tripDay == _tripLength)
    {
        switch (meal)
        {
        case BREAKFAST_MEAL:
            cutoffTime = LAST_DAY_BREAKFAST_CUTOFF;
            break;
        case LUNCH_MEAL:
            cutoffTime = LAST_DAY_LUNCH_CUTOFF;
            break;
        case DINNER_MEAL:
            cutoffTime = LAST_DAY_DINNER_CUTOFF;
            break;
        default:    // Not a valid meal, so use an impossible time
            cutoffTime = 24;
        }

        isAllowed = _arrivalTime[HOURS] > cutoffTime;
    }
    else
    {
        // Allow any valid meal
        isAllowed = (meal >= BREAKFAST_MEAL && meal <= DINNER_MEAL);
    }

    return isAllowed;
}