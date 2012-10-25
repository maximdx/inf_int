#include <iostream>
#include "inf_int.h"
#include "stdlib.h"
#include <string.h>
#include <ctype.h>

inf_int::inf_int() : m_p_data(NULL), m_ul_digitCount(0UL), m_b_isPositive(false) {}

inf_int::~inf_int() {
	if(m_p_data != NULL)
		delete[] m_p_data;
}

inf_int::inf_int(const inf_int &rhs) : m_p_data(NULL) {
	__copyConstruct(rhs);
}

inline void
inf_int::__copyConstruct(const inf_int &rhs) {
	ULONG ul_digit = rhs.m_ul_digitCount;	
	rhs.m_b_isPositive ? ul_digit += 1 : ul_digit += 2;
	if(m_p_data != NULL) {
		delete[] m_p_data;
	}
	m_p_data = new char[ul_digit];
	if(m_p_data == NULL)
		throw "data allocation failure.";
	memset(m_p_data, 0, ul_digit);
	strcpy(m_p_data, rhs.m_p_data);
	m_b_isPositive = rhs.m_b_isPositive;
	m_ul_digitCount = rhs.m_ul_digitCount;
}

template<typename T>
inf_int::inf_int(T t_input) {
	long l_trans = __castToLong(t_input);
	__initialLong(l_trans);
}

template<>
inf_int::inf_int(const char* p_input) : m_p_data(NULL) {
	__initialCstring(p_input);
}

template inf_int::inf_int(short);
template inf_int::inf_int(int);
template inf_int::inf_int(long);
template inf_int::inf_int(unsigned short);
template inf_int::inf_int(unsigned int);
template inf_int::inf_int(unsigned long);
template inf_int::inf_int(float);
template inf_int::inf_int(double);
template inf_int::inf_int(const char *);

template<typename T>
inf_int& 
inf_int::operator=(const T &t_input) {
	long l_input = __castToLong(t_input);
	if(m_p_data != NULL)
		delete[] m_p_data;
	__initialLong(l_input);
	return *this;
}

/*
 * Dont know why this doesnt work
template<> inline
inf_int& inf_int::operator=<inf_int>(const inf_int &t_input) {
	copyConstruct(t_input);
	return *this;
}
*/

inf_int&
inf_int::operator=(const inf_int &ref_ifint) {
	__copyConstruct(ref_ifint);
	return *this;
}

inf_int&
inf_int::operator=(const char *p_input) {
	__initialCstring(p_input);
	return *this;
}

template inf_int& inf_int::operator=(const int&);
template inf_int& inf_int::operator=(const long&);
template inf_int& inf_int::operator=(const short&);
template inf_int& inf_int::operator=(const unsigned int&);
template inf_int& inf_int::operator=(const unsigned long&);
template inf_int& inf_int::operator=(const unsigned short&);
template inf_int& inf_int::operator=(const float&);
template inf_int& inf_int::operator=(const double&);

template<typename T>
inf_int
inf_int::operator+=(const T &t_input) {
	inf_int ifint(static_cast<long>(t_input));
	*this = *this + ifint;
	return *this;
}

inf_int
inf_int::operator+=(const char *p_input) {
	inf_int ifint(p_input);
	*this = *this + ifint;
	return *this;
}

inf_int
inf_int::operator+=(const inf_int &t_input) {
    *this = *this + t_input;
    return *this;
}

template inf_int inf_int::operator+=(const int&);
template inf_int inf_int::operator+=(const long&);
template inf_int inf_int::operator+=(const short&);
template inf_int inf_int::operator+=(const unsigned int&);
template inf_int inf_int::operator+=(const unsigned long&);
template inf_int inf_int::operator+=(const unsigned short&);
template inf_int inf_int::operator+=(const float&);
template inf_int inf_int::operator+=(const double&);

template<typename T>
inf_int
inf_int::operator-=(const T &t_input) {
	inf_int ifint(static_cast<long>(t_input));
	*this = *this - ifint;
	return *this;
}

inf_int
inf_int::operator-=(const char *p_input) {
	inf_int ifint(p_input);
	*this = *this - ifint;
	return *this;
}

inf_int
inf_int::operator-=(const inf_int &t_input) {
    *this = *this - t_input;
    return *this;
}

template inf_int inf_int::operator-=(const int&);
template inf_int inf_int::operator-=(const long&);
template inf_int inf_int::operator-=(const short&);
template inf_int inf_int::operator-=(const unsigned int&);
template inf_int inf_int::operator-=(const unsigned long&);
template inf_int inf_int::operator-=(const unsigned short&);
template inf_int inf_int::operator-=(const float&);
template inf_int inf_int::operator-=(const double&);

inf_int
inf_int::operator-() const {
	if(strcmp(m_p_data, "0") == 0) {
		inf_int ifint_return(0);
		return ifint_return;
	}
	size_t sz_allocate = strlen(m_p_data);
	if(m_b_isPositive) {
		sz_allocate += 2;
		char *p_data = new char[sz_allocate];
		if(p_data == NULL) {
			throw "data allocation failure.";
		}
		memset(p_data, 0, sz_allocate);
		memcpy(p_data+1, m_p_data, sz_allocate-1);
		p_data[0] = '-';
		inf_int ifint_return(static_cast<const char*>(p_data));
		delete[] p_data;
		return ifint_return;
	}
	else {
		char *p_data = new char[sz_allocate];
		if(p_data == NULL) {
			throw "data allocation failure.";
		}
		memset(p_data, 0, sz_allocate);
		memcpy(p_data, m_p_data+1, sz_allocate);
		inf_int ifint_return(static_cast<const char*>(p_data));
		delete[] p_data;
		return ifint_return;
	}
}


/*
 * Notes for all the operators ++ and -- :
 * The return type (inf_int) suggests that it returns a
 * copy of *this. This saves one time construction compared
 * with
 * 	return inf_int(*this);
 */
inf_int
inf_int::operator++() {
	//for ++ifint
	*this = *this + 1;
	return *this;
}


inf_int
inf_int::operator--() {
	//for ++ifint
	*this = *this - 1;
	return *this;
}

inf_int
inf_int::operator++(int flag) {
	*this = *this + 1;
	return *this;
}

inf_int
inf_int::operator--(int flag) {
	*this = *this - 1;
	return *this;
}

template<typename T> inline long 
inf_int::__castToLong(T t_input) {
	long l_return;	
	try {
		l_return = static_cast<long>(t_input);
	}
	catch(const char *exceptionMessage) {
		std::cerr << "convert failure: " << exceptionMessage << std::endl;
	}
	return l_return;
}

inline ULONG 
inf_int::__getPositiveDigits(ULONG ulNum) {
	ULONG ulDigits = 0;
	while(0 != ulNum) {
		++ulDigits;
		ulNum /= 10;
	}
	if(0 == ulDigits) {
		ulDigits = 1;
	}
	return ulDigits;
}

inline bool 
inf_int::__fillDataUlong(char *pData, ULONG ulSource, ULONG ulBegin) {
	if(0 == ulSource) {
		pData[ulBegin] = '0';
		return true;
	}
	while(0 != ulSource) {
		pData[ulBegin--] = static_cast<char>((ulSource%10)+48);
		ulSource /= 10;
	}
	return true;
}

void 
inf_int::__initialUlong(ULONG ulInput) {
	m_b_isPositive = true;
	m_ul_digitCount = __getPositiveDigits(ulInput);
	//one more for '\0'
	m_p_data = new char[m_ul_digitCount+1];
	if(m_p_data == NULL)
		throw "data allocation failure.";
	memset(m_p_data, 0, m_ul_digitCount+1);
	ULONG ulDigitCount = m_ul_digitCount;
	m_p_data[ulDigitCount--] = '\0';
	__fillDataUlong(m_p_data, ulInput, ulDigitCount);
}

void
inf_int::__initialLong(long lInput) {
	if(lInput >= 0) {
		__initialUlong(static_cast<ULONG>(lInput));
	}	
	else {
		m_b_isPositive = false;
		ULONG ulNum = static_cast<ULONG>(abs(lInput));	
		m_ul_digitCount = __getPositiveDigits(ulNum);
		//one more for '\0', one more for '-'
		m_p_data = new char[m_ul_digitCount+2];
		if(m_p_data == NULL)
			throw "data allocation failure.";
		memset(m_p_data, 0, m_ul_digitCount+2);
		ULONG ulBegin = m_ul_digitCount + 1;
		m_p_data[ulBegin--] = '\0';
		__fillDataUlong(m_p_data, ulNum, ulBegin);
		m_p_data[0] = '-';
	}
}

void
inf_int::__initialCstring(const char *p_input) {
	size_t sz_start = 0;
	size_t sz_length = strlen(p_input);
	if(p_input[0] == '-') {
		sz_start = 1;
	}
	for(size_t sz_i = sz_start; sz_i < sz_length; ++sz_i) {
		if(!isdigit(p_input[sz_i])) {
			//TODO: This error info should happen while compiling
			std::cerr << "cannot initialize type inf_int with " << p_input << std::endl;
			*this = 0;
			return;
		}
	}
	ULONG digitCount = 0;
	if(sz_start == 1) {
		digitCount = sz_length - 1;
		m_b_isPositive = false;
	}
	else {
		digitCount = sz_length;
		m_b_isPositive = true;
	}
	while(p_input[sz_start] == '0' && sz_start < sz_length) {
		++sz_start;
		--digitCount;
	}
	if(digitCount == 0) {
		*this = 0;
	}
	else{
		size_t sz_fill = 0;
		ULONG ul_allocate = 0;
		if(m_p_data != NULL)
			delete[] m_p_data;
		if(m_b_isPositive == false) {
			ul_allocate = digitCount+2;
		}
		else {
			ul_allocate = digitCount+1;
		}
		m_p_data = new char[ul_allocate];
		if(m_p_data == NULL)
			throw "allocation failure.";
		memset(static_cast<void*>(m_p_data), 0, ul_allocate);
		if(m_b_isPositive == false) {
			m_p_data[sz_fill] = '-';
			++sz_fill;
		}
		while(sz_start < sz_length) {
			m_p_data[sz_fill++] = p_input[sz_start++];
		}
		m_ul_digitCount = digitCount;
	}
}

void
inf_int::__push_back(char ch) {
    size_t sz_orig = strlen(m_p_data);
    //one for push back, one for '\0'
    char *p_new_data = new char[sz_orig+2];
    if(p_new_data == NULL) {
        throw "allocation failure.";
    }
    memcpy(static_cast<void*>(p_new_data),
           static_cast<void*>(m_p_data),
           sz_orig);
    p_new_data[sz_orig] = ch;
    p_new_data[sz_orig+1] = '\0';
    if(m_p_data != NULL) {
        delete[] m_p_data;
    }
    m_p_data = p_new_data;
    ++m_ul_digitCount;
}

void
inf_int::__trim() {
    UINT ui_begin = 0;
    size_t sz_orig = strlen(m_p_data);
    bool b_positive = true;
    if(m_p_data[0] == '-') {
        ui_begin = 1;
        b_positive = false;
    }
    while(m_p_data[ui_begin] == '0' && ui_begin < sz_orig-1) {
        ++ui_begin;
    }
    if((ui_begin == 0 && b_positive) || (ui_begin == 1 && !b_positive)) {
        return;
    }
    UINT ui_new_length = sz_orig - ui_begin + 1;
    UINT ui_copy_begin = 0;
    if(!b_positive) {
        ++ui_new_length;
        ++ui_copy_begin;
    }
    char* p_new_data = new char[ui_new_length];
    memcpy(static_cast<void*>(p_new_data+ui_copy_begin),
           static_cast<void*>(m_p_data+ui_begin),
           (sz_orig-ui_begin));
    p_new_data[ui_new_length-1] = '\0';
    if(!b_positive) {
        p_new_data[0] = '-';
    }
    if(m_p_data != NULL) {
        delete[] m_p_data;
    }
    m_p_data = p_new_data;
    m_ul_digitCount = sz_orig - ui_begin;
}

const char*
inf_int::c_str() const {
	return m_p_data;
}

int
inf_int::to_int() const {
	return atoi(m_p_data);
}


long
inf_int::to_long() const {
	return atol(m_p_data);
}

std::string 
inf_int::to_bin() const {
	using namespace std;
	string str_return;
    inf_int ifint_remian(*this);
    while(ifint_remian != 0) {
        inf_int binary_digit = ifint_remian % 2;
        ifint_remian = ifint_remian / 2;
        str_return.insert(0, 1, binary_digit.m_p_data[0]);
    }
	return str_return;
}
