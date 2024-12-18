#include "menuLogic.hpp"
#include <iostream>
#include <cctype>

using namespace std;

/*******************************************************************************
 * Description: the initial startup screen for the user
 *
 * Input: filename and usercookbook vector
 *
 * Output: on screen text for the user
*******************************************************************************/
void welcomeDialogue(vector<Recipe>& userCookbook, const string& filename)
{
    int userSelection = 0;
    while (true) // Main program loop
    {
        // Refresh cookbook and size at start of each iteration
        userCookbook = readFile(filename);
        int cookbookSize = userCookbook.size();

        if (cookbookSize == 0)
        {
            cout << "You have no recipes in your cookbook!\n"
                 << "\t1. Add a recipe!\n"
                 << "\t0. Exit\n";

            cin >> userSelection;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(4096, '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            if (userSelection < 0 || userSelection > 1)
            {
                cout << "Please select a valid option (0-1)\n";
                continue;
            }
            if (userSelection == 0)
                break;
            getUserSelection(userSelection, userCookbook, filename);
        }
        else
        {
            cout << "Hello! Select your option, by entering the corresponding number\n"
                 << "\t1. Add a recipe\n"
                 << "\t2. Find a specific recipe\n"
                 << "\t3. List recipe by type\n"
                 << "\t4. List all recipes\n"
                 << "\t5. Update a recipe\n"
                 << "\t6. Delete a recipe\n"
                 << "\t0. Exit\n";

            cin >> userSelection;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(4096, '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            if (userSelection < 0 || userSelection > 6)
            {
                cout << "Please select a valid option (0-6)\n";
                continue;
            }

            if (userSelection == 0)
                break;

            getUserSelection(userSelection, userCookbook, filename);
        }
    }
    cout << "Goodbye!\n";
}

/*******************************************************************************
 * Description: this handles the user selection logic
 *
 * Input: userselection, usercookbook, and the filename
 *
 * Output: n/a
*******************************************************************************/
void getUserSelection(const int& userSelection, vector<Recipe>& userCookbook, const string& filename)
{
	switch(userSelection)
	{
		case 1:
	/*crud*/createRecipe(userCookbook, filename);
			break;
		case 2:
			getRecipe(userCookbook);
			break;
		case 3:
			getRecipeByType(userCookbook);
			break;
		case 4:
			printAllRecipes(userCookbook);
			break;
		case 5:
			updateRecipe(userCookbook, filename);
			break;
		case 6:
			deleteRecipe(userCookbook, filename);
			break;
		case 0:
			cout << "Goodbye\n";
			return;
			break;
		default:
			cout << "====Oh no error!===";
			return;
			break;
	}
}

/*******************************************************************************
 * Description: This will prompt the user to create a recipe object
 *
 * Input: the usercookbook vector and the filename
 *
 * Output: n/a
*******************************************************************************/
void createRecipe(vector<Recipe>& userCookbook, const string& filename)
{
	Recipe userRecipe;
	int userRecipeType;
	string userInput;

	cout << "Enter name of the recipe:";

	cin.ignore();
	getline(cin, userRecipe.name);

	cout << "What type of recipe is this?\n"
		 << "\t1. Breakfast\n"
	 	 << "\t2. Lunch\n"
	 	 << "\t3. Snack\n"
	 	 << "\t4. Dinner\n";

	cin >> userRecipeType;

	userRecipe.recipeType = getRecipeType(userRecipeType);

	recipeFactory(userCookbook, filename, userRecipe);
}


/*******************************************************************************
 * Description: This will call the get functions from crudlogic.cpp
 *
 * Input: the usercookbook vector
 *
 * Output: n/a
*******************************************************************************/
void getRecipe(const vector<Recipe>& userCookbook)
{
	string userInput;
	Recipe userRequestedRecipe;
	cout << "Enter the name: ";
	cin.ignore();
	getline(cin, userInput);

	userRequestedRecipe = getSpecificRecipe(userInput, userCookbook);

	if (userRequestedRecipe.name != "") printRecipe(userRequestedRecipe);
}

/*******************************************************************************
 * Description: this will get the recipe by type from the cookbook vector
 *
 * Input: usercookbook
 *
 * Output: a print out statement for the user
*******************************************************************************/
void getRecipeByType(const vector<Recipe>& userCookbook)
{
    int typeChoice;
    do {
        cout << "Select recipe type:\n"
             << "1. Breakfast\n"
             << "2. Lunch\n"
             << "3. Snack\n"
             << "4. Dinner\n"
             << "Enter your choice: ";

        cin >> typeChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(4096, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        // Clear input buffer after successful read
        cin.ignore(4096, '\n');

        if (typeChoice < 1 || typeChoice > 4)
        {
            cout << "Please select a valid option (1-4)\n";
            continue;
        }

        break;  // Valid input received, exit loop

    } while(true);

    listRecipesByType(userCookbook, typeChoice);
}

/*******************************************************************************
 * Description: This will call the update functions from crudlogic
 *
 * Input: usercookbook vector and the filename
 *
 * Output: this will update the user specified recipe
*******************************************************************************/
void updateRecipe(vector<Recipe>& userCookbook, const string& filename)
{
	string userInput;
	Recipe userRequestedRecipe;
	cout << "Enter the name of the recipe you want to update: ";
	cin.ignore();
	getline(cin, userInput);

	if (getSpecificRecipe(userInput, userCookbook).name == "")
	{
		cout << "Could not find recipe with that name ):\n";
		return;
	}

	if (updateSpecificRecipe(userInput, userCookbook, filename))
	{
		cout << "Update successful\n";
	}
	else
	{
		cout << "Update unsuccessful):\n";
	}

	// refresh
	updateCookbook(filename, userCookbook);
}

/*******************************************************************************
 * Description: this will call the crudlogic delete functions
 *
 * Input: usercookbook vector and filename
 *
 * Output: delete the user specified recipe
*******************************************************************************/
void deleteRecipe(vector<Recipe>& userCookbook, const string& filename)
{
	string userInput;
	Recipe userRequestedRecipe;
	cout << "Enter the name of the recipe you want to delete: ";
	cin.ignore();
	getline(cin, userInput);

	userRequestedRecipe = getSpecificRecipe(userInput, userCookbook);
	string userName = userRequestedRecipe.name;

	if (userName == "")
	{
		cout << "Cannot find recipe\n";
		return;
	}

	deleteRecipeFromVectorAndUpdate(userRequestedRecipe, userCookbook, filename);
	cout << userName << " has been deleted successfully\n";
}





