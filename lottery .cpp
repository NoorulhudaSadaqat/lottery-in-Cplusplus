#include<iostream>
#include<fstream>
#include<string>
#include<ctime>

using namespace std;
int main()
{
	srand(time(0));
	//asking user for there name to generate file of his/her name
	string userName = "Ali"; int numberOfPlay = 1;
	cout << "Enter your name please : ";
	cin >> userName;
	
	//asking user to how many time he/she wants to play the game
	cout << "\n How many times you want to play??  For Each play you have to pay 5$ \n \t Please enter the number : ";
	cin >> numberOfPlay;
	
	//to check if user enters a wrong input like an alpahbet or other special characters
	while (cin.fail())	
	{
		cin.clear(); //clearing the input stream to avoid errors
		cin.ignore();
		cout << "Error: You entered a wrong Input\n" << endl;
		cin >> numberOfPlay;
	}
	
	int userEnteredchar;
	int playCount = 1; int winningNumberCount = 0, checkRepeat;
	
	//In this while loop User we will play a complete turn
	while (numberOfPlay > 0)
	{
		//opening the file which will contain winning numbers
		ofstream lotteryFile(userName + "LotteryFile.txt");	
		
		int winningNumber;
		lotteryFile << "This Weeks winning numbers" << endl;
		
		int rand_1= 0 ,rand_2 = 0,rand_3 =0 , rand_4 = 0, rand_5 = 0; // to hold five winning numbers
		rand_1 = rand() % 49 + 1;
	
		// avoid repeating the numbers
		while(rand_2 == rand_1 || rand_2 == 0)
			rand_2 = rand() % 49 + 1;
		while(rand_3 == rand_2 || rand_3 == rand_1 || rand_3 == 0)
			rand_3 = rand() % 49 + 1;
		while(rand_4== rand_3 || rand_4 == rand_2 || rand_4 == rand_1 || rand_4 == 0)
			rand_4 = rand() % 49 + 1;
		while(rand_5 == rand_4 || rand_5== rand_3 || rand_5 == rand_2 || rand_5 == rand_1 || rand_5 == 0)
			rand_5 = rand() % 49 + 1;
		cout<<rand_1<<' '<<rand_2<<' '<<rand_3<<' '<<rand_4<<' '<<rand_5<<endl;
		lotteryFile<<rand_1<<' '<<rand_2<<' '<<rand_3<<' '<<rand_4<<' '<<rand_5;	// store in a file
		
		//opening other file which will store the user entered numbers
		fstream enteredNumber("enteredNumber.txt", ios::out | ios::in);
		winningNumberCount = 0;// to get count of user entered numbers
		
		cout << "\n\n\n\t\t\t\tPLay # " << playCount << endl;
		cout << "\t Keep in mind the winning numbers must be in range 1-49\n\n" << endl;
		
		// in this loop we will take 5 numbers from user and will check if the input is under given constraints
		while (winningNumberCount < 5)
		{
			cout << "Enter the winning number : ";
			cin >> userEnteredchar;
			
			//to check if user enters a wrong input like an alpahbet or other special characters
			while (cin.fail())	
			{
				cin.clear(); //clearing the input stream to avoid errors
				cin.ignore(256, '\n');
				cout << "Error: You entered a wrong Input\n" << endl;
				cout << "Enter the winning number : ";
				cin >> userEnteredchar;
			}
			
		    if (userEnteredchar < 1 || userEnteredchar>49)
			{
			   cout << "Error: You entered a wrong Input\n" << endl;
			}
			else
			{
				//taking the file pointer in the beginning to read the file from top
				enteredNumber.seekg(0, ios::beg);	
				bool flag = true;
				
				// in this loop we will check if the entered number is repeating or not
				for (int i = 0; i < winningNumberCount; i++)
				{
					enteredNumber >> checkRepeat;
					cout<<"Testing: "<<checkRepeat<<endl;
					if (userEnteredchar == checkRepeat)
					{
						flag = false;// if the number is already in the file set the flag false
						break;
					}
				}
				
				enteredNumber.seekg(0, ios::end);// taking pointer again to the end
				
				if (flag)	// if the entered number is not repeated place it at the end of file
				{
					enteredNumber << userEnteredchar << endl;
					winningNumberCount++;
				}
				else  //else print the error message
				{
					cout << "\n\t\tError : Number is repeated enter again !!\n" << endl;
				}

			}
		}
		//after taking all 5 numbers from user we are closing both files
		enteredNumber.close();
		lotteryFile.close();
		string title;
		
		//now we will open both files in input mode to get numbers from them
		ifstream WinningNumbersfile(userName + "LotteryFile.txt");
		int WinningNumbers = 0, userNumbers = 0;
		int rightNumbers = 0;
		
		if (WinningNumbersfile.good())
		{
			getline(WinningNumbersfile, title);//getting the tilte in the string that we placed on the top

			for (int i = 0; i < 5; i++)
			{
				WinningNumbersfile >> WinningNumbers;
				cout<<"Reading from file: "<<WinningNumbers<<endl;
				ifstream UserNumbersfile("enteredNumber.txt"); // opeing this file in the loop so that everytime pointer start checking from top
				UserNumbersfile >> userNumbers;
				cout<<"user number: "<<userNumbers<<endl;
				// in this loop we will check how many user entered number matches to the winning numbers
				while (!UserNumbersfile.eof())
				{
					if (userNumbers == WinningNumbers)
					{
						rightNumbers++;
					}
					UserNumbersfile >> userNumbers;
					if(UserNumbersfile.eof())
						break;
					cout<<"user number: "<<userNumbers<<endl;
				}
			}
		}
		//printing the end message of each play
		else{ 
			cout << "Error! Lottery File Not opened, closing the game." << endl;
			return 0;
		}
		cout << "\n\n\n\n";
		WinningNumbersfile.close();
		WinningNumbersfile.open(userName + "LotteryFile.txt");
		
		while(!WinningNumbersfile.eof()){
			string line;
			getline(WinningNumbersfile,line);
			cout<<line<<endl;
		}
		
		if (rightNumbers == 0)
		{
			cout<<"You weren't able to guess any number\n";
			cout << "\t\tYou Lost $5 BETTER LUCK NEXT TIME " << endl;
		}
		else if (rightNumbers == 1)
		{
			cout<<"You guessed only one number\n";
			cout << "\t\tYou WON $1 GOOD LUCK FOR NEXT TIME " << endl;
		}
		else if (rightNumbers == 2)
		{
			cout<<"You guessed two numbers\n";
			cout << "\t\tYou WON $2 GOOD LUCK FOR NEXT TIME " << endl;
		}
		else if (rightNumbers == 3)
		{
			cout<<"You guessed three numbers\n";
			cout << "\t\tYou WON $10 HAVE FUN! " << endl;
		}
		else if (rightNumbers == 4)
		{
			cout<<"You guessed 4 numbers\n";
			cout << "\t\tYOHOOOOO YOU WON $100 CONGRATULATIONS" << endl;
		}
		else if (rightNumbers == 5)
		{
			cout<<"You guessed all the numbers!\n";
			cout << "\t\tAMAZING PERFORMANCE YOU WON $1000 CONGRATULATIONS " << endl;
		}
		cout << "\n\n\n";
		numberOfPlay--;
		playCount++;
		
		//opening both files in ouput mode so that both of them get empty and we can store numbers in them again
		ofstream empty1(userName + "LotteryFile.txt");
		ofstream empty2("enteredNumber.txt");
	}

}
