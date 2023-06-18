#include <iostream>
#include <string>
#include <vector>

//Задание 1
class Overcoat
{
    char* type;
    char* size;
    char* color;
    double price;
public:
    Overcoat(const char* typeP, const char* sizeP, const char* colorP, double priceP);
    Overcoat() : type{ nullptr }, size{ nullptr }, color{ nullptr }, price{ 0 } {}
    Overcoat(const Overcoat& object);
    Overcoat(Overcoat&& object);

    Overcoat& setType(const char* typeP);
    Overcoat& setSize(const char* sizeP);
    Overcoat& setColor(const char* colorP);
    Overcoat& setPrise(double priceP) { price = priceP; return *this; };

    const char* getType()const { return type; }
    const char* getSize()const { return size; }
    const char* getColor()const { return color; }
    double getPrice()const { return price; }

    Overcoat& operator=(const Overcoat& object);
    Overcoat& operator=(Overcoat&& object);

    friend bool operator==(const Overcoat& left, const Overcoat& right);
    friend bool operator>(const Overcoat& left, const Overcoat& right);

    friend std::ostream& operator<<(std::ostream& out, const Overcoat& object);

    ~Overcoat() { delete[] type; delete[] size; delete[] color; }
};

Overcoat::Overcoat(const char* typeP, const char* sizeP, const char* colorP, double priceP) :
    type{ new char[strlen(typeP) + 1] }, size{ new char[strlen(sizeP) + 1] }, color{ new char[strlen(colorP) + 1] }, price{ priceP }
{
    strcpy_s(type, strlen(typeP) + 1, typeP);
    strcpy_s(size, strlen(sizeP) + 1, sizeP);
    strcpy_s(color, strlen(colorP) + 1, colorP);
}
Overcoat::Overcoat(const Overcoat& object) :
    type{ new char[strlen(object.type) + 1] }, size{ new char[strlen(object.size) + 1] }, color{ new char[strlen(object.color) + 1] }, price{ object.price }
{
    strcpy_s(type, strlen(object.type) + 1, object.type);
    strcpy_s(size, strlen(object.size) + 1, object.size);
    strcpy_s(color, strlen(object.color) + 1, object.color);
}
Overcoat::Overcoat(Overcoat&& object) :
    type{ object.type }, size{ object.size }, color{ object.color }, price{ object.price }
{
    object.type = nullptr;
    object.size = nullptr;
    object.color = nullptr;
    object.price = 0;
}

Overcoat& Overcoat::setType(const char* typeP)
{
    delete[] type;
    type = new char[strlen(typeP) + 1];
    strcpy_s(type, strlen(typeP) + 1, typeP);
    return *this;
}
Overcoat& Overcoat::setSize(const char* sizeP)
{
    delete[] size;
    size = new char[strlen(sizeP) + 1];
    strcpy_s(size, strlen(sizeP) + 1, sizeP);
    return *this;
}
Overcoat& Overcoat::setColor(const char* colorP)
{
    delete[] color;
    color = new char[strlen(colorP) + 1];
    strcpy_s(color, strlen(colorP) + 1, colorP);
    return *this;
}

Overcoat& Overcoat::operator=(const Overcoat& object)
{
    if (this == &object) { return *this; }

    delete[] type;
    delete[] size;
    delete[] color;

    type = new char[strlen(object.type) + 1];
    size = new char[strlen(object.size) + 1];
    color = new char[strlen(object.color) + 1];
    strcpy_s(type, strlen(object.type) + 1, object.type);
    strcpy_s(size, strlen(object.size) + 1, object.size);
    strcpy_s(color, strlen(object.color) + 1, object.color);
    price = object.price;
    return *this;
}
Overcoat& Overcoat::operator=(Overcoat&& object)
{
    if (this == &object) { return *this; }

    delete[] type;
    delete[] size;
    delete[] color;

    type = object.type;
    size = object.size;
    color = object.color;
    price = object.price;

    object.type = nullptr;
    object.size = nullptr;
    object.color = nullptr;
    object.price = 0;

    return *this;
}

bool operator==(const Overcoat& left, const Overcoat& right)
{
    return (strcmp(left.type, right.type) == 0 and strcmp(left.size, right.size) == 0 and strcmp(left.color, right.color) == 0 and left.price == right.price);
}

bool operator>(const Overcoat& left, const Overcoat& right)
{
    return (left.price > right.price);
}

std::ostream& operator<<(std::ostream& out, const Overcoat& object)
{
    if (object.type and object.size and object.color and object.price)
    {
        out << "Тип: " << object.type << " Размер: " << object.size << " Цвет: " << object.color << " Цена: " << object.price << '\n';
    }
    else { out << "[placeholder overcoat]"; }
    return out;
}



int main()
{
    setlocale(LC_ALL, "Russian");
    //Задание 1
    Overcoat overcoat_1;
    std::cout << overcoat_1 << '\n';

    Overcoat coatBlack{ "Плащ", "M", "Черный", 3500.5 };
    Overcoat coatBrown{ "Плащ", "L", "Коричневый", 4850.8 };
    std::cout << coatBlack << coatBrown << '\n';

    overcoat_1 = coatBlack;
    Overcoat coat_2{ std::move(coatBrown) };
    std::cout << coatBlack << overcoat_1 << coat_2 << coatBrown << '\n';

    Overcoat leatherJacket{ "Кожаная куртка", "M", "Черная", 5700 };
    std::cout << std::boolalpha << "\nКуртка дороже, чем плащ #2 - " << (leatherJacket > coat_2) << '\n';

    std::cout << std::boolalpha << "\nЧерный плащ и плащ №1 - одно и то же - " << (coatBlack == overcoat_1) << '\n';
    std::cout << std::boolalpha << "\nЧерный плащ и плащ №2 - одно и то же - " << (coatBlack == coat_2) << '\n';

    return 0;
}