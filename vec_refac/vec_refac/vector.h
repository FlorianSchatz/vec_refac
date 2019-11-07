#pragma once
#include <algorithm>
#include <memory>

template <class T>
class vector
{
private:
	std::unique_ptr<T> vec;		//"Start"Vektor
	int used_fields;		// number of used elemnts of the vector
	int length;			//real length of the vector
public:
	vector(int);
	vector(const vector&);
	~vector();
	void resize(int);			//verk�rzt Vektor auf �bergebene L�nge
	void popback();				//entfernt letztes Element
	void pushback(const T&);			//f�gt am Ende des Vektors �bergebenen Wert ein
	void clear();				//setzt alle ben�tzten Datenfelder des Vektors auf null
	int size() const;			//gibt L�nge des physikalischen Vektors zur�ck
	int capacity() const;
	T* at(int) const;					//gibt Inhalt an �bergebener Stelle zur�ck
	T& operator= (const vector&);
	T& operator[] (int);
	const T& operator[] (int) const;
};

template<class T>
vector<T>::vector(const vector& copy) {
	used_fields = copy->size();
	length = copy->capacity();
	vec = std::make_unique<T[]>(length);
	std::copy(std::begin(copy), copy+copy->size() , std::begin(vec));
}

template<class T>
vector<T>::vector(int size) : length(size)  {
	vec = std::make_unique<T[]>(size);
}

template<class T>
vector<T>::~vector() {
	
}

template<class T>
T& vector<T>::operator[](int pos) {
	return at(pos);
}

template<class T>
const T& vector<T>::operator[](int pos) const {
	return at(pos);
}

template<class T>
T& vector<T>::operator=(const vector& copy) {
	used_fields = copy.size();
	length = copy.capacity();
	vec.resize(length);
	std::copy(std::begin(copy), std::begin(copy)+used_fields, std::begin(vec));
}



template<class T>
void vector<T>::clear() {
	used_fields = 0;
}

template<class T>
void vector<T>::resize(int nu_length) {
	if (nu_length != length) {
		//�bergebene L�nge entspricht nicht der bereits Vorhandenen
		//neues Array allozieren
		std::unique_ptr<T> nu_vec = std::make_unique<T[]>(nu_length);
		/*for (int i = 0; i < length; i++) {
			if (i < nu_length) {
				//Elementweise kopieren
				nu_vector[i] = vec[i];
			}
			}
			*/
		std::copy(std::begin(vec), (nu_length > length ? std::end(vec) : vec+nu_length), std::begin(nu_vec));
		
		if (nu_length < used_fields) {
			//Vektor wurde so gek�rzt, dass Daten verloren gegangen sind -> Nutzdatenl�nge anpassen
			used_fields = nu_length;
		}
		// Gesamtl�nge des Vektors anpassen und alten Vektor l�schen
		length = nu_length;
		//Zeiger auf neuen Vektor umbiegen
		
		vec = nu_vec;	//Operator �berladen Problem?
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

template<class T>
int vector<T>::size() const {
	return used_fields;
}

template<class T>
int vector<T>::capacity() const {
	return length;
}

template<class T>
T* vector<T>::at(int pos) const {
	//gibt Wert an pos zur�ck; falls pos nicht im Vektor wird NULL returned
	if (pos < used_fields) {
		return vec[pos];
	}
	return NULL;
}

