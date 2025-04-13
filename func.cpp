#include "head.h"
#include <limits>

namespace db {

    Product::Product(const std::string& name, const std::string& author, const std::string& pass, const std::string& release_date) : _name(name), _author(author), _pass(pass), _release_date(release_date) {}

    std::string Product::getName() const { return _name; }
    std::string Product::getAuthor() const { return _author; }
    std::string Product::getPass() const { return _pass; }
    std::string Product::getReleaseDate() const { return _release_date; }

    void Product::setName(const std::string& name) { _name = name; }
    void Product::setAuthor(const std::string& author) { _author = author; }
    void Product::setPass(const std::string& pass) { _pass = pass; }
    void Product::setReleaseDate(const std::string& release_date) { _release_date = release_date; }

    std::istream& operator>>(std::istream& in, Product& p) {
        std::getline(in, p._name);
        std::getline(in, p._author);
        std::getline(in, p._pass);
        std::getline(in, p._release_date);
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const Product& p) {
        out << p._name << "\n" << p._author << "\n" 
            << p._pass << "\n" << p._release_date << "\n";
        return out;
    }

    Database::Database() : _products(nullptr), _size(0), _capacity(0) {}
    Database::~Database() { delete[] _products; }

    void Database::resize(int new_capacity) {
        Product* new_products = new Product[new_capacity];
        for (int i = 0; i < _size; ++i) {
            new_products[i] = _products[i];
        }
        delete[] _products;
        _products = new_products;
        _capacity = new_capacity;
    }

    void Database::AddMag(const Product& product) {
        if (_size >= _capacity) {
            if (_capacity == 0) {
                resize(1);} 
            else {
                resize(_capacity * 2);}
        }
        _products[_size++] = product;
    }

    void Database::RemoveMag(int index) {
        if (index < 0 || index >= _size) return;
        for (int i = index; i < _size - 1; ++i) {
            _products[i] = _products[i + 1];
        }
        _size--;
    }

    void Database::EditMag(int index, const Product& new_product) {
        if (index >= 0 && index < _size) {
            _products[index] = new_product;
        }
    }

    void Database::ReadMags() const {
        for (int i = 0; i < _size; ++i) {
            std::cout << "Журнал №" << i + 1 << ":\n";
            std::cout << "Название: " << _products[i].getName() << "\n";
            std::cout << "Автор: " << _products[i].getAuthor() << "\n";
            std::cout << "Одобрен/Не одобрен: " << _products[i].getPass() << "\n";
            std::cout << "Дата выпуска: " << _products[i].getReleaseDate() << "\n\n";
        }
    }

    void Database::SearchMagByName(const std::string& name) const {
        bool found = false;
        for (int i = 0; i < _size; ++i) {
            if (_products[i].getName().find(name) != std::string::npos) {
                std::cout << "Журнал №" << i + 1 << ":\n";
                std::cout << "Название: " << _products[i].getName() << "\n";
                std::cout << "Автор: " << _products[i].getAuthor() << "\n";
                std::cout << "Одобрен/Не одобрен: " << _products[i].getPass() << "\n";
                std::cout << "Дата выпуска: " << _products[i].getReleaseDate() << "\n\n";
                found = true;
            }
        }
        if (!found) {
            std::cout << "Журналы с названием '" << name << "' не найдены.\n";
        }
    }

    void Database::SearchMagByAuthor(const std::string& author) const {
        bool found = false;
        for (int i = 0; i < _size; ++i) {
            if (_products[i].getAuthor() == author) {
                std::cout << "Журнал №" << i + 1 << ":\n";
                std::cout << "Название: " << _products[i].getName() << "\n";
                std::cout << "Автор: " << _products[i].getAuthor() << "\n";
                std::cout << "Одобрен/Не одобрен: " << _products[i].getPass() << "\n";
                std::cout << "Дата выпуска: " << _products[i].getReleaseDate() << "\n\n";
                found = true;
            }
        }
        if (!found) {
            std::cout << "Журналы автора '" << author << "' не найдены.\n";
        }
    }

    void Database::SaveToFile(const std::string& filename) const {
        std::ofstream out(filename);
        out << _size << "\n";
        for (int i = 0; i < _size; ++i) {
            out << _products[i];
        }
        out.close();
    }

    void Database::LoadFromFile(const std::string& filename) {
         std::ifstream in(filename);

        if (!in) {
            std::cerr << "Не удалось открыть файл: " << filename << std::endl;
            return;
        }

        int file_size;
        in >> file_size;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        delete[] _products;
        _products = nullptr;
        _size = 0;
        _capacity = 0;

        if (file_size > 0) {
            _products = new Product[file_size];
            _capacity = file_size;
    
            for (int i = 0; i < file_size; ++i) {
                Product product;
                in >> product;
                if (!in) {
                    std::cerr << "Не удалось прочитать данные из файла." << std::endl;
                    break;
                } else {
                    _products[_size++] = product;
                }
            }
        }
        in.close();
    }

    int Database::getSize() const { return _size; }
    Product Database::getProduct(int index) const { 
        return (index >= 0 && index < _size) ? _products[index] : Product(); 
    }

    void showMenu() {
        std::cout << "\nМеню:\n";
        std::cout << "1. Вывести список журналов\n";
        std::cout << "2. Добавить новый журнал\n";
        std::cout << "3. Удалить журнал\n";
        std::cout << "4. Редактировать журнал\n";
        std::cout << "5. Поиск по названию\n";
        std::cout << "6. Поиск по автору\n";
        std::cout << "7. Сохранить изменения\n";
        std::cout << "8. Выйти\n";
        std::cout << "Ваш выбор: ";
    }
}
