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

static inline char * slurp(const char * const path);
static inline char * read_file(const char * const path);
static inline int write_file(const char * const path, const char * const s);
static inline int overwrite_file(const char * const path, const char * const s);
static inline int append_file(const char * const path, const char * const s);
static inline int prepend_file(const char * const path, const char * const s);

// XXX experimental naming
char * read_file_get_size(const char * const path, size_t * size);
int write_file_blob(const char * const path, const char * const s, size_t size);
int overwrite_file_blob(const char * const path, const char * const s, size_t size);
int append_file_blob(const char * const path, const char * const s, size_t size);
int prepend_file_blob(const char * const path, const char * const s, size_t size);

// ---

static inline
char * slurp(const char * const path) {
    return read_file(path);
}

static inline
char * read_file(const char * const path) {
    size_t discarder;
    char * r = read_file_get_size(path, &discarder);
    return r;
}

static inline
int write_file(const char * const path, const char * const s) {
    size_t size = strlen(s);
    return write_file_blob(path, s, size);
}

static inline
int overwrite_file(const char * const path, const char * const s) {
    size_t size = strlen(s);
    return overwrite_file_blob(path, s, size);
}

static inline
int append_file(const char * const path, const char * const s) {
    size_t size = strlen(s);
    return append_file_blob(path, s, size);
}

static inline
int prepend_file(const char * const path, const char * const s) {
    size_t size = strlen(s);
    return prepend_file_blob(path, s, size);
}

// ---

#ifdef SLURP_IMPLEMENTATION

char * read_file_get_size(const char * const path, size_t * size) {
    char * r = NULL;
    *size = 0;

    int fd = open(path, O_RDONLY | O_CLOEXEC);
    if (fd == -1) { return r; }

    struct stat stat_buf;
    if (fstat(fd, &stat_buf) == -1) { return r; }

    if (stat_buf.st_size > 0 && S_ISREG (stat_buf.st_mode)) {
        const auto len = stat_buf.st_size;
        r = (char*)malloc(len + 1);
        if (!r) { return r; }

        ssize_t bytes_read = 0;
        for (ssize_t n; bytes_read < len; bytes_read += n) {
            n = read(fd, r + bytes_read, len - bytes_read);
            if (n == -1) {
                close(fd);
                free(r);
                return NULL;
            }
            if (n == 0) { break; }
            *size += n;
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
                    r = (char*)realloc(r, cap);
                    if (!r) { goto error; }
                }
                memcpy(r + len, buf, bytes);
                len += bytes;
                *size += bytes;
            }

            if (feof(f)) { break; }
        }

        r[len] = '\0';
      error:
        fclose(f);
    }

    return r;
}

int proto_write_file(const char * const path, const char * const s, const int flags, size_t size) {
    int fd = open(path, flags, 0644);
    if (fd == -1) { return 1; }

    struct stat stat_buf;
    if (fstat(fd, &stat_buf) == -1) {
        close(fd);
        return 2;
    }

    if (size == 0) {
        // intentially writing empty file
        close(fd);
        return 0;
    }

    if (S_ISREG(stat_buf.st_mode)) {
        const off_t fallocate_offset = (flags & O_APPEND) ? stat_buf.st_size : 0;
        const int fallocate_mode = (flags & O_APPEND) ? FALLOC_FL_KEEP_SIZE : 0;
        if (fallocate(fd, fallocate_mode, fallocate_offset, size) == -1) {
            close(fd);
            return 3;
        }
    }
    
    for (ssize_t n, offset = 0; (size_t)offset < size; offset += n) {
        n = write(fd, s + offset, size - offset);
        if (n == -1) { return 1; }
    }

    if (close(fd) == -1) { return 4; }

    return 0;
}

int write_file_blob(const char * const path, const char * const s, size_t size) {
    return proto_write_file(path, s, O_WRONLY | O_CREAT | O_EXCL, size);
}

int overwrite_file_blob(const char * const path, const char * const s, size_t size) {
    return proto_write_file(path, s, O_WRONLY | O_CREAT | O_TRUNC, size);
}

int append_file_blob(const char * const path, const char * const s, size_t size) {
    return proto_write_file(path, s, O_WRONLY | O_CREAT | O_APPEND, size);
}

int prepend_file_blob(const char * const path, const char * const s, size_t size) {
    char * saved_contents = read_file(path);
    if (overwrite_file(path, s)) { return 1; }
    if (saved_contents) {
        if (append_file_blob(path, saved_contents, size)) { return 1; }
        free(saved_contents);
    }

    return 0;
}
#endif

#endif
