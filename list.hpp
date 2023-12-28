#pragma once
#include <cassert>

template <typename T>
class List;

// Classe d'une cellule. La liste est compos�e de plusieurs de ces cellules
template <typename T>
class Cellule {
	private:
		T _element; // Contenu d'une cellule de la liste
		Cellule<T>* _next; // Pointeur vers la cellule suivante de la liste
		Cellule<T>* _prev; // Pointeur vers la cellule pr�c�dente de la liste

		// Constructeur d'une cellule (m�thode appel�e � chaque fois qu'on fait un "new Cellule")
		Cellule(const T& element, Cellule<T>* next = nullptr, Cellule<T>* prev = nullptr) {
			_element = element;
			_next = next;
			_prev = prev;
		}

		friend class List<T>; /* La classe "List" a acc�s � la repr�sentation de la cellule bien que la classe
								 "Cellule" ait �t� d�clar�e � l'ext�rieur de la classe "List". */
};

template <typename T>
class List {
	private:
		Cellule<T>* _first;		// Pointe sur la premi�re cellule de la liste

		List(const List<T>&); // Copieur (pour le d�sactiver, il faut le placer dans la section "private")

	public:
		// Classe d'un it�rateur d'une liste (un it�rateur doit �tre associ� � une liste pour pointer une de ses cellules).
		class Iterator {
		private:
			Cellule<T>* _current; // Adresse de la cellule sur laquelle est pr�sentement positionn� l'it�rateur
			const List<T>* _list; // Adresse de la liste concern�e par l'it�rateur

			friend class List<T>; // La classe "List" a acc�s � la repr�sentation de l'it�rateur

		public:
			Iterator(); // Constructeur qui initialise "_current" et "_list" � "nullptr".
			~Iterator(); // Destructeur qui remet "_current" et "_list" � "nullptr".

			const Iterator& operator=(const Iterator&); // Pour assigner la valeur d'un it�rateur � un autre
			bool operator==(const Iterator&) const; // Pour comparer deux it�rateus (ils traitent de la m�me liste � la m�me position)
			bool operator!=(const Iterator&) const;
			Iterator operator++(int); // Pour d�placer un it�rateur � la cellule suivante (it++)
			const Iterator& operator++(); // Pour atteindre la cellule suivante sans modifier la position courante de l'it�rateur (++it)
			Iterator operator--(int); // Pour d�placer un it�rateur � la cellule pr�c�dente (it--)
			const Iterator& operator--(); // Pour atteindre la cellule pr�c�dente sans modifier la position courante de l'it�rateur (--it)
			T& operator*(); // Pour acc�der � l'�l�ment point� par l'it�rateur (it*)
			const T& operator*() const; // Pour acc�der � l'�l�ment point� par l'it�rateur (it*) sans pouvoir le modifier
		};

		List(); // Constructeur qui initialise "_first" � "nullptr".
		~List(); // Destructeur qui supprime toutes les cellules de la liste

		void clear(); // M�thode qui supprime toutes les cellules de la liste
		bool empty() const; // M�thode qui v�rifie si la liste est vide (retourne true) ou non (retourne false)

		Iterator begin() const; // M�thode qui retourne un it�rateur pointant sur la premi�re cellule
		Iterator end() const; // M�thode qui retourne un it�rateur ayant pour adresse "nullptr"

		Iterator insert(Iterator, const T&); // M�thode qui cr�e une nouvelle cellule juste avant la position de l'it�rateur.
		Iterator erase(Iterator); // M�thode qui supprime la cellule occupant la position point�e par l'it�rateur.
		Iterator erase(Iterator, Iterator); /* M�thode qui supprime toutes les cellules se retrouvant inclusivement entre le
											   premier it�rateur et le second it�rateur pass�s en param�tres d'entr�e. */
		T& operator[](Iterator); /* Cette surcharge d'op�rateur [] n'est pas pr�sente dans la librairie STL. Elle permet
									d'acc�der � l'�l�ment contenu dans la cellule qi occupe l'index sp�cifi� en param�tre
									d'entr�e. */
		const T& operator[](Iterator) const;

		Iterator operator()(const T&) const; /* Cette m�thode cherche dans la liste l'ocurrence de l'�l�ment pass� en param�tre
												d'entr�e. Si cet �l�ment est inexistant, un it�rateur "nullptr" est retourn�. */
		Iterator operator()(const T&, Iterator) const;

		const List<T>& operator=(const List<T>&); // Surcharge de l'op�rateur = pour copier le contenu d'une liste vers une autre.
};

/********************************************************/
/* CODEZ CI-DESSOUS LES M�THODES DE LA CLASSE ITERATOR. */
/********************************************************/
//========== CONSTRUCTEUR ==========//
template<typename T>
List<T>::Iterator::Iterator() {
	_current = nullptr;
	_list = nullptr;
}

//========== DESTUCTEUR ==========//
template<typename T>
List<T>::Iterator::~Iterator() {
	_current = nullptr;
	_list = nullptr;
}

//========== AFFECTATEUR ==========//
template<typename T>
typename const List<T>::Iterator& List<T>::Iterator::operator=(const Iterator& I) {
	_current = I._current;
	_list = I._list; 

	return I;
}

//========== OPERATEUR== ==========//
template<typename T>
typename bool List<T>::Iterator::operator==(const Iterator& I) const {
	assert(_list == I._list);

	return _current == I._current;
}

//========== OPERATEUR!= ==========//
template<typename T>
typename bool List<T>::Iterator::operator!=(const Iterator& I) const {
	assert(_list == I._list);

	return _current != I._current;
}

//========== OPERATEUR++ IT++ ==========//
template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int i) {
	Iterator it = (*this);
	
	operator++();

	return it;
}

//========== OPERATEUR++ ++IT ==========//
template<typename T>
typename const List<T>::Iterator& List<T>::Iterator::operator++() {
	assert(_list != nullptr);
	assert(_current != nullptr);		//Ne peut pas aller plus loin que nullptr

	_current = _current->_next;

	return *this;
}

//========== OPERATEUR++ IT-- ==========//
template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int i) {
	Iterator it = (*this);

	operator--();

	return it;
}

//========== OPERATEUR++ --IT ==========//
template<typename T>
typename const List<T>::Iterator& List<T>::Iterator::operator--() {
	assert(_list != nullptr);
	//assert(_current != _list->_first);

	if (_current == nullptr) {		//Si on recule du null, on va sur la derniere cellule
		_current = _list->_first->_prev;
	}
	else {
		_current = _current->_prev;
	}

	return *this;
}

//========== OPERATEUR* SETTEUR ==========//
template<typename T>
typename T& List<T>::Iterator::operator*() {
	assert(_list != nullptr);
	assert(_current != nullptr);
	assert(!_list->empty());

	return _current->_element;
}

//========== OPERATEUR* GETTEUR ==========//
template<typename T>
typename const T& List<T>::Iterator::operator*() const {
	assert(_list != nullptr);
	assert(_current != nullptr);
	assert(!_list->empty());

	return _current->_element;
}

/****************************************************/
/* CODEZ CI-DESSOUS LES M�THODES DE LA CLASSE LIST. */
/****************************************************/
//========== CONSTRUCTEUR ==========//
template<typename T>
List<T>::List() {
	_first = nullptr;
}

//========== DESTRUCTEUR ==========//
template<typename T>
List<T>::~List() {
	clear();
}

//========== CLEAR ==========//
template<typename T>
void List<T>::clear() {
	erase(begin(), end());
}

//========== EMPTY ==========//
//Bool�en qui retourne si le d�but de la liste est vide ou non
template<typename T>
bool List<T>::empty() const {
	return _first == nullptr;
}

//========== BEGIN ==========//
//Iterateur qui retourne la premiere position pour la liste
template<typename T>
typename List<T>::Iterator List<T>::begin() const {
	Iterator it;

	it._current = _first;
	it._list = this;

	return it;
}

//========== END ==========//
//Iterateur qui retourne la derniere position pour la liste
template<typename T>
typename List<T>::Iterator List<T>::end() const {
	Iterator it;

	it._current = nullptr;
	it._list = this;

	return it;
}

//========== INSERT ==========//
//Permet d'inserer une cellule dans la liste � un endroit donn�
template<typename T>
typename List<T>::Iterator List<T>::insert(Iterator I, const T& e) {
	assert(I._list == this);			//Si l'iterateur pointe dans la liste

	if (empty()) {						//Si la liste est vide
		I._current = _first->_prev = _first = new Cellule<T>(e);
	}
	else if (I._current == nullptr) {	//Insert apr�s le dernier �l�ment
		I._current = _first->_prev = _first->_prev->_next = new Cellule<T>(e, nullptr, _first->_prev);
	}
	else if (I._current == _first) {	//Insert apr�s le premier �l�ment
		I._current = _first = I._current->_prev = new Cellule<T>(e, I._current, I._current->_prev);
	}
	else {								//Insert au milieu
		I._current = I._current->_prev = I._current->_prev->_next = new Cellule<T>(e, I._current, I._current->_prev);
	}
	
	return I;
}

//========== ERASE I ==========//
//Supprime une cellule en fonction de l'it�rateur
template<typename T>
typename List<T>::Iterator List<T>::erase(Iterator I) {
	assert(I._list == this);					////Si l'iterateur pointe dans la liste
	assert(I._current != nullptr);				//Si l'iterateur actuel est diff�rent de null
	assert(!empty());							//S'il reste une seule cellule

	Cellule<T>* trash = I._current;

	if (_first == _first->_prev) {				//_first->_next == nullptr //Reste une seule cellule
		_first = I._current = nullptr;
	}
	else if (I._current == _first) {			//Supprime la premiere cellule
		I._current->_next->_prev = _first->_prev;
		_first = I._current = I._current->_next;
	}
	else if (I._current->_next == nullptr) {	//Supprime la derniere cellule
		I._current->_prev->_next = nullptr;
		I._current = _first->_prev = I._current->_prev;
	}
	else {										//Supprime cellule du milieu 
		I._current->_next->_prev = I._current->_prev;
		I._current = I._current->_prev->_next = I._current->_next;
	}

	delete trash;

	return I;
}

//============ ERASE POINT A a POINT B ============//
//Supprime plusieurs cellule d'un point A � un point B
template<typename T>
typename List<T>::Iterator List<T>::erase(Iterator first, Iterator last) {
	while (first != last) {
		first = erase(first);
	}	
	if (first != end()) {
		first = erase(first);
	}

	return first;
}

//============  OPERATOR[] SETTEUR ============//
template<typename T>
typename T& List<T>::operator[](Iterator I) {
	assert(_first->_prev._list == this);			//Si positionner sur la liste 	

	return *I;
}

//============  OPERATOR[] GETTEUR ============//
template<typename T>
typename const T& List<T>::operator[](Iterator I) const {
	assert(_first->_prev._list == this);		  //Si positionner sur la liste 	

	return *I;
}

//============  OPERATOR() 1 PARAMETRE ============//
template<typename T>
typename List<T>::Iterator List<T>::operator()(const T& e) const {

	return operator()(begin(), e);
}
//============  OPERATOR() 2 PARAMETRES ============//
template<typename T>
typename List<T>::Iterator List<T>::operator()(const T& e, Iterator I) const {
	assert(I._list == this);		//Si l'iterateur pointe dans la liste

	while (I != end()) {
		if (*I == e) {
			return I;
		}
		I++;
	}

	return I;
}

//============  OPERATOR= ============//
//Copier une liste dans une autre
template<typename T>
typename const List<T>& List<T>::operator=(const List<T>& l) {
	if (this == &l)			//Cas limite l  = l
		return *this;
	
	clear();

	for (Iterator it = begin(); it != end(); it++)
		insert(it, end());
	
	return *this;
}
