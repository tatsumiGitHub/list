#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "list.h"

void debugSort(void);
void debugTime(void);

int main(void)
{
    debugSort();
    //debugTime();
    return 0;
}

void debugSort(void)
{
    srand((unsigned int)time(NULL));
    int i;
    long cpu_time1, cpu_time2;
    ListInt list_int;
    initListInt(&list_int);
    for (i = 0; i < 100000; i++)
    {
        pushListInt(&list_int, rand() % 1000000);
    }
    cpu_time1 = clock();
    qsortListInt(&list_int, ACS_SORT);
    cpu_time2 = clock();
    freeListInt(&list_int);
    printf("<sort ListInt>\n");
    printf("  cpu time: %ld\n", (cpu_time2 - cpu_time1));
    ListDouble list_double;
    initListDouble(&list_double);
    for (i = 0; i < 100000; i++)
    {
        pushListDouble(&list_double, rand() * 0.000001);
    }
    cpu_time1 = clock();
    qsortListDouble(&list_double, ACS_SORT);
    cpu_time2 = clock();
    printf("<sort ListInt>\n");
    printf("  cpu time: %ld\n", (cpu_time2 - cpu_time1));
    freeListDouble(&list_double);
    return;
}

void debugTime(void)
{
    int i, j;
    ListInt list_int;
    ListDouble list_double;
    long cpu_time1, cpu_time2;
    cpu_time1 = clock();
    for (i = 0; i < 10000; i++)
    {
        initListInt(&list_int);
        for (j = 0; j < 10000; j++)
        {
            addListInt(&list_int, j, LIST_END);
        }
        for (j = 0; j < 10000; j++)
        {
            removeListInt(&list_int, LIST_END);
        }
        freeListInt(&list_int);
    }
    cpu_time2 = clock();
    printf("<ListInt>\n");
    printf("  cpu time: %f\n", (cpu_time2 - cpu_time1) * 0.0001);
    for (i = 0; i < 10000; i++)
    {
        initListDouble(&list_double);
        for (j = 0; j < 10000; j++)
        {
            addListDouble(&list_double, j, LIST_END);
        }
        for (j = 0; j < 10000; j++)
        {
            removeListDouble(&list_double, LIST_END);
        }
        freeListDouble(&list_double);
    }
    cpu_time2 = clock();
    printf("<ListDouble>\n");
    printf("  cpu time: %f\n", (cpu_time2 - cpu_time1) * 0.0001);
    return;
}