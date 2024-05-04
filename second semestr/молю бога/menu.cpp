#include "menu.h"

void menu() {
    Deque* users = loadDataBase(true);
    welcomeMessage();
    std::string read = "-1";
    std::string items[]{ "РАБОТА С ДАННЫМИ", "Ввод данных", "Редактирование данных", "Удаление данных", "Вывод данных",
                         "РАБОТА С ФАЙЛАМИ", "Создание нового файла", "Удаление файла", "Сохранение данных в файл", "Загрузка данных из файла",
                         "ОСТАЛЬНОЕ", "Сортировка", "Фильтрация", "Выйти" };
    int indexes[]{ 0, 5, 10 };
    std::string trigger = std::to_string(sizeof(items) / sizeof(items[0]) - sizeof(indexes) / sizeof(indexes[0]));
    while (read != trigger) {

        menuMessage(items, indexes, sizeof(items) / sizeof(items[0]));
        std::cout << "Количество пользователей: " << users->size << "\n";
        int choice = validInput(read);
        Deque* newD = initDeque();
        switch (choice) {
        case 1:
            sortShell(users, compareId);
            addElemEnd(users, enterNewUser(users)); break;
        case 2:
            if (users->size == 0) {
                std::cout << "Нет ни одного пользователя!\n\n";
            }
            else {
                editUsers(users);
            }
            break;
        case 3:
            if (users->size == 0) {
                std::cout << "Нет ни одного пользователя!\n\n";
            }
            else {
                users = deleteUsers(users);
                validFriends(users);
            }
            break;
        case 4:
            if (users->size == 0) {
                std::cout << "Нет ни одного пользователя!\n\n";
            }
            else {
                printAllUsersTable(users);
            }
            break;
        case 5:
            newDB(); break;
        case 6:
            deleteDB(); break;
        case 7:
            saveDataBase(users); break;
        case 8:
            users = loadDataBase(false); break;
        case 9:
            if (users->size == 0) {
                std::cout << "Нет ни одного пользователя!\n\n";
            }
            else {
                sorting(users);
            }
            break;
        case 10:
            if (users->size == 0) {
                std::cout << "Нет ни одного пользователя!\n\n";
            }
            else {
                newD = filtres(users);
                if (newD->size > 0) {
                    printAllUsersTable(newD);
                }
                clearDeque(newD);
            }
            break;
        case 11:
            break;
        default:
            std::cout << "Неверный выбор!\n";
            break;
        }
    }
}
