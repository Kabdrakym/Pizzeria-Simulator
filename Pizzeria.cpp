#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
enum class PizzaSize { SMALL, MEDIUM, LARGE };
enum class BaseType { THIN, TRADITIONAL, THICK };
string to_string(PizzaSize s) {
    return s == PizzaSize::SMALL ? "Small" : s == PizzaSize::MEDIUM ? "Medium" : "Large";
}
string to_string(BaseType b) {
    return b == BaseType::THIN ? "Thin" : b == BaseType::TRADITIONAL ? "Traditional" : "Thick";
}
class MenuItem {
protected:
    string name; double basePrice;
public:
    MenuItem(string n, double p) : name(n), basePrice(p) {}
    virtual ~MenuItem() = default;
    virtual double calculatePrice() const = 0;
    virtual void display() const = 0;
};
struct Topping {
    string name; double price;
};
class Pizza : public MenuItem {
    PizzaSize size; BaseType base;
    vector<Topping> toppings;
public:
    Pizza(string n, double p, PizzaSize s, BaseType b)
        : MenuItem(n, p), size(s), base(b) {}
    void addTopping(const Topping& t) { toppings.push_back(t); }
    double calculatePrice() const override {
        double price = basePrice;
        for (auto& t : toppings) price += t.price;
        if (size == PizzaSize::MEDIUM) price += 2;
        else if (size == PizzaSize::LARGE) price += 4;
        return price;
    }
    void display() const override {
        cout << "Pizza: " << name << ", Size: " << to_string(size)
             << ", Base: " << to_string(base) << ", Price: " << calculatePrice() << "\n";
    }
};
class Drink : public MenuItem {
    double volume; bool carbon;
public:
    Drink(string n, double p, double v, bool c)
        : MenuItem(n, p), volume(v), carbon(c) {}
    double calculatePrice() const override {
        return basePrice + volume * 0.05 + (carbon ? 0.5 : 0);
    }
    void display() const override {
        cout << "Drink: " << name << " (" << volume << "L, "
             << (carbon ? "Carbonated" : "Still") << ") - $" << calculatePrice() << "\n";
    }
};
class SideDish : public MenuItem {
    string portion;
public:
    SideDish(string n, double p, string ps)
        : MenuItem(n, p), portion(ps) {}
    double calculatePrice() const override {
        return basePrice + (portion == "Large" ? 2 : portion == "Medium" ? 1 : 0);
    }
    void display() const override {
        cout << "Side: " << name << " (" << portion << ") - $" << calculatePrice() << "\n";
    }
};
class Menu {
    vector<Pizza> pizzas;
    vector<Drink> drinks;
    vector<SideDish> sides;
    vector<Topping> toppings;
public:
    Menu() {
        toppings = { {"Cheese",1.0},{"Olives",0.5},{"Pepperoni",1.5},{"Mushrooms",0.7} };
        pizzas = {
            Pizza("Margherita",6.0,PizzaSize::SMALL,BaseType::TRADITIONAL),
            Pizza("Pepperoni",8.0,PizzaSize::MEDIUM,BaseType::THIN)
        };
        drinks = {
            Drink("Cola",2.0,0.5,true), Drink("Water",1.5,0.5,false)
        };
        sides = {
            SideDish("Fries",3.0,"Medium"), SideDish("Nuggets",4.0,"Large")
        };
    }
    void displayMenu() const {
        cout << "\n-- Menu --\n";
        for (auto& p : pizzas) p.display();
        for (auto& d : drinks) d.display();
        for (auto& s : sides) s.display();
    }
    void displayToppings() const {
        cout << "\n-- Toppings --\n";
        for (auto& t : toppings)
            cout << t.name << " ($" << t.price << ")\n";
    }
};
int main() {
    Menu menu;
    menu.displayMenu();
    menu.displayToppings();
    return 0;
}