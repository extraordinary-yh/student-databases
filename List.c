#include <iostream>
#include "Base.h"
#include "List.h"
using namespace std;

/* DO NOT CHANGE:  This file is used in evaluation */

struct Node {
	Base * data;
	struct Node * pre;
	struct Node * next;

	Node (Base * element) : data (element), pre (NULL), next (NULL) {}
	~Node (void);
	ostream & Write (ostream & stream) const {
		return data->Write (stream);
	}
};

List :: ~List (void) {
	Base * data;		/* working Base pointer */

	/* empty list */
	while (occupancy) {

		/* remove top element from list */
		data = Remove ();

		/* delete element */
		delete data;
	}
}

void List :: Advance_Next (void) {

	/* empty list */
	if (IsEmpty ()) {
		cerr << "Advance next from an empty list!!!\n";
		return;
	}

	current = current->next;
}

void List :: Advance_Pre (void) {

	/* empty list */
	if (IsEmpty ()) {
		cerr << "Advance pre from an empty list!!!\n";
		return;
	}

	current = current->pre;
}

long List :: Insert (Base * element) {
	Node * new_node;

	/* store element in a Node */
	new_node = new Node (element);

	/* is this the only element in the list??? */
	if (!occupancy)
		current = new_node->next = new_node->pre = new_node;
	
	else {
		new_node->next = current->next;
		new_node->pre = current;
		current->next->pre = new_node;
		current->next = new_node;
		current = current->next;
	}

	/* update occupancy */
	occupancy++;

	return 1;
}

Base * List :: Remove (void) {
	Node * old_node;		/* working node */
	Base * retval;

	/* check status of list */
	if (!occupancy) {
		cerr << "Removing from an empty list!!!\n";
		return NULL;
	}

	/* remember old_node and reassign the current pointer */
	old_node = current;
	current = current->pre;

	retval = old_node->data;

	/* remove old_node from list */
	old_node->pre->next = old_node->next;
	old_node->next->pre = old_node->pre;

	/* delete the empty node */
	delete old_node;

	/* update occupancy */
	occupancy--;

	/* check for empty list */
	if (occupancy == 0)
		current = NULL;

	return retval;
}

Base * List :: View (void) const {

	/* empty list */
	if (!occupancy) {
		cerr << "Viewing from an empty list!!!\n";
		return NULL;
	}

	return current->data;
}

ostream & List :: Write (ostream & stream) const {
	long count;		/* to know how many elements to print */
	Node * working;		/* working node */

	if (occupancy >= 1)
		working = current->next;

	for (count = 1; count <= occupancy; count++) {
		working->Write (stream);
		working = working->next;
	}
		
	return stream;
}

Node :: ~Node (void) {
	data = NULL;
	next = pre = NULL;
}
