#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
};

struct Contact contacts[MAX];
int count = 0;

void loadContacts() {
    FILE *file = fopen("contacts.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s %s", contacts[count].name, contacts[count].phone, contacts[count].email) != EOF) {
            count++;
        }
        fclose(file);
    }
}

void saveContacts() {
    FILE *file = fopen("contacts.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }
    fclose(file);
}

void addContact() {
    if (count >= MAX) {
        printf("Contact list is full!\n");
        return;
    }
    printf("Enter Name: ");
    scanf("%s", contacts[count].name);
    printf("Enter Phone: ");
    scanf("%s", contacts[count].phone);
    printf("Enter Email: ");
    scanf("%s", contacts[count].email);
    count++;
    saveContacts();
    printf("Contact added successfully.\n");
}

void viewContacts() {
    printf("\n--- Contact List ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. Name: %s | Phone: %s | Email: %s\n", i + 1, contacts[i].name, contacts[i].phone, contacts[i].email);
    }
}

void editContact() {
    int index;
    viewContacts();
    printf("Enter contact number to edit: ");
    scanf("%d", &index);
    if (index < 1 || index > count) {
        printf("Invalid contact number.\n");
        return;
    }
    index--; // Adjust for 0-based index
    printf("Enter new Name: ");
    scanf("%s", contacts[index].name);
    printf("Enter new Phone: ");
    scanf("%s", contacts[index].phone);
    printf("Enter new Email: ");
    scanf("%s", contacts[index].email);
    saveContacts();
    printf("Contact updated successfully.\n");
}

void deleteContact() {
    int index;
    viewContacts();
    printf("Enter contact number to delete: ");
    scanf("%d", &index);
    if (index < 1 || index > count) {
        printf("Invalid contact number.\n");
        return;
    }
    index--; // Adjust for 0-based index
    for (int i = index; i < count - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    count--;
    saveContacts();
    printf("Contact deleted successfully.\n");
}

int main() {
    int choice;
    loadContacts();
    do {
        printf("\n--- Contact Management System ---\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: editContact(); break;
            case 4: deleteContact(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}