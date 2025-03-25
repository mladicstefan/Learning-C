#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *array = NULL;
    int num_elements = 0;
    int i, j, temp;

    printf("Type a number: ");
    scanf("%d", &num_elements);

    array = malloc(num_elements * sizeof(int));
    if (array == NULL) {
        printf("Error allocating memory.\n");
        return 1;
    }

    for (i = 0; i < num_elements; i++) {
        printf("Enter element %d: ", i + 1);
        // Optionally check the return value to handle bad input:
        if (scanf("%d", &array[i]) != 1) {
            printf("Invalid input. Exiting.\n");
            free(array);
            return 1;
        }
    }

    for (i = 0; i < num_elements - 1; i++) {
        for (j = 0; j < num_elements - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    printf("\nSorted array:\n");
    for (i = 0; i < num_elements; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}


