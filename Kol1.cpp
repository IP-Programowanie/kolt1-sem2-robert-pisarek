#include "Wybor.h"

/*
* Uwaga: Zadania kod rozwiazania zaania umieszczać pomiędzy #ifdef a #endif. 
*/

#ifdef Kol_1

#include "kol_lib.h"
#include "PK1_kolA.h"
#include <bitset>
#include <cstdint>

using namespace std;

int main()
{
	Dane a = {}, b = {};
	wypelnij(a, 15, 'A', 1, 0, 1, 0);
	wypelnij(b, 12345, 'B', 1, 1, 1, 1);
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	uint32_t ca = 0, cb = 0;
	Dane_compress(ca, a);
	Dane_compress(cb, b);
	cout << endl << "compressed:" << endl;
	cout << "a: " << bitset<32>(ca) << endl;
	cout << "b: " << bitset<32>(cb) << endl;
	cout << "   " << "ELLLLLLLLLLLLLLLLA__SSSSSSSS_O_W" << endl;
	Dane da = {}, db = {};
	Dane_decompress(da, ca);
	Dane_decompress(db, cb);
	cout << endl << "decompressed:" << endl;
	cout << "a: " << da << endl;
	cout << "b: " << db << endl;
	cout << endl << "TEST:" << endl;
	cout << "a:" << ((a == da) ? "PASS" : "FAIL") << endl;
	cout << "b:" << ((b == db) ? "PASS" : "FAIL") << endl;
	Dane_setObliczonaLow(ca);
	Dane_setObliczonaLow(cb);
	cout << endl << "obliczona low:" << endl;
	cout << "a: " << bitset<32>(ca) << endl;
	cout << "b: " << bitset<32>(cb) << endl;
	cout << "   " << "ELLLLLLLLLLLLLLLLA__SSSSSSSS_O_W" << endl;
	cout << endl << "liczba:" << endl;
	cout << "a: " << Dane_getLiczba(ca) << endl;
	cout << "b: " << Dane_getLiczba(cb) << endl;
	const uint32_t size = 8;
	DA arr = DA_alloc(size);
	DA_set(arr, a, 0);
	DA_set(arr, ca, 1);
	DA_set(arr, da, 2);
	DA_set(arr, b, 3);
	DA_set(arr, cb, 4);
	DA_set(arr, db, 5);
	cout << endl << "DA:" << endl;
	for (int i = 0; i < DA_getSize(arr); i++) {
		cout << " " << i << ": " << bitset<32>(arr[0][i]) << endl;
	}
	cout << "    " << "ELLLLLLLLLLLLLLLLA__SSSSSSSS_O_W" << endl;

	DA_writeToFile(arr, "da.bin");
	DA new_arr = DA_readFromFile("da.bin");

	cout << endl << "DA from file:" << endl;
	for (int i = 0; i < DA_getSize(new_arr); i++) {
		cout << " " << i << ": " << bitset<32>(new_arr[0][i]) << endl;
	}
	cout << "    " << "ELLLLLLLLLLLLLLLLA__SSSSSSSS_O_W" << endl;

	DA_dealloc(arr);
	DA_dealloc(new_arr);
}

#endif
