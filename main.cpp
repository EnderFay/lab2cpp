#include "head.h"
#include <iostream>
#include <limits>

int main() {
    db::Database database;
    database.LoadFromFile("file.txt");

    int choice;
    do {
        db::showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                database.ReadMags();
                break;
            }
            case 2: {
                std::string name, author, pass, release_date;
                std::cout << "Введите название: ";
                std::getline(std::cin, name);
                std::cout << "Введите автора: ";
                std::getline(std::cin, author);
                std::cout << "Одобрен/Не одобрен: ";
                std::getline(std::cin, pass);
                std::cout << "Введите дату выпуска: ";
                std::getline(std::cin, release_date);

                db::Product new_product(name, author, pass, release_date);
                database.AddMag(new_product);
                std::cout << "Журнал добавлен.\n";
                break;
            }
            case 3: {
                int i;
                std::cout << "Введите номер журнала для удаления: ";
                std::cin >> i;
                std::cin.ignore();
                if (i > 0 && i <= database.getSize()) {
                    database.RemoveMag(i - 1);
                    std::cout << "Журнал удален.\n";
                } else {
                    std::cout << "Неверный номер журнала.\n";
                }
                break;
            }
            case 4: {
                int i;
                std::cout << "Введите номер журнала для редактирования: ";
                std::cin >> i;
                std::cin.ignore();
                if (i > 0 && i <= database.getSize()) {
                    db::Product product = database.getProduct(i - 1);

                    std::string name, author, pass, release_date;
                    std::cout << "Текущее название (" << product.getName() << "): ";
                    std::getline(std::cin, name);
                    std::cout << "Текущий автор (" << product.getAuthor() << "): ";
                    std::getline(std::cin, author);
                    std::cout << "Одобрен/Не одобрен (" << product.getPass() << "): ";
                    std::getline(std::cin, pass);
                    std::cout << "Текущая дата выпуска (" << product.getReleaseDate() << "): ";
                    std::getline(std::cin, release_date);

                    if (!name.empty()) product.setName(name);
                    if (!author.empty()) product.setAuthor(author);
                    if (!pass.empty()) product.setPass(pass);
                    if (!release_date.empty()) product.setReleaseDate(release_date);

                    database.EditMag(i - 1, product);
                    std::cout << "Журнал обновлен.\n";
                } else {
                    std::cout << "Неверный номер Журнал.\n";
                }
                break;
            }
            case 5: {
                std::string name;
                std::cout << "Введите название для поиска: ";
                std::getline(std::cin, name);
                database.SearchMagByName(name);
                break;
            }
            case 6: {
                std::string author;
                std::cout << "Введите автора для поиска: ";
                std::getline(std::cin, author);
                database.SearchMagByAuthor(author);
                break;
            }
            case 7: {
                database.SaveToFile("file.txt");
                std::cout << "Изменения сохранены.\n";
                break;
            }
            case 8: {
                break;
            }
            default: {
                std::cout << "Попробуйте снова.\n";
            }
        }
    } while (choice != 8);

    database.SaveToFile("file.txt");
    return 0;
}