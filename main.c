#include <time.h>

#include "list.h"

void debugTime(void);
void testListInt(void);
void testListDouble(void);

int main(void)
{
    debugTime();
    return 0;
}

void debugTime(void)
{
    int i;
    long cpu_time1, cpu_time2;
    cpu_time1 = clock();
    for (i = 0; i < 10000; i++) {
        testListInt();
    }
    cpu_time2 = clock();
    printf("<ListInt>\n");
    printf("  cpu time: %f\n", (cpu_time2 - cpu_time1) * 0.0001);
    for (i = 0; i < 10000; i++) {
        testListDouble();
    }
    cpu_time2 = clock();
    printf("<ListDouble>\n");
    printf("  cpu time: %f\n", (cpu_time2 - cpu_time1) * 0.0001);
    return;
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