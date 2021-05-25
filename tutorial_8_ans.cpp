// Student name:
// Student ID  :

// Submission deadline: Thursday, 21 March 2019, 2 pm.

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

struct dnode  // template struct is not used in this exercise
{
	int info;
	dnode *back, *next;
};

void merge(dnode *A, dnode *B, dnode*& first, dnode*& last);

// -------------------------------------- Part-1: sort doubly-linked list with quicksort

dnode* partition(dnode *first, dnode *last)
{
	// Precondition: first and last are valid pointers, and fisrt != last

	dnode *i = first->next;
	dnode *j = last;
	bool crossover = false;  // represent if i has met j and crossover
	
	while (!crossover)
	{
		while (!crossover && i->info <= first->info)
		{
			if (i == j)
				crossover = true;
			i = i->next;
		}

		while (j->info > first->info)
		{
			if (j == i)
				crossover = true;
			j = j->back;
		}

		if (!crossover)
		{
			int temp = i->info;
			i->info = j->info;
			j->info = temp;
		}
	}

	int temp = first->info;
	first->info = j->info;
	j->info = temp;

	return j;
}

void qsort_list(dnode *first, dnode *last)
{
	// first points to the first node of the list segment to be sorted.
	// last points to the last node of the list segment to be sorted.

	// Implement this function using the quicksort algorithm.

	// Data object can be copied from one node to another node.
	// The structure (pointers) of the list is not modified.

	if (first == last)  // list segment has <= 1 node, no further processing required
		return;

	dnode *j = partition(first, last);

	if (j != first)
		qsort_list(first, j->back);

	if (j != last)
		qsort_list(j->next, last);
}

// -------------------------------------- Part-2: sort single-linked list with merge sort

void msort_list(dnode*& first)
{
	// The back pointer in the node is not used. The linked list is treated as single-linked list.

	// The function to merge 2 sorted sublists is given to you.
	// The nodes in the linked list are rearranged. 
	// No new node is created in the sorting process.
	// Data object will NOT be copied from one node to another node.

	/*
	int n = 0;
	for (dnode *p = first; p != nullptr; p = p->next)
		n++;
	*/

	int size = 1; // size of sorted sublist
	bool multiple_subfiles = (first != nullptr && first->next != nullptr); 	

	//while (size < n)
	while (multiple_subfiles) 
	{
		dnode *remain = first;
		dnode *last;
		first = last = nullptr;  // reset the resultant merged list to empty
		multiple_subfiles = false;

		while (remain != nullptr)
		{
			dnode *A, *B, *r;	// reference pointers for sublists A and B
			A = r = remain;
			for (int count = 1; count < size && r->next != nullptr; count++)
				r = r->next;
			
			// r points to the last node of sublist A

			if (r->next != nullptr)  // sublist B is not empty
			{
				B = r->next;
				r->next = nullptr;  // terminate sublist A

				r = B;
				for (int count = 1; count < size && r->next != nullptr; count++)
					r = r->next;
				// r points to the last node of sublist B

				remain = r->next;  // remain points to the remaining part of the list
				r->next = nullptr; // terminate sublist B

				/*
				dnode *mFirst, *mLast;
				merge(A, B, mFirst, mLast);
				if (first == nullptr)
				{
					first = mFirst;
					last = mLast;
				}
				else
				{
					last->next = mFirst;
					last = mLast;
				}
				*/
				if (first == nullptr)
					merge(A, B, first, last);  // assert: execution will always go through this path once,
				                                //         first and last are assigned valid values
				else
				{
					merge(A, B, last->next, last);
					multiple_subfiles = true;
				}
			}
			else // sublist B is empty
			{
				last->next = A;  // assert: last is a valid pointer
				remain = nullptr;
				multiple_subfiles = true;
			}
		}
		size *= 2;
	}
}

void msort(dnode*& first, int n)  // recursive function
{
	// n is the length of the input list

	if (n <= 1)  // empty list or list with 1 node	
		return;
	
	// n >= 2, divide the list into 2 non-empty sublists A and B

	int lenA = n / 2;
	int lenB = n - lenA;  // assert: lenA > 0 and lenB > 0

	dnode *A, *B, *r; 
	A = r = first;
	for (int count = 1; count < lenA; count++)
		r = r->next;
	// r points to last node of sublist A

	B = r->next;
	r->next = nullptr;  // terminate sublist A

	// sublistB is already terminated

	msort(A, lenA);    // sort sublists A and B using recursion
	msort(B, lenB);
	merge(A, B, first, r); // merge the sorted sublists A and B
}

void msort_list_r(dnode*& first)
{
	// Implement merge sort using recursion

	int n = 0;
	for (dnode *p = first; p != nullptr; p = p->next)
		n++;			

	msort(first, n);
}

// ------------------------------------ functions given to you

void merge(dnode *A, dnode *B, dnode*& first, dnode*& last)
{
	// Preconditions: Lists A and B are not empty.
	//                Lists A and B are sorted in ascending order.

	// Merge lists A and B. Nodes in A and B are put together in the merged list.
	// The merged list is sorted in ascending order.
	// Pointers first and last point to the first and last node of the merged list.

	dnode *p, *q;
	
	if (A->info <= B->info)
	{
		first = last = A;
		p = A->next;
		q = B;
	}
	else
	{
		first = last = B;
		p = A;
		q = B->next;
	}

	while (p != nullptr && q != nullptr)
	{
		dnode *r;
		if (p->info <= q->info)
		{
			r = p;
			p = p->next;
		}
		else
		{
			r = q;
			q = q->next;
		}
		
		// Append node r to the merged list
		last->next = r;		
		last = r;
	}

	if (p != nullptr)
		last->next = p;
	else if (q != nullptr)
		last->next = q;

	while (last->next != nullptr)
		last = last->next;
}

void printList(const char *label, const dnode *list)
{
	cout << label << endl;
	int count = 0;
	const dnode *p = list;
	while (p != nullptr)
	{
		if (count > 0 && count % 10 == 0)  // print up to 10 numbers per line
			cout << endl;

		cout << setw(3) << p->info << ", ";
		count++;
		p = p->next;
	}
	cout << endl << endl;
}

void createList(int n, int range, dnode*& first, dnode*& last)
{
	// n = length of the linked list to be created

	if (n <= 0)
	{
		first = last = nullptr;
		return;
	}

	first = last = new dnode;
	first->info = rand() % range;
	first->back = nullptr;

	for (int i = 1; i < n; i++)
	{
		last->next = new dnode;
		last->next->back = last;
		last = last->next;
		last->info = rand() % range;
	}
	last->next = nullptr;
}

void clearList(dnode *list)
{
	dnode *p;
	while (list != nullptr)
	{
		p = list->next;
		delete list;
		list = p;
	}	
}

void test_qsort(int n, int range)
{
	cout << "\n*** Test case with n = " << n << endl;

	dnode *first, *last;
	createList(n, range, first, last);
	printList("list : ", first);

	qsort_list(first, last);

	printList("list (sorted) : ", first);
	clearList(first);
}

void change_to_single_linked(dnode *list)
{
	dnode *p = list;
	while (p != nullptr)
	{
		p->back = nullptr;
		p = p->next;
	}
}

void test_msort(int n, int range)
{
	cout << "\n*** Test case with n = " << n << endl;

	dnode *first, *last;
	createList(n, range, first, last);
	change_to_single_linked(first);

	printList("list : ", first);
	msort_list(first);
	printList("list (sorted) : ", first);
	clearList(first);
}

int main()
{	
	cout << "Sort a doubly-linked list of integers with quicksort" << endl << endl;
	
	srand((unsigned)time(NULL));  
	test_qsort(10, 97);
	test_qsort(50, 193);

	cout << "\nSort a single-linked list of integers with merge sort" << endl << endl;
	test_msort(10, 97);
	test_msort(50, 193);

	system("pause");
	return 0;
}