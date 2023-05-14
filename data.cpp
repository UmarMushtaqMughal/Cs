#include <iostream>
#include <vector>

using namespace std;

class Item {
protected:
    string name;
    string sku;
    int quantity;
    double price;

public:
    Item(const string& name, const string& sku, int quantity, double price)
        : name(name), sku(sku), quantity(quantity), price(price) {}

    virtual ~Item() {}

    // Getters and setters
    const string& getName() const {
        return name;
    }

    const string& getSKU() const {
        return sku;
    }

    int getQuantity() const {
        return quantity;
    }

    void setQuantity(int quantity) {
        this->quantity = quantity;
    }

    double getPrice() const {
        return price;
    }

    void setPrice(double price) {
        this->price = price;
    }

};

class Clothing : public Item {
private:
    string size;
    string color;
    string material;

public:
    Clothing(const string& name, const string& sku, int quantity, double price,
             const string& size, const string& color, const string& material)
        : Item(name, sku, quantity, price), size(size), color(color), material(material) {}

    // Getters and setters specific to Clothing class
    const string& getSize() const {
        return size;
    }

    const string& getColor() const {
        return color;
    }

    const string& getMaterial() const {
        return material;
    }
};

class Grocery : public Item {
private:
    string category;

public:
    Grocery(const string& name, const string& sku, int quantity, double price, const string& category)
        : Item(name, sku, quantity, price), category(category) {}

    // Getters and setters specific to Grocery class
    const string& getCategory() const {
        return category;
    }
};

class Inventory {
private:
    vector<Item*> items;

public:
    // Destructor to free memory allocated for items
    ~Inventory() {
        for (Item* item : items) {
            delete item;
        }
    }

    // Methods for managing the inventory
    void add_item(Item* item) {
        items.push_back(item);
    }

    void remove_item(const string& sku) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if ((*it)->getSKU() == sku) {
                delete *it;
                items.erase(it);
                break;
            }
        }
    }

    void update_item(const string& sku, const string& attribute, double value) {
        for (Item* item : items) {
            if (item->getSKU() == sku) {
                if (attribute == "quantity") {
                    item->setQuantity(static_cast<int>(value));
                } else if (attribute == "price") {
                    item->setPrice(value);
                }
                break;
            }
        }
    }

    Item* get_item(const string& sku) {
        for (Item* item : items) {
            if (item->getSKU() == sku) {
                return item;
            }
        }
        return nullptr; // Item with the given SKU not found
    }

    double get_inventory_value() {
        double totalValue = 0.0;
        for (Item* item : items) {
            totalValue += item->getQuantity() * item->getPrice();

            return totalValue;
        }
    }
    bool is_sku_unique(const std::string& sku) {
        // Iterate over the items in the inventory and check if any have the same SKU
        for (const auto& item : items) {
            if (item->getSKU() == sku) {
                return false; // SKU is not unique
            }
        }
        return true; // SKU is unique
    }
};

