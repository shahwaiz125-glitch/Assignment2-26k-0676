#include <stdio.h>
#include <string.h>
void displayMenu() {
    printf("\n--- University Library Management System ---\n");
    printf("1. Member Registration\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}
void registerMember(char name[], int *studentID, int *memberType) {
    printf("Enter member name: ");
    scanf(" %[^\n]", name);
    printf("Enter student ID: ");
    scanf("%d", studentID);
    printf("Enter membership type (1 for Student, 2 for Faculty): ");
    scanf("%d", memberType);
    while (*memberType != 1 && *memberType != 2) {
        printf("Invalid membership type. Enter 1 for Student, 2 for Faculty: ");
        scanf("%d", memberType);
    }
    printf("Registration successful!\n");
}
void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks) {
    printf("\n%-10s %-30s %-10s\n", "ID", "Title", "Copies");
    printf("--------------------------------------------------\n");
    int i = 0;
    while (i < totalBooks) {
        printf("%-10d %-30s %-10d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
        i++;
    }
}
void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType) {
    if (*borrowedCount >= 3) {
        printf("Error: A member can borrow a maximum of three books at a time.\n");
        return;
    }

    int bookID, days;
    printf("Enter book ID to borrow: ");
    scanf("%d", &bookID);

    int index = -1;
    int i = 0;
    while (i < totalBooks) {
        if (bookIDs[i] == bookID) {
            index = i;
            break;
        }
        i++;
    }

    if (index == -1) {
        printf("Error: Invalid book ID.\n");
        return;
    }

    if (availableCopies[index] <= 0) {
        printf("Error: No copies available for this book.\n");
        return;
    }

    printf("Enter number of days you intend to keep the book: ");
    scanf("%d", &days);
    while (days <= 0) {
        printf("Error: Number of days must be positive. Re-enter days: ");
        scanf("%d", &days);
    }

    borrowedBookIDs[*borrowedCount] = bookID;
    (*borrowedCount)++;
    availableCopies[index]--;
    printf("Book borrowed successfully!\n");
}
float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine) {
    if (*borrowedCount == 0) {
        printf("Error: You have not borrowed any books.\n");
        return 0.0f;
    }

    int bookID;
    printf("Enter book ID to return: ");
    scanf("%d", &bookID);

    int foundIndex = -1;
    int i = 0;
    while (i < *borrowedCount) {
        if (borrowedBookIDs[i] == bookID) {
            foundIndex = i;
            break;
        }
        i++;
    }

    if (foundIndex == -1) {
        printf("Error: You have not borrowed this book.\n");
        return 0.0f;
    }

    int actualDays;
    printf("Enter actual number of days the book was kept: ");
    scanf("%d", &actualDays);
    while (actualDays <= 0) {
        printf("Error: Number of days must be positive. Re-enter days: ");
        scanf("%d", &actualDays);
    }

    int allowedDays = (memberType == 1) ? 14 : 30;
    float currentFine = 0.0f;

    if (actualDays > allowedDays) {
        int extraDays = actualDays - allowedDays;
        float rate = (memberType == 1) ? 20.0f : 10.0f;
        currentFine = extraDays * rate;
    }

    *totalFine += currentFine;

    int bookIndex = -1;
    int j = 0;
    while (j < totalBooks) {
        if (bookIDs[j] == bookID) {
            bookIndex = j;
            break;
        }
        j++;
    }

    if (bookIndex != -1) {
        availableCopies[bookIndex]++;
    }

    j = foundIndex;
    while (j < *borrowedCount - 1) {
        borrowedBookIDs[j] = borrowedBookIDs[j + 1];
        j++;
    }
    (*borrowedCount)--;

    printf("Book returned successfully. Fine incurred for this book: Rs. %.2f\n", currentFine);
    return currentFine;
}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver) {
    printf("\n--- Member Record ---\n");
    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);
    printf("Membership Type: %s\n", (memberType == 1) ? "Student" : "Faculty");
    printf("Currently Borrowed Book IDs: ");
    if (borrowedCount == 0) {
        printf("None");
    } else {
        int i = 0;
        while (i < borrowedCount) {
            printf("%d ", borrowedBookIDs[i]);
            i++;
        }
    }
    printf("\nTotal Fine Charged Before Waiver: Rs. %.2f\n", totalFine);
    printf("Final Fine Payable After Waiver: Rs. %.2f\n", fineAfterWaiver);
}

int main() {
    int bookIDs[4] = {101, 102, 103, 104};
    char bookTitles[4][50] = {"Programming in C", "Data Structures", "Database Systems", "Computer Networks"};
    int availableCopies[4] = {5, 3, 0, 4};
    int totalBooks = 4;
    char name[50] = "";
    int studentID = 0;
    int memberType = 1;
    int borrowedBookIDs[3];
    int borrowedCount = 0;
    float totalFine = 0.0f;
    float fineAfterWaiver = 0.0f;
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                registerMember(name, &studentID, &memberType);
                break;
            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
                break;
            case 3:
                borrowBook(bookIDs, bookTitles, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType);
                break;
            case 4: {
                returnBook(bookIDs, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType, &totalFine);
                fineAfterWaiver = totalFine;
                if (totalFine > 0.0f) {
                    char waiverCode[20];
                    printf("Enter membership code for fine waiver: ");
                    scanf("%s", waiverCode);
                    if (strcmp(waiverCode, "LIB2026") == 0) {
                        fineAfterWaiver = totalFine * 0.5f;
                        printf("Waiver applied successfully! 50%% discount granted.\n");
                    } else {
                        printf("Invalid membership code. No waiver applied.\n");
                    }
                }
                break;
            }
            case 5:
                displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFine, fineAfterWaiver);
                break;
            case 6:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please select between 1 and 6.\n");
        }
    } while (choice != 6);
}