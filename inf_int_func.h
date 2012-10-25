#ifndef INF_INT_FUNC_H
#define INF_INT_FUNC_H
#include "inf_int.h"

#define PROC_ATTITUDE 3

inf_int abs(const inf_int &ref_ifint);

std::ostream& operator<<(std::ostream &out, const inf_int &ifint);

std::istream& operator>>(std::istream &in, inf_int &ifint);

bool operator==(const inf_int &ref_ifint_lhs, const inf_int &ref_ifint_rhs);

bool operator!=(const inf_int &ref_ifint_lhs, const inf_int &ref_ifint_rhs);

bool operator>(const inf_int &ref_ifint_lhs, const inf_int &ref_ifint_rhs);

bool operator>=(const inf_int &ref_ifint_lhs, const inf_int &ref_ifint_rhs);

bool operator<(const inf_int &ref_ifint_lhs, const inf_int &ref_ifint_rhs);

bool operator<=(const inf_int &ref_ifint_lhs, const inf_int &ref_ifint_rhs);

inf_int operator+(const inf_int &ref_ifint_lsh, const inf_int &ref_ifint_rhs);

inf_int operator-(const inf_int &ref_ifint_lhs, const inf_int &ref_ifint_rhs);

inf_int operator*(const inf_int &ref_ifint_lhs, const inf_int &ref_ifint_rhs);

inf_int operator/(const inf_int &ref_ifint_lhs, const inf_int &ref_ifint_rhs);

inf_int operator%(const inf_int &ref_ifint_lhs, const inf_int &ref_ifint_rhs);

#endif
