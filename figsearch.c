/**
 * @file figsearch.c
 * @author Adam Vágner <xvagnea00@fit.vutbr.cz>
 * @brief IZP PROJECT 2 => PRÁCE S DATOVÝMI STRUKTURAMI
 * @date 20-11-2024
 *
 */

#include <stdio.h> 
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    int rows;         
    int columns; 
} Image;

// Help menu (\t\t - tab character)
void print_help() {
    printf("--help\t\tPrint this help message\n");
    printf("test\t\tCheck if the bitmap file is valid\n");
    printf("hline\t\tFind the longest horizontal line\n");
    printf("vline\t\tFind the longest vertical line\n");
    printf("square\t\tFind the largest square\n");
}

// Checking right form of matrix
int is_valid_bitmap(char *filename, Image *img) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Invalid\n");
        return 0;
    }

    // Read rows and columns (just for discarding)
    if (fscanf(file, "%d %d", &img->rows, &img->columns) != 2) {
        fprintf(stderr, "Invalid\n");
        fclose(file);
        return 0;
    }

    // Check if there is some matrix
    if (img->rows <= 0 || img->columns <= 0) {
        fprintf(stderr, "Invalid\n");
        fclose(file);
        return 0;
    }

    char ch;
    int binary_count = 0;

    // Check 0, 1 and whitespace
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '0' || ch == '1') {
            binary_count++;
        } else if (isspace(ch)) {
            continue;
        } else {
            fprintf(stderr, "Invalid\n");
            fclose(file);
            return 0;
        }
    }

    // Check if numbers in matrix  ==  rows * columns
    if (binary_count != img->rows * img->columns) {
        fprintf(stderr, "Invalid\n");
        fclose(file);
        return 0;
    }

    printf("Valid\n");
    fclose(file);
    return 1;
}

// Searching for longest horizontal line
int find_hline(char *filename, Image *img) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Invalid\n");
        return 0;
    }

    // Read rows and columns 
    if (fscanf(file, "%d %d", &img->rows, &img->columns) != 2) {
        fprintf(stderr, "Invalid\n");
        fclose(file);
        return 0;
    }

    // Check if there is some matrix
    if (img->rows <= 0 || img->columns <= 0) {
        fprintf(stderr, "Invalid\n");
        fclose(file);
        return 0;
    }

    int start[2] = {0};             // Start index (row, column)
    int end[2] = {0};               // End index 
    int temporary_start[2] = {0};   // Temporary start index 
    int max_streak = 0;             // Longest streak
    int streak_count = 0;           // Current strak          
    int binary_count = 0;           // Number of numbers (check)

    int help_index = 0;

    // Array of pointers, one pointer for one row
    int **matrix = malloc(img->rows * sizeof(int *));
    // Pointer for each column
    for (int i = 0; i < img->rows; i++) {
        matrix[i] = malloc(img->columns * sizeof(int));
    }

    // Read the matrix data
    for (int idx = 0; idx < img->rows; idx++) {
        streak_count = 0; // Reset streak for each row
        for (int index = 0; index < img->columns; index++) {
            binary_count++; // Right amount of numbers in matrix (check)
            if (fscanf(file, "%d", &matrix[idx][index]) != 1) {
                fprintf(stderr, "Invalid\n");
                fclose(file);
                return 0;
            }
            // If negative
            if(matrix[idx][index] < 0 ){
                fprintf(stderr, "Invalid\n");
                return 0;
            }
            else if(matrix[idx][index] == 1){
                if (streak_count == 0) {  // Start of a new streak
                    temporary_start[0] = idx;
                    temporary_start[1] = index;
                }
                streak_count++;
            } else{
                // If the streak is greater than max_streak, update
                if (streak_count > max_streak) {
                    max_streak = streak_count;
                    start[0] = temporary_start[0];
                    start[1] = temporary_start[1];
                    end[0] = idx;
                    end[1] = index - 1; 
                    help_index = idx;
                }

                // Current streak is closer to the left 
                if ((streak_count == max_streak) && (temporary_start[1] > index)) {
                    if (idx > help_index) {
                        start[0] = temporary_start[0];
                        start[1] = temporary_start[1];
                        end[0] = idx;
                        end[1] = index - 1;
                        help_index = idx;
                    }
                }
                
                streak_count = 0;  // Reset streak 
            }
        }

        // Check streak at last column 
        if (streak_count > max_streak) {
            max_streak = streak_count;
            start[0] = temporary_start[0];
            start[1] = temporary_start[1];
            end[0] = idx;
            end[1] = img->columns - 1;
        }
        streak_count = 0; 
    }

    // Check if counted numbers in matrix  ==  matches rows * columns
    if (binary_count != img->rows * img->columns) {
        fprintf(stderr, "Invalid\n");
        fclose(file);
        return 0;
    }

    // No string our output
    if (max_streak == 0) {
        printf("Not found\n");
    } else {
        // Print the longest horizontal line
        printf("%d %d %d %d\n", start[0], start[1], end[0], end[1]);
    }

    // Free dynamically allocated memory
    for (int i = 0; i < img->rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    fclose(file);
    return 1;
}

// Searching for longest vertical line
int find_vline(char *filename, Image *img) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Invalid\n");
        return 0;
    }

    // Read rows and columns 
    if (fscanf(file, "%d %d", &img->rows, &img->columns) != 2) {
        fprintf(stderr, "Invalid\n");
        fclose(file);
        return 0;
    }

    // Check if there is some matrix
    if (img->rows <= 0 || img->columns <= 0) {
        fprintf(stderr, "Invalid\n");
        fclose(file);
        return 0;
    }

    int start[2] = {0};             // Start index (row, column)
    int end[2] = {0};               // End index 
    int temporary_start[2] = {0};   // Temporary start index
    int max_streak = 0;             // Longest streak
    int streak_count = 0;           // Current strak          
    int binary_count = 0;           // Number of numbers (check)

    // Pointers for each column
    int **matrix = malloc(img->columns * sizeof(int *));

    // Also pointer for each row in column
    for (int i = 0; i < img->columns; i++) {
        matrix[i] = malloc(img->rows * sizeof(int));
    }

    // Read the matrix data
    for (int i = 0; i < img->rows; i++) {
        for (int j = 0; j < img->columns; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) { // If successfull
                fprintf(stderr, "Invalid\n");
                fclose(file);
                return 0;
            }
            binary_count++; // Checking right amount of writen binary numbers
        }
    }

    // Check if number of binary  ==  matrix size
    if (binary_count != img->rows * img->columns) {
        fprintf(stderr, "Invalid\n");
        fclose(file);
        return 0;
    }

    fclose(file); // Close the file after reading the matrix

    // Going by columns in readed matrix
    for (int idx = 0; idx < img->columns; idx++) {
        streak_count = 0; // Reset streak for new column

        for (int index = 0; index < img->rows; index++) {
            // If negative number
            if(matrix[index][idx] < 0 ){
                fprintf(stderr, "Invalid\n");
                return 0;
            }
            else if (matrix[index][idx] == 1) {
                if (streak_count == 0) {  // Start of a new streak
                    temporary_start[0] = index;
                    temporary_start[1] = idx;
                }
                streak_count++;
            } else {
                // If the streak is greater than max_streak, update
                if (streak_count > max_streak) {
                    max_streak = streak_count;
                    start[0] = temporary_start[0];
                    start[1] = temporary_start[1];
                    end[0] = index - 1;
                    end[1] = idx;
                    index--;
                }

            // Same streak length -> closer to the left-top corner
            if (streak_count == max_streak) {
                if (( temporary_start[0] < start[0]) || 
                (temporary_start[0] == start[0] && temporary_start[1] < start[1])) {
                    start[0] = temporary_start[0];
                    start[1] = temporary_start[1];
                    end[0] = index - 1;
                    end[1] = idx;
                    index--;
                }
            }

            streak_count = 0; // Reset streak 
        }
    }

        // Check if the streak ended at the last row
        if (streak_count > max_streak) {
            max_streak = streak_count;
            start[0] = temporary_start[0];
            start[1] = temporary_start[1];
            end[0] = img->rows - 1;
            end[1] = idx;
        }
    }
           
    // No streak or printf
    if (max_streak == 0) {
        printf("Not found\n");
    } else {
        printf("%d %d %d %d\n", start[0], start[1], end[0], end[1]);
    }

    // Free dynamically allocated memory for the matrix
    for (int i = 0; i < img->rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 1;
}

// Searching for biggest square
int find_square(char *filename, Image *img) {    
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Invalid\n");
        return 0;
    }

    // Read rows and columns 
    if (fscanf(file, "%d %d", &img->rows, &img->columns) != 2) {
        fprintf(stderr, "Invalid\n");
        fclose(file);
        return 0;
    }

    // Check if there is some matrix
    if (img->rows <= 0 || img->columns <= 0) {
        fprintf(stderr, "Invalid\n");
        fclose(file);
        return 0;
    }

    // Dynamically allocate memory for the matrix
    int **matrix = malloc(img->rows * sizeof(int *));
    for (int i = 0; i < img->rows; i++) {
        matrix[i] = malloc(img->columns * sizeof(int));
    }

    // Read the matrix data
    int binary_count = 0; // Check the number in matrix, if '1' and '0' only
    for (int idx = 0; idx < img->rows; idx++) {
        for (int index = 0; index < img->columns; index++) {
            if (fscanf(file, "%d", &matrix[idx][index]) != 1) {
                fprintf(stderr, "Invalid\n");
                fclose(file);
                return 0;
            }
            binary_count++;
            if(matrix[idx][index] < 0 ){
                fprintf(stderr, "Invalid\n");
                return 0;
            }
        }
    }

    // Check if the number of pixels  ==  matches rows * columns
    if (binary_count != img->rows * img->columns) {
        fprintf(stderr, "Invalid\n");
        fclose(file);
        return 0;
    }

    int max_size = 0;         // Size of the largest square
    int square_start[2] = {0}; // Top-left corner
    int square_end[2] = {0};   // Bottom-right corner

    // Largest possible side (given matrix possibilities)
    int size = img->rows; 
    if (img->columns < size) {
        size = img->columns; 
    }

    // Searching from largest possible to 1x1
    for (; size >= 1; size--) {
        for (int idx = 0; idx <= img->rows - size; idx++) {
            for (int index = 0; index <= img->columns - size; index++) {
                int valid = 1; // Expect valid square


            // Check the horizontal lines (top and bottom) of the square
            for (int x = index; x < index + size; x++) {
                // If any value in rows is not 1, mark this as invalid
                if (matrix[idx][x] != 1 || matrix[idx + size - 1][x] != 1) {
                    valid = 0; 
                    break; 
                }
            }

            // Check the vertical lines (left and right) of the square
            for (int y = idx; y < idx + size; y++) {
                // If any value in column is not 1, mark this as invalid
                if (matrix[y][index] != 1 || matrix[y][index + size - 1] != 1) {
                    valid = 0; 
                    break; 
                }
            }
            
            // If it's a valid 
            if (valid) {
                max_size = size;
                square_start[0] = idx;
                square_start[1] = index;
                square_end[0] = idx + size - 1;
                square_end[1] = index + size - 1;
                printf("%d %d %d %d\n", square_start[0], square_start[1], square_end[0], square_end[1]); 
                exit(0);
                }
            }
        }
    }

    if(max_size == 0){
        printf("Not found\n");
        fclose(file);
        return 0;    
    } 
    // Free dynamically allocated memory
    for (int i = 0; i < img->rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    fclose(file);
    return 1;
}

// Function for handling arguments
int process_arguments(int argc, char *argv[], Image *img) {
    // Check if the right number of arguments were given
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Invalid\n");
        return 1;
    }

    // Switching between arguments
    switch (argv[1][0]) { //First character of the second command-line argument
        case '-': // Check for --help
            if (strcmp(argv[1], "--help") == 0) { // If argument/string comparison is equal
                print_help(); 
                return 0;
            } else {
                fprintf(stderr, "Invalid\n");
                return 1;
            }
            break;

        case 't': // Check for test
            if (strcmp(argv[1], "test") == 0) {
                if (argc < 3) {
                    fprintf(stderr, "Invalid\n");
                    return 1;
                }
                if (is_valid_bitmap(argv[2], img)) {
                    return 0; // "Valid" - already printed
                } else {
                    return 0; // "Invalid" - already printed
                }
            }
            break;

        case 'h':  // Check for horizontal line
            if (strcmp(argv[1], "hline") == 0) {
                if (argc < 3) {
                    fprintf(stderr, "Invalid\n");
                    return 1;
                }
                return (find_hline(argv[2], img));
            }
            break;

        case 'v':  // Check for vertical line
            if (strcmp(argv[1], "vline") == 0) {
                if (argc < 3) {
                    fprintf(stderr, "Invalid\n");
                    return 1;
                }
                return (find_vline(argv[2], img));
            }
            break;

        case 's':  // Check for square
            if (strcmp(argv[1], "square") == 0) {
                if (argc < 3) {
                    fprintf(stderr, "Invalid\n");
                    return 1;
                }
                return (find_square(argv[2], img));
            }
            break;

        default:
            fprintf(stderr, "Invalid\n");
            return 1;
    }
    return 1;
}

int main(int argc, char *argv[]) {

    Image img = {0}; // Initialization of rows and columns

    // Calling function to handle the arguments
    int result = process_arguments(argc, argv, &img);

    return result; 
}