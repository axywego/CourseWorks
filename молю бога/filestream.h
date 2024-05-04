#ifndef FILESTREAM_H
#define FILESTREAM_H

#include <iostream>
#include <string>
#include <fstream>
#include "structs.h"

void newDB();
void deleteDB();
void saveDataBase(Deque* users);
Deque* loadDataBase(bool isFirst);

#endif 
