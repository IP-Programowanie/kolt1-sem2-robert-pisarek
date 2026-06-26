#include "kol_lib.h"

void Dane_compress(uint32_t& dest, Dane src) {
	dest |= src.liczba << DaneT::SHIFT::s_liczba;
	dest |= src.symbol << DaneT::SHIFT::s_symbol;
	dest |= src.aktywna << DaneT::SHIFT::s_aktywna;
	dest |= src.wczytana << DaneT::SHIFT::s_wczytana;
	dest |= src.obliczona << DaneT::SHIFT::s_obliczona;
	dest |= src.estymowana << DaneT::SHIFT::s_estymowana;
}

void Dane_decompress(Dane& dest, uint32_t src) {
	dest.liczba = src >> DaneT::SHIFT::s_liczba & DaneT::MASK::liczba;
	dest.symbol = src >> DaneT::SHIFT::s_symbol & DaneT::MASK::symbol;
	dest.aktywna = src >> DaneT::SHIFT::s_aktywna & DaneT::MASK::aktywna;
	dest.wczytana = src >> DaneT::SHIFT::s_wczytana & DaneT::MASK::wczytana;
	dest.obliczona = src >> DaneT::SHIFT::s_obliczona & DaneT::MASK::obliczona;
	dest.estymowana = src >> DaneT::SHIFT::s_estymowana & DaneT::MASK::estymowana;
}

void Dane_setObliczonaLow(uint32_t& dest) {
	dest &= ~(DaneT::MASK::obliczona << DaneT::SHIFT::s_obliczona);
}

short Dane_getLiczba(uint32_t& src) {
	return ((src >> DaneT::SHIFT::s_liczba) & DaneT::MASK::liczba);
}

DA DA_alloc(uint32_t size) {
	uint32_t* data = new uint32_t[1 + size];
	DA da = new uint32_t * [2];
	da[1] = data;
	*data = size;
	data++;
	for (uint32_t i = 0; i < size; i++) {
		data[i] = 0;
	}
	da[0] = data;
	return da;
}

void DA_dealloc(DA arr) {
	arr[0] = nullptr;
	uint32_t* temp1 = arr[1];
	arr[1] = nullptr;
	delete[] temp1;
	temp1 = nullptr;

	uint32_t** temp2 = arr;
	arr = nullptr;
	delete[] temp2;
	temp2 = nullptr;
}

void DA_set(DA arr, uint32_t src, uint32_t index) {
	if (index >= *arr[1]) throw std::out_of_range("invalid index");
	arr[0][index] = src;
}

void DA_set(DA arr, Dane src, uint32_t index) {
	if (index >= *arr[1]) throw std::out_of_range("invalid index");
	uint32_t csrc = 0;
	Dane_compress(csrc, src);
	arr[0][index] = csrc;
}

uint32_t DA_getSize(DA arr) {
	return *arr[1];
}

void DA_writeToFile(DA arr, const char* filename) {
	FILE* file = nullptr;
	fopen_s(&file, filename, "w+b");
	if (file == nullptr) return;
	const uint32_t size = DA_getSize(arr);
	fwrite(arr[0], sizeof(uint32_t), size, file);
	fclose(file);
}

DA DA_readFromFile(const char* filename) {
	FILE* file = nullptr;
	fopen_s(&file, filename, "r+b");
	if (file == nullptr) return nullptr;
	fseek(file, 0, SEEK_END);
	uint32_t size = ftell(file) / sizeof(uint32_t);
	if (size <= 0) return nullptr;
	DA arr = DA_alloc(size);
	rewind(file);
	fread(arr[0], sizeof(uint32_t), size, file);
	fclose(file);
	return arr;
}