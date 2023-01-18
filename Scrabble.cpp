#include <fstream>
#include <iostream>
#include <string>

void printMenu();
std::string getAvailableLetters(int roundNumber);
bool lettersCheck(const std::string& inputWord, std::string& availableLetters);
bool wordDictionaryCheck(const std::string& inputWord); 

int main()
{
	printMenu();

	int numberChoiceFromMenu;
	std::cin >> numberChoiceFromMenu;

	int letterCount = 10;
	int roundCount  = 10;

    if (numberChoiceFromMenu == 2)
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
		else if (settingChoice == 'a')
		{
			std::cout << "Change letter count to : ";
			std::cin >> letterCount;

		}
	}

	int totalPoints = 0;
	
	for (int i = 1; i <= roundCount; i++)
	{   
		std::cout << std::endl;
		std::cout << "Round "<< i << ". Available letters: "; 
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
				std::cout << "Enter N for new letters or Try again with: ";
				std::cout << availableLetters << std::endl;
				
			}
			std::cout << std::endl;

		} while (lettersCheck(word, availableLetters) == false || wordDictionaryCheck(word) == false);
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

std::string getAvailableLetters(int letterCount)
{
	std::string letters;
	srand(time(0));
	for (int i = 0; i < letterCount; i++)
	{
		char letter = char('a' + rand() % 26);
		letters += letter;
		letters += ' ';
	}
	
	return letters;
}

bool lettersCheck(const std::string& inputWord, std::string& availableLetters)
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