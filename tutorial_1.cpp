// Student name: Wong Ka Ho
// Student ID  : 54816829

// Submission deadline: Thursday, 24 Jan 2019, 14:00
// Upload your program file (tutorial_1.cpp) to Canvas.
// Late submission or submission not revcieved via Canvas will not be graded.

/*
	Part-1:	Count the number of words in the input char array.
	A word is a continuous sequence of non-white space characters.
	White-space characters include 'space', tab '\t', newline '\n', and carriage return '\r'.

	You may use the C library function isspace() in your answer.

	Part-2: Print the words in the input array, one word per line.

	DO NOT modify the function interfaces given to you.

*/

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int wordCount(const char text[])
{
	// Return the number of words in the array text[].
	// Array text[] is terminated by '\0' (end of string symbol of C/C++).

	int count = 0;
	int i = 0;
		while (text[i] != '\0') {
			if(text[i]>'!'&&text[i]<'~' && text[i+1]==' '||text[i]>'!'&&text[i]<'~' && text[i + 1] == '\0'){
				count++;
			}
			i++;
	}
	return count;
}

int wordCount(const char text[], int lenThreshold)
{
	// Return the number of words (with length >= lenThreshold) in the array text[].

	int count = 0;
	int i = 0;
	int length = 0;
	while (text[i] != '\0') {
		if (text[i] > '!'&&text[i] < '~') {
			length += 1;
			i++;
			if (text[i + 1] == ' ' || text[i + 1] == '\0') {
				if (length >= lenThreshold) {
					count += 1;
				}
				length = 0;
			}
		}
		else
			i++;
	}
	return count;
}

void printWords(const char text[])
{	
	// Print the words in text[], one word per line.

	cout << "Words in the input array:" << endl;
	int i = 0;
	for(i=0;text[i]!='\0';i++) {
		if (text[i] == ' '||text[i]=='\0') {
			cout << endl;
			i++;
		}
		cout << text[i];
	}
	cout << endl;
	// Your codes

}


int main()
{		
	char text1[] = "  EE2331 Data  Structures \t and Algorithms Tutorial 1 ";
	char text2[] = "For a user's perspective, a keyboard consists of keys that can be pressed and released to type text.";

	cout << "Part-1: wordCount" << endl << endl;

	cout << "text1[] :\n" << text1 << endl << endl;
	int wc1 = wordCount(text1);
	cout << "Word count = " << wc1 << endl << endl;

	int lenThreshold = 5;
	int wc2 = wordCount(text1, lenThreshold);
	cout << "Word count (lenThreshold = " << lenThreshold << ") = " << wc2 << endl << endl;

	cout << "text2[] :\n" << text2 << endl << endl;
	wc1 = wordCount(text2);
	cout << "Word count = " << wc1 << endl << endl;

	wc2 = wordCount(text2, lenThreshold);
	cout << "Word count (lenThreshold = " << lenThreshold << ") = " << wc2 << endl << endl;
	
	cout << "--------------------------------------------\n";
	cout << "Part-2: printWords" << endl << endl;
	printWords(text2);	

	system("pause");
	return 0;
}