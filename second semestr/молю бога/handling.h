#ifndef HANDLING_H
#define HANDLING_H

#include <iostream>
#include "structs.h"
#include "utils.h"

Deque* searchUsersByAttribute(Deque* users, std::string attribute, std::string value);

void editUsers(Deque* users);

void sortShell(Deque* users, bool (*compare)(const User, const User));

void sorting(Deque* users);

Deque* deleteUsers(Deque* users);

User searchUserByIndex(Deque* users, int index);

void swapElementsDeque(Deque* users, int index1, int index2);

Deque* filtres(Deque* users);

#endif