#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

/*This function is used to get the type of the file, and save the type in string filetype.
The first letter in the human readable access string depends on filetype too, so it is otained
here.*/
void get_type(char * filetype, char * access, struct stat * ans) {
  switch (ans->st_mode & S_IFMT) {
    case S_IFBLK:
      access[0] = 'b';
      filetype = strcpy(filetype, "block special file");
      break;
    case S_IFCHR:
      access[0] = 'c';
      filetype = strcpy(filetype, "character special file");
      break;
    case S_IFDIR:
      access[0] = 'd';
      filetype = strcpy(filetype, "directory");
      break;
    case S_IFIFO:
      access[0] = 'p';
      filetype = strcpy(filetype, "fifo");
      break;
    case S_IFLNK:
      access[0] = 'l';
      filetype = strcpy(filetype, "symbolic link");
      break;
    case S_IFREG:
      access[0] = '-';
      filetype = strcpy(filetype, "regular file");
      break;
    case S_IFSOCK:
      access[0] = 's';
      filetype = strcpy(filetype, "socket");
      break;
    default:
      access[0] = '.';
      filetype = strcpy(filetype, "unknown");
      break;
  }
}

/*This function is used to use library functions to load the information of file,
genral information is loaded and saved in ans, information of uid and gid is loaded
and saved in p and g (pointed by pptr and gptr).*/
int load_info(char * filename,
              struct stat * ans,
              struct passwd ** pptr,
              struct group ** gptr) {
  //load general information, check failure
  if (lstat(filename, ans) != 0) {
    fprintf(stderr, "lstat failed\n");
    return EXIT_FAILURE;
  }

  //load uid and gid information, check failure
  if ((*pptr = getpwuid(ans->st_uid)) == NULL) {
    printf("get user name error\n");
    return EXIT_FAILURE;
  }

  if ((*gptr = getgrgid(ans->st_gid)) == NULL) {
    fprintf(stderr, "get group name error\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/*This function is used to print out the first 3 lines*/
void print_first_3(char * filename,
                   char * filetype,
                   char * linktarget,
                   struct stat * ans) {
  //the first line, if file is simbolic link type, obtain linktarget and print it too
  if (!strcmp(filetype, "symbolic link")) {
    ssize_t len = readlink(filename, linktarget, 256);
    linktarget[len] = '\0';
    printf("  File: %s -> %s\n", filename, linktarget);
  }
  else {
    printf("  File: %s\n", filename);
  }

  //the second line
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         ans->st_size,
         ans->st_blocks,
         ans->st_blksize,
         filetype);

  //the third line, if filetype is character or block, print device type too, in Ubuntu,
  //the format of device type is hex, as required in README, here using %d.
  if (!strcmp(filetype, "character special file") ||
      !strcmp(filetype, "block special file")) {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           ans->st_dev,
           ans->st_dev,
           ans->st_ino,
           ans->st_nlink,
           major(ans->st_rdev),
           minor(ans->st_rdev));
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           ans->st_dev,
           ans->st_dev,
           ans->st_ino,
           ans->st_nlink);
  }
}

/* This function is used to construct the rest part of access string.*/
void construct_access(char * access, int * Sarr, struct stat * ans) {
  //using a for loop to check each bit of st_mode, then write r, w, x or -
  for (size_t i = 1; i < 10; i++) {
    if ((ans->st_mode & Sarr[i - 1]) != 0) {
      //bit 1,4,7 -- r/-
      if (i % 3 == 1) {
        access[i] = 'r';
      }
      //bit 2,5,8 -- w/-
      if (i % 3 == 2) {
        access[i] = 'w';
      }
      //bit 3,6,9 -- x/-
      //some bit 9 would be t, here don't consider it
      if (i % 3 == 0) {
        access[i] = 'x';
      }
    }
    else {
      access[i] = '-';
    }
  }
  access[10] = '\0';
}

/*This function is used to print the 4th line*/
void print_line_4(char * access, struct stat * ans, struct passwd * p, struct group * g) {
  printf("Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
         ans->st_mode & ~S_IFMT,
         access,
         ans->st_uid,
         p->pw_name,
         ans->st_gid,
         g->gr_name);
}

/*This function is used to print the time information*/
void print_time(struct stat * ans) {
  char * atime = time2str(&ans->st_atime, ans->st_atim.tv_nsec);
  char * mtime = time2str(&ans->st_mtime, ans->st_mtim.tv_nsec);
  char * ctime = time2str(&ans->st_ctime, ans->st_ctim.tv_nsec);
  printf("Access: %s\n", atime);
  printf("Modify: %s\n", mtime);
  printf("Change: %s\n", ctime);
  printf(" Birth: -\n");
  free(atime);
  free(mtime);
  free(ctime);
}

int main(int argc, char ** argv) {
  //check the number of arguments
  if (argc <= 1) {
    fprintf(stderr, "wrong number of argument\n");
    exit(EXIT_FAILURE);
  }
  //for each argv (filename), repeat the same process
  for (int i = 1; i < argc; i++) {
    struct stat ans;
    struct passwd * p;
    struct group * g;
    //filetype string is guaranteed to be longer than any possible file type's name
    char filetype[20];
    char access[11];
    char linktarget[256];
    //this array contains each bit of st_mode that is related to r, w, x
    int Sarr[] = {
        S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};

    if (load_info(argv[i], &ans, &p, &g)) {
      continue;
    }

    get_type(filetype, access, &ans);

    construct_access(access, Sarr, &ans);

    print_first_3(argv[i], filetype, linktarget, &ans);

    print_line_4(access, &ans, p, g);

    print_time(&ans);
  }

  return EXIT_SUCCESS;
}
