#ifndef STRUCTS_H
#define STRUCTS_H

#include <cstring>
#include <iomanip>

#pragma warning(disable: 4996)

struct Friend {
    int id;
    char name[20];
    char surname[20];
};

struct Interest {
    int id;
    char name[30];
};

struct User {
    int id;
    int size_interests = 5;
    int size_friends = 10;
    char name[20];
    char surname[20];
    bool account_type;
    Interest interests[5];
    Friend friends[10];
};

struct Element {
    User data;
    Element* prev;
    Element* next;
};

struct Deque {
    Element* start;
    Element* end;
    int size;
};

static std::string namesInterestsStr[]{ "Программирование", "Музыка", "Танцы", "Живопись", "Схемотехника", "Волонтерство",
                                        "Культура", "Чтение книг", "Спорт", "Готовка", "Путешествия"
};

char** initInterests();

Deque* initDeque();

bool isEmptyDeque(Deque* d);

void addElemStart(Deque* d, User user);

User getElemStart(Deque* d);

void addElemEnd(Deque* d, User user);

User getElemEnd(Deque* d);

void clearDeque(Deque* d);

Deque* copyDeque(Deque* d);

#endif 
