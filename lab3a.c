#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char *argv[]) 
{
    int dirCounter=1;
    do {
        void * dirPtr = opendir(argv[dirCounter]);
        if (readdir(dirPtr) != NULL)
        {
            printf("Current dir: %s\n", argv[dirCounter]); 
            printf("type | usr | grp | oth |    user name    |   group name    |    size    |      name       |    modification time\n");
            struct dirent * entry;
            entry = readdir(dirPtr);
            while (NULL != entry)
            {
                struct stat statBuf;
                stat(entry->d_name, &statBuf);

                char * name = entry->d_name;

                char sizeStr[20] = {};
                
                char fileType;
                if (S_ISREG(statBuf.st_mode))
                {
                    fileType = '-';
                    sprintf(sizeStr, "%ld", statBuf.st_size);
                } 
                else if (S_ISDIR(statBuf.st_mode))
                    fileType = 'd';
                else 
                    fileType = '?';
                
                char userAccess[3] = {'-', '-', '-'};
                if (S_IRUSR & statBuf.st_mode)
                    userAccess[0] = 'r';
                if (S_IWUSR & statBuf.st_mode)
                    userAccess[1] = 'w';
                if (S_IXUSR & statBuf.st_mode)
                    userAccess[2] = 'x';

                char groupAccess[3] = {'-', '-', '-'};
                if (S_IRGRP & statBuf.st_mode)
                    groupAccess[0] = 'r';
                if (S_IWGRP & statBuf.st_mode)
                    groupAccess[1] = 'w';
                if (S_IXGRP & statBuf.st_mode)
                    groupAccess[2] = 'x';

                char othersAccess[3] = {'-', '-', '-'};
                if (S_IROTH & statBuf.st_mode)
                    othersAccess[0] = 'r';
                if (S_IWOTH & statBuf.st_mode)
                    othersAccess[1] = 'w';
                if (S_IXOTH & statBuf.st_mode)
                    othersAccess[2] = 'x';
                
                char * user = getpwuid(statBuf.st_uid)->pw_name;
                char * group = getgrgid(statBuf.st_gid)->gr_name;
                
                char * time = ctime(&statBuf.st_mtime);

                entry = readdir(dirPtr);
                printf("%4c | %c%c%c | %c%c%c | %c%c%c | %15s | %15s | %10s | %15s | %s", 
                fileType, 
                userAccess[0], userAccess[1], userAccess[2],
                groupAccess[0], groupAccess[1], groupAccess[2],
                othersAccess[0], othersAccess[1], othersAccess[2],
                user, group,
                sizeStr,
                name, 
                time

                );
            } 
        }   
        closedir(dirPtr);
        ++dirCounter;

    } while (argv[dirCounter]!=NULL);
    return 0;
}
