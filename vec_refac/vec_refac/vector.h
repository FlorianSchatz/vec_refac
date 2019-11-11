#pragma once
#include <algorithm>
#include <memory>

template <class T>
class vector
{
private:
	std::unique_ptr<T[]> vec;					//"Start"Vektor
	int used_fields;						// number of used elemnts of the vector
	int length;								//real length of the vector
public:
	vector(int);
	vector(const vector&);
	~vector();								//Destruktoer
	void resize(int);						//verkürzt Vektor auf übergebene Länge
	void popback();							//entfernt letztes Element
	void pushback(const T&);				//fügt am Ende des Vektors übergebenen Wert ein
	void clear();							//setzt alle benützten Datenfelder des Vektors auf null
	int size() const;						//gibt Länge des physikalischen Vektors zurück
	int capacity() const;
	T& at(unsigned long int) const;						//gibt Inhalt an übergebener Stelle zurück
	vector<T>& operator= (const vector& copy);
	T& operator[] (int);
	const T& operator[] (int) const;
};
//Kopierkonstruktor
template<class T>
vector<T>::vector(const vector& copy1) {
	used_fields = copy1.size();
	length = copy1.capacity();
	vec = std::make_unique<T[]>(length);
	std::copy(&copy1.at(0), &copy1.at(copy1.size()) ,	&vec[0]);
}
//Konstruktor erzeugt Unique Ponter (Smart Pointer) auf Vektor
template<class T>
vector<T>::vector(int size) : length(size)  {
	vec = std::make_unique<T[]>(size);
}
//Destruktor
template<class T>
vector<T>::~vector() {
	
}

//gibt Wert/Inhalt an Position zurück
template<class T>
T& vector<T>::operator[](int pos) {
	if (pos < used_fields) {
		return vec[pos];
	}
	return vec[used_fields - 1];
}														// SOLL DAS ZWEIMAL DRIN SEIN!!!??? JA
//gibt Wert/Inhalt an Position zurück
template<class T>
const T& vector<T>::operator[](int pos) const {
	if (pos < used_fields) {
		return vec[pos];
	}
	//Wir wollen das so!!!!!!!!!
	return vec[used_fields - 1];
}
//Überladung des Vergleichsoperators
template<class T>
vector<T>& vector<T>::operator=(const vector& copy1) {
	used_fields = copy1.size();
	length = copy1.capacity();
	this->resize(length);
	//Kopieren des Vektors
	std::copy(&copy1.at(0), &copy1.at(copy1.size()), &vec[0]);
	//Referenz auf das aktuelle Objekt zurückliefern
	return *this;
}


//Inhalt der benutzten Felder wird gelöscht
template<class T>
void vector<T>::clear() {
	used_fields = 0;
}

template<class T>
void vector<T>::resize(int nu_length) {
	if (nu_length != length) {
		//Übergebene Länge entspricht nicht der bereits Vorhandenen
		//neues Array allozieren
		std::unique_ptr<T[]> nu_vec = std::make_unique<T[]>(nu_length);
		/*for (int i = 0; i < length; i++) {
			if (i < nu_length) {
				//Elementweise kopieren
				nu_vector[i] = vec[i];
			}
			}
			*/
		T* end = (nu_length > length ? &this->at(used_fields) : &this->at(nu_length));
		std::copy(&(this->at(0)), end, &nu_vec[0]);		
		if (nu_length < used_fields) {
			//Vektor wurde so gekürzt, dass Daten verloren gegangen sind -> Nutzdatenlänge anpassen
			used_fields = nu_length;
		}
		// Gesamtlänge des Vektors anpassen und alten Vektor löschen
		length = nu_length;
		//Zeiger auf neuen Vektor umbiegen
		
		vec = std::move(nu_vec);	//Operator überladen Problem?
	}
}

template<class T>
void vector<T>::popback() {
	//letzteS Element nullen und physikalische Länge decrementieren
	used_fields--;
	//Wenn mehr als 2* EXTRA_LENGTH freie Felder, dann Vektor automatisch schrumpfen auf EXTRA_LENGTH Felder als Buffer
	/*if ((used_fields + 2 * EXTRA_LENGTH) <= length) {
		resize(used_fields + EXTRA_LENGTH);
	}*/
}

template<class T>
void vector<T>::pushback(const T& value) {
	//bei Bedarf Vekotr verlängern
	if (used_fields >= length) {
		resize(int(1.3 * length));
	}
	//Wert in das erste freie Feld des Vektors schreiben und physikalische Länge anpassen
	vec[used_fields] = value;
	used_fields++;
}

//gibt Größe des Vektors zurück
template<class T>
int vector<T>::size() const {
	return used_fields;
}
//gibt die Gesamtkapazität des Vektors zurück 
template<class T>
int vector<T>::capacity() const {
	return length;
}
//WIR BRAUCHEN GRO?ES ZAHL LONG DONG SILVER
template<class T>
T& vector<T>::at(unsigned long int pos) const {
	//gibt Wert an pos zurück; falls pos nicht im Vektor wird NULL returned
	if (pos == 0) {
		return vec[0];
	} 
	else if (pos < used_fields) {
		return vec[pos-1];
	}
	//Wir wollen das so!!!!!!!!!
	return vec[used_fields - 1];
}

