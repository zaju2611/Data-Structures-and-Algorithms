#include <iostream>
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    Node *prev;
    Node *next;
    char name[15];
    int size;
};

struct List
{
    List *prev;
    List *next;
    Node *node;
};


void merge(int *T, int l, int h)
{
    int *U = new int[h - l + 1];
    int m = (l + h) / 2;
    int i = l;
    int j = m + 1;
    int k = 0;
    while (i <= m && j <= h)
    {
        if (T[i] < T[j])
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

void mergesort(int *T, int l, int h)
{
    if (l < h)
    {
        int m = (l + h) / 2;
        mergesort(T, l, m);
        mergesort(T, m + 1, h);
    }

    merge(T, l, h);
}

int find(int *T, int n, int val)
{
    int l = 0;
    int r = n - 1;
    while (l <= r)
    {
        int m = (l + r) / 2;
        if (T[m] < val)
        {
            l = m + 1;
        }
        else if (T[m] > val)
        {
            r = m - 1;
        }
        else
        {
            return m;
        }
    }
    return -1;
}

void remove(int *T, int &n, int idx)
{
    for (int i = idx; i < n - 1; i++)
    {
        T[i] = T[i + 1];
    }
    n--;
}

int sumCount(List *head) //funkcja liczaca sume
{
    List *tmp = head;
    int sum = 0;
    while (1)
    {
        sum += tmp->node->size;
        if (tmp->next == head)
        {
            break;
        }
        tmp = tmp->next;
    }
    return sum;
}

void move(List *&head, int x, int y, int &oldSize)
{
    if (x < 0)
    {
        x = abs(x);
        for (int i = 0; i < x; i++)
        {
            head = head->prev;
        }
    }
    else
    {
        for (int i = 0; i < x; i++)
        {
            head = head->next;
        }
    }

    oldSize = head->node->size;
    if (y < 0)
    {
        y = abs(y);
        for (int i = 0; i < y; i++)
        {
            head->node = head->node->prev;
        }
    }
    else
    {
        for (int i = 0; i < y; i++)
        {
            head->node = head->node->next;
        }
    }
}

void shiftNode(List *&head)
{
    Node *node = head->node;
    if (node->next == node)
    {
        delete node;
        head->node = NULL;
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        Node *tmp = head->node;
        head->node = node->next;
        delete tmp;
    }
}

void shift(List *&head, List *&ptr)
{
    List *tmp = head;
    while (1) //przechodzi po wszystkich listach i usuwa odpowiednie pola
    {
        shiftNode(tmp);

        if (tmp->next == head)
        {
            break;
        }
        tmp = tmp->next;
    }

    //usuniecie pustych list
    while (head && head->node == NULL)
    {
        if (head == head->next)//przypadek gdy jest jedna lista
        {
            if (head == ptr)
            {
                ptr = NULL;
            }
            delete head;
            head = NULL;

            return;
        }
        else
        {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            List *oldhead = head;
            if (oldhead == ptr)
            {
                ptr = head->next;
            }
            head = head->next;
            delete oldhead;
        }
    }

    tmp = head;
    while (head) //wiemy że head wskazuje na cos co nie jest nullem wiec sprawdzamy czy nie trzeba czegos usunąć
    {
        if (tmp->node == NULL)
        {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            List *oldtmp = tmp;
            if (oldtmp == ptr)
            {
                ptr = tmp->next;
            }
            tmp = tmp->prev;
            delete oldtmp;
        }

        if (tmp->next == head)
        {
            break;
        }

        tmp = tmp->next;
    }
}

void print(List *head)
{
    List *tmp = head;
    while (1)
    {
        printf("%s ", tmp->node->name);

        if (tmp->next == head)
        {
            break;
        }
        tmp = tmp->next;
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    int n;
    scanf("%d", &n);
    List *head = new List;
    head->next = head;
    head->prev = head;
    List *last = head;

    for (int i = 1; i < n; i++)
    {
        List *tmp = new List;
        last->next = tmp;
        tmp->prev = last;
        tmp->next = head;
        head->prev = tmp;
        last = tmp;
    }

    List *tmp = head;
    for (int i = 0; i < n; i++)
    {
        int m;
        scanf("%d", &m);
        Node *nodehead = new Node;
        scanf("%s%d", nodehead->name, &nodehead->size);
        nodehead->next = nodehead;
        nodehead->prev = nodehead;
        Node *nodelast = nodehead;
        tmp->node = nodehead;
        for (int j = 1; j < m; j++)
        {
            Node *nodetmp = new Node;
            scanf("%s%d", nodetmp->name, &nodetmp->size);
            nodelast->next = nodetmp;
            nodetmp->prev = nodelast;
            nodetmp->next = nodehead;
            nodehead->prev = nodetmp;
            nodelast = nodetmp;
        }
        tmp = tmp->next;
    }

    int l;
    int max = -1;

    scanf("%d", &l);
    int *rabaty = new int[l];

    for (int i = 0; i < l; i++)
    {
        scanf("%d", &rabaty[i]);
    }

    mergesort(rabaty, 0, l - 1);

    List *ptr = head;

    int h;
    scanf("%d", &h);

    int wczytan = 0;

    int suma = sumCount(head);
    while (head)
    {
        if (l <= 0)
        {
            break;
        }
        int idx = find(rabaty, l, suma);
        if (idx != -1)
        {
            printf("%d ", suma);
            print(head);
            shift(head, ptr);
            if (!head)
            {
                break;
            }
            remove(rabaty, l, idx);
            suma = sumCount(head);
        }
        else
        {
            int x, y;
            if (wczytan++ >= h)
            {
                break;
            }
            scanf("%d%d", &x, &y);
            int oldrozmiar;
            move(ptr, x, y, oldrozmiar);
            suma = suma - oldrozmiar + ptr->node->size;
        }
    }

    while (head)
    {
        shift(head, ptr);
    }

    delete[] rabaty;

    return 0;
}