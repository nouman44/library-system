#include <iostream>
#include "doublylist.h"
#include "two3tree.h"

using namespace std;

//this class contains all the data for a book record
//used in the doubly list 
class BookData
{
	//data members
	int ISSN;
	char *Title;
	int noAuthors;
	char **Authors;
	int refCopies;
	int issueCopies;

public:
	BookData() //constructor
	{
		Title = nullptr;
		Authors = nullptr;
	}

	//parametrized constructor
	BookData(int newISSN,char *newTitle,int newNoAuthors, char **newAuthors,int newrefCopies,int newissueCopies) 
	{
		ISSN = newISSN;
		Title = newTitle;
		noAuthors = newNoAuthors;
		Authors = newAuthors;
		refCopies = newrefCopies;
		issueCopies = newissueCopies;
	}

	BookData(const BookData & source) //copy constructor
	{
		ISSN = source.ISSN;
		noAuthors = source.noAuthors;
		refCopies = source.refCopies;
		issueCopies = source.issueCopies;

		int i, size;

		size = strlen(source.Title); //size of title
		Title = new char[size + 1];

		for (i = 0;source.Title[i] != NULL;i++) ///deep copy
			Title[i] = source.Title[i];

		Title[size] = 0;

		Authors = new char*[noAuthors];

		for (i = 0;i < noAuthors;i++) //deep copy
		{
			size = strlen(source.Authors[i]); //size of author
			Authors[i] = new char[size + 1];

			for (int j = 0;source.Authors[i][j] != NULL;j++)
				Authors[i][j] = source.Authors[i][j];

			Authors[i][size] = 0;
		}
	}

	//this is helper function to uopdate the existing data of a book record
	void UpdateBookData(char *newTitle, int newNoAuthors, char **newAuthors, int newrefCopies, int newissueCopies)
	{
		if (Title != nullptr) //delete title
			delete[] Title;

		if (Authors != nullptr) //delete authors
		{
			for (int i = 0;i < noAuthors;i++)
				delete[] Authors[i];

			delete[] Authors;
		}

		//update details
		Title = newTitle;
		noAuthors = newNoAuthors;
		Authors = newAuthors;
		refCopies = newrefCopies;
		issueCopies = newissueCopies;
	}
	
	~BookData() //destructor
	{
		if (Title != nullptr)
			delete[] Title;

		if (Authors != nullptr)
		{
			for (int i = 0;i < noAuthors;i++)
				delete[] Authors[i];

			delete[] Authors;
		}
	}

	const BookData & operator=(const BookData & source) //operator overload for = operator
	{
		if (this != &source) //if not the object itself
		{
			if (Title != nullptr) //delete title
				delete[] Title;

			if (Authors != nullptr) //delete authors
			{
				for (int i = 0;i < noAuthors;i++)
					delete[] Authors[i];

				delete[] Authors;
			}

			//make details equal
			ISSN = source.ISSN;
			noAuthors = source.noAuthors;
			refCopies = source.refCopies;
			issueCopies = source.issueCopies;

			int i, size;

			size = strlen(source.Title);
			Title = new char[size + 1];

			for (i = 0;source.Title[i] != NULL;i++) //copy title
				Title[i] = source.Title[i];

			Title[size] = 0;

			Authors = new char*[noAuthors];

			for (i = 0;i < noAuthors;i++) //copy authors
			{
				size = strlen(source.Authors[i]);
				Authors[i] = new char[size + 1];

				for (int j = 0;source.Authors[i][j] != NULL;j++)
					Authors[i][j] = source.Authors[i][j];

				Authors[i][size] = 0;
			}
		}

		return *this; //return object
	}

	bool operator>(const BookData & operand) const //greater than operator overload
	{
		if (ISSN > operand.ISSN)
			return true;
		else
			return false;
	}

	bool operator<(const BookData & operand) const //less than operator overload
	{
		if (ISSN < operand.ISSN)
			return true;
		else
			return false;
	}

	//ostream operator overload
	//this function helps to ouput a book record
	friend ostream & operator<<(ostream &strm, const BookData & B)
	{
		cout << "ISSN: " << B.ISSN << endl;
		cout << "Title: " << B.Title << endl;

		for (int i = 0;i < B.noAuthors;i++) //output multiple authors
		{
			cout << "Author " << i + 1 << ": ";
			cout << B.Authors[i] << endl;
		}

		cout << "Reference copies available: " << B.refCopies << endl;
		cout << "Issuable copies available: " << B.issueCopies << endl;
		
		return strm;
	}
};

//this class contains the ISSN and doubly node ptr
//used as type for the 2 3 tree
class BookKey
{
	int ISSN;
	Node<BookData> *bookPtr;

public:
	BookKey() //constructor
	{

	}

	BookKey(int newISSN, Node<BookData> *newBookPtr) //parameterized constructor
	{
		ISSN = newISSN;
		bookPtr = newBookPtr;
	}

	BookKey(const BookKey & source) //copy constructor
	{
		ISSN = source.ISSN;
		bookPtr = source.bookPtr;
	}

	~BookKey() //destructor
	{
		bookPtr = nullptr;
	}

	//operator overload for = operator
	const BookKey & operator=(const BookKey & source)
	{
		if (this != &source) //if object not itself
		{
			ISSN = source.ISSN;
			bookPtr = source.bookPtr;
		}

		return *this;
	}

	bool operator==(const BookKey & operand) const //operator overload for == operator
	{
		if (ISSN == operand.ISSN)
			return true;
		else
			return false;
	}


	bool operator>(const BookKey & operand) const //operator overload for greater than operator
	{
		if (ISSN > operand.ISSN)
			return true;
		else
			return false;
	}

	bool operator<(const BookKey & operand) const //operator overload for less than operator
	{
		if (ISSN < operand.ISSN)
			return true;
		else
			return false;
	}

	void OutputData() //this functions outputs the data members of this class
	{
		cout << bookPtr->data;
	}

	//this function updates the details of a book record using the doubly ptr
	void UpdateData(char *newTitle, int newNoAuthors, char **newAuthors, int newrefCopies, int newissueCopies)
	{
		bookPtr->data.UpdateBookData(newTitle, newNoAuthors, newAuthors, newrefCopies, newissueCopies);
	}

	//this function returns the book ptr itself
	Node<BookData> * retBookPtr()
	{
		return bookPtr;
	}
};

//this is the main class for the book records
//it acts as the interface through which all the records are handled
class BookDatabase
{
	Two3Tree<BookKey> searchTree; //2 3 tree for storing the keys
	DoublyList<BookData> bookDataList; //doubly list for storing the book records

public:
	BookDatabase() //constructor
	{

	}

	~BookDatabase() //destructor
	{

	}

	//this function creates a new book record in the database
	void CreateBookRecord()
	{
		int ISSN, noAuthors, refCopies, issueCopies, n, i, size; //declare variables
		char *Title, **Authors;
		char *temp = new char[50];


		cout << "Please enter details for new record" << endl;
		cout << "Enter ISSN: ";
		cin >> ISSN; //input ISSN

		BookKey oldKey(ISSN, nullptr); //declare a key object
		Two3node<BookKey> *refKey = searchTree.Search(oldKey); //search ISSN to find in tree

		if (refKey == nullptr) //if ISSN does not already exist
		{
			cout << "Enter Title: ";
			cin.ignore();
			cin.getline(temp, 50); //input Title

			size = strlen(temp);
			Title = new char[size + 1];

			for (i = 0;temp[i] != NULL;i++) //store title
				Title[i] = temp[i];

			Title[size] = 0;

			cout << "How many authors does the book have: ";
			cin >> n; //input no of authors
			noAuthors = n;
			Authors = new char*[n];

			cin.ignore();

			for (i = 0;i < n;i++) //input multiple authors
			{
				cout << "Enter name of Author " << i + 1 << ": ";
				cin.getline(temp, 50);
				size = strlen(temp);
				Authors[i] = new char[size + 1];

				for (int j = 0;temp[j] != NULL;j++)
					Authors[i][j] = temp[j];

				Authors[i][size] = 0;
			}

			cout << "Enter number of copies available as reference book: ";
			cin >> refCopies; //input no of ref copies
			cout << "Enter number of copies available as issuable book: ";
			cin >> issueCopies; //input no of issue copies

			BookData newBook(ISSN, Title, noAuthors, Authors, refCopies, issueCopies); //store details in a book record object

			Node<BookData> *bookPtr = bookDataList.InsertOrdered(newBook); //insert book record in doubly list

			BookKey newKey(ISSN, bookPtr); //store details of key in a key object

			searchTree.Insert(newKey); //insert key in the 2 3 tree
		}
		else //if ISSN already exists
			cout << "Record with the same ISSN already exists!" << endl;

		delete[] temp;
	}

	//this function find a record from the doubly list and displays it
	void ReviewBookRecord()
	{
		int ISSN;
		cout << "Please enter ISSN to review book record: ";
		cin >> ISSN; //input ISSN
		
		BookKey oldKey(ISSN, nullptr); //declare a key object
		Two3node<BookKey> *refKey = searchTree.Search(oldKey); //search ISSN to find in tree

		if (refKey != nullptr) //if ISSN is found
		{
			//ouput data 
			if (oldKey == refKey->k1)
				refKey->k1.OutputData();
			else
				refKey->k2.OutputData();
		}
		else //ISSN was not found
			cout << "Record not found! Enter valid ISSN." << endl;

	}

	//this function updates the current book record with new details entered
	void UpdateBookRecord()
	{
		int ISSN;

		cout << "Please enter ISSN to update book record: ";
		cin >> ISSN; //input ISSN

		BookKey oldKey(ISSN, nullptr); //declare a key object
		Two3node<BookKey> *refKey = searchTree.Search(oldKey); //search ISSN to find in tree

		if (refKey != nullptr) //if ISSN is found
		{
			int noAuthors, refCopies, issueCopies, n, i, size;
			char *Title, **Authors;
			char *temp = new char[50];

			cout << "Please enter new details for record" << endl;

			cout << "Enter new Title: ";
			cin.ignore();
			cin.getline(temp, 50); //input Title

			size = strlen(temp);
			Title = new char[size + 1];

			for (i = 0;temp[i] != NULL;i++) //store Title
				Title[i] = temp[i];

			Title[size] = 0;

			cout << "How many authors does the book have: ";
			cin >> n;
			noAuthors = n;
			Authors = new char*[n];

			cin.ignore();

			for (i = 0;i < n;i++) //loop to store multiple authors 
			{
				cout << "Enter name of Author " << i + 1 << ": ";
				cin.getline(temp, 50);
				size = strlen(temp);
				Authors[i] = new char[size + 1];

				for (int j = 0;temp[j] != NULL;j++)
					Authors[i][j] = temp[j];

				Authors[i][size] = 0;
			}

			cout << "Enter number of copies available as reference book: ";
			cin >> refCopies; //input no of ref copies
			cout << "Enter number of copies available as issuable book: ";
			cin >> issueCopies; //input no of issue copies

			if (oldKey == refKey->k1) //if record to update is in k1
				refKey->k1.UpdateData(Title, noAuthors, Authors, refCopies, issueCopies);
			else //if record to update is in k2
				refKey->k2.UpdateData(Title, noAuthors, Authors, refCopies, issueCopies);

			delete[] temp;
		}
		else //if ISSN not found output error message
			cout << "Record not found! Enter valid ISSN." << endl;
	}

	//this function is to delete a book record from the doubly list and 2 3 tree
	void DeleteBookRecord()
	{
		int ISSN;

		cout << "Please enter ISSN to delete book record :";
		cin >> ISSN; //input ISSN
		
		BookKey oldKey(ISSN, nullptr); //declare a key object
		Two3node<BookKey> *refKey = searchTree.Search(oldKey); //search ISSN to find in tree

		if (refKey != nullptr) //if ISSN is found
		{
			Node<BookData> *curr;

			if (oldKey == refKey->k1) //if in k1 then return ptr
				curr = refKey->k1.retBookPtr();
			else //if in k2 then return ptr
				curr = refKey->k2.retBookPtr();

			bookDataList.DeleteNode(curr); //delete item from 2 3 tree

			searchTree.Delete(oldKey); //delete item from doubly list
			
			cout << "Record deleted successfully!" << endl;
		}
		else //if ISSN not found
			cout << "Record to delete not found! Enter valid ISSN." << endl;

	}

	//this function ouputs all the records in the database
	void ViewAllRecords()
	{
		bookDataList.OutputList();
	}

	//this function is used to view records in a given range of ISSN
	void ViewRangeISSN()
	{
		int r1, r2;

		cout << "Enter starting value for ISSN range: ";
		cin >> r1; //input starting range
		cout << "Enter ending value for ISSN range: ";
		cin >> r2; //input ending range
		cout << endl;

		BookKey oldKey1(r1, nullptr), oldKey2(r2, nullptr); //declare two key objects

		//search both keys in the tree
		Two3node<BookKey> *refKey1 = searchTree.Search(oldKey1), *refKey2 = searchTree.Search(oldKey2);

		//if both keys are found
		if (refKey1 != nullptr && refKey2 != nullptr)
		{

			Node<BookData> *curr, *end; //declare node ptrs

			if (oldKey1 == refKey1->k1) //if key exists in k1
				curr = refKey1->k1.retBookPtr();
			else
				curr = refKey1->k2.retBookPtr(); //if key exists in k2

			if (oldKey2 == refKey2->k1) //if key exists in k1
				end = refKey2->k1.retBookPtr();
			else
				end = refKey2->k2.retBookPtr(); //if key exists in k2

			while (curr != (end->next)) //go through list to print records
			{
				cout << curr->data;
				cout << endl;
				curr = curr->next;
			}

		}
		else //if keys not found
			cout << "ISSN values for range not found! Enter valid ISSN.";
	}
};

int main()
{
	BookDatabase B; //declare book database class object

	int choice = 1;

	//show user the options
	cout << "BOOK DATABASE PROGRAM: " << endl;
	cout << "1: Create a book record" << endl;
	cout << "2: Review a book record" << endl;
	cout << "3: Update a book record" << endl;
	cout << "4: Delete a book record" << endl;
	cout << "5: View all book records" << endl;
	cout << "6: View books in a ISSN range" << endl;
	cout << "0: Exit the program" << endl << endl;
	cout << "Input choice number: ";
	cin >> choice;
	cout << endl;

	//while user does not exit
	while (choice != 0)
	{
		switch (choice)
		{
		case 0:
			break;
		case 1:
			B.CreateBookRecord(); //create a new book record
			break;
		case 2:
			B.ReviewBookRecord(); //review an existing book record
			break;
		case 3:
			B.UpdateBookRecord(); //update an existing book record
			break;
		case 4:
			B.DeleteBookRecord();  //delete an existing book record
			break;
		case 5:
			B.ViewAllRecords(); //view all book records
			break;
		case 6:
			B.ViewRangeISSN(); //view book records in an ISSN range
			break;
		}

		//input choice from user
		cout << endl << "Input choice number: ";
		cin >> choice;
		cout << endl;
	}

	return 0;
}