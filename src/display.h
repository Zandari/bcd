#pragma once 

typedef struct Item Item;
struct Item {
  const char* name;
  char type;
  int size;
  bool selected;
  Item* contains;
};

struct Appearence {
  char unselected_fg;
  char unselected_bg;
  char selected_fg;
  char selected_bg;
  char delimiter;
  char dropdown;
  int width;
};

struct KeyConfig {
  char left;
  char right;
  char down;
  char up;
  char quit;
};

struct Buffer {
  int height;
  int width;
  Item** data;
};


struct Buffer* new_buffer(int height, int width);

void resize(struct Buffer* buffer, int height, int width);

void set_item(struct Buffer* buffer, Item item, int x, int y);

void display(struct Buffer* buffer, struct Appearence appearence);
