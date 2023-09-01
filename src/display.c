#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "aaa.h"


struct Buffer* new_buffer(int height, int width) 
{
  struct Buffer* buffer = malloc(sizeof(struct Buffer));
  buffer->data = malloc(height);
  for (int i = 0; i < height; ++i)
    buffer->data[i] = calloc(width, sizeof(Item));
  buffer->height = height;
  buffer->width = width;
  return buffer;
}

void resize(struct Buffer* buffer, int height, int width)
{
  if (height != buffer->height)
    buffer->data = realloc(buffer->data, height * sizeof(void*));
  if (height > buffer->height)
    for (int i = buffer->height; i < height; ++i) 
      buffer->data[i] = malloc(sizeof(Item) * width);
  if (width == buffer->width)
    return;

  for (int i = 0; i < buffer->height; ++i) {
    buffer->data[i] = realloc(buffer->data[i], width * sizeof(Item));
    for (int j = buffer->width; j < width; ++j)
      buffer->data[i][j] = (Item){"", '\0', 0, false, NULL};
  }
  buffer->width = width;
}

// void format_str(char* str, int width, )
void set_item(struct Buffer* buffer, Item item, int x, int y)
{
  buffer->data[y][x] = item;
}

void display(struct Buffer* buffer, struct Appearence appearence) 
{
  for (int i = 0; i < buffer->height * buffer->width; ++i) {
    Item el = buffer->data[i / buffer->width][i % buffer->width];
    if (el.name != NULL) {
      char fg, bg;
      if (el.selected) {
        fg = appearence.selected_fg;
        bg = appearence.selected_bg;
      }
      else {
        fg = appearence.unselected_fg;
        bg = appearence.unselected_bg;
      }
      printf("\e[38;5;%dm\e[48;5;%dm%s", fg, bg, el.name);
      if (el.contains != NULL)
        printf("%c", appearence.dropdown);
      printf("\e[m%c", appearence.delimiter);
    }
  }
}

