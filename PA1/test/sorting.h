
// Reads long integers from a binary file into an array of Size long ints.
// Returns address of the memory allocated
long * Load_From_File(char * Filename, int * Size);

// Saves Array of Size long ints to Filename in binary format.
// Returns the number of long ints successfully saved to file
int Save_To_File(char * Filename, long * Array, int Size);

// Takes in Array of Size longs and Shell sorts them (with insertion or selection sort)
// N_Comp and N_Move are the number of comparisons and moves made by the funtion
void Shell_Insertion_Sort(long * Array, int Size, double * N_Comp, double * N_Move);
void Shell_Selection_Sort(long * Array, int Size, double * N_Comp, double * N_Move);

// Prints sequence to be used in Shell sort
// Returns the number of integers in the sequence
int Print_Seq(char * Filename, int Size);
