#pragma once

#include <iostream> 
#include <iomanip>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

namespace MF
{
	auto ReadValidNum(string Text)
	{
		auto Num = 0;
		cout << Text << endl;
		cin >> Num;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Invalid Input, Pleas enter a number\n";
			cin >> Num;
		}
		return Num;
	}
	/*int ReadNumInRang(string Text, int from, int to)
	{

		cout << Text << endl;
		
	}*/
	int RandomNumber(int From, int To)
	{
		int randNum = rand() % (To - From + 1) + From;
		return randNum;
	}
	void GenerateDifferentRandomNum()
	{
		srand((unsigned)time(NULL));
	}
	char InverChar(char ch)
	{
		return (isupper(ch)) ? ch = tolower(ch) : ch = toupper(ch);
	}
	string ReadText(string Text)
	{
		cout << Text << endl;
		getline(cin, Text);
		return Text;
	}
	void InvertString(string Text)
	{
		for (int i = 0; i < Text.length(); i++)
		{
			Text[i] = MF::InverChar(Text[i]);
		}
		cout << Text << endl;
	}
	vector <string> SplitRecordLine(string RecordLine, string Delim = "#//#")
	{
		vector <string> vSplitData;
		size_t start = 0, Pos;
		while ((Pos = RecordLine.find(Delim, start)) != std::string::npos)
		{
			if (Pos > start)
				vSplitData.push_back(RecordLine.substr(start, Pos - start));

			start = Pos + Delim.length();
		}

		if (start < RecordLine.length())
			vSplitData.push_back(RecordLine.substr(start));

		return vSplitData;
	}
	string Tabs(short NumOfTabs)
	{
		string Tab = "";
		for (short i = 1; i <= NumOfTabs; i++)
		{
			Tab += "\t";
		}
		return Tab;
	}


}


