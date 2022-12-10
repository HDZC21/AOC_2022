#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
  std::ifstream inputFile;
  inputFile.open("input.txt");
  
  std::string currentLine;
  int xVal = 1;

  std::vector<char> crtDisplay (240, ' ');

  int sumSigStrengths = 0;
  bool midAdding = false;
  int numToAdd;
  
  if (inputFile.is_open()) 
  {
    for (int i = 0; i < crtDisplay.size(); i++)
    {
      int crtPos = i % 40;
      if ((xVal == crtPos ) || (xVal - 1 == crtPos) || (xVal + 1 == crtPos))
      {
        crtDisplay.at(i) = '#';
      }

      if (midAdding == true)
      {
        xVal += numToAdd;
        midAdding = false;
        continue;
      }
      else
      {
        getline(inputFile, currentLine);
        if (currentLine.at(0) == 'a')
        {
          numToAdd = std::stoi(currentLine.substr(5, 3));
          midAdding = true;
        }
      }
    }
  }
  
  inputFile.close();

  // Print Output
  for (int i = 0; i < crtDisplay.size(); i++)
  {
    std::cout << crtDisplay.at(i);

    if ((i + 1) % 40 == 0)
    {
      std::cout << std::endl;
    }
  }
}