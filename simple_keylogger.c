#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <dirent.h>
#include <string.h>


void findKeyboardFile(char *keyboard_file){
  DIR *d;
  struct dirent *dir;
  char found_it[100] = "/dev/input/by-path/";
  char found = 0;
  d = opendir(found_it);
  if(d){
    while((dir = readdir(d)) != NULL){
      if(strstr(dir->d_name, "kbd")!=NULL){
        strcat(found_it, dir->d_name);
        found = 1;
        break;
      }
    }
    closedir(d);
  }
  if(found){
    strcpy(keyboard_file, found_it);
  }
  else{
    keyboard_file = "";
  }
}

void getKeyName(char *key_name, int key_code){
  switch(key_code){
    case 0 : strcpy(key_name,"KEY_RESERVED"); break;
    case 1 : strcpy(key_name,"KEY_ESC"); break;
    case 2 : strcpy(key_name,"KEY_1"); break;
    case 3 : strcpy(key_name,"KEY_2"); break;
    case 4 : strcpy(key_name,"KEY_3"); break;
    case 5 : strcpy(key_name,"KEY_4"); break;
    case 6 : strcpy(key_name,"KEY_5"); break;
    case 7 : strcpy(key_name,"KEY_6"); break;
    case 8 : strcpy(key_name,"KEY_7"); break;
    case 9 : strcpy(key_name,"KEY_8"); break;
    case 10: strcpy(key_name,"KEY_9"); break;
    case 11: strcpy(key_name,"KEY_0"); break;
    case 12: strcpy(key_name,"KEY_MINUS"); break;
    case 13: strcpy(key_name,"KEY_EQUAL"); break;
    case 14: strcpy(key_name,"KEY_BACKSPACE"); break;
    case 15: strcpy(key_name,"KEY_TAB"); break;
    case 16: strcpy(key_name,"KEY_Q"); break;
    case 17: strcpy(key_name,"KEY_W"); break;
    case 18: strcpy(key_name,"KEY_E"); break;
    case 19: strcpy(key_name,"KEY_R"); break;
    case 20: strcpy(key_name,"KEY_T"); break;
    case 21: strcpy(key_name,"KEY_Y"); break;
    case 22: strcpy(key_name,"KEY_U"); break;
    case 23: strcpy(key_name,"KEY_I"); break;
    case 24: strcpy(key_name,"KEY_O"); break;
    case 25: strcpy(key_name,"KEY_P"); break;
    case 26: strcpy(key_name,"KEY_LEFTBRACE"); break;
    case 27: strcpy(key_name,"KEY_RIGHTBRACE"); break;
    case 28: strcpy(key_name,"KEY_ENTER"); break;
    case 29: strcpy(key_name,"KEY_LEFTCTRL"); break;
    case 30: strcpy(key_name,"KEY_A"); break;
    case 31: strcpy(key_name,"KEY_S"); break;
    case 32: strcpy(key_name,"KEY_D"); break;
    case 33: strcpy(key_name,"KEY_F"); break;
    case 34: strcpy(key_name,"KEY_G"); break;
    case 35: strcpy(key_name,"KEY_H"); break;
    case 36: strcpy(key_name,"KEY_J"); break;
    case 37: strcpy(key_name,"KEY_K"); break;
    case 38: strcpy(key_name,"KEY_L"); break;
    case 39: strcpy(key_name,"KEY_SEMICOLON"); break;
    case 40: strcpy(key_name,"KEY_APOSTROPHE"); break;
    case 41: strcpy(key_name,"KEY_GRAVE"); break;
    case 42: strcpy(key_name,"KEY_LEFTSHIFT"); break;
    case 43: strcpy(key_name,"KEY_BACKSLASH"); break;
    case 44: strcpy(key_name,"KEY_Z"); break;
    case 45: strcpy(key_name,"KEY_X"); break;
    case 46: strcpy(key_name,"KEY_C"); break;
    case 47: strcpy(key_name,"KEY_V"); break;
    case 48: strcpy(key_name,"KEY_B"); break;
    case 49: strcpy(key_name,"KEY_N"); break;
    case 50: strcpy(key_name,"KEY_M"); break;
    case 51: strcpy(key_name,"KEY_COMMA"); break;
    case 52: strcpy(key_name,"KEY_DOT"); break;
    case 53: strcpy(key_name,"KEY_SLASH"); break;
    case 54: strcpy(key_name,"KEY_RIGHTSHIFT"); break;
    case 55: strcpy(key_name,"KEY_KPASTERISK"); break;
    case 56: strcpy(key_name,"KEY_LEFTALT"); break;
    case 57: strcpy(key_name,"KEY_SPACE"); break;
    case 58: strcpy(key_name,"KEY_CAPSLOCK"); break;
    case 59: strcpy(key_name,"KEY_F1"); break;
    case 60: strcpy(key_name,"KEY_F2"); break;
    case 61: strcpy(key_name,"KEY_F3"); break;
    case 62: strcpy(key_name,"KEY_F4"); break;
    case 63: strcpy(key_name,"KEY_F5"); break;
    case 64: strcpy(key_name,"KEY_F6"); break;
    case 65: strcpy(key_name,"KEY_F7"); break;
    case 66: strcpy(key_name,"KEY_F8"); break;
    case 67: strcpy(key_name,"KEY_F9"); break;
    case 68: strcpy(key_name,"KEY_F10"); break;
    case 69: strcpy(key_name,"KEY_NUMLOCK"); break;
    case 70: strcpy(key_name,"KEY_SCROLLLOCK"); break;
  }
}

int main(void){
  char keyboard_file[100];
  char key_name[100];
  findKeyboardFile(keyboard_file);
  if(strlen(keyboard_file) > 0){
    int fd;
    printf("%s\n",keyboard_file);
    fd = open(keyboard_file, O_RDONLY);
    if(fd == -1){
      printf("Was not able to open the keyboard file\n");
      return 1;
    }
    struct input_event ev;
    ssize_t n;
    while(1){
      n = read(fd, &ev, sizeof ev);
      if(ev.type == EV_KEY && ev.value == 1){
        getKeyName(key_name, ev.code);
        printf("%s\n", key_name);
        if(ev.code == KEY_ESC){
          printf("Exiting\n");
          break;
        }
      }
    }
    close(fd);
    fflush(stdout);
  }else{
    printf("no keyboard file found\n");
  }
  return 0;
}
