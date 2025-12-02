#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <cctype>

using namespace std;

class Product {
public:
    string id;
    string name;
    int stock;
    double price;
    string category;

    Product(string id, string name, int stock, double price) {
        this->id = id;
        this->name = name;
        this->stock = stock;
        this->price = price;
        this->category = (id[0] == 'C' || id[0] == 'c') ? "CARD" : "PACK";
    }
};

class CartItem {
public:
    Product* product;
    int quantity;

    CartItem(Product* product, int quantity) {
        this->product = product;
        this->quantity = quantity;
    }

    double getSubtotal() {
        return product->price * quantity;
    }
};

class HotC {
private:
    vector<Product*> inventory;
    vector<CartItem*> cart;
    const int SCREEN_WIDTH = 78; // Total width including borders

    string formatNumber(double num) {
        stringstream ss;
        ss << fixed << setprecision(2);
        ss << num;
        string str = ss.str();

        // Thousands Comma
        int pos = str.find('.');
        if (pos == string::npos) pos = str.length();
        for (int i = pos - 3; i > 0; i -= 3) {
            str.insert(i, ",");
        }
        return str;
    }

    string getCurrentDateTime() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        stringstream ss;
        ss << 1900 + ltm->tm_year << "-"
           << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
           << setw(2) << setfill('0') << ltm->tm_mday << " "
           << setw(2) << setfill('0') << ltm->tm_hour << ":"
           << setw(2) << setfill('0') << ltm->tm_min << ":"
           << setw(2) << setfill('0') << ltm->tm_sec;
        return ss.str();
    }

    void initializeInventory() {
        // Cards
        inventory.push_back(new Product("C-001", "Dark Magician", 7, 550.00));
        inventory.push_back(new Product("C-002", "Blue-Eyes White Dragon", 4, 1172.50));
        inventory.push_back(new Product("C-003", "Red-Eyes Black Dragon", 12, 320.00));
        inventory.push_back(new Product("C-004", "Elemental Hero Neos", 18, 220.00));
        inventory.push_back(new Product("C-005", "Cyber Dragon", 6, 500.50));
        inventory.push_back(new Product("C-006", "Armed Dragon Lv10", 25, 55.50));
        inventory.push_back(new Product("C-007", "Stardust Dragon", 11, 233.00));
        inventory.push_back(new Product("C-008", "Red Dragon Archfiend", 9, 207.00));
        inventory.push_back(new Product("C-009", "Number 39: Utopia", 13, 223.50));
        inventory.push_back(new Product("C-010", "Galaxy-Eyes Photon Dragon", 23, 17.50));
        inventory.push_back(new Product("C-011", "Odd-Eyes Pendulum Dragon", 19, 14.50));
        inventory.push_back(new Product("C-012", "D/D/D Doom King Armageddon", 30, 3.00));
        inventory.push_back(new Product("C-013", "Firewall Dragon", 12, 20.50));
        inventory.push_back(new Product("C-014", "Decode Talker", 17, 17.50));
        inventory.push_back(new Product("C-015", "Borreload Dragon", 16, 7.50));
        inventory.push_back(new Product("C-016", "The Winged Dragon of Ra", 5, 450.00));
        inventory.push_back(new Product("C-017", "Slifer The Sky Dragon", 3, 600.00));
        inventory.push_back(new Product("C-018", "Obelisk The Tormentor", 2, 800.00));
        inventory.push_back(new Product("C-019", "Dark Magician Girl", 4, 1502.50));
        inventory.push_back(new Product("C-020", "Black Luster Soldier - Envoy of the Beginning", 11, 200.50));

        // Packs
        inventory.push_back(new Product("P-001", "Elemental Energy", 96, 250.50));
        inventory.push_back(new Product("P-002", "Champion Pack: Game One", 24, 487.00));
        inventory.push_back(new Product("P-003", "Retro Pack 1", 128, 120.50));
        inventory.push_back(new Product("P-004", "Retro Pack 2", 128, 120.50));
        inventory.push_back(new Product("P-005", "Lightning Overdrive", 72, 60.00));
    }

    // Center text within a line
    string centerText(string text, int width) {
        if (text.length() >= width) return text.substr(0, width);
        int padding = (width - text.length()) / 2;
        return string(padding, ' ') + text + string(width - text.length() - padding, ' ');
    }

    // Draw borders with consistent width
    void drawBorderTop() {
        cout << "+";
        for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << "~";
        cout << "+" << endl;
    }

    void drawBorderBottom() {
        cout << "+";
        for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << "~";
        cout << "+" << endl;
    }

    void drawBorderMiddle() {
        cout << "!";
        for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << "~";
        cout << "!" << endl;
    }

    void drawBorderThick() {
        cout << "+";
        for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << "=";
        cout << "+" << endl;
    }

    void drawBorderDouble() {
        cout << "+";
        for (int i = 0; i < SCREEN_WIDTH - 2; i++) cout << "-";
        cout << "+" << endl;
    }

    void drawTableBorderTop() {
        cout << "+~~~~~~~~~~~+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+~~~~~~~~~~~+~~~~~~~~~~~+" << endl;
    }

    void drawTableBorderMiddle() {
        cout << "+~~~~~~~~~~~+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+~~~~~~~~~~~+~~~~~~~~~~~+" << endl;
    }

    void drawTableBorderBottom() {
        cout << "+~~~~~~~~~~~+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+~~~~~~~~~~~+~~~~~~~~~~~+" << endl;
    }

    void drawTableBorderThick() {
        cout << "+===========+===============================================+===========+===========+" << endl;
    }

    void drawCartBorderTop() {
        cout << "+~~~~~~~~~~~+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+~~~~~~~~~~+~~~~~~~~~~~~~~~~+" << endl;
    }

    void drawCartBorderMiddle() {
        cout << "+~~~~~~~~~~~+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+~~~~~~~~~~+~~~~~~~~~~~~~~~~+" << endl;
    }

    void drawCartBorderBottom() {
        cout << "+~~~~~~~~~~~+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+~~~~~~~~~~+~~~~~~~~~~~~~~~~+" << endl;
    }

    void drawCartBorderThick() {
        cout << "+===========+===========================================+==========+================+" << endl;
    }

    void displayHeader(string title) {
        drawBorderTop();
        cout << "!" << centerText(title, SCREEN_WIDTH - 2) << "!" << endl;
        drawBorderThick();
    }

    void displayAllProducts() {
        displayHeader("HEART OF THE CARDS STORE");
        cout << "! Product ID ! Product Name                              ! In-Stock  !   Price     !" << endl;
        drawTableBorderThick();

        for (Product* p : inventory) {
            string stockInfo = (p->category == "CARD") ? to_string(p->stock) + " Cards" : to_string(p->stock) + " Packs";
            printf("! %-10s ! %-41s ! %-9s ! $%-10s !\n",
                   p->id.c_str(), p->name.c_str(), stockInfo.c_str(), formatNumber(p->price).c_str());
        }

        drawTableBorderBottom();
    }

    void displayProductsByCategory(string category) {
        string title = category + "S AVAILABLE";
        displayHeader(title);
        cout << "! Product ID ! Product Name                              ! In-Stock  !   Price     !" << endl;
        drawTableBorderThick();

        for (Product* p : inventory) {
            if (p->category == category) {
                string stockInfo = (p->category == "CARD") ? to_string(p->stock) + " Cards" : to_string(p->stock) + " Packs";
                printf("! %-10s ! %-41s ! %-9s ! $%-10s !\n",
                       p->id.c_str(), p->name.c_str(), stockInfo.c_str(), formatNumber(p->price).c_str());
            }
        }

        drawTableBorderBottom();
    }

    Product* findProduct(string id) {
        for (Product* p : inventory) {
            if (p->id == id) {
                return p;
            }
        }
        return nullptr;
    }

    void addToCart() {
        string productId;
        cout << "\nEnter Product ID (e.g., C-001 or P-001): ";
        cin >> productId;
        cin.ignore();

        transform(productId.begin(), productId.end(), productId.begin(), ::toupper);

        Product* product = findProduct(productId);
        if (product == nullptr) {
            cout << "⚠ Product not found!" << endl;
            return;
        }

        cout << "\nProduct: " << product->name << endl;
        cout << "Available Stock: " << product->stock << " " << (product->category == "CARD" ? "Cards" : "Packs") << endl;
        cout << "Price: $" << formatNumber(product->price) << endl;

        int quantity;
        cout << "\nEnter quantity: ";
        cin >> quantity;
        cin.ignore();

        if (quantity <= 0) {
            cout << "⚠ Invalid quantity!" << endl;
            return;
        }

        if (quantity > product->stock) {
            cout << "⚠ Insufficient stock! Only " << product->stock << " available." << endl;
            return;
        }

        // Check if product already in cart
        bool found = false;
        for (CartItem* item : cart) {
            if (item->product->id == productId) {
                int newQuantity = item->quantity + quantity;
                if (newQuantity > product->stock) {
                    cout << "⚠ Cannot add! Total would exceed available stock." << endl;
                    return;
                }
                item->quantity = newQuantity;
                found = true;
                break;
            }
        }

        if (!found) {
            cart.push_back(new CartItem(product, quantity));
        }

        cout << "✓ Added to cart successfully!" << endl;
    }

    void viewCart() {
        if (cart.empty()) {
            cout << "\n⚠ Your cart is empty!" << endl;
            return;
        }

        displayHeader("YOUR SHOPPING CART");
        cout << "! Product ID ! Product Name                          ! Quantity !   Subtotal     !" << endl;
        drawCartBorderThick();

        double total = 0;
        for (CartItem* item : cart) {
            printf("! %-10s ! %-38s ! %-8d ! $%-13s !\n",
                   item->product->id.c_str(), item->product->name.c_str(),
                   item->quantity, formatNumber(item->getSubtotal()).c_str());
            total += item->getSubtotal();
        }

        drawCartBorderMiddle();
        printf("!                                                                  TOTAL: $%-13s !\n", formatNumber(total).c_str());
        drawBorderBottom();
    }

    void checkout(string customerName, string customerAddress, string customerContact) {
        cout << "\n";
        displayHeader("CHECKOUT");

        double subtotal = 0;
        for (CartItem* item : cart) {
            subtotal += item->getSubtotal();
        }

        // Calculate discount based on total quantity with new rates
        int totalQuantity = 0;
        for (CartItem* item : cart) {
            totalQuantity += item->quantity;
        }

        double discountPercent = 0;
        if (totalQuantity >= 1 && totalQuantity <= 4) {
            discountPercent = 0;
        } else if (totalQuantity >= 5 && totalQuantity <= 10) {
            discountPercent = 2;
        } else if (totalQuantity >= 11 && totalQuantity <= 20) {
            discountPercent = 4;
        } else if (totalQuantity >= 21 && totalQuantity <= 25) {
            discountPercent = 6;
        } else if (totalQuantity >= 26 && totalQuantity <= 30) {
            discountPercent = 8;
        } else if (totalQuantity > 30) {
            discountPercent = 10;
        }

        double discountAmount = (subtotal * discountPercent) / 100;
        double afterDiscount = subtotal - discountAmount;

        // Add delivery fee
        const double DELIVERY_FEE = 3.00;
        double totalPrice = afterDiscount + DELIVERY_FEE;

        cout << "\nSubtotal: $" << formatNumber(subtotal) << endl;
        cout << "Discount (" << discountPercent << "%): -$" << formatNumber(discountAmount) << endl;
        cout << "Delivery Fee: $" << formatNumber(DELIVERY_FEE) << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "TOTAL PRICE: $" << formatNumber(totalPrice) << endl;
        cout << endl;

        // Payment
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << centerText("PAYMENT METHOD", 78) << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "[1] Cash" << endl;
        cout << "[2] Credit Card" << endl;
        cout << "Enter payment method: ";
        int paymentMethod;
        cin >> paymentMethod;
        cin.ignore();

        string paymentType = "CASH";
        string cardNumber = "";

        if (paymentMethod == 2) {
            paymentType = "CREDIT CARD";
            cout << "Credit Card Number: ";
            getline(cin, cardNumber);
            cout << "Credit Card PIN: ";
            string pin;
            getline(cin, pin);
            cout << "✓ Card verified!" << endl;
        }

        double paidAmount;
        cout << "\nPaid Amount: $";
        cin >> paidAmount;
        cin.ignore();

        double change = paidAmount - totalPrice;

        if (change < 0) {
            cout << "⚠ Insufficient payment!" << endl;
            return;
        }

        // Update inventory
        for (CartItem* item : cart) {
            item->product->stock -= item->quantity;
        }

        // Print Receipt
        printReceipt(customerName, customerAddress, customerContact, subtotal,
                    discountPercent, discountAmount, DELIVERY_FEE, totalPrice, paymentType,
                    cardNumber, paidAmount, change);

        cout << "\n✓ Transaction completed successfully!" << endl;
        cout << "Thank you for shopping at Heart of the Cards Store!" << endl;
    }

    void printReceipt(string name, string address, string contact,
                     double subtotal, double discountPercent, double discountAmount,
                     double deliveryFee, double totalPrice, string paymentType, string cardNumber,
                     double paidAmount, double change) {

        string dateTime = getCurrentDateTime();

        cout << "\n\n";
        drawBorderTop();
        cout << "!" << centerText("HEART OF THE CARDS STORE", SCREEN_WIDTH - 2) << "!" << endl;
        cout << "!" << centerText("OFFICIAL RECEIPT", SCREEN_WIDTH - 2) << "!" << endl;
        drawBorderDouble();


        cout << "! Date: " << dateTime;
        int datePadding = SCREEN_WIDTH - 9 - dateTime.length() - 1;
        if (datePadding > 0) cout << string(datePadding, ' ');
        cout << "!" << endl;

        drawBorderDouble();
        cout << "!" << centerText("CUSTOMER INFORMATION", SCREEN_WIDTH - 2) << "!" << endl;
        drawBorderDouble();


        cout << "! Name:    " << name;
        int namePadding = SCREEN_WIDTH - 11 - name.length() - 1;
        if (namePadding > 0) cout << string(namePadding, ' ');
        cout << "!" << endl;

        cout << "! Address: " << address;
        int addrPadding = SCREEN_WIDTH - 11 - address.length() - 1;
        if (addrPadding > 0) cout << string(addrPadding, ' ');
        cout << "!" << endl;

        cout << "! Contact: " << contact;
        int contactPadding = SCREEN_WIDTH - 11 - contact.length() - 1;
        if (contactPadding > 0) cout << string(contactPadding, ' ');
        cout << "!" << endl;

        drawBorderDouble();
        cout << "!" << centerText("ITEMS PURCHASED", SCREEN_WIDTH - 2) << "!" << endl;


        cout << "+===========+===========================================+==========+================+" << endl;
        cout << "! Product ID ! Product Name                          ! Quantity !   Subtotal     !" << endl;
        cout << "+~~~~~~~~~~~+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+~~~~~~~~~~+~~~~~~~~~~~~~~~~+" << endl;


        for (CartItem* item : cart) {
            printf("! %-10s ! %-38s ! %-8d ! $%-13s !\n",
                   item->product->id.c_str(), item->product->name.c_str(),
                   item->quantity, formatNumber(item->getSubtotal()).c_str());
        }

        cout << "+~~~~~~~~~~~+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+~~~~~~~~~~+~~~~~~~~~~~~~~~~+" << endl;

        // Subtotal
        string subtotalStr = "$" + formatNumber(subtotal);
        cout << "! Subtotal:";
        int subtotalPadding = 68 - subtotalStr.length();
        if (subtotalPadding > 0) cout << string(subtotalPadding, ' ');
        cout << subtotalStr << " !" << endl;

        // Discount
        string discountStr = "-$" + formatNumber(discountAmount);
        string discountLabel = "Discount (" + to_string((int)discountPercent) + "%):";
        cout << "! " << discountLabel;
        int discountPadding = 68 - discountLabel.length() - discountStr.length();
        if (discountPadding > 0) cout << string(discountPadding, ' ');
        cout << discountStr << " !" << endl;

        // Delivery Fee
        string deliveryStr = "$" + formatNumber(deliveryFee);
        cout << "! Delivery Fee:";
        int deliveryPadding = 68 - 14 - deliveryStr.length();
        if (deliveryPadding > 0) cout << string(deliveryPadding, ' ');
        cout << deliveryStr << " !" << endl;

        drawBorderDouble();

        // Total Price
        string totalStr = "$" + formatNumber(totalPrice);
        cout << "! TOTAL PRICE:";
        int totalPadding = 68 - 13 - totalStr.length();
        if (totalPadding > 0) cout << string(totalPadding, ' ');
        cout << totalStr << " !" << endl;

        drawBorderDouble();

        // Payment Method
        cout << "! Payment Method: " << paymentType;
        int paymentPadding = SCREEN_WIDTH - 18 - paymentType.length() - 1;
        if (paymentPadding > 0) cout << string(paymentPadding, ' ');
        cout << "!" << endl;

        // Card Number
        if (paymentType == "CREDIT CARD") {
            cout << "! Card Number: " << cardNumber;
            int cardPadding = SCREEN_WIDTH - 15 - cardNumber.length() - 1;
            if (cardPadding > 0) cout << string(cardPadding, ' ');
            cout << "!" << endl;
        }

        // Amount Paid
        string paidStr = "$" + formatNumber(paidAmount);
        cout << "! Amount Paid:";
        int paidPadding = 68 - 13 - paidStr.length();
        if (paidPadding > 0) cout << string(paidPadding, ' ');
        cout << paidStr << " !" << endl;

        // Change
        string changeStr = "$" + formatNumber(change);
        cout << "! Change:";
        int changePadding = 68 - 9 - changeStr.length();
        if (changePadding > 0) cout << string(changePadding, ' ');
        cout << changeStr << " !" << endl;

        drawBorderDouble();
        cout << "!" << centerText("THANK YOU FOR YOUR PURCHASE!", SCREEN_WIDTH - 2) << "!" << endl;
        cout << "!" << centerText("Heart of the Cards Store - Since 2025", SCREEN_WIDTH - 2) << "!" << endl;
        drawBorderThick();
    }

    void cleanup() {
        for (Product* p : inventory) {
            delete p;
        }
        for (CartItem* item : cart) {
            delete item;
        }
    }

public:
    HotC() {
        initializeInventory();
    }

    ~HotC() {
        cleanup();
    }

    void run() {
        drawBorderTop();
        cout << "!" << centerText("WELCOME TO HEART OF THE CARDS STORE", SCREEN_WIDTH - 2) << "!" << endl;
        drawBorderBottom();
        cout << endl;

        // Customer information
        string customerName, customerAddress, customerContact;
        cout << "CUSTOMER NAME: ";
        getline(cin, customerName);
        cout << "CUSTOMER ADDRESS: ";
        getline(cin, customerAddress);
        cout << "CUSTOMER CONTACT NUMBER: ";
        getline(cin, customerContact);
        cout << endl;

        bool shopping = true;
        while (shopping) {
            cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << centerText("MAIN MENU", 78) << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "[1] View All Products" << endl;
            cout << "[2] View Cards Only" << endl;
            cout << "[3] View Packs Only" << endl;
            cout << "[4] Add Item to Cart" << endl;
            cout << "[5] View Cart" << endl;
            cout << "[6] Proceed to Checkout" << endl;
            cout << "[7] Exit" << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1:
                    displayAllProducts();
                    break;
                case 2:
                    displayProductsByCategory("CARD");
                    break;
                case 3:
                    displayProductsByCategory("PACK");
                    break;
                case 4:
                    addToCart();
                    break;
                case 5:
                    viewCart();
                    break;
                case 6:
                    if (cart.empty()) {
                        cout << "\n⚠ Your cart is empty! Please add items first." << endl;
                    } else {
                        checkout(customerName, customerAddress, customerContact);
                        shopping = false;
                    }
                    break;
                case 7:
                    cout << "\nThank you for visiting Heart of the Cards Store!" << endl;
                    shopping = false;
                    break;
                default:
                    cout << "\n⚠ Invalid choice! Please try again." << endl;
            }
        }
    }
};

int main() {
    HotC store;
    store.run();
    return 0;
}
