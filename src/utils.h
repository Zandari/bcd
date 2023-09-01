#pragma once

char* get_cur_dir();

char** split_str(const char*, const char*, int*);

char** get_dirs(const char*, int*);

char* join(const char**, int n, const char*);

char* conc(const char* ,const char*);
