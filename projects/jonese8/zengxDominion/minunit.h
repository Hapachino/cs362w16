#pragma once
/* file: minunit.h */
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) printf("Test case failed! Error message: %s\n", message); \
				else printf("Test passed!\n"); } while (0)
extern int tests_run;
