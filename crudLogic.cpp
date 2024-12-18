#include "crudLogic.hpp"

/*******************************************************************************
 * Description: Create a recipe object through user input
 *
 * Input: App will prompt the user for the characteristics of the recipe
 *
 * Output: Recipe object
*******************************************************************************/
void recipeFactory(const vector<Recipe>& userCookbook, const string& filename, Recipe userRecipe)
{
	string userInput;
	cout << "List your ingredients. Enter 0 when you are done\n";
	// going from cin --> getline
	cin.ignore();

	while (true)
	{
		getline(cin, userInput);

		if (userInput == "0")
		{
			break;
		}
		userRecipe.ingredients.push_back(userInput);
	}

	cout << "Enter the instructions. Enter 0 when you are done\n";

	while (true)
	{
		getline(cin, userInput);

		if (userInput == "0")
		{
			break;
		}
		userRecipe.instructions.push_back(userInput);
	}

	cout << "Enter estimated prep time:";
	cin >> userRecipe.prepTime;

	cout << "Enter estimated cooking time:";
	cin >> userRecipe.cookingTime;

	writeFile(filename, userRecipe, false);
}

/*******************************************************************************
 * Description: prints all the recipes in the user's cookbook
 *
 * Input: none
 *
 * Output: prints all out recipe formatted for the user
*******************************************************************************/
void printAllRecipes(vector<Recipe> recipes)
{
	cout << "********* R E C I P E S ***********\n";
	for (Recipe recipe : recipes)
	{
		printRecipe(recipe);
	}
	cout << "*******************************\n";
}

/*******************************************************************************
 * Description: print recipe for user to see
 *
 * Input: recipe object
 *
 * Output: prints out recipe formatted for the user
*******************************************************************************/
void printRecipe(const Recipe& recipe)
{
	cout << "===================================\n"
	 	 << "-----------------------------------\n"
	     << "Name: " << recipe.name << endl
		 << "Prep Time: " << recipe.prepTime << endl
		 << "Cook Time: " << recipe.cookingTime << endl
		 << "Recipe Type: " << recipeToString(recipe.recipeType) << endl;

	cout << "\nIngredients:\n";
	for (string ingredient : recipe.ingredients)
	{
		cout << "   - " << ingredient << endl;
	}

	cout << "\nInstructions:\n";
	int i = 1;
	for (string instructions : recipe.instructions)
	{
		cout << "   Step " << i << ": " << instructions << endl;
		i++;
	}
	cout << "-----------------------------------\n";
}

/*******************************************************************************
 * Description: This will find a return a user specified recipe object
 *
 * Input: userinput which will be the name of the recipe and the usercookbook vector
 *
 * Output: the recipe object, if none was found, it will return a recipe object
 * 		   with the attributes as null
*******************************************************************************/
Recipe getSpecificRecipe(const string& userInput, const vector<Recipe> userCookbook)
{
    for(Recipe recipe : userCookbook)
    {
        string recipeName = recipe.name;
        string inputName = userInput;

        // Convert recipeName to lowercase
        for(char& c : recipeName)
        {
            c = tolower(c);
        }

        // Convert userInput to lowercase
        for(char& c : inputName)
        {
            c = tolower(c);
        }

        if(recipeName == inputName)
        {
            return recipe;
        }
    }
	// create a null recipe to return
    Recipe nullRecipe;
    nullRecipe.name = "";
    nullRecipe.prepTime = -1;
    nullRecipe.cookingTime = -1;
    nullRecipe.recipeType = static_cast<RecipeType>(1);

    return nullRecipe;
}


/*******************************************************************************
 * Description: This will update a specific recipe that is already
 * 				found in the cookbook
 *
 * Input: user input will be the name of the recipe, usercookbook vector, filename
 *
 * Output: a bool value telling the program whether or not the update was successful
*******************************************************************************/
bool updateSpecificRecipe(const string& userInput, vector<Recipe>& userCookbook, const string& filename)
{
	// Find recipe index in cookbook
	int recipeIndex = -1;
	for(int i = 0; i < userCookbook.size(); i++)
	{
		string recipeName = userCookbook[i].name;
		string searchName = userInput;

		// Convert both to lowercase for comparison
		for(char& c : recipeName)
			c = tolower(c);
		for(char& c : searchName)
			c = tolower(c);

		if(recipeName == searchName)
		{
			recipeIndex = i;
			break;
		}
	}

    // Could not find recipe
    if(recipeIndex == -1)  return false;

    Recipe& foundRecipe = userCookbook[recipeIndex];

    // Recipe not found
    if (foundRecipe.name == "")
    {
        return false;
    }

    int userSelection;
    do
    {
        cout << "What would you like to update?\n"
             << "1. Name\n"
             << "2. Prep Time\n"
             << "3. Cooking Time\n"
             << "4. Recipe Type\n"
             << "5. Ingredients\n"
             << "6. Instructions\n"
             << "0. Exit\n"
             << "Enter your choice: ";

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

        cin.ignore();

        switch(userSelection)
        {
            case 1:
            {
                cout << "Enter new name: ";
                string newName;
                getline(cin, newName);
                foundRecipe.name = newName;
                break;
            }
            case 2:
            {
                cout << "Enter new prep time: ";
                cin >> foundRecipe.prepTime;
                break;
            }
            case 3:
            {
                cout << "Enter new cooking time: ";
                cin >> foundRecipe.cookingTime;
                break;
            }
            case 4:
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

                foundRecipe.recipeType = getRecipeType(typeChoice);
                break;
            }
            case 5:
            {
                cout << "Current ingredients:\n";
                for(const string& ingredient : foundRecipe.ingredients)
                {
                    cout << "- " << ingredient << endl;
                }

                foundRecipe.ingredients.clear();
                cout << "Enter new ingredients (enter 0 when finished):\n";
                string ingredient;
                while(true)
                {
                    getline(cin, ingredient);
                    if(ingredient == "0") break;
                    foundRecipe.ingredients.push_back(ingredient);
                }
                break;
            }
            case 6:
            {
                cout << "Current instructions:\n";
                int step = 1;
                for(const string& instruction : foundRecipe.instructions)
                {
                    cout << step++ << ". " << instruction << endl;
                }

                foundRecipe.instructions.clear();
                cout << "Enter new instructions (enter 0 when finished):\n";
                string instruction;

                while(true)
                {
                    getline(cin, instruction);
                    if(instruction == "0") break;
                    foundRecipe.instructions.push_back(instruction);
                }
                break;
            }
            case 0:
            	return false;
            	break;
            default:
                cout << "Invalid selection.\n";
        }

        updateCookbook(filename, userCookbook);
        break;
    } while(true);

    return true;
}


/*******************************************************************************
 * Description: update the cookbook and text file
 *
 * Input: filename and the usercookbook
 *
 * Output: none
*******************************************************************************/
void updateCookbook(const string& filename, vector<Recipe>& userCookbook)
{
    // First recipe overwrites the file (clears it first)
    if (!userCookbook.empty())
    {
        writeFile(filename, userCookbook.at(0), true);

        // Remaining recipes append to the file
        for(int i = 1; i < userCookbook.size(); i++)
        {
            writeFile(filename, userCookbook.at(i), false);
        }
    }
}

/*******************************************************************************
 * Description: delete recipe from the vector and upate the cookbook
 *
 * Input: usercookbook vector and the filename
 *
 * Output: n/a
*******************************************************************************/
void deleteRecipeFromVectorAndUpdate(const Recipe& recipe, vector<Recipe>& userCookbook, const string& filename)
{
	string nameToBeDeleted = recipe.name;

	vector<Recipe> copyCookbook = userCookbook;

	userCookbook.push_back(recipe);
	printAllRecipes(userCookbook);

	deleteRecipeFromVector(recipe, userCookbook);

	userCookbook.pop_back();
	printAllRecipes(userCookbook);

	updateCookbook(filename, userCookbook);
}


/*******************************************************************************
 * Description: delete recipe from the vector and upate the cookbook
 *
 * Input: usercookbook vector and the filename
 *
 * Output: n/a
*******************************************************************************/
vector<Recipe> deleteRecipeFromVector(const Recipe& recipe, vector<Recipe>& userCookbook)
{
	vector<Recipe> firstHalf;
	vector<Recipe> secondHalf;
	int cutOffIndex;

	// Get the cut off index, which will split the vector into
	// two halves. The cut off is the recipe that is to be deleted
	for (int i = 0; i < userCookbook.size(); i++)
	{
		if (recipe.name == userCookbook.at(i).name)
		{
			cutOffIndex = i;
			break;
		}
	}

	// Populate firstHalf vector with first half of userCookbook
	for (int i = 0; i < cutOffIndex; i++)
	{
		firstHalf.push_back(userCookbook.at(i));
	}
	// Populate secondHalf vector with second half of userCookbook
	for (int i = cutOffIndex + 1; i < userCookbook.size(); i++)
	{
		secondHalf.push_back(userCookbook.at(i));
	}

	// clear the vector, to populate a fresh vector
	userCookbook.clear();
	int combinedSize = firstHalf.size() + secondHalf.size();
	int firstHalfSize = firstHalf.size();

	// repopulate userCookbook vector with the first and second vectors
	for (int i = 0; i < combinedSize; i++)
	{
		if (i < firstHalf.size())
		{
			userCookbook.push_back(firstHalf.at(i));
		}
		else
		{
			userCookbook.push_back(secondHalf.at(i - firstHalfSize));
		}
	}

	return userCookbook;
}

/*******************************************************************************
 * Description: Print out recipes by certain type
 *
 * Input: userCookbook that is stored as a vector. user input that will match that
 * 		  input to find the corresponding recipe
 *
 * Output: a print out statement for the user to see the list of recipes
*******************************************************************************/
void listRecipesByType(const vector<Recipe>& userCookbook, const int userInput)
{
	cout << "***** " << recipeToString(userInput) << " ****\n"
		 << "********* R E C I P E S ***********\n";
	for (Recipe recipe : userCookbook)
	{
		if (recipe.recipeType == userInput) printRecipe(recipe);
	}
	cout << "*******************************\n";

}

/*******************************************************************************
 * Description: convert int to RecipeType enum
 *
 * Input: userInput integer
 *
 * Output: RecipeType data type
*******************************************************************************/
RecipeType getRecipeType(int userInput)
{
	if (userInput == 1) return BREAKFAST;
	else if (userInput == 2) return LUNCH;
	else if (userInput == 3) return SNACK;
	else if (userInput == 4) return DINNER;
	else return BREAKFAST;
}

/*******************************************************************************
 * Description: convert userInput to string
 *
 * Input: userInput integer
 *
 * Output: string data type
*******************************************************************************/
string recipeToString(const int userInput)
{
	if (userInput == 1) return "BREAKFAST";
	else if (userInput == 2) return "LUNCH";
	else if (userInput == 3) return "SNACK";
	else if (userInput == 4) return "DINNER";
	else return "UNKNOWN";
}

