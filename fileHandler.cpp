
#include "fileHandler.hpp"

/*******************************************************************************
 * Description: reads the file and adds the contents to a vector
 *
 * Input: filename
 *
 * Output: a vector of recipes
*******************************************************************************/
vector<Recipe> readFile(const string& fileName)
{
	vector<Recipe> recipes;
	// create INPUT the file stream object
	ifstream inputFile;
	inputFile.open(fileName);

	// if file fails to open
	if (inputFile.fail())
	{

		cout << "Could not open file /:\nCreating a new file!\n";
	}
	else
	{
		string line;
		while (getline(inputFile, line))
		{
			Recipe recipe = convertToRecipe(line);
			recipes.push_back(recipe);
		}
	}
	inputFile.close();
	return recipes;
}

/*******************************************************************************
 * Description: write to the file
 *
 * Input: filename, userRecipe object, and a bool value to open the
 * 		  file in append mode or not
 *
 * Output: user updated file
*******************************************************************************/
void writeFile(const string& fileName, const Recipe& userRecipe, const bool overwrite)
{
	// Create OUTPUT file stream object
	ofstream outputFile;

	if (!overwrite)
	{
		// open in append mode to avoid overwriting
		outputFile.open(fileName, ios::app);
	}
	else
	{
		// overwrite the file!!
		outputFile.open(fileName);
	}

	if (!outputFile)
	{
		cout << "Error opening file!\n";
		return;
	}

	// using pipe character to delimit the Recipe attributes
	outputFile << userRecipe.name << "|";
	outputFile << userRecipe.prepTime << "|";
	outputFile << userRecipe.cookingTime << "|";
	outputFile << (userRecipe.recipeType) << "|";

	// Writing ingredients (delimited by -)
	for (int i = 0; i < userRecipe.ingredients.size(); i++)
	{
		outputFile << userRecipe.ingredients.at(i);
		// Check if it is at the last ingredient
		// If not, add the delimiter character (-)
		if (i < userRecipe.ingredients.size() - 1)
		{
			outputFile << "-";
		}
	}

	outputFile << "|";
	for (int i = 0; i < userRecipe.instructions.size(); i++)
	{
		outputFile << userRecipe.instructions.at(i);

		// Check if it is at the last ingredient
		// If not, add the - character
		if (i < userRecipe.instructions.size() - 1)
		{
			outputFile << "-";
		}
	}
	// Next recipe added will be on a new line
	outputFile << endl;
	outputFile.close();
}

/*******************************************************************************
 * Description: converts the string line to a recipe object
 *
 * Input: a string line from the text file
 *
 * Output: a recipe object
*******************************************************************************/
Recipe convertToRecipe(const string& line)
{
	// Popcorn chicken|10|20|3|chicken-breading-butter-garlic-soy sauce|cook chicken-fry check-bread chicken-cry
	Recipe recipe;
	size_t index = 0;
	size_t nextIndex;

	// Get name
	// Find index of first delimiter
	nextIndex = line.find('|');
	// Extract substring from line
	recipe.name = line.substr(index, nextIndex - index);
	// update index
	index = nextIndex + 1;

	// Get prep time
	nextIndex = line.find('|', index);
	// convert string to int
	recipe.prepTime = stoi(line.substr(index, nextIndex - index));
	index = nextIndex + 1;

	// Get cook time
	nextIndex = line.find('|', index);
	recipe.cookingTime = stoi(line.substr(index, nextIndex - index));
	index = nextIndex + 1;

	// Get recipe type
	nextIndex = line.find('|', index);
	recipe.recipeType = static_cast<RecipeType>(stoi(line.substr(index, nextIndex - index)));
	index = nextIndex + 1;

	// Get ingredient string
	size_t ingredientStart = 0;
	size_t ingredientEnd;

	nextIndex = line.find('|', index);
	string ingredientString = line.substr(index, nextIndex - index);
	index = nextIndex + 1;

	while ((ingredientEnd = ingredientString.find('-', ingredientStart)) != string::npos)
	{
		recipe.ingredients.push_back(ingredientString.substr(ingredientStart, ingredientEnd - ingredientStart));
		// update index
		ingredientStart = ingredientEnd + 1;
	}

	// Add last ingredient
	if (ingredientStart < ingredientString.length())
	{
		recipe.ingredients.push_back(ingredientString.substr(ingredientStart));
	}

    // Get and parse instructions
    size_t instructionStart = 0;
    size_t instructionEnd;

    string instructionString = line.substr(index);
    index = index + 1;

    while ((instructionEnd = instructionString.find('-', instructionStart)) != string::npos)
    {
        recipe.instructions.push_back(instructionString.substr(instructionStart, instructionEnd - instructionStart));
        instructionStart = instructionEnd + 1;
    }

    // Add last instruction
    if (instructionStart < instructionString.length())
    {
        recipe.instructions.push_back(instructionString.substr(instructionStart));
    }
	return recipe;
}
