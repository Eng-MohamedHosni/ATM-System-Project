#pragma once
#pragma warning (disable:4996)
#include <iostream>
#include<ctime>
using namespace std;


namespace Mylib
{
	struct stDate
	{
		int Year;
		int Month;
		int Day;
	};
	int ReadNumber(string Message)
	{
		int Number;
		cout << Message<<endl;
		cin >> Number;
		return Number;

	}

	int ReadNumber()
	{
		int Number;

		cin >> Number;
		cout << endl;
		return Number;

	}

	int ReadNumberInRange(int From ,int To)
	{
			int Number;
		do
		{
			cout << "Please enter nubmer from " << From << " to " << To << endl;
			cin >> Number;
			
		} while (Number > To || Number < From);
			return Number;
	}

	int RandomNumberInRange(int From, int To)
	{
		int random = rand() % (To - From + 1) + From;
		return random;
	}


	void ReadNumArray(int Array[100], int &ArrayLength)
	{
		for (int i = 0; i < ArrayLength; i++)
		{
			Array[i] = ReadNumber();
		}
		
	}
	

	void PrintArray(int Array[3], int length)
	{
		for (int i = 0; i < length; i++)
		{
			printf("%0*d   ", 2, Array[i]);
		}
		cout << endl;
	}
	void AddToArray(int Number,int Array[100], int& ArrayLength)
	{
		// you must give the Destination Array length value of 0 at first
		ArrayLength++;
	    Array[ArrayLength - 1] = Number;
	}

	string AllUpperString(string S)
	{
		for (int i = 0; i < S.length(); i++)
		{

			S.at(i) = toupper(S.at(i));

		}
		return S;
	}

	string AllLowerString(string S)
	{
		for (int i = 0; i < S.length(); i++)
		{

			S.at(i) = tolower(S.at(i));

		}
		return S;
	}

	string ReadString()
	{
		string c;
		cout << "Please Enter a string ? \n";
		getline(cin, c);
		return c;
	}
	string ReadString(string Message)
	{
		string c;
		cout << Message<<endl;
		getline(cin>>ws, c);
		return c;
	}

	char ReadChar()
	{
		char c;
		cout << "Please Enter a Character ? \n";
		cin>>c;
		return c;
	}

	


	vector <string> Split(string St, string delimiter="#//#")
	{
		vector <string> Sp;
		short pos = 0;
		string Word;
		while ((pos = St.find(delimiter)) != string::npos)
		{
			Word = St.substr(0, pos);
			if (Word != "")
			{
				Sp.push_back(Word);
			}
			St.erase(0, pos + delimiter.length());
		}
		if (St != "")
			Sp.push_back(St);
		return Sp;
	}


	string  JoinString(vector <string>& vString, string Separator)
	{
		string Str;
		for (string& St : vString)
		{
			Str += St + Separator;

		}

		return Str.substr(0, Str.length() - 1);

	}
	void ResetScreen()
	{
		system("color 0F");
		system("cls");
	}

	
	
	// time 
	bool IsLeepYear(short Year)
	{

		return (Year % 400 == 0 || Year % 4 == 0 && Year % 100 != 0) ? true : false;

	}

	short NumberOfDaysInYear(short Year)
	{
		return (IsLeepYear(Year)) ? 366 : 365;
	}

	int NumberOfDaysInMonth(int Year, int Month)
	{

		int NumberOfDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (IsLeepYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];

	}


	int DaysFromBeginingOfYear(short Year, short Month, short Day)
	{
		short DaysOfLastMonth = 0;
		short TotalDays = 0;
		DaysOfLastMonth = NumberOfDaysInMonth(Year, Month);
		for (short i = 1; i < Month; i++)
		{
			TotalDays += NumberOfDaysInMonth(Year, i);
		}
		if (Day <= DaysOfLastMonth)
		{
			TotalDays += Day;
		}
		else
		{
			cout << "this month is " << DaysOfLastMonth << endl;
		}

		return TotalDays;
	}

	string ReplaceWordInString(string S1, string StringToReplace, string sReplaceTo)
	{
		short pos = S1.find(StringToReplace);

		// Loop to replace all occurrences of the word
		while (pos != std::string::npos)
		{
			S1 = S1.replace(pos, StringToReplace.length(), sReplaceTo);
			pos = S1.find(StringToReplace, pos + sReplaceTo.length()); // find next occurrence
		}

		return S1;
	}

	stDate ReadDate()
	{
		stDate Date;

		Date.Day = ReadNumber("Please enter the Day?");
		Date.Month = ReadNumber("Please enter the Month?");
		Date.Year = ReadNumber("Please enter the year?");
		return Date;

	}

	stDate GetDateFromDateOrderInYear(short TotalDays, short Year)
	{
		stDate Date;

		short RemainingDays = TotalDays;

		Date.Year = Year;

		Date.Month = 1;
		while (true)
		{
			short MonthDays = NumberOfDaysInMonth(Year, Date.Month);

			if (RemainingDays > MonthDays)
			{

				RemainingDays -= NumberOfDaysInMonth(Year, Date.Month);
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

	bool IsDate1EqualDate2(stDate Date1, stDate Date2)
	{
		return ((Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month ? Date1.Day == Date2.Day : false)) : false);


	}
	bool IsDate1BeforeDate2(stDate Date1, stDate Date2)
	{
		return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);



	}

	bool IsDate1AfterDate2(stDate Date1, stDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}

	enum enCompareDate { Before = -1, Equal = 0, After = 1 };
	enCompareDate CompareDate(stDate Date1, stDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enCompareDate::Before;
		if (IsDate1EqualDate2(Date1, Date2))
			return enCompareDate::Equal;

		else
			return enCompareDate::After;

	}


	bool IsLastDayInMonth(stDate Date)
	{

		return (Date.Day == NumberOfDaysInMonth(Date.Year, Date.Month)) ? true : false;
	}


	bool IsLastMonthInYear(stDate Date)
	{
		return (Date.Month == 12);
	}

	stDate DateAfterAddingOneDay(stDate Date)
	{

		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date))
			{
				Date.Year++;
				Date.Month = 1;
				Date.Day = 1;
			}
			else
			{
				Date.Month++;
				Date.Day = 1;
			}
		}
		else
		{
			Date.Day++;
		}

		return Date;
	}

	int DiffDaysBetween2Dates(stDate Date1, stDate Date2, bool EndDay)
	{
		int DiffDays = 0;
		if (IsDate1BeforeDate2(Date1, Date2))
		{
			if (Date1.Year == Date2.Year)
			{
				DiffDays = DaysFromBeginingOfYear(Date2.Year, Date2.Month, Date2.Day) - DaysFromBeginingOfYear(Date1.Year, Date1.Month, Date1.Day);
			}
			else
			{
				DiffDays = DaysFromBeginingOfYear(Date2.Year, Date2.Month, Date2.Day);
				while (Date2.Year-- != Date1.Year)
				{
					DiffDays += NumberOfDaysInYear(Date2.Year);
				}
				while (Date2.Year-- == Date1.Year)
				{
					DiffDays += NumberOfDaysInYear(Date1.Year) - DaysFromBeginingOfYear(Date1.Year, Date1.Month, Date1.Day);

				}
			}
		}
		if (EndDay)
		{
			return DiffDays+1;
		}
		else
			return DiffDays;
	}
	int GetDayOfWeekOrder(stDate Date)
	{
		int a = (14 - Date.Month) / 12;
		int y = Date.Year - a;
		int m = Date.Month + 12 * a - 2;
		int d = (Date.Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
		return d;
	}
	bool IsWeekEnd(stDate Date)
	{
		int DayOrderInWeek = GetDayOfWeekOrder(Date);
		return (DayOrderInWeek == 5 || DayOrderInWeek == 6);
	}
	bool IsBusinessDay(stDate Date)
	{

		return (!IsWeekEnd(Date));
	}

	
	stDate GetSystemDate()
	{
		time_t t = time(0);
		stDate Date;
		tm* nowDate = localtime(&t);
		Date.Year = nowDate->tm_year + 1900;
		Date.Month = nowDate->tm_mon + 1;
		Date.Day = nowDate->tm_mday;
		return Date;
	}

	
	
	string DayShortName(int DayOrder)
	{
		string arrDay[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return arrDay[DayOrder];
	}

	int AcutualVacationDay2(stDate StartDate, stDate EndDate)
	{
		short DaysCount = 0;
		while (IsDate1BeforeDate2(StartDate, EndDate))
		{
			if (IsBusinessDay(StartDate))
			{
				DaysCount++;
			}
			StartDate = DateAfterAddingOneDay(StartDate);

		}
		return DaysCount;
	}

	//Increase date by 
	
}