/* WordList source file
*
*
*	This file will contain the function definitions you will implement.
*	The function signitures may NOT be changed.  You may create your own
*	helper functions and include them in this file.
*
*	In addition to the specific instructions for each function, no function
*	should cause any memory leaks or alias m_list in any way that would result
*	in undefined behavior.
*
*	Topics: Multilevel Pointers, Dynamic Allocation, Classes
*
*/
// MS VS does not like cstring functions, this is to tell it to chill out.
#ifdef _MSC_VER  //  Microsoft Visual C++

#define _CRT_SECURE_NO_DEPRECATE

#else  // not Microsoft Visual C++, so assume UNIX interface

#endif



// Do not include any other libraries
#include"wordlist.h"
#include<iostream>
#include<cstring>

using std::cout;
using std::endl;

using std::strcat;
using std::strcmp;
using std::strcpy;
using std::strlen;

/* Function: Wordlist Constructor
*/
WordList::WordList(const int max_words) {
	if (max_words >= 1) {
		m_max = max_words;
		m_count = 0;
		m_list = new char* [m_max];
		for (unsigned int i = 0; i < m_max; i++) {
			m_list[i] = new char[20];
		}
	}
	else {
		m_list = nullptr;
		m_max = 0;
		m_count = 0; 
	}
}

/* Function: Wordlist Copy Constructor
*/
WordList::WordList(const WordList& other) {
	m_max = other.m_max;
	m_count = other.m_count;
	m_list = new char* [m_max];
	for (unsigned int i = 0; i < m_max; i++) {
		m_list[i] = new char[20];
		if (i < m_count) {
			strcpy(m_list[i], other.m_list[i]);
		}
	}
}


/* Function: Wordlist Destructor
*/
WordList::~WordList() {
	for (unsigned int i = 0; i < m_max; i++) {
		delete[] m_list[i];
	}
	delete[] m_list;

}

/* Function: printList
*/
int	WordList::print() const {
	if (m_list != nullptr) {
		for (unsigned int i = 0; i < m_count; i++) {
			std::cout << m_list[i];
			if (i != m_count-1)
				std::cout <<" ";
		}
		if (m_count!=0)
			std::cout << std::endl;
		return m_count;
	}
	else {
		return -1;
	}


}



/* Function: at
*/
char* WordList::at(const int index) const {
	if ((unsigned int)index < m_count)
		return m_list[index];
	return nullptr;
}


/* Function: count
*/
int	WordList::count() const {

	return m_count;

}


/* Function: add
*/
int	WordList::add(const char word[]) {
	if(word[0]=='\0'){
		return -1;
	}else {
		int ret=0;
		if (m_max == m_count) {
			ret = 1;
			if (m_list == nullptr) { ret = -2; }
			WordList temp = *this;
			if (m_list != nullptr) {
				for (unsigned int i = 0; i < m_max; i++) {
					delete[] m_list[i];
				}
			}
			delete[] m_list;
			m_max += 1;
			m_list = new char* [m_max];
			for (unsigned int i = 0; i < m_max-1; i++) {
				m_list[i] = new char[20];
				for (unsigned int j = 0; j <= strlen(temp.m_list[i]); j++) {
					m_list[i][j] = temp.m_list[i][j];
				}
			}
			m_list[m_count] = new char[20];
		}
		for (unsigned int i = 0; i <= strlen(word); i++) {
			m_list[m_count][i] = word[i];
		}
		
		m_count += 1;
		return ret;

	}
}


/* Funtion: remove
*/
int	WordList::remove(const char word[]) {

	if (m_list == nullptr) {
		return -1;
	}
	else if (m_count == 0) {
		return 0;
	}
	else {
		for (unsigned int i = 0; i < m_count; i++) {
			if (strcmp(m_list[i], word) == 0) {
				delete[]m_list[i];
				m_list[i] = nullptr;
			}
		}
		WordList temp(m_max);
		int j=0;
		int wordRev = 0;
		for (unsigned int i = 0; i < m_max; i++) {
			while (m_list[i] == nullptr) {
				i++;
				wordRev++;
			}
				
			if (i == m_count)
				break;
			strcpy(temp.m_list[j], m_list[i]);
			j++;
			temp.m_count++;
		}
		*this = temp;
		return wordRev;
	}
	return -1;
}


/* Funtion: append
*/
int	WordList::append(const WordList* other) {
	if (other->m_list == nullptr || other->m_count == 0|| other == this) {
		return 0;
	}
	else {
		int retVal;
		if (m_list == nullptr) {
			retVal = -1;
		}else {
			retVal = other->m_count;
		}for (unsigned int i = 0; i < other->m_count; i++) {
			this->add(other->m_list[i]);
		}
		return retVal;
	}

}


/* Funtion: search
*/
int WordList::search(const char word[]) const {
	for (unsigned int i = 0; i < m_count; i++) {
		if (strcmp(m_list[i], word) == 0) {
			return i;
		}
	}
	return -1;
	

}


/* Funtion: sort
*/
int	WordList::sort() {
	if (m_list == nullptr) {
		return -1;
	}
	else if (m_count == 1) {
		return 1;
	}
	else if (m_count == 0) {
		return 0;
	}
	else {
		for (unsigned int k = 0; k <= m_count; k++) {
			for (unsigned int i = k + 1; i <= m_count - 1; i++) {
				if (strcmp(m_list[i], m_list[k]) == -1) {
					char* temp = m_list[k];
					m_list[k] = m_list[i];
					m_list[i] = temp;
				}
			}
		}
		return 0;
	}

}


/* Funtion: Assignment Operator
*/
WordList& WordList::operator=(const WordList& other) {
	if (&other == this)
		return (*this);
	if (m_list != nullptr) {
		for (unsigned int i = 0; i < m_max; i++) {
			delete[] m_list[i];
		}
	}
	delete[] m_list;
	m_max = other.m_max;
	m_count = other.m_count;
	m_list = new char* [m_max];
	for (unsigned int i = 0; i < m_max; i++) {
		m_list[i] = new char[20];
		if (i < m_count) {
			strcpy(m_list[i], other.m_list[i]);
		}
	}
	return *this;
}