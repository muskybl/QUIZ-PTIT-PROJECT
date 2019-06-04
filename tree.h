
struct Ques
{
	string subjectId;
	string question;
	string answerA, answerB, answerC, answerD;
	int rightAnswer;
	Ques() : rightAnswer(0) {}
	void input_question(int x, int y, string subId)
	{
		string ans[] = {"A", "B", "C", "D"};
		subjectId = subId;
		gotoxy(x, y);
		cout << "Cau hoi:";
		show_form_ques(x, y + 2);
		input_info(x + 9, y, MAX_CHAR_Q, MAX_CHAR_LINE2, question, 0, 0, 0);
		input_info(x + 3, y + 2, MAX_CHAR_LINE2 - 1, MAX_CHAR_LINE2, answerA, 0, 0, 0);
		input_info(x + 3, y + 3, MAX_CHAR_LINE2 - 1, MAX_CHAR_LINE2, answerB, 0, 0, 0);
		input_info(x + 3, y + 4, MAX_CHAR_LINE2 - 1, MAX_CHAR_LINE2, answerC, 0, 0, 0);
		input_info(x + 3, y + 5, MAX_CHAR_LINE2 - 1, MAX_CHAR_LINE2, answerD, 0, 0, 0);
		Button r[4];
		create_button(r, VERTICAL4 - 6, y + 3, 4, 5, 0, ans, 4, 3);
		rightAnswer = menu_position(r, 4) + 1;
	}
	void show_question(int x, int y, int ans)
	{
		if(ans && rightAnswer != 0) mark_rightAnswer(x - 1, y + 1 + ans);
		show_string(question, MAX_CHAR_LINE2, x + 2, y);
		show_string(answerA, MAX_CHAR_LINE2, x, y + 2);
		show_string(answerB, MAX_CHAR_LINE2, x, y + 3);
		show_string(answerC, MAX_CHAR_LINE2, x, y + 4);
		show_string(answerD, MAX_CHAR_LINE2, x, y + 5);
	}
	void change_question(Ques data)
	{
		question = data.question;
		answerA = data.answerA;
		answerB = data.answerB;
		answerC = data.answerC;
		answerD = data.answerD;
		rightAnswer = data.rightAnswer;
	}
	void read_file(ifstream &file)
	{
		file.ignore();
		getline(file, subjectId,'@');
		file.ignore();
		getline(file, question,'@');
		file.ignore();
		getline(file, answerA,'@');
		file.ignore();
		getline(file, answerB,'@');
		file.ignore();
		getline(file, answerC,'@');
		file.ignore();
		getline(file, answerD,'@');
		file >> rightAnswer;
	}
	void write_file(ofstream &file)
	{
		file << subjectId << "@\n"; 
		file << question << "@\n";
		file << answerA << "@\n";
		file << answerB << "@\n";
		file << answerC << "@\n";
		file << answerD << "@";
		file << rightAnswer << '\n';
	}
};
struct TNode
{
	int key;
	int  height;
	Ques info;
	TNode *left;
	TNode *right;
	TNode() : left(NULL), right(NULL) {}
};
int height(TNode *N)
{
	if (N == NULL) return 0;
    return N->height;
}
TNode *create_node(Ques data, int key)
{
	TNode *node = new TNode;
	node->key = key;
	node->info = data;
	node->height = 1;
	return node;
}
// Ham xu ly cay
TNode *right_rotate(TNode *y) // quay phai 
{
	TNode *x = y->left;
	TNode *T2 = x->right;
	
	// Perform rotation
	
	x->right = y;
	y->left = T2;
	
	// Update heights
	y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
	
	 // Return new root
    return x;
}
TNode *left_rotate(TNode *x) // quay trai
{
	TNode *y = x->right;
	TNode *T2 = y->left;
	
	// Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}

// Lay chi so can bang
int getBalance(TNode *N)
{
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}
// Them node va tra ve nut moi
TNode* insert_node(TNode* node, Ques data, int key)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(create_node(data, key));
        
 	// Find suitable node 
    if (key < node->key)
        node->left  = insert_node(node->left, data, key);
    else if (key > node->key)
        node->right = insert_node(node->right, data, key);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Cap nhat chieu cao node cha */
    node->height = max(height(node->left), height(node->right)) + 1;
                           
 
    /* 3. Kiem tra nut cha co bi mat can bang ? */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return right_rotate(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return left_rotate(node);
 
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  left_rotate(node->left);
        return right_rotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}

TNode * minValueNode(TNode* node)
{
    TNode* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
	// Nut cuc trai
    return current;
}
//Xoa 1 node tren cay

TNode* del_node(TNode* root, int key)
{
    if (root == NULL)
        return root;
 
    // Find suiable node to delete
    
    if ( key < root->key )
        root->left = del_node(root->left, key);
 
    else if( key > root->key )
        root->right = del_node(root->right, key);
 
    // Found the key
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            TNode *temp = root->left ? root->left : root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
			delete temp;
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            TNode* temp = minValueNode(root->right);
 
            // Copy the inorder successor's data to this node
            
            root->key = temp->key;
 			root->info = temp->info; // new fix
 			
            // Delete the inorder successor
            root->right = del_node(root->right, temp->key);
        }
    }
 
    // If the tree had only one node then return
    if (root == NULL)
      return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return right_rotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  left_rotate(root->left);
        return right_rotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return left_rotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
 
    return root;
}
void preorder(TNode *root)
{
	if(root != NULL)
	{
		cout << root->info.question << " : key: " << root->key << '\n';
		preorder(root->left);
		preorder(root->right);
	}
	
}
void count_question(TNode *root, string subId, int &number) // the number of question's subject 
{
	if(root == NULL) return;
	if(subId.compare(root->info.subjectId) == 0) ++number;
	count_question(root->left, subId, number);
	count_question(root->right, subId, number);
}
void address_arr(TNode *root, TNode *arr[], string subId, int &i) // mang dia chi nut cua mon hoc
{
	if(root != NULL)
	{
		if(subId.compare(root->info.subjectId) == 0)
		{
			arr[i] = root;
			i++;
		}
		address_arr(root->left, arr, subId, i);
		address_arr(root->right, arr, subId, i);
	}
} 
TNode *search_key(TNode *root, int key)
{
	if(root == NULL) return NULL;
	if(key > root->key) return search_key(root->right, key);
	if(key < root->key) return search_key(root->left, key);
	return root;
}
struct Tree
{
	TNode *Root;
	int number; // the number of node in AVL tree
	int arr[MAX_N_QUESTION]; // random array
	Tree()
	{
		number = 0;
		Root = NULL;
		srand(time(NULL));
		rand_arr(arr, MAX_N_QUESTION); // random array
	}
	void insert(string subId, int x, int y)
	{
		if(number == MAX_N_QUESTION) return;
		Ques data;
		data.input_question(x, y, subId);
		Root = insert_node(Root, data, arr[number]); // take value at arr[number]
		number++;
	}
	void change_value(TNode *data, int x, int y)
	{
		if(number == 0) return;
		data->info.input_question(x, y, data->info.subjectId);
		data->info.change_question(data->info);
	}
	void list_question(int x, int y, TNode *arr[], int *ans, int front, int rear) // wrong
	{
		int len, m; // len : length string, m : value min
		 
		while(front < rear)
		{
			string tmp;
			len = arr[front]->info.question.length();
			m = min(MAX_CHAR_LINE1, len);
			tmp.append(arr[front]->info.question, 0, m);
			if(m != len) tmp.append("... ?");
			
			gotoxy(x, y + front % MAX_LINE);
			cout << "Cau " << front + 1 << ":";
			
			gotoxy(x + 15, y + front % MAX_LINE); // question's info
			cout << tmp;
			
			convert_answer(ans[front], x + 77, y + front % MAX_LINE);
			++front;
		}
	}
	void del_question(int key)
	{
		Root = del_node(Root, key); // sai 
		--number;
	}
	void list_key()
	{
		cout << number << "**";
		preorder(Root);
	}
	void read_file(string fileName)
	{
		ifstream file(fileName);
		file >> number;
		if(file.fail())
		{
			cout << "fail ";
			return;
		}
		for(int i = 0; i < number; i++)
		{
			Ques data;
			data.read_file(file);
			Root = insert_node(Root, data, arr[i]);
		}
		file.close();
	}
	void write_node_tofile(ofstream &file, TNode *&way)
	{
		if(way != NULL) // if way is NULL . this function will stop
		{
			way->info.write_file(file);
			write_node_tofile(file, way->left);
			write_node_tofile(file, way->right);
		}
	}
	void write_file(string fileName)
	{
		ofstream file(fileName);
		TNode *p = Root;
		file << number << '\n';
		write_node_tofile(file, p);
	}
};
/////////////////////////////////////////





