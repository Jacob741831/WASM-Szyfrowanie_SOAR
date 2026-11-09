// Hasło wykorzystywane do wygenerowania klucza
const secret = "MOJ_TAJNY_KLUCZ_123";

// Funkcja generująca klucz 32-bitowy z hasła
// secret - hasło podane przez użytkownika
function generateKey(secret) {

    // Początkowa wartość skrótu
    let hash = 2166136261;

    // Zamiana hasła na tablicę bajtów
    const bytes = new TextEncoder().encode(secret);

    // Przejście przez wszystkie bajty hasła
    for (const byte of bytes) {

        // Operacja XOR na bajcie i aktualnym skrócie
        hash ^= byte;

        // Mnożenie w celu uzyskania kolejnej wartości skrótu
        hash = Math.imul(hash, 16777619);
    }

    // Zwrócenie klucza jako liczby 32-bitowej bez znaku
    return hash >>> 0;
}

// Wygenerowanie klucza na podstawie hasła
const key = generateKey(secret);


// Pobranie pól tekstowych ze strony
const inputText = document.getElementById("inputText");
const encryptedText = document.getElementById("encryptedText");
const decryptedText = document.getElementById("decryptedText");

// Pobranie przycisków ze strony
const encryptBtn = document.getElementById("encryptBtn");
const decryptBtn = document.getElementById("decryptBtn");

// Pobranie pola informującego o stanie programu
const status = document.getElementById("status");

// Zmienna informująca, czy WASM został załadowany
let wasmReady = false;


// Oczekiwanie na załadowanie WebAssembly
document.addEventListener("wasm-ready", function() {

    // Informacja, że WASM działa
    wasmReady = true;

    status.textContent = "WASM został załadowany!";
});


// Obsługa przycisku szyfrowania
encryptBtn.addEventListener("click", function() {

    // Sprawdzenie, czy WASM jest gotowy
    if (!wasmReady) return;

    // Pobranie tekstu z pierwszego pola
    const text = inputText.value;

    // Wywołanie funkcji szyfrującej napisanej w C++
    encryptedText.value = Module.xorEncrypt(text, key);

    // Wyczyszczenie pola odszyfrowanego tekstu
    decryptedText.value = "";
});


// Obsługa przycisku deszyfrowania
decryptBtn.addEventListener("click", function() {

    // Sprawdzenie, czy WASM jest gotowy
    if (!wasmReady) return;

    // Pobranie zaszyfrowanego tekstu
    const text = encryptedText.value;

    // Wywołanie funkcji odszyfrowującej napisanej w C++
    decryptedText.value = Module.xorDecrypt(text, key);
});