#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

bool DetermineIfTreeVisible(std::vector<std::vector<int>> &map, int i, int j);
int CalculateMaxScenicScore(std::vector<std::vector<int>> &map);

bool lessThan(int a, int b)
{
  return a < b;
}

int main()
{
  std::ifstream inputFile;
  inputFile.open("input.txt");
  
  std::string currentLine;

  int sumVisibleTrees = 0;
  std::vector<std::vector<int>> mapRows;
  
  if (inputFile.is_open()) 
  {
    while(getline(inputFile, currentLine))
    {
      std::vector<int> newRow;
      mapRows.push_back(newRow);

      for(int i = 0; i < currentLine.size(); i++)
      {
        mapRows.back().push_back((int)currentLine.at(i) - 48);
      }
    }
  }

  inputFile.close();

  // Sum up how many edge trees there are, all are visible
  // Minus 4 as the corner trees all get counted twice
  sumVisibleTrees += ((mapRows.size() * 2) + (mapRows.at(0).size() * 2) - 4);

  for (int i = 1; i < mapRows.size() - 1; i++)
  {
    for (int j = 1; j < mapRows.at(i).size() - 1; j++)
    {
      sumVisibleTrees += (DetermineIfTreeVisible(mapRows, i, j)) ? 1 : 0;
    }
  }

  std::cout << "Sum of Visible Trees = " << sumVisibleTrees << std::endl;

  int maxScenicScore = CalculateMaxScenicScore(mapRows);

  std::cout << "Maximum Possible Scenic Score = " << maxScenicScore << std::endl;
}

bool DetermineIfTreeVisible(std::vector<std::vector<int>> &map, int i, int j)
{
  bool results [4] = {true, true, true, true};
  // Check if visible in row
  // first left
  for (int k = 0; k < j; k++)
  {
    if (map.at(i).at(k) >= map.at(i).at(j))
    {
      results[0] = false;
      break;
    }
  }

  // Next right
  for (int k = j + 1; k < map.at(i).size(); k++)
  {
    if (map.at(i).at(k) >= map.at(i).at(j))
    {
      results[1] = false;
    }
  }
  
  // Check if visible in column
  // first up
  for (int k = 0; k < i; k++)
  {
    if (map.at(k).at(j) >= map.at(i).at(j))
    {
      results[2] = false;
    }
  }

  // next down
  for (int k = i + 1; k < map.size(); k++)
  {
    if (map.at(k).at(j) >= map.at(i).at(j))
    {
      results[3] = false;
    }
  }

  return results[0] || results [1] || results[2] || results[3];
}

int CalculateMaxScenicScore(std::vector<std::vector<int>> &map)
{
  int maxScenicScore = 0;

  for (int i = 0; i < map.size(); i++)
  {
    for (int j = 0; j < map.at(i).size(); j++)
    {
      int results [4] = {0, 0, 0, 0};

      if(j == 0)
      {
        // left edge, skip checking left
      }
      else
      {
        for (int k = j - 1; k >= 0; k--)
        {
          results[0]++;
          if (map.at(i).at(k) >= map.at(i).at(j))
          {
            break;
          }
        }
      }

      if(j == (map.at(i).size() - 1))
      {
        // right edge, skip checking right
      }
      else
      {
        for (int k = j + 1; k < map.at(i).size(); k++)
        {
          results[1]++;
          if (map.at(i).at(k) >= map.at(i).at(j))
          {
            break;
          }
        }
      }

      if(i == 0)
      {
        // top edge, skip checking up
      }
      else
      {
        for (int k = i - 1; k >= 0; k--)
        {
          results[2]++;
          if (map.at(k).at(j) >= map.at(i).at(j))
          {
            break;
          }
        }
      }

      if(i == (map.size() - 1))
      {
        // bottom edge, skip checking down
      }
      else
      {
        for (int k = i + 1; k < map.size(); k++)
        {
          results[3]++;
          if (map.at(k).at(j) >= map.at(i).at(j))
          {
            break;
          }
        }
      }

      int scenicScore = (results[0] * results [1] * results[2] * results[3]);

      if (scenicScore > maxScenicScore)
      {
        maxScenicScore = scenicScore;
      }
    }
  }

  return maxScenicScore;
}

// Maybe one day this will work
/*
// Check if visible in row
  // first left
  if (std::find_if(map.at(i).begin(), map.at(i).begin() + j, 
            [&](int &val) {return val > map.at(i).at(j); }) == map.at(i).begin() + j);
  {
    std::cout << "left: " << map.at(i).at(j) << std::endl;
    return true;
  }
  // Next right
  if (std::find_if(map.at(i).begin() + j + 1, map.at(i).end(), 
            [&](int &val) {return val > map.at(i).at(j); }) == map.at(i).end());
  {
    std::cout << "right: " << map.at(i).at(j) << std::endl;
    return true;
  }
  */