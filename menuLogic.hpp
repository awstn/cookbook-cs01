#include "crudLogic.hpp"
#include <vector>


void welcomeDialogue(vector<Recipe>&, const string&);
void getUserSelection(const int& userInput, vector<Recipe>&, const string&);
void createRecipe(vector<Recipe>&, const string&);
void getRecipe(const vector<Recipe>&);
void getRecipeByType(const vector<Recipe>&);
void updateRecipe(vector<Recipe>&, const string&);
void deleteRecipe(vector<Recipe>&, const string&);
