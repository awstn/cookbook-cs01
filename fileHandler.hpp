#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "ADT.hpp"

using namespace std;


vector<Recipe> readFile(const string&);
void writeFile(const string&, const Recipe&, const bool);
Recipe convertToRecipe(const string&);

