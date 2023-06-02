// ShoppingApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>

struct UserAccount {
	std::string username;
	double balance;
};

struct Product {
	std::string name;
	double price;
	int quantity;
};

struct Menu {
	std::string title;
	std::string instructions;
	std::unordered_map<int, std::string> options;
	bool active;
};

void displayMenu(const Menu& menu) {
	std::cout << menu.title << std::endl << std::endl;
	std::cout << menu.instructions << std::endl;
	for (const auto& option : menu.options) {
		std::cout << option.first << " " << option.second << std::endl;
	}
}

// Handles user input extraction
int getUserInput(const std::string& prompt, const std::regex& validationRegex) {
	std::string input;
	std::cout << prompt;
	std::getline(std::cin, input);
	while (!std::regex_match(input, validationRegex)) {
		std::cout << "Invalid input. Try again: ";
		std::getline(std::cin, input);
	}
	return std::stoi(input);
}

int main() {

	bool programState = true;

	// Accept input from keyboard if values are 0-9
	const std::regex inputValidationRegex(R"(\d+)");
	Menu mainMenu{
		"Kroger",
		"Select an option.",
		{
			{1, "Start"},
			{2, "Exit"}
		},
		true
	};


	while (programState == true){
		// When the main menu is active, display it and get user input.
		while (mainMenu.active) {
			// Display menu options to user and get their input.
			displayMenu(mainMenu);
			int selectedOption = getUserInput("Enter your choice: ", inputValidationRegex);

			// If the user selects an option that is not in the menu, display an error message and prompt them again.
			while (mainMenu.options.find(selectedOption) == mainMenu.options.end()) {
				std::cout << "Invalid option. Try again: ";
				selectedOption = getUserInput("Enter your choice: ", inputValidationRegex);
			}
			std::cout << "The " << mainMenu.options[selectedOption] << " menu has been selected." << std::endl;

			// Toggle main menu off.
			mainMenu.active = false;
		}
		programState = false;
	}
	return 0;
}

