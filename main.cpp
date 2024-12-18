/*
 * main.cpp
 *
 *  Created on: Dec 12, 2024
 *      Author: austinaguilar
 */
#include "menuLogic.hpp"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	string test = "recipeTest2.txt";

	string userInput;
	cout << "Enter the name of the file you want to open/create:";
	cin >> userInput;

	vector<Recipe> userCookbook;

	welcomeDialogue(userCookbook, userInput);


	return 0;
}

