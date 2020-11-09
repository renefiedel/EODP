#include "StringManager.hpp"
#include "FIPSException.hpp"

// This function initializes the StringManager class
StringManager::StringManager()
{
  // Construct
}

// This function destroys the StringManager class
StringManager::~StringManager()
{
  // Destroy
}


vector<string> StringManager::split(string str, char delimiter)
{
  vector<string> internal;
  stringstream ss(str);
  string tok;

  while (getline(ss, tok, delimiter))
  {
    tok.erase(remove(tok.begin(), tok.end(), ' '), tok.end());
    internal.push_back(tok);
  }

  return internal;
}

void StringManager::copyStringVectorToStringArray(vector<string>& stringVector, char*** stringArray)
{
  int numStrings = stringVector.size();

  (*stringArray) = (char**) calloc(numStrings, sizeof(char*));
  if ((*stringArray) == NULL)
  {
    throw(FIPSException(
        "Error allocating memory in time id initialization.",
        BOOST_CURRENT_FUNCTION));
  }

  for (int i = 0; i < numStrings; i++)
  {
    (*stringArray)[i] = (char*) calloc(512, sizeof(char));
    if ((*stringArray)[i] == NULL)
    {
      for (int j = 0; j < i; j++)
      {
        freeArray((void**) &((*stringArray)[j]));
      }
      freeArray((void**) &(*stringArray));

      throw(FIPSException("Error allocating memory in time id initialization.",
          BOOST_CURRENT_FUNCTION));
    }
    else
    {
      size_t numChars = stringVector[i].copy((*stringArray)[i],
          stringVector[i].size());
      (*stringArray)[i][numChars] = '\0';
    }
  }
}

void StringManager::freeStringArray(int numStrings, char*** stringArray)
{
  if ((*stringArray) != NULL)
  {
    for (int i = 0; i < numStrings; i++)
    {
      freeArray((void**) &((*stringArray)[i]));
    }
    freeArray((void**) &(*stringArray));
  }
}

void StringManager::freeArray(void **array)
{
  if ((*array) != NULL)
  {
    free((*array));
    (*array) = NULL;
  }
}


