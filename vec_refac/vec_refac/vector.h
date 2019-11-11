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
	void resize(int);						//verk�rzt Vektor auf �bergebene L�nge
	void popback();							//entfernt letztes Element
	void pushback(const T&);				//f�gt am Ende des Vektors �bergebenen Wert ein
	void clear();							//setzt alle ben�tzten Datenfelder des Vektors auf null
	int size() const;						//gibt L�nge des physikalischen Vektors zur�ck
	int capacity() const;
	T& at(unsigned long int) const;						//gibt Inhalt an �bergebener Stelle zur�ck
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

//gibt Wert/Inhalt an Position zur�ck
template<class T>
T& vector<T>::operator[](int pos) {
	if (pos < used_fields) {
		return vec[pos];
	}
	return vec[used_fields - 1];
}														// SOLL DAS ZWEIMAL DRIN SEIN!!!??? JA
//gibt Wert/Inhalt an Position zur�ck
template<class T>
const T& vector<T>::operator[](int pos) const {
	if (pos < used_fields) {
		return vec[pos];
	}
	//Wir wollen das so!!!!!!!!!
	return vec[used_fields - 1];
}
//�berladung des Vergleichsoperators
template<class T>
vector<T>& vector<T>::operator=(const vector& copy1) {
	used_fields = copy1.size();
	length = copy1.capacity();
	this->resize(length);
	//Kopieren des Vektors
	std::copy(&copy1.at(0), &copy1.at(copy1.size()), &vec[0]);
	//Referenz auf das aktuelle Objekt zur�ckliefern
	return *this;
}


//Inhalt der benutzten Felder wird gel�scht
template<class T>
void vector<T>::clear() {
	used_fields = 0;
}

template<class T>
void vector<T>::resize(int nu_length) {
	if (nu_length != length) {
		//�bergebene L�nge entspricht nicht der bereits Vorhandenen
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
			//Vektor wurde so gek�rzt, dass Daten verloren gegangen sind -> Nutzdatenl�nge anpassen
			used_fields = nu_length;
		}
		// Gesamtl�nge des Vektors anpassen und alten Vektor l�schen
		length = nu_length;
		//Zeiger auf neuen Vektor umbiegen
		
		vec = std::move(nu_vec);	//Operator �berladen Problem?
	}
}

template<class T>
void vector<T>::popback() {
	//letzteS Element nullen und physikalische L�nge decrementieren
	used_fields--;
	//Wenn mehr als 2* EXTRA_LENGTH freie Felder, dann Vektor automatisch schrumpfen auf EXTRA_LENGTH Felder als Buffer
	/*if ((used_fields + 2 * EXTRA_LENGTH) <= length) {
		resize(used_fields + EXTRA_LENGTH);
	}*/
}

template<class T>
void vector<T>::pushback(const T& value) {
	//bei Bedarf Vekotr verl�ngern
	if (used_fields >= length) {
		resize(int(1.3 * length));
	}
	//Wert in das erste freie Feld des Vektors schreiben und physikalische L�nge anpassen
	vec[used_fields] = value;
	used_fields++;
}

//gibt Gr��e des Vektors zur�ck
template<class T>
int vector<T>::size() const {
	return used_fields;
}
//gibt die Gesamtkapazit�t des Vektors zur�ck 
template<class T>
int vector<T>::capacity() const {
	return length;
}
//WIR BRAUCHEN GRO?ES ZAHL LONG DONG SILVER
template<class T>
T& vector<T>::at(unsigned long int pos) const {
	//gibt Wert an pos zur�ck; falls pos nicht im Vektor wird NULL returned
	if (pos == 0) {
		return vec[0];
	} 
	else if (pos < used_fields) {
		return vec[pos-1];
	}
	//Wir wollen das so!!!!!!!!!
	return vec[used_fields - 1];
}

