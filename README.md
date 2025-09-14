# Date Library

`clsDate` is a comprehensive, header-only C++ library for working with dates and times.  
It extends beyond the standard `<ctime>` utilities by providing a powerful and intuitive API for manipulating, formatting, comparing, and validating dates.  

It supports operations like adding or subtracting days, weeks, months, years, handling leap years, generating calendars, calculating business days, and much more.

---

## How to Use

Simply include the `clsDate.h` header file in your project.  
You can then use the functionality through the `clsDate` class directly, which offers both **static utility methods** and **object-oriented instance methods**.

---

## Example

```cpp
#include <iostream>
#include "clsDate.h"

int main()
{
    // --- Create Dates ---
    clsDate today; // defaults to system date
    clsDate customDate(14, 9, 2025); // day, month, year
    clsDate fromString("01/01/2024");

    // --- Print Dates ---
    today.Print();          // e.g., "14/9/2025"
    std::cout << customDate.DateToString() << std::endl; 
    // Output: 14/9/2025

    // --- Date Comparisons ---
    if (customDate.IsBefore(today))
        std::cout << "Custom date is before today.\n";

    // --- Increase / Decrease Dates ---
    clsDate nextWeek = today.IncreaseDateByOneWeek(today);
    std::cout << "One week later: " << nextWeek.DateToString() << std::endl;

    clsDate lastMonth = today.DecreaseDateByOneMonth(today);
    std::cout << "One month earlier: " << lastMonth.DateToString() << std::endl;

    // --- Calendars ---
    clsDate::PrintMonthCalendar(9, 2025);  // September 2025
    today.PrintYearCalendar();             // Calendar for current year

    // --- Business Days & Vacations ---
    clsDate startDate(1, 7, 2025);
    clsDate endDate(10, 7, 2025);

    std::cout << "Business days in range: "
              << clsDate::CalculateVacationDays(startDate, endDate)
              << std::endl;

    clsDate returnDate = startDate.VacationReturnDate(7);
    std::cout << "Vacation return date: " << returnDate.DateToString() << std::endl;

    // --- System Date and Time ---
    clsDate systemDate = clsDate::GetSystemDate();
    std::cout << "System date: " << systemDate.DateToString() << std::endl;
    std::cout << "System time: " << clsDate::GetSystemTime() << std::endl;

    return 0;
}
