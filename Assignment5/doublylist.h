#pragma once

template <class T>
struct Node //struct for a node in the doubly linked list
{
	T data;
	Node<T> *next;
	Node<T> *prev;
};

template <class T>
class DoublyList
{
	Node<T> head; //private member, the dummy head

public:
	DoublyList() //constructor
	{
		head.next = &head;
		head.prev = &head;
	}

	DoublyList(const DoublyList<T> & otherList) //copy constructor
	{
		Node<T> *curr = otherList.head->next, *t1 = &head, *t2;

		while (curr != &otherList.head) //loop through all items of the list
		{
			t2 = new Node<T>;
			t2->data = curr->data;
			t2->prev = t1;
			t1->next = t2;
			t1 = t2;
			curr = curr->next;
		}

		t1 -> next = &head;
	}

	~DoublyList() //destructor
	{
		Node<T> *t1, *t2;
		t1 = head.next;

		while (t1 != &head)
		{
			t2 = t1->next;
			delete t1;
			t1 = t2;
		}
	}

	Node<T> * InsertOrdered(T d) //function to insert a data item in list in ascending order
	{
		Node<T> *curr = head.next;
		Node<T> *temp = new Node<T>;
		temp->data = d;

		while (curr != &head && curr->data < d) //loop while right order not reached or end of list
			curr = curr->next;

		//update pointers for insertion
		temp->next = curr;
		temp->prev = curr->prev;
		curr->prev->next = temp;
		curr->prev = temp;

		return temp;
	}

	void DeleteNode(Node<T> *N) //this function deletes the node passed to it
	{
		N->prev->next = N->next;
		N->next->prev = N->prev;
		delete N;
	}

	void InsertAtStart(T d) //this function inserts a data item at start of list
	{
		Node<T> *temp = new Node<T>;
		temp->data = d;
		temp->next = head.next;
		temp->prev = &head;
		(head.next)->prev = temp;
		head.next = temp;
	}

	void InsertAtEnd(T d) //this function inserts a data item at end of list
	{
		Node<T> *temp = new Node<T>;
		temp->data = d;
		temp->next = &head;
		temp->prev = head.prev;
		(head.prev)->next = temp;
		head.prev = temp;
	}

	void RemoveFromStart() //this function removes a data item from start of list
	{
		if (head.next != &head)
		{
			(head.next) = (head.next)->next;
			delete (head.next)->prev;
			(head.next)->prev = &head;
		}
	}

	void RemoveFromEnd() //this function removes data item from end of list
	{
		if (head.next != &head)
		{
			Node<T> *tail = head.prev;
			tail->prev->next = &head;
			head.prev = tail->prev;
			delete[] tail;
		}
	}

	void OutputList() //this function outputs the whole linked list
	{
		Node<T> *curr = head.next;

		while (curr != &head)
		{
			cout << curr->data;
			cout<<endl;
			curr = curr->next;
		}
	}

};
