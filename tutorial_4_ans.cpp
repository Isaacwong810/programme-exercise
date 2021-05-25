// Student name: 
// Student ID  : 

// Submission deadline: Thursday, 21 Feb, 2 pm

#include <iostream>
#include <iomanip>  //setw()
#include <cstdlib>
#include <ctime>

using namespace std;


struct intSet
{
	// Data structure to represent a set of integers.
	// Members in a set are distinct.
	// Numbers in the array are maintained in ascending order.

	int *store;   // array store[] is created using dynamic memory allocation
	int maxSize;  // physical size of the array store[]
	int size;     // number of elements in the set
};

//----------------------------------------------- functions to be implemented by you

void setIntersection(const intSet& setA, const intSet& setB, intSet& setC)
{
	// Compute setC = setA intersect setB
	// Your algorithm should only require linear time.

	// You need to create the array store[] in setC

	setC.maxSize = (setA.size < setB.size) ? setA.size : setB.size;
	setC.store = new int[setC.maxSize];
	
	int i = 0, j = 0, k = 0;

	while (i < setA.size && j < setB.size)
	{
		if (setA.store[i] <= setB.store[j])
		{
			if (setA.store[i] == setB.store[j])
				setC.store[k++] = setB.store[j++];
			i++;
		}
		else
			j++;
	}
	setC.size = k;
}

bool isSubset(const intSet& setA, const intSet& setB)
{
	// Determine if setA is a subset of setB.
	// Your algorithm should only require linear time.

	int i = 0, j = 0;

	while (i < setA.size && j < setB.size)
	{
		if (setA.store[i] < setB.store[j])
			break;
		else if (setA.store[i] == setB.store[j])		
			i++;

		j++;
	}
	// assert: i = number of elements in setA that are found in setB
	return i == setA.size;
}

void search2DArray(int **A, int row, int col, int key, int& r, int& c)
{	
	/*
	Elements in A[row][col] are logically arranged in row-major order, 
	and sorted in ascending order.

	Search for the key in the 2D array A[][] using binary search. 
	If the key is found, determine r and c such that A[r][c] == key.
	If the key is not found, set r and c to -1.	
	*/

	int low = 0;
	int high = row * col - 1;
	bool found = false;

	while (low <= high && !found)
	{
		int mid = (low + high) / 2;
		r = mid / col;
		c = mid % col;

		if (A[r][c] > key)
			high = mid - 1;
		else if (A[r][c] < key)
			low = mid + 1;
		else
			found = true;
	}
	
	if (!found)
		r = c = -1;
}

//----------------------------------------------- functions prepared for you
int* gen1DArray(int n)
{
	int *A = new int[n];
	int delta = 3;
	int k = 1 + rand() % delta;
	for (int i = 0; i < n; i++)
	{
		A[i] = k;
		k += 1 + rand() % delta;
	}
	return A;
}

void printIntSet(const intSet& set)
{
   for (int i = 0; i < set.size; i++)
   {
	   if (i > 0 && i % 10 == 0)
		   cout << endl;
	   cout << setw(4) << set.store[i] << ",";
   }
   cout << endl << endl;
}

int** gen2DArray(int row, int col)
{
	// Create the array A[row][col] such that
	// 1. A[i][j] <= A[i][j+1] for 0 <= j < col-1; and
	// 2. A[i][n-1] <= A[i+1][0] for 0 <= i < row-1.

	int **A = new int*[row];
	for (int i = 0; i < row; i++)
		A[i] = new int[col];

	int k = 1 + rand() % 7;
	int delta = col / 2;

	for (int i = 0; i < row; i++)	
		for (int j = 0; j < col; j++)
		{
			A[i][j] = k;
			k += rand() % delta;
		}
	
	return A;
}

void print2DArray(int *A[], int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << setw(4) << A[i][j] << ",";
		cout << endl;
	}
	cout << endl;
}


void part_1()
{
	cout << "Part-1: Integer set\n\n";

	intSet setA, setB, setC, setD;

	setA.size = setA.maxSize = 10;
	setA.store = gen1DArray(setA.size);

	setB.size = setB.maxSize = 8;
	setB.store = gen1DArray(setB.size);

	cout << "setA:\n";
	printIntSet(setA);

	cout << "setB:\n";
	printIntSet(setB);

	setIntersection(setA, setB, setC);
	cout << "setC:\n";
	printIntSet(setC);

	setD.size = 0;
	setD.maxSize = 8;
	setD.store = new int[setD.maxSize];

	cout << "setD: empty\n\n";

	cout << "setB is subset of setA : " << isSubset(setB, setA) << endl;
	cout << "setC is subset of setA : " << isSubset(setC, setA) << endl;
	cout << "setC is subset of setB : " << isSubset(setC, setB) << endl;
	cout << "setD is subset of setA : " << isSubset(setD, setA) << endl;
	cout << "setC is subset of setD : " << isSubset(setC, setD) << endl;

	delete[] setA.store;
	delete[] setB.store;
	delete[] setC.store;
	delete[] setD.store;
}

void part_2()
{
	cout << "\n-----------------------------------------------\n\n";
	cout << "Part-2: 2D array and binary search\n\n";

	int row, col;
	cout << "Enter number of rows: ";
	cin >> row;

	cout << "Enter number of cols: ";
	cin >> col;

	int **A2 = gen2DArray(row, col);
	cout << "\nA2[][]:\n";
	print2DArray(A2, row, col);

	int value;
	do
	{
		cout << "\nEnter search value (enter -1 to exit): ";
		cin >> value;
		if (value >= 0)
		{
			int r, c;
			search2DArray(A2, row, col, value, r, c);

			if (r >= 0 && c >= 0)
				cout << value << " is found at [" << r << "][" << c << "]\n";
			else
				cout << value << " is not found\n";
		}
	} while (value >= 0);

	for (int i = 0; i < row; i++)
		delete[] A2[i];
	delete[] A2;
}

int main()
{
	srand((unsigned)time(NULL));	

	part_1();
	part_2();

	system("pause");
	return 0;
}