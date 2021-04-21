/*
 * project5.cpp
 *
 *  Created on: Apr 18, 2021
 *      Author: erictruong1014
 */

#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for math functions
#include<unordered_set> // used for generating unique elements

using namespace std;

// bubble sort algorithm with D number of comparisons allowed
int* bubbleSort(int* arr, int numElements, int D)
{
    int numComp = 0; // used to count the number of comparisons and to check with D

    int* arrCopy = new int[numElements]; // making a copy of arr as this is an inplace sorting algorithm
                                        // we want to retain the ordering of arr for shell sort
    for(int i = 0; i < numElements; i++)
        arrCopy[i] = arr[i];

    // bubble sort starts
    for (int i = 0; i < numElements; i++)
    {
        for (int j = 0; j < numElements - 1; j++)
        {
            numComp++; // incrementing the number of comparisons done right before
                        // the if condition where the comparison happens each time
            if(numComp >= D) // checking for number of comparisons
                return arrCopy; // return the not necessarily sorted array = approximately sorted array

            if (arrCopy[j] > arrCopy[j + 1]) //if current element is greater than the next, swap
            {
                // swap
                int temp = arrCopy[j];
                arrCopy[j] = arrCopy[j + 1];
                arrCopy[j + 1] = temp;
            }
        }
    }
    // return the completely sorted array
    return arrCopy;
}

// shell sort algorithm with D number of comparisons allowed
int* shellSort(int* arr, int numElements, int D)
{
	int j;
    int numComp = 0;

    // need not make a copy of the arr array since shell sort is performed later/last

    // Start with a largest increment, then reduce by factors of 3
    for (int inc = numElements / 3; inc > 1; inc /= 3)
    {
        // Insertion sort for the increment length
        for (int i = inc; i < numElements; ++i)
        {
            int temp = arr[i]; //temporarily store current value
            j = i - inc; //index of value to compare to

            numComp++; // incrementing the number of comparisons done right before
                        // the if condition where the comparison happens each time
            if(numComp >= D) // checking for number of comparisons
                return arr; // return the not necessarily sorted array = approximately sorted array

            while ((j >= 0) && (arr[j] > temp)) //compares elements in left part of range to swap find insertion point
            {
                arr[j + inc] = arr[j];
                j = j - inc;
            }
            arr[j + inc] = temp; //inserts element at insertion point
        }
    }
    // Insertion sort for the increment length = 1; force length 1 in case of inc/3 == 0
    for (int i = 1; i < numElements; ++i)
    {
        int temp = arr[i]; //temporarily store current value
        j = i - 1; //index of value to compare to

        numComp++; // incrementing the number of comparisons done right before
                    // the if condition where the comparison happens each time
        if(numComp >= D) // checking for number of comparisons
            return arr; // return the not necessarily sorted array = approximately sorted array

        while ((j >= 0) && (arr[j] > temp)) //compares elements in left part of range to swap and find insertion point
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp; //inserts element at insertion point
    }
	return arr;
}

//main function
int main()
{
	int n;
	cin >> n; // read the number of elements
	cout << "Number of elements: " << n << endl;

	int s, l, u, D;
	cin >> s >> l >> u >> D; // read the seed, lower range, upper range and the number of comparisons
    cout << "Number of comparisons allowed: " << D << endl;
    cout << endl;

	// generate n random elements with the seed s, within the lower and upper range
    int num; //number to be inserted
    unordered_set<int> intSet;
    srand(s); //sets seed for generating num
    while (intSet.size() < (unsigned)n) { //check if intSet still has room
    	num = l + (rand() % (u - l + 1)); //randomly generated number within the range
    	intSet.insert(num);
    }
    // store the randomly generated UNIQUE set of elements in an array 'A'
    int* A = new int[n]; //array for random integers
    int arrIdx = 0; //index to insert at
    for (auto it = intSet.begin(); it != intSet.end(); ++it) { //iterate through intSet
    	A[arrIdx] = *it; //add number from intSet into A
    	arrIdx++; //increment index to add at
    }

    // you may use the unordered set to help generate unique elements

	cout << "Randomly generated elements: ~~~~~~~~~~" << endl;
	// display the array A
	for (int i = 0; i < n; i++) {
		cout << A[i] << " ";
	}
	cout << endl << endl;

    // use one of the sorting algorithms with the third argument for D as n*n (for bubble sort) and store the fully sorted result
	int* sortedA = bubbleSort(A, n, n*n);

	cout << "Completely sorted elements: ~~~~~~~~~~" << endl;
	// display the completely sorted array
	for (int i = 0; i < n; i ++) {
		cout << sortedA[i] << " ";
	}
	cout << endl << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Bubble Sort algorithm and store the output array as bubResult in an array
    // calculate and display the two quality measures for bubResult
    cout << "Bubble Sort Result: ~~~~~~~~~~" << endl;
    int* bubResult = bubbleSort(A, n, D);

    // display bubResult
    for (int i = 0; i < n; i++) {
    	cout << bubResult[i] << " ";
    }
    cout << endl << endl;

    // find both the quality metrics for bubResult
    int bubInvNum = 0; //number of inversions needed to sort bubResult
    for (int i = 0; i < n - 1; i++) { //iterate through all but last index
    	for (int j = i + 1; j < n; j++) { //index of value to compare to
    		if (bubResult[i] > bubResult[j]) { //increment bubInvNum each time value at i has a number to the right that is less than it
    			bubInvNum++;
    		}
    	}
    }
    cout << "Number of inversions in bubResult: " << bubInvNum << endl;

    int bubChebyshev = 0; //Chebyshev distance of bubResult
    int displacement; //displacement of values;
    for (int i = 0; i < n; i++) { //iterate through all values of bubResult
    	displacement = 0; //reset displacement
    	for (int j = 0; j < n; j++) { //values in sortedA to compare to
    		if (bubResult[i] == sortedA[j]) { //matching values found
    			if (i == j) { //element at i is sorted correctly
    				displacement = 0;
    			}
    			else if (i > j) {
    				displacement = i - j;
    			}
    			else if (i < j) {
    				displacement = j - i;
    			}

    			if (bubChebyshev < displacement) { //set new Chebyshev distance if higher displacement is found
    				bubChebyshev = displacement;
    			}
    			break; //no need to continue j loop, array has unique elements
    		}
    	}
    }
    cout << "Chebyshev distance in bubResult: " << bubChebyshev << endl << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Shell Sort algorithm and store the output array as shellResult in an array
    // calculate and display the two quality measures for shellResult
    cout << "Shell Sort Result: ~~~~~~~~~~" << endl;
    int* shellResult = shellSort(A, n, D);

    // display shellResult
    for (int i = 0; i < n; i++) {
    	cout << shellResult[i] << " ";
    }
    cout << endl << endl;

    // find both the quality metrics for shellResult
    int shellInvNum = 0; //number of inversions needed to sort shellResult
    for (int i = 0; i < n - 1; i++) { //iterate through all but last index
        for (int j = i + 1; j < n; j++) { //index of value to compare to
        	if (shellResult[i] > shellResult[j]) { //increment shellInvNum each time value at i has a number to the right that is less than it
        		shellInvNum++;
        	}
        }
    }
    cout << "Number of inversions in shellResult: " << shellInvNum << endl;

    int shellChebyshev = 0; //Chebyshev distance of bubResult
    for (int i = 0; i < n; i++) { //iterate through all values of shellResult
        displacement = 0; //reset displacement
       	for (int j = 0; j < n; j++) { //values in sortedA to compare to
        	if (shellResult[i] == sortedA[j]) { //matching values found
        		if (i == j) { //element at i is sorted correctly
       				displacement = 0;
       			}
       			else if (i > j) {
       				displacement = i - j;
       			}
       			else if (i < j) {
       				displacement = j - i;
       			}

        		if (shellChebyshev < displacement) { //set new Chebyshev distance if higher displacement is found
        			shellChebyshev = displacement;
        		}
       			break; //no need to continue j loop, array has unique elements
       		}
       	}
    }
    cout << "Chebyshev distance in shellResult: " << shellChebyshev << endl << endl;

    return 0;
}


