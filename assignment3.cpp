/***************************************************************
 ** Program: assignment3.cpp
 ** Author: Andy James
 ** Date: 2/28/2021
 ** Description: runs tasks for assignemnt 3 A,B, and C
 ** Input: none
 ** Output: none
 ***************************************************************/
#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<cmath>


using namespace std;


void run_gcd();
void get_number(int&,string);
bool to_lowest_terms(int &, int &);
void make_fraction(int, int);
int g_c_d(int,int,int);
bool is_int(string);
int get_int(string);

void run_vowels_consonants();
bool vowel_consonants_equality(char sentence[]);
char to_lower(char);
bool is_vowel(char);

void run_palindrom_detector();
bool is_letter(char);
void purge_string(char *, char* );
bool check_palindrom(char* );

void run_word_frequency();
void get_number_2(int&);
void check(int&,char*, char*, string*);
bool is_letter_or_space(char c);
void purge_string_2(char *, char* );
int contains_word(char*,string);
string purge_word(string word);

void run_extra();
void make_top_picture(int);
void cout_numbers(int);
void make_bottom_picture(int);


/****************************************************************************************************
 ** Function: main()
 ** Description: runs run_gcd, run_vowels_consonants, run_palindrom_detector, and run_word_frequency
 ** Parameters: none
 ** Pre-condition: none
 ** Post-condition: none
 ***************************************************************************************************/
int main() { 
    
    string cont = "1";
    run_gcd(); // run part a
    while(cont == "1" || cont == "2" || cont == "3") { // run part b 
        cout << "what would you like to do, 1 for vowel v consonants, 2 for palindrom, 3 for num word frequency, else for quit: ";
        getline(cin,cont);
    if(cont == "1") {
        run_vowels_consonants();
    }
    else if (cont == "2") {
        run_palindrom_detector();
    }
    else if (cont == "3") {
        run_word_frequency();
    }
    else{}
    }
    
    run_extra(); // run part c

    return 0;
}




/****************************************************************************************
 ** Function: run_gcd()
 ** Description: initializes variables, and runs all the sub functions for making the gcd
 ** Parameters: none
 ** Pre-condition: none
 ** Post-condition: none
 ****************************************************************************************/
void run_gcd() {
    string cont = "y";
    while(cont == "y") { // continue if user puts in y
        int denominator = 0;
        int numerator = 0;
        get_number(numerator,"numerator");
        get_number(denominator, "denominator");
        while(to_lowest_terms(numerator, denominator) != true) { // repeat if denominator is 0
            cout << "Invalid input, cannot be 0" << endl;
            get_number(denominator, "denominator");
        }
        make_fraction(numerator,denominator);
        cout << "would you like to do another gcd? y for yes, else for no: ";
        getline(cin,cont);
    }
}
/***************************************************************************
 ** Function: get_number(int,string)
 ** Description: gets a whole number and repeats if not
 ** Parameters: int &number, string prompt
 ** Pre-condition: take in a int pointer and a string
 ** Post-condition: change number when given a full number
 ***************************************************************************/
void get_number(int&number, string prompt) {
    string input = "";
    cout << "input " << prompt << ": "; // prompt is either denominator or numerator
    getline(cin,input);
    if(is_int(input) != true) { // if it is not an int, re try
        cout << "Invalid input, please enter a full number" << endl;
        get_number(number,prompt);
    }
    else {
        number = get_int(input);
    }
}
/***************************************************************************
 ** Function: make_fraction(int,int)
 ** Description: makes the fraction from the numerator and denominator
 ** Parameters: int numerator, int denominator
 ** Pre-condition: take in two int variables
 ** Post-condition: output fraction string
 ***************************************************************************/
void make_fraction(int numerator, int denominator) {
    cout << "The lowest terms fraction is: ";
    if(denominator < 0) { //if the denominator is negative, switch sign, also works if both are negative
        numerator *= -1;
        denominator *= -1;
    }
    if(numerator == 0) { 
        cout << 0 << endl;
    }
    else if(denominator == 1) {
        cout << numerator << endl;
    }
    else { 
        cout << numerator << "/" << denominator << endl;
    }
}
/***********************************************************************************************************
 ** to_lowest_terms(int&,int&)
 ** Description: returns false if denom is 0, true if else, and reduces terms to lowest form
 ** Parameters: int &numerator, int &denominator
 ** Pre-condition: take in two int pointers
 ** Post-condition: false if denominator is 0, true otherwise. set numerator and denominator to lowest forms
 ***********************************************************************************************************/
bool to_lowest_terms(int &numerator, int &denominator) {
    if(denominator == 0) {
        return false;
    }
    else if(numerator == 0) { //if numerator is 0, its already at lowest terms
        return true;
    }
    else {
        int smaller = (abs(numerator) < abs(denominator)) ? abs(numerator) : abs(denominator); // find the smallest out of the two
        int gcd = g_c_d(numerator, denominator, smaller);
        numerator /= gcd;
        denominator /= gcd;
        return true;
    }
}
/***********************************************************************************************************
 ** Function: g_c_d(int,int,int)
 ** Description: finds and returns the g_c_d
 ** Parameters: int numerator, int denominator, int smaller
 ** Pre-condition: take in three ints
 ** Post-condition: return the gcd of the two numbers
 ***********************************************************************************************************/
int g_c_d(int numerator, int denominator, int smaller) {
    if((numerator % smaller == 0) && (denominator % smaller == 0)) { // starting at smaller size, go down until you find something
        return smaller;
    }
    else {
        g_c_d(numerator, denominator, smaller - 1);
    }
}
/***************************************************************
 ** Function: is_int(string)
 ** Description: determines if given string is an int
 ** Parameters: string num
 ** Pre-conditions: take in a string parameter
 ** Post-conditions: return true if it is an int, false if not
 ***************************************************************/
bool is_int(string num) {
   //if the first number is not a negative or a number
   if(num[0] != '-' && (num[0] < '0' || num[0] > '9')) {
      return false;
   }
   //if the first char is a negative and that is all there is
   if(num[0] == '-' && num.length() == 1) {

      return false;
   }
//if you dont count 0 following by numbers an int
/*   
   //if the number is 0 but has numbers following
   if(num[0] == '0' && num.length() > 1) {
      return false;
   }
   //if the number is -0
   if(num[0] == '-' && num[1] == '0') {
      return false;
   }
*/
   //if the number starts with - check
   if(num[0] == '-') {
      for(int i = 1; i < num.length(); i++) {
	      if(num[i] < '0' || num[i] > '9') {
	         return false;
	      }
      }
      return true;
   }
   //if the number dosent have negative
   for(int i = 0; i < num.length(); i++) {
      if(num[i] < '0' || num[i] > '9') {
	      return false;
      }
   }	  
   return true;
}
/***************************************************************
 ** Function: get_int(string)
 ** Description: returns an int from a string input
 ** Parameters: string prompt
 ** Pre-conditions: take in a string parameter
 ** Post-conditions: return an int that was given by a string
 ***************************************************************/
int get_int(string prompt) {
   int num = 0;
   //if the number is negative
   if(prompt[0] == '-') {  
      for(int i = 1; i < prompt.length(); i++) {
	 num += ((int)prompt[i] - 48) * pow(10,prompt.length() - 1 - i);
      }
      num *= -1;
   }

   //if the number is posotive
   else {
      for(int i = 0; i < prompt.length(); i++) {
	 num += ((int)prompt[i] - 48) * pow(10,prompt.length() - 1 - i);
      }
   }
   return num;
}



/***************************************************************
 ** Function: run_vowels_consonants
 ** Description: runs the sub functions for vowels vs consonants
 ** Parameters: none
 ** Pre-conditions: none
 ** Post-conditions: none
 ***************************************************************/
void run_vowels_consonants() {
    char sentence[1024];
    cout << "Enter a string: ";
    cin.getline(sentence,1024);
    cin.clear();
    if(vowel_consonants_equality(sentence)) {
        cout << "# vowels = # consonants" << endl;
    }
    else {
        cout << "# vowels != # consonants" << endl;
    }
    memset(sentence, '\0', 1024);
}
/************************************************************************************************
 ** Function: vowel_consonants_equality(char[])
 ** Description: returns if consonants are equal to vowels
 ** Parameters: char sentence[]
 ** Pre-conditions: take in a char array
 ** Post-conditions: return true if the amount of vowels and consonants are equal, false if else
 ************************************************************************************************/
bool vowel_consonants_equality(char sentence[]) {
    int vowel = 0;
    int consonant = 0;
    for(int i = 0; i < strlen(sentence); i++) {
        if(is_vowel(to_lower(sentence[i]))) { // if it is a vowel
            vowel++;
        }
        else if(to_lower((sentence[i])) >= 'a' && to_lower(sentence[i]) <= 'z') { // if it is a consonant
            consonant++;
        }
    }

    return vowel == consonant;
}
/************************************************************************************************
 ** Function: to_lower(char)
 ** Description: returns a lower case char letter if capital letter
 ** Parameters: char c
 ** Pre-conditions: take in a char 
 ** Post-conditions: return the lower case if it is a capital letter, or same char if else
 ************************************************************************************************/
char to_lower(char c) {
    if(c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}
/************************************************************************************************
 ** Function: is_vowel(char)
 ** Description: checks if given char is a vowel
 ** Parameters: char c
 ** Pre-conditions: take in a char 
 ** Post-conditions: return true if it is a vowel, false if else
 ************************************************************************************************/
bool is_vowel(char c) {
    if(to_lower(c) == 'a' || to_lower(c) == 'e' || to_lower(c) == 'i' || to_lower(c) == 'o' || to_lower(c) == 'u') {
        return true;
    }
    return false;
}



/************************************************************************************************
 ** Function: run_palindrom_detector()
 ** Description: runs subfunctions for finding palindroms and intializes variables
 ** Parameters: none
 ** Pre-conditions: none
 ** Post-conditions: none
 ************************************************************************************************/
void run_palindrom_detector() {
    char *sentence = new char[1024];
    char *purged = new char[1024];

    cout << "Enter a string: ";
    cin.getline(sentence,1024);
    cin.clear();

    purge_string(sentence,purged);
    if(check_palindrom(purged)) {
        cout << "this is a palindrome" << endl;
    }
    else{
        cout <<"this is not a palindrome" << endl;
    }

    memset(sentence, '\0', 1024);
    memset(purged, '\0', 1024);
    delete []sentence;
    delete []purged;
}
/************************************************************************************************
 ** Function: is_letter(char)
 ** Description: checks if char is a letter
 ** Parameters: char c
 ** Pre-conditions: take in a char 
 ** Post-conditions: return true if it is a letter, false for else
 ************************************************************************************************/
bool is_letter(char c) {
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return true;
    }
    return false;
}
/***********************************************************************************************************
 ** Function: purge_string(char*,char*)
 ** Description: removes special characters and spaces from a string by adding only letters to a new string
 ** Parameters: char *sentence, char *purged
 ** Pre-conditions: take in two char arrays
 ** Post-conditions: add only the letters from sentence to purged
 ***********************************************************************************************************/
void purge_string(char *sentence, char* purged) {
    int counter = 0;
     for(int i = 0; i < strlen(sentence); i++) { //checks if it is a letter, if so it adds it to a new string
        if(is_letter(sentence[i])) {
            *(purged + counter) = sentence[i];
            counter++;
        }
    }
}
/************************************************************************************************
 ** Function: check_palindrom(char*)
 ** Description: checks to see if the char array is a palindrom
 ** Parameters: char* purged
 ** Pre-conditions: take in a char array
 ** Post-conditions: return true if it is a palindrom, false if not
 ************************************************************************************************/
bool check_palindrom(char* purged) {
    for(int i = 0; i < strlen(purged) / 2; i++) {
        if(to_lower(purged[i]) != to_lower(purged[strlen(purged) - 1 - i])) { //if the char at i is not equal to the length - i, return false
            return false;
        }
    }
    return true;
}



/************************************************************************************************
 ** Function: run_word_frequency()
 ** Description: runs sub functions for finding word frequency and intializes variables
 ** Parameters: none
 ** Pre-conditions: none
 ** Post-conditions: none
 ************************************************************************************************/
void run_word_frequency() {
    char *sentence = new char[1024];
    char *purged = new char[1024];
    string *words;
    int num_words = 0;
    string word = "";

    cout << "Enter a string: ";
    cin.getline(sentence,1024);

    get_number_2(num_words);
    purge_string_2(sentence,purged);

    words = new string[num_words];

    for(int i = 0; i < num_words; i++) { // get words
        cout << "enter word " << i + 1 << ": ";
        getline(cin,word);
        *(words + i) = purge_word(word);
    }
    check(num_words,sentence,purged,words);
}
/***************************************************************************
 ** Function: get_number_2(int&)
 ** Description: gets a whole number larger than 0 and repeats if not
 ** Parameters: int&number
 ** Pre-condition: take in a int pointer 
 ** Post-condition: change number to a valid whole number
 ***************************************************************************/
void get_number_2(int&number) {
    string input = "";
    cout << "input number of words: ";
    getline(cin,input);
    if(is_int(input) != true) { // if input is not a full number
        cout << "Invalid input, please enter a full number" << endl;
        get_number_2(number);
    }
    else if(is_int(input) == true && get_int(input) <= 0) { // if input is 0 or lower
        cout << "invalid input, please enter a number bigger than 0" << endl;
        get_number_2(number);
    }
    else {
    number = get_int(input);
    }
}
/****************************************************************************************
 ** Function: check(int&,char*,char*,string*)
 ** Description: checks the words given by user in the sentence
 ** Parameters: int &number, string prompt
 ** Pre-condition: take in a int pointer and a string
 ** Post-condition: change number when given a full number
 ****************************************************************************************/
void check(int&num_words,char*sentence, char*purged, string*words) {
    
    for(int i = 0; i < num_words; i++) { // checks to see if purged contains word
        cout << *(words + i) << ": " << contains_word(purged,*(words + i)) << endl;
    }

    memset(sentence, '\0', 1024);
    memset(purged, '\0', 1024);

    for(int i = 0; i < num_words; i++) {
        words[i] = "";
    }

    delete [] sentence;
    delete [] purged;
    delete [] words;
}
/************************************************************************************************
 ** Function: is_letter_or_space(char)
 ** Description: checks if char is a letter or a space
 ** Parameters: char c
 ** Pre-conditions: take in a char 
 ** Post-conditions: return true if it is a letter or a space, false for else
 ************************************************************************************************/
bool is_letter_or_space(char c) {
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ') {
        return true;
    }
    return false;
}
/***********************************************************************************************************
 ** Function: purge_string_2(char*,char*)
 ** Description: removes special characters from a string by adding only letters and spaces to a new string
 ** Parameters: char *sentence, char *purged
 ** Pre-conditions: take in two char arrays
 ** Post-conditions: add only the letters and spaces from sentence to purged
 ***********************************************************************************************************/
void purge_string_2(char *sentence, char* purged) {
    int counter = 0;
     for(int i = 0; i < strlen(sentence); i++) { //adds only letters or spaces to a new string from old
        if(is_letter_or_space(sentence[i])) {
            *(purged + counter) = sentence[i];
            counter++;
        }
    }
}
/***********************************************************************************************************
 ** Function: contains_word(char,string)
 ** Description: checks to see how many times a char array contains a certain word
 ** Parameters: char *purged, string word
 ** Pre-conditions: take in a char array and a word
 ** Post-conditions: return the amount of times the word repeats in the given char array
 ***********************************************************************************************************/
int contains_word(char*purged,string word) {
    int checker = 0;
    int count = 0;

   for(int i = 0; i < strlen(purged); i++) {   
      if(to_lower(purged[i]) == to_lower(word[checker])) {				 
	      checker++;					   
      }		
      else {
	    checker = 0;
		}    
      if(checker == word.length()) {
          if(i == strlen(purged) - 1 || *(purged + i + 1) == ' ') {
	      count++;
          }
          checker = 0;
      }
   }
   return count;
}
/***********************************************************************************************************
 ** Function: purge_word(string)
 ** Description: takes out special characters in a word
 ** Parameters: string word
 ** Pre-conditions: take in a string
 ** Post-conditions: return string without any special characters
 ***********************************************************************************************************/
string purge_word(string word) {
    string new_word = "";
    for(int i = 0; i < word.length(); i++) { // gets rid of all special characters given by user in the word
        if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z')) {
            new_word += word[i];
        }
    }
    return new_word;
}



/***********************************************************************************************************
 ** Function: run_extra()
 ** Description: prints out a diamond shape pattern
 ** Parameters: none
 ** Pre-conditions: none
 ** Post-conditions: none
 ***********************************************************************************************************/
void run_extra() {
    string cont = "y";
    while (cont == "y") {
    int size = 0;
    cout << "how many rows(odd #): ";
    cin >> size;
    cin.clear();
    if(size == 1) {  // if the user wants a diamond of 1, print 1
        cout << "1" << endl;
    }
    else {
    make_top_picture(size);
    cout_numbers(size);
    cout << endl;
    make_bottom_picture(size);
    cout << "would you like to go agian? y for yes, else for no: ";
    cin >> cont;
    }
    }
}
/***********************************************************************************************************
 ** Function: make_top_picture(int)
 ** Description: prints top of diamond
 ** Parameters: int size
 ** Pre-conditions: take in a int
 ** Post-conditions: none
 ***********************************************************************************************************/
void make_top_picture(int size) {
    int spaces = size/2;
    int numbers = 1;
    for(int i = 0; i < size/2; i++) {
        for(int j = 0; j < spaces; j++) {
            cout << " ";
        }
        spaces--;
        cout_numbers(numbers);
        numbers += 2;
        cout << endl;
    }
}
/***********************************************************************************************************
 ** Function: make_bottom_picutre(int)
 ** Description: prints bottom of diamond
 ** Parameters: int size
 ** Pre-conditions: take in a int
 ** Post-conditions: none
 ***********************************************************************************************************/
void make_bottom_picture(int size) {
    int spaces = 1;
    int numbers = size - 2;
    for(int i = size/2; i > 0; i--) {
        for(int j = spaces; j > 0; j--) {
            cout << " ";
        }
        spaces++;
        cout_numbers(numbers);
        numbers -= 2;
        cout << endl;
    }
}
/***********************************************************************************************************
 ** Function: cout_numbers(int)
 ** Description: outputs 1 to the number
 ** Parameters: int numbers
 ** Pre-conditions: take in an int
 ** Post-conditions: none
 ***********************************************************************************************************/
void cout_numbers(int numbers) {
    for(int i = 1; i <= numbers; i++) {
        cout << i;
    }
}

