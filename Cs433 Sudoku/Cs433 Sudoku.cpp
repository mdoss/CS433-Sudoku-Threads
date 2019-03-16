// Cs433 Sudoku.cpp : This file contains the 'main' function. Progprecompiled header visual studioram execution begins and ends there.
//

#include <iostream>
#include <thread>

using namespace std;
int examplePuzzle[9][9] = 
{
{5, 3, 4, 6, 7, 8, 9, 1, 2},
{6, 7, 2, 1, 9, 5, 3, 4, 8},
{1, 9, 8, 3, 4, 2, 5, 6, 7},
{8, 5, 9, 7, 6, 1, 4, 2, 3},
{4, 2, 6, 8, 5, 3, 7, 9, 1},
{7, 1, 3, 9, 2, 4, 8, 5, 6},
{9, 6, 1, 5, 3, 7, 2, 8, 4},
{2, 8, 7, 4, 1, 9, 6, 3, 5},
{3, 4, 5, 2, 8, 6, 1, 7, 9}
}; //should be a real solution if i copied it from online correctly

int workerValid[11] = { 0 };

void checkSubGrid(int index)
{
	int repeatCheckArray[10] = { 0 };
	for (int i = (index / 3) * 3; i < ((index / 3) * 3) + 3; i++) // for some reason i decided against passing a structure and did this instead because i thought it would be easier. its ugly but its just making sure it starts at the right index for the subgrid
	{
		//cout << "i: " << i << endl;
		for (int k = (index * 3) % 9; k < ((index * 3) % 9) + 3; k++)
		{
			//cout << "k: " << k << endl;
			int value = examplePuzzle[i][k];
			//cout << "value: " << value << endl;
			if (repeatCheckArray[value] != 0)
				return;
			else
			{
				repeatCheckArray[value] = 1;
			}
		}
		
	}
	workerValid[index] = 1;
}

void resetArray(int (&arr)[10])
{
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		arr[i] = 0;
	}
}

void checkColumns()
{
	int repeatCheckArray[10] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		for (int k = 0; k < 9; k++)
		{
			int value = examplePuzzle[k][i];
			//cout << "value: " << value << " | repeat: " << repeatCheckArray[value] endl;
			if (repeatCheckArray[value] != 0)
			{
				cout << "Column " << i + 1<< " is invalid" << endl;
				return;
			}
			else
				repeatCheckArray[value] = 1;
		}
		resetArray(repeatCheckArray);
	}
	workerValid[9] = 1;
}

void checkRows()
{
	int repeatCheckArray[10] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		for (int k = 0; k < 9; k++)
		{
			int value = examplePuzzle[i][k];
			if (repeatCheckArray[value] != 0)
			{
				cout << "Row " << i + 1 << " is invalid" << endl;
				return;
			}
			else
				repeatCheckArray[value] = 1;
		}
		resetArray(repeatCheckArray);
	}
	workerValid[10] = 1;
}

int main()
{
	thread subGrids[9];
	for (int i = 0; i < 9; i++)
	{

		subGrids[i] = thread(checkSubGrid, i);

	}
	thread colTh = thread(checkColumns);
	colTh.join();
	thread rowTh = thread(checkRows);
	rowTh.join();
	for (int i = 0; i < 9; i++)
	{
		subGrids[i].join();
	}
	cout << "---Subgrid workers---" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << workerValid[i] << endl;
	}
	cout << "---Column worker---\n " << workerValid[9] << endl;
	cout << "---Row worker---\n " << workerValid[10] << endl;
	for (int i = 0; i < 11; i++)
	{
		if (workerValid[i] != 1)
		{
			cout << "Invalid Sodoku Puzzle" << endl;
			return 0;
		}
	}
	cout << "Valid Sodoku Puzzle" << endl;
	return 0;
}

