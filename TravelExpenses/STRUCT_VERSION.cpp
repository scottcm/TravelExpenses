// TravelExpenses.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Calculate and display the total travel expenses of a business person on a trip

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#define TEST 0


// Global constants
// Reimbursement constants
const double _MILEAGE_RATE = 0.27;
const double _MAX_PARKING_FEE_PER_DAY = 6.00;
const double _MAX_TAXI_FEE_PER_DAY = 10.00;
const double _MAX_HOTEL_FEE_PER_NIGHT = 90.00;
const double _MAX_BREAKFAST_FEE = 9.00;
const double _MAX_LUNCH_FEE = 12.00;
const double _MAX_DINNER_FEE = 16.00;
const int _FIRST_DAY_BREAKFAST_CUTOFF = 7;
const int _FIRST_DAY_LUNCH_CUTOFF = 12;
const int _FIRST_DAY_DINNER_CUTOFF = 18;
const int _LAST_DAY_BREAKFAST_CUTOFF = 8;
const int _LAST_DAY_LUNCH_CUTOFF = 13;
const int _LAST_DAY_DINNER_CUTOFF = 19;
const string _BREAKFAST_MEAL = "breakfast";
const string _LUNCH_MEAL = "lunch";
const string _DINNER_MEAL = "dinner";

// Magic # constants
const int _MIN_TRIP_DAYS = 1;
const int _MIN_SOMETHING = 1;


struct Time
{
    int Hour;
    int Minute;

    string ToString()
    {
        string time = ((Hour < 10) ? "0" + to_string(Hour) : to_string(Hour)) + ":" +
            ((Minute < 10) ? "0" + to_string(Minute) : to_string(Minute));
        
        return time;
    }

    void AskForTime(string userMessage)
    {
        char separator;
        int hour, minute;
        bool invalidHour = true, invalidMinute = true;
#if TEST == 1
		int maxLoopCount;
#endif

        do
        {
            cout << userMessage << " (24-Hour clock, HH:MM): ";
#if TEST == 1
		maxLoopCount = testCases->getMaxLoopCount();
		if (testCases->LoopCount > maxLoopCount)
		{
			return -1;
		}
		testCases->LoopCount++;
		hour = testCases->GetIntTestValue();
		minute = testCases->GetIntTestValue();
#else
            cin >> hour >> separator >> minute;
			cin.ignore(); // Ignore the enter after the user input.
#endif

            invalidHour = hour > 23 || hour < 0;
            invalidMinute = minute > 59 || minute < 0;
        } while (invalidHour && invalidMinute);

        Hour = hour;
        Minute = minute;
    }
};

bool operator< (Time& t1, Time& t2)
{
    if (t1.Hour < t2.Hour)
    {
        return true;
    }
    else if (t1.Hour == t2.Hour)
    {
        return t1.Minute < t2.Minute;
    }

    return false;
}

bool operator> (Time& t1, Time& t2)
{
    if (t1.Hour > t2.Hour)
    {
        return true;
    }
    else if (t1.Hour == t2.Hour)
    {
        return t1.Minute > t2.Minute;
    }

    return false;
}

// Structure for days and times of business trip
struct BusinessTrip
{
    int NumberOfDays;
    Time ArrivalTime{ 0,0 };
    Time DepartureTime{ 0,0 };

    bool CanExpenseBreakfast(int dayOfTrip)
    {
        if (dayOfTrip > 1 && dayOfTrip < (NumberOfDays - 1))
        {
            return true;
        }
        
        Time cutoff;
        if (dayOfTrip == 1)
        {
            cutoff = Time{ _FIRST_DAY_BREAKFAST_CUTOFF, 0 };
            return DepartureTime < cutoff;
        }

        // Must be last day of trip
        cutoff = Time{ _LAST_DAY_BREAKFAST_CUTOFF, 0 };
        return DepartureTime > cutoff;
    }

    bool CanExpenseLunch(int dayOfTrip)
    {
        if (dayOfTrip > 1 && dayOfTrip < (NumberOfDays - 1))
        {
            return true;
        }

        Time cutoff;
        if (dayOfTrip == 1)
        {
            cutoff = Time{ _FIRST_DAY_LUNCH_CUTOFF, 0 };
            return DepartureTime < cutoff;
        }

        // Must be last day of trip
        cutoff = Time{ _LAST_DAY_LUNCH_CUTOFF, 0 };
        return DepartureTime > cutoff;
    }

    bool CanExpenseDinner(int dayOfTrip)
    {
        if (dayOfTrip > 1 && dayOfTrip < (NumberOfDays - 1))
        {
            return true;
        }

        Time cutoff;
        if (dayOfTrip == 1)
        {
            cutoff = Time{ _FIRST_DAY_DINNER_CUTOFF, 0 };
            return DepartureTime < cutoff;
        }

        // Must be last day of trip
        cutoff = Time{ _LAST_DAY_DINNER_CUTOFF, 0 };
        return DepartureTime > cutoff;
    }
};

// Structure to keep track of expense report details
struct ExpenseReport
{
    double TotalExpenses{ 0.00 };       // Total amount of the expense report
    double ReimbursementAmout{ 0.00 };  // Amount that will be reimbursed;
    BusinessTrip BusinessTrip{ 0 };  // Days and times of trip

    void AddExpense(double amount)
    {
        TotalExpenses += amount;
        ReimbursementAmout += amount;
    }

    void AddExpense(double amount, double maxExpense)
    {
        TotalExpenses += amount;
        ReimbursementAmout += (amount > maxExpense) ? maxExpense : amount;
    }
};

ExpenseReport CreateExpenseReport();
void DisplayExpenseReport(ExpenseReport);
int TotalDaysOnTrip();
double GetCarRentalExpenses();
double GetFlightExpenses();
double GetMileageExpense(double reinbursementRate);
ExpenseReport GetPerDayMealExpense(int tripDay, BusinessTrip trip);
ExpenseReport GetTotalMealExpense(BusinessTrip businessTrip);
ExpenseReport GetTaxiExpense(double maxDailyExpense, int lengthOfTrip);
ExpenseReport GetHotelExpenses(double maxDailyExpense, int lengthOfTrip);
double GetConferenceFees();
bool AskYesNo(string question);
double GetCost(string message, double minCost);

#if TEST == 1
class ExpenseReportTest
{
private:
    int testCount = 0;
    int testFailureCount = 0;
    int intTestValues[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int intArrayLength = 0;
    double dblTestValues[10] = { 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00 };
    int dblArrayLength = 0;
    int maxLoopCount = 0;

    void ClearIntArray()
    {
        intArrayLength = 0;
        for (int i = 0; i < 10; i++)
        {
            this->intTestValues[i] = 0;
        }

        this->LoopCount = 0;
    }

    void ClearDblArray()
    {
        dblArrayLength = 0;
        for (int i = 0; i < 10; i++)
        {
            this->dblTestValues[i] = 0.00;
        }
        this->LoopCount = 0;
    }
public:
    int TestIndex = 0;
    int LoopCount = 0;
	BusinessTrip TestTrip{ 1, {0,0}, {0,0} };

    // Properties
    int getTestFailureCount()
    {
        return this->testFailureCount;
    }

    int getTestCount()
    {
        return this->testCount;
    }

    // Methods
    void StartTest()
    {
        this->testCount++;
    }
    void EndTest(bool testPassed)
    {
        if (!testPassed)
        {
            this->testFailureCount++;
        }
    }

    int GetIntTestValue()
    {
        int value;
        if (this->TestIndex >= this->intArrayLength)
        {
            this->TestIndex = 0;
        }

        value = this->intTestValues[this->TestIndex];
        this->TestIndex++;

        return value;
    }

    double GetDblTestValue()
    {
        double value;
        if (this->TestIndex >= this->dblArrayLength)
        {
            this->TestIndex = 0;
        }

        value = this->dblTestValues[this->TestIndex];
        this->TestIndex++;

        return value;
    }

    int getMaxLoopCount()
    {
        return this->maxLoopCount;
    }

    void RunUnitTests()
    {
        EndTest(TestLengthOfStay());
    }

    bool TestLengthOfStay()
    {
        this->TestIndex = 0;
        this->intArrayLength = 3;
        this->intTestValues[0] = -1;
        this->intTestValues[1] = 0;
        this->intTestValues[2] = 1;

        cout << "\n\nTESTING LengthOfStay()\n\n";
        StartTest();
        bool testFailed = false;
        this->maxLoopCount = 5;
        // Test -1, 0
        if (TotalDaysOnTrip() == 1 && this->LoopCount == 3)
        {
            cout << "**** Test case #1 passed.\n";
        }
        else
        {
            testFailed = true;
            this->testFailureCount++;
            cout << "**** Test case #1 failed.\n";
        }

        // Test 10
        ClearIntArray();
        this->intArrayLength = 2;
        this->intTestValues[0] = 10;
        this->maxLoopCount = 3;

        if (TotalDaysOnTrip() == 10 && this->LoopCount == 1)
        {
            cout << "\n**** Test case #2 passed.\n";
        }
        else
        {
            testFailed = true;
            this->testFailureCount++;
            cout << "\n**** Test case #2 failed.\n";
        }

        cout << "\n\nLengthOfStay() testing..." << (testFailed ? "FAILED" : "PASSED") << endl;
        return testFailed;
    }

	bool TestTime()
	{
		// Test Ask for time
		Time time;

		this->intArrayLength = 10;
		this->TestIndex = 0;

		// Hour lower than range
		this->intTestValues[0] = -1;
		this->intTestValues[1] = 5;

		// Hour after range
		this->intTestValues[2] = 24;
		this->intTestValues[3] = 5;

		// Minute before range
		this->intTestValues[4] = 1;
		this->intTestValues[5] = -1;

		// Minute after range
		this->intTestValues[6] = 1;
		this->intTestValues[7] = 60;

		// Valid time
		this->intTestValues[8] = 1;
		this->intTestValues[9] = 30;
		
		// Run tests
		time.AskForTime("Testing");

		ClearIntArray();
		this->TestIndex = 0;

		// Invalid hour and minute
		this->intTestValues[0] = 25;
		this->intTestValues[1] = 61;

		// Test Comparison operators

		// Test ToString
	}
};

ExpenseReportTest* testCases = new ExpenseReportTest();
#endif // TEST == 1

void StubMessage(string message)
{
    cout << message << endl;
}

int main()
{
#if TEST == 1
    //ExpenseReportTest testCases;
    testCases->RunUnitTests();
    return 0;
#endif // TEST == 1

    ExpenseReport report;

    report = CreateExpenseReport();
    DisplayExpenseReport(report);
    return 0;
}

ExpenseReport CreateExpenseReport()
{
    ExpenseReport report;

    // Fully initialize the new report
    report = ExpenseReport{ 0.00, 0.00, {0, 0, 0} };
#ifdef DEBUG
    cout << "****Starting state****\n";
    DisplayExpenseReport(report);
    cout << endl << endl;
#endif // DEBUG

    // Generate the expense report
    report.BusinessTrip.NumberOfDays = TotalDaysOnTrip();
    report.BusinessTrip.ArrivalTime.AskForTime("What time did you arrive at your destination?");
    report.BusinessTrip.DepartureTime.AskForTime("What time did you depart for your destination?");

    // Get vehicle expenses
    if (AskYesNo("Did you rent a vehicle?"))
    {
        // Car rental fees
        double rentalFee = GetCarRentalExpenses();
        report.AddExpense(rentalFee);
    }
    else
    {
        // Drove own car
        double mileageExpense = GetMileageExpense(_MILEAGE_RATE);
        report.AddExpense(mileageExpense);
    }

    // Airline fees
    if (AskYesNo("Did you take a flight?"))
    {
        double flightAmount = GetFlightExpenses();
        report.AddExpense(flightAmount);
    }

    // Meal expenses
    ExpenseReport meals = GetTotalMealExpense(report.BusinessTrip);
    report.TotalExpenses += meals.TotalExpenses;
    report.ReimbursementAmout = meals.ReimbursementAmout;

    // Get Taxi fees - Do NOT use AddExpense or it will mess up reimbursement
    if (AskYesNo("Did you use a taxi on your trip?"))
    {
        ExpenseReport taxi = GetTaxiExpense(_MAX_TAXI_FEE_PER_DAY, report.BusinessTrip.NumberOfDays);
        report.TotalExpenses += taxi.TotalExpenses;
        report.ReimbursementAmout += taxi.ReimbursementAmout;
    }

    // Hotel expenses - Do NOT use AddExpense or it will mess up reimbursement
    if (AskYesNo("Did you stay at a hotel?"))
    {
        ExpenseReport hotel = GetHotelExpenses(_MAX_HOTEL_FEE_PER_NIGHT, report.BusinessTrip.NumberOfDays);
        report.TotalExpenses += hotel.TotalExpenses;
        report.ReimbursementAmout += hotel.ReimbursementAmout;
    }

    // Conference fee
    if (AskYesNo("Did you go to a conference?"))
    {
        double conferenceFee = GetConferenceFees();
        report.AddExpense(conferenceFee);
    }

    return report;
}

void DisplayExpenseReport(ExpenseReport expenseReport)
{
    cout << endl << endl;
    cout << fixed << setprecision(2);
    // Stub code
    StubMessage("DisplayExpenseReport");
    cout << "Total number of days: " << expenseReport.BusinessTrip.NumberOfDays << endl;
    cout << "Total expenses: $" << expenseReport.TotalExpenses << endl;
    cout << "Reimbrusment amount: $" << expenseReport.ReimbursementAmout << endl;
}

// Returns the length of the trip in days
int TotalDaysOnTrip()
{
    int totalDays;
#if TEST == 1
    int maxLoopCount;
#endif
    // Stub code
    StubMessage("TotalDaysOnTrip");
    
    do
    {
        cout << "How many days was the trip? ";

#if TEST == 1
        maxLoopCount = testCases->getMaxLoopCount();
        if (testCases->LoopCount > maxLoopCount)
        {
            return -1;
        }
        testCases->LoopCount++;
        totalDays = testCases->GetIntTestValue();
#else
        cin >> totalDays;
        cin.ignore();   // Ignore any left over \n
#endif // TEST == 1

    } while (totalDays < _MIN_TRIP_DAYS);

    return totalDays;
}

// Returns the dollar price for a car rental
double GetCarRentalExpenses()
{
    double rentalFee;
    rentalFee = GetCost("What was the total cost of the car rental?", 0.00);
    // Stub code
    StubMessage("GetCarRentalExpenses");

    return rentalFee;
}

// Returns the dollar price of the flight
double GetFlightExpenses()
{
    // Stub code
    StubMessage("GetFlightExpenses");
    
    double ticketPrice = GetCost("How much was the flight?", 0.00);
    return ticketPrice;
}

// Returns the dollar amount of the mileage reimbursement
double GetMileageExpense(double reinbursementRate)
{
    double mileageExpense,
        milesDriven;

    // Stub code
    StubMessage("GetMileageExpense");
    
    do
    {
        cout << "What were the total miles driven? $";
        cin >> milesDriven;

        cin.ignore(); // Ignore the \n
    } while (milesDriven < 0);

    mileageExpense = milesDriven * reinbursementRate;
    return mileageExpense;
}

ExpenseReport GetPerDayMealExpense(int tripDay, BusinessTrip trip)
{
    ExpenseReport mealExpense = ExpenseReport();

    cout << "Enter meal expenses for day " << tripDay << ":";

    if (trip.CanExpenseBreakfast(tripDay))
    {
        double breakfastCost = GetCost("\t" + _BREAKFAST_MEAL, 0.00);
        mealExpense.AddExpense(breakfastCost, _MAX_BREAKFAST_FEE);
    }
    else
    {
        cout << "\tYou cannot expense " << _BREAKFAST_MEAL << " for this day.\n";
    }

    if (trip.CanExpenseLunch(tripDay))
    {
        double lunchCost = GetCost("\t" + _LUNCH_MEAL, 0.00);
        mealExpense.AddExpense(lunchCost, _MAX_LUNCH_FEE);
    }
    else
    {
        cout << "\tYou cannot expense " << _LUNCH_MEAL << " for this day.\n";
    }

    if (trip.CanExpenseDinner(tripDay))
    {
        double dinnerCost = GetCost("\t" + _DINNER_MEAL, 0.00);
        mealExpense.AddExpense(dinnerCost, _MAX_DINNER_FEE);
    }
    else
    {
        cout << "\tYou cannot expense " << _DINNER_MEAL << " for this day.\n";
    }

    return mealExpense;
}
ExpenseReport GetTotalMealExpense(BusinessTrip businessTrip)
{
    ExpenseReport expenseReport = ExpenseReport();
    ExpenseReport dailyExpense;

    // Stub code
    StubMessage("GetTotalMealExpense");
    
    // Get the daily meal expenses and add them up
    for (int i = 1; i <= businessTrip.NumberOfDays; i++)
    {
        dailyExpense = GetPerDayMealExpense(i, businessTrip);
        expenseReport.TotalExpenses += dailyExpense.TotalExpenses;
        expenseReport.ReimbursementAmout += dailyExpense.ReimbursementAmout;
    }

    return expenseReport;
}
ExpenseReport GetTaxiExpense(double maxDailyExpense, int lengthOfTrip)
{
    ExpenseReport taxiExpense = ExpenseReport();
    double dailyTaxiCost;

    // Stub code
    StubMessage("GetTaxiExpense");
    
    for (int i = 1; i <= lengthOfTrip; i++)
    {
        dailyTaxiCost = GetCost("Taxi costs for day " + i, 0.00);
        taxiExpense.AddExpense(dailyTaxiCost, _MAX_TAXI_FEE_PER_DAY);
    }

    return taxiExpense;
}

ExpenseReport GetHotelExpenses(double maxDailyExpense, int lengthOfTrip)
{
    ExpenseReport hotelExpense = ExpenseReport();
    double dailyRate;

    // Stub code
    StubMessage("GetHotelExpenses");
    
    for (int i = 1; i <= lengthOfTrip; i++)
    {
        dailyRate = GetCost("Hotel rate for day " + i, 0.00);
        hotelExpense.AddExpense(dailyRate, _MAX_HOTEL_FEE_PER_NIGHT);
    }
    return hotelExpense;
}

double GetConferenceFees()
{
    // Stub code
    StubMessage("GetConferenceFees");
    
    double fee = GetCost("Cost of conference: ", 0.00);
    return fee;
}

// Returns true if the user enters Y, false if user enters N
// Requires either Y/N answer
bool AskYesNo(string question)
{
    char response;
    bool invalidResponse = true;
    bool isYes;

    do
    {
        cout << question << "(Y/N): ";
        cin >> response;

        cin.ignore(); // Ignore enter at the end;

        switch (_toupper(response))
        {
            case 'Y':
                isYes = true;
                invalidResponse = false;
                break;
            case 'N':
                isYes = false;
                invalidResponse = false;
                break;
        }
    } while (invalidResponse);

    return isYes;
}

double GetCost(string message, double minValue)
{
    double cost;
    do
    {
        cout << message << " $";
        cin >> cost;

        cin.ignore(); // Ignore \n
    } while (cost < minValue);

    return cost;
}
