#ifndef CS20A_LIST_H
#define CS20A_LIST_H

#include<iostream>
#include<assert.h>
// Linked List object that maintains both m_head and m_tail pointers
// and the m_size of the list.  Note that you have to keep the m_head,
// m_tail and m_size consistent with the intended state of the List 
// otherwise very bad things happen. 
template<typename Item>
class List {
public:

	List();

	List(const List<Item>& other);

	List<Item>& operator=(const List<Item>& other);

	~List();

	void	print() const;
	bool	empty() const;

	void	push_front(const Item& item);
	void	push_rear(const Item& item);
	void	insert(int index, const Item& item);

	// Note that the user must first ensure the list is not empty
	// prior to calling these functions.
	Item	front() const;
	Item	rear() const;
	Item	get(int index) const;

	int		size() const;
	int		find(const Item& item) const;

	bool	pop_front();
	bool	pop_rear();
	bool	remove(int index);

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif
	// Forward declare the nodes for our List.
	// Will be implemented along with list's
	// member functions
	class Node;

	// We'll have both m_head and m_tail points for 
	// Fast insertion/deletion from both ends.
	Node* m_head;
	Node* m_tail;

	// Keep track of number of nodes in the list
	int		m_size;
};


/* List Implementation
//
//  Since List is a template class (which is not an actual
//  class yet, not until we actually instantiate the list)
//  we need to keep the implementation together with
//  the definition.  There are ways to simulate having
//  separate "implementation/definition" with templates,
//  but they aren't necessary and can be confusing.
*/

/* Node definition
//		Already implemented, nothing to do here but to use it.
*/
template<typename Item>
struct List<Item>::Node {
	Node() :next(nullptr), prev(nullptr) {}
	Node(Item it, Node* p, Node* n) : item(it), next(n), prev(p) {}

	Item  item;
	Node* next;
	Node* prev;
};



/* List default constructor
//		Set m_head and m_tail pointer to point to nothing, m_size is zero
//		Already implemented, nothing to do.
*/
template<typename Item>
List<Item>::List() :m_head(nullptr), m_tail(nullptr), m_size(0) {
}


/* Copy constructor
*/
template<typename Item>
List<Item>::List(const List<Item>& other) {
	Node* ptr = other.m_head;
	for (int i = 0; i < other.m_size; i++) {
		push_rear(ptr->item);
		ptr = ptr->next;
	}
	

}
/* Overloaded assignment operator
*/
template<typename Item>
List<Item>& List<Item>::operator=(const List<Item>& other) {
	if (this == &other)
		return(*this);
	Node* killme = m_head;
	while (m_head != nullptr) {
		m_head = killme->next;
		delete killme;
		killme = m_head;
		m_size--;
	}
	Node* ptr = other.m_head;
	for (int i = 0; i < other.m_size; i++) {
		push_rear(ptr->item);
		ptr = ptr->next;
	}
	return *this;
}


/* List destructor
*/
template<typename Item>
List<Item>::~List() {
	Node* killme=m_head;
	while (m_head != nullptr) {
		m_head = killme->next;
		delete killme;
		killme = m_head;
	}
}

/* List print
*/
template<typename Item>
void List<Item>::print() const {
	Node* ptr = m_head;
	while (ptr != nullptr) {
		std::cout << ptr->item;
		if (ptr != m_tail)
			std::cout << " ";
		else
			std::cout << std::endl;
		ptr = ptr->next;
	}
}

/* List empty
*/
template<typename Item>
bool List<Item>::empty() const {
	if (m_size == 0)
		return true;
	return false;
}


/* List push_front
*/
template<typename Item>
void List<Item>::push_front(const Item& item) {
	Node* ptr = new Node;
	ptr->item = item;
	ptr->next = m_head;
	ptr->prev = nullptr;
	if (m_size!=0)
		m_head->prev = ptr;
	m_head = ptr;
	if (m_tail == nullptr)
		m_tail = m_head;
	m_size++;
}

/* List push_rear
*/
template<typename Item>
void List<Item>::push_rear(const Item& item) {
	Node* ptr = new Node;
	ptr->item = item;
	ptr->next = nullptr;
	ptr->prev = m_tail;
	if (m_size != 0)
		m_tail->next = ptr;
	m_tail = ptr;
	if (m_head == nullptr)
		m_head = m_tail;
	m_size++;
}

/* List insert
*/
template<typename Item>
void List<Item>::insert(int index, const Item& item) {
	if (index <= 0) {
		push_front(item);
	}else if (index >= m_size) {
		push_rear(item);
	}else {
		Node* ptr = m_head;
		Node* inserted = new Node;
		for (int i = 0; i < m_size; i++) {
			if (i == index) {
				break;
			}
			ptr = ptr->next;
		}
		inserted->prev = ptr->prev;
		inserted->next = ptr;
		inserted->item = item;
		ptr->prev->next = inserted;
		ptr->prev = inserted;
		m_size++;
	}
}

/*  List front
*/
template<typename Item>
Item List<Item>::front() const {
	// Force check that the m_head is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, but since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(m_head != nullptr);
	Item firstItem=m_head->item;
	return firstItem;
}

/* List rear
*/
template<typename Item>
Item List<Item>::rear() const {

	// Force check that the m_tail is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(m_tail != nullptr);
	Item lastItem=m_tail->item;
	return lastItem;

}

/* List get
//		returns the item at index
*/
template<typename Item>
Item List<Item>::get(int index) const {

	// Force index to be correct before getting the Item
	// Typical solution for deployement code is to throw
	// exceptions, since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(index >= 0 && index < m_size);

	Node* ptr = m_head;
	for (int i = 0; i < m_size;i++) {
		if (i == index) {
			Item someItem = ptr->item;
			return someItem;
		}
		ptr = ptr->next;
	}
}

/* List size
*/
template<typename Item>
int List<Item>::size() const {
	return m_size;
}

/* List find
*/
template<typename Item>
int List<Item>::find(const Item& item) const {
	Node* ptr = m_head;
	int i=0;
	while (ptr != nullptr) {
		if (ptr->item == item)
			return i;
		ptr = ptr->next;
		i++;
	}
	return -1;
}

/* List pop_front
*/
template<typename Item>
bool List<Item>::pop_front() {
	if (m_head == nullptr)
		return false;
	if (m_size == 1) {
		delete m_head;
		m_head = nullptr;
		m_tail = nullptr;
	}
	else {
		Node* ptr = m_head->next;
		ptr->prev = nullptr;
		delete m_head;
		m_head = ptr;
	}
	m_size--;
	return true;
}

/* List pop_rear
*/
template<typename Item>
bool List<Item>::pop_rear() {
	if (m_head == nullptr)
		return false;
	if (m_size == 1) {
		delete m_head;
		m_head = nullptr;
		m_tail = nullptr;
	}else {
		Node* ptr = m_tail->prev;
		ptr->next = nullptr;
		delete m_tail;
		m_tail = ptr;
	}
	m_size--;
	return true;

}

/* List remove
*/
template<typename Item>
bool List<Item>::remove(int index) {
	if (index < 0 || index >= m_size) {
		std::cout << "Can't remove: Out of bounds" << std::endl;
		return false;
	}
	else if (index == 0) {
		pop_front();
	}
	else if (index == m_size - 1) {
		pop_rear();
	}
	else {
		Node* eraseMe = m_head;
		for (int i = 0; i < m_size; i++) {
			if (i == index) {
				eraseMe->prev->next = eraseMe->next;
				eraseMe->next->prev = eraseMe->prev;
				delete eraseMe;
				m_size--;
				break;
			}
			eraseMe = eraseMe->next;
		}
	}
	return true;

}

#endif // _X_XMMXX
