// Student name: wong ka ho
// Student ID  : 54816829

// Submission deadling: Thursday, 4 April 2019, 2 pm

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

struct Coordinate
{
	int x, y;  // x is the row-index, y is the col-index
};

ostream& operator<<(ostream& osObject, const Coordinate& d)
{
	osObject << "(" << d.x << ", " << d.y << ")";
	return osObject;
}

//----------------------------------------------- function to be implemented by student

//void printArrayd(int **d, int row, int col)       //check function
//{
//
//	cout << "Array[" << row << "][" << col << "]" << endl << endl;
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			cout<<" " << d[i][j]<<" ";
//		}
//		cout << endl;
//	}
//}


void findShortestPath(char **A, int row, int col, stack<Coordinate>& s)
{
	// A[][] represents the maze of size row x col.

	// The array offset[4] allows you to find out the coordinates of the 
	// 4 neighboring points of a given point using a for-loop.

	Coordinate offset[4];    
	offset[0].x = offset[1].x = 0;
	offset[0].y = -1;
	offset[1].y = 1;
	offset[2].y = offset[3].y = 0;
	offset[2].x = -1;
	offset[3].x = 1;

	int **d;  // d[][] is used for finding the distances of other points from the start-point
	d = new int*[row];
	for (int i = 0; i < row; i++)
		d[i] = new int[col];

	queue<Coordinate> q;  
	Coordinate p,g;  // for saving the coordinate
	int distance=0;
	// q.front() return the front element in the queue
	// q.push(e) add element e to the queue
	// q.pop()   remove the front element from the queue

	for (int i = 0; i < row; i++) {      // fill the d[][]
		for (int j = 0; j < col; j++) {
			if (A[i][j] != 'S') {
				d[i][j] = -1;
			}
			else {
				d[i][j] = distance;
				p.x = i;
				p.y = j;
				q.push(p);
			}
		}
	}


	bool found = false;
	while (!q.empty() && !found) {
		g.x = q.front().x;						//save the coordinate of starting point
		g.y = q.front().y;
		q.pop();								// move out the queue when the point is checked
		distance=d[g.x][g.y];                   //increase the distance while moving
		for (int i = 0; i < 4; i++) {           //check 4 direction
			p.x = g.x + offset[i].x;
			p.y = g.y + offset[i].y;
			if (p.x >= 0 && p.x < row && p.y >= 0 && p.y < col && d[p.x][p.y] == -1) { // if it is in the bound and not checked
				if (A[p.x][p.y] == '.') {            // if it is not a wall
					d[p.x][p.y] = distance+1;
					q.push(p);
				}
				if (A[p.x][p.y] == 'E') {           // if it is end point
					d[p.x][p.y] = distance+1;
					s.push(p);
					found = true;
					break;
				}
			}
		}
	}


	if (found) {                              //track the shortest path

		for (int i = d[p.x][p.y]; i > 0;i--) {           // define the maximum step to prevent over tracking
			for (int j = 0; j < 4; j++) {				// search 4 direction
				g.x = p.x + offset[j].x;				//starting in end point and change the point in every checking
				g.y = p.y + offset[j].y;
				if (g.x >= 0 && g.x < row && g.y >= 0 && g.y < col ) {
					if (d[g.x][g.y] == d[p.x][p.y] - 1) {                  // if next point is smaller than the previous with 1
						p = g;
						s.push(p);
						break;
					}
				}
			}
			
		}
	}


	/*printArrayd(d, row, col);*/  // checking function 

}



//---------------------------------------------------- functions prepared for student

char** readFile(const char filename[], int& row, int& col)
{
	ifstream inFile(filename);
	if (!inFile.is_open())
	{
		cout << "Cannot open data file " << filename << endl;
		system("pause");
		exit(1);
	}

	inFile >> row >> col;  // read the values of row and col

	//create the 2D array A[row][col]
	char **A;
	A = new char*[row];
	for (int i = 0; i < row; i++)	
		A[i] = new char[col];
	
	//read in the contents of A[][]
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			inFile >> A[i][j];

	inFile.close();
	return A;
}

void printArray(char **A, int row, int col)
{
	Coordinate startPoint, endPoint;

	cout << "Array[" << row << "][" << col << "]" << endl << endl;
	for (int i = 0; i < row; i++)	
	{
		for (int j = 0; j < col; j++)
		{
			cout << A[i][j];
			if (A[i][j] == 'S')
			{
				startPoint.x = i;
				startPoint.y = j;
			}
			else if (A[i][j] == 'E')
			{
				endPoint.x = i;
				endPoint.y = j;
			}			
		}
		cout << endl;
	}
	
	cout << endl;
	cout << "start-point : " << startPoint << endl;
	cout << "end-point : " << endPoint << endl;
	cout << endl;
}


int main()
{	
	const char *files[] = {"T10-data-1.txt", "T10-data-2.txt", "T10-data-3.txt"};
	char **A;
	int row, col;

	for (int i = 0; i < 3; i++)
	{
		cout << "\n------------------------------------------\n\n";
		cout << "Test file : " << files[i] << endl << endl;

		A = readFile(files[i], row, col);
		printArray(A, row, col);

		stack<Coordinate> s;
		findShortestPath(A, row, col, s);

		if (!s.empty())
		{
			cout << "\nShortest path from start-point to end-point:\n";

			cout << s.top();
			s.pop();

			int count = 1;
			while (!s.empty())
			{
				cout << " -> ";
				if (count % 5 == 0)
					cout << endl;

				cout << s.top(); 
				s.pop();				
				count++;
			}
			cout << endl;
		}
		else
			cout << "DO NOT find any path from start-point to end-point\n";

		for (int j = 0; j < row; j++)
			delete[] A[j];
		delete[] A;  // return the memory space to the OS
	}

	system("pause");
	return 0;
}