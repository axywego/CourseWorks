#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <iomanip>
#include "structs.h"
#include "handling.h"
#include <set>
#include <algorithm>

std::ostream& operator << (std::ostream& os, const User& user);

void getline(std::istream& is, std::string& value);

bool isNum(const std::string& input);

int validInput(std::string& input);

void welcomeMessage();

void menuMessage(std::string items[], int indexes[], int size);

void validFriends(Deque* users);

bool compareId(const User user1, const User user2);

bool compareSurname(const User user1, const User user2);

bool compareName(const User user1, const User user2);

#endif
