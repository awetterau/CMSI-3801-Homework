#include "string_stack.h"
#include <stdlib.h>
#include <string.h>

struct _Stack
{
    char** elements;
    int current_size;
    int capacity;
};

stack_response create()
{
    stack s = malloc(sizeof(struct _Stack));
    if (s == NULL)
    {
        return (stack_response){.code = out_of_memory, .stack = NULL};
    }

    s->elements = malloc(16 * sizeof(char*));
    s->current_size = 0;
    s->capacity = 16;

    if (!s->elements)
    {
        free(s);
        return (stack_response){.code = out_of_memory, .stack = NULL};
    }

    return (stack_response){.code = success, .stack = s};
}

int size(const stack s)
{
    return s ? s->current_size : 0;
}

bool is_empty(const stack s)
{
    return size(s) == 0;
}

bool is_full(const stack s)
{
    return s ? s->current_size >= MAX_CAPACITY : true;
}

// static char* make_string_copy(const char *str)
// {
//     size_t len = strlen(str);
//     if (len >= MAX_ELEMENT_BYTE_SIZE)
//     {
//         return NULL;
//     }
//     char* copy = malloc(len + 1);
//     if (copy)
//     {
//         strcpy(copy, str);
//     }
//     return copy;
// }

response_code push(stack s, char* item)
{
    if (is_full(s))
    {
        return stack_full;
    }

    if (strlen(item) >= MAX_ELEMENT_BYTE_SIZE)
    {
        return stack_element_too_large;
    }

    if (s->current_size == s->capacity) 
    {
        int new_capacity = s->capacity * 2;
        if(new_capacity > MAX_CAPACITY) 
        {
            new_capacity = MAX_CAPACITY;
        }

        char** new_elements = realloc(s->elements, new_capacity * sizeof(char*));
        if (new_elements == NULL) 
        {
            return out_of_memory;
        }
        s->elements = new_elements;
        s->capacity = new_capacity;
    }

    s->elements[s->current_size++] = strdup(item);
    return success;
}

string_response pop(stack s)
{
    if (is_empty(s))
    {
        return (string_response){.code = stack_empty, .string = NULL};
    }

    char* popped_item = s->elements[--s->current_size];

    if (s->current_size < s->capacity / 4) {
        int new_capacity = s->capacity / 2;

        if (new_capacity < 1) {
            new_capacity = 1;
        }

        char** new_elements = realloc(s->elements, new_capacity * sizeof(char*));
        if (new_elements == NULL) {
            return (string_response){.code = out_of_memory, .string = NULL};
        }

        s->elements = new_elements;
        s->capacity = new_capacity;
    }

    // char* copied_popped_item = make_string_copy(popped_item);
    // free(popped_item);

    return (string_response){.code = success, .string = popped_item};
}

void destroy(stack *s)
{
    for (int i = 0; i < (*s)->current_size; i++)
    {
        free((*s)->elements[i]);
    }

    free((*s)->elements);
    free(*s);
    *s = NULL;
}