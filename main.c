#include <time.h>

#include "list.h"

void testListInt(void);
void testListDouble(void);
void testListString(void);

int main(void)
{
    testListInt();
    printf("----------\n");
    testListDouble();
    printf("----------\n");
    testListString();
    return 0;
}

int cmp_int(const void *_x, const void *_y)
{
    return *(int *)_x - *(int *)_y;
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
int cmp_str(const void *_str1, const void *_str2)
{
    return strcmp(*(char **)_str1, *(char **)_str2);
}

void testListInt(void)
{
    srand((unsigned int)time(NULL));
    int tmp, i;
    int num = 8;
    List list;
    init_List(&list, sizeof(int), false);
    for (i = 0; i < num; i++)
    {
        tmp = (rand() % 100) * (i % 2 == 0 ? 1 : -1);
        push_List(&list, &tmp);
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
        printf("%d", *(int *)get_List(&list, i));
        if (i != list.size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    printf("peek_List() = %d\n", *(int *)peek_List(&list));
    qsort_List(&list, 0, list.size - 1, cmp_int);
    printf("[");
    for (i = 0; i < list.size; i++)
    {
        printf("%d", *(int *)get_List(&list, i));
        if (i != list.size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    free_List(&list);
}
void testListDouble(void)
{
    srand((unsigned int)time(NULL));
    int i;
    int num = 8;
    double tmp;
    List list;
    init_List(&list, sizeof(double), false);
    for (i = 0; i < num; i++)
    {
        tmp = rand() * 0.0000001 * (i % 2 == 0 ? 1 : -1);
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
        printf("%f", *(double *)get_List(&list, i));
        if (i != list.size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
    printf("peek_List() = %f\n", *(double *)peek_List(&list));
    qsort_List(&list, 0, list.size - 1, cmp_double);
    printf("[");
    for (i = 0; i < list.size; i++)
    {
        printf("%f", *(double *)get_List(&list, i));
        if (i != list.size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
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
        printf("%s", (char *)get_List(&list, i));
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
    qsort_List(&list, 0, list.size - 1, cmp_str);
    printf("[");
    for (i = 0; i < list.size; i++)
    {
        printf("%s", (char *)get_List(&list, i));
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
    inputFile_List(&list, "VDRJ_Ver1_1_Research_Top60894.csv", NULL, LINE_SPLIT_TRUE);
    printf("----------\n");
    printf("file name: VDRJ_Ver1_1_Research_Top60894.csv\n");
    printf("     size: %ld\n", list.size);
    printf("allocated: %ld\n", list.allocated);
    free_List(&list);
}