#include <time.h>

#include "list.h"

void testListInt(void);
void testListDouble(void);
void testListString(void);
void testSort(void);

int main(void)
{
    // testListInt();
    // testListDouble();
    // testListString();
    testSort();
    return 0;
}

void testListInt(void)
{
    srand((unsigned int)time(NULL));
    int i;
    long num = 100;
    ListInt list;
    init_ListInt(&list);
    int *array;
    if ((array = (int *)malloc(num * sizeof(int))) == NULL)
    {
        return;
    }
    for (i = 0; i < num; i++)
    {
        array[i] = rand() % 100;
    }
    printf("asList_ListInt\n");
    asList_ListInt(&list, array, num);
    show_ListInt(&list);

    printf("\nqsort_ListInt\n");
    qsort_ListInt(&list, 0, list.size - 1, ACS_SORT);
    show_ListInt(&list);
    free_ListInt(&list);

    init_ListInt(&list);
    printf("\npush_ListInt\n");
    for (i = 0; i < num; i++)
    {
        push_ListInt(&list, i);
    }
    show_ListInt(&list);

    printf("\nadd_ListInt\n");
    add_ListInt(&list, 1024, 10);
    show_ListInt(&list);

    printf("\nremove_ListInt\n");
    remove_ListInt(&list, 10);
    show_ListInt(&list);

    printf("\nset_ListInt\n");
    set_ListInt(&list, -1, 10);
    show_ListInt(&list);

    printf("\nindexOf_ListInt(99) = %ld\n", indexOf_ListInt(&list, 99));
    printf("\nindexOf_ListInt(1024) = %ld\n", indexOf_ListInt(&list, 1024));
    printf("\nget_ListInt(50) = %d\n", get_ListInt(&list, 50));
    printf("\npeek_ListInt() = %d\n", peek_ListInt(&list));
    show_ListInt(&list);
    printf("\npop_ListInt() = %d\n", pop_ListInt(&list));
    show_ListInt(&list);

    free_ListInt(&list);
}
void testListDouble(void)
{
    srand((unsigned int)time(NULL));
    int i;
    long num = 100;
    ListDouble list;
    init_ListDouble(&list);
    double *array;
    if ((array = (double *)malloc(num * sizeof(double))) == NULL)
    {
        return;
    }
    for (i = 0; i < num; i++)
    {
        array[i] = rand() % 10000 * 0.01;
    }
    printf("asList_ListDouble\n");
    asList_ListDouble(&list, array, num);
    show_ListDouble(&list);

    printf("\nqsort_ListDouble\n");
    qsort_ListDouble(&list, 0, list.size - 1, ACS_SORT);
    show_ListDouble(&list);
    free_ListDouble(&list);

    init_ListDouble(&list);
    printf("\npush_ListDouble\n");
    for (i = 0; i < num; i++)
    {
        push_ListDouble(&list, i * 0.1);
    }
    show_ListDouble(&list);

    printf("\nadd_ListDouble\n");
    add_ListDouble(&list, 1.024, 10);
    show_ListDouble(&list);

    printf("\nremove_ListDouble\n");
    remove_ListDouble(&list, 10);
    show_ListDouble(&list);

    printf("\nset_ListDouble\n");
    set_ListDouble(&list, -0.1, 10);
    show_ListDouble(&list);

    printf("\nindexOf_ListDouble(9.9) = %ld\n", indexOf_ListDouble(&list, 9.9));
    printf("\nindexOf_ListDouble(1024) = %ld\n", indexOf_ListDouble(&list, 1024));
    printf("\nget_ListDouble(50) = %f\n", get_ListDouble(&list, 50));
    printf("\npeek_ListDouble() = %f\n", peek_ListDouble(&list));
    show_ListDouble(&list);
    printf("\npop_ListDouble() = %f\n", pop_ListDouble(&list));
    show_ListDouble(&list);

    free_ListDouble(&list);
}
void testListString(void)
{
    ListString list;
    {
        inputFile_ListString(&list, "VDRJ_Ver1_1_Research_Top60894.txt", NULL, LINE_SPLIT_TRUE);

        printf("\nget_ListString(0) = %s\n", get_ListString(&list, 0));
        printf("  size: %ld, allocated: %ld\n", list.size, list.allocated);

        printf("\nset_ListString(0, \"東京都　２３区\")\n");
        set_ListString(&list, "東京都　２３区", 0);
        printf("get_ListString(0) = %s\n", get_ListString(&list, 0));
        printf("  size: %ld, allocated: %ld\n", list.size, list.allocated);

        printf("\nremove_ListString(0)\n");
        remove_ListString(&list, 0);
        printf("get_ListString(0) = %s\n", get_ListString(&list, 0));
        printf("  size: %ld, allocated: %ld\n", list.size, list.allocated);

        printf("\npush_ListString(\"大阪府　大阪市\")\n");
        push_ListString(&list, "大阪府　大阪市");
        printf("  size: %ld, allocated: %ld\n", list.size, list.allocated);

        printf("\npeek_ListString() = %s\n", peek_ListString(&list));
        printf("  size: %ld, allocated: %ld\n", list.size, list.allocated);

        printf("\npop_ListString() = %s\n", pop_ListString(&list));
        printf("  size: %ld, allocated: %ld\n", list.size, list.allocated);

        qsort_ListString(&list, 0, list.size - 1, ACS_SORT);

        free_ListString(&list);
    }

    {
        inputFile_ListString(&list, "paper.txt", NULL, LINE_SPLIT_TRUE);
        free_ListString(&list);
    }
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