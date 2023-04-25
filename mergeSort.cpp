#include <iostream>
#include <stdio.h>

class Warzywo
{
public:
    char nazwa[15];
    float z;
    int d;
    int m;

    Warzywo() {}

    float getKwasowosc()
    {
        return z;
    }

    int getGestosc()
    {
        return d;
    }

    int getMiesiac()
    {
        return m;
    }

    char *getNazwa()
    {
        return nazwa;
    }
};

// -1 (this < other) +1 (this > other) 0 this == other
int porownajKwasowosc(Warzywo a, Warzywo b)
{
    if (a.getKwasowosc() > b.getKwasowosc())
    {
        return -1;
    }
    else if (a.getKwasowosc() < b.getKwasowosc())
    {
        return 1;
    }
    return 0;
}

// -1 (this < other) +1 (this > other) 0 this == other
int porownajGestosc(Warzywo a, Warzywo b)
{
    if (a.getGestosc() > b.getGestosc())
    {
        return -1;
    }
    else if (a.getGestosc() < b.getGestosc())
    {
        return 1;
    }

    return 0;
}

// -1 (this < other) +1 (this > other) 0 this == other
int porownajMiesiac(Warzywo a, Warzywo b)
{
    if (a.getMiesiac() > b.getMiesiac())
    {
        return -1;
    }
    else if (a.getMiesiac() < b.getMiesiac())
    {
        return 1;
    }
    return 0;
}

int compare123(const Warzywo &a, const Warzywo &b)
{
    int ret1 = porownajKwasowosc(a, b);
    int ret2 = porownajGestosc(a, b);
    int ret3 = porownajMiesiac(a, b);

    return (ret1 != 0) ? ret1 : ((ret2 != 0) ? ret2 : ret3);
}

int compare132(const Warzywo &a, const Warzywo &b)
{
    int ret1 = porownajKwasowosc(a, b);
    int ret2 = porownajMiesiac(a, b);
    int ret3 = porownajGestosc(a, b);

    return (ret1 != 0) ? ret1 : ((ret2 != 0) ? ret2 : ret3);
}

int compare213(const Warzywo &a, const Warzywo &b)
{
    int ret1 = porownajGestosc(a, b);
    int ret2 = porownajKwasowosc(a, b);
    int ret3 = porownajMiesiac(a, b);

    return (ret1 != 0) ? ret1 : ((ret2 != 0) ? ret2 : ret3);
}

int compare231(const Warzywo &a, const Warzywo &b)
{
    int ret1 = porownajGestosc(a, b);
    int ret2 = porownajMiesiac(a, b);
    int ret3 = porownajKwasowosc(a, b);

    return (ret1 != 0) ? ret1 : ((ret2 != 0) ? ret2 : ret3);
}

int compare312(const Warzywo &a, const Warzywo &b)
{
    int ret1 = porownajMiesiac(a, b);
    int ret2 = porownajKwasowosc(a, b);
    int ret3 = porownajGestosc(a, b);

    return (ret1 != 0) ? ret1 : ((ret2 != 0) ? ret2 : ret3);
}

int compare321(const Warzywo &a, const Warzywo &b)
{
    int ret1 = porownajMiesiac(a, b);
    int ret2 = porownajGestosc(a, b);
    int ret3 = porownajKwasowosc(a, b);

    return (ret1 != 0) ? ret1 : ((ret2 != 0) ? ret2 : ret3);
}

void wczytaj(Warzywo *tab, int size)
{

    for (int i = 0; i < size; i++)
    {
        scanf("%s%f%d%d", tab[i].nazwa, &tab[i].z, &tab[i].d, &tab[i].m);
    }
}

void merge123(Warzywo *T, int l, int h)
{
    Warzywo *U = new Warzywo[h - l + 1];
    int m = (l + h) / 2;
    int i = l;
    int j = m + 1;
    int k = 0;
    while (i <= m && j <= h)
    {
        if (compare123(T[i], T[j]) <= 0)
        {
            U[k] = T[i];
            i++;
            k++;
        }
        else
        {
            U[k] = T[j];
            j++;
            k++;
        }
    }

    if (i > m)
    {
        while (j <= h)
        {
            U[k] = T[j];
            j++;
            k++;
        }
    }
    else
    {
        while (i <= m)
        {
            U[k] = T[i];
            i++;
            k++;
        }
    }

    for (int ii = 0; ii < k; ii++)
    {
        T[ii + l] = U[ii];
    }

    delete[] U;
}

void merge132(Warzywo *T, int l, int h)
{
    Warzywo *U = new Warzywo[h - l + 1];
    int m = (l + h) / 2;
    int i = l;
    int j = m + 1;
    int k = 0;
    while (i <= m && j <= h)
    {
        if (compare132(T[i], T[j]) <= 0)
        {
            U[k] = T[i];
            i++;
            k++;
        }
        else
        {
            U[k] = T[j];
            j++;
            k++;
        }
    }

    if (i > m)
    {
        while (j <= h)
        {
            U[k] = T[j];
            j++;
            k++;
        }
    }
    else
    {
        while (i <= m)
        {
            U[k] = T[i];
            i++;
            k++;
        }
    }

    for (int ii = 0; ii < k; ii++)
    {
        T[ii + l] = U[ii];
    }

    delete[] U;
}

void merge213(Warzywo *T, int l, int h)
{
    Warzywo *U = new Warzywo[h - l + 1];
    int m = (l + h) / 2;
    int i = l;
    int j = m + 1;
    int k = 0;
    while (i <= m && j <= h)
    {
        if (compare213(T[i], T[j]) <= 0)
        {
            U[k] = T[i];
            i++;
            k++;
        }
        else
        {
            U[k] = T[j];
            j++;
            k++;
        }
    }

    if (i > m)
    {
        while (j <= h)
        {
            U[k] = T[j];
            j++;
            k++;
        }
    }
    else
    {
        while (i <= m)
        {
            U[k] = T[i];
            i++;
            k++;
        }
    }

    for (int ii = 0; ii < k; ii++)
    {
        T[ii + l] = U[ii];
    }

    delete[] U;
}

void merge231(Warzywo *T, int l, int h)
{
    Warzywo *U = new Warzywo[h - l + 1];
    int m = (l + h) / 2;
    int i = l;
    int j = m + 1;
    int k = 0;
    while (i <= m && j <= h)
    {
        if (compare231(T[i], T[j]) <= 0)
        {
            U[k] = T[i];
            i++;
            k++;
        }
        else
        {
            U[k] = T[j];
            j++;
            k++;
        }
    }

    if (i > m)
    {
        while (j <= h)
        {
            U[k] = T[j];
            j++;
            k++;
        }
    }
    else
    {
        while (i <= m)
        {
            U[k] = T[i];
            i++;
            k++;
        }
    }

    for (int ii = 0; ii < k; ii++)
    {
        T[ii + l] = U[ii];
    }

    delete[] U;
}

void merge312(Warzywo *T, int l, int h)
{
    Warzywo *U = new Warzywo[h - l + 1];
    int m = (l + h) / 2;
    int i = l;
    int j = m + 1;
    int k = 0;
    while (i <= m && j <= h)
    {
        if (compare312(T[i], T[j]) <= 0)
        {
            U[k] = T[i];
            i++;
            k++;
        }
        else
        {
            U[k] = T[j];
            j++;
            k++;
        }
    }

    if (i > m)
    {
        while (j <= h)
        {
            U[k] = T[j];
            j++;
            k++;
        }
    }
    else
    {
        while (i <= m)
        {
            U[k] = T[i];
            i++;
            k++;
        }
    }

    for (int ii = 0; ii < k; ii++)
    {
        T[ii + l] = U[ii];
    }

    delete[] U;
}

void merge321(Warzywo *T, int l, int h)
{
    Warzywo *U = new Warzywo[h - l + 1];
    int m = (l + h) / 2;
    int i = l;
    int j = m + 1;
    int k = 0;
    while (i <= m && j <= h)
    {
        if (compare321(T[i], T[j]) <= 0)
        {
            U[k] = T[i];
            i++;
            k++;
        }
        else
        {
            U[k] = T[j];
            j++;
            k++;
        }
    }

    if (i > m)
    {
        while (j <= h)
        {
            U[k] = T[j];
            j++;
            k++;
        }
    }
    else
    {
        while (i <= m)
        {
            U[k] = T[i];
            i++;
            k++;
        }
    }

    for (int ii = 0; ii < k; ii++)
    {
        T[ii + l] = U[ii];
    }

    delete[] U;
}

void mergesort123(Warzywo *T, int l, int h)
{
    if (l < h)
    {
        int m = (l + h) / 2;
        mergesort123(T, l, m);
        mergesort123(T, m + 1, h);
    }

    merge123(T, l, h);
}

void mergesort132(Warzywo *T, int l, int h)
{
    if (l < h)
    {
        int m = (l + h) / 2;
        mergesort132(T, l, m);
        mergesort132(T, m + 1, h);
    }

    merge132(T, l, h);
}

void mergesort213(Warzywo *T, int l, int h)
{
    if (l < h)
    {
        int m = (l + h) / 2;
        mergesort213(T, l, m);
        mergesort213(T, m + 1, h);
    }

    merge213(T, l, h);
}

void mergesort231(Warzywo *T, int l, int h)
{
    if (l < h)
    {
        int m = (l + h) / 2;
        mergesort231(T, l, m);
        mergesort231(T, m + 1, h);
    }

    merge231(T, l, h);
}

void mergesort312(Warzywo *T, int l, int h)
{
    if (l < h)
    {
        int m = (l + h) / 2;
        mergesort312(T, l, m);
        mergesort312(T, m + 1, h);
    }

    merge312(T, l, h);
}

void mergesort321(Warzywo *T, int l, int h)
{
    if (l < h)
    {
        int m = (l + h) / 2;
        mergesort321(T, l, m);
        mergesort321(T, m + 1, h);
    }

    merge321(T, l, h);
}

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    scanf("%d", &n);

    int c1, c2, c3;
    scanf("%d%d%d", &c1, &c2, &c3);

    Warzywo *korzenne = new Warzywo[n];
    Warzywo *niekorzenne = new Warzywo[n];

    wczytaj(korzenne, n);
    wczytaj(niekorzenne, n);

    if (c1 == 1 && c2 == 2 && c3 == 3)
    {
        mergesort123(korzenne, 0, n - 1);
        mergesort123(niekorzenne, 0, n - 1);
    }
    else if (c1 == 1 && c2 == 3 && c3 == 2)
    {
        mergesort132(korzenne, 0, n - 1);
        mergesort132(niekorzenne, 0, n - 1);
    }
    else if (c1 == 2 && c2 == 1 && c3 == 3)
    {
        mergesort213(korzenne, 0, n - 1);
        mergesort213(niekorzenne, 0, n - 1);
    }
    else if (c1 == 2 && c2 == 3 && c3 == 1)
    {
        mergesort231(korzenne, 0, n - 1);
        mergesort231(niekorzenne, 0, n - 1);
    }
    else if (c1 == 3 && c2 == 1 && c3 == 2)
    {
        mergesort312(korzenne, 0, n - 1);
        mergesort312(niekorzenne, 0, n - 1);
    }
    else if (c1 == 3 && c2 == 2 && c3 == 1)
    {
        mergesort321(korzenne, 0, n - 1);
        mergesort321(niekorzenne, 0, n - 1);
    }

    for (int i = 0; i < n; i++)
    {
        printf("%s-%s ", korzenne[i].nazwa, niekorzenne[i].nazwa);
    }

    delete[] korzenne;
    delete[] niekorzenne;

    return 0;
}