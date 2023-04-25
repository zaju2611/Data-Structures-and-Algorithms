#include <iostream>

using std::cout; using std::cin; using std::endl;

struct element {
    char symbol;
    int czas;
    int miejsce;
    element* nast;

    element(char symbolP, int czasP, int miejsceP) {
        symbol = symbolP;
        czas = czasP;
        miejsce = miejsceP;
        nast = NULL;
    }
};

// struktura kolejki
struct kolejka {
    element* poczatek;
    element* koniec;

    kolejka() {
        poczatek = NULL;
        koniec = NULL;
    }

    ~kolejka() {
        element* usuwany;

        while (poczatek) {
            usuwany = poczatek;
            poczatek = poczatek->nast;
            delete usuwany;
        }
    }
};

// funkcja odpowiedzialna za dodanie elementu do kolejki
void enqueue(kolejka* kol, element* elem) {
    if (kol->poczatek) { // jesli kolejka nie jest pusta
        kol->koniec->nast = elem; // niech koniec wskazuje na nowu element
    } else { // jesli kolejka jest pusta
        kol->poczatek = elem; // nowy element jest rowniez poczatkiem kolejki
    }

    kol->koniec = elem; // nowy element staje sie koncem kolejki
    elem->nast = NULL; // nastepnikiem konca jest NULL
}

// funkcja odpowiedzialna za pobranie elementu z kolejki
element* dequeue(kolejka* kol) {
    element* elem = kol->poczatek; // pobranie pierwszego elementu kolejki

    if (elem) { // jesli poczatek nie jest pusty
        kol->poczatek = elem->nast; // nowym poczatkiem jest element po pobieranym elemencie
    }

    return elem; // zwrocenie elementu, ktory byl poczatkiem kolejki
}

// funkcja, ktora sprawdza czy kolejka jest pusta
bool isEmpty(kolejka* kol) {
    return kol->poczatek == NULL;
}

int main() {
    int m, n, rozmiar;
    char* pola;
    int liczbaZestawow;
    kolejka* kol;
    bool sukces;
    char symbol;
    int czas;
    int miejsce, poz, wiersz, kolumna;
    element* el;

    cin >> liczbaZestawow;

    while (liczbaZestawow-- > 0) {
        cin >> m >> n;
        rozmiar = m * n;
        pola = new char[rozmiar + 1]; // utworzenie tablicy znakow symbolizujacej pola
        cin.ignore();

        // wczytanie pol
        for (int i = 0, j = 0; i < m; ++i, j += n) {
            cin.getline(pola + j, n + 1);
        }

        kol = new kolejka(); // utworzenie pustej kolejki

        // wyszukanie znaku Mieszka i dodanie do kolejki jego pozycji z czasem 0
        for (int i = 0; i < rozmiar; ++i) {
            if (pola[i] == 'M') {
                enqueue(kol, new element('M', 0, i));
                break;
            }
        }

        // szukanie znakow Ognia i dodawanie ich do kolejki
        for (int i = 0; i < rozmiar; ++i) {
            if (pola[i] == 'O') {
                enqueue(kol, new element('O', 0, i));
            }
        }

        sukces = false; // ustawienie sukceus na false

        // wykonywanie dzialan dopoki kolejka nie jest pusta
        while (!isEmpty(kol)) {
            el = dequeue(kol); // pobranie elementu z kolejki
            symbol = el->symbol; // uzyskanie symbolu rozpatrywanego elementu
            czas = el->czas + 1; // uzyskanie czasu rozpatrywanego elementu i dodanie do niego 1
            miejsce = el->miejsce; // uzyskanie pozycji rozpatrywanego elementu
            delete el; // usuniecie elementu

            if ((symbol == 'M') && (pola[miejsce] == 'O')) {
                continue; // nalezy przejsc do kolejnego elementu jesli na rozpatrywanym polu jest Mieszko lub ogien
            }

            // uzyskanie wspolrzednych aktualnego miejsca
            wiersz = miejsce / n;
            kolumna = miejsce - n * wiersz;

            // dodanie do kolejki sasiednich pol o ile nie sa one zajete lub symbolem jest ogien, a na polu znajduje sie Mieszko
            // jesli nastepuje wyjscie poza plansze to w przypadku, gdy symbolem jest Mieszko nastepuje sukces
            if (kolumna > 0) {
                poz = miejsce - 1;

                if ((pola[poz] == '.') || ((symbol == 'O') && (pola[poz] == 'M'))) {
                    pola[poz] = symbol;
                    enqueue(kol, new element(symbol, czas, poz));
                }
            } else if (symbol == 'M') {
                sukces = true;
                break;
            }

            if ((kolumna + 1) < n) {
                poz = miejsce + 1;

                if ((pola[poz] == '.') || ((symbol == 'O') && (pola[poz] == 'M'))) {
                    pola[poz] = symbol;
                    enqueue(kol, new element(symbol, czas, poz));
                }
            } else if (symbol == 'M') {
                sukces = true;
                break;
            }

             if (wiersz > 0) {
                poz = miejsce - n;

                if ((pola[poz] == '.') || ((symbol == 'O') && (pola[poz] == 'M'))) {
                    pola[poz] = symbol;
                    enqueue(kol, new element(symbol, czas, poz));
                }
            } else if (symbol == 'M') {
                sukces = true;
                break;
            }

            if ((wiersz + 1) < m) {
                poz = miejsce + n;

                if ((pola[poz] == '.') || ((symbol == 'O') && (pola[poz] == 'M'))) {
                    pola[poz] = symbol;
                    enqueue(kol, new element(symbol, czas, poz));
                }
            } else if (symbol == 'M') {
                sukces = true;
                break;
            }
        }

        if (sukces) {
            cout << czas << endl;
        } else {
            cout << "NIE" << endl;
        }

        delete kol; // usuniecie kolejki
        delete[] pola; // usuniecie pol
    }

    return 0;
}
