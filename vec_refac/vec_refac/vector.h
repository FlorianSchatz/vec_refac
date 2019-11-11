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
	if(used_fields) std::copy(&copy1.at(1), &copy1.at(copy1.size()), &vec[0]);
}

template<class T>
vector<T>::vector(unsigned long int size) : length(size)  {
	//constructor: creates unique_ptr to vec with given size
	vec = std::make_unique<T[]>(size);
}

template<class T>
T& vector<T>::operator[](unsigned long int pos) {
	if (pos < used_fields) {
		//pos in bounds of vec
		return vec[pos];
	}
	else if (pos >= used_fields) {
		throw std::out_of_range("Out of range");
	}
}

template<class T>
const T& vector<T>::operator[](unsigned long int pos) const {
	if (pos < used_fields) {
		return vec[pos];
	}
	else if (pos >= used_fields) {
		throw std::out_of_range("out of range");
	}
}

template<class T>
vector<T>& vector<T>::operator=(const vector& copy1) {
	used_fields = copy1.size();
	length = copy1.capacity();
	//adjust length of this vec
	this->resize(length);
	//copy all data to this vec
	if(used_fields) std::copy(&copy1.at(1), &copy1.at(copy1.size()), &vec[0]);
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
		if(used_fields) std::copy(&(this->at(1)), nu_length > length ? &this->at(used_fields) : &this->at(nu_length), &nu_vec[0]);	//FIX!!!
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
		unsigned long int nu_length = 1.3 * length;
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
		// return bla
		//issue: no return possible, but one is needed (warning)
	} 
	else if (pos <= used_fields) {
		//normal case: no boundaries crossed
		return vec[pos-1];
	}
}