#include <iostream>
#include <string>

using namespace std;

struct wezel {
    string etykieta;
    int klasa;
    wezel* pod;
    wezel* obok;

    wezel(const int& klasaP) {
        klasa = klasaP;
        etykieta = "X";
        pod = NULL;
        obok = NULL;
    }
};

// funkcja rekurencyjna, ktora wypisuje drzewo w porzadku postorder i rownoczesnie usuwa wezly tego drzewa
void post(wezel* w) {
    if (w->pod) { // jesli istnieje potomek wezla w
        post(w->pod); // wywolanie rekurencyjne dla potomka wezla w
    }

    cout << w->etykieta << endl; // wypisanie etykiety wezla w

    if (w->obok) { // jesli istnieje rodzenstwo wezla w
        post(w->obok); // wywolanie rekurencyjne dla rodzenstwa wezla w
    }

    delete w; // usuniecie wezla w
}

void pre(wezel* w) {
    cout << w->etykieta << endl; // wypisanie etykiety wezla w

    if (w->pod) { // jesli istnieje potomek wezla w
        pre(w->pod); // wywolanie rekurencyjne dla potomka wezla w
    }

    if (w->obok) { // jesli istnieje rodzenstwo wezla w
        pre(w->obok); // wywolanie rekurencyjne dla rodzenstwa wezla w
    }

    delete w; // usuniecie wezla w
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int liczbaInstrukcji, liczbaKlas;
    string etykieta;
    int klasa;
    cin >> liczbaInstrukcji; // wczytanie liczby wszystkich instrukcji
    wezel* korzen = new wezel(0); // utworzenie korzenia drzewa
    korzen->etykieta = "Stan spoczynku"; // nadanie odpowiedniej etykiety korzeniowi
    wezel* obecny;

    // wczytywanie kolejnych instrukcji
    while (liczbaInstrukcji-- > 0) {
        getline(cin, etykieta);
        getline(cin, etykieta); // wczytanie linii z etykieta
        cin >> liczbaKlas; // wczytanie liczby klas
        obecny = korzen; // proces przechodzenia po drzewie rozpoczyna sie od korzenia

        // wykonywanie dzialan dla kolejnych numerow klas
        while (liczbaKlas-- > 0) {
            cin >> klasa; // wczytanie numeru klasy

            if (obecny->pod == NULL) { // jesli obecny wezel nie ma potomka
                obecny->pod = new wezel(klasa); // utworzenie potomka wezla obecngo i nadanie mu wczytanego numeru
                obecny = obecny->pod; // przejscie do potomka
                continue; // wykonanie kolejnego obrotu petli
            }

            obecny = obecny->pod; // przejscie do potomka wezla obecnego

            // przeszukiwanie rodzenstwa wezla obecnego
            while (obecny->obok) {
                if (obecny->klasa == klasa) {
                    break; // przerwanie dzialania petli jesli znaleziono wezel o odpowiednim numerze klasy
                }

                obecny = obecny->obok; // przejscie do kolejnego wezla
            }

            if (obecny->klasa == klasa) {
                continue; // nalezy przejsc do kolejnego obrotu petli jesli znaleziono wezel o odpowiednim numerze klasy
            }

            // nie znaleziono wezla o odpowiednim numerze klasy, wiec nalezy taki wezel utworzyc i dodac na koniec listy wezlow
            obecny->obok = new wezel(klasa);
            obecny = obecny->obok;
        }

        obecny->etykieta = etykieta; // nadanie etykiety docelowemu wezlowi
    }

    cin >> klasa; // klasa odpowiada tutaj za decyzje o sposobie wypisywania drzewa

    if (klasa == 1) {
        pre(korzen); // wypisanie drzewa w porzadku preorder
    } else if (klasa == 2) {
        post(korzen); // wypisanie drzewa w porzadku postorder
    }

    return 0;
}
