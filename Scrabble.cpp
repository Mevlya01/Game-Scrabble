/**
*
* Solution to course project # 8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Mevlya Ryustemova
* @idnumber 0MI0600076
* @compiler VC
*
* <file with helper functions>
*
*/

#include <fstream>
#include <iostream>
#include <string>

void printMenu();
void addWordToTheDictionary();
std::string getAvailableLetters(int letterCount);
bool lettersCheck(const std::string& inputWord, const std::string& availableLetters);
bool wordDictionaryCheck(const std::string& inputWord); 
int changeLetterCount(int letterCount);
int changeRoundCount(int roundCount);
int menuChoiceInput();
char settingChoiceInput();
void printPoints(int points);
void printRoundNumber(int i);

int main()
{
	do 
	{ 
		printMenu();
		int numberChoiceFromMenu = menuChoiceInput();
		int roundCount = 10;
		int letterCount = 10;

		if (numberChoiceFromMenu == 2)
		{
			char settingChoice = settingChoiceInput();
			if (settingChoice == 'b')
			{
				roundCount = changeRoundCount(roundCount);
			}
			else if (settingChoice == 'a')
			{
				letterCount = changeLetterCount(letterCount);
			}
		}
		else if (numberChoiceFromMenu == 3)
		{
			addWordToTheDictionary();
			continue;
		}
		else if (numberChoiceFromMenu == 4)
		{
			return 0;
		}

		int totalPoints = 0;
		for (int i = 1; i <= roundCount; i++)
		{
			printRoundNumber(i);
			std::string availableLetters = getAvailableLetters(letterCount);
			std::cout << availableLetters << std::endl;
			std::cout << "Enter a word: " << std::endl;
			std::string word;

			do
			{
				std::cin >> word;
				if (lettersCheck(word, availableLetters) == true && wordDictionaryCheck(word) == true)
				{
					int letterCountOfWord = word.size();
					totalPoints += letterCountOfWord;
					std::cout << "Correct! Total points: " << totalPoints;
					break;
				}
				else
				{
					std::cout << "Invalid word." << std::endl;
					std::cout << "Try again with: ";
					std::cout << availableLetters << std::endl;
				}

			} while (lettersCheck(word, availableLetters) == false || wordDictionaryCheck(word) == false);
			std::cout << std::endl;
		}
		printPoints(totalPoints);

	} while (true);

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
} 

void addWordToTheDictionary()
{
	std::fstream wordFile;
	wordFile.open("wordDictionary.txt", std::fstream::out | std::fstream::app);

	if (wordFile.is_open())
	{
		std::string wordInput;
		std::cout << "Add a word to the dictionary: ";
		std::cin >> wordInput;
		wordFile << std::endl << wordInput;
		std::cout << "Your word was added." << std::endl;
		std::cout << std::endl;
		wordFile.close();
	}
}

std::string getAvailableLetters(int letterCount)
{
	srand(time(0));
	int finalNum = rand() % (50) + 1;;

	std::string letters;
	std::fstream letterFile;

	if (letterCount == 10)
	{
		letterFile.open("availableLetters.txt", std::fstream::in);
	}
	else if (letterCount == 15)
	{
		letterFile.open("availableLongLetters.txt", std::fstream::in);
	}

	if (letterFile.is_open())
	{
		for (int k = 0; k < finalNum; k++)
		{
			getline(letterFile, letters);
		}
		letterFile.close();
	}

	return letters; 
}

bool lettersCheck(const std::string& inputWord, const std::string& availableLetters)
{   
	bool check = false;

	int letterCount = availableLetters.size();
	std::string letters = availableLetters;

	std::string checkWord;

	for (int k = 0; k < inputWord.size(); k++)
	{
		for (int j = 0; j < letterCount; j++)
		{
			if (inputWord[k] == letters[j])
			{
				checkWord += letters[j];
				letters.erase(letters.begin() + j);
				letterCount--;
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
	wordFile.open("wordDictionary.txt", std::fstream::in);
	
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

	wordFile.close();

	return check;
} 

int changeLetterCount(int letterCount) 
{
	std::cout << "Change letter count to 15 or stay at 10 (Enter 15 or 10): ";
	std::cin >> letterCount;

	while (letterCount != 15 && letterCount != 10)
	{
		std::cout << "Please enter valid letter count (15 or 10) :";
		std::cin >> letterCount;
	}

	return letterCount;
}

int changeRoundCount(int roundCount)
{
	std::cout << "Note: maximum possible round count is 20. " << std::endl;
	std::cout << "Change round count to : ";
	std::cin >> roundCount;

	while (roundCount < 1 || roundCount > 20)
	{
		std::cout << "Round Count should be in the range of [1;20]. Please enter new number: ";
		std::cin >> roundCount;
	}

	return roundCount;
}

int menuChoiceInput()
{   
	int numberChoiceFromMenu;
	std::cout << "Enter your number choice from menu: ";
	std::cin >> numberChoiceFromMenu;
	while (numberChoiceFromMenu < 1 || numberChoiceFromMenu > 4)
	{
		std::cout << "Please enter valid number from the menu (1-4) :";
		std::cin >> numberChoiceFromMenu;
	}

	return numberChoiceFromMenu;
}

char settingChoiceInput()
{
	char settingChoice;
	std::cout << "Enter your setting choice (a or b): ";
	std::cin >> settingChoice;

	while (settingChoice != 'a' && settingChoice != 'b')
	{
		std::cout << "Please enter valid setting choice (a or b): ";
		std::cin >> settingChoice;
	}

	return settingChoice;
}

void printPoints(int points)
{
	std::cout << std::endl;
	std::cout << "Your points for the game are: " << points << std::endl;
	std::cout << std::endl;
}

void printRoundNumber(int i)
{
	std::cout << std::endl;
	std::cout << "Round " << i << ". Available letters: ";
}