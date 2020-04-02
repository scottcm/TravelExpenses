#pragma once

#include <iostream>
#include <string>

using namespace std;

const int EXPENSE_SIZE = 3;		// Length of the _expenses array
const int TIME_SIZE = 2;		// Length of time arrays
const int TOTAL_EXPENSES = 0;   // Index of _expenses for total expenses amount
const int TOTAL_ALLOWED = 1;    // Index of _expenses for total allowed amount
const int EXCESS_EXPENSE = 2;		// EXCESS_EXPENSE amount
const int HOURS = 0;            // Index for hour in a time array
const int MINUTES = 1;          // Index for minute in a time array
const int MAX_HOUR = 24;
const int MIN_HOUR = 0;
const int MAX_MINUTE = 60;
const int MIN_MINUTE = 0;
const int MIN_TRIP_LENGTH = 1;

const double MILEAGE_RATE = 0.27;
const double MAX_PARKING_FEE_PER_DAY = 6.00;
const double MAX_TAXI_FEE_PER_DAY = 10.00;
const double MAX_HOTEL_FEE_PER_NIGHT = 90.00;
const double MAX_BREAKFAST_COST = 9.00;
const double MAX_LUNCH_COST = 12.00;
const double MAX_DINNER_COST = 16.00;

const int FIRST_DAY_BREAKFAST_CUTOFF = 7;
const int FIRST_DAY_LUNCH_CUTOFF = 12;
const int FIRST_DAY_DINNER_CUTOFF = 18;
const int LAST_DAY_BREAKFAST_CUTOFF = 8;
const int LAST_DAY_LUNCH_CUTOFF = 13;
const int LAST_DAY_DINNER_CUTOFF = 19;

const int BREAKFAST_MEAL = 0;		// ID for breakfast
const int LUNCH_MEAL = 1;			// ID for lunch
const int DINNER_MEAL = 2;			// ID for dinner


// Prototypes for Time
void GetTime(string question, int* time);
bool IsValidHour(int);
bool IsValidMinute(int);
void SetArrivalTime(int hour, int minute);
void SetDepartureTime(int hour, int minute);
string ToTimeString(int time[], int size);

// Prototypes for Helper functions
void ResetGlobalValues();
bool AskYesNo(string question);
int GetLengthOfTrip();
double GetExpenseAmount(string question, double minValue);
void AddExpense(double expenseAmount);
void AddExpense(double expenseAmount, double maxAmount);
double GetTotalExpenses();
double GetTotalAllowed();
double GetExcessExpenses();
bool AllowMealExpense(int meal, int tripDay);

// Prototypes for Expenses
void AddFlightExpense();
void AddCarRentalExpense();
void AddMileageExpense(double mileageRate);
void AddParkingFees(int tripLength, double maxPerDay);
void AddTaxiFees(int tripLength, double maxPerDay);
void AddConferenceFee();
void AddHotelExpense(int tripLength, double maxPerNight);
void AddMealExpenses(int tripLength);
void DisplayExpenseReport();
