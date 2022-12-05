#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

int CalculateAddedScore(char input);

int main()
{
  std::ifstream inputFile;
  inputFile.open("input.txt");
  
  std::string currentLine;

  std::set<char> firstHalfSet;
  std::set<char> secondHalfSet;
  std::vector<char> intersectOutput;

  int sumOfPriorities = 0;

  if (inputFile.is_open()) 
  {
    while(getline(inputFile, currentLine))
    {
      std::string firstHalf = currentLine.substr(0, (currentLine.length() / 2));
      std::string secondHalf = currentLine.substr((currentLine.length() / 2), std::string::npos);

      for (int i = 0; i < firstHalf.length(); i++)
      {
        firstHalfSet.insert(firstHalf.at(i));
      }

      for (int i = 0; i < secondHalf.length(); i++)
      {
        secondHalfSet.insert(secondHalf.at(i));
      }

      std::set_intersection(firstHalfSet.begin(), firstHalfSet.end(), secondHalfSet.begin(), secondHalfSet.end(), std::inserter(intersectOutput, intersectOutput.begin()));

      if (intersectOutput.size() != 0)
      {
        sumOfPriorities += CalculateAddedScore(intersectOutput.at(0));
      }

      firstHalfSet.clear();
      secondHalfSet.clear();
      intersectOutput.clear();
    }
  }
  inputFile.close();

  std::cout << "Sum Of Priorities = " << sumOfPriorities << std::endl;
}

int CalculateAddedScore(char input)
{
  // ASCII
  // A = 65 : Z = 90
  // a = 97 : z = 122

  // Convert to:
  // A = 27 : Z = 52
  // a = 1 : z = 26

  // Difference of 38 for Uppercase
  // Different of 96 for Lowercase

  if ((input >= 65) && (input <= 90))
  {
    // Uppercase
    return input - 38;
    
  }
  else
  {
    // lowerCase
    return input - 96;
  }
  return 0;
}