#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

char DetermineCommonType(std::vector<std::set<char>> &outputSets);
int CalculateAddedScore(char input);

int main()
{
  std::ifstream inputFile;
  inputFile.open("input.txt");

  bool fileReading = true;
  std::string currentLine;

  std::set<char> workingSet;
  std::vector<std::set<char>> elfGroupSets;

  int sumOfPriorities = 0;

  if (inputFile.is_open()) 
  {
    while(fileReading)
    {
      for (int i = 0; i < 3; i++)
      {
        if (getline(inputFile, currentLine))
        {
          for (int j = 0; j < currentLine.length(); j++)
          {
            workingSet.insert(currentLine.at(j));
          }

          elfGroupSets.push_back(workingSet);
          workingSet.clear();
        }
        else
        {
          // Break out of for loop
          fileReading = false;
          break;
        }
      }

      if (fileReading == false)
      {
        // Break out of while loop
        break;
      }

      sumOfPriorities += CalculateAddedScore(DetermineCommonType(elfGroupSets));
      elfGroupSets.clear();
    }
  }
  inputFile.close();

  std::cout << "Sum Of Priorities = " << sumOfPriorities << std::endl;
}

char DetermineCommonType(std::vector<std::set<char>> &outputSets)
{
  std::set<char> firstIntersect;
  std::vector<char> secondIntersect;

  std::set_intersection(outputSets.at(0).begin(), outputSets.at(0).end(), outputSets.at(1).begin(), outputSets.at(1).end(), std::inserter(firstIntersect, firstIntersect.begin()));
  std::set_intersection(firstIntersect.begin(), firstIntersect.end(), outputSets.at(2).begin(), outputSets.at(2).end(), std::inserter(secondIntersect, secondIntersect.begin()));

  return secondIntersect.at(0);
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