// adblockhelper.cpp : Defines the entry point for the console application.
// Author:Jinsong.van@gmail.com.

#include "stdafx.h"

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <time.h> 

int _tmain(int argc, _TCHAR* argv[])
{
	// Read file.
	std::ifstream in("china_mobile_list.txt");
	if (!in)
		return 0;
	// init list.
	std::string line;
	std::list<std::string> blocklist;
	std::list<std::string> hidelist;
	while (getline(in, line)) {
		if (line[0] == '!')
			continue;
		if (line.find("##") != std::string::npos)
			hidelist.push_back(line);
		else
			blocklist.push_back(line);
	}
	in.close();
	// sort list.
	blocklist.sort();
	hidelist.sort();
	// get curent time.
	time_t rawtime = time(NULL);
	struct tm  timeinfo;
	localtime_s(&timeinfo, &rawtime);
	char version[64];
	strftime(version, sizeof(version), "%Y%m%d", &timeinfo);
	char modified[64];
	strftime(modified, sizeof(modified), "%d %b. %Y %H:%M UTC", &timeinfo);
	char currenttime[64];
	strftime(currenttime, sizeof(currenttime), "  %a, %d %b. %Y %H:%M:%S +0800", &timeinfo);

	// print list.
	std::ofstream out("china_mobile_list.txt");
	// print info.
	out << "! [AdBlock Plus 2.1]" << std::endl,
	out << "! Version: " << std::string(version) << std::endl;
	out << "! Title: China Mobile List" << std::endl;
	out << "! Chinese supplement for the AdBlock filters" << std::endl;
	out << "! Last Modified: " << std::string(modified) << std::endl;
	out << "! Expires: 5 days(update frequency)" << std::endl;
	out << "!" << std::endl;
	out << "! Please report any unblocked adverts or problems" << std::endl;
	out << "! or via e-mail(jinsong.van@gmail.com)." << std::endl;
	out << "!" << std::endl;
	out << "! Fork of: ChinaList https://github.com/JinsongVan/chinalist" << std::endl;
	out << "!" << std::string(currenttime) << std::endl;
	out << "!*** china-mobile-list.txt ***!" << std::endl;
	// print blocking rules.
	for (std::list<std::string>::iterator it = blocklist.begin();
			it != blocklist.end(); ++it) {
		if (out.is_open())
		    out << *it << std::endl;
	}
	// print element hide rules.
	out << "!********** Element Hide ************!" << std::endl;
	for (std::list<std::string>::iterator it = hidelist.begin();
		it != hidelist.end(); ++it) {
		if (out.is_open())
			out << *it << std::endl;
	}
	out << "!************* The End **************!";
	out.close();
	
	return 0;
}

