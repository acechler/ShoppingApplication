#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>

struct Product {
    std::string name;
    double price = 0;
    int quantity = 0;
};

struct Menu {
    std::string title;
    std::string instructions;
    std::unordered_map<int, Product> items;
    bool active;
};

class ShoppingApplication {
private:
    void populateMenu(Menu& menu) {
        // Add products to the menu
        menu.title = { "Available Products" };
        menu.items = {
            {1, {"Product 1", 10.99, 5}},
            {2, {"Product 2", 5.99, 10}},
            {3, {"Product 3", 8.99, 3}},
            // Add more products as needed
        };
        menu.active = { true };
    }

    void displayMenu(const Menu& menu) const {
        std::cout << menu.title << std::endl << std::endl;
        std::cout << menu.instructions << std::endl;

        for (const auto& item : menu.items) {
            const Product& product = item.second;
            std::cout << item.first << ". " << product.name << " - $" << product.price << " (" << product.quantity << " left)" << std::endl;
        }
    }

    // Handles user input extraction
    int getUserInput(const std::string& prompt, const std::regex& validationRegex) const {
        std::string input;
        std::cout << prompt;
        std::getline(std::cin, input);
        while (!std::regex_match(input, validationRegex) || input.empty() || input.find_first_not_of(' ') == std::string::npos) {
            std::cout << "Invalid input. Try again: ";
            std::getline(std::cin, input);
        }
        return std::stoi(input);
    }

public:
    void run() {
        bool programState = true;

        const std::regex inputValidationRegex(R"(\d+)");
        Menu mainMenu{};
        populateMenu(mainMenu);

        while (programState) {
            while (mainMenu.active) {
                displayMenu(mainMenu);
                int selectedOption = getUserInput("Enter your choice: ", inputValidationRegex);

                while (mainMenu.items.find(selectedOption) == mainMenu.items.end()) {
                    std::cout << "Invalid option. Try again: ";
                    selectedOption = getUserInput("Enter your choice: ", inputValidationRegex);
                }

                const Product& selectedProduct = mainMenu.items[selectedOption];
                
                // !! Trying to get the quantity of requested item !!
                int selectedOption = getUserInput("How many: ", inputValidationRegex);

                mainMenu.items[selectedOption].quantity -= 1;
                // Perform actions based on the selected product (e.g., add to cart, update quantity, etc.)
                
                mainMenu.active = false;
            }

            std::cout << "Do you want to by another item?" << std::endl;
            int selectedOption = getUserInput("Enter your choice: ", inputValidationRegex);
            switch (selectedOption)
            {
            case 1:
                mainMenu.active = true;
                break;
            case 2:
                programState = false;
            default:
                break;
            }

           
        }
    }
};

int main() {
    
    ShoppingApplication app;
    app.run();
    return 0;
}
