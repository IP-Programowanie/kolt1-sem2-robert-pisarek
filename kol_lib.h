#pragma once
#include "PK1_kolA.h"
#include <cstdint>

namespace DaneT {
	enum SHIFT {
		s_liczba = 15,
		s_symbol = 4,
		s_aktywna = 14,
		s_wczytana = 0,
		s_obliczona = 2,
		s_estymowana = 31
	};
	enum MASK {
		liczba = 0xFFFF,
		symbol = 0xFF,
		aktywna = 1,
		wczytana = 1,
		obliczona = 1,
		estymowana = 1
	};
}

typedef uint32_t** DA;

void Dane_compress(uint32_t& dest, Dane src);

void Dane_decompress(Dane& dest, uint32_t src);

void Dane_setObliczonaLow(uint32_t& dest);

short Dane_getLiczba(uint32_t& src);

DA DA_alloc(uint32_t size);

void DA_dealloc(DA arr);

void DA_set(DA arr, uint32_t src, uint32_t index);

void DA_set(DA arr, Dane src, uint32_t index);

uint32_t DA_getSize(DA arr);

void DA_writeToFile(DA arr, const char* filename);

DA DA_readFromFile(const char* filename);