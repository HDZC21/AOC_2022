#include <iostream>
#include <fstream>
#include <string>

int DetermineRangeContainment(std::pair<int, int> &elf1, std::pair<int, int> &elf2);
int DetermineRangeOverlap(std::pair<int, int> &elf1, std::pair<int, int> &elf2);

int main()
{
  std::ifstream inputFile;
  inputFile.open("input.txt");
  
  std::string currentLine;

  int sumOfDuplicateRanges = 0;
  int sumofRangeOverlap = 0;

  if (inputFile.is_open()) 
  {
    while(getline(inputFile, currentLine))
    {
      std::pair<int, int> firstElf;
      std::pair<int, int> secondElf;

      std::string firstRange = currentLine.substr(0, currentLine.find(','));
      std::string secondRange = currentLine.substr(currentLine.find(',') + 1, std::string::npos);

      firstElf.first = std::stoi(firstRange.substr(0, firstRange.find('-')));
      firstElf.second = std::stoi(firstRange.substr(firstRange.find('-') + 1, std::string::npos));

      secondElf.first = std::stoi(secondRange.substr(0, secondRange.find('-')));
      secondElf.second = std::stoi(secondRange.substr(secondRange.find('-') + 1, std::string::npos));

      sumOfDuplicateRanges += DetermineRangeContainment(firstElf, secondElf);
      sumofRangeOverlap += DetermineRangeOverlap(firstElf, secondElf);
    }
  }
  inputFile.close();

  std::cout << "Sum Of Fully Contained Ranges = " << sumOfDuplicateRanges << std::endl;
  std::cout << "Sum Of Overlapping Ranges = " << sumofRangeOverlap << std::endl;
}

int DetermineRangeContainment(std::pair<int, int> &elf1, std::pair<int, int> &elf2)
{
  // Case 1 - Does Elf 2 contain Elf 1
  if ((elf1.first >= elf2.first) && (elf1.second <= elf2.second))
  {
    return 1;
  }

  // Case 2 - Does Elf 1 contain Elf 2
  if ((elf2.first >= elf1.first) && (elf2.second <= elf1.second))
  {
    return 1;
  }

  // Case 3 - No range is fully enveloped
  return 0;
}

int DetermineRangeOverlap(std::pair<int, int> &elf1, std::pair<int, int> &elf2)
{
  // Case 1 - Does Elf 2 overlap Elf 1
  if (((elf1.first >= elf2.first) && (elf1.first <= elf2.second)) ||
      ((elf1.second >= elf2.first) && (elf1.second <= elf2.second)))
  {
    return 1;
  }

  // Case 2 - Does Elf 1 overlap Elf 2
  if (((elf2.first >= elf1.first) && (elf2.first <= elf1.second)) ||
      ((elf2.second >= elf1.first) && (elf2.second <= elf1.second)))
  {
    return 1;
  }

  // Case 3 - No overlap
  return 0;
}