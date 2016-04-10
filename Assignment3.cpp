#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Mydate.hh"
using std::string;
using std::vector;
using std::endl;
using std::cout;
using std::ifstream;
using std::cin;
using std::istringstream;

// read a date file into vector of events.
void readfile(const string &filename,vector<EventSpec> &E)
{
	ifstream file(filename.c_str());
	if(!file)
	{
		file.close();
		std::cout << "No such file";
		return;
	}
	//
	while(file)
	{
		string line;
		getline(file,line);
		if(file.eof()) break;
		if(line.empty()) continue;
		if(line[0]=='#') continue;
		// fields
		string day;
		string month;
		string year;
		string weekday;
		string event;
		//
		unsigned long pos=line.find(':');
		string line1 = line.substr(0,pos);
		string line2 = line.substr(pos+1,line.length());
		istringstream ss1(line1);
		istringstream ss2(line2);
		//
		string tmp="";
		getline(ss1,tmp,'.');
		day = tmp;
		getline(ss1,tmp,'.');
		month = tmp;
		getline(ss1,tmp,'.');
		year = tmp;
		getline(ss2,tmp,':');
		weekday = tmp;
		getline(ss2,tmp,':');
		event = tmp;
		// convert
		int f1,f2,f3,f4;
		// day
		if(day=="$") f1=-1;
		else if(day=="*") f1=0;
		else f1=atoi(day.c_str());
		// month
		if(month=="*") f2=0;
		else f2=atoi(month.c_str());
		// year
		if(year=="*") f3=0;
		else f3=atoi(year.c_str());
		// weekday
		if(weekday=="*") f4=0;
		else if(weekday=="Mon") f4=1;
		else if(weekday=="Tue") f4=2;
		else if(weekday=="Wed") f4=3;
		else if(weekday=="Thu") f4=4;
		else if(weekday=="Fri") f4=5;
		else if(weekday=="Sat") f4=6;
		else if(weekday=="Sun") f4=7;
		else f4=-1;
		// append
		EventSpec s={f1,f2,f3,f4,event};
		E.push_back(s);
	}
}

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
