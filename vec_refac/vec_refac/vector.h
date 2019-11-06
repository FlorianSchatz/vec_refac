#pragma once
#include <algorithm>
#include <memory>

template <class T>
class vector
{
private:
	std::unique_ptr<T> vec = std::make_unique<T[]>(0);		//"Start"Vektor
	int used_fields;		// number of used elemnts of the vector
	int length;			//real length of the vector
public:
	vector() {};
	~vector();
	void resize(int);			//verk�rzt Vektor auf �bergebene L�nge
	void popback();				//entfernt letztes Element
	void pushback(T);			//f�gt am Ende des Vektors �bergebenen Wert ein
	void clear();				//setzt alle ben�tzten Datenfelder des Vektors auf null
	int size();					//gibt L�nge des physikalischen Vektors zur�ck
	T& at(int);					//gibt Inhalt an �bergebener Stelle zur�ck
	//T& operator= (const vector&);
	//const T& operator[] (size_type) const;
	//T& operator[] (size_type);
};


template<class T>
vector<T>::~vector() {
	
}

template<class T>
void vector<T>::clear() {
	for (int i = 0; i < used_fields; ++i) {
		//Inhalt des Vektors elementweise nullen
		vec[i] = 0;
	}
	//Vektor auf Bufferl�nge k�rzen
	resize(EXTRA_LENGTH);
	used_fields = 0;
}

template<class T>
void vector<T>::resize(int nu_length) {
	if (nu_length != length) {
		//�bergebene L�nge entspricht nicht der bereits Vorhandenen
		//neues Array allozieren
		T* nu_vector = new T[nu_length];
		for (int i = 0; i < length; i++) {
			if (i < nu_length) {
				//Elementweise kopieren
				nu_vector[i] = vec[i];
			}
		}
		if (nu_length < used_fields) {
			//Vektor wurde so gek�rzt, dass Daten verloren gegangen sind -> Nutzdatenl�nge anpassen
			used_fields = nu_length;
		}
		// Gesamtl�nge des Vektors anpassen und alten Vektor l�schen
		length = nu_length;
		delete[] vec;
		//Zeiger auf neuen Vektor umbiegen
		vec = nu_vector;
	}
}

template<class T>
void vector<T>::popback() {
	//letzteS Element nullen und physikalische L�nge decrementieren
	vec[used_fields - 1] = 0;
	used_fields--;
	//Wenn mehr als 2* EXTRA_LENGTH freie Felder, dann Vektor automatisch schrumpfen auf EXTRA_LENGTH Felder als Buffer
	if ((used_fields + 2 * EXTRA_LENGTH) <= length) {
		resize(used_fields + EXTRA_LENGTH);
	}
}

template<class T>
void vector<T>::pushback(T value) {
	//bei Bedarf Vekotr verl�ngern
	if (used_fields >= length) {
		resize(used_fields + EXTRA_LENGTH);
	}
	//Wert in das erste freie Feld des Vektors schreiben und physikalische L�nge anpassen
	vec[used_fields] = value;
	used_fields++;
}

template<class T>
int vector<T>::size() {
	//gibt physikalische L�nge zur�ck
	return used_fields;
}

template<class T>
T vector<T>::at(int pos) {
	//gibt Wert an pos zur�ck; falls pos nicht im Vektor wird NULL returned
	if (pos < used_fields) {
		return vec[pos];
	}
	return nullptr;
}

