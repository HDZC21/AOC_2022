#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

char DetermineCommonType(std::vector<std::string> &inputStrings, std::vector<std::set<char>> &outputSets);
char FindUniqueCharacter(std::vector<std::set<char>> &inputSets);
int CalculateAddedScore(char input);

int main()
{
  std::ifstream inputFile;
  inputFile.open("input.txt");

  std::string currentLine;
  std::vector<std::string> elfGroupLines;
  std::vector<std::set<char>> elfGroupSets;

  int sumOfPriorities = 0;

  if (inputFile.is_open()) 
  {
    while(getline(inputFile, currentLine))
    {
      elfGroupLines.push_back(currentLine);
      getline(inputFile, currentLine);
      elfGroupLines.push_back(currentLine);
      getline(inputFile, currentLine);
      elfGroupLines.push_back(currentLine);

      for (int i = 0; i < elfGroupLines.size(); i++)
      {
        std::set<char> workingSet;
        elfGroupSets.push_back(workingSet);
      }

      sumOfPriorities += CalculateAddedScore(DetermineCommonType(elfGroupLines, elfGroupSets));

      elfGroupLines.clear();
      elfGroupSets.clear();
    }
  }
  inputFile.close();

  std::cout << "Sum Of Priorities = " << sumOfPriorities << std::endl;
}

char DetermineCommonType(std::vector<std::string> &inputStrings, std::vector<std::set<char>> &outputSets)
{
  for (int i = 0; i < inputStrings.size(); i++)
  {
    for (int j = 0; j < inputStrings.at(i).length(); j++)
    {
      outputSets.at(i).insert(inputStrings.at(i).at(j));
    }
  }

  std::vector<std::set<char>> intersectionOutputs;
  std::set<char> workingIntersectionSet;

  std::set_intersection(outputSets.at(0).begin(), outputSets.at(0).end(), outputSets.at(1).begin(), outputSets.at(1).end(), std::inserter(workingIntersectionSet, workingIntersectionSet.begin()));
  intersectionOutputs.push_back(workingIntersectionSet);
  workingIntersectionSet.clear();

  std::set_intersection(outputSets.at(0).begin(), outputSets.at(0).end(), outputSets.at(2).begin(), outputSets.at(2).end(), std::inserter(workingIntersectionSet, workingIntersectionSet.begin()));
  intersectionOutputs.push_back(workingIntersectionSet);
  workingIntersectionSet.clear();

  std::set_intersection(outputSets.at(1).begin(), outputSets.at(1).end(), outputSets.at(2).begin(), outputSets.at(2).end(), std::inserter(workingIntersectionSet, workingIntersectionSet.begin()));
  intersectionOutputs.push_back(workingIntersectionSet);
  workingIntersectionSet.clear();

  return FindUniqueCharacter(intersectionOutputs);
}

char FindUniqueCharacter(std::vector<std::set<char>> &inputSets)
{
  char workingChar;
  int shortestSetIdx = 0;
  std::vector<int> otherIdxs;

  // Determine index of smallest set
  int shortestSet = inputSets.at(0).size();
  if (inputSets.at(1).size() <= shortestSet)
  {
    shortestSetIdx = 1;
    otherIdxs.push_back(0);
  }
  if (inputSets.at(2).size() <= shortestSet)
  {
    shortestSetIdx = 2;
  }

  std::set<char> workingSet = inputSets.at(shortestSetIdx);
  inputSets.erase(inputSets.begin() + shortestSetIdx);

  std::pair<std::set<char>::iterator, bool> firstInsert;
  std::pair<std::set<char>::iterator, bool> secondInsert;
  std::set<char>::iterator itr;

  // Determine character that appears in all three sets
  for (itr = workingSet.begin(); itr != workingSet.end(); itr++)
  {
    workingChar = *itr;
    firstInsert = inputSets.at(0).insert(workingChar);
    secondInsert = inputSets.at(1).insert(workingChar);

    if ((firstInsert.second == false) && (secondInsert.second == false))
    {
      return workingChar;
    }
  }

  return 0;
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