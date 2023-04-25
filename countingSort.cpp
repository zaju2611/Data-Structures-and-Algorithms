#include <iostream>

using namespace std;

void show(char **tab_przed, int n, int k, int m) //funkcja do wyswietlania od ostatniego wiersza odpowiedniej ilości w kolejnosci rosnącej
{
    for (int i = n - 1; i >= n - m; i--)
    {
        for (int j = 0; j < k; j++)
        {
            cout << tab_przed[i][j];
        }
        cout << '\n';
    }
}

void swap(char **tab_przed, char **tab_po, int n )//funkcja do zamieniania wierszy tablic
{
    for (int i = 0; i < n; i++)
    {
        tab_przed[i] = tab_po[i];
    }
}

void counting_sort(char **tab_przed, int n, int k, int m) //
{
    char **tab_po = new char *[n]; //tworze tablice pomocnicza

    int *count = new int[2]; // tablica do zliczania ilosci wystapien

    for (int i = k - 1; i >= 0; i--)
    {

        count[0] = 0;//zerowanie ilosci wystapien znakow
        count[1] = 0;
        for (int j = n- 1; j >= 0; j--)
        {
            if (tab_przed[j][i] == 'o') //zliczanie ilosci znakow
            {
                count[0]++;
            }
            else
            {
                count[1]++;
            }
        }
        count[1] += count[0]; //dodanie ilosci wystąpień 'o' do ilosci wystapien 'X'
        for (int j = n - 1; j >= 0; j--)
        {
            if (tab_przed[j][i] == 'o')
            {
                tab_po[count[0] - 1] = tab_przed[j]; //przypisywanie odpowiednim wierszom wartosci
                count[0]--;// zmniejszenie ilosci wystapien
            }
            else
            {
                tab_po[count[1] - 1] = tab_przed[j];
                count[1]--;
            }
        }
        swap(tab_przed, tab_po, n); // zamiana tablic
        
    }

    show(tab_przed, n, k, m); // wyswietlenie wynikow
    delete[] tab_po; // usuniecie tablicy pomocniczej
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k, m;
    cin >> n >> k >> m;

    char **sort_przed = new char *[n];
    for (int i = 0; i < n; i++)
    {
        sort_przed[i] = new char[k];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            cin >> sort_przed[i][j];
        }
    }

    counting_sort(sort_przed, n, k, m);

    for (int i = 0; i < n; i++)
    {
        delete[] sort_przed[i];
    }
    delete[] sort_przed;

    return 0;
}