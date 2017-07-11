// SortAndAggre.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include<time.h> 
using namespace std;


std::vector<std::string> split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//扩展字符串以方便操作
	int size = str.size();
	
	for (int i = 0; i<size; i++)
	{
	     pos = str.find(pattern, i);
	     if (pos<size)
		 {
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		 }
	 }
	 return result;
}

int main()
{
	clock_t start, finish,midlle;
	start = clock();
	ifstream fin("decode.txt");
	string s;
	std::map<string, int> map;
	std::map<string, int>::iterator it;

	while (getline(fin, s))
	{
		std::vector<std::string> res = split(s,",");
		string key = res.at(2) + "," + res.at(3);
		it = map.find(key);
		if (it == map.end()) {
			map[key] = atoi( res.at(0).c_str() ) ;
		}
		else {
			map[key] += atoi( res.at(0).c_str() ) ;
		}
		
	 }
	fin.close();
	ofstream fout("result.txt", ios::out);
	
	for (it = map.begin(); it != map.end(); ++it)
		 fout << it->first << "  " << it->second << endl;
	fout.close();
	 finish = clock();
	 cout << double(finish - start) / CLOCKS_PER_SEC << " (s) " << endl;
	 return 0;
}

