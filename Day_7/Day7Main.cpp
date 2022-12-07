#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>

struct Directory_t;

struct File_t
{
  Directory_t* parentDir;
  long fileSize;
};

struct Directory_t
{
  Directory_t* parentDir;
  
  std::vector<Directory_t*> childDirs;
  std::vector<File_t> files;
  
  int currentIdx = 0;
  long dirSize = 0;
};

long DetermineDirectorySizes(Directory_t* currentDir);
void OutputAllDirsSmallerThanX(Directory_t* currentDir, long &output);
void FindDirSizeToDelete(Directory_t* currentDir, long &sizeReq, long &output);

int main()
{
  std::ifstream inputFile;
  inputFile.open("input.txt");
  
  std::string currentLine;

  // Skip two lines (always a change to root Dir and ls)
  getline(inputFile, currentLine);
  getline(inputFile, currentLine);

  // Create root dir
  Directory_t rootDir;
  rootDir.parentDir = nullptr;

  Directory_t* currentDir = &rootDir;
  
  if (inputFile.is_open()) 
  {
    while(getline(inputFile, currentLine))
    {
      if (currentLine.at(0) == '$')
      {
        if (currentLine.at(2) == 'c')
        {
          if (currentLine.at(5) != '.')
          {
            currentDir = currentDir->childDirs.at(currentDir->currentIdx);
          }
          else // Come back out of Directory
          {
            currentDir = currentDir->parentDir;
            currentDir->currentIdx += 1;
          }
        }
        else 
        {
          // ls, so do nothing
        }
      }
      else if (currentLine.find("dir ") != std::string::npos)
      {
        // Create a DIR entry
        Directory_t* dirEntry = new Directory_t;
        dirEntry->parentDir = currentDir;
        currentDir->childDirs.push_back(dirEntry);
      }
      else
      {
        // It's a file
        File_t newFile;
        newFile.parentDir = currentDir;
        newFile.fileSize = std::stoll(currentLine.substr(0, currentLine.find(' ')));
        currentDir->dirSize += newFile.fileSize;
        currentDir->files.push_back(newFile);
      }
    }
  }

  inputFile.close();

  currentDir = &rootDir;
  long rootDirSize = DetermineDirectorySizes(currentDir);
  
  long finalOutput = 0;
  OutputAllDirsSmallerThanX(currentDir, finalOutput);

  std::cout << "Final Sum of Directories = " << finalOutput << std::endl;

  long unusedSpace = 70000000 - rootDirSize;
  long spaceRequired = 30000000 - unusedSpace;
  long dirSizeToDelete = LONG_MAX;

  FindDirSizeToDelete(currentDir, spaceRequired, dirSizeToDelete);

  std::cout << "Size of Directory to Delete = " << dirSizeToDelete << std::endl;

}

long DetermineDirectorySizes(Directory_t* currentDir)
{
  for (int i = 0; i < currentDir->childDirs.size(); i++)
  {
    currentDir->dirSize += DetermineDirectorySizes(currentDir->childDirs.at(i));
  }
  return currentDir->dirSize;
}

void OutputAllDirsSmallerThanX(Directory_t* currentDir, long &output)
{
  for (int i = 0; i < currentDir->childDirs.size(); i++)
  {
    OutputAllDirsSmallerThanX(currentDir->childDirs.at(i), output);
  }
  
  if (currentDir->dirSize <= 100000)
  {
    output += currentDir->dirSize;
  }
}

void FindDirSizeToDelete(Directory_t* currentDir, long &sizeReq, long &output)
{
  for (int i = 0; i < currentDir->childDirs.size(); i++)
  {
    FindDirSizeToDelete(currentDir->childDirs.at(i), sizeReq, output);
  }
  
  if ((currentDir->dirSize < output) && (currentDir->dirSize >= sizeReq))
  {
    output = currentDir->dirSize;
  }
}