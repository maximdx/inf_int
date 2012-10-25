#include "inf_int_func.h"
#include <ctype.h>
#include <string.h>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const inf_int &ifint) {
    out << ifint.c_str();
    return out;
}

istream& operator>>(istream &in, inf_int &ifint) {
    string str_storage;
    in >> str_storage;
    ifint = str_storage.c_str();
    return in;
}


bool operator==(const inf_int &ref_ifint_lhs, const inf_int &ref_ifint_rhs) {
    if(strcmp(ref_ifint_lhs.c_str(), ref_ifint_rhs.c_str()) == 0) {
        return true;
    }
    else {
        return false;
    }
}


bool operator!=(const inf_int &ref_ifint_lhs, const inf_int &ref_ifint_rhs) {
    if(strcmp(ref_ifint_lhs.c_str(), ref_ifint_rhs.c_str()) != 0) {
        return true;
    }
    else {
        return false;
    }
}

bool __is_positive(const inf_int &ref) {
    const char *p_data = ref.c_str();
    if(p_data[0] == '-') {
        return false;
    }
    else {
        return true;
    }
}

/*
 * return value of __is_abs_greater_than:
 *  1: lhs > rhs
 *  0: lhs == rhs
 * -1: lhs < rhs
 */
int __is_abs_greater_than(const inf_int &lhs, const inf_int &rhs) {
    inf_int abs_lhs(abs(lhs));
    inf_int abs_rhs(abs(rhs));
    size_t sz_abs_lhs = strlen(abs_lhs.c_str()); 
    size_t sz_abs_rhs = strlen(abs_rhs.c_str());
    if(sz_abs_lhs > sz_abs_rhs) {
        return 1;
    }
    else if(sz_abs_lhs < sz_abs_rhs) {
        return -1;
    }
    else {
        size_t sz_pos = 0;
        const char *p_lhs_data = abs_lhs.c_str();
        const char *p_rhs_data = abs_rhs.c_str();
        while(sz_pos <= sz_abs_lhs) {
            if(p_lhs_data[sz_pos] > p_rhs_data[sz_pos]) {
                return 1;
            }
            else if (p_lhs_data[sz_pos] < p_rhs_data[sz_pos]) {
                return -1;
            }
            else {
                ++sz_pos;
            }
        }
        return 0;
    }
}

//Add two inf_int parameters whose sign symbol is similar
//Note that lhs and rhs MUST BE both positive or negative
inf_int __add(const inf_int &lhs, const inf_int &rhs) {
    const char *p_lhs = lhs.c_str();
    const char *p_rhs = rhs.c_str();
    int i_lhs_length = strlen(p_lhs);
    int i_rhs_length = strlen(p_rhs);
    int i_ending = 0;
    bool b_lhs_positive = __is_positive(lhs);
    bool b_rhs_positive = __is_positive(rhs);
    //lhs and rhs MUST have the same sign symbol
    if(b_lhs_positive != b_rhs_positive) {
        throw "__add called incorrectly.";
    }
    if(!b_lhs_positive) {
        i_ending = 1;
    }
    int i_lhs_pos = i_lhs_length - 1;
    int i_rhs_pos = i_rhs_length - 1;
    int i_carry = 0;
    string str_build;
    //Iteration for doing adding work
    while(i_lhs_pos >= i_ending && i_rhs_pos >= i_ending) {
        int i_digit = (p_lhs[i_lhs_pos--]-48) + (p_rhs[i_rhs_pos--]-48) + i_carry;
        if(i_digit > 9) {
            i_carry = 1;
        }
        else {
            i_carry = 0;
        }
        i_digit %= 10;
        str_build.insert(0, 1, static_cast<char>(i_digit+48));
    }
    if(i_rhs_pos >= i_ending) {
        p_lhs = rhs.c_str();
        i_lhs_pos = i_rhs_pos;
    }
    while(i_lhs_pos >= i_ending) {
        int i_digit = (p_lhs[i_lhs_pos--]-48) + i_carry;
        if(i_digit > 9) {
            i_carry = 1;
        }
        else {
            i_carry = 0;
        }
        i_digit %= 10;
        str_build.insert(0, 1, static_cast<char>(i_digit+48));
    }
    if(i_carry == 1) {
        str_build.insert(0, 1, static_cast<char>(i_carry+48));
    }
    if(!b_lhs_positive) {
        str_build.insert(0, 1, '-');
    }
    inf_int ifint_return(str_build.c_str());
    return ifint_return;
}

//Subtract rhs from lhs (lhs - rhs)
//Note that lhs MUST BE positive and rhs MUST BE negative
inf_int __sub(const inf_int &lhs, const inf_int &rhs) {
    const char *p_lhs = lhs.c_str();	
    const char *p_rhs = rhs.c_str();
    int i_lhs_length = strlen(p_lhs);
    int i_rhs_length = strlen(p_rhs);
    int i_lhs_ending = 0;
    int i_rhs_ending = 1;
    int i_carry = 0;
    int i_lhs_pos = i_lhs_length - 1;	
    int i_rhs_pos = i_rhs_length - 1;
    bool b_positive;
    string str_build;
    if(__is_abs_greater_than(rhs, lhs) == 1) {
        p_lhs = rhs.c_str();
        p_rhs = lhs.c_str();
        int i_tmp = i_lhs_pos;
        i_lhs_pos = i_rhs_pos;
        i_rhs_pos = i_tmp;
        i_tmp = i_lhs_ending;
        i_lhs_ending = i_rhs_ending;
        i_rhs_ending = i_tmp;
        b_positive = false;
    }
    else {
        b_positive = true;
    }
    while(i_lhs_pos > i_lhs_ending && i_rhs_pos > i_rhs_ending) {
        int i_digit = (p_lhs[i_lhs_pos--]-48) - i_carry - (p_rhs[i_rhs_pos--]-48);
        if(i_digit < 0) {
            i_carry = 1;
            i_digit += 10;
        }
        else {
            i_carry = 0;
        }
        str_build.insert(0, 1, static_cast<char>(i_digit+48));
    }
    if(i_lhs_pos == i_lhs_ending && i_rhs_pos == i_rhs_ending) {
        int i_digit = (p_lhs[i_lhs_pos]-48) - i_carry - (p_rhs[i_rhs_pos]-48);
        str_build.insert(0, 1, static_cast<char>(abs(i_digit)+48));
        if(!b_positive) {
            str_build.insert(0, 1, '-');
        }
    }
    else {
        int i_digit = (p_lhs[i_lhs_pos--]-48) - i_carry - (p_rhs[i_rhs_pos]-48);
        if(i_digit < 0) {
            i_carry = 1;
            i_digit += 10;
        }
        else {
            i_carry = 0;
        }
        str_build.insert(0, 1, static_cast<char>(i_digit+48));
        while(i_lhs_pos >= i_lhs_ending) {
            int i_digit = (p_lhs[i_lhs_pos--]-48) - i_carry;
            if(i_digit < 0) {
                i_carry = 1;
                i_digit += 10;
            }
            else {
                i_carry = 0;
            }
            str_build.insert(0, 1, static_cast<char>(i_digit+48));
        }
        if(!b_positive) {
            str_build.insert(0, 1, '-');
        }
    }
    //chop nonsense 0s
    size_t sz_start = 0;
    if(!b_positive) {
        sz_start = 1;
    }
    while(sz_start < str_build.length()-1) {
        if(str_build[sz_start] == '0') {
            str_build.erase(sz_start, 1);
        }
        else {
            break;
        }
    }
    inf_int ifint_return(str_build.c_str());
    return ifint_return;
}

inf_int __multiply(const inf_int &lhs, const inf_int &rhs) {
    bool b_positive = !(__is_positive(lhs) ^ __is_positive(rhs));
    inf_int abs_lhs(abs(lhs));
    inf_int abs_rhs(abs(rhs));
    vector<inf_int> vec_ifint_values;
    inf_int *p_left;
    inf_int *p_right;
    if(strlen(abs_lhs.c_str()) < strlen(abs_rhs.c_str())) {
        p_left = &abs_rhs;
        p_right = &abs_lhs;
    }
    else {
        p_left = &abs_lhs;
        p_right = &abs_rhs;
    }
    string str_multiplicator(p_right->c_str()); 
    for(UINT i = 0; i < str_multiplicator.length(); ++i) {
        string str_base(p_left->c_str());
        //Generate the base (x1) of every digit
        for(UINT j = 0; j < str_multiplicator.length()-i-1; ++j) {
            str_base.push_back('0');
        }
        inf_int ifint_base(str_base.c_str());
        UINT ui_times = static_cast<UINT>(str_multiplicator[i]-48);
        inf_int ifint_digit(0);
        for(UINT j = 0; j < ui_times; ++j) {
            ifint_digit += ifint_base;
        }
        vec_ifint_values.push_back(ifint_digit);
    }
    inf_int ifint_return(0);
    for(UINT i = 0; i < vec_ifint_values.size(); ++i) {
        ifint_return += vec_ifint_values[i];
    }
    if(!b_positive) {
        ifint_return = -ifint_return;
    }
    return ifint_return;
}

inf_int divide_by_int(const inf_int &infint_lhs, int i_rhs) {
    if(i_rhs == 0) {
        inf_int ifint_return(0);
        return ifint_return;
    }
    bool b_positive = !(__is_positive(infint_lhs) ^ (i_rhs<0?false:true));
    if(i_rhs < 0) {
        i_rhs = abs(i_rhs);
    }
    string str_lhs(abs(infint_lhs).c_str());
    string str_result;
    string str_candidate;
    UINT ui_pos = 0;
    while(ui_pos < str_lhs.size()) {
        str_candidate.push_back(str_lhs[ui_pos++]);
        int i_left = atoi(str_candidate.c_str());
        if(i_left >= i_rhs) {
            str_result.push_back(static_cast<char>(i_left/i_rhs+48));
            int i_remainder = i_left % i_rhs;
            char rmd_buf[32];
            memset(rmd_buf, 0, 32);
            sprintf(rmd_buf, "%d", i_remainder);
            str_candidate = rmd_buf;
        }
        else {
            str_result.push_back('0');
        }
    }
    ui_pos = 0;
    while(ui_pos < str_result.length()-1) {
        if(str_result[ui_pos] == '0') {
            str_result.erase(ui_pos, 1);
            ++ui_pos;
        }
        else {
            break;
        }
    }
    inf_int ifint_return(str_result.c_str());
    if(!b_positive) {
        ifint_return = -ifint_return;
    }
    return ifint_return;
}

inf_int __divide(const inf_int &lhs, const inf_int &rhs) {
    inf_int ifint_return(0);
    if(lhs == 0) {
        return ifint_return;
    }
    if(rhs == 0) {
        throw "divisor cannot be ZERO.";
    }
    inf_int abs_lhs(abs(lhs));
    inf_int abs_rhs(abs(rhs));
    if(abs_rhs > abs_lhs) {
        return ifint_return;
    }
    string str_rhs(abs_rhs.c_str());
    string str_lhs(abs_lhs.c_str());
    UINT ui_begin = str_rhs.size();
    inf_int ifint_remain(str_lhs.substr(0, str_rhs.size()).c_str());
    while(ui_begin <= str_lhs.size()) {
        if(ifint_remain < abs_rhs) {
            ifint_remain.__push_back(str_lhs[ui_begin++]);
            ifint_remain.__trim();
            ifint_return.__push_back('0');
        }
        else {
            UINT ui_digit = 0;
            while(ifint_remain >= abs_rhs) {
                ifint_remain -= abs_rhs;
                ++ui_digit;
            }
            ifint_return.__push_back(static_cast<char>(ui_digit+48));
            if(ui_begin < str_lhs.size()) {
                ifint_remain.__push_back(str_lhs[ui_begin++]);
                ifint_remain.__trim();
            }
            else {
                ++ui_begin;
            }
        }
    }
    ifint_return.__trim();
    if(lhs < 0 && rhs > 0) {
        ifint_return = -ifint_return;
    }
    return ifint_return;
}

inf_int __mod(const inf_int &lhs, const inf_int &rhs) {
    inf_int ifint_return(0);
    bool b_lhs_positive = __is_positive(lhs);
    bool b_rhs_positive = __is_positive(rhs);
    inf_int abs_lhs(abs(lhs));
    inf_int abs_rhs(abs(rhs));
    if(abs_rhs > abs_lhs) {
        ifint_return = lhs;
        return ifint_return;
    }
    if(abs_rhs == abs_lhs) {
        return ifint_return;
    }
    inf_int quotient = abs_lhs / abs_rhs;
    ifint_return = abs_lhs - (quotient * abs_rhs);
    if(!b_lhs_positive && b_rhs_positive) {
        ifint_return = -ifint_return;
    }
    return ifint_return;
}

inf_int abs(const inf_int &ref_ifint) {
    bool b_is_positive = __is_positive(ref_ifint);
    if(!b_is_positive) {
        inf_int ifint_return(-ref_ifint);
        return ifint_return;
    }	
    else {
        inf_int ifint_return(ref_ifint);
        return ifint_return;
    }
}

bool operator>(const inf_int &lhs, const inf_int &rhs) {
    if(lhs == rhs || (lhs == 0 && rhs == 0)) {
        return false;
    }
    bool b_lhs_positive = __is_positive(lhs);	
    bool b_rhs_positive = __is_positive(rhs);	
    bool b_result;
	if(b_lhs_positive && !b_rhs_positive) {
		return true;
	}
	else if(!b_lhs_positive && b_rhs_positive) {
		return false;
	}
	else {
        inf_int abs_lhs(abs(lhs));
        inf_int abs_rhs(abs(rhs));
        if(abs_lhs.m_ul_digitCount > abs_rhs.m_ul_digitCount) {
            b_result = true;
        }
        else if(abs_lhs.m_ul_digitCount < abs_rhs.m_ul_digitCount) {
            b_result = false;
        }
        else {
            if(strcmp(abs_lhs.m_p_data, abs_rhs.m_p_data) > 0) {
                b_result = true;
            }
            else {
                b_result = false;
            }
        }
	}
    if(!b_lhs_positive && !b_rhs_positive) {
        return !b_result;
    }
    else {
        return b_result;
    }
}

bool operator<(const inf_int &lhs, const inf_int &rhs) {
	if(lhs > rhs || lhs == rhs) {
		return false;
	}
	else {
		return true;
	}
}

bool operator>=(const inf_int &lhs, const inf_int &rhs) {
	if(lhs > rhs || lhs == rhs) {
		return true;
	}
	else {
		return false;
	}
}

bool operator<=(const inf_int &lhs, const inf_int &rhs) {
	if(lhs < rhs || lhs == rhs) {
		return true;
	}
	else {
		return false;
	}
}

inf_int operator+(const inf_int &lhs, const inf_int &rhs) {
	inf_int ifint_return;
	bool b_lhs_positive = __is_positive(lhs);
	bool b_rhs_positive = __is_positive(rhs);
	if((b_lhs_positive && b_rhs_positive) || (!b_lhs_positive && !b_rhs_positive)) {
		ifint_return = __add(lhs, rhs);
	}
	else {
		if(!b_lhs_positive) {
			ifint_return = __sub(rhs, lhs);
		}
		else {
			ifint_return = __sub(lhs, rhs);
		}
	}
	return ifint_return;
}

inf_int operator-(const inf_int &lhs, const inf_int &rhs) {
	inf_int ifint_return;
	bool b_lhs_positive = __is_positive(lhs);
	bool b_rhs_positive = __is_positive(rhs);
	if(b_lhs_positive && b_rhs_positive) {
		ifint_return = __sub(lhs, -rhs);
	}
	else if(b_lhs_positive && !b_rhs_positive) {
		ifint_return = __add(lhs, -rhs);
	}
	else if(!b_lhs_positive && b_rhs_positive) {
		ifint_return = __add(lhs, -rhs);
	}
	else {
		ifint_return = __sub(-rhs, lhs);
	}
	return ifint_return;	
}

inf_int operator*(const inf_int &lhs, const inf_int &rhs) {
    return __multiply(lhs, rhs);
}

inf_int operator/(const inf_int &lhs, const inf_int &rhs) {
    return __divide(lhs, rhs);
}

inf_int operator%(const inf_int &lhs, const inf_int &rhs) {
    return __mod(lhs, rhs);
}
