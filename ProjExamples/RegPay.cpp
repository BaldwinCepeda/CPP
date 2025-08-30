// Compute regular payments on a loan (project example)
//
// Formula used:
//
//               interestRate * (Principal / PayPerYear)
// Payments =  ---------------------------------------------
//             1 - ( (1 + (interestRate / PayPerYear))^(-PayPerYear * NumYears) )
//
// Goal of the program:
// To calculate regular loan payments. This example is useful because it
// demonstrates the use of multiple data types and functions from the <cmath> library.

//I'll try to keep my comments at the top of this short programm since I believe the code should be self explanatory and given variable names and programm flow anyone should be able to determine what the program is doing otherwise it means I have not done my best job. Note I know there's a better way of getting user input but I doing it this way for the sake of the example.

#include <iostream>
#include <cmath> 

using namespace std;

int main(){

double Principal, IntRate, PayPerYear, NumYears,Payment;
double numer, denom;
double b, e; //base and exponents for call to std::pow()

std::cout << "Enter the Principal:";
std::cin >> Principal;

std::cout << "Enter the interest rate: ";
std::cin >> IntRate;

std::cout << "Enter number of payments per year: ";
std::cin >> PayPerYear;

std::cout << "Enter the number of years: ";
std::cin >> NumYears;

//Financial Calculation 

numer = (IntRate * Principal) / PayPerYear;

e = -(PayPerYear * NumYears);
b = (IntRate / PayPerYear) + 1;

denom = 1 - std::pow(b,e);

Payment = numer / denom;

std::cout << "Payment is: " << Payment;


    
    
    
    
    
return 0;
}
