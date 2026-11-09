#include <string>
#include <cstdint>
#include <emscripten/bind.h>

using namespace std;

// Funkcja szyfrująca tekst operatorem XOR
// text - tekst do zaszyfrowania
// key - 32-bitowy klucz szyfrujący
string xorEncrypt(const string& text, uint32_t key) {

    // Tablica znaków do zamiany wyniku na system szesnastkowy
    const char hex[] = "0123456789ABCDEF";

    // Zmienna przechowująca zaszyfrowany tekst
    string result = "";

    // Pętla przechodząca przez każdy znak tekstu
    for (size_t i = 0; i < text.size(); i++) {

        // Pobranie jednego bajtu z klucza 32-bitowego
        unsigned char keyByte = (key >> ((i % 4) * 8)) & 0xFF;

        // Wykonanie operacji XOR na znaku i bajcie klucza
        unsigned char encrypted = text[i] ^ keyByte;

        // Zamiana wyniku na dwa znaki szesnastkowe
        result += hex[encrypted >> 4];
        result += hex[encrypted & 0x0F];
    }

    // Zwrócenie zaszyfrowanego tekstu
    return result;
}


// Funkcja odszyfrowująca tekst operatorem XOR
// text - tekst zaszyfrowany w formacie HEX
// key - ten sam 32-bitowy klucz użyty do szyfrowania
string xorDecrypt(const string& text, uint32_t key) {

    // Zmienna przechowująca odszyfrowany tekst
    string result = "";

    // Sprawdzenie, czy długość szyfrogramu jest parzysta
    if (text.size() % 2 != 0) {
        return "";
    }

    // Pętla odczytująca po dwa znaki HEX
    for (size_t i = 0; i < text.size(); i += 2) {

        // Zmienna przechowująca odczytany bajt
        unsigned int byte;

        // Zamiana dwóch znaków HEX na liczbę
        try {
            byte = stoi(text.substr(i, 2), nullptr, 16);
        }
        catch (...) {
            return "";
        }

        // Pobranie odpowiedniego bajtu klucza
        unsigned char keyByte = (key >> (((i / 2) % 4) * 8)) & 0xFF;

        // Ponowne wykonanie XOR w celu odzyskania tekstu
        result += static_cast<char>(byte ^ keyByte);
    }

    // Zwrócenie odszyfrowanego tekstu
    return result;
}


// Udostępnienie funkcji C++ dla JavaScript przez Embind
EMSCRIPTEN_BINDINGS(xor_module) {
    emscripten::function("xorEncrypt", &xorEncrypt);
    emscripten::function("xorDecrypt", &xorDecrypt);
}