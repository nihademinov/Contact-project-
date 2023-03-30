#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void arrowHere_2(int realPosition, int arrowPosition) {
	if (realPosition == arrowPosition) {
		SetConsoleTextAttribute(console, 9);
		cout << " ----->>    ";
	}
	else {
		SetConsoleTextAttribute(console, 4);
		cout << "          ";
	}
}

			bool chechCreate = false;
		bool checkDelete = false;
		bool checkSearchName = false;
		bool checkSearchPhone = false;
		bool checkShowContact = false;


//bool choice_Back_ = false;


void AskToPlayer()
{
	cout << endl;
	int position = 1;
	int keyPressed = 0;

	while (keyPressed != 13)
	{
		system("cls");
		SetConsoleTextAttribute(console, 11);
		cout << "\n\n\n\n\n\n";
		cout << "PLEASE,CHOICE FUNCTIONS" << endl;
		arrowHere_2(1, position);
		cout << "Delete by contact\n";
		arrowHere_2(2, position);
		cout << "Search by name \n";
		arrowHere_2(3, position);
		cout << "Serach by phone \n";
		arrowHere_2(4, position);
		cout << "Create new contact \n";
		arrowHere_2(5, position);
		cout << "Show all contact \n";


		keyPressed = _getch();

		if (keyPressed == 80 && position != 5)
		{
			position++;
		}
		else if (keyPressed == 72 && position != 1)
		{
			position--;
		}
		else
		{
			position = position;
		}
	}
		
		

	switch (position)
	{
	case 1:
		//system("cls");
		SetConsoleTextAttribute(console, 7);
		checkDelete = true;
		break;
	case 2:
		//system("cls");
		SetConsoleTextAttribute(console, 7);
		checkSearchName = true;
		break;
	case 3:
		//system("cls");
		SetConsoleTextAttribute(console, 7);
		checkSearchPhone = true;
		break;


	case 4:
		//system("cls");
		SetConsoleTextAttribute(console, 7);
		chechCreate = true;
		break;
	case 5:
		//system("cls");
		SetConsoleTextAttribute(console, 7);
		checkShowContact = true;
		break;

	}
}
