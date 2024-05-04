#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <iomanip>
#include "structs.h"
#include <set>
#include <algorithm>

Deque* deleteUsers(Deque* users);

bool isNum(const std::string& input);

int validInput(std::string& input);

Deque* searchUsersByAttribute(Deque* users, std::string attribute, std::string value);

void welcomeMessage();

void menuMessage(std::string items[], int indexes[], int size);

void editUsers(Deque* users);

void validFriends(Deque* users);

User searchUserByIndex(Deque* users, int index);

void swapElementsDeque(Deque* users, int index1, int index2);

Deque* filtres(Deque* users);

bool compareId(const User user1, const User user2);

bool compareSurname(const User user1, const User user2);

bool compareName(const User user1, const User user2);

void sortShell(Deque* users, bool (*compare)(const User, const User));

void sorting(Deque* users);

#endif
