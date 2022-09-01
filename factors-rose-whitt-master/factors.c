/*
 * COMP 321 Project 1: Factors
 *
 * This program computes the number of prime factors, and optionally the number
 * of distinct prime factors, for an unsigned integer input.
 * 
 * Rose Whitt; rew9
 */

#include <assert.h>
#include <math.h>     // Included in case you use the standard math library.
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static unsigned int	count_distinct_factors(unsigned int n);
static unsigned int	count_factors(unsigned int n);
static unsigned int	count_factors_recursive(unsigned int n);
static void		test_factors(void);

// Replace this comment with any global variable declarations.

// Replace this comment with any helper functions.
/*
 * Effects:
 *	Returns 0 if n is not in arr, 1 if it is.
 *
 */
static int
contains(int arr[], int n) {
	int arr_size = sizeof(arr);
	
	for (int i = 0; i < arr_size; i++) {
		if (arr[i] == n) {
			return (1);
		}
	}
	return (0);	

}


/*
 * Effects:
 *	Recursively divides by incrementing factor until prime factor is found
 *	and prime factor is returned to count_factors_recursive
 *
 */
static unsigned int
prime_recursive_helper(unsigned int num, unsigned int factor, unsigned int counter) {
	// BASE
	// you have reached the last prime factor
	if (num / factor < 2) {
		counter++;
		return (counter);
	}
	// RECURSIVE STEPS
	// 1) when the number, n, is not prime and is divisible by count
	if (num % factor == 0) {
		// factor down the tree
		counter++;
		return (prime_recursive_helper(num / factor, factor, counter));
	// 2) when the number, n, could be prime, or could not be.
	//	increment count until you either reach rec. case 1 or
	// 	find that the only factor is itself
	} else {
		return (prime_recursive_helper(num, factor + 1, counter));
	}
}

/* 

 * Requires:  
 *   The input "n" must be greater than 1.
 *
 * Effects: 
 *   Returns the number of factors of the input "n".
 */
static unsigned int
count_factors_recursive(unsigned int n)
{
	// Replace this comment with your local variable declarations.
    
	assert(n > 1);
	return prime_recursive_helper(n, 2, 0);
	
}

/* 
 * Requires:  
 *   The input "n" must be greater than 1.
 *
 * Effects: 
 *   Returns the number of factors of the input "n".
 */
static unsigned int
count_factors(unsigned int n)
{
	// Replace this comment with your local variable declarations.
    	int count = 0;
	assert(n > 1);
	/*
	 * Replace this comment with your code. 
	 */
	 
	 // divide n by the lowest prime number, 2, until no longer possible
	 while (n % 2 == 0) {
	 	n /= 2;
	 	count++;
	 }
		 
	 // divide n by each odd number until no longer possible
	 for (int i = 3; i <= sqrt(n); i += 2) {
	 	while (n % i == 0) {
	 		n /= i;
	 		count++;
	 	}
	 }
	 
	 // handles case where n is already prime but greater than 2
	 if (n > 2) {
	 	count++;
	 }
	return (count);
}

/* 
 * Requires:  
 *   The input "n" must be greater than 1.
 *
 * Effects: 
 *   Returns the number of distinct factors of the input "n".
 */
static unsigned int
count_distinct_factors(unsigned int n)
{
	assert(n > 1);
	
	int sqrt_n = ceil(sqrt(n));
	
	// array to hold prime numbers found
	int primes[sqrt_n];
	
	// set each element to zero
	for (int i = 0; i < sqrt_n; i++) {
		primes[i] = 0;
	}
	
	// tracks first empty index
	int idx = 0;
	// tracks number of distinct primes
	int count = 0;
	
	// divide n by the lowest prime number, 2, until no longer possible
	while (n % 2 == 0) {
		n /= 2;
		// when contains returns 0, 2 is a new prime factor!
		if (contains(primes, 2) == 0) {
			count++;
			primes[idx] = 2;
			idx++;
		}
	}
	
	// divide n by each odd number, beginning at 3, until no longer possible
	for (int i = 3; i <= sqrt(n); i += 2) {
		while (n % i == 0) {
			n /= i;
			// 0 is new prime
			if (contains(primes, i) == 0) {
				count++;
				primes[idx] = i;
				idx++;
			}
		}
	}
	
	// if n is a prime greater than 2
	if (n > 2) {
		if (contains(primes, n) == 0) {
			count++;
			primes[idx] = n;
			idx++;
		}
	}
	
	return (count);
}

/* 
 * Requires:
 *   Nothing.
 *
 * Effects:
 *   Runs testing procedures.  Currently only prints a message.
 */
static void
test_factors(void)
{

	printf("Test Factors\n");
}

/* 
 * Requires:
 *   Nothing.
 *
 * Effects:
 *   If the "-t" option is specified on the command line, then test code is
 *   executed and the program exits.
 *   
 *   Otherwise, requests a number from standard input.  If the "-r" option is
 *   specified on the command line, then prints the number of prime factors
 *   that the input number has, calculated using a recursive function.
 *   Otherwise, prints the number of prime factors that the input number has
 *   and the number of those factors that are distinct using iterative
 *   functions.
 *
 *   Upon completion, the program always returns 0.
 *
 *   If the number that is input is not between 2 and the largest unsigned
 *   integer, the output of the program is undefined, but it will not crash.
 */
int
main(int argc, char **argv)
{
	unsigned int n;
	int c;
	bool recursive = false;
	bool runtests = false;

	// Parse the command line.
	while ((c = getopt(argc, argv, "rt")) != -1) {
		switch (c) {
		case 'r':             // Use recursive version.
			recursive = true;
			break;
		case 't':             // Run test procedure and exit.
			runtests = true;
			break;
		default:
			break;
		}
	}

	// If "-t" is specified, run test procedure and exit program.
	if (runtests) {
		test_factors();
		return (0);
	}

	// Get input.
	printf("Enter number:\n");
	if (scanf("%u", &n) != 1) {
		fprintf(stderr, "Input error\n");
		return (1);
	}

	// Validate the input.
	if (n < 2) {
		fprintf(stderr, "Invalid input: %u\n", n);
		return (1);
	}

	// Print results.
	if (recursive) {
		// Use recursive version.
		printf("%u has %u prime factors.\n",
		    n, count_factors_recursive(n));
	} else {
		// Use iterative versions.
		printf("%u has %u prime factors, %u of them distinct.\n",
		    n, count_factors(n), count_distinct_factors(n));
	}

	// Report no errors.
	return (0);
}
