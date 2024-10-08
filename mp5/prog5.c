//partners: devdp2, loganeh2
//Aryan Shah
//ECE 220 FA22

/*The purpose of MP5 was to implement the logic for a code-breaker game in C.
We were to implement 3 different functions within the given prog5.c file. 
The set_seed function utilizes the C sscanf function to find the integer
seed value from seed_str and initialized the value with the pseudo-random number
srand function. The start_game function initialized the array of numbers using C's
rand function to pick a random value between 1 and 8, inclusive. It also sets the
respective solution to the value pointing to the random value. Lastly, the start_game
function implements array, loop, and conditional logic to go through the different
game cases and award points as necessary. Print statements and outputs are implemented
as specified by the course wiki.*/   

/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
    int seed;
    char post[2];
    if (sscanf (seed_str, "%d%1s", &seed, post) == 1) //check to see if sscanf return was successful
    {
        srand(seed); //call pseudo-random number generator on seed
        return 1; //return 1 if string is valid
    }
    else
    {
        printf("set_seed: invalid seed\n"); //prints given error message
        return 0; //return 0 if the given string is invalid
    }
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
   
    return 0;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    *one = (rand() % (8 - 1 + 1)) + 1; //formula: rand() % (lower - upper + 1) + lower
    *two = (rand() % (8 - 1 + 1)) + 1; //lower = 1, upper = 8
    *three = (rand() % (8 - 1 + 1)) + 1; //set for all four solution value variables
    *four = (rand() % (8 - 1 + 1)) + 1; //set for all four solution value variables
    solution1 = *one; //point static solution variable to respective pointer
    solution2 = *two; //point static solution variable to respective pointer
    solution3 = *three; //point static solution variable to respective pointer
    solution4 = *four; //point static solution variable to respective pointer
    guess_number = 1; //guess_number should be initialized to 1
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
        int perfectMatch = 0; //set variable for perfect match
        int misplacedMatch = 0; //set variable for misplaced match
        int w, x, y, z; //variables for four guess_str integers
        int userArr[] = {*one, *two, *three, *four}; //array to store user input
        int answerArr[] = {solution1, solution2, solution3, solution4}; //array to check against real solutions
        int currentVal[] = {0, 0, 0, 0}; //array to ensure we don't check perfect matches for imperfect matches

        char post[2];
        int ret_value = sscanf(guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
        if (ret_value != 4)
        {
            printf("make_guess: invalid guess\n"); //print error message as given in wiki
            return 0; //return 0 alongside error message
        }

        int temp = 0; //variable to keep track of user's correct guesses

        for(int a = 0; a < 4; a++) //Check 1: user input >= 1 && <= 8
        {
            for(int b = 1; b <= 8; b++)
            {
                if(userArr[a] == b)
                {
                    temp++;
                    break;
                }
            }
        }

        if(temp != 4)
        {
            printf("make_guess: invalid guess\n"); //print error message as given in wiki
        }

        for(int c = 0; c < 4; c++) //Check 2: check for perfect matches b/w userArr and answerArr
        {
            if(userArr[c] == answerArr[c])
            {
                perfectMatch++; //increment # of perfect matches
                currentVal[c] = 1; //set current value out of 4 values to 1 to indicate perfect match found
            }
        }
        
        for(int d = 0; d < 4; d++) //Check 3: check for misplaced matches b/w userArr and answerArr
        {
            if(currentVal[d] != 1) //prevent perfect matches from reaching this point
            {
                for(int e = 0; e < 4; e++) //loop through 4 values
                {
                    if(userArr[d] == answerArr[e] && d != e)
                    {
                        misplacedMatch++;
                        break;
                    }
                }
            }
        }
        printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfectMatch, misplacedMatch); //print final statement from course wiki
        guess_str++; //increment guess_match

//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
    return 1;
}


