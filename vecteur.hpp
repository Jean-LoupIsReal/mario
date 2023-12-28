#pragma once
#include<assert.h>

template <class TYPE>
class vecteur {

private:
	TYPE* _tab;					// Pointeur sur une vecteur d'entiers
	int _dim;					// Taille du vecteur

public:
	vecteur();					// Constructeur sans paramètre.
	vecteur(int dim);			// Initialise le vecteur avec une taille donnée par le paramètre d'entrée dim
	~vecteur();

	// Ajoutez des méthodes ici au fur et à mesure que
	// vous avancez votre laboratoire sur le vecteur.

	vecteur(const vecteur& v);						// Constructeur de copie / Copieur
	void print(std::ostream& sortie) const;			// Afficher les vecteur

	void push_back(const TYPE& nb);					// Methode qui permet d'aggrandir le tableau
	int size() const;								// Retourne le nombre d'élement dans un vecteur
	void resize(int dim);							// Methode qui change la taille du vecteur
	void clear();									// Methode qui remet le vecteur à vide

	TYPE& at(int index) const;						//Permet de donner une position d'un vecteur
	TYPE& operator[](int index) const;

	const vecteur<TYPE>& operator=(const vecteur<TYPE>& vecteur);  //Permet de mettre un vecteur égale à un autre
	bool operator==(const vecteur<TYPE>& vecteur) const;		// Vérifie si 2 vecteur sont égaux par le nombre d'élémentn et les élements contenus

	vecteur operator+(const vecteur<TYPE>& v) const;	//Concatène deux vecteur 
	const vecteur<TYPE>& operator+=(const vecteur& vecteur);

	template <class TYPE>
	friend void swap(vecteur<TYPE>& a, vecteur<TYPE>& b);			//Permet d'inversé 2 v

	void reverse();										//Itérative
	void reverseRecursive(int ind = 0);					//Récursive
};

template <class TYPE>
std::ostream& operator<<(std::ostream& sortie, const vecteur<TYPE>& v);

//*************************** Définition des variables ***************************//

// Complétez ce fichiers et ajouter des méthodes au fur et à
// mesure que vous avancez votre laboratoire sur le vecteur.

template <class TYPE>
vecteur<TYPE>::vecteur() {
	_tab = nullptr;
	_dim = 0;
}

template <class TYPE>
vecteur<TYPE>::vecteur(int dim) {
	assert(_dim >= 0);

	_dim = dim;
	_tab == nullptr; // Vecteur vide

	if (_dim > 0)
		_tab = new TYPE[_dim];
}

template <class TYPE>
vecteur<TYPE>::~vecteur() {
	clear();
}

template <class TYPE>
vecteur<TYPE>::vecteur(const vecteur<TYPE>& v) {
	_dim = v._dim;

	if (_dim > 0) {
		_tab = new TYPE[_dim];

		for (int i = 0; i < _dim; i++) {
			*(_tab + i) = *(v._tab + i);
		}
	}
	else {
		_tab = nullptr;
	}
}

template <class TYPE>
void vecteur<TYPE>::print(std::ostream& sortie) const {
	for (int i = 0; i < _dim; i++) {
		sortie << *(_tab + i);
	}
}

template <class TYPE>
void vecteur<TYPE>::push_back(const TYPE& nb) {
	TYPE* newTab = new TYPE[_dim + 1];

	for (int i = 0; i < _dim; i++) {
		*(newTab + i) = *(_tab + i);
	}

	*(newTab + _dim) = nb;

	delete[]_tab;
	_tab = newTab;
	_dim++;
}

template <class TYPE>
int vecteur<TYPE>::size() const {
	return _dim;
}

template <class TYPE>
void vecteur<TYPE>::resize(int dim) {
	assert(dim >= 0);

	TYPE* newTab = nullptr;
	newTab = new TYPE[dim];

	if (_dim == dim)
		return;

	if (dim == 0) {
		clear();
		return;
	}

	if (dim > 0) {

		for (int i = 0; i < _dim && i < dim; i++) {
			*(newTab + i) = *(_tab + i);
		}
	}

	delete[]_tab;
	_tab = newTab;
	_dim = dim;
}

template <class TYPE>
void vecteur<TYPE>::clear() {
	delete[]_tab;
	_tab = nullptr;
	_dim = 0;
}

template <class TYPE>
TYPE& vecteur<TYPE>::at(int index) const {
	assert(index >= 0 && index < _dim);

	return *(_tab + index);
}

template <class TYPE>
TYPE& vecteur<TYPE>::operator[](int index) const {
	return at(index);
}

template <class TYPE>
const vecteur<TYPE>& vecteur<TYPE>::operator=(const vecteur<TYPE>& vecteur) {
	if (this == &vecteur)
		return *this;

	clear();

	if (vecteur._dim > 0) {
		_dim = vecteur._dim;
		_tab = new int[_dim];

		for (int i = 0; i < _dim; i++) {
			*(_tab + i) = *(vecteur._tab + i);
		}
	}
	return *this;
}

template <class TYPE>
bool vecteur<TYPE>::operator==(const vecteur<TYPE>& vecteur) const {
	if (_dim != vecteur._dim)
		return false;

	for (int i = 0; i < _dim && i < vecteur._dim; i++) {

		if (*(_tab + i) != *(vecteur._tab + i))
			return false;
	}
	return true;
}

template <class TYPE>
vecteur<TYPE> vecteur<TYPE>::operator+(const vecteur<TYPE>& v) const {
	vecteur temp(_dim + v._dim);

	for (int i = 0; i < _dim; i++) {
		*(temp._tab + i) = *(_tab + i);
	}

	for (int i = 0; i < v._dim; i++) {
		*(temp._tab + i + _dim) = *(v._tab + i);
	}
	return temp;
}


template <class TYPE>
const vecteur<TYPE>& vecteur<TYPE>::operator+=(const vecteur<TYPE>& vecteur) {
	int ancDim = _dim;
	int ancDimV = vecteur._dim;

	resize(_dim + vecteur._dim);

	for (int i = 0; i < ancDimV; i++) {
		*(_tab + i + ancDim) = *(vecteur._tab + i);
	}
	return *this;
}

template <class TYPE>
void swap(vecteur<TYPE>& a, vecteur<TYPE>& b) {
	TYPE* tabTemp = a._tab;
	a._tab = b._tab;
	b._tab = tabTemp;

	int dimTemp = a._dim;
	a._dim = b._dim;
	b._dim = dimTemp;
}

template <class TYPE>
void vecteur<TYPE>::reverse() {
	for (int i = 0; i < _dim / 2; i++) {
		swap(*(_tab + i), *(_tab + _dim - i - 1));
	}
}

template <class TYPE>
void vecteur<TYPE>::reverseRecursive(int ind) {
	assert(ind >= 0 && ind <= _dim);

	if (ind == _dim / 2)
		return;

	swap(*(_tab + ind), *(_tab + _dim - ind - 1));

	reverseRecursive(ind + 1);
}

template <class TYPE>
std::ostream& operator<<(std::ostream& sortie, const vecteur<TYPE>& v) {
	v.print(sortie);

	return sortie;
}
