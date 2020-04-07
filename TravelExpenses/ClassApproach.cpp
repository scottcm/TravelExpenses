// Implements the code as classes, which makes the code more intuitive and easier to reuse.

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Time
{
private:
    const int MAX_HOUR = 23;
    const int MIN_HOUR = 0;
    const int MAX_MINUTE = 59;
    const int MIN_MINUTE = 0;

    int hour{ 0 };
    int minute{ 0 };

    // Returns true if MIN_HOUR <= hour < MAX_HOUR, otherwise false
    // - hour: The hour to evaluate
    bool IsValidHour(int hour)
    {
        return (hour >= MIN_HOUR && hour <= MAX_HOUR);
    }

    // Returns true if MIN_MINUTE <= minute < MAX_MINUTE, otherwise false
    // - minute: The minute to evaluate
    bool IsValidMinute(int minute)
    {
        return (minute >= MIN_MINUTE && minute <= MAX_MINUTE);
    }

public:
    int Hour()
    {
        return hour;
    }
    int Minute()
    {
        return minute;
    }

    string ToString()
    {
        string time = ((Hour() < 10) ? "0" + to_string(Hour()) : to_string(Hour())) + ":" +
            ((Minute() < 10) ? "0" + to_string(Minute()) : to_string(Minute()));

        return time;
    }

    void AskForTime(string userMessage)
    {
        char separator;
        int hour, minute;

        do
        {
            cout << userMessage << " (24-Hour clock, HH:MM): ";

            cin >> hour >> separator >> minute;
            cin.ignore(); // Ignore the enter after the user input.
        } while (!IsValidHour(hour) && !IsValidMinute(minute));

        this->hour = hour;
        this->minute = minute;
    }
};

/*********************************** OVERLOADS FOR TIME *****************************************/
bool operator< (Time& t1, Time& t2)
{
    if (t1.Hour() < t2.Hour())
    {
        return true;
    }
    else if (t1.Hour() == t2.Hour())
    {
        return t1.Minute() < t2.Minute();
    }

    return false;
}

bool operator< (int hour, Time& t2)
{
    return hour < t2.Hour();
}

bool operator< (Time& t1, int hour)
{
    return t1.Hour() < hour;
}

bool operator> (Time& t1, Time& t2)
{
    if (t1.Hour() > t2.Hour())
    {
        return true;
    }
    else if (t1.Hour() == t2.Hour())
    {
        return t1.Minute() > t2.Minute();
    }

    return false;
}

bool operator> (int hour, Time& t2)
{
    return hour > t2.Hour();
}

bool operator> (Time& t1, int hour)
{
    return t1.Hour() > hour;
}

/*********************************** END OVERLOADS FOR TIME *****************************************/

class BusinessTrip
{
private:
    const int MIN_TRIP_LENGTH = 1;
    const int FIRST_DAY_BREAKFAST_CUTOFF = 7;
    const int FIRST_DAY_LUNCH_CUTOFF = 12;
    const int FIRST_DAY_DINNER_CUTOFF = 18;
    const int LAST_DAY_BREAKFAST_CUTOFF = 8;
    const int LAST_DAY_LUNCH_CUTOFF = 13;
    const int LAST_DAY_DINNER_CUTOFF = 19;

    int tripLength{ 0 };
    Time arrivalTime;
    Time departureTime;

public:
    // Getter for TripLength
    int TripLength()
    {
        return tripLength;
    }

    string ArrivalTime()
    {
        return arrivalTime.ToString();
    }

    string DepartureTime()
    {
        return departureTime.ToString();
    }

    int GetTripLength()
    {
        int tripLength;

        do
        {
            cout << "How many days was the trip? ";
            cin >> tripLength;
            cin.ignore();   // Ignore any left over \n

        } while (tripLength < MIN_TRIP_LENGTH);

        this->tripLength = tripLength;

        return TripLength();
    }

    void GetArrivalTime()
    {
        arrivalTime.AskForTime("What time did arrive back from your trip?");
    }

    void GetDepartureTime()
    {
        departureTime.AskForTime("What time did you depart on the trip?");
    }

    bool CanExpenseBreakfast(int dayOfTrip)
    {
        // If not first or last day then can expense any meal
        if (dayOfTrip > 1 && dayOfTrip < TripLength())
        {
            return true;
        }

        if (dayOfTrip == 1)
        {
            return departureTime < FIRST_DAY_BREAKFAST_CUTOFF;
        }

        // Must be last day of trip
        return arrivalTime > LAST_DAY_BREAKFAST_CUTOFF;
    }

    bool CanExpenseLunch(int dayOfTrip)
    {
        // If not first or last day then can expense any meal
        if (dayOfTrip > 1 && dayOfTrip < TripLength())
        {
            return true;
        }

        if (dayOfTrip == 1)
        {
            return departureTime < FIRST_DAY_LUNCH_CUTOFF;
        }

        // Must be last day of trip
        return arrivalTime > LAST_DAY_LUNCH_CUTOFF;
    }

    bool CanExpenseDinner(int dayOfTrip)
    {
        // If not first or last day then can expense any meal
        if (dayOfTrip > 1 && dayOfTrip < TripLength())
        {
            return true;
        }

        if (dayOfTrip == 1)
        {
            return departureTime < FIRST_DAY_DINNER_CUTOFF;
        }

        // Must be last day of trip
        return arrivalTime > LAST_DAY_DINNER_CUTOFF;
    }
};

class BusinessExpenses
{
private:
    double totalExpenses{ 0.00 };       // Total expenses incurred
    double expenseOverage{ 0.00 };      // Amount that exceeded maximum allowed
    double maxAllowed{ 0.00 };          // Total allowed expense amount

    // Returns the dollar amount of an expense
    // - question: The question that asks the user for an amout
    // - minValue: The minimum amount allowed as input
    double AskForExpense(string question, double minValue)
    {
        double cost;

        // Ask the user for an amount until they provide a valid amount
        do
        {
            cout << question << " $";
            cin >> cost;

            cin.ignore(); // Ignore \n
        } while (cost < minValue);

        return cost;
    }
public:
    // Getter for total expenses
    double TotalExpenses()
    {
        return totalExpenses;
    }

    // Getter for expense overage
    double ExpenseOverage()
    {
        return expenseOverage;
    }

    // Getter for max allowed
    double MaxAllowed()
    {
        return maxAllowed;
    }

    void Add(double amount)
    {
        totalExpenses += amount;
        maxAllowed += amount;
    }

    void Add(double amount, double maxExpense)
    {
        totalExpenses += amount;
        maxAllowed += maxExpense;
        if (amount > maxExpense)
        {
            expenseOverage += (amount - maxExpense);
        }
    }

    void Add(string question, double minValue)
    {
        double expense = AskForExpense(question, minValue);
        Add(expense);
    }

    void Add(string question, double minValue, double maxValue)
    {
        double expense = AskForExpense(question, minValue);
        Add(expense, maxValue);
    }

    void AddDailyExpense(string baseQuestion, int numDays, double maxAmount)
    {
        string dailyQuestion;

        for (int i = 1; i <= numDays; i++)
        {
            dailyQuestion = baseQuestion + " for day " + to_string(i);
            // If maxAmount < 0 then there is no max amount
            if (maxAmount < 0)
            {
                Add(dailyQuestion, 0);
            }
            else
            {
                Add(dailyQuestion, 0, maxAmount);
            }
        }
    }
};

class ExpenseReport
{
private:
    const double MILEAGE_RATE = 0.27;
    const double MAX_PARKING_FEE_PER_DAY = 6.00;
    const double MAX_TAXI_FEE_PER_DAY = 10.00;
    const double MAX_HOTEL_FEE_PER_NIGHT = 90.00;
    const double MAX_BREAKFAST_COST = 9.00;
    const double MAX_LUNCH_COST = 12.00;
    const double MAX_DINNER_COST = 16.00;

    BusinessExpenses _expenses;
    BusinessTrip _businessTrip;

    // Returns true if the user enters Y to a Y/N question
    // Input is allowed to be upper or lowercase
    // - question: the yes/no question to ask the user
    bool AskYesNo(string question)
    {
        char response;
        bool invalidResponse = true;
        bool isYes;

        do
        {
            cout << question << " (Y/N): ";
            cin >> response;

            cin.ignore(); // Ignore enter at the end;

            // convert the response to uppercase because answer is case-insensitive
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

    double GetMilesDriven()
    {
        double milesDriven;

        do
        {
            cout << "How many total miles did you drive on this trip? ";
            cin >> milesDriven;
            cin.ignore();
        } while (milesDriven < 0);

        return milesDriven;
    }

    void AddMealExpenses()
    {
        for (int day = 1; day <= _businessTrip.TripLength(); day++)
        {
            cout << "Please enter the amount you spent on meals for day " << day << endl;
            if (_businessTrip.CanExpenseBreakfast(day))
            {
                _expenses.Add("How much did breakfast cost?", 0, MAX_BREAKFAST_COST);
            }
            if (_businessTrip.CanExpenseLunch(day))
            {
                _expenses.Add("How much did lunch cost?", 0, MAX_LUNCH_COST);
            }
            if (_businessTrip.CanExpenseDinner(day))
            {
                _expenses.Add("How much did dinner cost?", 0, MAX_DINNER_COST);
            }
            cout << endl;
        }
    }
public:
    void CollectExpenses()
    {
        _businessTrip.GetTripLength();
        _businessTrip.GetDepartureTime();
        _businessTrip.GetArrivalTime();

        cout << endl;
        // Add vehicle expenses
        if (AskYesNo("Did you use a personal vehicle?"))
        {
            double milesDriven = GetMilesDriven();
            _expenses.Add(milesDriven * MILEAGE_RATE);
        }
        else if (AskYesNo("Did you rent a car?"))
        {
            _expenses.Add("What was your car rental fee?", 0);
        }

        cout << endl;
        //Add taxi expenses
        if (AskYesNo("Did you use a taxi?"))
        {
            _expenses.AddDailyExpense("What was your taxi expense", _businessTrip.TripLength(), MAX_TAXI_FEE_PER_DAY);
        }

        cout << endl;
        // Add flight expense
        if (AskYesNo("Did you take a round trip flight?"))
        {
            _expenses.Add("What was the cost of your flight?", 0);
        }

        cout << endl;
        // Add hotel expenses
        if (AskYesNo("Did you stay at a hotel?"))
        {
            _expenses.AddDailyExpense("What was your hotel fee", _businessTrip.TripLength(), MAX_HOTEL_FEE_PER_NIGHT);
        }

        cout << endl;
        // Add conference fee
        if (AskYesNo("Was there a conference fee?"))
        {
            _expenses.Add("What was the conference fee?", 0);
        }

        cout << endl;
        // Add parking fees
        if (AskYesNo("Did you pay any parking fees?"))
        {
            _expenses.AddDailyExpense("What was your parking fee", 0, MAX_PARKING_FEE_PER_DAY);
        }

        cout << endl;
        // Add meal expenses
        if (AskYesNo("Did you pay for any meals?"))
        {
            AddMealExpenses();
        }
    }

    void Display()
    {
        double totalExpenses = _expenses.TotalExpenses();
        double excessExpenses = _expenses.ExpenseOverage();
        double totalAllowed = _expenses.MaxAllowed();

        cout << setprecision(2) << fixed;
        cout << endl;
        cout << "************************************************\n";
        cout << "                 Expense Report                 \n";
        cout << "------------------------------------------------\n";
        cout << "TOTAL EXPENSES INCURRED: $" << totalExpenses << endl;
        cout << "EXPENSES OVER ALLOWED  : $" << excessExpenses << endl;
        cout << "MAX ALLOWED EXPENSES   : $" << totalAllowed << endl;
        cout << endl;

        // If expenses incurred is greater than reimbursable expenses then company is owed money
        if (totalExpenses < totalAllowed)
        {
            cout << "Thank you! You saved the company $" << (totalAllowed - totalExpenses) << endl;
            if (excessExpenses > 0)
            {
                cout << "Although you saved the company money, you exceeded a daily maximum expense amount.\n";
                cout << "Some expenses have a maximum allowable amount. Try to keep those expenses under the cap.\n";
            }
        }
        else if (totalExpenses > totalAllowed)
        {
            // More was spent then is allowed
            cout << "You exceeded the maximum allowable expenses.\n";
            cout << "Try to be more careful about your expense amounts.\n";
        }

        if (excessExpenses > 0)
        {
            cout << "You need to reimburse the company $" << excessExpenses;
        }
    }
};

// Driver function
void UseClassApproach()
{
    ExpenseReport expenseReport;
    expenseReport.CollectExpenses();    // Collect the expenses
    expenseReport.Display();            // Display the expense report
}