#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
  std::ifstream inputFile;
  inputFile.open("input.txt");
  
  std::string inputLine;
  getline(inputFile, inputLine);
  inputFile.close();

  int answer;
  bool answerFound = false;

  std::vector<int> seenChars (26, 0);
  std::vector<bool> onlyOne (26, true);
  bool atFourteen = false;
  bool pastFourteen = false;

  while (answerFound == false)
  {
    for (int i = 0; i < inputLine.length(); i++)
    {
      int currentVal = inputLine.at(i) - 97;
      if (i == 13)
      {
        atFourteen = true;
      }
      if (i == 14)
      {
        pastFourteen = true;
      }
      
      seenChars.at(currentVal) += 1;
      if (seenChars.at(currentVal) > 1)
      {
        onlyOne.at(currentVal) = false;
      }
      if (pastFourteen)
      {
        int pastChar = (inputLine.at(i - 14)) - 97;
        seenChars.at(pastChar) -= 1;
        if (seenChars.at(pastChar) < 2)
        {
          onlyOne.at(pastChar) = true;
        }
      }

      if (atFourteen)
      {
        std::vector<bool>::iterator it;
        it = find(onlyOne.begin(), onlyOne.end(), false);
        if (it == onlyOne.end())
        {
          answer = i + 1;
          answerFound = true;
          break;
        }
      }
    }
  }

  std::cout << "First Index of Unique Pattern = " << answer << std::endl;
}

