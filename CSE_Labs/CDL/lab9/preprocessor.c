#include <stdio.h>
#include <stdlib.h>

char intermediateFilePath[] = "testical.c";

int preprocessor(char *path) {
    FILE *fa, *fb;
    int ca, cb;

    fa = fopen(path, "r");
    if (fa == NULL) {
        printf("Cannot open file %s\n", path);
        exit(0);
    }

    fb = fopen(intermediateFilePath, "w");
    if (fb == NULL) {
        printf("Cannot open file %s\n", intermediateFilePath);
        fclose(fa);
        exit(0);
    }

    while ((ca = getc(fa)) != EOF) {
        if (ca == '/') {
            cb = getc(fa);
            if (cb == '/') { // Single line comment
                while ((ca = getc(fa)) != '\n' && ca != EOF);
                continue;
            } else if (cb == '*') { // Multi-line comment
                do {
                    while ((ca = getc(fa)) != '*' && ca != EOF);
                    if (ca == EOF) break;
                    cb = getc(fa);
                } while (cb != '/' && cb != EOF);
                continue;
            } else {
                putc(ca, fb);
                putc(cb, fb);
                continue;
            }
        } else if (ca == '#') { // Preprocessor directive
            while ((ca = getc(fa)) != '\n' && ca != EOF);
            continue;
        } else if (ca == '"' || ca == '\'') { // String or character literal
            char quoteType = ca;
            putc(ca, fb);
            while ((ca = getc(fa)) != quoteType && ca != EOF) {
                putc(ca, fb);
                if (ca == '\\') { // Escape sequence, so skip next char too
                    ca = getc(fa);
                    if (ca != EOF) {
                        putc(ca, fb);
                    }
                }
            }
            if (ca != EOF) {
                putc(ca, fb);
            }
            continue;
        }

        putc(ca, fb);
    }

    fclose(fa);
    fclose(fb);

    return 0;
}
