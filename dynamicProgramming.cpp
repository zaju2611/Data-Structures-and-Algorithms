#include <iostream>
#include <algorithm>

using namespace std;

int max_skrajny(int x, int y)
{
    return max(x, y);
}
int max_srodkowy(int x, int y, int z)
{
    int maxi = x;
    if (y > maxi)
        maxi = y;
    if (z > maxi)
        maxi = z;
    return maxi;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    if (n == 1) // dla przypadku gdy jest jeden rząd
    {
        int *tab = new int[m];
        for (int i = 0; i < m; i++)
        {
            cin >> tab[i];
        }

        int index = 0;
        int max_value = tab[0];

        for (int j = 1; j < m; j++) // przeszukuje tablice w celu znalezienia indexu najwiekszej wartosci
        {
            if (tab[j] > tab[index])
            {
                index = j;
            }
        }

        for (int j = 0; j < m; j++) //przeszukuje tablice w celu znalezienia najwiekszej wartosci
        {
            if (tab[j] >= max_value)
            {
                max_value = tab[j];
            }
        }
        cout << index << " " << max_value;

        delete[] tab;
    }

    else // dla pozostałych przypadków
    {
        int *tab1 = new int[m]; // tworze tablice pomocniczą do przechowywania pierwszego rzedu
        int **tab = new int *[2]; // tworze tablice dwuwymiarowa z dwoma wierszami, zeby nie przechowywac wszystkich wierszy wczytywanych tylko zamieniac je na biezaco
        for (int i = 0; i < 2; i++)
        {
            tab[i] = new int[m];
        }

        for (int i = 0; i < m; i++) // wczytuje pierwszy rzad tablicy
        {
            cin >> tab[0][i];
        }

        for (int i = 0; i < m; i++)
        {
            tab1[i] = tab[0][i]; //tablice pomocnicza wypelniam wartosciami pierwszego rzedu
        }
        for (int i = 0; i < m; i++) //wczytuje drugi rzad dodajac wartosci pierwszego rzedu
        {
            if (i == 0)
            {
                cin >> tab[1][i];
                tab[1][i] += max_skrajny(tab1[i], tab1[i + 1]);
                continue;
            }
            else if (i == m - 1)
            {
                cin >> tab[1][i];
                tab[1][i] += max_skrajny(tab1[i], tab1[i - 1]);
                continue;
            }

            else
            {
                cin >> tab[1][i];
                tab[1][i] += max_srodkowy(tab1[i], tab1[i - 1], tab1[i + 1]);
                continue;
            }
        }

        for (int i = 0; i < m; i++) // zamieniam pierwszy rzad z drugim i przypisuje do tablicy pomocniczej wartosci pierwszego rzedu
        {
            tab[0][i] = tab[1][i];
            tab1[i] = tab[0][i];
        }

        for (int i = 2; i < n; i++) // petla dla pozostalych rzedow 
        {
            for (int j = 0; j < m; j++)
            {

                if (j == 0)
                {
                    cin >> tab[1][j]; //wczytuje wartosc nowego rzedu
                    tab[1][j] += max_skrajny(tab1[j], tab1[j + 1]); // dodaje do niego zsumowana wartosc poprzednich rzedow
                    tab[0][j] = tab[1][j]; // zamieniam rzedy miejscami
                }
                else if (j == m - 1)
                {
                    cin >> tab[1][j];//wczytuje wartosc nowego rzedu
                    tab[1][j] += max_skrajny(tab1[j], tab1[j - 1]);// dodaje do niego zsumowana wartosc poprzednich rzedow
                    tab[0][j] = tab[1][j];// zamieniam rzedy miejscami
                }

                else
                {
                    cin >> tab[1][j];//wczytuje wartosc nowego rzedu
                    tab[1][j] += max_srodkowy(tab1[j], tab1[j - 1], tab1[j + 1]);// dodaje do niego zsumowana wartosc poprzednich rzedow
                    tab[0][j] = tab[1][j];// zamieniam rzedy miejscami
                }
            }
            for (int k = 0; k < m; k++) // petla do zmiany wartosci w tablicy pomocniczej
            {
                tab1[k] = tab[0][k];
            }
        }

        int index = 0; //zmienna do przechowywania indexu
        int maximum = tab[1][0]; // zmienna do przechowywania maksymalnej wartosci
        for (int j = 1; j < m; j++)
        {
            if (tab[1][j] > tab[1][index]) 
            {
                index = j; // zamiana wartosci indexu w przypadku wystapienia wiekszej zmiennej
            }
        }

        for (int j = 0; j < m; j++)
        {
            if (tab[1][j] >= maximum)
            {
                maximum = tab[1][j]; // zamiana wartosci maksymalnej
            }
        }
        cout << index << " " << maximum; // wypisanie wynikow

        for (int i = 0; i < 2; i++)
        {
            delete[] tab[i];
        }
        delete[] tab;
        delete[] tab1;
    }

    return 0;
}