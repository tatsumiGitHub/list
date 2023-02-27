#include "list.h"

void init_List(List *_list, const int _data_size, const bool _is_string)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"init_List(List *_list, const int _data_size, const bool _is_string)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    _list->size = 0;
    if (_is_string == true)
    {
        _list->is_string = true;
        _list->data_size = sizeof(char *);
    }
    else
    {
        _list->is_string = false;
        _list->data_size = _data_size;
    }
    _list->capacity = _list->data_size * LIST_BUF_SIZE;
    _list->allocated = 0;
    if ((_list->base_addr = (void *)malloc(_list->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    return;
}
void asList_List(List *_list, const void *_array, const long _size, const long _data_size, const int _is_string)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"asList_List(List *_list, const void *_array, const long _size, const long _data_size, const int _is_string)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_array == NULL)
    {
        printf("Error: Cannot invoke \"asList_List(List *_list, const void *_array, const long _size, const long _data_size, const int _is_string)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    _list->is_string = _is_string;
    _list->size = _size;
    if (_list->is_string == true)
    {
        _list->data_size = sizeof(char *);
    }
    else
    {
        _list->data_size = _data_size;
    }
    _list->capacity = (_size / LIST_BUF_SIZE + 1) * LIST_BUF_SIZE * _list->data_size;
    _list->allocated = 0;
    if (_list->is_string == true)
    {
        long i;
        char *str_tmp;
        if ((_list->base_addr = (char **)malloc(_list->capacity)) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        for (i = 0; i < _size; i++)
        {
            str_tmp = *((char **)_array + i);
            if ((*((char **)_list->base_addr + i) = (char *)calloc((strlen(str_tmp) + 1), sizeof(char))) == NULL)
            {
                printf("Error: unable to allocate new heap space\n");
                exit(EX_OSERR);
            }
            strcpy(*((char **)_list->base_addr + i), str_tmp);
            _list->allocated += strlen(str_tmp) + 1;
        }
    }
    else
    {
        if ((_list->base_addr = (void *)malloc(_list->capacity)) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        memcpy(_list->base_addr, _array, _size * _data_size);
    }
    return;
}
void free_List(List *_list)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"free_List(List *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->is_string == true)
    {
        int i;
        for (i = 0; i < _list->size; i++)
        {
            free(*((char **)_list->base_addr + i));
        }
    }
    _list->is_string = false;
    _list->size = 0;
    _list->data_size = 0;
    _list->capacity = 0;
    _list->allocated = 0;
    free(_list->base_addr);
    _list->base_addr = NULL;
    return;
}
void copy_List(List *_list_dst, const List *_list_src)
{
    if (_list_dst == NULL)
    {
        printf("Error: Cannot invoke \"copy_List(List *_list_dst, const List *_list_src)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list_src == NULL)
    {
        printf("Error: Cannot invoke \"copy_List(List *_list_dst, const List *_list_src)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    _list_dst->is_string = _list_src->is_string;
    _list_dst->size = _list_src->size;
    _list_dst->data_size = _list_src->data_size;
    _list_dst->capacity = _list_src->capacity;
    _list_dst->allocated = _list_src->allocated;
    if ((_list_dst->base_addr = (void *)malloc(_list_dst->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    if (_list_dst->is_string == true)
    {
        long i;
        char *str_tmp;
        if ((_list_dst->base_addr = (char **)malloc(_list_dst->capacity)) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        for (i = 0; i < _list_dst->size; i++)
        {
            str_tmp = *((char **)_list_src->base_addr + i);
            if ((*((char **)_list_dst->base_addr + i) = (char *)calloc((strlen(str_tmp) + 1), sizeof(char))) == NULL)
            {
                printf("Error: unable to allocate new heap space\n");
                exit(EX_OSERR);
            }
            strcpy(*((char **)_list_dst->base_addr + i), str_tmp);
        }
    }
    else
    {
        memcpy(_list_dst->base_addr, _list_src->base_addr, _list_dst->capacity);
        _list_dst->allocated = _list_src->allocated;
    }
    return;
}
void *get_List(const List *_list, const long _idx)
{
    static void *return_ptr = NULL;
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"get_List(const List *_list, const long _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size < _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    if (_list->is_string == true)
    {
        char *str_ptr = *((char **)_list->base_addr + _idx);
        if ((return_ptr = (char *)realloc(return_ptr, (strlen(str_ptr) + 1))) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        strcpy(return_ptr, str_ptr);
        *((char *)return_ptr + strlen(return_ptr)) = '\0';
    }
    else
    {
        if ((return_ptr = realloc(return_ptr, _list->data_size)) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        memcpy(return_ptr, (_list->base_addr + _idx * _list->data_size), _list->data_size);
    }
    return return_ptr;
}
void set_List(List *_list, const void *_elements, const long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"set_List(List *_list, const void *_elements, const long _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_elements == NULL)
    {
        printf("Error: Cannot invoke \"set_List(List *_list, const void *_elements, const long _idx)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size < _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    void *tmp;
    if (_list->is_string == true)
    {
        _list->allocated -= strlen(*((char **)_list->base_addr + _idx));
        if ((tmp = (char *)realloc(*((char **)_list->base_addr + _idx), (strlen(_elements) + 1) * sizeof(char))) == NULL)
        {
            free(*((char **)_list->base_addr + _idx));
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            *((char **)_list->base_addr + _idx) = tmp;
        }
        _list->allocated += strlen(_elements);
        strcpy(*((char **)_list->base_addr + _idx), _elements);
        *((char *)*((char **)_list->base_addr + _idx) + strlen(_elements)) = '\0';
    }
    else
    {
        memmove((_list->base_addr + _idx * _list->data_size), _elements, _list->data_size);
    }
    return;
}
void add_List(List *_list, const void *_elements, const long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"add_List(List *_list, const void *_elements, const long _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_elements == NULL)
    {
        printf("Error: Cannot invoke \"add_List(List *_list, const void *_elements, const long _idx)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size < _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    if (_list->capacity <= _list->size * _list->data_size)
    {
        void *tmp;
        _list->capacity += LIST_BUF_SIZE * _list->data_size;
        if ((tmp = (void *)realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    memmove((_list->base_addr + (_idx + 1) * _list->data_size), (_list->base_addr + _idx * _list->data_size), (_list->size - _idx) * _list->data_size);
    if (_list->is_string == true)
    {
        if ((*((char **)_list->base_addr + _idx) = (char *)calloc((strlen(_elements) + 1), sizeof(char))) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        _list->allocated += strlen(_elements) + 1;
        strcpy(*((char **)_list->base_addr + _idx), _elements);
    }
    else
    {
        memmove((_list->base_addr + _idx * _list->data_size), _elements, _list->data_size);
    }
    _list->size++;
    return;
}
void remove_List(List *_list, const long _idx)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"remove_List(List *_list, const long _idx)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_idx < 0 || _list->size <= _idx)
    {
        printf("Error: Index %ld out of bounds for length %ld\n", _idx, _list->size);
        exit(EX_USAGE);
    }
    if (_list->is_string == true)
    {
        _list->allocated -= strlen(*((char **)_list->base_addr + _idx)) + 1;
        free(*((char **)_list->base_addr + _idx));
    }
    memmove((_list->base_addr + _idx * _list->data_size), (_list->base_addr + (_idx + 1) * _list->data_size), (_list->size - _idx) * _list->data_size);
    _list->size--;
    if (LIST_BUF_SIZE * _list->data_size < _list->capacity && _list->size * _list->data_size + LIST_BUF_SIZE * _list->data_size < _list->capacity)
    {
        void *tmp;
        _list->capacity -= LIST_BUF_SIZE * _list->data_size;
        if ((tmp = realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    return;
}
void push_List(List *_list, const void *_elements)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"push_List(List *_list, const void *_elements)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_elements == NULL)
    {
        printf("Error: Cannot invoke \"push_List(List *_list, const void *_elements)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->capacity <= _list->size * _list->data_size)
    {
        void *tmp;
        _list->capacity += LIST_BUF_SIZE * _list->data_size;
        if ((tmp = (void *)realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    if (_list->is_string == true)
    {
        if ((*((char **)_list->base_addr + _list->size) = (char *)calloc((strlen(_elements) + 1), sizeof(char))) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        _list->allocated += strlen(_elements) + 1;
        strcpy(*((char **)_list->base_addr + _list->size), _elements);
    }
    else
    {
        memmove((_list->base_addr + _list->size * _list->data_size), _elements, _list->data_size);
    }
    _list->size++;
    return;
}
void *peek_List(const List *_list)
{
    static void *return_ptr = NULL;
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"peek_List(const List *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->size == 0)
    {
        printf("Error: Index 0 out of bounds for length %ld\n", _list->size);
        exit(EX_USAGE);
    }
    if (_list->is_string == true)
    {
        char *str_ptr = *((char **)_list->base_addr + _list->size - 1);
        if ((return_ptr = (char *)realloc(return_ptr, (strlen(str_ptr) + 1))) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        strcpy(return_ptr, str_ptr);
    }
    else
    {
        if ((return_ptr = realloc(return_ptr, _list->data_size)) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        memcpy(return_ptr, (_list->base_addr + (_list->size - 1) * _list->data_size), _list->data_size);
    }
    return return_ptr;
}
void *pop_List(List *_list)
{
    static void *return_ptr = NULL;
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"pop_List(List *_list)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_list->size == 0)
    {
        printf("Error: Index 0 out of bounds for length %ld\n", _list->size);
        exit(EX_USAGE);
    }
    if (_list->is_string == true)
    {
        char *str_ptr = *((char **)_list->base_addr + _list->size - 1);
        if ((return_ptr = (char *)realloc(return_ptr, (strlen(str_ptr) + 1))) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        strcpy(return_ptr, str_ptr);
        _list->allocated -= strlen(*((char **)_list->base_addr + _list->size - 1)) + 1;
        free(*((char **)_list->base_addr + _list->size - 1));
    }
    else
    {
        if ((return_ptr = realloc(return_ptr, _list->data_size)) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        memcpy(return_ptr, (_list->base_addr + (_list->size - 1) * _list->data_size), _list->data_size);
    }
    _list->size--;
    if (LIST_BUF_SIZE * _list->data_size < _list->capacity && _list->size * _list->data_size + LIST_BUF_SIZE * _list->data_size < _list->capacity)
    {
        void *tmp;
        _list->capacity -= LIST_BUF_SIZE * _list->data_size;
        if ((tmp = realloc(_list->base_addr, _list->capacity)) == NULL)
        {
            free(_list->base_addr);
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
        else
        {
            _list->base_addr = tmp;
        }
    }
    return return_ptr;
}
void qsort_List(List *_list, const long _left, const long _right, int (*_compare)(const void *, const void *))
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"qsort_List(List *_list, const long _left, const long _right, int (*compare)(const void *, const void *))\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_compare == NULL)
    {
        printf("Error: Cannot invoke \"qsort_List(List *_list, const long _left, const long _right, int (*compare)(const void *, const void *))\" because \"<local4>\" is null\n");
        exit(EX_USAGE);
    }
    void *ptr_tmp, *cpy_tmp = NULL;
    void *pivot;
    long i, j, k, left, right, max_len = -1;
    List left_list, right_list;
    init_List(&left_list, sizeof(long), false);
    init_List(&right_list, sizeof(long), false);
    push_List(&left_list, &_left);
    push_List(&right_list, &_right);

    if (_list->is_string == true)
    {
        for (i = 0; i < _list->size; i++)
        {
            if (max_len < (long)strlen(*((char **)_list->base_addr + i)))
            {
                max_len = (long)strlen(*((char **)_list->base_addr + i));
            }
        }
        if ((cpy_tmp = (char *)calloc(max_len + 1, sizeof(char))) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
    }
    else
    {
        if ((cpy_tmp = malloc(_list->data_size)) == NULL)
        {
            printf("Error: unable to allocate new heap space\n");
            exit(EX_OSERR);
        }
    }
    while (left_list.size != 0 && right_list.size != 0)
    {
        left = *(long *)pop_List(&left_list);
        right = *(long *)pop_List(&right_list);
        i = left;
        j = right;
        pivot = _list->base_addr + ((i + j) / 2) * _list->data_size;
        while (1)
        {
            while (_compare(_list->base_addr + i * _list->data_size, pivot) < 0)
            {
                i++;
            }
            while (0 < _compare(_list->base_addr + j * _list->data_size, pivot))
            {
                j--;
            }
            if (j <= i)
            {
                break;
            }

            if (_list->is_string == true)
            {
                strcpy(cpy_tmp, *((char **)_list->base_addr + i));
                if ((ptr_tmp = (char *)realloc(*((char **)_list->base_addr + i), (strlen(*((char **)_list->base_addr + j)) + 1) * sizeof(char))) == NULL)
                {
                    printf("Error: unable to allocate new heap space\n");
                    exit(EX_OSERR);
                }
                else
                {
                    *((char **)_list->base_addr + i) = ptr_tmp;
                }
                strcpy(*((char **)_list->base_addr + i), *((char **)_list->base_addr + j));
                if ((ptr_tmp = (char *)realloc(*((char **)_list->base_addr + j), (strlen(cpy_tmp) + 1) * sizeof(char))) == NULL)
                {
                    printf("Error: unable to allocate new heap space\n");
                    exit(EX_OSERR);
                }
                else
                {
                    *((char **)_list->base_addr + j) = ptr_tmp;
                }
                strcpy(*((char **)_list->base_addr + j), cpy_tmp);
            }
            else
            {
                memcpy(cpy_tmp, _list->base_addr + i * _list->data_size, _list->data_size);
                memcpy(_list->base_addr + i * _list->data_size, _list->base_addr + j * _list->data_size, _list->data_size);
                memcpy(_list->base_addr + j * _list->data_size, cpy_tmp, _list->data_size);
            }
            i++;
            j--;
        }
        if (j + 1 < right)
        {
            k = j + 1;
            push_List(&left_list, &k);
            push_List(&right_list, &right);
        }
        if (left < i - 1)
        {
            k = i - 1;
            push_List(&left_list, &left);
            push_List(&right_list, &k);
        }
    }

    free(cpy_tmp);
    free_List(&left_list);
    free_List(&right_list);
    return;
}
long indexOf_List(const List *_list, const void *_elements, int (*_compare)(const void *, const void *))
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"indexOf_List(const List *_list, const void * _elements, int (*_compare)(const void *, const void *))\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_elements == NULL)
    {
        printf("Error: Cannot invoke \"indexOf_List(const List *_list, const void * _elements, int (*_compare)(const void *, const void *))\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    if (_compare == NULL)
    {
        printf("Error: Cannot invoke \"indexOf_List(const List *_list, const void * _elements, int (*_compare)(const void *, const void *))\" because \"<local3>\" is null\n");
        exit(EX_USAGE);
    }
    long i;
    for (i = 0; i < _list->size; i++)
    {
        if (_compare(_list->base_addr + i * _list->data_size, _elements) == 0)
        {
            return i;
        }
    }
    return -1;
}
void inputFile_List(List *_list, const char *_file_name, const char *_token, const unsigned _LINE_SPLIT)
{
    if (_list == NULL)
    {
        printf("Error: Cannot invoke \"inputFile_List(List *_list, const char *_file_name, const char *_token, const unsigned _LINE_SPLIT)\" because \"<local1>\" is null\n");
        exit(EX_USAGE);
    }
    if (_file_name == NULL)
    {
        printf("Error: Cannot invoke \"inputFile_List(List *_list, const char *_file_name, const char *_token, const unsigned _LINE_SPLIT)\" because \"<local2>\" is null\n");
        exit(EX_USAGE);
    }
    const unsigned buf_size = 1024;
    FILE *fp;
    if ((fp = fopen(_file_name, "r")) == NULL)
    {
        printf("Error: %s (No such file or directory)\n", _file_name);
        exit(EX_NOINPUT);
    }
    char buf[buf_size];
    char *tmp, *line, *string_tmp;
    unsigned line_size = buf_size;
    if ((line = (char *)calloc(buf_size + 1, sizeof(char))) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    _list->is_string = true;
    _list->size = 0;
    _list->data_size = sizeof(char *);
    _list->capacity = LIST_BUF_SIZE * _list->data_size;
    _list->allocated = 0;
    if ((_list->base_addr = (char **)malloc(_list->capacity)) == NULL)
    {
        printf("Error: unable to allocate new heap space\n");
        exit(EX_OSERR);
    }
    int next_line = 1;
    while (fgets(buf, buf_size, fp) != NULL)
    {
        if (next_line == 1)
        {
            strcpy(line, buf);
        }
        else
        {
            if (line_size < strlen(line) + buf_size)
            {
                line_size += buf_size;
                if ((string_tmp = (char *)realloc(line, line_size * sizeof(char))) == NULL)
                {
                    free(string_tmp);
                    printf("Error: unable to allocate new heap space\n");
                    exit(EX_OSERR);
                }
                else
                {
                    line = string_tmp;
                }
            }
            strcat(line, buf);
        }
        if (line[strlen(line) - 1] == '\n')
        {
            if (_token == NULL)
            {
                line[strlen(line) - 1] = '\0';
                push_List(_list, line);
                next_line = 1;
            }
            else
            {
                tmp = line;
                while ((string_tmp = strstr(tmp, _token)) != NULL)
                {
                    *(string_tmp) = '\0';
                    push_List(_list, tmp);
                    tmp = string_tmp + strlen(_token);
                }
                next_line = 1;
                if (_LINE_SPLIT == LINE_SPLIT_FALSE)
                {
                    strcpy(line, tmp);
                    next_line = 0;
                }
                else
                {
                    tmp[strlen(tmp) - 1] = '\0';
                    push_List(_list, tmp);
                }
            }
        }
        else
        {
            next_line = 0;
        }
    }
    if (next_line == 0)
    {
        push_List(_list, line);
    }
    if (_token != NULL)
    {
        *(((char **)_list->base_addr + (_list->size - 1)) + strlen(*((char **)_list->base_addr + (_list->size - 1))) - strlen(_token)) = '\0';
    }
    free(line);
    fclose(fp);
}