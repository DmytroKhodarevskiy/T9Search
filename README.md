# T9Search Program

## Description

T9Search is a command-line program developed for a university programming project. It reads a text file containing contacts in the "LF" (Line Feed) format, where each contact is represented by a name and a corresponding phone number separated by a newline.

The program filters the contacts based on user input and displays the matching results. It utilizes the T9 predictive text input method, commonly found on mobile phones, to search for contacts efficiently.

## Features

- Read contacts from a text file in the LF format for Unix / CRLF for Windows.
- Filter contacts based on user input.
- Utilize T9 predictive text input method for efficient searching.
- Display matching contacts with their associated phone numbers.

<br>

----

<br>

## Prerequisites

To run the T9Search program, ensure that you have the following:

- A C compiler (such as GCC) installed on your system.
- A text file containing contacts in the LF/CRLF format.


<br>

----

<br>

## Usage

Compile the program by running the following command:

```
gcc -std=c99 -lm -Wall -Werror -Wextra -pedantic -o t9search t9search.c
```

Or use the integrated makefile

```
make
```


Run the program by executing the following command:

```
./t9search < <input_file> <numbers_sequence>
```
> or
```
./t9search <numbers_sequence> < <input_file>
```

Where `<input_file>` is the name of the text file containing contacts in the LF format and the `<number_sequence>` is your desired search filter.


<br>

----

<br>

## Usage Guide

To use the T9Search program, follow these steps:

1. Use `help` in the second argument to display the usage guide.

1. Write a string of numbers to perform a non-breaking sequence contacts search. This means that the program will match contacts whose phone numbers contain the exact sequence of numbers you provide.

2. Write `-s` as the first argument to use a breaking sequence contacts search. This means that the program will match contacts whose phone numbers contain the numbers you provide in any order.

3. Write `-l L` as either the first and second argument or the second and third argument. This allows you to search for contacts with typing errors, where `L` stands for the number of errors allowed. The program will find contacts with similar phone numbers, accounting for a certain number of errors.

4. If you don't enter anything, the program will list all contacts without any filtering.

5. Make sure to follow the specified rules when entering your search query. If the rules are not followed, the program will generate an error.

### File Format

- All the contacts must be in the file that you specify when running the program.
- The file must be in the same directory as the program.
- The contacts file should be in the Unix format, with each contact listed on a new line, separating the name and phone number with a newline.

<br>

### Example


Suppose we have a contacts file named `contacts.txt` with the following contents:

<br>

  > John Doe
  >
  > 12345678
  >
  > Jane Smith
  >
  > 98765432

<br>
<br>

To search for contacts with a non-breaking sequence of numbers, you would run the program and input the desired sequence.

<!-- john doe | 5646 363
    jane smith | 5263 76484 -->

  ```
  ./t9search < contacts.txt 123
  ```
>*It will output the following:*

  ```
  You have selected search by non-breaking sequence -------------
  John Doe, 12345678
  ```
>**or**
  ```
  ./t9search < contacts.txt 5646
  ```
>*It will output the following (5646 - John):*
  
  ```
  You have selected search by non-breaking sequence -------------
  John Doe, 12345678
  ```

<br>

To perform a breaking sequence search, include the `-s` argument before entering the numbers.

  ```
  ./t9search -s < contacts.txt 1256
  ```
>*It will output the following:*

  ```
  You have selected search by breaking sequence -------------
  John Doe, 12345678
  ```
>**or**
  ```
  ./t9search -s < contacts.txt 5363
  ```
>*It will output the following (5363 - J Doe):*
  
  ```
  You have selected search by breaking sequence -------------
  John Doe, 12345678
  ```
<br>

To search for contacts with typing errors, include the `-l L` argument, where `L` is the number of errors allowed.

  ```
  ./t9search -l 1 < contacts.txt 122
  ```
>*It will output the following (12**2** vs 12**3**):*

  ```
  You have selected search by non-breaking sequence, with 1 errors check -------------
  John Doe, 12345678
  ```
>**or**
  ```
  ./t9search -l 1 < contacts.txt 565
  ```
>*It will output the following (56**5** vs 56**4**):*
  
  ```
  You have selected search by non-breaking sequence, with 1 errors check -------------
  John Doe, 12345678
  ```
<br>

If you run the program without entering anything, it will list all contacts from the file.

  ```
  ./t9search < contacts.txt
  ```
>*It will output the following:*

  ```
  John Doe, 12345678
  Jane Smith, 98765432
  ```

<br>

**Note:** however you can run program still without errors even if you do not specify the file with the contacts:
  
  ```
  ./t9search 12
  ```
  
  >**or**
  ```
  ./t9search
  ```
Will result the program to act as if the file was empty and expect the input by the user, because the `<` sign in the command line is represented as *`input`* from a file. And since it is not specified, the program will wait for the user to input the contacts. And in this specific project we are not using the file pointers, so it is the only way to redirect file information. This leads to some issues with the number of arguments, becase both 
```
./t9search 
```
>**and**
```
./t9search < contacts.txt
```
have the same amount of arguments, but the first one will expect the user to input the contacts, while the second one will read from the file. So i wasn't able to distinguish two situations properly, one is valid other is not.

<br>

_Remember to follow the correct syntax and rules to ensure the program functions as expected._

<br>

----

<br>

## Bugs

1. However, there is one bug in this program, if you have, for example, a contact with a number
`77779`
And you use search with order of numbers
`7779`.
That contact will not be found due to a certain function in the program that I tried to fix at night, which led to unpleasant consequences, and as far as I understand it did not fix the situation

2. Using the program without a contact file can lead to waiting for input from the user, as I mentioned earlier






