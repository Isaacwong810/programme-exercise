// Student name: wong ka ho
// Student ID  : 54816829

/*
	Submission deadline: Thursday, 28 Feb 2019, 2 pm.

	This exercise is on sorting.
	We shall compare the performances of bubble sort, insertion sort, and qsort
	for sorting arrays of cstring and C++ string objects.

	A template (generic) function for insertion sort is given to you.
	You need to define your own compare functions in order to use the template insertionSort function.
	We want to sort an array of string (or cstring) by length, 
	and strings of the same length are sorted by alphabetical order.

	In the second part, you need to design a template function for bubble sort.

	In the third part, you need to define the compare functions required by qsort.

	Observe the performances of the 3 algorithms, and the differences in the computation
	time for sorting arrays of cstring and string.
	You need to understand the reasons behind the differences in performances of the 3 algorithms.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Part-1: Define your compare functions for using the template insertionSort function


template<class Type>
void insertionSort(Type *x, int n, int (*compare)(const Type&, const Type&))
{
	for (int i = 1; i < n; i++)
	{
		Type t = x[i];
		int j;
		for (j = i-1; j >= 0 && compare(x[j], t) > 0; j--)
			x[j+1] = x[j];
		x[j+1] = t;
	}
}

void test_insertionSort(char **a, string *s, int n)
{
	// Sort the list of strings by length, and 
	// strings of the same length are sorted in alphabetical order

	clock_t begin, end;
	double elapsedTime;

	cout << "Insertion sort:\n\n";
	cout << "Sort an array of char*, size = " << n << endl;
	begin = clock();

	// *** add your statement to sort the array a[] using insertionSort
	for (int i = 0; i < n; i++)
	{
		string t = a[i];
		int length = t.length();
		for (int k = 1; k < length-1; k++) {
			int j;
			char p = char(t[k]);
			for (j = k - 1; j >= 0 && t[j] > p; j--) {
				t[j + 1] = t[j];
			}
			t[j + 1] = p;
		}
		string(a) = t;
	}

	end = clock();
	elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
	cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;	

	cout << "Sort an array of string, size = " << n << endl;
	begin = clock();

	// *** add your statement to sort the array s[] using insertionSort
	for (int i = 0; i < n; i++)
	{
		string t = s[i];
		int length = t.length();
		for (int k = 1; k < length; k++) {
			int j;
			char p = t[k];
			for (j = k - 1; j >= 0 && t[j] > p; j--) {
				t[j + 1] = t[j];
			}
			t[j + 1] = p;
		}
		s[i] = t;
	}

	end = clock();
	elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
	cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;		

	cout << "\nFirst 5 and last 5 strings in the sorted list:\n\n";
	for (int i = 0; i < 5; i++)
		cout << a[i] << " : " << s[i] << endl;
	cout << endl;
	for (int i = 5; i > 0; i--)
		cout << a[n-i] << " : " << s[n-i] << endl;
}

//-------------------------------------------------------------------------------------

// Part-2: Define your template function bubbleSort



void test_bubbleSort(char **a, string *s, int n)
{
	// Sort the list of strings by length, and 
	// strings of the same length are sorted in alphabetical order

	clock_t begin, end;
	double elapsedTime;

	cout << "\n------------------------------------------------------\n";
	cout << "Bubble sort:\n\n";
	cout << "Sort an array of char*, size = " << n << endl;
	begin = clock();

	// *** add your statement to sort the array a[] using bubbleSort
	for (int i = 0; i < n; i++) {
		string x = a[i];
		int lengthx = x.length();
		int switched = 1;
		for (int pass = 1; pass < lengthx && switched; pass++)
		{
			switched = 0;
			for (int j = 0; j < lengthx - pass; j++)
				if (x[j] > x[j + 1]) // assert: j+1 is a valid index
				{
					int temp = x[j];
					x[j] = x[j + 1];
					x[j + 1] = temp;
					switched = 1;
				}
		}
		string a = x;
	}

	end = clock();
	elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
	cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;	

	cout << "Sort an array of string, size = " << n << endl;
	begin = clock();

	// *** add your statement to sort the array s[] using bubbleSort
	{
		for (int i = 0; i < n; i++) {
			string x = s[i];
			int lengthx = x.length();
			int switched = 1;
			for (int pass = 1; pass < lengthx && switched; pass++)
			{
				switched = 0;
				for (int j = 0; j < lengthx - pass; j++)
					if (x[j] > x[j + 1]) // assert: j+1 is a valid index
					{
						int temp = x[j];
						x[j] = x[j + 1];
						x[j + 1] = temp;
						switched = 1;
					}
			}
			s[i] = x;
		}
	}

	end = clock();
	elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
	cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;		

	cout << "\nFirst 5 and last 5 strings in the sorted list:\n\n";
	for (int i = 0; i < 5; i++)
		cout << a[i] << " : " << s[i] << endl;
	cout << endl;
	for (int i = 5; i > 0; i--)
		cout << a[n-i] << " : " << s[n-i] << endl;
}

//-------------------------------------------------------------------------------------

// Part-3: Define your compare functions here for using qsort
void swap(string x[], int i, int j)
{
	string t = x[i];
	x[i] = x[j];
	x[j] = t;
}

int partition(string x[], int s, int e)
{
	// precondition: s < e
	int i = s + 1;
	int j = e;
	bool done = false;
	while (!done)
	{
		while (i < j && x[i] <= x[s])
			i++;
		while (x[j] > x[s]) // j will NOT go out of bound
			j--;
		if (i < j)
			swap(x, i, j);
		else
			done = true;
	}
	swap(x, s, j); // swap x[s] and x[j]
	return j;
}
void simpleQuicksort(string x[], int start, int end)
{
	if (start < end)
	{
		int j = partition(x, start, end);
		simpleQuicksort(x, start, j - 1);
		simpleQuicksort(x, j + 1, end);
	}
}

void test_qsort(char **a, string *s, int n)
{
	// Sort the list of strings by length, and 
	// strings of the same length are sorted in alphabetical order.

	clock_t begin, end;
	double elapsedTime;

	cout << "\n------------------------------------------------------\n";
	cout << "qsort:\n\n";
	cout << "Sort an array of char*, size = " << n << endl;
	begin = clock();

	// *** add your statement to sort the array a[] using qsort
	for (int i = 0; i < n; i++) {
		int lengthq = s->length();
		simpleQuicksort(s, 0, lengthq);
	}
	end = clock();
	elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
	cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;	

	cout << "Sort an array of string, size = " << n << endl;
	begin = clock();

	// *** add your statement to sort the array s[] using qsort
	for (int i = 0; i < n; i++) {
		int lengthq = s->length();
		simpleQuicksort(s, 0, lengthq);
	}

	


	end = clock();
	elapsedTime = (double)(end - begin)/CLOCKS_PER_SEC;
	cout << "Elapsed time = " << elapsedTime << " seconds" << endl << endl;		

	cout << "\nFirst 5 and last 5 strings in the sorted list:\n\n";
	for (int i = 0; i < 5; i++)
		cout << a[i] << " : " << s[i] << endl;
	cout << endl;
	for (int i = 5; i > 0; i--)
		cout << a[n-i] << " : " << s[n-i] << endl;
	cout << endl;
}

// ---------------------------------------------- other functions given to you

void randomize(char **a, string *s, int n)
{
	for (int i = 0; i < n; i++)
	{
		int j = rand() % n;
		char *t = a[i];
		a[i] = a[j];
		a[j] = t;

		string w = s[i];
		s[i] = s[j];
		s[j] = w;
	}
}

char* gen_cstring(int len)
{
	char *t = new char[len+1];
	for (int i = 0; i < len; i++)
		t[i] = 'a' + rand() % 26;
	t[len] = '\0';
	return t;
}

int main()
{		
	srand((unsigned)time(NULL));  // set the seed of the random number generator
	
	int n = 2000;
	char **a = new char*[n];  
	string *s = new string[n];

	for (int i = 0; i < n; i++)	
	{
		int len = 5 + rand() % 15;
		a[i] = gen_cstring(len);
		s[i] = string(a[i]);
	}
	
	test_insertionSort(a, s, n);	

	randomize(a, s, n);	
	test_bubbleSort(a, s, n);
	
	randomize(a, s, n);
	test_qsort(a, s, n);

	system("pause");
	return 0;
}