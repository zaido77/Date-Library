#pragma once

#include <ctime>
#include <cstdio>  // printf
#include <iostream>
#include "Inputs.h"
#include "clsString.h"

class clsDate
{
private:
	short Day;
	short Month;
	short Year;

public:
	clsDate()
	{	
		*this = GetSystemDate();
	}

	clsDate(string DateString)
	{
		*this = StringToDate(DateString);
	}

	clsDate(short Day, short Month, short Year)
	{
		this->Day = Day;
		this->Month = Month;
		this->Year = Year;
	}

	clsDate(short DayOrder, short Year)
	{
		*this = GetDateFromDayOrderInYear(DayOrder, Year);
	}

	short GetDay()
	{
		return Day;
	}
	__declspec(property(get = GetDay)) short Day;

	short GetMonth()
	{
		return Month;
	}
	__declspec(property(get = GetMonth)) short Month;

	short GetYear()
	{
		return Year;
	}
	__declspec(property(get = GetYear)) short Year;

	void Print()
	{
		cout << DateToString() << "\n";
	}

	static bool isLeapYear(short Year)
	{
		return  ((Year % 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0);
	}

	bool isLeapYear()
	{
		return isLeapYear(Year);
	}

	static short NumberOfDaysInYear(short Year)
	{
		return isLeapYear(Year) ? 366 : 365;
	}

	short NumberOfDaysInYear()
	{
		return NumberOfDaysInYear(Year);
	}

	static short NumberOfHoursInYear(short Year)
	{
		return NumberOfDaysInYear(Year) * 24;
	}

	short NumberOfHoursInYear()
	{
		return NumberOfHoursInYear(Year);
	}

	static int NumberOfMinutesInYear(short Year)
	{
		return NumberOfHoursInYear(Year) * 60;
	}

	int NumberOfMinutesInYear()
	{
		return NumberOfMinutesInYear(Year);
	}

	static int NumberOfSecondsInYear(short Year)
	{
		return NumberOfMinutesInYear(Year) * 60;
	}

	int NumberOfSecondsInYear()
	{
		return NumberOfSecondsInYear(Year);
	}

	static short NumberOfDaysInMonth(short Month, short Year)
	{
		if (Month < 1 || Month > 12)
			return 0;

		short NumberOfDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
	}

	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(Month, Year);
	}

	static short NumberOfHoursInMonth(short Month, short Year)
	{
		return NumberOfDaysInMonth(Month, Year) * 24;
	}

	short NumberOfHoursInMonth()
	{
		return NumberOfHoursInMonth(Month, Year);
	}

	static int NumberOfMinutesInMonth(short Month, short Year)
	{
		return NumberOfHoursInMonth(Month, Year) * 60;
	}

	int NumberOfMinutesInMonth()
	{
		return NumberOfMinutesInMonth(Month, Year);
	}

	static int NumberOfSecondsInMonth(short Month, short Year)
	{
		return NumberOfMinutesInMonth(Month, Year) * 60;
	}

	int NumberOfSecondsInMonth()
	{
		return NumberOfSecondsInMonth(Month, Year);
	}

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;

		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;
		// 0:Sun, 1:Mon, 2:Tue, 3:Wed, 4:Thu, 5:Fri, 6:Sat
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	static short DayOfWeekOrder(clsDate Date)
	{
		return DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
	}

	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(*this);
	}

	static string DayShortName(short DayOfWeekOrder)
	{
		string arrDaysNames[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

		return arrDaysNames[DayOfWeekOrder];
	}

	string DayShortName()
	{
		return DayShortName(DayOfWeekOrder(*this));
	}

	static string MonthShortName(short Month)
	{
		string arrMonthsNames[] = {
			"Jan", "Feb", "Mar", "Apr", "May", "Jun",
			"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
		};

		return arrMonthsNames[Month - 1];
	}

	string MonthShortName()
	{
		return MonthShortName(Month);
	}

	static void PrintMonthCalendar(short Month, short Year)
	{
		short DayOneOrder = DayOfWeekOrder(1, Month, Year);
		short NumberOfDays = NumberOfDaysInMonth(Month, Year);

		printf("\n  ______________%s________________\n\n", MonthShortName(Month).c_str());
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		short i;
		for (i = 0; i < DayOneOrder; i++)
			printf("     ");

		for (short j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}
		}

		printf("\n  _________________________________\n");
	}

	void PrintMonthCalendar()
	{
		PrintMonthCalendar(Month, Year);
	}

	static void PrintYearCalendar(short Year)
	{
		printf("\n  _________________________________\n\n");
		printf("          Calendar - %d\n", Year);
		printf("  _________________________________\n");

		for (short i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, Year);
		}
	}

	void PrintYearCalendar()
	{
		PrintYearCalendar(Year);
	}

	static short TotalDaysFromBeginningOfYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;

		for (short i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInMonth(i, Year);
		}

		TotalDays += Day;

		return TotalDays;
	}

	static short TotalDaysFromBeginningOfYear(clsDate Date)
	{
		return TotalDaysFromBeginningOfYear(Date.Day, Date.Month, Date.Year);
	}

	short TotalDaysFromBeginningOfYear()
	{
		return TotalDaysFromBeginningOfYear(*this);
	}

	static clsDate GetDateFromDayOrderInYear(short DayOrder, short Year)
	{
		clsDate Date(0, 0, 0);
		short RemainingDays = DayOrder;
		short MonthDays = 0;

		Date.Year = Year;
		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Date.Month, Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	void SetToDayOrderInYear(short DayOrder)
	{
		*this = GetDateFromDayOrderInYear(DayOrder, Year);
	}

	static clsDate GetDateAfterAddingDays(short DaysToAdd, clsDate Date)
	{
		short RemainingDays = DaysToAdd + TotalDaysFromBeginningOfYear(Date.Day, Date.Month, Date.Year);
		short MonthDays = 0;

		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Date.Month, Date.Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;

				if (Date.Month > 12)
				{
					Date.Month = 1;
					Date.Year++;
				}
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}

		return Date;
	}

	void AddDays(short DaysToAdd)
	{
		*this = GetDateAfterAddingDays(DaysToAdd, *this);
	}

	static clsDate ReadDate()
	{
		clsDate Date;

		Date.Day = Inputs::ReadNumber("Enter Day : ");
		Date.Month = Inputs::ReadNumber("Enter Month: ");
		Date.Year = Inputs::ReadNumber("Enter Year : ");

		return Date;
	}

	void Read()
	{
		*this = ReadDate();
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year < Date2.Year) ? true : ((Date1.Year ==
			Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month ==
				Date2.Month ? Date1.Day < Date2.Day : false)) : false);

		/*if (Date1.Year < Date2.Year)
			return true;
		else if (Date1.Year == Date2.Year)
		{
			if (Date1.Month < Date2.Month)
				return true;
			else if (Date1.Month == Date2.Month)
				return Date1.Day < Date2.Day;
			else
				return false;
		}
		else
			return false;*/
	}

	bool IsBefore(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year == Date2.Year) && (Date1.Month == Date2.Month) && (Date1.Day == Date2.Day);
		//return (Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
	}

	bool IsEqual(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return !IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2);
	}

	bool IsAfter(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	//--------------STOPPED HERE---------------
	static bool IsLastDayInMonth(clsDate Date)
	{
		return Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year);
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return Month == 12;
	}

	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(Month);
	}

	static clsDate IncreaseDateByOneDay(clsDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Day = 1;
				Date.Month = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}
		else
		{
			Date.Day++;
		}

		return Date;
	}

	void IncreaseDateByOneDay()
	{
		*this = IncreaseDateByOneDay(*this);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;

		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}

	void SwapDates(clsDate& Date2)
	{
		SwapDates(*this, Date2);
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		short SwapFlagValue = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}

		int Days = 0;

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}

		return (IncludeEndDay ? ++Days : Days) * SwapFlagValue;
	}

	int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}

	static clsDate GetSystemDate()
	{
		clsDate DateNow(0, 0, 0);

		time_t t = time(0);
		tm* now = localtime(&t);

		DateNow.Day = now->tm_mday;
		DateNow.Month = now->tm_mon + 1;
		DateNow.Year = now->tm_year + 1900;

		return DateNow;
	}

	static string GetSystemTime()
	{
		clsDate DateNow;

		time_t t = time(0);
		tm* now = localtime(&t);

		int Hour = now->tm_hour;
		int Minute = now->tm_min;

		string AMorPM = (Hour >= 12) ? "PM" : "AM";
		string HourStr = (Hour == 0) ? "12" : (Hour > 12 ? to_string(Hour - 12) : to_string(Hour));
		string MinuteStr = (Minute < 10) ? ("0" + to_string(Minute)) : to_string(Minute);

		return HourStr + ":" + MinuteStr + ' ' + AMorPM;
	}

	clsDate IncreaseDateByXDays(short Days, clsDate Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;
	}

	clsDate IncreaseDateByOneWeek(clsDate Date)
	{
		//return IncreaseDateByXDays(7, Date);	

		for (short i = 1; i <= 7; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;
	}

	clsDate IncreaseDateByXWeeks(short Weeks, clsDate Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;
	}

	clsDate IncreaseDateByOneMonth(clsDate Date)
	{
		// (Date.Month == 12)
		if (IsLastMonthInYear(Date.Month))
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Month++;
		}

		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}

	clsDate IncreaseDateByXMonths(short Months, clsDate Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}

	clsDate IncreaseDateByOneYear(clsDate Date)
	{
		//Date = IncreaseDateByXMonths(12, Date);

		Date.Year++;

		/*short MonthDays = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > MonthDays)
			Date.Day = MonthDays;*/


		return Date;
	}

	clsDate IncreaseDateByXYears(short Years, clsDate Date)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}

	clsDate IncreaseDateByXYearsFaster(short Years, clsDate Date)
	{
		Date.Year += Years;

		return Date;
	}

	clsDate IncreaseDateByOneDecade(clsDate Date)
	{
		//Date = IncreaseDateByXYears(10, Date);

		Date.Year += 10;

		return Date;
	}

	clsDate IncreaseDateByXDecades(short Decades, clsDate Date)
	{
		/*for (short i = 1; i <= Decades; i++)
		{
			Date = IncreaseDateByOneDecade(Date);
		}*/

		for (short i = 1; i <= Decades * 10; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}

	clsDate IncreaseDateByXDecadesFaster(short Decades, clsDate Date)
	{
		Date.Year += Decades * 10;

		return Date;
	}

	clsDate IncreaseDateByOneCentury(clsDate Date)
	{
		//Date = IncreaseDateByXDecadesFaster(10, Date);

		Date.Year += 100;

		return Date;
	}

	clsDate IncreaseDateByOneMillennium(clsDate Date)
	{

		//Date = IncreaseDateByXDecadesFaster(100, Date);

		/*for (short i = 1; i <= 10; i++)
		{
			Date = IncreaseDateByOneCentury(Date);
		}*/

		Date.Year += 1000;

		return Date;
	}

	clsDate DecreaseDateByOneDay(clsDate Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Day = 31;
				Date.Month = 12;
				Date.Year--;
			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
			}
		}
		else
		{
			Date.Day--;
		}

		return Date;
	}

	clsDate DecreaseDateByXDays(short Days, clsDate Date)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	clsDate DecreaseDateByOneWeek(clsDate Date)
	{
		//Date = DecreaseDateByXDays(7, Date);	

		for (short i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}

	clsDate DecreaseDateByXWeeks(short Weeks, clsDate Date)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}

		return Date;
	}

	clsDate DecreaseDateByOneMonth(clsDate Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
		{
			Date.Month--;
		}

		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}

	clsDate DecreaseDateByXMonths(short Months, clsDate Date)
	{
		for (short i = 1; i <= Months; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}

		return Date;
	}

	clsDate DecreaseDateByOneYear(clsDate Date)
	{
		//Date = DecreaseDateByXMonths(12, Date);

		Date.Year--;

		/*short MonthDays = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > MonthDays)
			Date.Day = MonthDays;*/


		return Date;
	}

	clsDate DecreaseDateByXYears(short Years, clsDate Date)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}

	clsDate DecreaseDateByXYearsFaster(short Years, clsDate Date)
	{
		Date.Year -= Years;

		return Date;
	}

	clsDate DecreaseDateByOneDecade(clsDate Date)
	{
		//Date = DecreaseDateByXYears(10, Date);

		Date.Year -= 10;

		return Date;
	}

	clsDate DecreaseDateByXDecades(short Decades, clsDate Date)
	{
		/*for (short i = 1; i <= Decades; i++)
		{
			Date = DecreaseDateByOneDecade(Date);
		}*/

		for (short i = 1; i <= Decades * 10; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}

	clsDate DecreaseDateByXDecadesFaster(short Decades, clsDate Date)
	{
		Date.Year -= Decades * 10;

		return Date;
	}

	clsDate DecreaseDateByOneCentury(clsDate Date)
	{
		//Date = DecreaseDateByXDecadesFaster(10, Date);

		Date.Year -= 100;

		return Date;
	}

	clsDate DecreaseDateByOneMillennium(clsDate Date)
	{

		//Date = DecreaseDateByXDecadesFaster(100, Date);

		/*for (short i = 1; i <= 10; i++)
		{
			Date = DecreaseDateByOneCentury(Date);
		}*/

		Date.Year -= 1000;

		return Date;
	}

	static bool IsEndOfWeek(clsDate Date)
	{
		return DayOfWeekOrder(Date) == 6;
	}

	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date)
	{
		short DayOrder = DayOfWeekOrder(Date);

		return (DayOrder == 5) || (DayOrder == 6);
	}

	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekEnd(Date);

		//short DayOrder = DayOfWeekOrder(Date);
		//return (DayOrder >= 0 && DayOrder <= 4);
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date);
	}

	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date)
	{
		clsDate EndOfMonthDate;

		EndOfMonthDate.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
		EndOfMonthDate.Month = Date.Month;
		EndOfMonthDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfMonthDate, true);

		//return NumberOfDaysInMonth(Date.Month, Date.Year) - Date.Day;
	}

	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date)
	{
		clsDate EndOfYearDate;

		EndOfYearDate.Day = 31;
		EndOfYearDate.Month = 12;
		EndOfYearDate.Year = Date.Year;

		return GetDifferenceInDays(Date, EndOfYearDate, true);

		//return NumberOfDaysInYear(Date.Year) - TotalDaysFromBeginningOfYear(Date);
	}

	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}

	static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo)
	{
		short DaysCount = 0;

		while (IsDate1BeforeDate2(DateFrom, DateTo))
		{
			if (IsBusinessDay(DateFrom))
				DaysCount++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return DaysCount;
	}

	short CalculateVacationDays(clsDate DateTo)
	{
		return CalculateVacationDays(*this, DateTo);
	}

	static clsDate VacationReturnDate(clsDate DateFrom, short VacationDays)
	{
		//while (VacationDays > 0)
		//{
		//	if (IsBusinessDay(DateFrom))
		//		VacationDays--;
		//
		//	DateFrom = IncreaseDateByOneDay(DateFrom);
		//}
		//
		//while (IsWeekEnd(DateFrom))
		//	DateFrom = IncreaseDateByOneDay(DateFrom);
		//
		//return DateFrom;

		while (IsWeekEnd(DateFrom))
			DateFrom = IncreaseDateByOneDay(DateFrom);

		short WeekEndDaysCount = 0;
		for (short i = 1; i <= VacationDays + WeekEndDaysCount; i++)
		{
			if (IsWeekEnd(DateFrom))
				WeekEndDaysCount++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		while (IsWeekEnd(DateFrom))
			DateFrom = IncreaseDateByOneDay(DateFrom);

		return DateFrom;
	}

	clsDate VacationReturnDate(short VacationDays)
	{
		return VacationReturnDate(*this, VacationDays);
	}

	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;

		//if (IsDate1AfterDate2(Date1, Date2))
		//	return enDatesCompare::After;

		return enDateCompare::After;
	}

	enDateCompare CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}

	static bool IsValidDate(clsDate Date)
	{
		return (Date.Year >= 1) &&
			(Date.Month >= 1 && Date.Month <= 12) &&
			(Date.Day >= 1 && Date.Day <= NumberOfDaysInMonth(Date.Month, Date.Year));
	}

	bool IsValidDate()
	{
		return IsValidDate(*this);
	}

	static clsDate StringToDate(string DateString)
	{
		clsDate Date(0, 0, 0);

		vector<string> vDate = clsString::Split(DateString, "/");

		Date.Day = stoi(vDate[0]);
		Date.Month = stoi(vDate[1]);
		Date.Year = stoi(vDate[2]);

		return Date;
	}

	static string DateToString(clsDate Date)
	{
		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}

	string DateToString()
	{
		return DateToString(*this);
	}

	static string FormatDate(clsDate Date, string DateFormat = "dd/mm/yyyy")
	{
		string FormattedDateString = "";

		FormattedDateString = clsString::ReplaceSubStrings(DateFormat, "dd", to_string(Date.Day));
		FormattedDateString = clsString::ReplaceSubStrings(FormattedDateString, "mm", to_string(Date.Month));
		FormattedDateString = clsString::ReplaceSubStrings(FormattedDateString, "yyyy", to_string(Date.Year));

		return FormattedDateString;
	}

};

