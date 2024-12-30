#include "../libft/libft.h"

int main (void)
{
    char ***hashtable = malloc(sizeof(char**) * 1000000);
    int fd = open("input.txt", 0);
    int i = 0;
    char *line = get_next_line(fd);
    char *str;
    char *str2;
    char *str3;
  
    //this part fills the hashtable with the input
    while (line)
    {
      str = malloc(4);
      while (line[i] >= 'A' && line[i] <= 'Z' && line[i])
      {
        str[i] = line[i];
          i++;
      }
      str[i] = '\0';
      int j = 0;
      while ((line[i] < 'A' || line[i] > 'Z') && line[i])
        i++;
      str2 = malloc(4);
      while (line[i] >= 'A' && line[i] <= 'Z' && line[i])
      {
        str2[j] = line[i];
          i++;
          j++;
      }
      str2[j] = '\0';
      j = 0;
      while ((line[i] < 'A' || line[i] > 'Z') && line[i])
        i++;
      str3 = malloc(4);
      while (line[i] >= 'A' && line[i] <= 'Z' && line[i])
      {
        str3[j] = line[i];
          i++;
          j++;
      }
      str3[j] = '\0';
      hashtable[get_hash(str)] = malloc(sizeof(char *) * 2);
      hashtable[get_hash(str)][0] = ft_strdup(str2);
      hashtable[get_hash(str)][1] = ft_strdup(str3);
      free(str2);
      free(str3);
      free(str);
      free(line);
      line = get_next_line(fd);
      i = j = 0;
    }
  
    //this part searches in the hashtable
    char *inst = "LLRRRLRLLRLRRLRLRLRRRLLRRLRRRLRRRLRRRLRRRLRRRLRRLRLLRRRLRRLLRLRLLLRRLRRLRLRLRLRRRLRLRRRLRRLLLRRRLLRRLLRRLLRRRLLLLRLRLRRRLRLRRRLRLLLRLRRLRRRLRRRLRRRLRRRLLRRLLLLRRLLRRLLRRLRLRRRLRRRLRRRLRRLRRRLRRLRRLRRLRLRRRLRRLRRRLRRRLRRLRLRRRLRRLLRLRRLRRRLRLRRLRRRLRRLRRLRRRLLRRRR";
    int counter = 0;
    size_t targ = get_hash("AAA");
    long int result = 0;
    while (targ != get_hash("ZZZ"))
    {
      if (inst[counter] == 'L')
      {
        targ = get_hash(hashtable[targ][0]);
      }
      else if (inst[counter] == 'R')
      {
        targ = get_hash(hashtable[targ][1]);
      }
      result++;
      counter++;
      if (inst[counter] == '\0')
        counter = 0;
    }
    ft_printf("RESULT: %l\n", result);
} 