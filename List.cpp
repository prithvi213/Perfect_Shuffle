/* Name: Prithvi Arunshankar
 * CruzID: parunsha
 * Assignment: pa5
*/
//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include<climits>
#include"List.h"

// Private Constructor --------------------------------------------------------

// Node Constructor
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}


// Class Constructors & Destructors ------------------------------------------

// Creates a new List in the empty state.
List::List() {
    this->frontDummy = new Node(INT_MIN);
    this->backDummy = new Node(INT_MAX);
    this->frontDummy->next = backDummy;
    this->backDummy->prev = frontDummy;
    this->beforeCursor = frontDummy;    
    this->afterCursor = backDummy;
    this->beforeCursor->next = afterCursor;
    this->afterCursor->prev = beforeCursor;
    this->pos_cursor = 0;
    this->num_elements = 0;
}

// Copy Constructor
List::List(const List& L) {
    // make this an empty List
    this->frontDummy = new Node(INT_MIN);
    this->backDummy = new Node(INT_MAX);
    this->frontDummy->next = backDummy;
    this->backDummy->prev = frontDummy;
    this->beforeCursor = frontDummy;    
    this->afterCursor = backDummy;
    this->beforeCursor->next = afterCursor;
    this->afterCursor->prev = beforeCursor;
    this->pos_cursor = 0;
    this->num_elements = 0;

    // if L is not empty, load its elements
    if(L.length() != 0) {
        Node* cursor = L.frontDummy->next;

        while(cursor != L.backDummy) {
            this->insertBefore(cursor->data); 
            cursor = cursor->next;
        }

        this->moveFront();
        this->num_elements = L.num_elements;
    }
}

// Destructor
List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

// Access functions ----------------------------------------------------------

// length()
// Returns the length of this List
int List::length() const {
    return(num_elements);
}

// front()
// Returns the front element in this List.
// pre: length() > 0
ListElement List::front() const {
    if(length() == 0) {
        throw std::length_error("List: front(): empty List");
    }

    return(frontDummy->next->data);
}

// back()
// Returns the back element in this List.
// pre: length() > 0
ListElement List::back() const {
    if(length() == 0) {
        throw std::length_error("List: back(): empty List");
    }

    return(backDummy->prev->data);
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length()
int List::position() const {
    return(pos_cursor);
}

// peekNext()
// Returns the element after the cursor
// pre: position() < length() 
ListElement List::peekNext() const {
    if(position() == length()) {
        throw std::out_of_range("List: peekNext(): cannot return data at next element");
    }

    return(afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor
// pre: position() > 0
ListElement List::peekPrev() const {
    if(position() == 0) {
        throw std::out_of_range("List: peekPrev(): cannot return data at previous element");
    }

    return(beforeCursor->data);
}


// Manipulation procedures ---------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
    if(length() == 0) {
        return;
    }

    this->moveFront();

    while(this->length() > 0) {
        this->eraseAfter();    
    }

    num_elements = 0;
    pos_cursor = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = beforeCursor->next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
    pos_cursor = length();
    afterCursor = backDummy; 
    beforeCursor = afterCursor->prev;
}

// moveNext()
// Moves cursor to next higher position. Returns the list element that
// was passed over.
// pre: position() < length()
ListElement List::moveNext() {
    if(position() == length()) {
        throw std::out_of_range("List: moveNext(): Cursor pointed at last element."); 
    }

    pos_cursor++;
    beforeCursor = beforeCursor->next;
    afterCursor = afterCursor->next;
    return(peekPrev()); 
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position() > 0
ListElement List::movePrev() {
    if(position() == 0) {
        throw std::out_of_range("List: movePrev(): Cursor pointed at first element."); 
    }

    pos_cursor--;
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    return(peekNext());
}

// insertAfter()
// Inserts x after cursor
void List::insertAfter(ListElement x) {
    Node* newNode = new Node(x);
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;
    newNode->prev = beforeCursor;
    newNode->next = afterCursor;
    afterCursor = newNode;
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
    Node* newNode = new Node(x);
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;
    newNode->prev = beforeCursor;
    newNode->next = afterCursor;
    beforeCursor = newNode;
    num_elements++;
    pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x
// pre: position() < length() 
void List::setAfter(ListElement x) {
    if(position() == length()) {
        throw std::out_of_range("List: setAfter(): Cursor pointed at end of list"); 
    }

    afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x
// pre: position() > 0 
void List::setBefore(ListElement x) {
    if(position() == 0) {
        throw std::out_of_range("List: setAfter(): Cursor pointed at front of list"); 
    }

    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position() < length()
void List::eraseAfter() {
    if(position() == length()) {
        throw std::out_of_range("List: eraseAfter(): Cursor pointed at end of list");
    } 

    Node* deletedNode = afterCursor;
    Node* afterNext = afterCursor->next;
    beforeCursor->next = afterNext;
    afterNext->prev = beforeCursor;
    afterCursor = afterNext;
    num_elements--;
    delete(deletedNode); 
}

// eraseBefore()
// Deletes element before cursor.
// pre: position() > 0
void List::eraseBefore() {
    if(position() == 0) {
        throw std::out_of_range("List: eraseBefore(): Cursor pointed at front of list");
    }

    Node* deletedNode = beforeCursor;
    Node* beforePrev = beforeCursor->prev;
    afterCursor->prev = beforePrev;
    beforePrev->next = afterCursor;
    beforeCursor = beforePrev;
    num_elements--;
    pos_cursor--;
    delete(deletedNode);
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x) {
    while(position() != length()) {
        moveNext(); 

        if(peekPrev() == x) {
            return pos_cursor;    
        }
    }

    return(-1); 
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
    while(position() != 0) {
        movePrev();

        if(peekNext() == x) {
            return(pos_cursor);
        }
    }

    return(-1);
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrence of each element, and removing all other occurrences. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
    // If length() <= 1 -> NOTHING to clean up
    if(length() <= 1) {
        return;
    }

    int original_pos = position();
    int findValue;
    int cursorDrop = 0;
    int tempCursor = 1;
    int loops = 0;
    int new_pos;

    for(Node* val = frontDummy->next; val != backDummy; val = val->next) {
        tempCursor = tempCursor + loops;
        moveFront();

        for(int i = 0; i < tempCursor; i++) {
            moveNext();
        }

        while(position() != length()) {
            findValue = findNext(val->data);
            
            if(findValue != -1) {
                eraseBefore();
                movePrev();

                if(findValue < original_pos) {
                    cursorDrop++; 
                }
            }

            if(position() != length()) {
                moveNext();
                tempCursor++;
            }
        }

        loops++;
        tempCursor = 1;
    }

    if(original_pos == 0) {
        moveFront();
        new_pos = 0;
    } else {
        moveFront();
        for(int i = 0; i < (original_pos - cursorDrop); i++) {
            moveNext();
        }

        new_pos = original_pos - cursorDrop;
    }

    pos_cursor = new_pos;
} 

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at position 0.
List List::concat(const List& L) const {
    List J; 
    Node* cursor = this->frontDummy->next;   
    Node* cursorL = L.frontDummy->next;

    // Gets original contents into new List
    while(cursor != this->backDummy) {
        J.moveBack();
        J.insertAfter(cursor->data);
        cursor = cursor->next;
    }

    // Copies contents of L into List
    while(cursorL != L.backDummy) {
        J.moveBack();
        J.insertAfter(cursorL->data);
        cursorL = cursorL->next;
    }

    J.moveFront();
    J.num_elements = this->length() + L.length();
    return(J);
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
    std::string listRep = "";

    if(length() == 0) {
        return "";
    }

    Node* cursor = frontDummy->next;

    while(cursor != backDummy) {
        if(cursor != nullptr) {
            listRep += "(" + std::to_string(cursor->data) + ")";
        }

        if(cursor != backDummy->prev) {
            listRep += ", ";
        }

        cursor = cursor->next;
    }

    return(listRep);
} 

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
    if(this->length() != R.length()) {
        return(false);
    }

    if(this->length() == 0 && R.length() == 0) {
        return(true);
    }

    Node* cursor = this->frontDummy->next;
    Node* cursorR = R.frontDummy->next; 

    while(cursor != backDummy && cursorR != R.backDummy) {
        if(cursor->data != cursorR->data) {
            return(false);
        }

        cursor = cursor->next;
        cursorR = cursorR->next;
    }

    return(true);
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream
std::ostream& operator<<( std::ostream& stream, const List& L) {
    return(stream << L.List::to_string());
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
    return(A.List::equals(B));
}

// operator=()
// Overwrites the state of this List with state of L
List& List::operator=( const List& L ) {
    if(this != &L) {
        List temp = L;

        // Swap all the fields
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }

    return(*this);
}
