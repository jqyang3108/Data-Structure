// Used to implement linked list of long integers
typedef struct Node {
	long value;
	struct Node *next;
} Node;

// Reads all longs from a file and stores in linked list
// Returns pointer to first node
Node *Load_From_File(char *Filename);

// Writes all longs in a linked list to a file
// Returns number of ints successfully written
int Save_To_File(char *Filename, Node *list);

// Shell Insertion Sort
// Sorts by manipulating next pointers
// Deallocates sequence before returning
// Returns pointer to first node in sorted list
Node *Shell_Sort(Node *list);
