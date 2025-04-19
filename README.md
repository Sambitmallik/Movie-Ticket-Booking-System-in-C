# 🎬 Movie Ticket Booking System (C Project)

A simple console-based movie ticket booking system developed in C. This project allows users to book and cancel tickets, view movie schedules, and check seat availability. An admin feature also exists to view all bookings.

## 🚀 Features

- View movies available for the next 3 days.
- Check seat availability with real-time seating chart.
- Book tickets with seat selection and price display.
- Cancel tickets using phone number (with refund logic).
- Admin-only access to view all current bookings.
- Booking data saved in `bookings.txt` file.

## 💡 Technologies Used

- C Programming Language
- File Handling (`bookings.txt`)
- Command-line Interface (CLI)

## 🖥️ Seating Layout

Seats are displayed in a 5x5 grid with three types:
- `S`: Standard (₹200)
- `P`: Premium (₹300)
- `V`: VIP (₹500)

`[O-S]` = Available Standard Seat  
`[X-P]` = Booked Premium Seat

## 📸 Demo


## 🔐 Admin Panel

To access the admin panel (option 3), use the following password:

```plaintext
admin123

.
├── main.c           # Main source code
├── bookings.txt     # File storing booking records
├── temp.txt         # Temporary file used during cancellation
└── README.md        # Project documentation

