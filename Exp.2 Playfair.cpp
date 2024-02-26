#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to prepare the key matrix
void prepareKeyMatrix(char key[], char keyMatrix[5][5]) {
    int i, j, k;
    int keyLen = strlen(key);
    char keySet[26];
    int len = 0;

    // Initialize keySet array with 0
    memset(keySet, 0, sizeof(keySet));

    // Fill keySet array
    for(i = 0; i < keyLen; i++) {
        if(key[i] != ' ') {
            if(!keySet[toupper(key[i]) - 'A']) {
                keySet[toupper(key[i]) - 'A'] = 1;
                keyMatrix[len / 5][len % 5] = toupper(key[i]);
                len++;
            }
        }
    }

    // Fill remaining characters from the alphabet
    for(i = 0, k = 0; i < 26; i++) {
        if(keySet[i] == 0) {
            keyMatrix[len / 5][len % 5] = 'A' + i;
            len++;
        }
    }
}

// Function to find position of a character in the key matrix
void findPosition(char keyMatrix[5][5], char ch, int *row, int *col) {
    int i, j;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            if(keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a digraph
void encryptDigraph(char keyMatrix[5][5], char digraph[2], char encryptedDigraph[2]) {
    int row1, row2, col1, col2;

    findPosition(keyMatrix, toupper(digraph[0]), &row1, &col1);
    findPosition(keyMatrix, toupper(digraph[1]), &row2, &col2);

    if(row1 == row2) {
        encryptedDigraph[0] = keyMatrix[row1][(col1 + 1) % 5];
        encryptedDigraph[1] = keyMatrix[row2][(col2 + 1) % 5];
    } else if(col1 == col2) {
        encryptedDigraph[0] = keyMatrix[(row1 + 1) % 5][col1];
        encryptedDigraph[1] = keyMatrix[(row2 + 1) % 5][col2];
    } else {
        encryptedDigraph[0] = keyMatrix[row1][col2];
        encryptedDigraph[1] = keyMatrix[row2][col1];
    }
}

// Function to encrypt plaintext using Playfair cipher
void encryptPlayfair(char plaintext[], char key[], char ciphertext[]) {
    char keyMatrix[5][5];
    int i, j;
    int plaintextLen = strlen(plaintext);
    int k = 0;

    // Prepare key matrix
    prepareKeyMatrix(key, keyMatrix);

    // Encrypt digraphs
    for(i = 0; i < plaintextLen; i += 2) {
        char digraph[2];
        char encryptedDigraph[2];
        
        digraph[0] = plaintext[i];
        digraph[1] = (i + 1 < plaintextLen) ? plaintext[i + 1] : 'X';

        encryptDigraph(keyMatrix, digraph, encryptedDigraph);

        ciphertext[k++] = encryptedDigraph[0];
        ciphertext[k++] = encryptedDigraph[1];
    }

    ciphertext[k] = '\0';
}

int main() {
    char key[100];
    char plaintext[100];
    char ciphertext[100];

    printf("Enter the key: ");
    scanf("%[^\n]s", key);
    getchar(); // Consume the newline character

    printf("Enter the plaintext: ");
    scanf("%[^\n]s", plaintext);
    getchar(); // Consume the newline character

    // Encrypt the plaintext
    encryptPlayfair(plaintext, key, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
