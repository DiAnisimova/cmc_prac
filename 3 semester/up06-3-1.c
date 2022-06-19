#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

char *relativize_path(const char *path1, const char *path2)
{
    char *res = calloc(PATH_MAX, 1);
    char *str1 = calloc(sizeof(path1), 1);
    char *str2 = calloc(sizeof(path2), 1);
    int i = 0;
    int j = 0;
    while (path1[i] != 0) {
        if (path1[i] == '.' && 
                (path1[i + 1] == '/' || path1[i + 1] == 0)) {
            i += 2;
        } else if (strncmp(&path1[i], "..", 2) == 0) {
            str1[j] = 0;
            j--;
            str1[j] = 0;
            j--;
            while (str1[j] != '/') {
                str1[j] = 0;
                j--;
            }
            i += 2;
        } else {
            str1[j] = path1[i];
            i++;
            j++;
        }
    }
    i = 0;
    j = 0;
    while (path2[i] != 0) {
        if (path2[i] == '.' &&                     
                (path2[i + 1] == '/' || path2[i + 1] == 0)) {
            i += 2;
        } else if (strncmp(&path2[i], "..", 2) == 0) {
            str2[j] = 0;
            j--;
            str2[j] = 0;
            j--;
            while (str2[j] != '/') {
                str2[j] = 0;
                j--;
            }
            i += 2;
        } else {
            str2[j] = path2[i];
            j++;
            i++;
        }
    }
    if (strcmp(str1, str2) == 0 && strcmp(str1, "/") == 0) {
        res[0] = '.';
        free(str1);
        free(str2);
        return res;
    }
    //char *slash = strstr(str1, str2);
    //if (slash - str1 == 0 && strrchr(str1, '/') == str1 + strlen(str2)) {
    //    res[0] = '.';
    //    fputs(res, stdout);
    //    printf("\n");
        //return res;
    //}
    int k1 = 0;
    int k2 = 0;
    i = 0;
    while (str1[i] != 0) {
        if (str1[i] == '/') {
            k1++;
        }
        i++;
    }
    i = 0;
    while (str2[i] != 0) {
        if (str2[i] == '/') {
            k2++;
        }
        i++;
    }
    if ((strcmp(str1, "/") == 0 || k1 == 1) && strcmp(str2, "/")) {
        strncpy(res, &str2[1], strlen(str2) - 1);
        free(str1);
        free(str2);
        return res;
    }
    if (strcmp(str2, "/") == 0 && k1 != 1) {
        for (i = 0; i < k1 - 1; i++) {
            strncat(res, "../", 3);
        }
        res[strlen(res) - 1] = 0;
        free(str1);
        free(str2);
        return res;
    } else if (strcmp(str2, "/") == 0) {
        res[0] = '.';
        free(str1);
        free(str2);
        return res;
    }
    char **mas1 = calloc(k1 - 1, sizeof(char *));
    char sep[1] = "/";
    mas1[0] = strtok(str1, sep);
    for (i = 1; i < k1 - 1; i++) {
        mas1[i] = strtok(NULL, sep);
    }
    char **mas2 = calloc(k2, sizeof(char *));
    mas2[0] = strtok(str2, sep);
    for (i = 1; i < k2; i++) {
        mas2[i] = strtok(NULL, sep);
    }
    int common = 0;
    int min = k1 - 1;
    if (k2 < min) {
        min = k2;
    }
    i = 0;
    while (i < min && strcmp(mas1[i], mas2[i]) == 0) {
        printf("Cycle 7\n");
        common++;
        i++;
    }
    char last = 0;
    printf("common = %d\n", common);
    for (i = 0; i < k1 - 1 - common; i++) {
        last = 1;
        strncat(res, "../", 3);
    }
    for (i = common; i < k2; i++) {
        last = 0;
        if (i == common) {
            strncat(res, mas2[i], PATH_MAX - strlen(res));
        } else {
            strncat(res, "/", 1);
            strncat(res, mas2[i], PATH_MAX - strlen(res));
        }
    }
    if (last) {
        res[strlen(res) - 1] = 0;
    }
    if (common == k2 && k1 == k2 + 1) {
        res[0] = '.';
    }
    if (mas1) {
        for (i = 0; i < k1; i++) {
            if (mas1[i]) {
                free(mas1[i]);
            }
        }
        free(mas1);
    }
    if (mas2) {
        for (i = 0; i < k2; i++) {
            if (mas2[i]) {
                free(mas2[i]);
            }
        }
        free(mas2);
    }
    free(str1);
    free(str2);
    return res;
}
