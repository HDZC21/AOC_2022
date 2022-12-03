#include <iostream>
#include <fstream>
#include <string>
#include <set>

int CalculateAddedScore(char input);

int main()
{
  std::ifstream inputFile;
  inputFile.open("input.txt");
  
  std::string currentLine;

  std::set<char> firstHalfSet;
  std::set<char> secondHalfSet;

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

      std::pair<std::set<char>::iterator, bool> insertFirstHalfResult;
      std::pair<std::set<char>::iterator, bool> insertSecondHalfResult;

      for (int i = 0; i < secondHalf.length(); i++)
      {
        char charToAdd = secondHalf.at(i);
        insertFirstHalfResult = firstHalfSet.insert(charToAdd);
        insertSecondHalfResult = secondHalfSet.insert(charToAdd);

        if ((insertFirstHalfResult.second == false) &&
            (insertSecondHalfResult.second == true))
        {
          sumOfPriorities += CalculateAddedScore(charToAdd);
          break;
        }
      }

      firstHalfSet.clear();
      secondHalfSet.clear();
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