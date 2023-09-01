#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "utils.h"

char* get_cur_dir()
{
  long size = 1024;
  char* buffer = malloc(size * sizeof(char));
  getcwd(buffer, size);
  return buffer;
}

char** split_str(const char* input, const char* del, int* n)  // TODO: should be refactored
{
  *n = 0;
  char* str = malloc(strlen(input) + 1);
  char* ptr_begin = str;
  // char* ptr_end = str + strlen(input) ;
  strcpy(str, input);

  while (strsep(&str, del)) (*n)++;

  (*n)--;
  
  char** result = malloc(*n * sizeof(void**));
  int i = 0;
  for (char* it = ptr_begin; i < *n; ++it)
    if (*it == '\0') {
      result[i] = it + 1;
      ++i;
    }
  return result;
}

char** get_dirs(const char* path, int* n)
{
  struct dirent* entry;
  DIR* dp = opendir(path);
  if (dp == NULL); // TODO: handle error

  long size = 16;
  char** result = malloc(size * sizeof(void**));
  while ((entry = readdir(dp))) {

  }
    

  closedir(dp);
}

char* join(const char** array, int n, const char* del) 
{
  int size = (strlen(del)) * n + 1;
  for (int i = 0; i < n; ++i) {
    size += strlen(array[i]);
  }
  char* result = malloc(size * sizeof(char));
  char* ptr = result;
  for (int i = 0; i < n; ++i) {
    strcpy(ptr, del);
    ptr += strlen(ptr);
    strcpy(ptr, array[i]);
    ptr += strlen(array[i]);
  }
  result[size] = '\0';
  return result;
}

char* conc(const char* l, const char* r)
{
  int size = strlen(l) + strlen(r) + 1;
  char* result = malloc(size);
  strcpy(result, l);
  strcpy(result + strlen(l), r);
  result[size] = '\0';
  return result;
}
