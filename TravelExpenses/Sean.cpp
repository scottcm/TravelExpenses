#include "TravelExpenses.h"

// Add flight expense
void AddFlightExpense()
{
    double roundTripFare;
    //Ask for the amount of round trip airfare.
    roundTripFare = GetExpenseAmount("What was the cost of the airfare?", 0);
    //Take amount and add to expenses.
    AddExpense(roundTripFare);
}

// Add car rental expense
void AddCarRentalExpense()
{
    double rentalCost;
    //Ask for total amount of car rentals.
    rentalCost = GetExpenseAmount("What was the total cost of car rentals?", 0);
    //Take total amount and add to expenses.
    AddExpense(rentalCost);
}

// Add mileage expense
// - mileageRate: The mileage reimbursement rate
void AddMileageExpense(double mileageRate)
{
    double milesDriven;
    double mileageCost;
      do
    {   //Ask for miles driven.
        cout << "What was the total miles driven for the trip?\n";
        cin >> milesDriven;
        cin.ignore();
    } while (milesDriven < 0); 
    //Calculate cost with mileageRate.
    mileageCost = milesDriven * mileageRate;
    //Add amount to expenses.
    AddExpense(mileageCost);
}

// Add parking expense
// - tripLength: Length of the trip in days
// - maxParkingFee: The maximum per day parking fee
void AddParkingFees(int tripLength, double maxParkingFee)
{
    double dailyFee;
    //ask for fee per day, from day 1 to tripLength.
    for (int dayNumber = 1; dayNumber <= tripLength; dayNumber++)
    {
        dailyFee = GetExpenseAmount("What was the parking fee for day" + to_string(dayNumber) + "?", 0);
        //Take amount and add to expenses.
        AddExpense(dailyFee, maxParkingFee);
    }

}

// Add taxi expense
// - tripLength: Length of the trip in days
// - maxTaxiFee: The maximum per day taxi fee
void AddTaxiFees(int tripLength, double maxTaxiFee)
{
    double dailyFee;
    //ask for fee per day, from day 1 to tripLength.
    for (int dayNumber = 1; dayNumber <= tripLength; dayNumber++)
    {
        dailyFee = GetExpenseAmount("What was the taxi fee for day" + to_string(dayNumber) + "?", 0);
        //Take amount and add to expenses.
        AddExpense(dailyFee, maxTaxiFee);
    }
}

// Add conference expense
void AddConferenceFee()
{
    double conferenceCost;
    //Ask for total amount of conference and seminar fees.
    conferenceCost = GetExpenseAmount("What was the total cost of conference and seminar fees?", 0);
    //Take total amount and add to expenses.
    AddExpense(conferenceCost);
}

// Add hotel expense
// - tripLength: Length of the trip in days
// - maxHotelFee: max per night hotel fee
void AddHotelExpense(int tripLength, double maxHotelFee)
{
    double dailyHotel;
    //ask for fee per day, from day 1 to tripLength.
    for (int dayNumber = 1; dayNumber <= tripLength; dayNumber++)
    {
        dailyHotel = GetExpenseAmount("What was the hotel fee for day" + to_string(dayNumber) + "?", 0);
        //Take amount and add to expenses.
        AddExpense(dailyHotel, maxHotelFee);
    }
   
}