#pragma once
#include <assert.h>

template <class TYPE>
class map {
private:
	char* _name; // Pointeur sur le nom attribué à la map
	TYPE** _map; // Pointeur de pointeurs pour accéder à la matrice de la map
	int _nbLine, // Nombre de lignes de la matrice de la map
		_nbCol; // Nombre de colonnes de la matrice de la map

public:
	map();
	map(const char* name, int line, int col);
	~map();

	void clear(); // Désalloue complètement la matrice et son nom
	void clearMap(); // Désalloue seulement la matrice (pas son nom)
	void clearName(); // Désalloue seulement le nom (pas la matrice)int nbLine() const;

	int nbLine() const; // Retourne le nombre de lignes de la matrice
	int nbCol() const; // Retourne le nombre de colonnes de la matrice

	void resize(int nbLine, int nbCol); // Redimensionne la matrice de la map
	TYPE& at(int posI, int posJ); // Retourne une référence sur l’élément occupant la
	// position (i, j) dans la matrice pour pouvoir y
	// accéder ou le modifier
	TYPE* operator[](int posI); // Retourne un pointeur (une référence) sur la rangée de
	// la matrice dans laquelle se retrouve la valeur qu’on
	// souhaite lire ou remplacer

	const char* getName() const; // Retourne le nom de la map (sans modification possible)
	void setName(const char* name); // Modifie le nom de la map

	void print(std::ostream& output) const; // Affiche le nom et le contenu de la matrice
	void read(std::istream& input); // Enregistre dans le nom et dans la matrice de la map
	// les informations provenant d’un flux d’entrée (fichier,
	// console, etc.)

	map(const map& map); // Copieur
	const map<TYPE>& operator=(const map& map); // Affectateur
};

template <class TYPE>
std::ostream& operator<<(std::ostream& sortie, const map<TYPE>& mapObj);

template <class TYPE>
std::istream& operator>>(std::istream& input, map<TYPE>& mapObj);

// Etape 1 : Constructeurs, destructeur, constructeur de copie et méthode clear
template <class TYPE>
map<TYPE>::map() {
	_name = nullptr;
	_map = nullptr;
	_nbLine = _nbCol = 0;
}

template <class TYPE>
map<TYPE>::map(const char* name, int nbLine, int nbCol) {
	assert(nbLine >= 0 && nbCol >= 0);

	_name = nullptr;
	_map = nullptr;
	_nbLine = _nbCol = 0;

	if (nbLine != 0 && nbCol != 0) {	// Pour construire la matrice
		_nbLine = nbLine;
		_nbCol = nbCol;

		int lenght = strlen(name); // Construit le nom
		if (lenght != 0) {
			_name = new char[lenght + 1];
			strcpy_s(_name, lenght + 1, name);
		}

		_map = new TYPE * [nbLine];

		for (int i = 0; i < nbLine; i++) {
			*(_map + i) = new TYPE[nbCol];

		}
	}
}

template <class TYPE>
map<TYPE>::~map() {
	clear();
}

template <class TYPE>
void map<TYPE>::clear() {
	clearMap();
	clearName();
}

template <class TYPE>
void map<TYPE>::clearMap() {
	for (int i = 0; i < _nbLine; i++) {
		delete[] * (_map + i);
	}

	delete[] _map;
	_map = nullptr;
	_nbLine = _nbCol = 0;
}

template <class TYPE>
void map<TYPE>::clearName() {
	delete[] _name;
	_name = nullptr;
}

// Etape 2 : Setteur et getteur
template <class TYPE>
int map<TYPE>::nbLine() const {
	return _nbLine;
}

template <class TYPE>
int map<TYPE>::nbCol() const {
	return _nbCol;
}

template <class TYPE>
const char* map<TYPE>::getName() const {
	if (_name == nullptr) {

		return "\0";
	}

	return _name;
}

template <class TYPE>
void map<TYPE>::setName(const char* name) {
	clearName();

	int length = strlen(name);

	if (length != 0) {

		_name = new char[length + 1];
		strcpy_s(_name, length + 1, name);
	}
}

// Etape 3 : Resize
template <class TYPE>
void map<TYPE>::resize(int nbLine, int nbCol) {
	assert(nbLine >= 0 && nbCol >= 0);

	if (nbLine == _nbLine && nbCol == _nbCol) // Si identique
		return;

	TYPE** newMap = nullptr;

	if (nbLine != 0 && nbCol != 0) {
		newMap = new TYPE * [nbLine];

		for (int i = 0; i < nbLine; i++) {
			*(newMap + i) = new TYPE[nbCol];
		}

		for (int i = 0; i < nbLine && i < _nbLine; i++) {

			for (int j = 0; j < _nbCol && j < nbCol; j++) {
				*(*(newMap + i) + j) = *(*(_map + i) + j);
			}
		}
	}
	else {
		nbLine = nbCol = 0;
	}

	clearMap();

	_map = newMap;
	_nbLine = nbLine;
	_nbCol = nbCol;
}


// Etape 4 : at() et opérateur []
template <class TYPE>
TYPE& map<TYPE>::at(int posI, int posJ) {
	assert(posI >= 0 && posI < _nbLine);
	assert(posJ >= 0 && posJ < _nbCol);

	return *(*(_map + posI) + posJ);
}

template <class TYPE>
TYPE* map<TYPE>::operator[](int posI) {
	assert(posI >= 0 && posI < _nbLine);

	return *(_map + posI);
}

// Etape 5 : print et operateur <<
template <class TYPE>
void map<TYPE>::print(std::ostream& output) const {
	for (int i = 0; i < _nbLine; i++) {

		for (int j = 0; j < _nbCol; j++) {
			output << *(*(_map + i) + j) << " ";
		}
		output << std::endl;
	}
}

// Etape 6 : read et operateur >>
template <class TYPE>
void map<TYPE>::read(std::istream& input) {
	assert(_map != nullptr);

	for (int i = 0; i < _nbLine; i++) {

		for (int j = 0; j < _nbCol; j++) {
			input >> *(*(_map + i) + j);
		}
	}
}

template <class TYPE>
std::ostream& operator<<(std::ostream& output, const map<TYPE>& mapObj) {
	mapObj.print(output);

	return output;
}

template <class TYPE>
std::istream& operator>>(std::istream& input, map<TYPE>& mapObj) {
	mapObj.read(input);

	return input;
}

// Etape 8 : copieur & operateur = 
template <class TYPE>
map<TYPE>::map(const map& map) {
	_nbLine = map._nbLine;
	_nbCol = map._nbCol;
	_map = nullptr;
	_name = nullptr;

	int lenght = strlen(map._name);
	if (lenght != 0) {
		_name = new char[lenght + 1];
		strcpy_s(_name, lenght + 1, map._name);
	}

	if (_nbLine != 0) {
		_map = new TYPE * [_nbLine];

		for (int i = 0; i < _nbLine; i++) {
			*(_map + i) = new TYPE[_nbCol];
		}

		for (int i = 0; i < _nbLine; i++) {

			for (int j = 0; j < _nbCol; j++) {
				*(*(_map + i) + j) = *(*(map._map + i) + j);
			}
		}
	}
}

// Etape 8 : Copieur et operateur =
template <class TYPE>
const map<TYPE>& map<TYPE>:: operator=(const map& map) {
	if (this == &map) // Cas limite map = map
		return *this;

	clear();

	if (map._nbLine != 0 && map._nbCol != 0) {
		_nbLine = map._nbLine;
		_nbCol = map._nbCol;

		int lenght = strlen(map._name);
		if (lenght != 0) {
			_name = new char[lenght + 1];
			strcpy_s(_name, lenght + 1, map._name);
		}

		_map = new TYPE * [_nbLine];

		for (int i = 0; i < _nbLine; i++) {
			*(_map + i) = new TYPE[_nbCol];

			for (int j = 0; j < _nbCol; j++) {
				*(*(_map + i) + j) = *(*(map._map + i) + j);
			}
		}
	}
	return *this;
}
