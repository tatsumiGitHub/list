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
    srand((unsigned int)time(NULL));
    int i;
    int num = 8;
    List list, list_copy;
    int *array;
    if ((array = (int *)malloc(num * sizeof(int))) == NULL)
    {
        return;
    }
    for (i = 0; i < num; i++)
    {
        array[i] = i;
    }
    asList_List(&list, array, num, sizeof(int), false);
    copy_List(&list_copy, &list);
    int tmp = *(int *)get_List(&list, num / 2);
    printf("get_List(%d) = %d\n", num / 2, tmp);
    tmp = 1024;
    set_List(&list, &tmp, num / 2);
    tmp = *(int *)get_List(&list, num / 2);
    printf("get_List(%d) = %d\n", num / 2, tmp);
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
    tmp = 16;
    add_List(&list, &tmp, 4);
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
    remove_List(&list, 3);
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
    free(array);
    free_List(&list);
    free_List(&list_copy);
}
void testListDouble(void)
{
    srand((unsigned int)time(NULL));
    int i;
    int num = 8;
    List list, list_copy;
    double *array;
    if ((array = (double *)malloc(num * sizeof(double))) == NULL)
    {
        return;
    }
    for (i = 0; i < num; i++)
    {
        array[i] = i * 0.1;
    }
    asList_List(&list, array, num, sizeof(double), false);
    copy_List(&list_copy, &list);
    double tmp = *(double *)get_List(&list, num / 2);
    printf("get_List(%d) = %f\n", num / 2, tmp);
    tmp = 3.14;
    set_List(&list, &tmp, num / 2);
    tmp = *(double *)get_List(&list, num / 2);
    printf("get_List(%d) = %f\n", num / 2, tmp);
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
    tmp = 2.71;
    add_List(&list, &tmp, 4);
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
    remove_List(&list, 3);
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
    free(array);
    free_List(&list);
    free_List(&list_copy);
}
void testListString(void)
{
    int i;
    int num = 128;
    List list;
    init_List(&list, sizeof(char *), true);
    for (i = 0; i < num; i++)
    {
        add_List(&list, "ab", list.size);
    }
    char *tmp = (char *)get_List(&list, num / 2);
    set_List(&list, "foo", num / 2);
    add_List(&list, "hoge", num / 2);
    remove_List(&list, list.size - 1);
    remove_List(&list, list.size - 1);
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