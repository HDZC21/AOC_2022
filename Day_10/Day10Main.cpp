#include <iostream>
#include <fstream>
#include <string>

int main()
{
  std::ifstream inputFile;
  inputFile.open("input.txt");
  
  std::string currentLine;
  
  if (inputFile.is_open()) 
  {
    while(getline(inputFile, currentLine))
    {
      
    }
  }
  
  inputFile.close();

  //std::cout << "Answer = " << answerVar << std::endl;
}