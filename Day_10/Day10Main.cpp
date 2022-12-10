#include <iostream>
#include <fstream>
#include <string>

int main()
{
  std::ifstream inputFile;
  inputFile.open("input.txt");
  
  std::string currentLine;
  int xVal = 1;
  int loopCounter = 1;
  int sumSigStrengths = 0;
  
  if (inputFile.is_open()) 
  {
    while(getline(inputFile, currentLine))
    {
      if (loopCounter % 40 == 20)
      {
        sumSigStrengths += loopCounter * xVal;
      }
      if (currentLine.at(0) == 'a')
      {
        int numToAdd = std::stoi(currentLine.substr(5, 3));
        loopCounter++;
        if (loopCounter % 40 == 20)
        {
          sumSigStrengths += loopCounter * xVal;
        }
        xVal += numToAdd;
      }
      loopCounter++;
    }
  }
  
  inputFile.close();

  std::cout << "Sum of Six Signal Strengths = " << sumSigStrengths << std::endl;
}