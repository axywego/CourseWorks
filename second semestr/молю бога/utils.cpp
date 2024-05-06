#include "utils.h"

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "Имя: " << user.name << "\n";
    os << "Фамилия: " << user.surname << "\n";
    os << "Тип аккаунта: " << (user.account_type ? "Открытый" : "Закрытый") << "\n";
    os << "Интересы:\n";
    if (user.size_interests == 0) {
        std::cout << "\tОтсутствуют\n";
    }
    for (int i = 0; i < user.size_interests; i++) {
        os << "\t" << user.interests[i].name << "\n";
    }
    std::cout << "Друзья:\n";
    if (user.size_friends == 0) {
        std::cout << "\tОтсутствуют\n";
    }
    for (int i = 0; i < user.size_friends; i++) {
        os << "\t" << user.friends[i].name << " " << user.friends[i].surname;
    }
    os << "\n";
    return os;
}

void getline(std::istream& is, std::string& value) {
    std::cout << ">>> ";
    std::getline(std::cin, value);
}

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
        getline(std::cin, input);
        if (isNum(input)) {
            try {
                return stoi(input);
            }
            catch (std::invalid_argument) {
                std::cout << "Неверно введено значение!\n";
            }
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
            if(cycle != 0)
                std::cout << "|" << std::string(50, ' ') << "|\n";
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

bool compareId(const User user1, const User user2) {
    return user1.id < user2.id;
}

bool compareSurname(const User user1, const User user2) {
    return std::strcmp(user1.surname, user2.surname) < 0;
}

bool compareName(const User user1, const User user2) {
    return std::strcmp(user1.name, user2.name) < 0;
}
