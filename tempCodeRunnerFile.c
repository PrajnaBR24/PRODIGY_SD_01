#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void clearInputBuffer() {
    while (getchar() != '\n');
}

int getValidIntegerInput() {
    int input;
    while (scanf("%d", &input) != 1) {
        printf("Invalid input! Please enter a number: ");
        clearInputBuffer();
    }
    clearInputBuffer();
    return input;
}

int selectDifficulty() {
    int choice;
    printf("\nChoose Difficulty Level:\n");
    printf("1. Easy (1 to 50)\n");
    printf("2. Medium (1 to 100)\n");
    printf("3. Hard (1 to 500)\n");
    printf("Enter your choice (1-3): ");
    while (1) {
        choice = getValidIntegerInput();
        if (choice >= 1 && choice <= 3) break;
        printf("Invalid choice. Enter 1, 2, or 3: ");
    }
    return choice;
}

int getMaxRangeFromDifficulty(int level) {
    switch (level) {
        case 1: return 50;
        case 2: return 100;
        case 3: return 500;
        default: return 100;
    }
}

void playGame() {
    int difficulty = selectDifficulty();
    int maxRange = getMaxRangeFromDifficulty(difficulty);
    int number, guess, attempts = 0;
    char playAgain;

    srand(time(0));
    number = rand() % maxRange + 1;

    printf("\nI'm thinking of a number between 1 and %d. Try to guess it!\n", maxRange);

    do {
        printf("Enter your guess: ");
        guess = getValidIntegerInput();
        attempts++;

        if (guess > number) {
            if (guess - number <= 5)
                printf("A bit high, you're close!\n");
            else
                printf("Too high! Try again.\n");
        } else if (guess < number) {
            if (number - guess <= 5)
                printf("A bit low, you're close!\n");
            else
                printf("Too low! Try again.\n");
        } else {
            printf("🎉 Congratulations! You guessed the number in %d attempts.\n", attempts);
        }

    } while (guess != number);
}

int main() {
    char choice;

    printf("========================================\n");
    printf("     🎯 Welcome to Number Guessing Game\n");
    printf("========================================\n");

    do {
        playGame();
        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &choice);
        clearInputBuffer();
    } while (choice == 'y' || choice == 'Y');

    printf("Thanks for playing! Goodbye 👋\n");
    return 0;
}
