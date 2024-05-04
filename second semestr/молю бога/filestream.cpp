#include "filestream.h"

void newDB() {
    std::cout << "Напишите название для нового файла базы данных:\n>>> ";
    std::string input;
    getline(std::cin, input);
    std::fstream newF(input, std::ios::out);
    if (newF.is_open()) {
        std::cout << "Файл успешно создан!\n";
        return;
    }
    std::cout << "Не удалось создать файл!\n";
}

void deleteDB() {
    std::cout << "Введите название файла базы данных для удаления:\n>>> ";
    std::string input;
    getline(std::cin, input);

    if (std::remove(input.c_str()) != 0)
    {
        std::cout << "Не удалось удалить файл\n";
        return;
    }
    std::cout << "Файл успешно удален!\n\n";
}

void saveDataBase(Deque* users) {
    std::ofstream fileWrite("users.txt");
    if (fileWrite.is_open()) {
        int size = users->size;
        for (int i = 0; i < size; i++) {
            User user = getElemStart(users);

            std::string line = "id:";
            line += std::to_string(user.id);
            line += " size_interests:" + std::to_string(user.size_interests);
            line += " size_friends:" + std::to_string(user.size_friends);
            line += user.account_type ? " 1" : " 0";

            std::string name(user.name), surname(user.surname);

            line += " {;" + name + ";,;" + surname + ";}";

            if (user.size_interests != 0) {
                line += " {";
                for (int j = 0; j < user.size_interests; j++) {
                    line += std::to_string(user.interests[j].id) + ",";
                }
                line += "}";
            }

            for (int j = 0; j < user.size_friends; j++) {
                std::string friend_name(user.friends[j].name),
                    friend_surname(user.friends[j].surname);
                line += " {" + std::to_string(user.friends[j].id) + ",";
                line += ";" + friend_name + ";,;" + friend_surname + ";}";
            }
            if (i != users->size) line += "\n";
            fileWrite << line;
            line = "";
            addElemEnd(users, user);
        }
        std::cout << "Данные успешно сохранены!\n";
    }
    else {
        std::cout << "Ошибка сохранения данных!\n";
    }
    fileWrite.close();
}

Deque* loadDataBase(bool isFirst) {
    std::fstream fileRead("users.txt");
    std::string line;

    Deque* users = initDeque();

    if (fileRead.is_open()) {
        while (getline(fileRead, line)) {
            User user;

            int id = 0, size_interests = 0, size_friends = 0, count = 0, num = 0;
            for (int j = 0; j < line.length(); j++) {
                if (line[j] == ':') {
                    std::string temp = "";
                    count = j + 1;
                    while (line[count] != ' ') {
                        temp += line[count];
                        count++;
                    }
                    switch (num) {
                    case 0:
                        id = stoi(temp);
                        break;
                    case 1:
                        size_interests = stoi(temp);
                        break;
                    case 2:
                        size_friends = stoi(temp);
                        break;
                    default:
                        break;
                    }
                    num++;
                }
            }
            char account_type = line[count + 1];
            count += 5;
            char name[20];
            int index = count;
            while (line[count] != ';') {
                name[count - index] = line[count];
                count++;
            }
            name[count - index] = '\0';
            count += 3;
            index = count;
            char surname[20];
            while (line[count] != ';') {
                surname[count - index] = line[count];
                count++;
            }
            surname[count - index] = '\0';
            count++;
            Interest interests[5];
            if (size_interests != 0) {
                count += 3;
                index = 0;
                while (line[count] != '}' && index < size_interests) {
                    std::string temp = "";
                    while (line[count] != ',') {
                        temp += line[count];
                        count++;
                    }

                    char** interestsInit = initInterests();
                    interests[index].id = std::stoi(temp);

                    strcpy_s(interests[index].name, interestsInit[interests[index].id - 1]);
                    count += 1;
                    index++;
                }
            }
            Friend friends[10];
            if (size_friends != 0) {
                count--;
                for (int j = 0; j < size_friends; j++) {
                    count += 4;
                    std::string temp;
                    while (line[count] != ',') {
                        temp += line[count];
                        count++;
                    }
                    count += 2;
                    friends[j].id = std::stoi(temp);
                    char name[20];
                    index = count;
                    while (line[count] != ';') {
                        name[count - index] = line[count];
                        count++;
                    }
                    name[count - index] = '\0';
                    count += 3;
                    char surname[20];
                    index = count;
                    while (line[count] != ';') {
                        surname[count - index] = line[count];
                        count++;
                    }
                    surname[count - index] = '\0';
                    strcpy_s(friends[j].name, name);
                    strcpy_s(friends[j].surname, surname);
                }
            }

            user.id = id;
            strcpy_s(user.name, name);
            strcpy_s(user.surname, surname);
            user.account_type = account_type == '1' ? true : false;
            user.size_interests = size_interests;
            user.size_friends = size_friends;

            for (int j = 0; j < size_interests; j++) {
                user.interests[j].id = interests[j].id;
                strcpy_s(user.interests[j].name, interests[j].name);
            }

            for (int j = 0; j < size_friends; j++) {
                user.friends[j].id = friends[j].id;
                strcpy_s(user.friends[j].name, friends[j].name);
                strcpy_s(user.friends[j].surname, friends[j].surname);
            }
            addElemEnd(users, user);
        }
    }
    else {
        std::cout << "Не удалось открыть файл!\n\n";
    }
    fileRead.close();
    if(!isFirst)
        std::cout << "Данные базы данных успешно загружены!\n";
    return users;
}
