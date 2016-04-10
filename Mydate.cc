#include <iostream>
#include <string>
#include <vector>
#include "Mydate.hh"
using std::string;
using std::vector;
using std::endl;
using std::cout;

// Default constructor
MyDate::MyDate():day(1),month(1),year(1754),weekday(-1){}

// Constructor
MyDate::MyDate(int d,int m,int y):day(d),month(m),year(y)
{
	int days=0;
	if(this->year>1754)
	{
		for(int i=1754;i<this->year;i++)
		{
			if(is_leap(i)) days+=366;
			else days+=365;
		}
	}

	if(this->month>1)
	{
		for(int i=1;i<this->month;i++)
		{
			if(i==1 or i==3 or i==5 or i==7 or i==8 or i==10 or i==12)
			{
				days+=31;
			}
			else if(i==4 or i==6 or i==9 or i==11)
			{
				days+=30;
			}
			else // deal with February
			{
				if(is_leap(this->year)) days+=29;
				else days+=28;
			}
		}
	}

	days+=(this->day-1);
	switch(days%7)
	{
	case 0:
		this->weekday = 2;
		break;
	case 1:
		this->weekday = 3;
		break;
	case 2:
		this->weekday = 4;
		break;
	case 3:
		this->weekday = 5;
		break;
	case 4:
		this->weekday = 6;
		break;
	case 5:
		this->weekday = 7;
		break;
	case 6:
		this->weekday = 1;
		break;
	}
}

void MyDate::minus_one()
{
	if(this->weekday==1) this->weekday=7;
	else this->weekday--;
	//
	if(this->day==1)
	{
		// 1.1 change year
		if(this->month==1)
		{
			this->year--;
			this->month=12;
			this->day=31;
			return;
		}
		// 3.1 February situations, leap year or not
		if(this->month==3)
		{
			if(is_leap(this->year)) this->day = 29;
			else this->day = 28;
			this->month--;
			return;
		}
		// 2,6,8,9,11 change to 31
		if(this->month==2 or this->month==6 or this->month==8 or
				this->month==9 or this->month==11)
		{
			this->month--;
			this->day=31;
			return;
		}
		// 5,7,10,
		if(this->month==5 or this->month==7 or this->month==10)
		{
			this->month--;
			this->day=30;
			return;
		}
	}
	// just minus 1 day
	else
	{
		this->day--;
	}
}

void MyDate::add_one()
{
	if(((this->month==1 or
			this->month==3 or
			this->month==5 or
			this->month==7 or
			this->month==8 or
			this->month==10) and this->day==31) or
		   ((this->month==4 or
				   this->month==6 or
				   this->month==9 or
				   this->month==11) and this->day==30) or
			 (this->month==2 and this->day==28 and !is_leap(this->year)) or
			 (this->month==2 and this->day==29 and is_leap(this->year)))
		{
			this->day = 1;
			++this->month;
		}
		else if(this->month==12 and this->day==31)
		{
			this->day = 1;
			this->month = 1;
			++this->year;
		}
		else
		{
			++this->day;
		}
	if(this->weekday==7) this->weekday=1;
	else this->weekday+=1;
}

string MyDate::get_weekday()
{
	switch(this->weekday)
	{
	case 1:
		return "[Mon]";
	case 2:
		return "[Tue]";
	case 3:
		return "[Wed]";
	case 4:
		return "[Thu]";
	case 5:
		return "[Fri]";
	case 6:
		return "[Sat]";
	case 7:
		return "[Sun]";
	default:
		return "Error";
	}
}

bool MyDate::check_last()
{
	if(this->day==31 and (this->month==1 or this->month==3
			or this->month==5 or this->month==7 or this->month==8
			or this->month==10 or this->month==12))
	{
		return true;
	}
	if(this->day==30 and(this->month==4 or this->month==6
			or this->month==9 or this->month==11))
	{
		return true;
	}
	if(this->month==2 and (this->day==29 or (this->day==28 and !is_leap(this->year))))
	{
		return true;
	}
	return false;
}

string MyDate::get_events(vector<EventSpec> &MyHappenings)
{
	string events;
	int count=0;
	for(unsigned long i=0;i<MyHappenings.size();i++)
	{
		if(MyHappenings[i].day==0 or MyHappenings[i].day==this->day or (check_last() and MyHappenings[i].day==-1))
		{
			if(MyHappenings[i].month==0 or MyHappenings[i].month==this->month)
			{
				if(MyHappenings[i].year==0 or MyHappenings[i].year==this->year)
				{
					if(MyHappenings[i].weekday==0 or MyHappenings[i].weekday==this->weekday)
					{
						if(count>0) events += ", "+MyHappenings[i].event;
						else events += MyHappenings[i].event;
						count++;
					}
				}
			}
		}
	}
	if(events=="") events="-";
	return events;
}

void MyDate::print(vector<EventSpec> &MyHappenings)
{
	cout<<this->day<<"."<<this->month<<"."<<this->year<<" "<<this->get_weekday()<<" "<<this->get_events(MyHappenings)<<endl;
}

bool is_leap(int y)
{
	if(y%400==0)
	{
		return true;
	}
	else if(y%100==0)
	{
		return false;
	}
	else if(y%4==0)
	{
		return true;
	}
	else
		return false;
}

bool check_input_date(const MyDate& d)
{
	if(d.month<=12 and d.month>=1)
	{
		if(((d.month==1 or
				d.month==3 or
				d.month==5 or
				d.month==7 or
				d.month==8 or
				d.month==10 or
				d.month==12) and d.day>31) or
					((d.month==4 or
							d.month==6 or
							d.month==9 or
							d.month==11) and d.day>30) or
					(d.month==2 and d.day>28 and !is_leap(d.year)) or
					(d.month==2 and d.day>29 and is_leap(d.year)))
				{
					return false;
				}
	}
	else
	{
		return false;
	}
	return true;
}
