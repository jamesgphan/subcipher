#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int keyValue(int keyletter);
int convertToDecimal(int input, int position);

int main(int argc, char *argv[])
{
    // if there are more commandline arg other than the executable and the 2nd input
    // or no 2nd input at all
    if (argc >= 3 || argc == 1) {
        // display error and exit program
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // if the length of the second commandline arg (the cipherkey) is not 26
    if (strlen(argv[1]) != 26) {
        // display error and exit program
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    int key[26];
    // iterate through each character of the given key
    for (int i = 0; i < strlen(argv[1]); i++) {
        // if as long one of the characters isn't a letter,
        // display error and exit program
        if (!isalpha(argv[1][i])) {
            printf("Usage: ./substitution key\n");
            return 1;
        }

        // change the key so that it displays alphabetical rank of each character
        // this is to avoid a distinction between upper and lowercase
        // {24,19,13,18,7,10,...} for {Y,T,N,S,H,K,...}
        key[i] = keyValue(argv[1][i]);
    }

    // starts with key[j=0], then moves to the next for-loop which will start at key[k=0+1=1]
    // so, key[j=0] and key[k=1] are compared
    // once passed, key[j=0] will be compared to key[k=2] and so forth...
    // the second for-loop is exited once key[k=25] is reached
    // the first for-loop goes through another iteration (key[j=1])...
    // iterate through the key
    for (int j = 0; j < strlen(argv[1]); j++) {
        // iterate through the key but with an offset of +1
        for (int k = j + 1; k < strlen(argv[1]); k++) {
            // if keys become equal at some point, display error and exit program
            if (key[j] == key[k]) {
                printf("Duplicate Letters!\n");
                return 1;
            }
       }
    }

    // prompt user for a message to be encrypted
    printf("plaintext:  ");
    char message[7];
    scanf("%[^\n]%*c", message);
    // display for after encryption
    printf("ciphertext: ");

    // iterate through the original message
    for (int x = 0; x < strlen(message); x++) {
        // change the character to decimal
        int deci = message[x];
        // find alphabetical rank of character in og message via keyValue(deci),
        // that gives the alphabetical rank of the new character
        int final = key[keyValue(deci)];
        // determine if letter from original message is upper, lower, or nonletter
        // convert that to decimal, then set to char
        char output = convertToDecimal(deci, final);
        // display ciphertext
        printf("%c", output);
    }

    printf("\n");

    return 0;
}

int keyValue(int keyletter) {
    if (keyletter >= 65 && keyletter <= 90) {
        int value = keyletter - 65;
        return value;
    } else if (keyletter >= 97 && keyletter <= 122) {
        int value = keyletter - 97;
        return value;
    } else {
        return 0;
    }
}

int convertToDecimal(int input, int position) {
    if (input >= 65 && input <= 90) {
        int decimal = position + 65;
        return decimal;
    } else if (input >= 97 && input <= 122) {
        int decimal = position + 97;
        return decimal;
    } else {
        int nonletter = input;
        return nonletter;
    }
}
