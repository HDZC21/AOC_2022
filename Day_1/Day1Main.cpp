#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
  std::vector<int> elfCalories;

  std::ifstream inputFile;
  inputFile.open("input.txt");

  std::string currentLine;

  if (inputFile.is_open()) 
  {
    int currentElfCalories = 0;
    while(getline(inputFile, currentLine))
    {
      if (currentLine != "")
      {
        currentElfCalories += std::stoi(currentLine);
      }
      else
      {
        elfCalories.push_back(currentElfCalories);
        currentElfCalories = 0;
      }
    }
  }
  inputFile.close();

  std::sort(elfCalories.begin(), elfCalories.end(), std::greater<int>());

  std::cout << "Most Calories = " << elfCalories.at(0) << std::endl;
  std::cout << "Top Three Calorie Sum = " << (elfCalories.at(0) + elfCalories.at(1) + elfCalories.at(2)) << std::endl;
}