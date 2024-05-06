#include "ioput.h"

User enterNewUser(Deque* users) {
    User user;

    int id = 0;

    int sizeUsers = users->size;
    if (users->size == 0) {
        id = 1;
    }
    else {
        const User temp = getElemStart(users);
        if (temp.id != 1) {
            id = 1;
        }
        addElemStart(users, temp);
        Deque* newD = initDeque();
        newD = copyDeque(users);
        while (sizeUsers > 1) {
            const User first = getElemStart(users), second = getElemStart(users);
            if (abs(first.id - second.id) > 1) {
                id = first.id + 1;
                break;
            }
            addElemEnd(users, first);
            addElemStart(users, second);
            sizeUsers--;
        }
        if (id == 0) {
            id = users->size + 1;
        }
        *users = *copyDeque(newD);
        clearDeque(newD);
    }

    user.id = id;
    std::string input = "";

    enterName:
    while (true) {
        std::cout << "Напишите свое имя:\n";
        getline(std::cin, input);
        if (input.size() == 0) {
            std::cout << "Имя не может быть пустым!\n";
        }
        else if (input.size() <= 20) {
            for (char el : input) {
                if (el >= 'A' && el <= 'Z' || el >= 'a' && el <= 'z' ||
                    el >= 'А' && el <= 'Я' || el >= 'а' && el <= 'я' ||
                    el == 'Ё' || el == 'ё') {
                    continue;
                }
                else {
                    std::cout << "Имя не может содержать цифры, пробелы и спец. символы!\n";
                    goto enterName;
                }
            }
            break;
        }
        else {
            std::cout << "Имя превысило ограничение\n";
        }
    }
    strcpy_s(user.name, input.c_str());

    enterSurname:
    while (true) {
        std::cout << "Напишите свою фамилию:\n";
        getline(std::cin, input);
        if (input.size() == 0) {
            std::cout << "Фамилия не может быть пустой!\n";
        }
        else if (input.size() <= 20) {
            for (char el : input) {
                if (el >= 'A' && el <= 'Z' || el >= 'a' && el <= 'z' ||
                    el >= 'А' && el <= 'Я' || el >= 'а' && el <= 'я' ||
                    el == 'Ё' || el == 'ё') {
                    continue;
                }
                else {
                    std::cout << "Имя не может содержать цифры, пробелы и спец. символы!\n";
                    goto enterSurname;
                }
            }
            break;
        }
        else {
            std::cout << "Имя превысило ограничение\n";
        }
    }
    strcpy_s(user.surname, input.c_str());


    std::cout << "Выберите тип своего аккаунта: 0 - закрытый, 1 - открытый:\n";

    while (true) {
        getline(std::cin, input);
        if (input == "0" || input == "1") {
            user.account_type = std::stoi(input);
            break;
        }
        else {
            std::cout << "Неверный выбор!\n";
        }
    }

    //-----------------------------------------Интересы------------------------------------------//

    char** interests = initInterests();
    int size = sizeof(namesInterestsStr) / sizeof(namesInterestsStr[0]);

    std::cout << "Выберите 5 интересов(пишите номера через пробел)\n";
    std::cout << std::string(120, '-') << "\n";

    int counter = 0;

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

interestsLoop:

    std::set<int> nums_interests;
    int count = 0;
    getline(std::cin, input);
    if (input.size() == 0) {
        std::cout << "Неверный ввод!\n";
        goto interestsLoop;
    }
    size_t i = input.size() - 1;
    while (input[i] == ' ') {
        input.pop_back();
        i--;
    }
    input += ' ';

    if (std::count(input.begin(), input.end(), ' ') > 5) {
        std::cout << "Слишком много интересов!\n";
        goto interestsLoop;
    }
    if (input.size() == 0) {
        std::cout << "Вы не ввели ни одного интереса!\n";
        goto interestsLoop;
    }
    std::string choice;
    for (char el : input) {
        if (el >= '0' && el <= '9') choice += el;
        else if (el >= 'A' && el <= 'Z' || el >= 'a' && el <= 'z' ||
            el >= 'А' && el <= 'Я' || el >= 'а' && el <= 'я' ||
            el == 'Ё' || el == 'ё') {
            std::cout << "В строке содержаться буквы!\n";
            goto interestsLoop;
        }
        else if (std::isspace(el)) {
            int number;
            try {
                number = stoi(choice);
            }
            catch (std::invalid_argument) {
                std::cout << "Недействительный ввод!\n";
                goto interestsLoop;
            }
            if (number <= size && number > 0) {
                count++;
                nums_interests.insert(number);
            }
            else {
                std::cout << "Вы ввели недействительные номера!\n";
                goto interestsLoop;
            }
            choice = "";
        }
        else {
            std::cout << "Введите номера!\n";
            goto interestsLoop;
        }
    }
    if (nums_interests.size() != count) {
        std::cout << "Есть повторяющие номера!\n";
        goto interestsLoop;
    }
    user.size_interests = count;

    int index = 0;
    for (int number : nums_interests) {
        char name[30];
        for (int j = 0; j < 30; j++) {
            name[j] = interests[number - 1][j];
        }
        Interest interest;
        interest.id = number;
        strcpy_s(interest.name, name);
        user.interests[index] = interest;
        index++;
    }
    std::cout << "\nИнтересы успешно добавлены!\n";

    //-----------------------------------------Друзья------------------------------------------//

    user.size_friends = 0;
    while (user.size_friends <= 9) {
        Deque* maybeFriends = initDeque();

        std::cout << "\nТеперь друзья: чтобы добавить друга - напишите его фамилию.\nЕсли вы уже закончили ввод или хотите пропусть это, тогда напишите 0\n";
    newInput:
        std::cout << "Фамилия пользователя:\n";

        while (true) {
            getline(std::cin, input);
            maybeFriends = searchUsersByAttribute(users, "surname", input);
            if (input == "0") goto end;
            else if (maybeFriends->size != 0) break;
            else if (maybeFriends->size == 0) std::cout << "Совпадения не найдены, попробуйте еще раз\n";

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

    checkValidInput:

        int friend_id = validInput(input);

        if (friend_id == -1) goto newInput;
        else {
            User friend_user = getElemStart(searchUsersByAttribute(maybeFriends, "id", std::to_string(friend_id)));
            if (friend_user.id == -1) {
                std::cout << "Введите id заново: ";
                goto checkValidInput;
            }
            else {
                user.size_friends++;
                user.friends[user.size_friends - 1].id = friend_user.id;
                strcpy_s(user.friends[user.size_friends - 1].name, friend_user.name);
                strcpy_s(user.friends[user.size_friends - 1].surname, friend_user.surname);
                std::cout << "Друг добавлен!\n";
            }
        }
    }
end:
    return user;
}

void printAllUsersTable(Deque* users) {
    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(20) << "Имя"
        << std::setw(20) << "Фамилия"
        << std::setw(15) << "Тип аккаунта"
        << std::setw(20) << "Интересы"
        << "Друзья\n";

    std::cout << std::string(120, '-') << "\n";

    int index = 1;
    int size = users->size;
    while (size > 0) {
        User user = getElemStart(users);
        int max = (std::max)(user.size_interests, user.size_friends);
        max = max == 0 ? 1 : max;
        for (int i = 0; i < max; i++) {
            std::cout << std::left << std::setw(5) << (i == 0 ? std::to_string(user.id) : "")
                << std::setw(20) << (i == 0 ? user.name : "")
                << std::setw(20) << (i == 0 ? user.surname : "")
                << std::setw(15) << (i == 0 ? (user.account_type ? "Открытый" : "Закрытый") : "")
                << std::setw(20) << (i < user.size_interests ? user.interests[i].name : "")
                << std::setw(20) << (i < user.size_friends ? user.friends[i].name : "")
                << std::setw(20) << (i < user.size_friends ? user.friends[i].surname : "") << "\n";
        }
        std::cout << std::string(120, '-') << "\n";
        addElemEnd(users, user);
        size--;
    }
}
