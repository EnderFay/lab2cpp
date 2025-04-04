#include <iostream>
#include <string>
#include <fstream>

using namespace std;

namespace db {
    class Product {
        string _name;
        string _author;
        string _pass;
        string _release_date;

    public:
        Product() = default;
        Product(const string& name, const string& author, 
                const string& pass, const string& release_date);

        string getName() const;
        string getAuthor() const;
        string getPass() const;
        string getReleaseDate() const;

        void setName(const string& name);
        void setAuthor(const string& author);
        void setPass(const string& pass);
        void setReleaseDate(const string& release_date);

        friend istream& operator>>(istream& in, Product& p);
        friend ostream& operator<<(ostream& out, const Product& p);
    };

    class Database {
        Product* _products;
        int _size;
        int _capacity;

        void resize(int new_capacity);

    public:
        Database();
        ~Database();

        void AddMag(const Product& product);
        void RemoveMag(int index);
        void EditMag(int index, const Product& new_product);
        void ReadMags() const;
        void SearchMagByName(const string& name) const;
        void SearchMagByAuthor(const string& author) const;
        void SaveToFile(const string& filename) const;
        void LoadFromFile(const string& filename);
        int getSize() const;
        Product getProduct(int index) const;
    };

    void showMenu();
}