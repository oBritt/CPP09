

#ifndef BITCOINEXCHANGE_CPP
#define BITCOINEXCHANGE_CPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>
int get_map(std::map<std::string, double>& mp);
void handle_one_line(std::map<std::string, double>& mp, std::string line);
#endif