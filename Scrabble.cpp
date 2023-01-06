#include <fstream>
#include <iostream>
#include <string>

void printMenu();
std::string getAvailableLetters(int roundNumber);
bool lettersCheck(const std::string& inputWord, int roundNumber);
bool wordDictionaryCheck(const std::string& inputWord); 

int main()
{
	printMenu();

	int numberChoiceFromMenu;
	std::cin >> numberChoiceFromMenu;

	int roundCount  = 0;
	if (numberChoiceFromMenu == 1)
	{
		roundCount = 10;
	}
	else if (numberChoiceFromMenu == 2)
	{
		std::cout << "Enter your setting choice (a or b): ";
		char settingChoice;
		std::cin >> settingChoice;

		if (settingChoice == 'b')
		{
			std::cout << "Note: maximum possible round count is 20. " << std::endl;
			std::cout << "Change round count to : ";
			std::cin >> roundCount;
		}
	}

	int totalPoints = 0;
	
	for (int i = 1; i <= roundCount; i++)
	{   
		std::cout << std::endl;
		std::cout << "Round "<< i << ". Available letters: ";
		std::cout << getAvailableLetters(i) << std::endl;

		std::cout << "Enter a word: " << std::endl;
		std::string word;

		do 
		{
			std::cin >> word;

			if (lettersCheck(word, i) == true && wordDictionaryCheck(word) == true)
			{
				int letterCountOfWord = word.size();
				totalPoints += letterCountOfWord;
				std::cout << "Correct! Total points: " << totalPoints;
			}
			else
			{
				std::cout << "Invalid word" << std::endl;
				std::cout << "Try again with: ";
				std::cout << getAvailableLetters(i) << std::endl;
				std::cout << "Enter a word: ";

			}
			std::cout << std::endl;

		} while (lettersCheck(word, i) == false || wordDictionaryCheck(word) == false);
	}
	
	return 0;
}

void printMenu()
{
	std::cout << "Game Scrabble" << std::endl;
	std::cout << std::endl;
	std::cout << "1. New Game" << std::endl;
	std::cout << "2. Settings" << std::endl;
	std::cout << "   a. Change the count of the given letters" << std::endl;
	std::cout << "   b. Change the count of rounds" << std::endl;
	std::cout << "3. Enter a new word" << std::endl;
	std::cout << "4. Exit" << std::endl;
	std::cout << std::endl;
	std::cout << "Enter your number choice from menu: ";
}

std::string getAvailableLetters(int roundNumber)
{
	std::fstream letterFile;
	letterFile.open("availableLetters.txt", std::fstream::in);
	std::string letters;

	if (letterFile.is_open())
	{
		for (int k = 0; k < roundNumber; k++)
		{
		   getline(letterFile, letters);
		}
		letterFile.close();
	}
	
	return letters;
}

bool lettersCheck(const std::string& inputWord,int roundNumber)
{   
	bool check = false;

	std::string availableLetters = getAvailableLetters(roundNumber);
	int availableLetterCount = availableLetters.size();
	std::string checkWord;

	for (int k = 0; k < inputWord.size(); k++)
	{
		for (int j = 0; j < availableLetterCount; j++)
		{
			if (inputWord[k] == availableLetters[j])
			{
				checkWord += availableLetters[j];
				availableLetters.erase(availableLetters.begin() + j);
				availableLetterCount--;
				break;
			}
		}
	}

	if (checkWord == inputWord)
	{
		check = true;
	}
	
	return check;
}

bool wordDictionaryCheck(const std::string& inputWord)
{
	bool check = false;

	std::fstream wordFile;
	wordFile.open("wordDictionarty.txt", std::fstream::in);
	
	if (wordFile.is_open())
	{  
		std::string word;

		while (getline(wordFile, word))
		{
		   if (inputWord == word)
		   {
			   check = true;
			   break;
		   }
		}
	}
	return check;
} 