#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 5
struct Passenger {
    int ticketNo;
    char name[50];
    int age;
    char gender[15];
};
struct Passenger queue[MAX];
int front = -1, rear = -1;
int ticketCounter = 100;
int isValidName(char name[]) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i])) {
            return 0;
        }
    }
    return 1;
}
int isDuplicate(char name[], int age) {
    for (int i = front; i <= rear; i++) {
        if (strcmp(queue[i].name, name) == 0 && queue[i].age == age) {
            return 1;
        }
    }
    return 0;
}
int isValidGender(char gender[]) {
    if (strcmp(gender, "Male") == 0 ||
        strcmp(gender, "Female") == 0 ||
        strcmp(gender, "Transgender") == 0) {
        return 1;
    }
    return 0;
}
void enqueue() {
    if (rear == MAX - 1) {
        printf("Queue Full — No more reservations\n");
        return;
    }
    struct Passenger p;
    printf("Enter Name: ");
    scanf("%s", p.name);
    if (!isValidName(p.name)) {
        printf("Invalid Name! Only alphabets allowed\n");
        return;
    }
    printf("Enter Age: ");
    if (scanf("%d", &p.age) != 1) {
        printf("Invalid Age! Enter numbers only\n");
        return;
    }
    printf("Enter Gender (Male/Female/Transgender): ");
    scanf("%s", p.gender);
    if (!isValidGender(p.gender)) {
        printf("Invalid Gender! Enter Male, Female or Transgender only\n");
        return;
    }
    if (isDuplicate(p.name, p.age)) {
        printf("Reservation already successful for this passenger!\n");
        return;
    }
    p.ticketNo = ticketCounter++;
    if (front == -1)
        front = 0;
    rear++;
    queue[rear] = p;
    printf("Reservation Successful!\n");
    printf("Your Ticket Number: %d\n", p.ticketNo);
}
void dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue Empty — No passengers\n");
        return;
    }
    struct Passenger p = queue[front];
    printf("\nPassenger Removed (Ticket Issed)\n");
    printf("Ticket No: %d\n", p.ticketNo);
    printf("Name: %s\n", p.name);
    front++;
}
void display() {
    if (front == -1 || front > rear) {
        printf("Queue Empty\n");
        return;
    }
    printf("\n--- Waiting List ---\n");
    for (int i = front; i <= rear; i++) {
        printf("Ticket: %d | Name: %s | Age: %d | Gender: %s\n",
               queue[i].ticketNo,
               queue[i].name,
               queue[i].age,
               queue[i].gender);
    }
}
int main() {
    int choice;
    while (1) {
        printf("\n===== Railway Reservation System =====\n");
        printf("1. Reserve Ticket\n");
        printf("2. Issue Ticket\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                enqueue();
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Thank You!\n");
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}
