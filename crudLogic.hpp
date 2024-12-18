#include "fileHandler.hpp"
#include <vector>
#include <string>
#include <iostream>

//
// Functions pertaining to create actions
//
void recipeFactory(const vector<Recipe>& userCookbook, const string& filename, Recipe userRecipe);
vector<Recipe> initializeCookbook(const string& filename);

//
// Functions pertaining to read actions
//
void readRecipe();
Recipe getSpecificRecipe(const string&, const vector<Recipe>);
void printRecipe(const Recipe&);
void printAllRecipes(const vector<Recipe>);
void listRecipesByType(const vector<Recipe>& userCookbook, const int userInput);


//
// Functions pertaining to update actions
//
bool updateSpecificRecipe(const string& userInput, vector<Recipe>& userCookbook, const string& filename);
void updateCookbook(const string& filename, vector<Recipe>& userCookbook);


//
// Functions pertaining to delete actions
//
void deleteRecipeFromVectorAndUpdate(const Recipe& recipe, vector<Recipe>& userCookbook, const string& filename);
vector<Recipe> deleteRecipeFromVector(const Recipe& recipe, vector<Recipe>& userCookbook);



//
// Recipe function helpers
//
RecipeType getRecipeType(int);
string recipeToString(const int);



