#include <time.h>

#include "list.h"

void testSort(void);

int main(void)
{
    testSort();
    return 0;
}

int cmp_int(const void *_x, const void *_y)
{
    if (*(int *)_y < *(int *)_x)
    {
        return 1;
    }
    else if (*(int *)_x < *(int *)_y)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
int cmp_double(const void *_x, const void *_y)
{
    if (*(double *)_y < *(double *)_x)
    {
        return 1;
    }
    else if (*(double *)_x < *(double *)_y)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
void testSortArray(void)
{
    srand((unsigned int)time(NULL));
    int i;
    long cpu_time1, cpu_time2;
    size_t num = 100000;
    int *list_int;
    if ((list_int = (int *)malloc(num * sizeof(int))) == NULL)
    {
        return;
    }
    for (i = 0; i < num; i++)
    {
        list_int[i] = rand();
    }
    cpu_time1 = clock();
    qsort(list_int, num, sizeof(int), cmp_int);
    cpu_time2 = clock();
    free(list_int);
    printf("<sort ArrayInt>\n");
    printf("  cpu time: %ld\n", (cpu_time2 - cpu_time1));
    double *list_double;
    if ((list_double = (double *)malloc(num * sizeof(double))) == NULL)
    {
        return;
    }
    for (i = 0; i < num; i++)
    {
        list_double[i] = rand() * 0.000001;
    }
    cpu_time1 = clock();
    qsort(list_double, num, sizeof(double), cmp_double);
    cpu_time2 = clock();
    free(list_double);
    printf("<sort ArrayDouble>\n");
    printf("  cpu time: %ld\n", (cpu_time2 - cpu_time1));
    return;
}
void testSortList(void)
{
    srand((unsigned int)time(NULL));
    int i;
    long cpu_time1, cpu_time2;
    ListInt list_int;
    initListInt(&list_int);
    for (i = 0; i < 100000; i++)
    {
        pushListInt(&list_int, rand());
    }
    cpu_time1 = clock();
    qsortListInt(&list_int, 0, list_int.size - 1, ACS_SORT);
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
    qsortListDouble(&list_double, 0, list_double.size - 1, ACS_SORT);
    cpu_time2 = clock();
    freeListDouble(&list_double);
    printf("<sort ListDouble>\n");
    printf("  cpu time: %ld\n", (cpu_time2 - cpu_time1));
    return;
}
void testSort(void)
{
    testSortArray();
    testSortList();
    return;
}