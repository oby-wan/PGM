#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <class T>
class PGM {
protected:
	T** board;
	T numrows;
	T numcols;
	T max;
	string magic;
	string comment;
	void readInput(ifstream& infile);

public:
	class exceptionClass;
	PGM(); //default
	PGM(ifstream&);//one arg
	~PGM();//destructor
	PGM operator+(const PGM<T>&);//addition
	PGM(const PGM<T>&); //copy
	PGM(PGM<T>&&); //move
	PGM<T>& operator=(const PGM<T>&); //assignment
	PGM<T>& operator=(PGM<T>&&); //move assignment
	template <class T>
	friend void savetoPGM(const PGM<T>&, const char&);
};

template <class T>
void PGM<T>::readInput(ifstream& infile) {      //read input
	cout << "Read Input Called" << endl;
	if (infile) {
		getline(infile, magic);
		getline(infile, comment);
		infile >> numcols >> numrows >> max;
		board = new T * [numrows];

		for (T i = 0; i < numrows; i++) {
			board[i] = new T[numcols];
		}

		for (T row = 0; row < numrows; row++) {
			for (T col = 0; col < numcols; col++) {
				infile >> board[row][col];
			}
		}
	}
	else
		throw PGM::exceptionClass("Read input error");
}


template <class T>
class PGM<T>::exceptionClass {            //exception class
private:
	const char* message;
public:
	exceptionClass(const char* c);
	const char* returnError();
};
template <class T>
PGM<T>::exceptionClass::exceptionClass(const char* c) : message(c) {
	message = c;
}

template <class T>
const char* PGM<T>::exceptionClass::returnError() {
	return message;
}

template <class T>
PGM<T>::PGM() : numrows(0), numcols(0), max(0), board(nullptr), magic(""), comment("") {
	cout << "Default constructor called" << endl;
} 

template <class T>
PGM<T>::PGM(ifstream& infile) {
	cout << "PGM One arg constructor called" << endl;
	try {
		readInput(infile);
	}
	catch (PGM::exceptionClass e) {
		throw e;
	}
}

template <class T>
PGM<T>::~PGM() {
	cout << "PGM destructor called" << endl;
	for (T i = 0; i < numcols; i++){
		delete[] board[i];
		board[i] = nullptr;
	}
	delete[] board;
	board = nullptr;
}

template <class T>
PGM<T> PGM<T>::operator+(const PGM<T>& p) {
	cout << "PGM addition operator called" << endl;
	PGM result;
	for (T i = 0; i < numrows; i++) {
		for (T j = 0; j < numcols; j++) {
			result.board[i][j] = board[i][j] + p.board[i][j];
		}
	}
	return result;
}

template <class T>
PGM<T>::PGM(const PGM<T>& p) {
	cout << "Copy constructor called" << endl;
	numrows = p.numrows;
	numcols = p.numcols;
	max = p.max;
	magic = p.magic;
	comment = p.comment;
	board = new T * [numrows];

	for (T i = 0; i < numrows; i++) {
		board[i] = new T[numcols];
	}
	for (T i = 0; i < numrows; i++) {
		for (T j = 0; j < numcols; j++) {
			board[i][j] = p.board[i][j];
		}
	}
}

template <class T>
PGM<T>::PGM(PGM<T>&& p) : numrows(p.numrows), numcols(p.numcols), max(p.max), board(p.board), magic(p.magic), comment(p.comment) {
	cout << "move constructor called" << endl;
	p.numrows = 0;
	p.numcols = 0;
	p.board = nullptr;
}

template <class T>
PGM<T>& PGM<T>::operator=(const PGM<T>& p) {
	cout << "assignment operator called" << endl;
	if (board != nullptr) {
		for (T i = 0; i < numrows; i++) {
			delete[] board[i];
		}
		delete[] board;
	}
		numrows = p.numrows;
		numcols = p.numcols; 
		max = p.max;
		magic = p.magic;
		comment = p.comment;

	board = new T * [numrows];
	for (T i = 0; i < numrows; i++) {
		board[i] = new T[numcols];
	}
	for (T i = 0; i < numrows; i++) {
		for (T j = 0; j < numcols; j++) {
			swap(board[i][j], board[i][j]);
		}
	}
	return *this;
}

template <class T>
PGM<T>& PGM<T>::operator=(PGM<T>&& p) {
	cout << "move assignment operator called" << endl;
	swap(board, p.board);
	swap(numrows, p.numrows);
	swap(numcols, p.numcols);
	swap(max, p.max);
	swap(magic, p.magic);
	swap(comment, p.comment);
	
}

template <class T>
void savetoPGM(const PGM<T>& p, const char* c) {
	cout << "Saving PGM object to ASCII file " << endl;
	if (p.board != nullptr) {
		ofstream out(c);
		out << p.magic << endl;
		out << p.comment << end;
		out << p.numcols << " " << p.numrows << endl;
		out << p.max << endl;

		for (int i = 0; i < p.numrows; i++) {
			for (int j = 0; j < p.numcols; j++) {
				out << p.board[i][j] << " ";
			}
			out << endl;
		}
		out.close();
	}
	else
	{
		cout << "Error: PGM object is uninitialized." << endl;
	}
}