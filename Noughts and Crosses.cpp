// Noughts and Crosses.cpp : Defines the entry point for the console application.
/*

*/

#include "stdafx.h" // This ensures that no header files get recompiled when no change has been made to them. This saves compiling time.
#include <iostream> // Used for accessing the Command Console functions.
#include <string> // This initializes the Standard Template Library's string container !
#include <Windows.h> // Used for Font and Text Colour and Size.
#include <map> // Used for our Index Key pairs.
#include <conio.h> // Used for the character input.
#include <ctype.h> // Used for function to force uppercase chars.
#include <ctime> // Used for recording how much time we have to make a move.
using namespace std;

// General Functions !
class JohnsFunctions
{
public:

	struct Definitions
	{
	// Definitions
	#define cLime 10
	#define cGreen 2
	#define cRed 12
	#define cWhite 7
	#define cTeal 11
	#define cPurple 5
	#define cPink 13
	#define cYellow 14
	#define cDarkYellow 6
	#define cDarkRed 4
	};

	// This function sets the size of a console window. Arg0 is int width and Arg1 is int height.
	void fSetConsoleSize(int Width, int Height)
	{
		HWND console = GetConsoleWindow();
		RECT r;
		GetWindowRect(console, &r); //stores the console's current dimensions

		MoveWindow(console, r.left, r.top, Width, Height, TRUE);
	}

	// This function sets the position in the console whereyou want to modify text. x is the column, y is the row. The origin (0,0) is top-left. GetWindowRect(GetConsoleWindow(), RECT);
	void fsetCursorPosition(int x, int y)
	{
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout.flush();
		COORD coord = { (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition(hOut, coord);
	}

	// This function searches a string (Argument 0) for occurances of another string (Argument 2). Argument 2 filter by default looks for all characters except numbers and spaces. Argument 1 then asks if you want to search all whole occurances of the string you provided (0 default) or all occurances of the individual characters you provided in your string (0). Argument 3 limits the string length to be searched. If an occurance of the filter is found then return is True, otherwise false.
	bool fStringFind(string content, bool whole = 1, string filter = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_=+\\|]}[{';:/?"".>,<", int length = 0)
	{
		if (length == 0)
		{
			length = content.length();
		}

		int lfilter = filter.length(); // The length of the filter string.
		string rString = content.substr(0, length); // Assign argument 0 to a variable.

		if (content == "") // If the input string is empty then we exit the function immediately and return true.
		{
			return 1;
		}
		else
		{
			if (whole) // If the filter type is the whole string (1).
			{
				if (rString.find(filter) != -1) // If an occurance of the filter is found then return true.
				{
					return 1;
				}
				return 0; // If no occurance of the filter was found then return false;
			}
			else // If the filter type is individual characters (0).
			{
				for (int i = 0; i < lfilter; i++) // Cycle through the character length of the filter and check to see if any of the characters in the filter has an occurance in the content string.
				{
					string charfilter = filter.substr(i, 1); // Iterate through the original filter then create a 1 character string filter and assign 1 character from the original to it.

					if (rString.find(charfilter) != -1) // If there is an occurance of the filter (-1) provided in the content string then continue, otherwise if there is no occurance then return an error string (0).
					{
						return 1; // If an occurance of any of the characters in the filter was found then return true.
					}
				}
				return 0; // If no occurance of the filter was found then return false.
			}
		}
	}

	// This function displays coloured text to console output. Argument a is for a colour code accepts numbers from 0 to 255. Works in blocks of 16. Alternating, and starting at 0, the first set of 16 blocks alters the text colour, the second alternated set of 16 blocks alters the background text colour. Reference 2: https://cboard.cprogramming.com/c-programming/157954-changing-font-size-colour.html
	void fconsole_c(char a)
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, a);
	}

	// This function generates a random integer in a given range.
	int fRandom(int min, int max)
	{
		return (min + rand() % int((max - min) + 1));
	}

	// Set Windows Command Console Interface Font Size.
	void fconsole_fs(int FontSize)
	{
		CONSOLE_FONT_INFOEX info = { 0 };
		info.cbSize = sizeof(info);
		info.dwFontSize.Y = FontSize; // leave X as zero
		info.FontWeight = FW_NORMAL;
		wcscpy_s(info.FaceName, L"Lucida Console");
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
	}

}; JohnsFunctions JF; // Creates an object pointer to my custom class which containins my functions !

int main(void)
{
	srand(time(0)); // This ensures that our random values are actually random.

	bool iValid = true; // Whether our Console Input is valid or not.
	bool fPlayer; // The first player to make a move. 0 For player 1, 1 for Player 2.
	bool cPlayer; // The current player. 0 For player 1, 1 for Player 2.
	bool Player1Win = false;
	bool Player2Win = false;
	bool Player1AI = false; // Is player 1 an AI
	bool Player2AI = false; // Is player 2 an AI
	bool MoveType = 0; // MoveType 0 is for human player move, 1 is for AI move.

	bool GameRunning = true;
	bool MainMenu = true;
	bool GameRoom = false;

	int GameGrid[9] = { 0,2,0,2,1,2,0,2,0 }; // This array will keep track of the nodes which have been occupied by player 1 with a 1, nodes occupied by player 2 with 2, and nodes which are not occupied with 0.

	char Input = '\0'; // Our Console Input.

	int PlayerModify = 0; // When we enter a custom name we can cycle through both players starting at player 1.
	int GameType = 1; // 0 is for player vs AI, 1 is for player vs player, 2 is for AI vs AI.
	int AIDifficultyP1 = 1; // Player 1's defualt AI difficulty if AI. 0 For easy, 1 for hard.
	int AIDifficultyP2 = 1; // Player 1's defualt AI difficulty if AI. 0 For easy, 1 for hard.
	int cAIDifficulty; // The current AI player's intelligence.
	int l = 0; // Offensive counter: How many nodes are occupied in the current goal by the current player.
	int m = 0; // Defensive Counter: How many nodes are occupied in the current goal by the opposing player.
	int Player1Wins = 0;
	int Player2Wins = 0;

	int PWatch; // We will use this variable to record how long we take to make a move.
	int PTime = 20 * 1000; // This variable determines how much time we have to make a move in milliseconds.
	int GoalGrid[8][3]; // This 2D Grid stores all 8 of the possible winning outcomes.
	int Moves = 0; // This variable keeps track of the number of moves that have been made so far.
	// Here we insert all possible winning outcomes into the GoalGrid.
	for (int i = 1; i <= 8; i++)
	{
		// Horizontal Winning Outcomes.
		if (i >= 1 && i <= 3)
		{
			for (int j = 1; j <= 3; j++)
			{
				GoalGrid[i - 1][j - 1] = (j - 1) + ((i - 1) * 3);
			}
		}

		// Vertical Winning Outcomes.
		if (i >= 4 && i <= 6)
		{
			for (int j = 1; j <= 3; j++)
			{
				GoalGrid[i - 1][j - 1] = ((j - 1) * 3) + (i - 4);
			}
		}

		// Left Diagonal Winning Outcome.
		if (i == 7)
		{
			for (int j = 1; j <= 3; j++)
			{
				GoalGrid[i - 1][j - 1] =  ((j - 1) * 4);
			}
		}

		// Right Diagonal Winning Outcome.
		if (i == 8)
		{
			for (int j = 1; j <= 3; j++)
			{
				GoalGrid[i - 1][j - 1] = (j + 1) + ((j + 1) - 2);
			}
		}
	}

	map <char, int> GridMap; // First column stores the default name, second column stores the index starting at (A,0).
	map <char, int>::iterator GridMapIt;

	string Player1 = "X"; // Player 1s symbol
	string Player2 = "O"; // Player 2s symbol
	string Player1name = "Player 1";
	string Player2name = "Player 2";

	SetConsoleTitle(TEXT("Noughts and Crosses")); // We set the Console Title

	// Here we create a map pair assigning A an index of 0 and B 1 and so on until I...
	for (int i = 0; i < 9; i++)
	{
		pair<map<char, int>::iterator, bool> retr;
		retr = GridMap.insert(std::pair<char, int>(char(65 + i), i));
	}

	while (GameRunning)
	{
		// 1: We start in the Main Menu
		if (MainMenu)
		{
			// Set the console text size.
			JF.fconsole_fs(25);

			// Write the Main Menu console contents just once, from then on just modify what needs to change.
			JF.fsetCursorPosition(0, 0);
			JF.fconsole_c(cTeal);
			cout << "Welcome to Noughts and Crosses !" << endl;
			cout << "\nMain Menu:\n" << endl;

			JF.fconsole_c(cPink);
			cout << "Press 1 - To Cycle Game Type" << endl;
			cout << "Press 2 - To Cycle Player Name" << endl;
			cout << "Press 3 - To Start Game" << endl;
			cout << "Press 0 - To Quit Game" << endl;

			JF.fconsole_c(cTeal);
			cout << "\nSelected Game Type : ";

			JF.fconsole_c(cLime);
			cout << "Player vs Player" << endl;

			JF.fconsole_c(cTeal);
			cout << "\nPlayer 1 Name: ";
			JF.fconsole_c(cGreen);
			cout << Player1name;
			JF.fconsole_c(cTeal);
			cout << "\nPlayer 2 Name: ";
			JF.fconsole_c(cDarkRed);
			cout << Player2name;

			JF.fconsole_c(cTeal);
			JF.fsetCursorPosition(0, 14);
			JF.fconsole_c(cTeal);
			cout << "Game Types: P v AI | ";
			JF.fconsole_c(cPink);
			cout << "P v P ";
			JF.fconsole_c(cTeal);
			cout << "| AI v AI";


			while (MainMenu)
			{
				// We lock the Console Window Size
				JF.fSetConsoleSize(900, 600);

				// Set the cursor position then clear the console input.
				JF.fsetCursorPosition(0, 16);
				Input = toupper(_getche());
				JF.fsetCursorPosition(0, 16);
				cout << "                                                        ";

				// Execute action based on input.
				if (Input == '1')
				{
					// Cycle through the game types.
					GameType++;
					if (GameType > 2)
					{
						GameType = 0;
					}

					JF.fconsole_c(cLime);
					if (GameType == 0) // Player vs AI
					{
						JF.fsetCursorPosition(21, 9);
						cout << "                ";
						JF.fsetCursorPosition(21, 9);
						cout << "Player vs AI" << endl;

						JF.fsetCursorPosition(0, 14);
						JF.fconsole_c(cTeal);
						cout << "Game Types: ";
						JF.fconsole_c(cPink);
						cout << "P v AI";
						JF.fconsole_c(cTeal);
						cout << " | P v P | AI v AI";

						if (Player1AI)
						{
							Player1name = Player1name.substr(0, Player1name.length() - 5);
						}
						if (!Player2AI)
						{
							Player2name += " (AI)";
						}
						Player1AI = false;
						Player2AI = true;

						JF.fsetCursorPosition(15, 11);
						cout << "                                        ";
						JF.fsetCursorPosition(15, 11);
						JF.fconsole_c(cGreen);
						cout << Player1name << endl;

						JF.fsetCursorPosition(15, 12);
						cout << "                                        ";
						JF.fsetCursorPosition(15, 12);
						JF.fconsole_c(cDarkRed);
						cout << Player2name << endl;
					}

					if (GameType == 1) // Player vs Player
					{
						JF.fsetCursorPosition(21, 9);
						cout << "                ";
						JF.fsetCursorPosition(21, 9);
						cout << "Player vs Player" << endl;

						JF.fsetCursorPosition(0, 14);
						JF.fconsole_c(cTeal);
						cout << "Game Types: P v AI | ";
						JF.fconsole_c(cPink);
						cout << "P v P ";
						JF.fconsole_c(cTeal);
						cout << "| AI v AI";

						if (Player1AI)
						{
							Player1name = Player1name.substr(0, Player1name.length() - 5);
						}
						if (Player2AI)
						{
							Player2name = Player2name.substr(0, Player2name.length() - 5);
						}
						Player1AI = false;
						Player2AI = false;

						JF.fsetCursorPosition(15, 11);
						cout << "                                        ";
						JF.fsetCursorPosition(15, 11);
						JF.fconsole_c(cGreen);
						cout << Player1name << endl;

						JF.fsetCursorPosition(15, 12);
						cout << "                                        ";
						JF.fsetCursorPosition(15, 12);
						JF.fconsole_c(cDarkRed);
						cout << Player2name << endl;
					}

					if (GameType == 2) // AI vs AI
					{
						JF.fsetCursorPosition(21, 9);
						cout << "                ";
						JF.fsetCursorPosition(21, 9);
						cout << "AI vs AI" << endl;

						JF.fsetCursorPosition(0, 14);
						JF.fconsole_c(cTeal);
						cout << "Game Types: P v AI | P v P | ";
						JF.fconsole_c(cPink);
						cout << "AI v AI";

						if (!Player1AI)
						{
							Player1name += " (AI)";
						}
						if (!Player2AI)
						{
							Player2name += " (AI)";
						}
						Player1AI = true;
						Player2AI = true;

						JF.fsetCursorPosition(15, 11);
						cout << "                                        ";
						JF.fsetCursorPosition(15, 11);
						JF.fconsole_c(cGreen);
						cout << Player1name << endl;

						JF.fsetCursorPosition(15, 12);
						cout << "                                        ";
						JF.fsetCursorPosition(15, 12);
						JF.fconsole_c(cDarkRed);
						cout << Player2name << endl;
					}

				}

				if (Input == '2')
				{
					if (PlayerModify == 0)
					{
						PlayerModify = 1;
					}
					else
					{
						if (PlayerModify == 1)
						{
							PlayerModify = 2;
						}
						else
						{
							if (PlayerModify == 2)
							{
								PlayerModify = 0;
							}
						}
					}

					if (PlayerModify == 0)
					{
						JF.fsetCursorPosition(29, 11);
						cout << "                          ";
						JF.fsetCursorPosition(29, 12);
						cout << "                          ";
					}

					if (PlayerModify == 1)
					{
						JF.fsetCursorPosition(29, 12);
						cout << "                          ";

						JF.fconsole_c(cGreen);
						JF.fsetCursorPosition(29, 11);
						cout << "<<<";
						JF.fconsole_c(cTeal);
						cout << " Press Enter to Modify!" << endl;
					}

					if (PlayerModify == 2)
					{
						JF.fsetCursorPosition(29, 11);
						cout << "                          ";

						JF.fconsole_c(cDarkRed);
						JF.fsetCursorPosition(29, 12);
						cout << "<<<";
						JF.fconsole_c(cTeal);
						cout << " Press Enter to Modify!" << endl;
					}
				}

				if (Input == '3')
				{
					MainMenu = false;
				}

				if (Input == '0')
				{
					JF.fconsole_c(cRed);
					JF.fsetCursorPosition(0, 16);
					cout << "Now Exiting Game!\n" << endl;
					JF.fconsole_c(cTeal);
					exit(0);
				}

				//Enter key
				if (Input == 13)
				{
					if (PlayerModify == 1)
					{
						JF.fconsole_c(cGreen);
						JF.fsetCursorPosition(15, 11);
						cout << "                                        ";
						JF.fsetCursorPosition(15, 11);
						getline(cin, Player1name);

						if (Player1AI)
						{
							Player1name += " (AI)";
							JF.fsetCursorPosition(15, 11);
							cout << "                                 ";
							JF.fsetCursorPosition(15, 11);
							JF.fconsole_c(cGreen);
							cout << Player1name << endl;
						}

						PlayerModify = 0;
						Input = '\0';
					}

					if (PlayerModify == 2)
					{
						JF.fconsole_c(cDarkRed);
						JF.fsetCursorPosition(15, 12);
						cout << "                                        ";
						JF.fsetCursorPosition(15, 12);
						getline(cin, Player2name);

						if (Player2AI)
						{
							Player2name += " (AI)";
							JF.fsetCursorPosition(15, 12);
							cout << "                                 ";
							JF.fsetCursorPosition(15, 12);
							JF.fconsole_c(cDarkRed);
							cout << Player2name << endl;
						}

						PlayerModify = 0;
						Input = '\0';
					}
				}
			}
		}

		if (!MainMenu)
		{
			// Clear the Screen before drawing the contents of the new menu.
			system("cls");
			GameRoom = true;
		}

		// 2: We then go to the Game Room and execute the following code until we reach the while loop only once.
		if (GameRoom)
		{
			// Reset variables
			{
				// Choose a new random player to start first.
				fPlayer = JF.fRandom(0, 1);
				cPlayer = fPlayer;
				// Reset Console Input
				Input = '\0';

				// Reset Weight Grid
				for (int i = 0; i < 9; i++)
				{
					GameGrid[i] = 0;
				}
			}

			// Reset the number of Moves
			Moves = 0;
			// Reset the Win counters
			Player1Wins = 0;
			Player2Wins = 0;

			// Set the console text size.
			JF.fconsole_fs(35);

			// We draw the Graphics Output initially. From then on we only redraw whatever changes.	
			JF.fsetCursorPosition(0, 0);
			JF.fconsole_c(cTeal);
			cout << "Game Type: ";
			JF.fconsole_c(cPink);

			if (GameType == 0) { cout << "Player vs AI"; }
			if (GameType == 1) { cout << "Player vs Player"; }
			if (GameType == 2) { cout << "AI vs AI"; }

			JF.fconsole_c(cTeal);
			cout << "\nPress ";
			JF.fconsole_c(cPink);
			cout << "ESCAPE ";
			JF.fconsole_c(cTeal);
			cout << "to to restart !";


			JF.fconsole_c(cTeal);
			JF.fsetCursorPosition(0, 3);
			cout << "Current Player =  \n\n" << endl;

			// Here we build the text graphics of our Game Grid. After this initial build, we just modify what needs to change instead of redrawing everything.
			JF.fsetCursorPosition(0, 6);
			int j = 0;
			for (int i = 0; i < 5; i++)
			{
				if (i == 0 || i == 2 || i == 4)
				{
					for (int k = 0; k < 3; k++)
					{
						JF.fconsole_c(cTeal);
						cout << " " << char(65 + j) << " ";
						JF.fconsole_c(cPink);
						j++;

						if (k <= 1)
						{
							cout << "|";
						}
					}
				}
				else
				{
					cout << "\n___ ___ ___\n";
				}
			}

			JF.fconsole_c(cTeal);
			cout << "\n\n\nNext move: ";

			// Update the Screen at the start to show which player it is currently.
			if (cPlayer == 0)
			{
				JF.fconsole_c(cGreen);
				JF.fsetCursorPosition(17, 3);
				cout << Player1name << " (" << Player1 << ")                    ";
				JF.fsetCursorPosition(11, 13);
			}
			else if (cPlayer == 1)
			{
				JF.fconsole_c(cDarkRed);
				JF.fsetCursorPosition(17, 3);
				cout << Player2name << " (" << Player2 << ")                    ";
				JF.fsetCursorPosition(11, 13);
			}

			// Set Timer Notice.
			JF.fsetCursorPosition(0, 15);
			JF.fconsole_c(cDarkYellow);
			cout << "Notice You only have ";
			JF.fconsole_c(cTeal);
			cout << PTime / 1000;
			JF.fconsole_c(cDarkYellow);
			cout << " seconds to make a move!";
			JF.fsetCursorPosition(11, 13);

			// Draw Win counters
			JF.fsetCursorPosition(0, 17);
			JF.fconsole_c(cGreen);
			cout << Player1name;
			JF.fconsole_c(cTeal);
			cout << " wins: ";
			JF.fconsole_c(cLime);
			cout << Player1Wins;

			JF.fsetCursorPosition(0, 18);
			JF.fconsole_c(cDarkRed);
			cout << Player2name;
			JF.fconsole_c(cTeal);
			cout << " wins: ";
			JF.fconsole_c(cLime);
			cout << Player2Wins;


			// The recursive game loop starts here.
			while (GameRoom)
			{
				// Reset Cursor
				JF.fsetCursorPosition(0, 0);

				// At the start of our move we empty the Input to flag.
				Input = '\0';

				// We lock the Console Window Size
				JF.fSetConsoleSize(1200, 800);

				// Determine if the current player is an AI player or a human player. If it is a human player then we go through the regular input procedures. If it is an AI player then we go through AI procedures.
				if (GameType == 0) // Player vs AI
				{
					if (cPlayer == 0)
					{
						MoveType = 0;
					}
					else if (cPlayer == 1)
					{
						MoveType = 1;
					}
				}

				if (GameType == 2) // AI vs AI
				{
					MoveType = 1;
				}

				if (GameType == 1) // Player vs Player
				{
					MoveType = 0;
				}

				if (MoveType == 1)
				{
					JF.fsetCursorPosition(13, 13);
					JF.fconsole_c(cWhite);
					cout << "Press Enter to Continue!      ";
				}

				if (MoveType == 0)
				{
					JF.fsetCursorPosition(13, 13);
					JF.fconsole_c(cLime);
					cout << "Your turn !                  ";
				}

				if (MoveType == 0) // If the next move is a human player move.
				{
					// Here we start the player timer.
					PWatch = clock();

					// Get a single character input from console and convert it into uppercase.
					while (Input == '\0' && GameRoom)
					{
						// We take input and attempt to convert it into an uppercase character.
						JF.fconsole_c(cTeal);
						JF.fsetCursorPosition(11, 13);
						Input = toupper(_getche());

						// Next we assess the input. If the Input is valid and the selected node has not been occupied yet.
						if (Input == 'A' || Input == 'B' || Input == 'C' || Input == 'D' || Input == 'E' || Input == 'F' || Input == 'G' || Input == 'H' || Input == 'I')
						{
							// If the Input was valid but the selected node is already occupied then we give an error message and take input again.
							if (GameGrid[GridMap[Input]] > 0)
							{
								iValid = false;
								Input = '\0';

								JF.fconsole_c(cYellow);
								JF.fsetCursorPosition(12, 13);
								cout << " is Occupied!                    ";
								JF.fsetCursorPosition(11, 13);
							}
							else // If the Node is not yet occupied but the input is valid then we flag the node as occupied and say the input is valid, and increment how many moves we have made.
							{
								Moves += 1;
								iValid = true;


								// 4: Check to see if someone has won.
								if (!Player1Win || !Player2Win)
								{
									for (int i = 0; i < 8; i++)
									{
										l = 0;

										for (int k = 0; k < 3; k++)
										{
											for (int j = 0; j < 9; j++)
											{
												if (GameGrid[j] == cPlayer + 1)
												{
													if (GoalGrid[i][k] == j)
													{
														l += 1;
													}
												}

												if (k >= 2)
												{
													if (l == 2)
													{
														for (int n = 0; n < 3; n++)
														{
															if (GameGrid[GoalGrid[i][n]] == 0)
															{
																// If we got to this point then someone won !
																if (cPlayer == 0)
																{
																	Player1Win = true;
																}
																else if (cPlayer == 1)
																{
																	Player2Win = true;
																}

																j = 9;
																k = 3;
																i = 8;
																n = 4;
															}
														}
													}
												}
											}
										}
									}
								}


								GameGrid[GridMap[Input]] = cPlayer + 1; // Use the input to find its grid in the map index then flag that index as occupied for the current player in the grid array.
							}
						}
						// If the input was not valid then we say the input is not valid, and take input again.
						else
						{
							// If we press escape then return to the Main Menu
							if (Input == 27) // Escape key
							{
								JF.fsetCursorPosition(11, 13);
								GameRoom = false;
								MainMenu = true;
								iValid = false;
								Input = '\0';
							}
							else
							{
								iValid = false;
							}
						}
					}
				}
				else if (MoveType == 1) // If the next move is an AI player move.
				{
					// If it is AI then we clear the Timer message region.
					JF.fsetCursorPosition(0, 15);
					cout << "                                                                ";
					JF.fsetCursorPosition(11, 13);

					while (Input == '\0' && GameRoom)
					{
						// We give the player control initially to specify whether to exit to main menu or continue to next move.
						JF.fconsole_c(cTeal);
						JF.fsetCursorPosition(11, 13);
						Input = toupper(_getche());

						// If the Input was invalid then we get another input.
						if (Input != 27 && Input != 13)
						{
							iValid = false;
							Input = '\0';
						}

						if (Input == 27) // Escape key
						{
							JF.fsetCursorPosition(11, 13);
							GameRoom = false;
							MainMenu = true;
							iValid = false;
							Input = '\0';
							break;
						}

						// This is where the AI's brain lives. The AI works by picking a goal to work towards, but prioritizing defense at every move.
						if (Input == 13) // Enter key (If the player decides to continue the AI's move)
						{
							Input = '\0';
							// IMPOSSIBLE MODE
							// 1: Every round the AI needs to decide what its goal is. At the start a smart AI will always start in a random corner (A,C,G,I), or in the center (E) if it is moving second.
							if (Moves == 0) // First we find out if this is the first move or not.
							{
								// If it is then start in a random corner and continue to the next player's move.
								while (Input != 'A' && Input != 'C' && Input != 'G' && Input != 'I')
								{
									Input = char(JF.fRandom(65, 73)); // A to I
								}
							}
							else // If this is not the first move then see if it is the first move for the opposing AI, or any move after that.
							{
								// 2: A smart AI will always occupy the center on the second move if it is defending.
								if (Moves == 1 && GameGrid[GridMap['E']] == 0) // Find out if only one move has been performed so far and if the center is free then make a decision.
								{
									Input = 'E'; // If this is the second move and the center is free then claim it.
								}
								else if (Moves == 1) // Otherwise grab a corner which is available.
								{
									while (Input != 'A' && Input != 'C' && Input != 'G' && Input != 'I')
									{
										Input = JF.fRandom(65, 73); // A to I
										if (GameGrid[Input - 65] > 0) // If the corner node is occupied then get a different random corner.
										{
											Input = '\0';
										}
									}
								}
								// 3: All the moves after the first and second moves are checked for defensive requirements as well.
								if (Moves > 2)
								{
									// First check to see if there is an imminent chance to win, if there isn't then see if there is an imminent loss threat by assessing if the opponent has claimed at least two of three goal nodes.
									for (int i = 0; i < 8; i++) // There are 8 possible winning outcomes, assess all of them.
									{
										// Then reset the occupied node goal counters before continuing to the next goal assessment.
										l = 0;
										m = 0;

										// Check all vertical, horizontal or diagonal lines (goals).
										for (int k = 0; k < 3; k++)
										{
											// Check the entire Game Matrix
											for (int j = 0; j < 9; j++)
											{
												if (GameGrid[j] == cPlayer + 1) // If a node is occupied by the current player then increment the offensive (l) counter by l.
												{
													if (GoalGrid[i][k] == j)
													{
														l += 1;
													}
												}

												if (GameGrid[j] == (1 + ((cPlayer + 1) % 2))) // Otherwise if a node is occupied by the opposing player then increment the defensive counter (m) by 1.
												{
													if (GoalGrid[i][k] == j)
													{
														m += 1;
													}
												}

												// If we discover a goal then skip the remaining loops.
												if (k >= 2)
												{
													// If two of the three goal nodes are occupied but the third one is free then claim it!
													if (m == 2)
													{
														// Then iterate over the goal again to see if there is an empty node.
														for (int n = 0; n < 3; n++)
														{
															// Now that we know 2 goal nodes have been claimed, we check to see if 1 is free, we then find the free node and claim it!
															if (GameGrid[GoalGrid[i][n]] == 0)
															{
																Input = 65 + GoalGrid[i][n];
																n = 4;
															}
														}
													}
													// If two of the three goal nodes are occupied but the third one is free then claim it!
													if (l == 2)
													{
														// Then iterate over the goal again to see if there is an empty node.
														for (int n = 0; n < 3; n++)
														{
															// Now that we know 2 goal nodes have been claimed, we check to see if 1 is free, we then find the free node and claim it!
															if (GameGrid[GoalGrid[i][n]] == 0)
															{
																// If we got to this point then someone won !
																if (cPlayer == 0)
																{
																	Player1Win = true;
																}
																else if (cPlayer == 1)
																{
																	Player2Win = true;
																}
																Input = 65 + GoalGrid[i][n];
																j = 9;
																k = 3;
																i = 8;
																n = 4;
															}
														}
													}
												}
											}
										}
									}
								}
							}
							// If no offensive or defensive goals exist, then we pick an available move to make next.
							if (Input == '\0')
							{
								// If it is then start in a random corner and continue to the next player's move.
								while (GameGrid[Input - 65] > 0)
								{
									Input = JF.fRandom(65, 73); // A to I
								}
							}
						}
					}

					GameGrid[GridMap[Input]] = cPlayer + 1; // After the AI has decided where to go next, use the input to find its grid in the map index then flag that index as occupied for the current player in the grid array.
					Moves += 1; // Increment the number of moves made.
					iValid = true; // Then continue the visual game loop like normal.
				}

				// Update Timer Notice for human players only.
				if (MoveType == 0)
				{
					JF.fsetCursorPosition(0, 15);
					JF.fconsole_c(cDarkYellow);
					cout << "Notice You only have ";
					JF.fconsole_c(cTeal);
					cout << PTime / 1000;
					JF.fconsole_c(cDarkYellow);
					cout << " seconds to make a move!";
					JF.fsetCursorPosition(11, 13);
				}

				// Timer Verdict for Human players only
				if ((PTime - clock() + PWatch) / 1000 <= 0 && MoveType == 0) // If we have no time left.
				{
					JF.fsetCursorPosition(0, 15);
					JF.fconsole_c(cRed);

					if (cPlayer == 0)
					{
						JF.fconsole_c(cGreen);
						cout << Player1name << " (" << Player1 << ")                    ";

						Player2Win = true;
					}

					if (cPlayer == 1)
					{
						JF.fconsole_c(cDarkRed);
						cout << Player2name << " (" << Player2 << ")                    ";

						Player1Win = true;
					}

					JF.fconsole_c(cRed);
					cout << " time exceeded !                    ";
					JF.fsetCursorPosition(11, 13);
				}

				// Here we execute our game logic once we have a valid input and a timer limit was not exceeded.
				if (iValid)// && !Player1Win && !Player2Win)
				{
					// Next we update our console output with a valid input message for human players only.
					if (MoveType == 0)
					{
						JF.fconsole_c(cLime);
						JF.fsetCursorPosition(12, 13);
						cout << " is Valid!                    ";
						JF.fconsole_c(cLime);
						JF.fsetCursorPosition(11, 13);
					}

					// We specify the coordinates then set the cursor to the appropriate position in the Game's Grid.
					if (Input == 'A') { JF.fsetCursorPosition(1, 6); }
					if (Input == 'B') { JF.fsetCursorPosition(5, 6); }
					if (Input == 'C') { JF.fsetCursorPosition(9, 6); }
					if (Input == 'D') { JF.fsetCursorPosition(1, 8); }
					if (Input == 'E') { JF.fsetCursorPosition(5, 8); }
					if (Input == 'F') { JF.fsetCursorPosition(9, 8); }
					if (Input == 'G') { JF.fsetCursorPosition(1, 10); }
					if (Input == 'H') { JF.fsetCursorPosition(5, 10); }
					if (Input == 'I') { JF.fsetCursorPosition(9, 10); }

					// We write the player's symbol into the appropriate game grid position.
					if (cPlayer == 0) // Player 0 is player (1) Green and Player 1 is player (2) DarkRed
					{
						JF.fconsole_c(cGreen);
						cout << Player1;
					}
					else if (cPlayer == 1)
					{
						JF.fconsole_c(cDarkRed);
						cout << Player2;
					}

					// Move to the next player, then update the Screen to show which player it is now, and make the current AI difficulty setting the same as the next player's AI difficulty !
					JF.fsetCursorPosition(17, 3);
					if (cPlayer == 0)
					{
						cPlayer = 1;
						cAIDifficulty = AIDifficultyP2;

						JF.fconsole_c(cDarkRed);
						cout << Player2name << " (" << Player2 << ")                  ";
					}
					else if (cPlayer == 1)
					{
						cPlayer = 0;
						cAIDifficulty = AIDifficultyP1;

						JF.fconsole_c(cGreen);
						cout << Player1name << " (" << Player1 << ")                  ";
					}
				}

				// If the input is not valid then we give an error message for human players only.
				if (!iValid && MoveType == 0)
				{
					// if the Input is invalid
					JF.fconsole_c(cRed);
					JF.fsetCursorPosition(12, 13);
					cout << " is Invalid!                    ";
					JF.fsetCursorPosition(11, 13);
				}

				JF.fsetCursorPosition(22, 17);
				cout << "                            ";
				JF.fsetCursorPosition(22, 18);
				cout << "                            ";

				if (Player1Win)
				{
					JF.fsetCursorPosition(22, 17);
					JF.fconsole_c(cTeal);
					cout << "<<< ";
					JF.fconsole_c(cGreen);
					cout << Player1name;
					JF.fconsole_c(cTeal);
					cout << " won !";

					Player1Wins += 1;
				}

				if (Player2Win)
				{
					JF.fsetCursorPosition(22, 18);
					JF.fconsole_c(cTeal);
					cout << "<<< ";
					JF.fconsole_c(cDarkRed);
					cout << Player2name;
					JF.fconsole_c(cTeal);
					cout << " won !";

					Player2Wins += 1;
				}

				// Draw
				if (Moves == 9)
				{
					JF.fsetCursorPosition(22, 18);
					JF.fconsole_c(cTeal);
					cout << "<<< ";
					JF.fconsole_c(cYellow);
					cout << " It's a Draw !";

					JF.fsetCursorPosition(22, 17);
					JF.fconsole_c(cTeal);
					cout << "<<< ";
					JF.fconsole_c(cYellow);
					cout << " It's a Draw !";
				}

				JF.fsetCursorPosition(0, 17);
				JF.fconsole_c(cGreen);
				cout << Player1name;
				JF.fconsole_c(cTeal);
				cout << " wins: ";
				JF.fconsole_c(cLime);
				cout << Player1Wins;

				JF.fsetCursorPosition(0, 18);
				JF.fconsole_c(cDarkRed);
				cout << Player2name;
				JF.fconsole_c(cTeal);
				cout << " wins: ";
				JF.fconsole_c(cLime);
				cout << Player2Wins;

				// Reset everything when a player has won !
				if (Player1Win || Player2Win || Moves == 9)
				{
					// Reset Graphics
					JF.fsetCursorPosition(0, 6);
					int j = 0;
					for (int i = 0; i < 5; i++)
					{
						if (i == 0 || i == 2 || i == 4)
						{
							for (int k = 0; k < 3; k++)
							{
								JF.fconsole_c(cTeal);
								cout << " " << char(65 + j) << " ";
								JF.fconsole_c(cPink);
								j++;

								if (k <= 1)
								{
									cout << "|";
								}
							}
						}
						else
						{
							cout << "\n___ ___ ___\n";
						}
					}

					//Reset Game Grid
					for (int i = 0; i < 9; i++)
					{
						GameGrid[i] = 0;
					}

					// Reset Winning Flags
					Player1Win = false;
					Player2Win = false;

					Moves = 0;

					Input = '\0';
					while (Input = '\0')
					{
						Input = cin.get();
					}
				}
			}

			if (!GameRoom)
			{
				// If we return to the main menu then clear the screen and set the flag.
				system("cls");
				MainMenu = true;
			}
		}
	}		
}
