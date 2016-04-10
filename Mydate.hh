#include <iostream>
#include <string>
using std::string;
using std::vector;

struct EventSpec
{
	int day;
	int month;
	int year;
	int weekday;
	string event;
};

class MyDate
{
public:
	int day;
	int month;
	int year;
	int weekday;
	MyDate();
	MyDate(int d,int m,int y);
	// -1 operation on current date
	void minus_one();
	// +1 operation on current date
	void add_one();
	// return current weekday as string
	string get_weekday();
	// check if current date is the last day of the month
	bool check_last();
	// get events of current date
	string get_events(vector<EventSpec> &MyHappenings);
	// print
	void print(vector<EventSpec> &MyHappenings);
};

bool check_input_date(const MyDate& d);

bool is_leap(int y);
