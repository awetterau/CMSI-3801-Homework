#include "string_stack.h"
#include <stdlib.h>
#include <string.h>

// Complete your string stack implementation in this file.
// string_stack.c

struct _Stack
{
    char **elements;
    int current_size;
    int capacity;
};

stack_response create()
{
    struct _Stack *s = malloc(sizeof(struct _Stack));
    if (!s)
    {
        return (stack_response){.code = out_of_memory, .stack = NULL};
    }

    s->elements = malloc(16 * sizeof(char *));
    if (!s->elements)
    {
        free(s);
        return (stack_response){.code = out_of_memory, .stack = NULL};
    }

    s->current_size = 0;
    s->capacity = 16;

    return (stack_response){.code = success, .stack = s};
}

int size(const stack s)
{
    return s ? s->current_size : 0;
}

bool is_empty(const stack s)
{
    return s ? s->current_size == 0 : true;
}

bool is_full(const stack s)
{
    return s ? s->current_size >= MAX_CAPACITY : true;
}

static char *make_string_copy(const char *str)
{
    size_t len = strlen(str);
    if (len >= MAX_ELEMENT_BYTE_SIZE)
    {
        return NULL;
    }
    char *copy = malloc(len + 1);
    if (copy)
    {
        strcpy(copy, str);
    }
    return copy;
}

static response_code resize_if_needed(stack s)
{
    if (s->current_size == s->capacity && s->capacity < MAX_CAPACITY)
    {
        int new_capacity = s->capacity * 2;
        if (new_capacity > MAX_CAPACITY)
        {
            new_capacity = MAX_CAPACITY;
        }

        char **new_elements = realloc(s->elements, new_capacity * sizeof(char *));
        if (!new_elements)
        {
            return out_of_memory;
        }

        s->elements = new_elements;
        s->capacity = new_capacity;
    }
    return success;
}

response_code push(stack s, char *item)
{
    if (!s || !item)
    {
        return out_of_memory;
    }

    if (strlen(item) >= MAX_ELEMENT_BYTE_SIZE)
    {
        return stack_element_too_large;
    }

    if (s->current_size >= MAX_CAPACITY)
    {
        return stack_full;
    }

    response_code resize_result = resize_if_needed(s);
    if (resize_result != success)
    {
        return resize_result;
    }

    char *copy = make_string_copy(item);
    if (!copy)
    {
        return out_of_memory;
    }

    s->elements[s->current_size++] = copy;
    return success;
}

string_response pop(stack s)
{
    if (!s || s->current_size == 0)
    {
        return (string_response){.code = stack_empty, .string = NULL};
    }

    char *item = s->elements[--s->current_size];

    if (s->current_size > 0 && s->current_size * 4 <= s->capacity && s->capacity > 16)
    {
        int new_capacity = s->capacity / 2;
        if (new_capacity < 16)
            new_capacity = 16;

        char **new_elements = realloc(s->elements, new_capacity * sizeof(char *));
        if (new_elements)
        {
            s->elements = new_elements;
            s->capacity = new_capacity;
        }
    }

    return (string_response){.code = success, .string = item};
}

void destroy(stack *s)
{
    if (!s || !*s)
        return;

    for (int i = 0; i < (*s)->current_size; i++)
    {
        free((*s)->elements[i]);
    }

    free((*s)->elements);
    free(*s);
    *s = NULL;
}