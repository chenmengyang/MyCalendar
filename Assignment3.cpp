#include <iostream>
#include <vector>
#include "Mydate.hh"
using namespace std;

int main()
{
	vector<EventSpec> MyHappenings1;
	readfile("Events.dat",MyHappenings1);

	int day;
	int month;
	int year;

	cout<<"Give date(day month year):";
	cin>>day;
	cin>>month>>year;
	if(!cin)
	{
		cout<<"Error input, please input integer!"<<endl;
		return 0;
	}
	MyDate date = MyDate(day,month,year);
	int w = date.weekday;
	// minus the date to the first day of the week
	if(check_input_date(date))
	{
		for(int i=1;i<w;i++)
		{
			date.minus_one();
		}
	}
	else
	{
		cout<<"Input date incorrect!"<<endl;
	}
	// output every day and event of the current week
	for(int i=0;i<7;++i)
	{
		date.print(MyHappenings1);
		date.add_one();
	}


	return 0;
}
