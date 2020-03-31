#include "TravelExpenses.h"

void AddFlightExpense()
{
    cout << "FUNCTION: AddFlightExpense - no input args\n";
}
void AddCarRentalExpense()
{
    cout << "FUNCTION: AddCarRentalExpense - no input args\n";
}
void AddMileageExpense(double mileageRate)
{
    cout << "FUNCTION: AddMileageExpense - " << "mileageRate = " << mileageRate << endl;
}
void AddParkingFees(int tripLength, double maxPerDay)
{
    cout << "FUNCTION: AddParkingFees - " << "tripLength = " << tripLength << endl <<
        "maxPerDay = " << maxPerDay << endl;
    double dailyFee;
  //ask for fee per day, from day 1 to tripLength.
    for (int dayNumber = 1; dayNumber <= tripLength; dayNumber++)
    {
        //Take amount and add to expenses.
        dailyFee = GetExpenseAmount("What was the parking fee for today?", 0);
        AddExpense(dailyFee, maxPerDay);
    }

}
void AddTaxiFees(int tripLength, double maxPerDay)
{
    cout << "FUNCTION: AddTaxiFees - " << "tripLength = " << tripLength << endl <<
        "maxPerDay = " << maxPerDay << endl;
}
void AddConferenceFee()
{
    cout << "FUNCTION: AddConferenceFee - no input args\n";
}
void AddHotelExpense(int tripLength, double maxPerNight)
{
    cout << "FUNCTION: AddHotelExpense - " << "tripLength = " << tripLength << endl <<
        "maxPerNight = " << maxPerNight << endl;
}

void TestSeanParts()
{
    ResetGlobalValues();
    //AddFlightExpense();
    //AddCarRentalExpense();
    //AddMileageExpense(double mileageRate);
    //AddParkingFees(int days, double maxPerDay);
    AddParkingFees(int days, double maxPerDay);
    //AddTaxiFees(int days, double maxPerDay);
    //AddConferenceFee();
    //AddHotelExpense(int days, double maxPerNight);
    ResetGlobalValues();
}