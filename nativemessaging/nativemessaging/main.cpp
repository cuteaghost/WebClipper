#include <iostream>  
#include <string>  
#include <fstream>  
#include <stdlib.h>
#include <windows.h>
#include <time.h>
using namespace std;
#include "json/json.h"

std::string UTF8_To_GBK(const std::string &source);
std::string getTime();

int main(int argc, char* argv[]) {
	//getTime();
	unsigned int length = 0;
	//read the first four bytes (=> Length)
	for (int i = 0; i < 4; i++)
	{
		unsigned int read_char = getchar();
		length = length | (read_char << i * 8);
	}

	//read the json-message
	string msg = "";
	for (int i = 0; i < length; i++)
	{
		msg += getchar();
	}
	

	Json::Reader reader;
	Json::Value value;
	std::string out;
	std::string type;
	std::string URL;
	std:string title;
	if (reader.parse(msg, value))
	{
		type = value["type"].asString();
		URL = value["URL"].asString();
		title = value["title"].asString();

		if (type == "SelectedTxt")
		{
			out = value["data"].asString();
			out = UTF8_To_GBK(out);
		}
		else if (type == "WebText")
		{
			out = value["data"].asString();
			out = UTF8_To_GBK(out);
		}
		else if(type == "SelectedWebPage")
		{
			const Json::Value arrayObj1 = value["data"];
			for (int i = 0; i<arrayObj1.size(); i++)
			{

				const Json::Value arrayObj2 = arrayObj1[i];
				for (int j = 0; j < arrayObj2.size(); j++)
				{
					out = arrayObj2[j].asString();
					out = UTF8_To_GBK(out);
				}
			}
		}
		else if (type == "WebPage")
		{
			const Json::Value arrayObj1 = value["data"];
			for (int i = 0; i<arrayObj1.size(); i++)
			{

				const Json::Value arrayObj2 = arrayObj1[i];
				for (int j = 0; j < arrayObj2.size(); j++)
				{
					out = arrayObj2[j].asString();
				}

			}
		}
	}

	//std::string filename = UTF8_To_GBK(title)+"_"+ UTF8_To_GBK(type) + "_" + getTime() + ".html";
	std::string filename = UTF8_To_GBK(title) + "_" + UTF8_To_GBK(type)+ ".html";
	std::string filepath = "E:\\program\\WebClipper\\webclipper\\Debug\\data\\" + filename;
	ofstream myfile(filepath);
	if (myfile.is_open())
	{
		//myfile << msg;
		myfile << out;
		//cout << out << endl;
		myfile.close();
	}
	
	WinExec("E:\\program\\WebClipper\\webclipper\\Debug\\webclipper.exe", SW_SHOW);   // 打开记事本*/
	system("pause");
	return 0;
}

std::string UTF8_To_GBK(const std::string &source)
{
	enum { GB2312 = 936 };

	unsigned long len = ::MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, NULL, NULL);
	if (len == 0)
		return std::string();
	wchar_t *wide_char_buffer = new wchar_t[len];
	::MultiByteToWideChar(CP_UTF8, NULL, source.c_str(), -1, wide_char_buffer, len);

	len = ::WideCharToMultiByte(GB2312, NULL, wide_char_buffer, -1, NULL, NULL, NULL, NULL);
	if (len == 0)
	{
		delete[] wide_char_buffer;
		return std::string();
	}
	char *multi_byte_buffer = new char[len];
	::WideCharToMultiByte(GB2312, NULL, wide_char_buffer, -1, multi_byte_buffer, len, NULL, NULL);

	std::string dest(multi_byte_buffer);
	delete[] wide_char_buffer;
	delete[] multi_byte_buffer;
	return dest;
}


std::string getTime()
{
	std::string totaltime;
	char buf[50];
	struct tm local;
	time_t t;
	time(&t);
	localtime_s(&local,&t);
	sprintf_s(buf, "%d年%d月%d日%d时%d分%d秒\n", local.tm_year + 1900, local.tm_mon + 1, local.tm_mday, local.tm_hour, local.tm_min, local.tm_sec);
	totaltime = buf;
	return totaltime;
}

