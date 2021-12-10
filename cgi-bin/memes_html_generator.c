#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>




char *strremove(char *str, const char *sub) {
    char *p, *q, *r;
    if (*sub && (q = r = strstr(str, sub)) != NULL) {
        size_t len = strlen(sub);
        while ((r = strstr(p = r + len, sub)) != NULL) {
            memmove(q, p, r - p);
            q += r - p;
        }
        memmove(q, p, strlen(p) + 1);
    }
    return str;
}

void listFiles(const char *path, char *str)
{
    struct dirent *dp;
    DIR *dir = opendir(path);
    if (!dir) 
    return; 
    
    int i = 0;    
    while ((dp = readdir(dir)) != NULL)
    {
        if(i == 0)
        {        
            sprintf(str, "%s\n", dp->d_name);
            i++;
        }else{
            strcat(str,"\n");
            strcat(str, dp->d_name);
        }

    }
    closedir(dir);
    strremove(str, "..\n");
    strremove(str, ".\n");
}

int main()
{
    char str[1000];
    const char path[]="./memes/";
    listFiles(path, str);
    
    char *html_str;

    html_str = strtok(str, "\n");
    while(html_str != NULL)
    {
    printf("<img src=\"memes/%s\">\n<br>\n<br>\n<hr>\n<br>\n", html_str);
        html_str = strtok(NULL, "\n");
    }
    
    return 0;
}
