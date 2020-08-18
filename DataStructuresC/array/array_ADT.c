#include <stdio.h>
#include <stdlib.h>

typedef struct intArray {
    int *array;
    int size;
    int length;
} intArray;


intArray * intArrayNew(int size)
{
    intArray *tmp = (intArray *) malloc(sizeof(intArray));

    // size in memory
    tmp->size = size;
    // array memory allocation
    tmp->array = (int *) malloc(size * sizeof(int));
    // element inside array
    tmp->length = 0;

    // initializing all values to zero
    for (int i = 0; i < size; i++) {
        tmp->array[i] = 0;
    }

    return tmp;
}

void intArrayDisplay(intArray *tmp)
{
    for (int i = 0; i < tmp->length; i++) {
        printf("%d ", tmp->array[i]);
    }
}

void intArrayAppend(intArray *tmp, int value)
{
    if (tmp->length < tmp->size) {

        tmp->array[tmp->length] = value;
        tmp->length++;
    }
}

void intArrayInsert(intArray *tmp, int index, int value)
{
    // check if index is in offset
    if (index >= 0 && index <= tmp->length) {

        for (int i = tmp->length; i > index; i--) {
            tmp->array[i] = tmp->array[i - 1];
        }

        tmp->array[index] = value;
        tmp->length++;
    }
}

int intArrayDelete(intArray *tmp, int index)
{
    // check if index is in offset
    if (index >= 0 && index <= tmp->length) {

        for (int i = index; i < tmp->length; i++) {
            tmp->array[i] = tmp->array[i + 1];
        }

        tmp->length--;

        return index;
    }

    return 0;
}

void intArraySwap(int *x, int *y)
{
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

int intArrayLinearSearchImproved(intArray *tmp, int key)
{
    for (int i = 0; i < tmp->length; i++)
    {
        if (tmp->array[i] == key) {
            
            if (i > 0) {
                intArraySwap(&tmp->array[i], &tmp->array[i-1]);
            }
            
            return i;
        }
    }

    return -1;
}

int intArrayLinearSearch(intArray *tmp, int key)
{
    for (int i = 0; i < tmp->length; i++)
    {
        if (tmp->array[i] == key) {
            return i;
        }
    }

    return -1;
}

int intArrayBinarySearch(intArray *tmp, int key)
{
    int low = 0;
    int high = tmp->length - 1;
    int middle = 0;;

    while (low <= high) {

        middle = (low + high) / 2;

        if (key == tmp->array[middle]) {
            return middle;
        }
        else if (key < tmp->array[middle]) {
            high = middle - 1;
        }
        else {
            low = middle + 1;
        }
    }

    return -1;
}

int intArrayBinarySearchRecursive(intArray *tmp, int low, int high, int key)
{
    int middle = 0;;

    while (low <= high) {

        middle = (low + high) / 2;

        if (key == tmp->array[middle]) {
            return middle;
        }
        else if (key < tmp->array[middle]) {
            return intArrayBinarySearchRecursive(tmp, low, middle - 1, key);
        }
        else {
            return intArrayBinarySearchRecursive(tmp, middle + 1, high, key);
        }
    }

    return -1;
}


int intArrayGet(intArray *tmp, int index)
{
    if (index >= 0 && index < tmp->length) {
        
        return tmp->array[index];
    }

    return -1;
}

void intArraySet(intArray *tmp, int index, int value)
{
    if (index >= 0 && index < tmp->length) {
        
        tmp->array[index] = value;
    }
}

int intArrayMax(intArray *tmp)
{
    int max = tmp->array[0];

    for (int i = 1; i < tmp->length; i++) {
        
        if (max < tmp->array[i]) {
            max = tmp->array[i];
        }
    }

    return max;
}

int intArrayMin(intArray *tmp)
{
    int min = tmp->array[0];

    for (int i = 1; i < tmp->length; i++) {
        
        if (min > tmp->array[i]) {
            min = tmp->array[i];
        }
    }

    return min;
}

int intArraySum(intArray *tmp)
{
    int sum = 0;

    for (int i = 0; i < tmp->length; i++) {
        
        sum += tmp->array[i];
    }

    return sum;
}

int intArrayAverage(intArray *tmp)
{
    int sum = 0;

    for (int i = 0; i < tmp->length; i++) {
        
        sum += tmp->array[i];
    }

    return sum / tmp->length;
}

void intArrayReverse(intArray *tmp)
{
    int *cache = (int *) malloc(tmp->length * sizeof(int));

    int i = 0;
    int j = 0;

    for (i = tmp->length - 1, j = 0; i >= 0; i--, j++) {

        cache[j] = tmp->array[i];
    }

    for (i = 0; i < tmp->length; i++) {
        tmp->array[i] = cache[i];
    }

    free(cache);
}

void intArrayReverseNoCache(intArray *tmp)
{
    int i = 0;
    int j = 0;
    int temp = 0;

    for (i = 0, j = tmp->length - 1; i < j; i++, j--) {

        temp = tmp->array[i];
        tmp->array[i] = tmp->array[j];
        tmp->array[j] = temp;
    }
}

// remove first element from left in the array
void intArrayLeftShift(intArray *tmp)
{
    for (int i = 0; i < tmp->length; i++)
    {
        if ( i + 1 == tmp->length) {
            tmp->array[i] = 0;
            break;
        }
        tmp->array[i] = tmp->array[i + 1];
    }

    tmp->length--;
}

void intArrayLeftRotate(intArray *tmp)
{
    int temp = tmp->array[0];

    for (int i = 0; i < tmp->length - 1; i++)
    {
        // if ( i + 1 == tmp->length) {
        //    tmp->array[i] = temp;
        //    break;
        // }
        tmp->array[i] = tmp->array[i + 1];
    }

    tmp->array[tmp->length - 1] = temp;

}

int intArrayInsertSorted(intArray *tmp, int value)
{
    int i = tmp->length - 1;

    if (tmp->length == tmp->size) {
        return -1;
    }

    while (i >= 0 && tmp->array[i] > value) {
        tmp->array[i + 1] = tmp->array[i];
        i--;
    }

    tmp->array[i + 1] = value;
    tmp->length++;

    return i + 1;
}

// check if array is sorted
int intArrayIsSorted(intArray *tmp)
{
    for (int i = 0; i < tmp->length -1; i++)
    {
        if (tmp->array[i] > tmp->array[i + 1]) {
            return 0;
        }
    }

    return 1;
}

// merge two ordered arrays in one ordered array
intArray * intArrayMerge(intArray *tmp1, intArray *tmp2)
{
    int size = tmp1->size + tmp2->size;

    intArray *tmp = intArrayNew(size);

    int i = 0;
    int j = 0;
    int k = 0;

    while (i < tmp1->length && j < tmp2->length) {

        if (tmp1->array[i] < tmp2->array[j]) {
            tmp->array[k] = tmp1->array[i];
            k++;
            i++;
        }
        else {
            tmp->array[k] = tmp2->array[j];
            k++;
            j++;
        }
    }

    for (;i < tmp1->length; i++) {
        tmp->array[k] = tmp1->array[i];
        k++;
    }

    for (;j < tmp2->length; j++) {
        tmp->array[k] = tmp2->array[j];
        k++;
    }

    tmp->length = tmp1->length + tmp2->length;

    return tmp;
}

// merge two arrays avoiding duplicates
intArray * intArrayUnion(intArray *tmp1, intArray *tmp2)
{
    int size = tmp1->size + tmp2->size;

    intArray *tmp = intArrayNew(size);

    int i = 0;
    int j = 0;
    int k = 0;

    while (i < tmp1->length && j < tmp2->length) {

        if (tmp1->array[i] < tmp2->array[j]) {
            tmp->array[k] = tmp1->array[i];
            i++;
        }
        else if (tmp2->array[j] < tmp1->array[i]) {
            tmp->array[k] = tmp2->array[j];
            j++;
        }
        else {
            tmp->array[k] = tmp1->array[i];
            i++;
            j++;
        }

        k++;
    }

    for (;i < tmp1->length; i++) {
        tmp->array[k] = tmp1->array[i];
        k++;
    }

    for (;j < tmp2->length; j++) {
        tmp->array[k] = tmp2->array[j];
        k++;
    }

    tmp->length = k;

    return tmp;
}

// merge two arrays copying only values present in both
intArray * intArrayIntersection(intArray *tmp1, intArray *tmp2)
{
    int size = tmp1->size + tmp2->size;

    intArray *tmp = intArrayNew(size);

    int i = 0;
    int j = 0;
    int k = 0;

    while (i < tmp1->length && j < tmp2->length) {

        if (tmp1->array[i] < tmp2->array[j]) {
            i++;
        }
        else if (tmp2->array[j] < tmp1->array[i]) {
            j++;
        }
        else if (tmp2->array[j] == tmp1->array[i]) {
            tmp->array[k] = tmp1->array[i];
            i++;
            j++;
            k++;
        }
    }

    tmp->length = k;

    return tmp;
}

intArray * intArrayDifference(intArray *tmp1, intArray *tmp2)
{
    int size = tmp1->size + tmp2->size;

    intArray *tmp = intArrayNew(size);

    int i = 0;
    int j = 0;
    int k = 0;

    while (i < tmp1->length && j < tmp2->length) {

        if (tmp1->array[i] < tmp2->array[j]) {
            tmp->array[k] = tmp1->array[i];
            k++;
            i++;
        }
        else if (tmp2->array[j] < tmp1->array[i]) {
            j++;
        }
        else {
            i++;
            j++;
        }

        
    }

    for (;i < tmp1->length; i++) {
        tmp->array[k] = tmp1->array[i];
        k++;
    }

    tmp->length = k;

    return tmp;
}

void intArrayFree(intArray *tmp)
{
    // set all values to zero
    for (int i = 0; i < tmp->size; i++) {
        tmp->array[i] = 0;
    }

    free(tmp->array);
    free(tmp);
}

/**
 * Main.
 */
int main () {

    // operation
    // display - ok
    // add/append - ok
    // insert - ok
    // delete - ok
    // linear search - ok
    // binary search - ok
    // get - ok
    // set - ok
    // max/min - ok
    // reverse - ok
    // shift/rotate - ok
    // merge sorted - ok
    // union - ok
    // intersect - ok
    // difference


    // iniatilizing arrays
    intArray *tmp2 = intArrayNew(15);

    // append
    intArrayAppend(tmp2, 1);
    intArrayAppend(tmp2, 2);
    intArrayAppend(tmp2, 3);
    intArrayAppend(tmp2, 4);
    intArrayAppend(tmp2, 5);
    intArrayAppend(tmp2, 6);

    // insert
    intArrayInsert(tmp2, 2, 33);

    // display
    intArrayDisplay(tmp2);

    printf("\n");

    // delete
    intArrayDelete(tmp2, 3);

    // display
    intArrayDisplay(tmp2);

    printf("\n");

    // linear search
    printf("%d\n", intArrayLinearSearch(tmp2, 33));
    printf("%d\n", intArrayLinearSearch(tmp2, 34));

    // linear search
    printf("%d\n", intArrayLinearSearchImproved(tmp2, 5));
    printf("%d\n", intArrayLinearSearchImproved(tmp2, 5));
    printf("%d\n", intArrayLinearSearchImproved(tmp2, 5));
    printf("%d\n", intArrayLinearSearchImproved(tmp2, 5));
    printf("%d\n", intArrayLinearSearchImproved(tmp2, 5));
    printf("%d\n", intArrayLinearSearchImproved(tmp2, 5));
    printf("%d\n", intArrayLinearSearchImproved(tmp2, 5));

    // display
    intArrayDisplay(tmp2);

    printf("\n");

    // free;
    intArrayFree(tmp2);

    // iniatilizing array
    intArray *tmp3 = intArrayNew(25);

    // append
    intArrayAppend(tmp3, 1);
    intArrayAppend(tmp3, 2);
    intArrayAppend(tmp3, 3);
    intArrayAppend(tmp3, 4);
    intArrayAppend(tmp3, 5);
    intArrayAppend(tmp3, 6);
    intArrayAppend(tmp3, 10);
    intArrayAppend(tmp3, 25);
    intArrayAppend(tmp3, 36);
    intArrayAppend(tmp3, 47);
    intArrayAppend(tmp3, 58);
    intArrayAppend(tmp3, 69);
    intArrayAppend(tmp3, 70);
    intArrayAppend(tmp3, 81);
    intArrayAppend(tmp3, 105);
    intArrayAppend(tmp3, 123);
    intArrayAppend(tmp3, 158);
    intArrayAppend(tmp3, 169);

    // display
    intArrayDisplay(tmp3);

    printf("\n");

    // binary search
    printf("Binary search for element 10: %d\n", intArrayBinarySearch(tmp3, 10));
    // binary search recursive
    printf("Binary search for element 10: %d\n", intArrayBinarySearchRecursive(tmp3, 0, tmp3->length - 1, 10));


    // get
    printf("Get 6: %d\n", intArrayGet(tmp3, 6));

    // set
    intArraySet(tmp3, 6, 11);

    // get
    printf("Get 6: %d\n", intArrayGet(tmp3, 6));

    // max
    printf("Max: %d\n", intArrayMax(tmp3));

    // min
    printf("Min: %d\n", intArrayMin(tmp3));

    // sum
    printf("Sum: %d\n", intArraySum(tmp3));

    // average
    printf("Average: %d\n", intArrayAverage(tmp3));

    

    // display
    printf("Reverse:\n");
    intArrayDisplay(tmp3);
    printf("\n");
    
    // reverse
    intArrayReverse(tmp3);

    // display
    intArrayDisplay(tmp3);
    printf("\n");
    
    // reverse
    intArrayReverse(tmp3);

    // display
    intArrayDisplay(tmp3);
    printf("\n");

    // display
    printf("Reverse no cache:\n");
    intArrayDisplay(tmp3);
    printf("\n");
    
    // reverse
    intArrayReverseNoCache(tmp3);

    // display
    intArrayDisplay(tmp3);
    printf("\n");
    
    // reverse
    intArrayReverseNoCache(tmp3);

    // display
    intArrayDisplay(tmp3);
    printf("\n");

    // free;
    intArrayFree(tmp3);


    // iniatilizing array
    intArray *tmp4 = intArrayNew(25);

    // append
    intArrayAppend(tmp4, 0);
    intArrayAppend(tmp4, 1);
    intArrayAppend(tmp4, 2);
    intArrayAppend(tmp4, 3);
    intArrayAppend(tmp4, 4);
    intArrayAppend(tmp4, 5);
    intArrayAppend(tmp4, 6);
    intArrayAppend(tmp4, 7);
    intArrayAppend(tmp4, 8);
    intArrayAppend(tmp4, 9);

    // display
    printf("Left Shift:\n");
    intArrayDisplay(tmp4);
    printf("\n");

    intArrayLeftShift(tmp4);
    intArrayLeftShift(tmp4);
    intArrayLeftShift(tmp4);

    // display
    intArrayDisplay(tmp4);
    printf("\n");

    printf("Array Len after 3 shifts: %d\n", tmp4->length);


    // display
    printf("Left Rotate:\n");
    intArrayDisplay(tmp4);
    printf("\n");
    intArrayLeftRotate(tmp4);
    intArrayDisplay(tmp4);
    printf("\n");
    intArrayLeftRotate(tmp4);
    intArrayDisplay(tmp4);
    printf("\n");
    intArrayLeftRotate(tmp4);
    intArrayDisplay(tmp4);
    printf("\n");
    intArrayLeftRotate(tmp4);
    intArrayDisplay(tmp4);
    printf("\n");
    intArrayLeftRotate(tmp4);
    intArrayDisplay(tmp4);
    printf("\n");
    intArrayLeftRotate(tmp4);
    intArrayDisplay(tmp4);
    printf("\n");
    intArrayLeftRotate(tmp4);
    intArrayDisplay(tmp4);
    printf("\n");
    intArrayLeftRotate(tmp4);

    // free;
    intArrayFree(tmp4);

    // iniatilizing array
    intArray *tmp5 = intArrayNew(25);

    // insert sorted
    intArrayInsertSorted(tmp5, 0);
    intArrayInsertSorted(tmp5, 10);
    intArrayInsertSorted(tmp5, 2);
    intArrayInsertSorted(tmp5, 30);
    intArrayInsertSorted(tmp5, 14);
    intArrayInsertSorted(tmp5, 35);
    intArrayInsertSorted(tmp5, 61);
    intArrayInsertSorted(tmp5, 27);
    intArrayInsertSorted(tmp5, 18);
    intArrayInsertSorted(tmp5, 49);
    intArrayInsertSorted(tmp5, -3);

    // display
    printf("Insert Sorted:\n");
    intArrayDisplay(tmp5);
    printf("\n");

    // free;
    intArrayFree(tmp5);


    // iniatilizing first array
    intArray *array1 = intArrayNew(25);
    // iniatilizing first array
    intArray *array2 = intArrayNew(25);

    // insert in array 1
    intArrayInsertSorted(array1, 1);
    intArrayInsertSorted(array1, 10);
    intArrayInsertSorted(array1, 2);
    intArrayInsertSorted(array1, 30);
    intArrayInsertSorted(array1, 14);
    intArrayInsertSorted(array1, 70);
    // insert in array 2
    intArrayInsertSorted(array2, 35);
    intArrayInsertSorted(array2, 61);
    intArrayInsertSorted(array2, 30);
    intArrayInsertSorted(array2, 18);
    intArrayInsertSorted(array2, 49);
    intArrayInsertSorted(array2, 70);

    intArray *arrayMerged = intArrayMerge(array1, array2);

    // display
    printf("Array 1 Sorted:\n");
    intArrayDisplay(array1);
    printf("\n");

    // display
    printf("Array 2 Sorted:\n");
    intArrayDisplay(array2);
    printf("\n");

    // display
    printf("Array Merged:\n");
    intArrayDisplay(arrayMerged);
    printf("\n");

    intArray *arrayUnion = intArrayUnion(array1, array2);

    // display
    printf("Array Union:\n");
    intArrayDisplay(arrayUnion);
    printf("\n");

    intArray *arrayIntersection = intArrayIntersection(array1, array2);

    // display
    printf("Array Intersection:\n");
    intArrayDisplay(arrayIntersection);
    printf("\n");

    intArray *arrayDifference = intArrayDifference(array1, array2);

    // display
    printf("Array Difference:\n");
    intArrayDisplay(arrayDifference);
    printf("\n");

    // free
    intArrayFree(array1);
    intArrayFree(array2);
    intArrayFree(arrayMerged);
    intArrayFree(arrayUnion);
    intArrayFree(arrayIntersection);
    intArrayFree(arrayDifference);
}