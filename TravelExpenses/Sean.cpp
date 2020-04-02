#include "TravelExpenses.h"

void AddFlightExpense()
{
    double roundTripFare;
    //Ask for the amount of round trip airfare.
    //Take amount and add to expenses.
    roundTripFare = GetExpenseAmount("What was the cost of the airfare?",0);
    AddExpense(roundTripFare);
}
void AddCarRentalExpense()
{
    double rentalCost;
    //Ask for total amount of car rentals.
    //Take total amount and add to expenses.
    rentalCost = GetExpenseAmount("What was the total cost of car rentals?", 0);
    AddExpense(rentalCost);
}
void AddMileageExpense(double MILEAGE_RATE)
{
    double milesDriven;
    double mileageCost;
      //Ask for miles driven.
    do
    {
        cout << "What was the total miles driven for the trip?\n";
        cin >> milesDriven;
        cin.ignore();
        //Calculate cost with mileageRate.
        mileageCost = milesDriven * MILEAGE_RATE;
    } while (milesDriven < 0); 
    //Add amount to expenses.
    AddExpense(mileageCost);
}
void AddParkingFees(int tripLength, double MAX_PARKING_FEE_PER_DAY)
{
    double dailyFee;
  //ask for fee per day, from day 1 to tripLength.
    for (int dayNumber = 1; dayNumber <= tripLength; dayNumber++)
    {
        cout << "Please enter the amount you spent on parking fees for day " << dayNumber << endl;
        //Take amount and add to expenses.
        dailyFee = GetExpenseAmount("What was the parking fee for today?", 0);
        AddExpense(dailyFee, MAX_PARKING_FEE_PER_DAY);
    }

}
void AddTaxiFees(int tripLength, double MAX_TAXI_FEE_PER_DAY)
{
    double dailyFee;
    //ask for fee per day, from day 1 to tripLength.
    for (int dayNumber = 1; dayNumber <= tripLength; dayNumber++)
    {
        cout << "Please enter the amount you spent on taxi fees for day " << dayNumber << endl;
        //Take amount and add to expenses.
        dailyFee = GetExpenseAmount("What was the taxi fee for today?", 0);
        AddExpense(dailyFee, MAX_TAXI_FEE_PER_DAY);
    }
}
void AddConferenceFee()
{
    double conferenceCost;
    //Ask for total amount of conference and seminar fees.
    //Take total amount and add to expenses.
    conferenceCost = GetExpenseAmount("What was the total cost of conference and seminar fees?", 0);
    AddExpense(conferenceCost);
}
void AddHotelExpense(int tripLength, double MAX_HOTEL_FEE_PER_NIGHT)
{
    double dailyHotel;
    //ask for fee per day, from day 1 to tripLength.
    for (int dayNumber = 1; dayNumber <= tripLength; dayNumber++)
    {
        cout << "Please enter the amount you spent on hotels for day " << dayNumber << endl;
        //Take amount and add to expenses.
        dailyHotel = GetExpenseAmount("What was the hotel expense for today?", 0);
        AddExpense(dailyHotel, MAX_HOTEL_FEE_PER_NIGHT);
    }
   
}

void TestSeanParts()
{
    ResetGlobalValues();
    //AddFlightExpense();
    //AddCarRentalExpense();
    //AddMileageExpense(MILEAGE_RATE);
    //AddParkingFees(3, MAX_PARKING_FEE_PER_DAY);
    //AddTaxiFees(3, MAX_TAXI_FEE_PER_DAY);
    //AddConferenceFee();
    //AddHotelExpense(3, MAX_HOTEL_FEE_PER_NIGHT);
    ShowExpenses();
    ResetGlobalValues();
}