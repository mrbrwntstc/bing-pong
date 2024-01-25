#include <string.h>

#include "../engine.h"

array_list *array_list_create(usize item_size, usize initial_capacity)
{
  array_list *list = malloc(sizeof(array_list));
  if(!list)
    ERROR_RETURN(NULL, "Not enough memory to create array list\n");
  
  list->item_size = item_size;
  list->len = 0;
  list->capacity = initial_capacity;
  list->data = malloc(initial_capacity * item_size);

  if(!list->data)
    ERROR_RETURN(NULL, "Not enough memory to create array_list.data\n");

  return list;
}

usize array_list_append(array_list *list, void *item)
{
  if(list->len == list->capacity) {
    list->capacity = list->capacity = 0 ? 1 : list->capacity * 2;
    void* items = realloc(list->data, list->capacity * list->item_size);
    if(!items)
      ERROR_RETURN(-1, "Not enough memory to resize array_list.data\n");

    list->data = items;
  }

  usize index = list->len++;

  memcpy((u8*)list->data + index * list->item_size, item, list->item_size);

  return index;
}

void *array_list_get(array_list *list, usize index)
{
  if(index >= list->len)
    ERROR_RETURN(NULL, "Index out of bounds in array_list_get\n");

  return (u8*)list->data + index * list->item_size;
}

bool array_list_remove(array_list *list, usize index)
{
  if(index >= list->len)
    ERROR_RETURN(false, "Index out of bounds in array_list_remove\n");
  if(list->len == 0)
    ERROR_RETURN(false, "array_list is empty in array_list_remove\n");

  if(list->len == 1) {
    list->len = 0;
    return true;
  }

  list->len--;

  u8 *item_ptr = (u8*)list->data + index * list->item_size;
  u8 *end_ptr = (u8*)list->data + list->len * list->item_size;
  memcpy(item_ptr, end_ptr, list->item_size);

  return true;
}
