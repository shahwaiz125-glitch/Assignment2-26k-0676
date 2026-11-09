#include <stdio.h>
int main() {
    int rows, seats_per_row;
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of seats per row: ");
    scanf("%d", &seats_per_row);
    int seat[20][20];
    printf("Enter the seating status (0 for available, 1 for booked):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < seats_per_row; j++) {
            scanf("%d", &seat[i][j]);
        }
    }
    printf("\nInitial Seating Arrangement:\n");
    printf("  ");
    for (int j = 0; j < seats_per_row; j++) {
        printf("%d ", j);
    }
    printf("\n");
    for (int i = 0; i < rows; i++) {
        printf("R%d ", i);
        for (int j = 0; j < seats_per_row; j++) {
            if (seat[i][j] == 0) {
                printf("_ ");
            } else {
                printf("X ");
            }
        }
        printf("\n");
    }
    int total_free = 0;
    printf("\nSeat Availability Report:\n");
    for (int i = 0; i < rows; i++) {
        int row_free = 0;
        for (int j = 0; j < seats_per_row; j++) {
            if (seat[i][j] == 0) {
                row_free++;
            }
        }
        total_free += row_free;
        printf("Row %d available seats: %d\n", i, row_free);
    }
    printf("Total free seats in the entire hall: %d\n", total_free);

    int k;
    do {
        printf("\nEnter number of customers in the group (k): ");
        scanf("%d", &k);
        if (k <= 0 || k > seats_per_row) {
            printf("Invalid group size! Must be between 1 and %d.\n", seats_per_row);
        }
    } while (k <= 0 || k > seats_per_row);
    int mid = rows / 2;
    int found = 0;
    int alloc_row = -1;
    int alloc_start = -1;
    for (int d = 0; d < rows && !found; d++) {
        int r1 = mid - d;
        int r2 = mid + d;
        
        int rows_to_check[2];
        int count = 0;

        if (r1 >= 0 && r1 < rows) {
            rows_to_check[count++] = r1;
        }
        if (d > 0 && r2 >= 0 && r2 < rows && r2 != r1) {
            rows_to_check[count++] = r2;
        }
        for (int idx = 0; idx < count && !found; idx++) {
            int r = rows_to_check[idx];
            int consecutive = 0;
            int start_seat = -1;
            
            for (int c = 0; c < seats_per_row; c++) {
                if (seat[r][c] == 0) {
                    if (consecutive == 0) {
                        start_seat = c;
                    }
                    consecutive++;
                    if (consecutive == k) {
                        alloc_row = r;
                        alloc_start = start_seat;
                        found = 1;
                        break;
                    }
                } else {
                    consecutive = 0;
                    start_seat = -1;
                }
            }
        }
    }
    if (found) {
        printf("\nGroup of %d seated in Row %d, Seats %d to %d\n", k, alloc_row, alloc_start, alloc_start + k - 1);
        
        for (int c = alloc_start; c < alloc_start + k; c++) {
            seat[alloc_row][c] = 1;
        }
        
        printf("\nUpdated Seating Arrangement:\n");
        printf("  ");
        for (int j = 0; j < seats_per_row; j++) {
            printf("%d ", j);
        }
        printf("\n");
        for (int i = 0; i < rows; i++) {
            printf("R%d ", i);
            for (int j = 0; j < seats_per_row; j++) {
                if (seat[i][j] == 0) {
                    printf("_ ");
                } else {
                    printf("X ");
                }
            }
            printf("\n");
        }
        
        int new_total_free = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < seats_per_row; j++) {
                if (seat[i][j] == 0) {
                    new_total_free++;
                }
            }
        }
        printf("Remaining available seats: %d\n", new_total_free);
    } else {
        printf("\nSorry, no row contains %d consecutive available seats. Seating plan remains unchanged.\n", k);
    }
    return 0;
}