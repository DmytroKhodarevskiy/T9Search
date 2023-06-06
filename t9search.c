#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define M_S 101 // Max_Size

char name_string[M_S];
bool read_line();
void trans();
bool output_print(int control_switch, char *arg[], int input_l);
bool num_arg_check(int switch_check, char *arg[]);
void clear_string(char string[]);
bool control(char input_argv[M_S]);
bool control_s(char input_argv[M_S]);
bool control_l(char input_argv[M_S], int input_l);

int main(int argc, char *argv[])
{
  // if (argc == 1)
  // {
  //   fprintf(stderr, "You have not entered any arguments!\n"); 
  //   fprintf(stderr, "Try: ./t9search help\n");
  //   return 1;
  // }
  if (argc < 2)
  { 
    char print_name[M_S];
    char print_phone[M_S];
    while(1)
    {
      bool flag = read_line();
      if (flag == false)
      {
        fprintf(stderr, "Your name or number is too long!\n");
        return 1;
      }
      if (name_string[0] == '\0')            //blank spot check
         break;

      int length = strlen(name_string);
      for (int j = 0; j < length; j++)       //copying line for print
          print_name[j] = name_string[j]; 
      print_name[length] = '\0';
      clear_string(name_string);

      flag = read_line();
      if (flag == false)
      {
        fprintf(stderr, "Your name or number is too long!\n");
        return 1;
      }

      length = strlen(name_string);
      for (int j = 0; j < length; j++)
          print_phone[j] = name_string[j]; 
      print_phone[length] = '\0';
      clear_string(name_string);

      printf("%s, %s\n", print_name, print_phone);

      clear_string(print_name);
      clear_string(print_phone);
    }  
    return 0; 
  }
  else if (strcmp(argv[1], "help") == 0)
  {
    fprintf(stderr, "How to use the program:\n");
    fprintf(stderr, "1) Write a string of numbers to use non-breaking sequence contacts search\n");
    fprintf(stderr, "2) Write -s in first place to use breaking sequence contacts search\n");
    fprintf(stderr, "3) Write -l L (either in 1st and 2nd place or 2nd and 3rd place) to search for\n");
    fprintf(stderr, "contacts with typing errors (L stands for the number of errors allowed)\n");
    fprintf(stderr, "4) If you do not enter anything, the program will list all contacts\n");
    fprintf(stderr, "5) If the rules are not followed, the program will generate an error!\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "All the contacts must be in the file that you are specifying, the file must be\n");
    fprintf(stderr, "in the same directory as the program and has a unix format\n");
    return 0;
  }
  else if (argc == 2)
  {
    if (num_arg_check(1, argv) == false)
       return 1;
    fprintf(stderr, "You have selected search by non-breaking sequence -------------\n"); 
    if (output_print(0, argv, 0) == false)
       return 1;
  }
  else if(strcmp(argv[1], "-s") == 0)
  {
    if (num_arg_check(2, argv) == false)
       return 1;
    fprintf(stderr, "You have selected search by breaking sequence -------------\n");
    if (output_print(1, argv, 0) == 0)
       return 1;
  }
  else if((strcmp(argv[2], "-l") == 0) && (argc == 4))
  {
    if (num_arg_check(1, argv) == false)
       return 1;
    if (num_arg_check(3, argv) == false)
       return 1;
    fprintf(stderr, "You have selected search by non-breaking sequence, with %s errors check -------------\n", argv[3]);
    int x = atoi(argv[3]);
    if (output_print(2, argv, x) == 0)
       return 1;
  }
  else if((strcmp(argv[1], "-l") == 0) && (argc == 4))
  {
    if (num_arg_check(3, argv) == false)
       return 1;
    if (num_arg_check(2, argv) == false)
       return 1;
    fprintf(stderr, "You have selected search by non-breaking sequence, with %s errors check -------------\n", argv[2]);
    int x = atoi(argv[2]);
    if (output_print(3, argv, x) == 0)
       return 1;
  }
  else
  {
    fprintf(stderr, "One string of numbers expected, print help for instructions\n");
    return 1;
  }
  return 0;
}

void clear_string(char string[])
{
  for (int i = 0; string[i] != '\0'; i++)
      string[i] = 0;
}

bool num_arg_check(int switch_check, char *arg[])
{
  char *ptr;
  if (switch_check == 1)
      ptr = arg[1];
  if (switch_check == 2)
      ptr = arg[2];
  if (switch_check == 3)
      ptr = arg[3];
  for (int i = 0; i < M_S; i++)
  {
    if((*(ptr + i) < '0') || ('9' < *(ptr + i)))
    {
      fprintf(stderr, "Please enter a sequence of numbers, print help for instructions\n");
      return false;
    }
    if (*(ptr + i + 1) == '\0')             //checking if the next symbol is 0
       break;
  }
  return true;
}

bool output_print(int control_switch, char *arg[], int input_l)
{
  int count_output_contacts = 0;
    while(1)
    {
      char print_name[M_S];
      char print_phone[M_S];
      int check;

      bool flag = read_line();
      if (flag == false)
      {
        fprintf(stderr, "Your name or number is too long!\n");
        return false;
      }

      if (name_string[0] == '\0')           //blank spot check
         break;

      int length = strlen(name_string);
      for (int j = 0; j <= length; j++)     //copying line for print
          print_name[j] = name_string[j]; 
      trans();                              //translating to numbers  
      print_name[length] = '\0';

      if (control_switch == 0)
         check = control(arg[1]);
      if (control_switch == 1)
         check = control_s(arg[2]);
      if (control_switch == 2)
         check = control_l(arg[1], input_l);
      if (control_switch == 3)
         check = control_l(arg[3], input_l);
      int check1 = check;
      clear_string(name_string);

      flag = read_line();
      if (flag == false)
      {
        fprintf(stderr, "Your name or number is too long!\n");
        return false;
      }

      length = strlen(name_string);
      for (int j = 0; j < length; j++)
          print_phone[j] = name_string[j]; 
      trans();
      print_phone[length] = '\0';

      if(control_switch == 0)
        check = control(arg[1]);
      if(control_switch == 1)
        check = control_s(arg[2]);
      if(control_switch == 2)
        check = control_l(arg[1], input_l);
      if(control_switch == 3)
        check = control_l(arg[3], input_l);
      int check2 = check;
      clear_string(name_string);

      if(check2 == 1)
      {
        printf("%s, %s\n", print_name, print_phone);
        count_output_contacts++;
        continue;
      }
      else if(check1 == 1)
      {
        printf("%s, %s\n", print_name, print_phone);
        count_output_contacts++;
        continue;
      }
      else
        continue;

      clear_string(print_name);
      clear_string(print_phone);
    }
    
  if(count_output_contacts == 0)
  {
    fprintf(stderr, "Not found\n");
    return true;  
  }
  return true;  
}

bool control_s(char input_argv[M_S])
{
  int count = 0;
  int place = 0;
    for (int j = 0; input_argv[j] != '\0'; j++)
    {
      for (int i = place; name_string[i] != '\0'; i++)
      {
        if (name_string[i] == input_argv[j])
        {
           count += 1;
           place = i + 1;
           break;
        }
      }
    } 
  int length_ctrl = strlen(input_argv);      
  if (length_ctrl == count)                 //if all argv numbers match 
     return true;
  else
     return false;
}

// bool control(char input_argv[M_S])
// {
//   int count = 0;                                  //extra is the check for not throwing out the needed symbol    
//   int extra = 0;                                  //if 7779 is in name and we typed 779 
//   int extra_end = 0;                              //(or 777779 (i ruined my code for this bug))
//   int extra_count = 0;                            //I'm sorry for such a messy code, I noticed this bug by accident     
//   int minus = 0;                                  //8 hours before deadline and barely fixed it within 3 hours, i need to sleep 
//   bool only_once = false;
//   int length_ctrl = strlen(input_argv);      
//   for (int i = 0 ; name_string[i] != '\0'; i++)
//   {
//     count = 0;
//     if (name_string[i] == input_argv[0])
//     {
//       extra = 0;
//       count++;
//        for (int j = 0; input_argv[j] != '\0'; j++)   //while argv is not over
//        {
//         if (name_string[i] == name_string[i+1])
//         {
//           extra++;
//           if(only_once == false)
//             extra_end++;
//         }
//         if (input_argv[j] == input_argv[j+1])
//           minus++;                                   //minus is count to go back to (if we have 777779 and argv                                           
//         if (name_string[i+1] == input_argv[j+1])     //is 7779, we go back by 3 and start control again)    
//         {                                            //check for next number
//           count++;
//           i++;
//         }
//        }
//        if (extra >= 2)
//        {
//         extra_count++;
//         if(extra_count < extra_end)                  //extra_count is count of such operations
//         {                                            //extra_end is max count of such ops allowed 
//           i -= minus - 1;   
//           only_once = true;    
//         }
//         if (extra % 2 > 0)                           //if we have odd count of same kind of symbols, 
//            i -= 1;                                   //go back to one more 
//        }  
//     }
//     if (length_ctrl == count)                       //if all argv numbers match
//        return true;
//   }
//   return false;
// }

bool control(char input_argv[M_S])
{
  
  int count = 0;
  int length_ctrl = strlen(input_argv);      
  for (int i = 0 ; name_string[i] != '\0'; i++)
  {
    count = 0;
    if (name_string[i] == input_argv[0])
    {
      count++;
       for (int j = 0; input_argv[j+1] != '\0'; j++)
       {
        if (name_string[i+1] == input_argv[j+1])
        {
          count++;
          i++;
        }
       }
    }
    if (length_ctrl == count)
    {
      return true;
    }
  }
  return false;
}

bool control_l(char input_argv[M_S], int input_l)
{
 int count = 0;                                     
  int length_ctrl = strlen(input_argv);      
  for (int i = 0 ; name_string[i] != '\0'; i++)
  {
    count = 0;
    if (name_string[i] == input_argv[0])
    {
      count++;
      for (int j = 0; input_argv[j+1] != '\0'; j++)
       {
        if (name_string[i+1] == input_argv[j+1])
        {
          count++;
          i++;
        }
       }
    }
    if (length_ctrl <= count + input_l)             //if all argv numbers match + errors count
       return true;
  }
  return false;
}

bool read_line()
{
  char last;
  int check = 0;
    for (int i = 0; (last = getchar()) != '\n' ; i++) //(╯°□°）╯︵ ┻━┻
    {
      if (last == EOF) 
         break;
      name_string[i] = last;
      check++;
    }
  
  if (check > M_S - 1)
     return false;
  return true;  
}

char* strlwr2 (char* s)
{
  int s_length = strlen(s);
  for (int i = 0; i < s_length; ++i)
  {
    if (s[i] >= 'A' && s[i] <= 'Z')
       s[i] += 'a' - 'A';
  }
  return s;
}

void trans()
{
  strlwr2(name_string);
  int name_len = strlen(name_string);
  for(int i = 0 ; i < name_len ; i++)
  {
    switch (name_string[i])
    {
      case 'a': case 'b': case 'c':
      name_string[i] = '2';
      break;
  
      case 'd': case 'e': case 'f':
      name_string[i] = '3';
      break;
  
      case 'g': case 'h': case 'i':
      name_string[i] = '4';
      break;
  
      case 'j': case 'k': case 'l':
      name_string[i] = '5';
      break;
  
      case 'm': case 'n': case 'o':
      name_string[i] = '6';
      break;
  
      case 'p': case 'q': case 'r': case 's':
      name_string[i] = '7';
      break;
  
      case 't': case 'u': case 'v':
      name_string[i] = '8';
      break;
  
      case 'w': case 'x': case 'y': case 'z':
      name_string[i] = '9';
      break;
  
      case '+':
      name_string[i] = '0';
      break;
    }
  }
    name_string[name_len] = '\0';                     //setting last symbol to 0
}  