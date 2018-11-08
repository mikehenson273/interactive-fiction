#include <Windows.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

void bedSearch();
void GameEngine();
void goAgain();
void look();
void openDesk();
void openDoor();
void wait();
bool checkAgain = false;
bool deskKey = false;
bool doorCheck = false; //had to add an additional boolean as a check so the program wouldn't freak out
bool doorKey = false;
bool isLightOn = false;
bool lightCheck = false;
bool playAgain = false;
string name;
string playAgainChoices;
string playAgainChoice();
string userChoice();
string usersChoice;
string WelcomeUser();


void bedSearch()
{
	do
	{
		if (isLightOn == false) //won't let you search if the light is off
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets color for text to red
			cout << "\nWithout a light you can't really search. You give up in the meantime.\n\n";
			checkAgain = false;
		}

		else if (deskKey == true) //only does this if you already have desk key
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets color for text to red
			cout << "\nYou've already searched this area\n\n";
			checkAgain = false;
		}

		else if (isLightOn == true) //only lets you search bed if the light is on
		{
			wait();
			cout << "\nWith the light on you find it easier to search.\n";
			cout << "After rummaging through the bed and flipping it\n";
			cout << "you find a key... you wonder what it goes to.\n\n";
			deskKey = true;
			checkAgain = false;
		}

		else //shouldn't hit unless something goes wrong
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets color for text to red
			cout << "\n\nError something went wrong";
			checkAgain = true;
		}
	} while (checkAgain);
}

void openDesk()
{
	do
	{
		if (isLightOn == false && deskKey == false) //won't let you search if the light is off
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets color for text to red
			cout << "\nWithout a light you can't really search. You give up in the meantime.\n\n";
			checkAgain = false;
		}

		else if (doorKey == true) //only does this if you already have door key
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets color for text to red
			cout << "\nYou've already searched this area\n\n";
			checkAgain = false;
		}

		else if (isLightOn == true && deskKey == false) //informs you that you're missing the key
		{
			wait();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets color for text to red
			cout << "\nUpon searching you discover the desk is locked. You wonder where\n";
			cout << "the key could possibly be.\n\n";
			checkAgain = false;
		}

		else if (isLightOn == true && deskKey == true) //only lets you search desk if the light is on and key is found
		{
			wait();
			cout << "\nWith the light on you find it easier to search.\n";
			cout << "After rummaging through the desk and searching through\n";
			cout << "you find another key... you bet it goes to the door.\n\n";
			doorKey = true;
			checkAgain = false;
		}

		else //shouldn't hit unless something goes wrong
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets color for text to red
			cout << "\n\nError something went wrong";
			checkAgain = true;
		}
	} while (checkAgain);
}

void openDoor()
{
	do
	{
		if (isLightOn == false && doorKey == false) //won't let you search if the light is off
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets color for text to red
			cout << "\nWithout a light you can't really search. You give up in the meantime.\n\n";
			doorCheck = false;
			checkAgain = true;
		}

		else if (isLightOn == true && doorKey == false && deskKey == true) //tells you if you have only one key that it's the wrong one
		{
			wait();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets color for text to red
			cout << "\nWhen you use the key to try to open the door you discover\n";
			cout << "that it's still locked. You wonder where the real key could be.\n\n";
			doorCheck = false;
			checkAgain = true;
		}

		else if (isLightOn == true && doorKey == false) //lets you know you can't open door
		{
			wait();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets color for text to red
			cout << "\nWhen you try to open the door you discover that it's\n";
			cout << "locked. You wonder where the key could be.\n\n";
			doorCheck = false;
			checkAgain = true;
		}

		else if (isLightOn == true && doorKey == true) //only lets you open door if the light is on and key is found
		{
			wait();
			cout << "\nYou managed to leave the room... Now onwards with the day...\n";
			cout << "Now though, why was your door locked from the outside " << name << "?\n\n";
			system("pause");
			doorCheck = false;
			checkAgain = false;
			playAgain = true;
		}
		 
		else //shouldn't hit unless something goes wrong
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets color for text to red
			cout << "\n\nError something went wrong";
			doorCheck = true;
			checkAgain = true;
		}
	} while (doorCheck);
}

void GameEngine()
{
	name = WelcomeUser();
	cout << endl;

	do
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //sets color for text back to green
		system("pause");
		system("cls");

		if (isLightOn == false)
		{
			cout << "You wake up in a dark room. You should probably look around " << name << ".\n\n";
		}

		else if (isLightOn == true)
		{
			cout << "Look and open: ";
		}

		userChoice();

		if (usersChoice == "LOOK" || usersChoice == "LOOK AROUND")
		{
			look();
			checkAgain = true;
		}
		else if (usersChoice == "SEARCH BED")
		{
			bedSearch();
			checkAgain = true;
		}
		else if (usersChoice == "OPEN DESK" || usersChoice == "SEARCH DESK")
		{
			openDesk();
			checkAgain = true;
		}
		else if (usersChoice == "OPEN DOOR" || usersChoice == "TRY DOOR")
		{
			openDoor();
			playAgain = true;
		}

		//for ending the game... added the fuck off bit cuz i was bored
		else if (usersChoice == "NO" || usersChoice == "N" || usersChoice == "QUIT")
		{
			cout << "\nOh... Ok. Bye " << name << ".\n\n";
			checkAgain = false;
		}
		else if (usersChoice == "FUCK OFF")
		{
			cout << "\nWell that was uncalled for.... Good Bye " << name << "!\n\n";
			cout << "Also ";
			checkAgain = false;
		}

		else //informs user that their choice was invalid
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets color for text to red
			cout << name << ", I am sorry I do not understand your command" << endl;
			checkAgain = true;
		}
	} while (checkAgain);
}

void look()
{
	if (isLightOn == false) //lets you know the light is off
	{
		cout << "\nYou look around in the darkness. All you can see is a dimly lit LED.\n";
		cout << "Do you want to press the LED Y/N: ";
		userChoice();
		do
		{
			if ((usersChoice == "YES") || (usersChoice == "Y")) //lights up room
			{
				cout << "\nYou reach over and turn on the light illuminating the room.\n";
				isLightOn = true;
				checkAgain = false;
				look();
			}

			else if ((usersChoice == "NO") || (usersChoice == "N")) //quits game (yes it is intentional)
			{
				cout << "\nYou roll back into bed and decide to go back to sleep\n";
				cout << "for a while longer\n\n";
				system("pause");
				wait();
				checkAgain = false;
			}

			else //shouldn't hit unless wrong phrasing typed
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets color for text to red
				cout << "\nNot a valid response please enter yes or no!\n\n";
				checkAgain = true;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //sets color for text back to green
				system("pause");
			}
		} while (checkAgain);
	}

	else if (isLightOn == true) //informs you of your surroundings
	{
		cout << "\nYou see that the room is sparse. All that is in it, is\n";
		cout << "the bed you are sleeping on, a desk, and a door.\n\n";
	}

	else //shouldn't hit unless something horrible goes wrong
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets color for text to red
		cout << "\n\nError something went wrong\n";
		system("pause");
	}

}

void goAgain() // Replay Loop Confirmation
{
	if (playAgain == true) //triggers this if playAgain is true when reaching the loop
	{
		do
		{
			cout << "\n\nWant to go Again Y/N: ";
			userChoice();

			if (usersChoice == "YES" || usersChoice == "Y")
			{
				playAgain = true; //replay program
				checkAgain = false; //leave current loop
				system("cls"); //clears console for new playthrough
			}
			else if (usersChoice == "NO" || usersChoice == "N")
			{
				cout << "\n\nThanks for playing. Please come again " << name << ".\n";
				playAgain = false; //leave program altogether
				checkAgain = false; //leaves this loop
				system("pause");
			}
			else //error catcher
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); //sets color for text to red
				cout << "\nInvalid response. Please enter a valid response.\n";
				checkAgain = true; //resets current loop for proper guess
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //sets color for text back to green
			}
		} while (checkAgain); //boolean for this do while loop
	}

	else if (playAgain == false) //triggered if playAgain is false when reaching this loop
	{
		cout << "\n\nThanks for playing.\n\n";
		system("pause");
	}
}

string userChoice() //small function for user input
{
	usersChoice;	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //sets color for text only to aqua
	getline(cin, usersChoice); //gets input from user
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //sets color for text back to green
	for (int i = 0; usersChoice[i] != '\0'; i++) //this loop capitalizes input for decisions.
	{
		usersChoice[i] = toupper(usersChoice[i]);
	}
	return usersChoice;
}

// A psuedo-load screen
void wait()
{
	for (int a = 0; a < 3; ++a)
	{
		system("cls");
		for (int b = 0; b < 6; ++b)
		{
			Sleep(500);
			cout << ". ";
		}
	}
	cout << "\n\n";
}


string WelcomeUser() //function to greet user and explain the situation.
{
	string playersName;
	cout << "Wake up!\n\n";
	cout << "What is your name? "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //sets color for text to aqua
	getline(cin, playersName); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //sets color for text back to green
	cout << endl << playersName << ", ok now we got to get going.\n";
	return playersName;
}

int main()
{
	//makes full screen when activated
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	system("title Waking Up");
	system("color 02"); //changes all console colors
	do //do loop that the main resides in is a play again loop
	{
		//resets booleans at program restart
		checkAgain = false;
		deskKey = false;
		doorCheck = false;
		doorKey = false;
		isLightOn = false;
		lightCheck = false;
		playAgain = false;
		 
		GameEngine();
		goAgain(); //function run for confirmation on playing again
	} while (playAgain);
	return 0;
}