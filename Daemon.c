#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/anwar/praktikum_2/no1")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {

    DIR *dir;
    struct dirent *ent;
    //char *fileName,*ext;
    char fileName[1000]="";
    int ret;
    char nameRule[10] = ""; 
    char originalName[1000]="";
    char newName[1000]="";
    char imageSrc[1000] = "/home/anwar/praktikum_2/no1/";
    char dest[1000] = "/home/anwar/modul2/gambar/";
    char ext[3]="";
    char file[100]="";
   

    if ((dir = opendir ("/home/anwar/praktikum_2/no1/")) != NULL) {
 
        while ((ent = readdir (dir)) != NULL) {
            
            strcpy(originalName, imageSrc); 
            strcat(originalName,ent->d_name);   
            
            strncpy(file,ent->d_name,99);
           

            int length = strlen(file);
            int j,i;
                    
            for(i=length-3,j=0; i<=length; j++ ,i++){
              ext[j]=file[i];
            }

            for(i=0; i<=length-5; i++){
              fileName[i]=file[i];
            }
            

            if(ext!=NULL)
            {
                ret=strcmp(ext,"png");
                if(ret==0)
                {
                    //nameRule="";
                    strcpy(nameRule,"_grey.png");
                    //printf("%s\n",nameRule);
                    
                   // printf("ori : %s\n",originalName);
                    //printf("filename : %s\n",fileName);
                    strcpy(newName,dest);

                    strcat(fileName,nameRule);
                   
                    //printf("name + rule : %s\n",fileName);
                    strcat(newName,fileName);
                    //printf("newname : %s\n",newName);
                    memset(&fileName[0], 0, sizeof(fileName));
                    
                    rename(originalName,newName);
                     
                }
            }
        
        }
        closedir (dir);
    } 

    sleep(1);
  }
  
  exit(EXIT_SUCCESS);
}