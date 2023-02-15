#include <stdio.h>
#include <time.h>

#include "list.h"

void testListInt(void);
void testListDouble(void);

int main(void)
{
    int i;
    long cpu_time1, cpu_time2;
    for (i = 0; i < 10000; i++) {
        testListInt();
    }
    cpu_time1 = clock();
    printf("<ListInt>\n");
    printf("  cpu time: %ld\n", cpu_time1);
    for (i = 0; i < 10000; i++) {
        testListDouble();
    }
    cpu_time2 = clock();
    printf("<ListInt>\n");
    printf("  cpu time: %ld\n", cpu_time2 - cpu_time1);
    return 0;
}

void testListInt(void)
{
    int i;
    ListInt list;
    initListInt(&list);
    for (i = 0; i < 10000; i++)
    {
        addListInt(&list, i, LIST_END);
    }
    for (i = 0; i < 10000; i++)
    {
        removeListInt(&list, LIST_END);
    }
    freeListInt(&list);
    return;
}

void testListDouble(void)
{
    int i;
    ListDouble list;
    initListDouble(&list);
    for (i = 0; i < 10000; i++)
    {
        addListDouble(&list, i, LIST_END);
    }
    for (i = 0; i < 10000; i++)
    {
        removeListDouble(&list, LIST_END);
    }
    freeListDouble(&list);
}