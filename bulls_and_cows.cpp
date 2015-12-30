/*
* Title: Bulls and Cows
* Description: A simple guessing game. The game selects a number with MAX_DIGITS in it.
*              The digits are unique. The player then tries to guess the number. If the
*              player has guessed the right number in the right position, it is a "bull".
*              If the player guessed the right number but in the wrong position, it is a
*              "cow." The game ends when either the player chooses to quit or correctly guesses
*              the number.
* Author: Dustin Chase
* Contact: dustin.chase@gmail.com
* Version: 1.0, September 2015
* Note this is an exercise from Stroustrup's "Programming Principles and Practice Using C++".
* Chapter 5, number 12. The weird include is from Stroustrup's booksite.
*/


#include "std_lib_facilities.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>

//the maximum number of digits in the solution
constexpr int MAX_DIGITS = 4;

using namespace std;

//returns true if str is all digits, false otherwise
bool is_digits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

/*obtain the user's next number guess
* Returns an integer vector containing the next guess
* If the user decides to quit guessing, an empty vector is returned
*/
vector<int> next_guess()
{
    string next_guess;
    vector<int> guess_vector;
    bool good_input;
    string quit = "|";

    do
    {
        cout << "Please enter your guess or | to quit:";
        getline(cin, next_guess);

        if (next_guess == quit)
        {
            good_input = true;
        }
        else if (next_guess.length() != MAX_DIGITS || !is_digits(next_guess))
        {
            //if the guess is too short or too long, or user has entered non-numbers
            cout << "Invalid guess. The guess must be a 4 digit integer between 0000 and 9999.\n";
            good_input = false;
        }
        else
        {
            //good input! Store it in vector and return
            for (int i = 0; i < MAX_DIGITS; i++)
            {
                guess_vector.push_back(next_guess[i] - '0');
            }
            good_input = true;
        }

    } while (!good_input);

    return guess_vector;
}

/*
* Generate a vector of MAX_DIGITS random integers
*/
vector<int> get_solution()
{
    srand(time(NULL));
    vector<int> solution;
    int next;
    bool check = true;
    while (solution.size() < MAX_DIGITS)
    {
        next = rand() % 10;

        for (int i:solution)
        {
            if (next == i)
            {
                check = false;
                break;
            }
        }
        if (check)
        {
            solution.push_back(next);
        }
        else
        {
            check = true;
        }
    }
    return solution;
}

/*
* Plays the bulls and cows game
*/
void play_game()
{
     vector<int> answer = get_solution();
      int num_bulls = 0;
      int num_cows = 0;
      int misses = 0;
      vector<int> guess_vector;

      do
      {

          //get the user's next guess. next_guess error-handles
          //bad user input. guess_vector will be empty if the user
          //has decided to stop playing
          guess_vector = next_guess();

          if (guess_vector.size() > 0)
          {

              for (int j = 0; j < MAX_DIGITS; j++)
              {
                  if (guess_vector[j] == answer[j]) //right digit in the right place
                  {
                      num_bulls++;
                  }
                  else if (std::find(answer.begin(), answer.end(), guess_vector[j])!= answer.end())
                  {
                      //right digit but in the wrong place
                      num_cows++;
                  }
                  else
                  {
                      //not using this for anything but it is easy to add and
                      //could be useful in a future iteration of the game
                      misses++;
                  }
              }
              //output the guess results and reset the counts
              cout << "You had " << num_bulls << " bulls and " << num_cows << " cows.\n";
              num_bulls = num_cows = misses = 0;
          }

      } while (guess_vector.size() > 0 && num_bulls < MAX_DIGITS);

      if (num_bulls == MAX_DIGITS) //if player guessed correctly
      {
          cout << "Great job, you guessed it!\n";
      }
      else //player didn't guess correctly
      {
          cout << "The correct answer was ";
          for (int j:answer)
          {
              cout << j;
          }
          cout << "\n";

          cout << "Better luck next time!\n";
      }

      cout << "Thank you for playing!\n";

}

int main()
{
    play_game();
    return 0;
}
