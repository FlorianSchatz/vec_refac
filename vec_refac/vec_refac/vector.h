#pragma once
#include <algorithm>
#include <memory>

template <class T>
class vector
{
private:
	std::unique_ptr<T[]> vec;					//unique ptr to vector
	unsigned long int used_fields;				//number of used elements of the vector
	unsigned long int length;					//real length of the vector
public:
	vector(unsigned long int);					//constructor
	vector(const vector&);						//Copy-constructor
	~vector() {};								//destructor
	void resize(unsigned long int);				//resizes vec to given length
	void popback();								//deletes last element
	void pushback(const T&);					//adds element with given value
	void clear();								//clears vec
	unsigned long int size() const;				//returns num of used elements
	unsigned long int capacity() const;			//returns capacity
	T& at(unsigned long int) const;				//returns value at pos
	vector<T>& operator= (const vector& copy);	//overload = operator (deep copy)
	T& operator[] (unsigned long int);			//overload []operators
	const T& operator[] (unsigned long int) const;
};

template<class T>
vector<T>::vector(const vector& copy1) {
	//copy constructor: copies all elements of given vector copy1 to new vector
	used_fields = copy1.size();
	length = copy1.capacity();
	vec = std::make_unique<T[]>(length);
	//if(used_fields) std::copy(&copy1.at(1), &copy1.at(copy1.size()), &vec[0]);
	if (used_fields) {
		for (unsigned long int i = 0; i < length; i++) {
			if (i < used_fields) {
				vec[i] = copy1[i];
			}
		}
	}
}

template<class T>
vector<T>::vector(unsigned long int size) : length(size)  {
	//constructor: creates unique_ptr to vec with given size
	vec = std::make_unique<T[]>(size);
}

template<class T>
T& vector<T>::operator[](unsigned long int pos) {
	if (pos >= used_fields) {
		throw std::out_of_range("Out of range");
	}
	return vec[pos];
}

template<class T>
const T& vector<T>::operator[](unsigned long int pos) const {
	if (pos >= used_fields) {
		throw std::out_of_range("out of range");
	}
	return vec[pos];
}

template<class T>
vector<T>& vector<T>::operator=(const vector& copy1) {
	//this->clear();
	used_fields = copy1.size();
	//length = copy1.capacity();
	//adjust length of this vec
	this->resize(copy1.capacity());
	//copy all data to this vec
	//if(used_fields) std::copy(&copy1.at(1), &copy1.at(copy1.size()), &vec[0]);
	if (used_fields) {
		for (unsigned long int i = 0; i < length; i++) {
			if (i < used_fields) {
				vec[i] = copy1[i];
			}
		}
	}

	return *this;
}

template<class T>
void vector<T>::clear() {
	//makes all fields of vec free to overwrite
	used_fields = 0;
}

template<class T>
void vector<T>::resize(unsigned long int nu_length) {
	if (nu_length != length) {
		//create new vec using unique_ptr
		std::unique_ptr<T[]> nu_vec = std::make_unique<T[]>(nu_length);
		//copy all relevant data to new vec
		//T* end = (nu_length > length) ? &this->at(used_fields) : &this->at(nu_length);
		//if(used_fields > 0) std::copy(&(this->at(1)), end, &nu_vec[0]);	//FIX!!!
		if (used_fields) {
			for (unsigned long int i = 0; i < nu_length; i++) {
				if (i < used_fields) {
					nu_vec[i] = vec[i];
				}
			}
		}
		if (nu_length < used_fields) {
			//adjust used_fields when vec has been shortened
			used_fields = nu_length;
		}
		length = nu_length;
		//make nu_vec be owned by vec (automatically deletes data vec has been pointing at till this moment)
		vec = std::move(nu_vec);  //move constructor needed?
	}
}

template<class T>
void vector<T>::popback() {
	if (used_fields > 0) used_fields--;
}

template<class T>
void vector<T>::pushback(const T& value) {
	if (used_fields >= length) {
		//no remaining free fields, thus resize vec
		unsigned long int nu_length = (unsigned long int)round(1.3 * length); 
		resize(nu_length);
	}
	vec[used_fields] = value;
	used_fields++;
}

template<class T>
unsigned long int vector<T>::size() const {
	return used_fields;
}
 
template<class T>
unsigned long int vector<T>::capacity() const {
	return length;
}

template<class T>
T& vector<T>::at(unsigned long int pos) const {
	//boundaries check
	if (pos == 0 || pos > used_fields) {
		throw std::out_of_range ("out of range");
	}
	return vec[pos - 1];
}