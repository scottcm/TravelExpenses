#include "TravelExpenses.h"

// Returns the length of the trip in days
// Return value must be >= MIN_TRIP_LENGTH
int GetLengthOfTrip()
{
    int lengthOfTrip;

    do
    {
        cout << "How many days was the trip? ";
        cin >> lengthOfTrip;
        cin.ignore();   // Ignore any left over \n

    } while (lengthOfTrip < MIN_TRIP_LENGTH);

    return lengthOfTrip;
}

/********************* TIME FUNCTIONS **********************/
// Returns true if MIN_HOUR <= hour < MAX_HOUR, otherwise false
bool IsValidHour(int hour)
{
    return (hour >= MIN_HOUR && hour < MAX_HOUR);
}

// Returns true if MIN_MINUTE <= minute < MAX_MINUTE, otherwise false
bool IsValidMinute(int minute)
{
    return (minute >= MIN_MINUTE && minute < MAX_MINUTE);
}

// Assigns user entered time to the time argument
// string question: Text that is displayed to the user to ask for a time
// int* time: a reference argument that is assigned a 2 element time array
void GetTime(string question, int* time)
{
    char separator;
    int hour, minute;

    do
    {
        cout << question << " (24-Hour clock, HH:MM): ";
        cin >> hour >> separator >> minute;
        cin.ignore(); // Ignore the enter after the user input.
    } while (!IsValidHour(hour) || !IsValidMinute(minute));

    time[HOURS] = hour;
    time[MINUTES] = minute;
}

// Returns true if time t1 is before time t2
bool IsTimeBefore(int t1[], int t2[], int size)
{
    if (size != TIME_SIZE)
    {
        return false;
    }

    if (t1[HOURS] < t2[HOURS])
    {
        return true;
    }
    else if (t1[HOURS] == t2[HOURS])
    {
        return (t1[MINUTES] < t2[MINUTES]);
    }

    return false;
}

// Returns true if time t1 is after time t2, otherwise false
bool IsTimeAfter(int t1[], int t2[], int size)
{
    if (size != TIME_SIZE)
    {
        return false;
    }

    if (t1[HOURS] > t2[HOURS])
    {
        return true;
    }
    else if (t1[HOURS] == t2[HOURS])
    {
        return (t1[MINUTES] > t2[MINUTES]);
    }

    return false;
}

// Returns a time array as a 24-hour clock string in format HH:MM
string ToTimeString(int time[], int size)
{
    string timeString;
    if (size != TIME_SIZE)
    {
        timeString = "";
    }
    else
    {
        timeString = (((time[HOURS] < 10) ? "0" : "") + to_string(time[HOURS]) + ":" +
            ((time[MINUTES] < 10) ? "0" : "") + to_string(time[MINUTES]));
    }

    return timeString;
}
/********************* END TIME FUNCTIONS **********************/

/********************* HELPER FUNCTIONS **********************/
// Returns true if the user enters Y to a Y/N question
// Input is allowed to be upper or lowercase
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

// Returns the dollar amount of an expense
// Outputs the question
// Dollar amount inputted must >= minValue
double GetExpenseAmount(string question, double minValue)
{
    double cost;
    do
    {
        cout << question << " $";
        cin >> cost;

        cin.ignore(); // Ignore \n
    } while (cost < minValue);

    return cost;
}