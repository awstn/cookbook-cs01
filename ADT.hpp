#include <string>
#include <vector>

using namespace std;

enum RecipeType
{
	BREAKFAST = 1, LUNCH = 2, SNACK = 3, DINNER = 4
};


struct Recipe
{
	string name;
	int prepTime;
	int cookingTime; // minutes
	RecipeType recipeType;
	vector<string> ingredients;
	vector<string> instructions;
};


