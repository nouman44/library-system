#pragma once

template <class T>
struct Two3node //struct for node of a two 3 tree
{
	T k1;
	T k2;
	Two3node *left, *mid, *right;
	int n;
};

template <class T>
struct Two3ReturnValue //struct to return value from functions of two three tree
{
	T k;
	Two3node<T> *tNode;
};

template <class T>
class Two3Tree
{
	Two3node<T> *root; //private member

	Two3node<T> * Search(Two3node<T> * r, T d) //main search function for an item d
	{
		if (r != nullptr) //if node is not null then continue search
		{
			if (r->n == 1) //if it is a 2 node
			{
				if (d == r->k1)
					return r;
				else if (d < r->k1) //traverse left
					return Search(r->left, d);
				else
					return Search(r->mid, d); //traverse to mid
			}
			else //if it is a 3 node
			{
				if (d == r->k1 || d == r->k2)
					return r;
				else if (d < r->k1)
					return Search(r->left, d); //traverse left
				else if (d < r->k2)
					return Search(r->mid, d); //traverse mid
				else
					return Search(r->right, d); //traverse right
			}

			return r;
		}
		else //else return nullptr
			return nullptr;

	}

	//this a helper function for delete
	//it searches the parent of a given node
	Two3node<T> * SearchParent(Two3node<T> * r, Two3node<T> * d) 
	{
		Two3node<T> *parent = nullptr;

		if (d != nullptr)
		{

			if (d->n == 1) //if d is 2 node
			{
				if (d->left == r) //if found in left return
					return d;
				else if (d->mid == r) //if found in mid return
					return d;
				else //if not found continue search
				{
					if (parent == nullptr) 
						parent = SearchParent(r, d->left);

					if (parent == nullptr)
						parent = SearchParent(r, d->mid);
				}
			}
			else //if d is a 3 node
			{
				if (d->left == r) //if found in left return
					return d;
				else if (d->mid == r) //if found in mid return
					return d;
				else if (d->right == r) //if found in right return
					return d;
				else //if not found continue search
				{
					if (parent == nullptr)
						parent = SearchParent(r, d->left);

					if (parent == nullptr)
						parent = SearchParent(r, d->mid);

					if (parent == nullptr)
						parent = SearchParent(r, d->right);
				}
			}
		}
		else
			return parent;
		
	}

	//this is a helper function for the insert function
	//it splits the 3 node
	Two3ReturnValue<T> Split(Two3node<T> *curr, Two3node<T> *child,T k)
	{
		Two3node<T> *temp = new Two3node<T>; //create a new temp node
		temp->n = 1;
		temp->left = temp->right = temp->mid = nullptr;
		T mid;
		Two3ReturnValue<T> retVal; //return value for function

		if (k < curr->k1) //if value to be inserted is less than k1
		{
			mid = curr->k1;
			curr->k1 = k;
			temp->k1 = curr->k2;
			if (curr->left != nullptr)
			{
				temp->left = curr->mid;
				temp->mid = curr->right;
				curr->mid = child;
			}
		}
		else if (k < curr->k2) //if value to be inserted is less than k2
		{
			mid = k;
			temp->k1 = curr->k2;
			if (curr->left != nullptr)
			{
				temp->left = child;
				temp->mid = curr->left;
			}
		}
		else //if value to be inserted is greater than k2
		{
			mid = curr->k2;
			temp->k1 = k;
			if (curr->left != nullptr)
			{
				temp->left = curr->right;
				temp->mid = child;
			}
		}

		curr->right = nullptr;
		curr->n = 1;

		//return val updated
		retVal.k = mid;
		retVal.tNode = temp;

		return retVal;
	}

	Two3ReturnValue<T> Insert(Two3node<T> * &r, T d) //function for inserting a value in the tree
	{
		Two3ReturnValue<T> rVal;

		if (root == nullptr) //the tree is empty
		{
			root = new Two3node<T>;
			root->k1 = d;
			root->left = nullptr;
			root->mid = nullptr;
			root->right = nullptr;
			root->n = 1;
			rVal.k = d;
			rVal.tNode = nullptr;
			return rVal;
		}
		else if (r->left == nullptr) //r is a leaf node
		{
			if (r->n == 1) //r is a 2 node
			{
				if (d < r->k1) //if d is less than r->k1
				{
					r->k2 = r->k1;
					r->k1 = d;
				}
				else //if d is greater than r->k1
					r->k2 = d;

				r->n++;
				rVal.k = d;
				rVal.tNode = nullptr;
				return rVal;
			}
			else //r is a 3 node
			{
				return Split(r, nullptr, d); //call split function for 3 node
			}
		}
		else //r is a non-leaf node
		{
			if (r->n == 1) //r is a 2 node
			{
				if (d < r->k1) //if d is less than r->k1
				{
					rVal = Insert(r->left, d);
					if (rVal.tNode != nullptr)
					{
						r->k2 = r->k1;
						r->k1 = rVal.k;
						r->right = r->mid;
						r->mid = rVal.tNode;
						r->n++;
					}
				}
				else //if d is greater than r->k1
				{
					rVal = Insert(r->mid, d);
					if (rVal.tNode != nullptr)
					{
						r->k2 = rVal.k;
						r->right = rVal.tNode;
						r->n++;
					}
				}

				rVal.k = d;
				rVal.tNode = nullptr;
				return rVal;
			}
			else //r is a 3 node
			{
				if (d < r->k1)
					rVal = Insert(r->left, d); //insert in r->left
				else if (d < r->k2)
					rVal = Insert(r->mid, d); //insert in r->mid
				else
					rVal = Insert(r->right, d); //insert in r->right

				if (rVal.tNode != nullptr)
					return Split(r, rVal.tNode, rVal.k); //call split function
				else
				{
					rVal.k = d;
					rVal.tNode = nullptr;
					return rVal;
				}
			}
		}
	}

	//this is a helper function for delete
	Two3node<T> * SwapWithSuccessor(Two3node<T> * &r,T d)
	{
		Two3node<T> * curr;
		T temp;

		if (r->k1 == d) //if 2 node then traverse mid
			curr = r->mid;
		else //else traverse right
			curr = r->right;

		while (curr->left != nullptr) //keep traversing left to min val
		{
			curr = curr->left; 
		}

		if (r->k1 == d) //if r is a 2 node
		{
			temp = r->k1; //swap with k1 of curr
			r->k1 = curr->k1;
			curr->k1 = temp;
		}
		else //if r is a 3 node
		{
			temp = r->k2; //swap with k1 of curr
			r->k2 = curr->k1;
			curr->k1 = temp;
		}

		return curr;
	}

	//this is a helper function for delete
	//it checks whehter a sibling is a 3 node or not
	bool SiblingCheck(Two3node<T> * parent, Two3node<T> * child)
	{
		if (parent->n == 1) //if parent is a 2 node
		{
			if (child == parent->left) //if child is the left node
			{
				if ((parent->mid)->n == 2)
					return true;
				else
					return false;
			}
			else //if child is the mid node
			{
				if ((parent->left)->n == 2)
					return true;
				else
					return false;
			}
		}
		else //if parent is a 3 node
		{
			if (child == parent->left) //if child is the left node
			{
				if ((parent->mid)->n == 2)
					return true;
				else
					return false;
			}
			else if(child == parent->mid) //if child is the mid node
			{
				if ((parent->left)->n == 2 || (parent->right)->n == 2)
					return true;
				else
					return false;
			}
			else //if parent is the right node
			{
				if ((parent->mid)->n == 2)
					return true;
				else
					return false;
			}
		}
	}

	//this is helper function for delete
	//it redistributes the tree after deletion
	Two3node<T> * RedistributeTree(Two3node<T> * &r, T d)
	{
		if (r == root) //if r is the root 
		{
			if (root->left != nullptr) //if r has a left node
				root = root->left;
			else if (root->mid != nullptr) //if r has a mid node
				root = root->mid;
			else //else r is a leaf node
			{
				delete r;
				root = nullptr;
			}
			return r;
		}
		else //r is not the root of the tree
		{
			Two3node<T> *parent = SearchParent(r, root); //search the parent of node r

			if (SiblingCheck(parent, r)) //if a sibling of r is a 3 node
			{
				if (parent->n == 1) //if parent is a 2 node
				{
					if (r == parent->left) //if r is left node of parent
					{
						r->k1 = parent->k1;
						parent->k1 = (parent->mid)->k1;
						(parent->mid)->k1 = (parent->mid)->k2;
						if (r->left != nullptr || r->mid!=nullptr) //if r is not a leaf node
						{
							if (r->mid != nullptr)
								r->left = r->mid;
							r->mid = (parent->mid)->left;
							(parent->mid)->left = (parent->mid)->mid;
							(parent->mid)->mid = (parent->mid)->right;
							(parent->mid)->right = nullptr;
						}
						(parent->mid)->n--;
					}
					else //if r is the mid node of parent
					{
						r->k1 = parent->k1;
						parent->k1 = (parent->left)->k2;
						if (r->left != nullptr || r->mid != nullptr) //if r is not a leaf node
						{
							if (r->left != nullptr)
								r->mid = r->left;
							r->left = (parent->left)->right;
							(parent->left)->right = nullptr;
						}
						(parent->left)->n--;
					}
				}
				else //if parent is a 3 node
				{
					if (r == parent->left) //if r is the left node of parent
					{
						r->k1 = parent->k1;
						parent->k1 = (parent->mid)->k1;
						(parent->mid)->k1 = (parent->mid)->k2;
						if (r->left != nullptr || r->mid != nullptr) //if r is not a leaf node
						{
							if (r->mid != nullptr)
								r->left = r->mid;
							r->mid = (parent->mid)->left;
							(parent->mid)->left = (parent->mid)->mid;
							(parent->mid)->mid = (parent->mid)->right;
							(parent->mid)->right = nullptr;
						}
						(parent->mid)->n--;
					}
					else if(r == parent->mid) //if r is the left mid of parent
					{
						if ((parent->left)->n == 2)
						{
							r->k1 = parent->k1;
							parent->k1 = (parent->left)->k2;
							if (r->left != nullptr || r->mid != nullptr) //if r is not a leaf node
							{
								if (r->left != nullptr)
									r->mid = r->left;
								r->left = (parent->left)->right;
								(parent->left)->right = nullptr;
							}
							(parent->left)->n--;
						}
						else
						{
							r->k1 = parent->k2;
							parent->k2 = (parent->right)->k1;
							(parent->right)->k1 = (parent->right)->k2;
							if (r->left != nullptr || r->mid != nullptr) //if r is not a leaf node
							{
								if (r->mid != nullptr)
									r->left = r->mid;
								r->mid = (parent->right)->left;
								(parent->right)->left = (parent->right)->mid;
								(parent->right)->mid = (parent->right)->right;
								(parent->right)->right = nullptr;
							}
							(parent->right)->n--;
						}
					}
					else //if r is the right node of parent
					{
						r->k1 = parent->k2;
						parent->k2 = (parent->mid)->k2;
						if (r->left != nullptr || r->mid != nullptr) //if r is not a leaf node
						{
							if (r->left != nullptr)
								r->mid = r->left;
							r->left = (parent->mid)->right;
							(parent->mid)->right = nullptr;
						}
						parent->mid->n--;
					}
				}
			}
			else //if all siblings of r are 2 nodes
			{
				if (parent->n == 1) //if parent is a 2 node
				{
					if (r == parent->left) //if r is the left node of parent
					{
						(parent->mid)->k2 = (parent->mid)->k1;
						(parent->mid)->k1 = parent->k1;
						(parent->mid)->n++;
						if (r->left != nullptr) //if r->left is not null
						{
							(parent->mid)->right = (parent->mid)->mid;
							(parent->mid)->mid = (parent->mid)->left;
							(parent->mid)->left = r->left;
						}
						else if (r->mid != nullptr)//if r->mid is not null
						{
							(parent->mid)->right = (parent->mid)->mid;
							(parent->mid)->mid = (parent->mid)->left;
							(parent->mid)->left = r->mid;
						}
						else
							delete r;
						parent->left = nullptr;
						RedistributeTree(parent, parent->k1); //recursive call to redistribute tree
					}
					else //if r is the mid node of parent
					{
						(parent->left)->k2 = parent->k1; 
						(parent->left)->n++;
						if (r->left != nullptr) //if r->left is not null
							(parent->left)->right = r->left;
						else if (r->mid != nullptr) //if r->mid is not null
							(parent->left)->right = r->mid;
						else
							delete r;
						parent->mid = nullptr;
						RedistributeTree(parent, parent->k1); //recursive call to redistribute tree
					}
				}
				else //if parent is a 3 node
				{
					if (r == parent->left) //if r is the left node of parent
					{
						(parent->mid)->k2 = (parent->mid)->k1;
						(parent->mid)->k1 = parent->k1;
						(parent->mid)->n++;
						parent->k1 = parent->k2;
						parent->n--;
						if (r->left != nullptr) //if r->left is not null
						{
							(parent->mid)->right = (parent->mid)->mid;
							(parent->mid)->mid = (parent->mid)->left;
							(parent->mid)->left = r->left;
						}
						else if (r->mid != nullptr) //if r->mid is not null
						{
							(parent->mid)->right = (parent->mid)->mid;
							(parent->mid)->mid = (parent->mid)->left;
							(parent->mid)->left = r->mid;
						}
						else
							delete r;
						parent->left = parent->mid;
						parent->mid = parent->right;
						parent->right = nullptr;
					}
					else if (r == parent->mid) //if r is the mid node of parent
					{
						(parent->left)->k2 = parent->k1;
						(parent->left)->n++;
						parent->k1 = parent->k2;
						parent->n--;
						if (r->left != nullptr) //if r->left is not null
							(parent->left)->right = r->left;
						else if (r->mid != nullptr) //if r->mid is not null
							(parent->left)->right = r->mid;
						else
							delete r;
						parent->mid = parent->right;
						parent->right = nullptr;
					}
					else //if r is the right node of parent
					{
						(parent->mid)->k2 = parent->k2;
						(parent->mid)->n++;
						parent->n--;
						if (r->left != nullptr) //if r->left is not null
							(parent->mid)->right = r->left;
						else if (r->mid != nullptr) //if r->mid is not null
							(parent->mid)->right = r->mid;
						else
							delete r;
						parent->right = nullptr;
					}
				}
			}
		}

		return r;
	}

	//this function deletes a item d from the tree
	Two3node<T> * Delete(Two3node<T> * &r,T d)
	{
		if (r->left != nullptr) //if r is not a leaf node then swap
			r = SwapWithSuccessor(r, d);

		if (r->n == 1) //if r is a 2 node then redistribute the whole tree
		{
			r = RedistributeTree(r, d);
		}
		else //if r is a 3 node
		{
			if (r->k1 == d)
			{
				r->k1 = r->k2;
				r->n--;
			}
			else
				r->n--;
		}
		
		return r;
	}
	
	void Destruct(Two3node<T> * r) //function to destroy the tree. Root is passed as parameter
	{
		if (r != nullptr)
		{
			if (r->n = 1) //if it is a 2 node
			{
				Destruct(r->left); //traverse left
				Destruct(r->mid); //traverse mid
				delete r;
			}
			else //it is a 3 node
			{
				Destruct(r->left); //traverse left
				Destruct(r->mid); //traverse mid
				Destruct(r->right); //traverse right
				delete r;
			}
		}
	}

public:

	Two3Tree() //constructor
	{
		root = nullptr;
	}

	~Two3Tree() //destructor
	{
		Destruct(root);
		root = nullptr;
	}

	Two3node<T> * Search(T d) //Wrapper function for Search
	{
		Two3node<T> * rNode = Search(root, d); //function call for search. Start from root

		return rNode;
	}

	void Insert(T d) //Wrapper function for insert
	{
		Two3ReturnValue<T> rVal;
		rVal = Insert(root, d); //function call for inserting d

		if (rVal.tNode != nullptr) //if return value doesnot have a null ptr
		{
			Two3node<T> *temp = new Two3node<T>;
			temp->k1 = rVal.k;
			temp->n = 1;
			temp->left = root;
			temp->mid = rVal.tNode;
			temp->right = nullptr;
			root = temp;
		}
	}

	void Delete(T d) //wrapper function for delete
	{
		Two3node<T> * rNode = Search(d);

		if (rNode != nullptr) //if item to delete is present then delete
			Delete(rNode,d);
	} 

};