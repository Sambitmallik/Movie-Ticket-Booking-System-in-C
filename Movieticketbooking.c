#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "bookings.txt"
#define TEMPFILE "temp.txt"
#define ADMIN_PASSWORD "admin123"

#define ROWS 5  
#define COLS 5  

char seatingChart[ROWS][COLS];  
char seatTypes[ROWS][COLS];  

// Ticket Prices
#define STANDARD_PRICE 200
#define PREMIUM_PRICE 300
#define VIP_PRICE 500

// Function to initialize seating chart
void initializeSeats() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            seatingChart[i][j] = 'O';  
            if (i < 2) seatTypes[i][j] = 'S';
            else if (i < 4) seatTypes[i][j] = 'P';
            else seatTypes[i][j] = 'V';
        }
    }
}

void displayMovies() {
    printf("\n Movies Available Today:\n");
    printf("1. Avengers: Endgame - 10:00 AM, 3:00 PM, 7:00 PM\n");
    printf("2. Inception - 11:00 AM, 4:00 PM, 8:00 PM\n");
    printf("3. Titanic - 12:00 PM, 5:00 PM, 9:00 PM\n");
    printf("4. Joker - 1:00 PM, 6:00 PM, 10:00 PM\n");
    
    printf("\n Movies Available Tomorrow:\n");
    printf("5. The Dark Knight - 10:00 AM, 3:00 PM, 7:00 PM\n");
    printf("6. Interstellar - 11:00 AM, 4:00 PM, 8:00 PM\n");
    printf("7. Gladiator - 12:00 PM, 5:00 PM, 9:00 PM\n");
    printf("8. Spider-Man: No Way Home - 1:00 PM, 6:00 PM, 10:00 PM\n");
    
    printf("\n Movies Available Day After Tomorrow:\n");
    printf("9. Parasite - 10:00 AM, 3:00 PM, 7:00 PM\n");
    printf("10. The Matrix - 11:00 AM, 4:00 PM, 8:00 PM\n");
    printf("11. Black Panther - 12:00 PM, 5:00 PM, 9:00 PM\n");
    printf("12. Iron Man - 1:00 PM, 6:00 PM, 10:00 PM\n");
}

void displaySeats() {
    printf("\n Seating Chart (O = Available, X = Booked):\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("[%c-%c] ", seatingChart[i][j], seatTypes[i][j]);
        }
        printf("\n");
    }
}

// Function to get ticket price
int getPrice(char seatType) {
    if (seatType == 'S') return STANDARD_PRICE;
    if (seatType == 'P') return PREMIUM_PRICE;
    return VIP_PRICE;
}

// Function to book a ticket
void bookTicket() {
    char name[50], phone[15], email[50], movie[50];
    int movieChoice, row, col, price;

    printf("\nEnter your name: ");
    scanf(" %[^\n]", name);

    printf("Enter your phone number (10 digits): ");
    scanf("%s", phone);

    printf("Enter your email: ");
    scanf("%s", email);

    displayMovies();
    printf("\nSelect a movie (1-12): ");
    scanf("%d", &movieChoice);
    
    displaySeats();
    printf("\nEnter the seat row (0-%d): ", ROWS - 1);
    scanf("%d", &row);
    printf("Enter the seat column (0-%d): ", COLS - 1);
    scanf("%d", &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS || seatingChart[row][col] == 'X') {
        printf(" This seat is already booked!\n");
        return;
    }

    seatingChart[row][col] = 'X';
    price = getPrice(seatTypes[row][col]);
    printf("\n Ticket price: Rs. %d\n", price);

    FILE *file = fopen(FILENAME, "a");
    fprintf(file, "Name: %s, Phone: %s, Email: %s, Movie Choice: %d, Seat: [%d,%d], Price: Rs.%d\n",
            name, phone, email, movieChoice, row, col, price);
    fclose(file);

    printf("\n Ticket booked successfully!\n");
}

// Function to cancel a ticket and refund amount
void cancelTicket() {
    char phone[15], line[200];
    int row, col, found = 0, refundAmount = 0;

    printf("\nEnter your phone number to cancel: ");
    scanf("%s", phone);

    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen(TEMPFILE, "w");

    if (file == NULL || temp == NULL) {
        printf("\n Error accessing booking data!\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, phone) != NULL) {
            sscanf(line, "%*[^[][%d,%d]", &row, &col);
            seatingChart[row][col] = 'O';
            refundAmount = getPrice(seatTypes[row][col]);
            found = 1;
        } else {
            fprintf(temp, "%s", line);
        }
    }

    fclose(file);
    fclose(temp);
    remove(FILENAME);
    rename(TEMPFILE, FILENAME);

    if (found) {
        printf("\n Ticket canceled successfully! Refund Amount: Rs. %d\n", refundAmount);
    } else {
        printf("\n No booking found with this phone number!\n");
    }
}

// Function to view bookings (Admin only)
void viewBookings() {
    char password[20];
    printf("\nEnter admin password: ");
    scanf("%s", password);

    if (strcmp(password, ADMIN_PASSWORD) != 0) {
        printf("Incorrect password! Access denied.\n");
        return;
    }

    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No bookings found.\n");
        return;
    }

    char line[200];
    printf("\n--- All Bookings ---\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

// Main menu
int main() {
    int choice;
    initializeSeats();

    while (1) {
        printf("\n||===== Movie Ticket Booking System =====||\n");
        displayMovies();
        printf("\n1. Book a Ticket\n");
        printf("2. Cancel a Ticket\n");
        printf("3. View All Bookings (Admin Only)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: bookTicket(); break;
            case 2: cancelTicket(); break;
            case 3: viewBookings(); break;
            case 4: printf("\n Exiting... Have a great day!\n"); exit(0);
            default: printf("\n Invalid choice, please try again.\n");
        }
    }
    return 0;
}
