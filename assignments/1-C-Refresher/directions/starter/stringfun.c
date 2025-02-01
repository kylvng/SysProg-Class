#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int);

void reverse(char *, int);

void word_print(char *, int);
//add additional prototypes here


int setup_buff(char *buff, char *user_str, int len){
    int user_str_size = 0;
    char *user_str_pointer = user_str;
    int last_char_was_space = 1; // Start with 1 to ignore leading spaces

    while (*user_str_pointer != '\0'){
        if (*user_str_pointer == ' ' || *user_str_pointer == '\t') {
            if (!last_char_was_space) {
                buff[user_str_size++] = ' ';
                last_char_was_space = 1;
            }
        } else {
            buff[user_str_size++] = *user_str_pointer;
            last_char_was_space = 0;
        }
        user_str_pointer++;
    }

    // Remove trailing space if any
    if (user_str_size > 0 && buff[user_str_size - 1] == ' ') {
        user_str_size--;
    }

    int user_str_len = user_str_size;
    if (user_str_len > len){
        exit(1);
    }
    while (user_str_size < len){
        buff[user_str_size] = '.';
        user_str_size++;
    }
    buff[user_str_size] = '\0';

    return user_str_len; 
}

void print_buff(char *buff, int len){
    printf("Buffer:  [");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    printf("]");
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);
}

int count_words(char *buff, int str_len){
    //YOU MUST IMPLEMENT
    int word_count = 0;
    int in_word = 0;

    for (int i = 0; i < str_len; i++){
        char c = buff[i];
        if (c == ' ' || c == '\t'){
            in_word = 0;
        } else {
            if (!in_word){
                word_count++;
                in_word = 1;
            }
        }
    }

    return word_count;
}

void reverse(char *buff, int len){
    //YOU MUST IMPLEMENT
    int left = 0;
    int right = len - 1;
    while (left < right) {
        char temp = buff[left];
        buff[left] = buff[right];
        buff[right] = temp;
        left++;
        right--;
    }
}

void word_print(char *buff, int len){   
    printf("Word Print\n");
    printf("----------\n");

    int column_num = 1;
    int i = 0;

    while (i < len) {
        while (i < len && (buff[i] == ' ' || buff[i] == '\t')) {
            i++;
        }

        if (i >= len) {
            break;
        }

        printf("%d. ", column_num);
        column_num++;

        int word_length = 0;
        char word[BUFFER_SZ];

        while (i < len && buff[i] != ' ' && buff[i] != '\t') {
            word[word_length] = buff[i];
            word_length++;
            i++;
        }
        word[word_length] = '\0';

        printf("%s(%d)\n", word, word_length);
    }
    printf("\nNumber of words returned: %d\n", column_num - 1);
}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
    //      The if statement checks if the user provides at least two command-line arguments
    //      It also checks if the second argument is a flag by checking if the second argument starts with a hyphen
    //      If the user does not provide at least two arguments or the second argument does not start with a hyphen,
    //      the program will print the usage message to display usage information and exit with a return code of 1
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    //      PLACE A COMMENT BLOCK HERE EXPLAINING
    //      The if statement checks if the user provides at least three command-line arguments
    //      If the user does not provide at least three arguments, the program will print the 
    //      usage message to display usage information and exit with a return code of 1
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    // CODE GOES HERE FOR #3
    buff = malloc(BUFFER_SZ);
    if (buff == NULL){
        printf("Error allocating buffer");
        exit(99);
    }


    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos

    // printf("User String Length: %d\n", user_str_len);
    // print_buff(buff,BUFFER_SZ);
    
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options

        case 'r': {
            reverse(buff, user_str_len);
            break;
        }
        
        case 'w':
            word_print(buff, user_str_len);
            break;

        case 'x':
            if (argc != 5){
                usage(argv[0]);
                exit(1);
            }

            printf("Not Implemented!\n");
            exit(0);
            break;

        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff,BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          Providing both the buffer pointer and its length to helper functions
//          enhances safety and flexibility. It prevents buffer overflows by ensuring 
//          functions operate within the allocated memory and allows the code to easily 
//          adapt to changes in buffer size without requiring modifications to the functions