#include <iostream>
#include "stdlib.h"
#include "inf_int.h"

using namespace std;

int main(int argc, char **argv) {
	inf_int ifint = -100;
	inf_int ifint2(ifint);
	inf_int ifint3 = ifint2;
	inf_int ifint4("12345");
	ifint = 209.225;
	ifint3 = 0;
	/*
	 * Testing with cout (operator<<)
	 */
	cout << "ifint: " << -ifint << endl; 
	cout << "ifint2: " << ifint2 << endl;
	cout << "ifint3: " << -ifint3 << endl;
	ifint4 = -ifint4;
	cout << "ifint4: " << (--(ifint4++))-- << endl;
	cout << "ifint4: " << ifint4 << endl;

	/*
	// Testing with cin (operator>>)
	inf_int if4;
	cin >> if4;
	cout << if4 << endl;
	*/

	/*
	 * Testing with operator== and operator!=, > and <
	 */
	int i_val = 209;
	ifint == i_val ? cout << "operator==(const inf_int&, const inf_int&) test true" << endl 
		: cout << "operator==(const inf_int&, const inf_int&) test false" << endl;
	i_val = -209;
	i_val == ifint ? cout << "operator==(const inf_int&, const inf_int&) test true" << endl 
		: cout << "operator==(const inf_int&, const inf_int&) test false" << endl;

	ifint != i_val ? cout << "operator!=(const inf_int&, const inf_int&) test true" << endl 
		: cout << "operator==(const inf_int&, const inf_int&) test false" << endl;
	i_val = 209;
	i_val != ifint ? cout << "operator!=(const inf_int&, const inf_int&) test true" << endl 
		: cout << "operator==(const inf_int&, const inf_int&) test false" << endl;
	if(ifint == 0) {
		cout << "ifint = 0" << endl;
	}
	if(0 != ifint) {
		cout << "0 != ifint" << endl;
	}
	if(ifint > ifint2) {
		cout << "ifint > ifint2" << endl;
	}
	if(ifint < ifint2) {
		cout << "ifint < ifint2" << endl;
	}
	if(ifint2 < ifint) {
		cout << "ifint2 < ifint" << endl;
	}
	if(ifint2 > ifint) {
		cout << "ifint2 > ifint" << endl;
	}
	//ifint = ifint2;
	if(ifint >= ifint2) {
		cout << "ifint >= ifint2" << endl;
	}
	if(ifint <= ifint2) {
		cout << "ifint <= ifint2" << endl;
	}

	/*
	 * Testing with convertion functions
	 */
	ifint = -209;
	long l_val = 100000;
	cout << ifint.to_int() + 100 << endl;
	cout << ifint.to_long() + l_val << endl;

	/*
	 * Testing with operator+, -, += and -=
	 */
	ifint = -209;
	ifint2 = 309;
	ifint2 += 100;
	ifint += "100";
	ifint -= 100;
	ifint2-= "100";
	cout << "ifint: " << ifint << endl;
	cout << "ifint2: " << ifint2 << endl;
	cout << "ifint + ifint2 = " << ifint + ifint2 << endl;
	cout << "ifint - ifint2 = " << ifint - ifint2 << endl;

    /*
     * Testing with operator *
     */
    ifint = "123452345634567456785678967890";
    ifint2 = "1234523456";
    cout << "ifint: " << ifint << endl;
    cout << "ifint2: " << ifint2 << endl;
    cout << "ifint * ifint2 = " << ifint * ifint2 << endl;

    /*
     * Testing with operator /
     */
    ifint = "123452345634567456785678967890";
    ifint2 = "123452345634567";
    cout << "ifint: " << ifint << endl;
    cout << "ifint2: " << ifint2 << endl;
    cout << "ifint / ifint2 = " << ifint / ifint2 << endl;
    cout << "ifint % ifint2 = " << ifint % ifint2 << endl;

    /*
     * Testing with to_bin()
     */
    ifint = "123452345634567456785678967890";
    cout << "ifint binary: " << ifint.to_bin() << endl; 

	return 0;
}
