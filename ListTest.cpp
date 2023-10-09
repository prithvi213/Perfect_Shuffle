/* Name: Prithvi Arunshankar
 * CruzID: parunsha
 * Assignment: pa5
*/
//-----------------------------------------------------------------------------
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main() {
    List A;
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    A.insertBefore(4);
    A.insertBefore(4);
    cout << "Before Cleanup: " << A << endl;

    A.findPrev(4);
    A.cleanup();

    cout << "After Cleanup: " << A << endl;
    cout << A.position() << endl;
    cout << endl;

    List B, C;

    for(int i = 1; i <= 12; i++) {
        B.insertAfter(i);
        C.insertBefore(12 - (2 * i));
    }   

    cout << "B: " << B << endl;
    cout << "C: " << C << endl;
    cout << endl;

    List D, E;
    D = A.concat(B);
    E = A.concat(C);
    E.moveBack();

    cout << "D: " << D << endl;
    cout << "E: " << E << endl; 
    cout << endl;

    cout << "D.findNext(3) = " << D.findNext(3) << endl;
    cout << "E.findPrev(4) = " << E.findPrev(4) << endl;
    cout << endl;

    List F;
    F = E;
    cout << "E == F is " << (E==F?"true":"false") << endl;
    cout << "A == B is " << (A==B?"true":"false") << endl;
    cout << endl;

    List G;
    G = F;

    for(int i = 0; i < 5; i++) {
        G.moveNext();
    }

    G.setBefore(23);
    G.setAfter(29);
    cout << "G: " << G << endl;

    List H;
    H = C;

    for(int i = 0; i < 2; i++) {
        H.moveNext();
    }

    H.movePrev();
    H.eraseBefore();
    cout << "H: " << H << endl;
    cout << endl;

    List I;
    I = D;

    I.moveBack();

    for(int i = 0; i < 2; i++) {
        I.movePrev();
    }

    I.eraseAfter(); 
    cout << "I: " << I << endl;
    cout << endl;

    cout << "I.front() = " << I.front() << endl;
    cout << "I.back() = " << I.back() << endl;
    cout << "I.length() = " << I.length() << endl;
    cout << endl;

    List J;
    J = F;
    
    for(int i = 0; i < 5; i++) {
        J.moveNext();
    }

    cout << "J: " << J << endl;
    cout << "J.peekPrev() = " << J.peekPrev() << endl;
    cout << "J.peekNext() = " << J.peekNext() << endl;
    J.clear();
    cout << "After Clear: J = " << J << endl;
    cout << "J.length() = " << J.length() << endl;

    exit(EXIT_SUCCESS);
}
