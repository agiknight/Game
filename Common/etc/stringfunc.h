#pragma once


namespace common
{
	void replaceAll(string& str, const string& from, const string& to);
	string& trim(string &str);

	string& lowerCase(string &str);
	string& upperCase(string &str);

	string wstr2str(const wstring &wstr);
	wstring str2wstr(const string &str);

	string format(const char* fmt, ...);
	wstring formatw(const char* fmt, ...);

}
