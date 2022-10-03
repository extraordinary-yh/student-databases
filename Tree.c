#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string.h>
#include "Tree.h"
using namespace std;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

static const char ALLOCATE[] = " - Allocating]\n";
static const char DEALLOCATE[] = " has been deallocated]\n";
static const char AND[] = " and ";
static const char COMPARE[] = " - Comparing ";
static const char INSERT[] = " - Inserting ";
static const char TREE[] = "[Tree ";

/**
 * The following struct contains functions associated with a tree node
 * such as constructor, destructor and write functions
 *
 * @author Mark Zeng(cs12fa19dm)
 */
struct TNode {
	Base * data;
	TNode * left, * right, *parent;
	static long occupancy;
        unsigned long hasBeenDeleted;

	// left child's height - right child's height
	long balance;

	// 1 + height of tallest child, or 0 for leaf
	long height;

TNode (Base * element) : data (element), left (0), right (0),
	parent (0), hasBeenDeleted (FALSE), balance (0), height(0) 
/***************************************************************************
% Routine Name : TNode (public)
% File :         Tree.c
% 
% Description : This function will allocates and initializes the memory 
%               associated with the TNode object.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% element           the data stored in the node
***************************************************************************/
{
	occupancy++;
}

~TNode (void) 
/*************************************************************************** 
% Routine Name : ~TNode  (public) 
% File :         Tree.c 
%  
% Description :  deallocates memory associated with the Tree Node.
***************************************************************************/  
{
	delete(data);
	occupancy--;
}
        
ostream & Write (ostream & stream) const {
                stream << "at height:  " << height << "  with balance:  "
			<< balance << "  ";
		return data->Write (stream) << "\n";
        }
	
ostream & Write_AllTNodes (ostream & stream) const {
		if (left)
			left->Write_AllTNodes (stream);
		if (!hasBeenDeleted)
			Write (stream);
		if (right)
			right->Write_AllTNodes (stream);

		return stream;
	}

void delete_AllTNodes (void) 
/*************************************************************************** 
% Routine Name : delete_AllTNodes  (public) 
% File :         Tree.c 
%  
% Description :  use post-order traversal to delete all the nodes
***************************************************************************/  
{
	if(left)
		left -> delete_AllTNodes();
	
	if(right)
		right -> delete_AllTNodes();
         
	delete(this);
}

};

// initialization of static data fields of Tree
long TNode :: occupancy = 0;
bool Tree :: debug_on = 0;

void Tree :: Set_Debug (bool option) {
/*************************************************************************** 
% Routine Name : Tree :: Set_Debug (public) 
% File :         Tree.c
%  
% Description :  This function sets debug mode on or off 
% 
% Parameters descriptions : 
%  
% name               description 
% ------------------ ------------------------------------------------------ 
% option             true should set debug mode on, false should set debug 
%                    mode off. 
***************************************************************************/  
	debug_on = option;
}

Tree :: Tree (const char * name) : root (0), tree_name (strdup (name))
/***************************************************************************
% Routine Name : Tree :: Tree  (public)
% File :         Tree.c
% 
% Description :  Initializes root pointer to NULL, and occupancy to 0.
***************************************************************************/

{
	TNode :: occupancy = 0;
	if(debug_on){
		cerr << TREE << tree_name << ALLOCATE ;
	}
}

Tree :: ~Tree (void)
/***************************************************************************
% Routine Name : Tree :: ~Tree  (public)
% File :         Tree.c
% 
% Description :  deallocates memory associated with the Tree.  It
%                will also delete all the memory of the elements within
%                the table.
***************************************************************************/

{
	if(debug_on){
		cerr << TREE << tree_name << DEALLOCATE;
	}
	/*delete node*/
	TNode :: occupancy = 0;
	if(root != NULL){
	root -> delete_AllTNodes();
	}
	/*delete tree*/
	free((void*)tree_name);
}	/* end: ~Tree */

unsigned long Tree :: IsEmpty () const 
/***************************************************************************
% Routine Name : Tree :: IsEmpty  (public)
% File :         Tree.c
% 
% Description :  checks if the Tree is Empty
% 
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% <return>           1 if empty, 0 if not
***************************************************************************/
{
	return (TNode :: occupancy)? 0 : 1;
}

void updateHeight (TNode * current)
/***************************************************************************
% Routine Name : Tree :: updateHeight  (private)
% File :         Tree.c
% 
% Description :  this function updates height of each node after insert
***************************************************************************/
{
	/*check if height realy needs to be updated*/
	if(current -> left != NULL && current -> right != NULL){
		return ;
	}
	/*update the height*/
	while(true){
		current -> height++;
		/*check root*/
		if(current -> parent == NULL)
			break;
		current = current -> parent;
	}
}

void updateBalance (TNode * current)
/***************************************************************************
% Routine Name : Tree :: updateBalance  (private)
% File :         Tree.c
% 
% Description :  this function updates balance of each node after insert
***************************************************************************/
{
	long leftHeight; /*the height of left node*/
	long rightHeight;/*the height of right node*/
		
	/*check balance*/
	while(true) {
		/*check left*/
		if(current->left == NULL){
			leftHeight = -1;
		}
		else{
			leftHeight = current -> left -> height;
		}
		/*check right*/
		if(current -> right == NULL){
			rightHeight = -1;
		}
		else{
			rightHeight = current -> right -> height;
		}
                current -> balance = leftHeight - rightHeight;
		/*check root*/
		if(current -> parent == NULL)
			break;
		current = current -> parent;
	}
}
unsigned long Tree :: Insert (Base * element) 
/***************************************************************************
% Routine Name : Tree :: Insert (public)
% File :         Tree.c
% 
% Description : Inserts the element into the binary tree. Returns true or 
%		false indicating success of insertion.
% 
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% element            element to be inserted
% <return>           1 if scucess, 0 if not
***************************************************************************/
{
	TNode * current;   /*used to keep track of the current node*/
	
	/*check if root exist*/
	if(root == NULL){
		if(debug_on){
			cerr << TREE << tree_name << INSERT << 
					(const char *)*element << "]" << endl;
		}
		root = new TNode(element);
               	return true;
	}
	current = root;
	while(true){	
		if(debug_on){
			cerr << TREE << tree_name << COMPARE <<  
					(const char *)*element << AND << 
				       	(const char *)*current -> data << "]" <<  
					endl;
		}
		/*check to go right or left*/
		if(*element > *current -> data){
			/*check if right exists*/
			if(current->right == NULL){
				current->right = new TNode(element);
				current->right->parent = current;
				updateHeight(current);
				updateBalance(current);
				if(debug_on){
				cerr << TREE << tree_name << INSERT << 
					(const char *)*element << "]" << endl;
				}
				return true;
			}
			/*go right*/
			else{
				current = current->right;
				continue;
			}
		}
		else{
			/*check if left exist*/
			if(current->left == NULL){
				current->left = new TNode(element);
				current->left->parent = current;
				updateHeight(current);
				updateBalance(current);
				if(debug_on){
				cerr << TREE << tree_name << INSERT << 
					(const char *)*element << "]" << endl;
				}
				return true;
			}
			/*go left*/
			else{
				current = current->left;
				continue;
			}
		}
	}
}

const Base * Tree :: Lookup (const Base * element) const 
/***************************************************************************
% Routine Name : Tree :: Lookup (public)
% File :         Tree.c
% 
% Description : Look up the element in the binary tree. Returns pointer to data
%		or NULL
% 
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% element            element to be looked up
% <return>           pointer to data if found, null if not
***************************************************************************/
{
	TNode * current;   /*used to keep track of the current node*/
	
	/*check if root exist*/
	if(root == NULL){
		return NULL;
	}
	current = root;
	
	/*checking down the tree*/
	while(true){	
		if(debug_on){
			cerr << TREE << tree_name << COMPARE <<  
					(const char *)*element << AND << 
				       	(const char *)*current -> data << "]" <<  
					endl;
		}
		/*go right?*/
		if(*element > *current->data){
			/*check if right exists*/
			if(current->right == NULL){
				return NULL;
			}
			/*go right*/
			else{
				current = current->right;
				continue;
			}
		}
		/*found*/
		else if(*element == *current->data){
			/*deleted?*/
			if(current->hasBeenDeleted == false){
				return current->data;
			}
			else{
				return NULL;
			}
		}
		else{
			/*check if left exists*/
			if(current->left == NULL){
				return NULL;
			}
			/*go left*/
			else{
				current = current->left;
				continue;
			}
		}
	}
}

Base * Tree :: Remove (const Base * element) 
/***************************************************************************
% Routine Name : Tree :: Remove (public)
% File :         Tree.c
% 
% Description : remove the matching data in the binary tree. Returns pointer to
%		data or NULL
% 
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% element            element to be removed
% <return>           pointer to data if found, null if not
***************************************************************************/
{
	TNode * current;   /*used to keep track of the current node*/
	
	/*check if root exist*/
	if(root == NULL){
		return NULL;
	}
	current = root;
	
	/*checking down the tree*/
	while(true){	
		if(debug_on){
			cerr << TREE << tree_name << COMPARE <<  
					(const char *)*element << AND << 
				       	(const char *)*current -> data << "]" <<  
					endl;
		}
		/*go right?*/
		if(*element > *current->data){
			/*check if right exists*/
			if(current->right == NULL){
				return NULL;
			}
			/*go right*/
			else{
				current = current->right;
				continue;
			}
		}
		/*found*/
		else if(*element == *current->data){
			/*deleted?*/
			if(current->hasBeenDeleted == false){
				current->hasBeenDeleted = true;
				TNode :: occupancy--;
				return current->data;
			}
			else{
				return NULL;
			}
		}
		else{
			/*check if left exists*/
			if(current->left == NULL){
				return NULL;
			}
			/*go left*/
			else{
				current = current->left;
				continue;
			}
		}
	}
}

ostream & Tree :: Write (ostream & stream) const
/***************************************************************************
% Routine Name : Tree :: Write (public)
% File :         Tree.c
% 
% Description : This function will output the contents of the Tree table
%               to the stream specificed by the caller.  The stream could be
%               cerr, cout, or any other valid stream.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% stream             A reference to the output stream.
% <return>           A reference to the output stream.
***************************************************************************/

{
        stream << "Tree " << tree_name << ":\n"
		<< "occupancy is " << TNode :: occupancy << " elements.\n";

	return (root) ? root->Write_AllTNodes (stream) : stream;
}       /* end: Write */

