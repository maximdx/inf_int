#ifndef INF_INT_H
#define INF_INT_H

#include <iostream>

typedef unsigned long ULONG;
typedef unsigned int  UINT;

class inf_int {
	friend std::istream& operator>>(std::istream &in, inf_int &ifint);
    friend inf_int __divide(const inf_int &lhs, const inf_int &rhs);
    friend bool operator>(const inf_int &lhs, const inf_int &rhs);
public:
	inf_int();
	inf_int(const inf_int &rhs);
	template <typename T> inf_int(T anyValidType);
	~inf_int();
	
	template <typename T> inf_int& operator=(const T &anyValidTypeRef);
	inf_int& operator=(const inf_int &ifType);
	inf_int& operator=(const char *p_input);
	inf_int operator-() const;
	inf_int operator++();	//for ++ifint
	inf_int operator++(int);//for ifint++
	inf_int operator--();
	inf_int operator--(int);
	template <typename T> inf_int operator+=(const T &anyValidTypeRef);
	inf_int operator+=(const char *p_input);
    inf_int operator+=(const inf_int &t_input);
	template <typename T> inf_int operator-=(const T &anyValidTypeRef);
	inf_int operator-=(const char *p_input);
    inf_int operator-=(const inf_int &t_input);

	const char* c_str() const;
	int to_int() const;
	long to_long() const;
	std::string to_bin() const;
private:
	ULONG __getPositiveDigits(ULONG ulNum);
	//ULONG __getPositiveDigits(char *csNum);
	bool __fillDataUlong(char *pData, ULONG ulSource, ULONG ulBegin);
	void __initialLong(long l_input);
	void __initialUlong(ULONG ul_input);
	void __initialCstring(const char *p_input);
	template <typename T> long __castToLong(T anyValidType);
	void __copyConstruct(const inf_int &rhs);
    void __push_back(char ch);
    void __trim();
private:
	char *m_p_data;
	ULONG m_ul_digitCount;
	bool m_b_isPositive;
};

#include "inf_int_func.h"

#endif
