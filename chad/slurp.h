#ifndef SLURP_H
#define SLURP_H

#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

static char * read_file(const char * const path);
static inline int write_file(const char * const path, const char * const s);
static inline int overwrite_file(const char * const path, const char * const s);
static inline int append_file(const char * const path, const char * const s);
static inline int prepend_file(const char * const path, const char * const s);

#define slurp read_file

static
char * read_file(const char * const path) {
    char * r = NULL;

    int fd = open(path, O_RDONLY | O_CLOEXEC);
    if (fd == -1) { return r; }

    struct stat stat_buf;
    if (fstat(fd, &stat_buf) == -1) { return r; }

    if (stat_buf.st_size > 0 && S_ISREG (stat_buf.st_mode)) {
        const auto len = stat_buf.st_size;
        r = malloc(len + 1);
        if (!r) { return r; }

        ssize_t bytes_read = 0;
        for (ssize_t n; bytes_read < len; bytes_read += n) {
            n = read(fd, r + bytes_read, len - bytes_read);
            if (n == -1) { return r; }
            if (n == 0) { break; }
        }

        r[bytes_read] = '\0';
    } else {
        FILE * f = fdopen(fd, "re");
        if (!f) { return r; }

        size_t len = 0;
        size_t cap = 4096;
        char buf[4096];
        r = (char*)malloc(cap * sizeof(char));
        if (!r) { return r; }

        while (true) {
            size_t bytes = fread(buf, 1, sizeof(buf), f);
            if (ferror(f)) { free(r); goto error; }

            if (bytes > 0) {
                while (len + bytes > cap) {
                    cap *= 2;
                    r = realloc(r, cap);
                    if (!r) { goto error; }
                }
                memcpy(r + len, buf, bytes);
                len += bytes;
            }

            if (feof(f)) { break; }
        }

        r[len] = '\0';
      error:
        fclose(f);
    }

    return r;
}

static
int proto_write_file(const char * const path, const char * const s, const int flags) {
    const size_t len = strlen(s);

    int fd = open(path, flags, 0644);
    if (fd == -1) { return 1; }

    struct stat stat_buf;
    if (fstat(fd, &stat_buf) == -1) { return 1; }

    if (S_ISREG (stat_buf.st_mode)) {
        if (fallocate(fd, 0, 0, len) == -1) { return 1; }
    }
    
    for (ssize_t n, offset = 0; offset < len; offset += n) {
        n = write(fd, s + offset, len - offset);
        if (n == -1) { return 1; }
    }

    if (close(fd) == -1) { return 1; }

    return 0;
}

static inline
int write_file(const char * const path, const char * const s) {
    return proto_write_file(path, s, O_WRONLY | O_CREAT | O_EXCL);
}

static inline
int overwrite_file(const char * const path, const char * const s) {
    return proto_write_file(path, s, O_WRONLY | O_CREAT | O_TRUNC);
}

static inline
int append_file(const char * const path, const char * const s) {
    return proto_write_file(path, s, O_WRONLY | O_CREAT | O_APPEND);
}

static inline
int prepend_file(const char * const path, const char * const s) {
    char * const saved_contents = read_file(path);
    if (overwrite_file(path, s)) { return 1; }
    if (append_file(path, saved_contents)) { return 1; }
    free(saved_contents);

    return 0;
}

#endif
