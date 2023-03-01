#include <time.h>
#include <sys/time.h>

#include "list.h"

void sort_test(void);

int main(void)
{
    sort_test();
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

void sort_test(void)
{
    srand((unsigned int)time(NULL));
    const int num = 1000000;
    struct timeval _time;
    int i;
    double start, end;
    List list;
    ///----- sort int data -----///
    printf("----- sort int data -----\n");
    int *arr_int;
    if ((arr_int = (int *)malloc(num * sizeof(int))) == NULL)
    {
        exit(EX_OSERR);
    }
    for (i = 0; i < num; i++)
    {
        arr_int[i] = rand();
    }
    asList_List(&list, arr_int, num, sizeof(int), false);
    gettimeofday(&_time, NULL);
    start = _time.tv_sec + _time.tv_usec * 0.000001;
    qsort(arr_int, num, sizeof(int), cmp_int);
    gettimeofday(&_time, NULL);
    end = _time.tv_sec + _time.tv_usec * 0.000001;
    printf("time1: %f\n", end - start);
    gettimeofday(&_time, NULL);
    start = _time.tv_sec + _time.tv_usec * 0.000001;
    qsort_List(&list, 0, num, cmp_int);
    gettimeofday(&_time, NULL);
    end = _time.tv_sec + _time.tv_usec * 0.000001;
    printf("time2: %f\n", end - start);
    free(arr_int);
    free_List(&list);
    ///----- sort double data -----///
    printf("----- sort double data -----\n");
    double *arr_double;
    if ((arr_double = (double *)malloc(num * sizeof(double))) == NULL)
    {
        exit(EX_OSERR);
    }
    for (i = 0; i < num; i++)
    {
        arr_double[i] = rand() * 0.000001;
    }
    asList_List(&list, arr_double, num, sizeof(double), false);
    gettimeofday(&_time, NULL);
    start = _time.tv_sec + _time.tv_usec * 0.000001;
    qsort(arr_double, num, sizeof(double), cmp_double);
    gettimeofday(&_time, NULL);
    end = _time.tv_sec + _time.tv_usec * 0.000001;
    printf("time1: %f\n", end - start);
    gettimeofday(&_time, NULL);
    start = _time.tv_sec + _time.tv_usec * 0.000001;
    qsort_List(&list, 0, num, cmp_double);
    gettimeofday(&_time, NULL);
    end = _time.tv_sec + _time.tv_usec * 0.000001;
    printf("time2: %f\n", end - start);
    free(arr_double);
    free_List(&list);
    return;
}