#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
#include "aaa.h"

#define DEPTH 1

void print_cdw(Item* items, int n, int selected[DEPTH], struct Appearence appearence)
{
  for (int i = 0; i < n; i++) {
    char fg, bg;
    if (i == selected[0]) {
      fg = appearence.selected_fg;
      bg = appearence.selected_bg;
    }
    else {
      fg = appearence.unselected_fg;
      bg = appearence.unselected_bg;
    }
    printf("\e[38;5;%dm\e[48;5;%dm%s", fg, bg, items[i].name);
    if (items[i].contains != NULL)
      printf("%c", appearence.dropdown);
    printf("\e[m%c", appearence.delimiter);
  }

  for (int i = 1; i < DEPTH; ++i) {
    printf("%d", i);
  }
}

bool handle_input(struct KeyConfig key_config, int n, int* selected) {
  bool quit = false;
  char input = getc(stdin); 
  if (input == key_config.left && selected[0] > 0)
    selected[0]--;
  else if (input == key_config.right && selected[0] < n - 1)
    selected[0]++;
  else if (input == '\r') // <enter>
    quit = true;
  else if (input != key_config.quit && input != EOF) {
    selected[0] = n - 1;  // setting selected folder to current
    quit = true;
  }
  return quit;
}

int* perform(Item* items, int n, struct Appearence appearence, struct KeyConfig key_config)
{
  bool confirmed = false;
  unsigned int level = 0;
  int* selected = malloc(DEPTH * sizeof(int));
  for (int i = 0; i < DEPTH; ++i)
    selected[i] = -1;
  selected[0] = n - 1;

  system("/bin/stty raw");

  do {
    print_cdw(items, n, selected, appearence);
    printf("\e[2K\r");  
  }
  while (handle_input(key_config, n, selected));

  system("/bin/stty cooked");
  return selected;
}

int* asdf(Item* items, int n, struct Appearence appearence, struct KeyConfig key_config)
{
  struct Buffer* buf = new_buffer(1, n);
  for (int i = 0; i < n; ++i)
    set_item(buf, items[i], i, 0);
  display(buf, appearence);
  return NULL;
}

int main(int argc, char** argv) {
  char* filepath = NULL;
  bool is_dir_mode = false;

  for (int i = 1; i < argc; ++i)
    if (strcmp(argv[i], "-d") || strcmp(argv[i], "--dirs"))
      is_dir_mode = true;
    else 
      filepath = argv[i];

  char* path_str = get_cur_dir();
  int n = 0;
  char** dirs_str = split_str(path_str, "/", &n);
  
  if (argc > 1) {
    printf("%s\n", path_str);
    for (int i = 0; i < n; ++i) {
      printf("%d. %s\n", i, dirs_str[i]);
    }
  }

  Item* items = malloc(n * sizeof(Item));
  for (int i = 0; i < n; ++i) {
    items[i].name = dirs_str[i];
    items[i].contains = NULL;
  }

  struct Appearence appearence = {7, 0, 14, 0, ' ', '-', 5};
  struct KeyConfig key_config = {'h', 'l', 'j', 'k', 'q'};

  // int *selected = perform(items, n, appearence, key_config);
  int *selected = asdf(items, n, appearence, key_config);

  if (filepath != NULL) {
    char* target = join((const char**)dirs_str, selected[0] + 1, "/");
    FILE* file = fopen(filepath, "w");
    fprintf(file, "%s", target); 
    fclose(file);

    free(target);
  }

  free(selected);
  free(path_str);
  free(items);
}
