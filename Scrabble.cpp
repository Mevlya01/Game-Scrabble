#include <fstream>
#include <iostream>
#include <string>

void printMenu();
std::string getAvailableLetters();
bool lettersCheck(const std::string& inputWord, std::string& availableLetters);
bool wordDictionaryCheck(const std::string& inputWord); 
void addWordToTheDictionary();

int main()
{
	printMenu();

	int numberChoiceFromMenu;
	std::cin >> numberChoiceFromMenu;

	while (numberChoiceFromMenu < 1 || numberChoiceFromMenu > 4)
	{
		std::cout << "Please enter valid number from the menu (1-4) :";
		std::cin >> numberChoiceFromMenu;
	}

	int roundCount  = 10;
	int letterCount = 10;

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

			while (roundCount < 1 || roundCount > 20)
			{
				std::cout << "Round Count should be in the range of [1;20]. Please enter new number: ";
				std::cin >> roundCount;

			}
		}
		else if (settingChoice == 'a')
		{
			std::cout << "Change letter count to 15 or stay at 10 (Enter 15 or 10): ";
			std::cin >>letterCount;

			while (letterCount != 15 && letterCount != 10)
			{
				std::cout << "Please enter valid letter count (15 or 10) :";
				std::cin >> letterCount;
			}
		}
	}
	else if (numberChoiceFromMenu == 3)
	{
		addWordToTheDictionary();
	}
	else if (numberChoiceFromMenu == 4)
	{
		return 0;
	}

	int totalPoints = 0;
	
	for (int i = 1; i <= roundCount; i++)
	{   
		std::cout << std::endl;
		std::cout << "Round "<< i << ". Available letters: "; 
		std::string availableLetters = getAvailableLetters();
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

std::string getAvailableLetters()
{
	srand(time(0));
	int finalNum = rand() % (42) + 1;

	std::fstream letterFile;
	letterFile.open("availableLetters.txt", std::fstream::in);
	std::string letters;

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

	wordFile.close();

	return check;
} 

void addWordToTheDictionary()
{
	
	std::fstream wordFile;
	wordFile.open("wordDictionarty.txt", std::fstream::out | std::fstream::app);

	if (wordFile.is_open())
	{
		std::string wordInput;
		std::cout << "Add a word to the dictionary: ";
		std::cin >> wordInput;
		wordFile << std::endl << wordInput;
		std::cout << "Your word was added." << std::endl;
	}
	
	wordFile.close();
}