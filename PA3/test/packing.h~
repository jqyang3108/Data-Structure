typedef struct _TreeNode{
	int label;
	char character;
	int size;
	double width;
	double height;
	double x_cor;
	double y_cor;
	struct _TreeNode *left;
	struct _TreeNode *right;
}TreeNode;

typedef TreeNode StackElement;

typedef struct _Stack{
	StackElement **content;
	int top;
	int MaxSize;
}Stack;

TreeNode *Load_From_File(char *Filename);
TreeNode *Perform_Packing(TreeNode *root);
void Save_To_File(char *Filename, TreeNode *tree);
void Destroy_Tree(TreeNode *root);
