#include "utils.h"

bool isNum(const std::string& input){
    for (char el : input) {
        if(!(el >= '0' && el <= '9')){
            return false;
        }
    }
    return true;
}

int validInput(std::string& input) {
    while (true) {
        std::cout << ">>> ";
        getline(std::cin, input);
        if (isNum(input)) {
            return stoi(input);
        }
        else {
            std::cout << "Неверно введено значение!\n";
        }
    }
}

void welcomeMessage() {
    char a = 92;
    std::cout << "    " << " __        __   _\n";
    std::cout << "    " << " " << a << " " << a << "      / /__| | ___ ___  _ __ ___   ___  \n";
    std::cout << "    " << "  " << a << " " << a << " /" << a << " / / _ " << a << " |/ __/ _ " << a << "| '_ ` _ " << a << " / _ " << a << " \n";
    std::cout << "    " << "   " << a << " V  V /  __/ | (_| (_) | | | | | |  __/ \n";
    std::cout << "    " << "    " << a << "_/" << a << "_/ " << a << "___|_|" << a << "___" << a << "___/|_| |_| |_|" << a << "___| \n";
}

void menuMessage(std::string items[], int indexes[], int size) {
    int index = 0, cycle = 0, outIndex = 1;
    char a = 92;
    std::cout << " " << std::string(50, '_') << "\n";
    std::cout << "/" << std::string(50, ' ') << a << "\n";
    while (cycle < size) {

        std::string str = items[cycle];
        const size_t msgSize = str.length();

        if (cycle == indexes[index]) {
            index++;
            size_t offset = 50 / 2 - msgSize / 2;
            std::cout << "|" << std::string(offset, ' ') << str << std::string((msgSize % 2 == 0 ? offset : offset - 1), ' ') << "|\n";

        }
        else {
            std::cout << "|" << std::string(6, ' ') << outIndex << ". " << str << std::string(41 - msgSize - (outIndex >= 10 ? 1 : 0), ' ') << "|\n";
            outIndex++;
        }
        cycle++;
    }
    std::cout << a << std::string(50, '_') << "/\n";
    std::cout << "\n";
}

Deque* searchUsersByAttribute(Deque* users, std::string attribute, std::string value) {
    Deque* attributeUsers = initDeque();
    User user;
    int size = users->size;
    while (size > 0) {
        user = getElemStart(users);
        if (user.surname == value && attribute == "surname") {
            addElemEnd(attributeUsers, user);
        }
        else if (user.name == value && attribute == "name") {
            addElemEnd(attributeUsers, user);
        }
        else if (std::to_string(user.id) == value && attribute == "id") {
            addElemEnd(attributeUsers, user);
        }
        addElemEnd(users, user);
        size--;
    }
    return attributeUsers;
}

void editUsers(Deque* users) {
    std::string itemsSearch[]{ "МЕНЮ РЕДАКТИРОВАНИЯ", "Поиск по id", "Поиск по фамилии", "Выход в меню" };
    int choice = 0, numItems = sizeof(itemsSearch) / sizeof(itemsSearch[0]), indexes[]{ 0 };
    std::string itemsToEdit[]{ "ВЫБОР ИЗМЕНЕНИЯ","Поменять фамилию", "Поменять имя", "Поменять тип аккаунта",
                               "Поменять интересы", "Поменять друзей (переобуться)" , "Выйти в меню" };
    Deque* maybeFriends = initDeque();
    char** interests;
    std::string input, choiceInterest;
    std::set<int> nums_interests;

    size_t i;
    int index, size, counter, count;
    while (choice != numItems - 1) {
    startEdit:
        menuMessage(itemsSearch, indexes, numItems);
        std::string input;

        Deque* searchUsers = initDeque();

        int choice = validInput(input);
        if (choice == 3) {
            std::cout << "Выход в меню...\n\n";
            return;
        }
        else if (choice == 1 || choice == 2) {
            if (choice == 1)
                searchUsers = copyDeque(users);
            else {
                Deque* surnameUsers = initDeque();
                while (true) {
                    std::cout << "Напишите фамилию пользователя(напишите -1, если хотите вернуться):\n>>> ";
                    getline(std::cin, input);
                    if (input == "-1") goto startEdit;
                    surnameUsers = searchUsersByAttribute(users, "surname", input);
                    if (surnameUsers->size == 0) {
                        std::cout << "Не найдено совпадений!\n\n";
                    }
                    else {
                        break;
                    }
                }
                searchUsers = copyDeque(surnameUsers);
                int size = searchUsers->size;
                while (size > 0) {
                    User temp = getElemStart(searchUsers);
                    std::cout << temp.id << ". " << temp.name << " " << temp.surname << ". Интересы: ";
                    for (int i = 0; i < temp.size_interests; i++) {
                        std::cout << temp.interests[i].name << " ";
                    }
                    std::cout << "\n";
                    addElemEnd(searchUsers, temp);
                    size--;
                }
            }
            std::cout << "Напишите id пользователя(напишите -1, если хотите вернуться):\n\n";
            User user;
            while (true) {
                choice = validInput(input);

                if (choice == -1) goto startEdit;

                user = getElemStart(searchUsersByAttribute(searchUsers, "id", std::to_string(choice)));
                if (user.id == -1) std::cout << "Такой пользователь не найден!\n\n";
                else break;
            }
            //-------------------------------------------Изменение пользователя-----------------------------------------//
            menuMessage(itemsToEdit, indexes, sizeof(itemsToEdit) / sizeof(itemsToEdit[0]));
            choice = validInput(input);
            switch (choice) {
            case 1:
            editSurname:
                while (true) {
                    std::cout << "Введите новую фамилию:\n>>> ";
                    getline(std::cin, input);
                    if (input.size() <= 20) {
                        for (char el : input) {
                            if (el >= 'A' && el <= 'Z' || el >= 'a' && el <= 'z' ||
                                el >= 'А' && el <= 'Я' || el >= 'а' && el <= 'я' ||
                                el == 'Ё' || el == 'ё') {
                                continue;
                            }
                            else {
                                std::cout << "Фамилия не может содержать цифры, пробелы и спец. символы!!\n";
                                goto editSurname;
                            }
                        }
                        break;
                    }
                    else {
                        std::cout << "Фамилия превысила ограничение\n";
                    }
                }
                std::cout << "Фамилия успешно изменена!\n\n";
                strcpy(user.surname, input.c_str());//strcpy_s
                break;
            case 2:
                while (true) {
                    std::cout << "Введите новое имя:\n>>> ";
                    getline(std::cin, input);
                    if (input.size() <= 20) {
                        for (char el : input) {
                            if (el >= 'A' && el <= 'Z' || el >= 'a' && el <= 'z' ||
                                el >= 'А' && el <= 'Я' || el >= 'а' && el <= 'я' ||
                                el == 'Ё' || el == 'ё') {
                                continue;
                            }
                            else {
                                std::cout << "Имя не может содержать цифры, пробелы и спец. символы!!\n";
                                goto editSurname;
                            }
                        }
                        break;
                    }
                    else {
                        std::cout << "Имя превысило ограничение\n";
                    }
                }
                std::cout << "Имя успешно изменено!\n\n";
                strcpy(user.name, input.c_str());//strcpy_s
                break;
            case 3:
                std::cout << "Выберите новый тип аккаунта: 0 - закрытый, 1 - открытый:\n";

                while (true) {
                    std::cout << ">>> ";
                    getline(std::cin, input);
                    if (input == "0" || input == "1") {
                        user.account_type = std::stoi(input);
                        break;
                    }
                    else {
                        std::cout << "Неверный выбор!\n";
                    }
                }
                std::cout << "Тип аккаунта успешно изменен!\n\n";
                break;
            case 4:
                interests = initInterests();
                size = sizeof(namesInterestsStr) / sizeof(namesInterestsStr[0]);

                std::cout << "Выберите 5 новых интересов(пишите номера через пробел)\n";
                std::cout << std::string(120, '-') << "\n";

                counter = 0;

                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (i < size) {
                            std::string line = std::to_string(i + 1) + "." + interests[i];
                            std::cout << std::left << std::setw(45) << line;
                            i++;
                        }
                    }
                    i--;
                    std::cout << "\n";
                }
                std::cout << "\n";

            interestsEditLoop:
                std::cout << ">>> ";
                getline(std::cin, input);
                i = input.size() - 1;
                while (input[i] == ' ') {
                    input.pop_back();
                    i--;
                }
                input += ' ';

                if (std::count(input.begin(), input.end(), ' ') > 5) {
                    std::cout << "Слишком много интересов!\n";
                    goto interestsEditLoop;
                }
                count = 0;
                for (char el : input) {
                    if (el >= '0' && el <= '9') choiceInterest += el;
                    else if (el >= 'A' && el <= 'Z' || el >= 'a' && el <= 'z' ||
                        el >= 'А' && el <= 'Я' || el >= 'а' && el <= 'я' ||
                        el == 'Ё' || el == 'ё') {
                        std::cout << "В строке содержаться буквы!\n";
                        goto interestsEditLoop;
                    }
                    else if (std::isspace(el)) {
                        int number = stoi(choiceInterest);
                        if (number <= size && number > 0) {
                            count++;
                            nums_interests.insert(number);
                        }
                        else {
                            std::cout << "Вы ввели недействительные номера!\n";
                            goto interestsEditLoop;
                        }
                        choiceInterest = "";
                    }
                    else {
                        std::cout << "Введите номера!\n";
                        goto interestsEditLoop;
                    }
                }
                if (nums_interests.size() != count) {
                    std::cout << "Есть повторяющие номера!\n";
                    goto interestsEditLoop;
                }
                user.size_interests = count;

                index = 0;
                for (int number : nums_interests) {
                    char name[30];
                    for (int j = 0; j < 30; j++) {
                        name[j] = interests[number - 1][j];
                    }
                    Interest interest;
                    interest.id = number;
                    strcpy(interest.name, name);//strcpy_s
                    user.interests[index] = interest;
                    index++;
                }
                std::cout << "\nИнтересы успешно изменены!\n";
                break;
            case 5:
                user.size_friends = 0;
                while (user.size_friends <= 9) {

                    std::cout << "\nТеперь друзья: чтобы добавить друга - напишите его фамилию.\n";
                restartInput:
                    std::cout << "Если вы уже закончили ввод или хотите пропусть это, тогда напишите 0\n";
                    std::cout << "Фамилия пользователя:\n";

                    while (true) {
                        std::cout << ">>> ";
                        getline(std::cin, input);
                        maybeFriends = initDeque();
                        maybeFriends = searchUsersByAttribute(users, "surname", input);
                        size = maybeFriends->size;
                        while (size > 0) {
                            User temp = getElemStart(maybeFriends);
                            if (user.id != temp.id) {
                                addElemEnd(maybeFriends, temp);
                            }
                            size--;
                        }
                        if (input == "0") goto endEditFriends;
                        else if (maybeFriends->size != 0) break;
                        else if (maybeFriends->size == 0) std::cout << "овпадения не найдены, попробуйте еще раз\n";

                    }
                    std::cout << "Найдены совпадения:\n\n";

                    size = maybeFriends->size;
                    while (size > 0) {
                        User temp = getElemStart(maybeFriends);
                        std::cout << temp.id << ". " << temp.name << " " << temp.surname << ". Интересы: ";
                        for (int i = 0; i < temp.size_interests; i++) {
                            std::cout << temp.interests[i].name << " ";
                        }
                        addElemEnd(maybeFriends, temp);
                        size--;
                    }
                    std::cout << "\n\n";
                    std::cout << "Напишите id того пользователя, которого хотите добавить в друзья (если вы ошиблись в фамилии, то напишите -1)\n";

                checkValidInputFriends:

                    int friend_id = validInput(input);

                    if (friend_id == -1) goto restartInput;
                    else {
                        User friend_user = getElemStart(searchUsersByAttribute(maybeFriends, "id", std::to_string(friend_id)));
                        if (friend_user.id == -1) {
                            std::cout << "Введите id заново: ";
                            goto checkValidInputFriends;
                        }
                        else {
                            user.size_friends++;
                            user.friends[user.size_friends - 1].id = friend_user.id;
                            strcpy(user.friends[user.size_friends - 1].name, friend_user.name);//strcpy_s
                            strcpy(user.friends[user.size_friends - 1].surname, friend_user.surname);//strcpy_s
                        }
                    }
                }
            endEditFriends:
                std::cout << "Друзья успешно изменены!\n\n";
                break;
            case 6:
                break;
            default:
                std::cout << "Неправильный ввод!";
            }
            //--------------------------------------------Конец изменения-------------------------------------//
            int size = users->size;
            while (size > 0) {
                User temp = getElemStart(users);
                if (temp.id == user.id) {
                    temp = user;
                }
                addElemEnd(users, temp);
                size--;
            }
            if (1 <= choice && choice <= 6) {
                std::cout << "Вы желаете продолжить?\n1. Да\n2. Нет\n\n";
                while (true) {
                    choice = validInput(input);

                    if (choice == 1) {
                        choice = numItems;
                        break;
                    }
                    else if (choice == 2) {
                        return;
                    }
                    else {
                        std::cout << "Выберите либо 1, либо 2!\n\n";
                    }
                }
            }
        }
        else {
            std::cout << "Неверно выбран пункт!\n\n";
        }
    }
}

void validFriends(Deque* users) {
    Deque* copyUsers = initDeque();
    int size = users->size;
    while (size > 0) {
        User user = getElemStart(users);
        int count = 0;
        Friend newFriends[10];
        for (int i = 0; i < user.size_friends; i++) {
            if (searchUsersByAttribute(users, "id", std::to_string(user.friends[i].id))->size != 0) {
                newFriends[count] = user.friends[i];
                count++;
            }
        }
        for (int i = 0; i < 10; i++) {
            user.friends[i] = newFriends[i];
        }
        user.size_friends = count;
        addElemEnd(users, user);
        size--;
    }
}

User searchUserByIndex(Deque* users, int index) {
    int i = 0, size = users->size;
    User user;
    if (index < size) {
        Deque* newD = initDeque();
        while (size > 0) {
            User temp = getElemStart(users);
            addElemEnd(newD, temp);
            addElemEnd(users, temp);
            size--;
        }
        size = users->size;
        while (i <= index) {
            user = getElemStart(newD);
            i++;
        }
    }
    else {
        user.id = -1;
    }
    return user;
}

void swapElementsDeque(Deque* users, int index1, int index2) {
    User user1, user2, temp;
    if (index1 > index2) {
        int tempnum = index1;
        index1 = index2;
        index2 = tempnum;
    }
    int size = users->size;
    user1 = searchUserByIndex(users, index1);
    user2 = searchUserByIndex(users, index2);
    const int _size = users->size;
    while (size > 0) {
        temp = getElemStart(users);
        if (_size - size == index1) {
            addElemEnd(users, user2);
        }
        else if (_size - size == index2) {
            addElemEnd(users, user1);
        }
        else {
            addElemEnd(users, temp);
        }
        size--;
    }
}

Deque* filtres(Deque* users) {
    std::string menuItems[]{ "ВЫБЕРИТЕ КРИТЕРИЙ ФИЛЬТРАЦИИ", "По имени", "По фамилии", "По интересам", "Выход в меню" };

    int indexes[]{ 0 }, trigger = sizeof(menuItems) / sizeof(menuItems[0]) - sizeof(indexes) / sizeof(indexes[0]),
        choice = 0, size, count;
    size_t i;
    char** interests = initInterests();

    std::string choiceInput;

    while (choice != trigger) {
        menuMessage(menuItems, indexes, sizeof(menuItems) / sizeof(menuItems[0]));
        std::set<int> nums_interests;
        Deque* newDInterests = initDeque();
        Deque* nameUsers = initDeque();
        Deque* surnameUsers = initDeque();
        std::string input;
        choice = validInput(input);
        switch (choice) {
        case 1:
            std::cout << "Напишите имя, по которому вести поиск:\n";
            getline(std::cin, input);
            if (input == "-1") {
                std::cout << "Вы вышли в меню...";
                return nameUsers;
            }
            nameUsers = searchUsersByAttribute(users, "name", input);
            if (nameUsers->size == 0) {
                std::cout << "Не найдено совпадений!\n";
            }
            else {
                return nameUsers;
            }
            break;
        case 2:
            std::cout << "Напишите фамилию, по которой вести поиск:\n";
            getline(std::cin, input);
            if (input == "-1") {
                std::cout << "Вы вышли в меню...";
                return surnameUsers;
            }
            surnameUsers = searchUsersByAttribute(users, "surname", input);
            if (surnameUsers->size == 0) {
                std::cout << "Не найдено совпадений!\n";
            }
            else {
                return surnameUsers;
            }
            break;
        case 3:

            size = sizeof(namesInterestsStr) / sizeof(namesInterestsStr[0]);

            std::cout << "Выберите 5 интересов(пишите номера через пробел)\n";
            std::cout << std::string(120, '-') << "\n";

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < 3; j++) {
                    if (i < size) {
                        std::string line = std::to_string(i + 1) + "." + interests[i];
                        std::cout << std::left << std::setw(45) << line;
                        i++;
                    }
                }
                i--;
                std::cout << "\n";
            }
            std::cout << "\n";

        interestsFilterLoop:
            count = 0;
            std::cout << ">>> ";
            getline(std::cin, input);
            i = input.size() - 1;
            while (input[i] == ' ') {
                input.pop_back();
                i--;
            }
            input += ' ';

            if (std::count(input.begin(), input.end(), ' ') > 5) {
                std::cout << "Слишком много интересов!\n";
                goto interestsFilterLoop;
            }

            for (char el : input) {
                if (el >= '0' && el <= '9') choiceInput += el;
                else if (el >= 'A' && el <= 'Z' || el >= 'a' && el <= 'z' ||
                    el >= 'А' && el <= 'Я' || el >= 'а' && el <= 'я' ||
                    el == 'Ё' || el == 'ё') {
                    std::cout << "В строке содержаться буквы!\n";
                    goto interestsFilterLoop;
                }
                else if (std::isspace(el)) {
                    int number = stoi(choiceInput);
                    if (number <= size && number > 0) {
                        count++;
                        nums_interests.insert(number);
                    }
                    else {
                        std::cout << "Вы ввели недействительные номера!\n";
                        goto interestsFilterLoop;
                    }
                    choiceInput = "";
                }
                else {
                    std::cout << "Введите номера!\n";
                    goto interestsFilterLoop;
                }
            }
            if (nums_interests.size() != count) {
                std::cout << "Есть повторяющие номера!\n";
                goto interestsFilterLoop;
            }
            size = users->size;
            while (size > 0) {
                User user = getElemStart(users);
                bool check = true;
                std::set<int> copyNums = nums_interests;
                for (int i = 0; i < user.size_interests; i++) {
                    for (int num : copyNums) {
                        if (user.interests[i].id == num) {
                            copyNums.erase(num);
                            break;
                        }
                    }
                }
                if (copyNums.size() == 0) {
                    addElemEnd(newDInterests, user);
                }
                addElemEnd(users, user);
                size--;
            }
            if (newDInterests->size == 0) {
                std::cout << "Нет совпадений!\n";
            }
            else {
                return newDInterests;
            }
            break;
        case 4:
            return nameUsers;
        default:
            std::cout << "Неверный выбор!\n\n";
            break;
        }
    }
}

bool compareId(const User user1, const User user2) {
    return user1.id < user2.id;
}

bool compareSurname(const User user1, const User user2) {
    return std::strcmp(user1.surname, user2.surname) < 0;
}

bool compareName(const User user1, const User user2) {
    return std::strcmp(user1.name, user2.name) < 0;
}

void sortShell(Deque* users, bool (*compare)(const User, const User)) {
    int size = users->size;
    int steps[]{ 9, 5, 3, 1 };
    for (int i = 0; i < 4; i++) {
        int first = 0;
        while (first < size) {
            int pos = first, min = first;
            while (pos < size) {
                bool condition = compare(searchUserByIndex(users, pos), searchUserByIndex(users, min));
                if (condition) {
                    min = pos;
                }
                pos += steps[i];
            }
            if (min > first) {
                swapElementsDeque(users, min, first);
            }
            first += steps[i];
        }
    }
}

void sorting(Deque* users) {
    std::string mainItems[]{ "ТИП СОРТИРОВКИ", "По возрастанию", "По убыванию", "Выйти в меню" },
        typeItems[]{ "КРИТЕРИИ СОРТИРОВКИ", "По id", "По фамилии", "По имени", "Вернуться в главное меню"};
    int indexes[]{ 0 };
    std::string input = "";
    int mainChoice = 0, choiceCrit = 0,
        triggerToMenu = sizeof(mainItems) / sizeof(mainItems[0]) - sizeof(indexes) / sizeof(indexes[0]),
        sizeMain = sizeof(mainItems) / sizeof(mainItems[0]), sizeCrit = sizeof(typeItems) / sizeof(typeItems[0]);

    while (mainChoice != triggerToMenu) {
        menuMessage(mainItems, indexes, sizeMain);
        mainChoice = validInput(input);
        if (mainChoice != triggerToMenu) {
            menuMessage(typeItems, indexes, sizeCrit);
            choiceCrit = validInput(input);
            if (choiceCrit == 1) {
                sortShell(users, compareId);
            }
            else if (choiceCrit == 2) {
                sortShell(users, compareSurname);
            }
            else if (choiceCrit == 3) {
                sortShell(users, compareName);
            }
            else {
                break;
            }
        }
        else {
            break;
        }
        if (mainChoice == 2) {
            Deque* revUsers = initDeque();
            int size = users->size;
            while (size > 0) {
                User temp = getElemStart(users);
                addElemStart(revUsers, temp);
                size--;
            }
            size = revUsers->size;
            while (size > 0) {
                addElemEnd(users, getElemStart(revUsers));
                size--;
            }
        }
        else if (mainChoice == 3) {
            break;
        }
        std::cout << "Сортировка выполнена успешно!\n";
        std::cout << "Вы желаете продолжить?\n1. Да\n2. Нет\n\n";
        while (true) {
            mainChoice = validInput(input);

            if (mainChoice == 1) {
                mainChoice = triggerToMenu;
                break;
            }
            else if (mainChoice == 2) {
                return;
            }
            else {
                std::cout << "Выберите либо 1, либо 2!\n\n";
            }
        }
    }
}

Deque* deleteUsers(Deque* users) {
    std::string items[] = { "МЕНЮ УДАЛЕНИЯ" ,"Удаление по id", "Удаление по фамилии", "Выйти в меню" };
    int indexes[]{ 0 };
    if (users->size == 0) {
        std::cout << "В базе данных нет пользователей!\n";
        return users;
    }
    else {
        while (true) {
            menuMessage(items, indexes, sizeof(items) / sizeof(items[0]));
            std::string input;

            Deque* searchUsers = initDeque();
            Deque* newUsers = initDeque();

            int choice = validInput(input);
            if (choice == 3) {
                std::cout << "Выход в меню...\n";
                return users;
            }

            else if (choice == 1 || choice == 2) {
                if (choice == 1) searchUsers = copyDeque(users);
                else {
                    std::cout << "Напишите фамилию:\n\n";

                    Deque* surnameUsers = initDeque();
                    std::string surname;

                    while (true) {
                        std::cout << ">>> ";
                        getline(std::cin, surname);

                        surnameUsers = searchUsersByAttribute(users, "surname", surname);

                        if (surnameUsers->size == 0) std::cout << "Совпадений не найдено, попробуйте еще раз\n\n";
                        else break;
                    }
                    std::cout << "Найдены совпадения:\n\n";

                    int size = surnameUsers->size;

                    while (size > 0) {
                        User temp = getElemStart(surnameUsers);
                        std::cout << temp.id << ". " << temp.surname << " " << temp.name << ". Интересы: ";
                        if (temp.size_interests != 0) {
                            for (int i = 0; i < temp.size_interests; i++) {
                                std::cout << temp.interests[i].name << " ";
                            }
                        }
                        else std::cout << "интересов нет";
                        std::cout << "\n";

                        addElemEnd(surnameUsers, temp);
                        size--;
                    }
                    searchUsers = copyDeque(surnameUsers);
                }
                std::cout << "Напишите id пользователя, которого надо удалить:\n\n";
                int id;

                User user;
                Deque* findedUsers = initDeque();
                while (true) {
                    id = validInput(input);
                    findedUsers = searchUsersByAttribute(searchUsers, "id", std::to_string(id));
                    if (findedUsers->size == 0) std::cout << "Не найдено совпадений!\n\n";
                    else break;
                }
                user = getElemStart(findedUsers);
                int size = users->size;
                while (size > 0) {
                    User temp = getElemStart(users);
                    if (temp.id != id) {
                        addElemEnd(users, temp);
                    }
                    size--;
                }

                std::cout << "Пользователь успешно удалён!\n\n";
                if (users->size != 0) {
                    std::cout << "Вы желаете продолжить удаление пользователей?\n1. Да\n2. Нет\n\n";
                    while (true) {
                        choice = validInput(input);

                        if (choice == 1) {
                            break;
                        }
                        else if (choice == 2) {
                            return users;
                        }
                        else {
                            std::cout << "Выберите либо 1, либо2!\n\n";
                        }
                    }
                }
                else {
                    std::cout << "Вы возвращены в главное меню...\n";
                    return users;
                }
            }
            else {
                std::cout << "Неверный выбор!\n\n";
            }
        }
    }
}
