# Szyfrowanie XOR – C++ i WebAssembly

## 1\. Opis projektu

Projekt przedstawia prosty program do szyfrowania i deszyfrowania tekstu przy wykorzystaniu operatora XOR.

Program został napisany w języku C++, a następnie skompilowany do WebAssembly (WASM) przy użyciu narzędzia Emscripten.

Interfejs programu został wykonany w HTML i JavaScript.

## 2\. Wykorzystane technologie

- **C++** – implementacja szyfrowania i deszyfrowania XOR.
- **WebAssembly (WASM)** – uruchamianie kodu C++ w przeglądarce.
- **Emscripten** – kompilacja C++ do WebAssembly.
- **HTML** – struktura strony internetowej.
- **JavaScript** – obsługa formularza i komunikacja z WASM.

## 3\. Działanie programu

Program umożliwia:

1. Wpisanie tekstu do pola tekstowego.
2. Zaszyfrowanie tekstu przy użyciu operatora XOR.
3. Wyświetlenie zaszyfrowanego tekstu w formacie HEX.
4. Wklejenie szyfrogramu do pola tekstowego.
5. Odszyfrowanie tekstu przy użyciu tego samego klucza.
6. Odzyskanie oryginalnej wiadomości.

## 4\. Zasada działania XOR

Operator XOR porównuje dwa bity:

| Bit 1 | Bit 2 | Wynik XOR |
| --- | --- | --- |
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

Przykład:

text

```text
b1   010011
b2   110011
     ------
XOR  100000
```

Najważniejszą właściwością XOR jest możliwość odwrócenia operacji przy użyciu tego samego klucza.

text

```text
A XOR B = C
C XOR B = A
```

Dzięki temu do szyfrowania i deszyfrowania wykorzystywana jest ta sama operacja.

## 5\. Klucz szyfrujący

W projekcie wykorzystano klucz 32-bitowy.

Klucz jest generowany na podstawie hasła znajdującego się w pliku `app.js`.

javascript

```javascript
const secret = "MOJ_TAJNY_KLUCZ_123";
```

Hasło jest przetwarzane na liczbę 32-bitową, która następnie wykorzystywana jest podczas operacji XOR.

## 6\. Struktura projektu

text

```text
MojProjekt/
│
├── main.cpp
├── index.html
├── app.js
├── main.js
├── main.wasm
└── README.md
```

Opis plików:

- `main.cpp` – funkcje szyfrujące i deszyfrujące.
- `index.html` – interfejs strony internetowej.
- `app.js` – obsługa przycisków i generowanie klucza.
- `main.js` – plik wygenerowany przez Emscripten.
- `main.wasm` – skompilowany kod C++.
- `README.md` – dokumentacja projektu.

## 7\. Instalacja i kompilacja

Do kompilacji wymagany jest Emscripten SDK.

Po aktywowaniu środowiska Emscripten należy przejść do folderu projektu i wykonać polecenie:

cmd

```cmd
em++ main.cpp -o main.js -lembind -std=c++17
```

Kompilacja wygeneruje pliki:

- `main.js`
- `main.wasm`

## 8\. Uruchomienie projektu

W folderze projektu należy uruchomić lokalny serwer:

cmd

```cmd
python -m http.server 8000
```

Następnie otworzyć przeglądarkę i przejść pod adres:

http://localhost:8000

## 9\. Podsumowanie

Projekt pokazuje zastosowanie operatora XOR do szyfrowania i deszyfrowania danych.

Dodatkowo przedstawia sposób wykorzystania języka C++ w przeglądarce internetowej dzięki technologii WebAssembly.

**Uwaga:** Projekt ma charakter edukacyjny. XOR z powtarzanym kluczem 32-bitowym nie jest bezpiecznym algorytmem do ochrony poufnych danych.

Zapisz plik pod nazwą `README.md` bezpośrednio w folderze `MojProjekt`.
