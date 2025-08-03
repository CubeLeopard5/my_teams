#include "../../include/server/server.h"

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');

    if (!dot || dot == filename) {
        return "";
    }
    return dot + 1;
}

void create_dir(char *dir_name)
{
    struct stat st = {0};
    
    if (mkdir(dir_name, 0700) == -1) {
        if (errno == EEXIST) {
            if (stat(dir_name, &st) == 0 && S_ISDIR(st.st_mode)) {
                return;
            } else {
                fprintf(stderr, "Path exists but is not a directory\n");
            }
        } else {
            perror("mkdir failed");
        }
    }
}

char *get_file_content(char *file_path) {
    char *buffer = NULL;
    long length;
    FILE *f = fopen(file_path, "rb");

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
            fread(buffer, 1, length, f);
        }
        fclose(f);
    }
    return buffer;
}