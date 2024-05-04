#include "structs.h"

char** initInterests() {
    int size = sizeof(namesInterestsStr) / sizeof(namesInterestsStr[0]);
    char** names_interests = (char**)calloc(size, sizeof(char*));
    for (int i = 0; i < size; i++) {
        names_interests[i] = (char*)calloc(namesInterestsStr[i].length() + 1, sizeof(char));
        strcpy(names_interests[i], namesInterestsStr[i].c_str());//strcpy_s
        names_interests[i][namesInterestsStr[i].length()] = '\0';
    }
    return names_interests;
}

Deque* initDeque() {
    struct Deque* d = (struct Deque*)calloc(1, sizeof(struct Deque));
    d->start = nullptr;
    d->end = nullptr;
    d->size = 0;
    return d;
}

bool isEmptyDeque(Deque* d) {
    if (d->size == 0) return 1;
    return 0;
}

void addElemStart(Deque* d, User user) {
    Element* newElement = (Element*)malloc(sizeof(Element));
    newElement->data = user;
    newElement->prev = nullptr;
    newElement->next = d->start;

    if (isEmptyDeque(d)) {
        d->end = newElement;
    }
    else {
        d->start->prev = newElement;
    }

    d->start = newElement;
    d->size++;
}

User getElemStart(Deque* d) {
    User frontData = d->start->data;
    Element* nextElement = d->start->next;

    delete d->start;

    if (nextElement != nullptr) {
        nextElement->prev = nullptr;
    }
    else {
        d->end = nullptr;
    }

    d->start = nextElement;
    d->size--;

    return frontData;
}

void addElemEnd(Deque* d, User user) {
    Element* newElement = (Element*)malloc(sizeof(Element));
    newElement->data = user;
    newElement->prev = d->end;
    newElement->next = nullptr;

    if (isEmptyDeque(d)) {
        d->start = newElement;
    }
    else {
        d->end->next = newElement;
    }

    d->end = newElement;
    d->size++;
}

User getElemEnd(Deque* d) {
    User backData = d->end->data;
    Element* prevElement = d->end->prev;

    delete d->end;

    if (prevElement != nullptr) {
        prevElement->next = nullptr;
    }
    else {
        d->start = nullptr;
    }

    d->end = prevElement;
    d->size--;

    return backData;
}

void clearDeque(Deque* d) {
    User elem;
    while (!isEmptyDeque(d)) {
        elem = getElemStart(d);
    }
    free((void*)d->start);
    free((void*)d->end);
}

Deque* copyDeque(Deque* d) {
    int size = d->size;
    Deque* newD = initDeque();
    while (size > 0) {
        User temp = getElemStart(d);
        addElemEnd(newD, temp);
        addElemEnd(d, temp);
        size--;
    }
    return newD;
}
