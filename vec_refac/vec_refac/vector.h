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
	void resize(int);			//verkürzt Vektor auf übergebene Länge
	void popback();				//entfernt letztes Element
	void pushback(T);			//fügt am Ende des Vektors übergebenen Wert ein
	void clear();				//setzt alle benützten Datenfelder des Vektors auf null
	int size();					//gibt Länge des physikalischen Vektors zurück
	T& at(int);					//gibt Inhalt an übergebener Stelle zurück
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
	//Vektor auf Bufferlänge kürzen
	resize(EXTRA_LENGTH);
	used_fields = 0;
}

template<class T>
void vector<T>::resize(int nu_length) {
	if (nu_length != length) {
		//Übergebene Länge entspricht nicht der bereits Vorhandenen
		//neues Array allozieren
		T* nu_vector = new T[nu_length];
		for (int i = 0; i < length; i++) {
			if (i < nu_length) {
				//Elementweise kopieren
				nu_vector[i] = vec[i];
			}
		}
		if (nu_length < used_fields) {
			//Vektor wurde so gekürzt, dass Daten verloren gegangen sind -> Nutzdatenlänge anpassen
			used_fields = nu_length;
		}
		// Gesamtlänge des Vektors anpassen und alten Vektor löschen
		length = nu_length;
		delete[] vec;
		//Zeiger auf neuen Vektor umbiegen
		vec = nu_vector;
	}
}

template<class T>
void vector<T>::popback() {
	//letzteS Element nullen und physikalische Länge decrementieren
	vec[used_fields - 1] = 0;
	used_fields--;
	//Wenn mehr als 2* EXTRA_LENGTH freie Felder, dann Vektor automatisch schrumpfen auf EXTRA_LENGTH Felder als Buffer
	if ((used_fields + 2 * EXTRA_LENGTH) <= length) {
		resize(used_fields + EXTRA_LENGTH);
	}
}

template<class T>
void vector<T>::pushback(T value) {
	//bei Bedarf Vekotr verlängern
	if (used_fields >= length) {
		resize(used_fields + EXTRA_LENGTH);
	}
	//Wert in das erste freie Feld des Vektors schreiben und physikalische Länge anpassen
	vec[used_fields] = value;
	used_fields++;
}

template<class T>
int vector<T>::size() {
	//gibt physikalische Länge zurück
	return used_fields;
}

template<class T>
T vector<T>::at(int pos) {
	//gibt Wert an pos zurück; falls pos nicht im Vektor wird NULL returned
	if (pos < used_fields) {
		return vec[pos];
	}
	return nullptr;
}

