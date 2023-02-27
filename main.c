#include <time.h>

#include "list.h"

void testListInt(void);
void testListDouble(void);
void testListString(void);
void testSort(void);

int main(void)
{
    testListInt();
    printf("----------\n");
    testListDouble();
    printf("----------\n");
    testListString();
    return 0;
}

void testListInt(void)
{
    int tmp, i;
    int num = 8;
    List list;
    init_List(&list, sizeof(int), false);
    for (i = 0; i < num; i++)
    {
        push_List(&list, &i);
    }
    tmp = 16;
    set_List(&list, &tmp, 3);
    tmp = 1024;
    add_List(&list, &tmp, 4);
    remove_List(&list, 1);
    printf("pop_List() = %d\n", *(int *)pop_List(&list));
    printf("[");
    for (i = 0; i < list.size; i++)
    {
        tmp = *(int *)get_List(&list, i);
        printf("%d", tmp);
        if (i != list.size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    printf("peek_List() = %d\n", *(int *)peek_List(&list));
    free_List(&list);
}
void testListDouble(void)
{
    int i;
    int num = 8;
    double tmp;
    List list;
    init_List(&list, sizeof(double), false);
    for (i = 0; i < num; i++)
    {
        tmp = i * 0.1;
        push_List(&list, &tmp);
    }
    tmp = 3.14;
    set_List(&list, &tmp, 3);
    tmp = 2.71;
    add_List(&list, &tmp, 4);
    remove_List(&list, 1);
    printf("pop_List() = %f\n", *(double *)pop_List(&list));
    printf("[");
    for (i = 0; i < list.size; i++)
    {
        tmp = *(double *)get_List(&list, i);
        printf("%f", tmp);
        if (i != list.size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    printf("peek_List() = %f\n", *(double *)peek_List(&list));
    free_List(&list);
}
void testListString(void)
{
    int i;
    int num = 8;
    char *tmp = malloc(16);
    List list;
    init_List(&list, sizeof(char *), true);
    for (i = 0; i < num; i++)
    {
        strcpy(tmp, "0abc");
        tmp[0] += i;
        push_List(&list, tmp);
    }
    set_List(&list, "foo", 3);
    add_List(&list, "bar", 4);
    remove_List(&list, 1);
    printf("pop_List() = %s\n", (char *)pop_List(&list));
    printf("[");
    for (i = 0; i < list.size; i++)
    {
        tmp = (char *)get_List(&list, i);
        printf("%s", tmp);
        if (i != list.size - 1)
        {
            printf(", ");
        }
        if (i % 16 == 15)
        {
            printf("\n");
        }
    }
    printf("]\n");
    printf("peek_List() = %s\n", (char *)peek_List(&list));
    free_List(&list);
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
    long cpu_time1, cpu_time2, num = 50000;
    int *array_int;
    if ((array_int = (int *)malloc(num * sizeof(int))) == NULL)
    {
        return;
    }
    for (i = 0; i < num; i++)
    {
        array_int[i] = rand();
    }
    cpu_time1 = clock();
    qsort(array_int, num, sizeof(int), cmp_int);
    cpu_time2 = clock();
    free(array_int);
    printf("<sort ArrayInt>\n");
    printf("  cpu time: %ld\n", (cpu_time2 - cpu_time1));
    double *array_double;
    if ((array_double = (double *)malloc(num * sizeof(double))) == NULL)
    {
        return;
    }
    for (i = 0; i < num; i++)
    {
        array_double[i] = rand() * 0.000001;
    }
    cpu_time1 = clock();
    qsort(array_double, num, sizeof(double), cmp_double);
    cpu_time2 = clock();
    free(array_double);
    printf("<sort ArrayDouble>\n");
    printf("  cpu time: %ld\n", (cpu_time2 - cpu_time1));
    return;
}
void testSortList(void)
{
    srand((unsigned int)time(NULL));
    int i;
    long cpu_time1, cpu_time2, num = 50000;
    ListInt list_int;
    init_ListInt(&list_int);
    for (i = 0; i < num; i++)
    {
        push_ListInt(&list_int, rand());
    }
    cpu_time1 = clock();
    qsort_ListInt(&list_int, 0, list_int.size - 1, ACS_SORT);
    cpu_time2 = clock();
    free_ListInt(&list_int);
    printf("<sort ListInt>\n");
    printf("  cpu time: %ld\n", (cpu_time2 - cpu_time1));
    ListDouble list_double;
    init_ListDouble(&list_double);
    for (i = 0; i < num; i++)
    {
        push_ListDouble(&list_double, rand() * 0.000001);
    }
    cpu_time1 = clock();
    qsort_ListDouble(&list_double, 0, list_double.size - 1, ACS_SORT);
    cpu_time2 = clock();
    free_ListDouble(&list_double);
    printf("<sort ListDouble>\n");
    printf("  cpu time: %ld\n", (cpu_time2 - cpu_time1));
    ListString list_string;
    init_ListString(&list_string);
    inputFile_ListString(&list_string, "VDRJ_Ver1_1_Research_Top60894.txt", NULL, LINE_SPLIT_TRUE);
    cpu_time1 = clock();
    qsort_ListString(&list_string, 0, list_string.size - 1, ACS_SORT);
    cpu_time2 = clock();
    free_ListString(&list_string);
    printf("<sort ListString>\n");
    printf("  cpu time: %ld\n", (cpu_time2 - cpu_time1));
    return;
}
void testSort(void)
{
    testSortArray();
    testSortList();
    return;
}