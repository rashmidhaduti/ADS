#include<iostream> 
using namespace std; 
  
class BTreeNode 
{ 
    int *keys;  
    int t;      
    BTreeNode **C;
    int n;     
    bool leaf; 
public: 
    BTreeNode(int _t, bool _leaf);   
    void insertNonFull(int k); 
    
    void splitChild(int i, BTreeNode *y); 
  
    void traverse();  
   
    BTreeNode *search(int k);   
friend class BTree; 
}; 
  
// A BTree 
class BTree 
{ 
    BTreeNode *root; 
    int t;  
public: 
   
    BTree(int _t) 
    {  root = NULL;  t = _t; } 
     
    void traverse() 
    {  if (root != NULL) root->traverse(); } 
    
    BTreeNode* search(int k) 
    {  return (root == NULL)? NULL : root->search(k); } 
    
    void insert(int k); 
}; 
  
BTreeNode::BTreeNode(int t1, bool leaf1) 
{ 

    t = t1; 
    leaf = leaf1; 
     
    keys = new int[2*t-1]; 
    C = new BTreeNode *[2*t]; 
 
} 
  
void BTreeNode::traverse() 
{    
    int i; 
    for (i = 0; i < n; i++) 
    { 
       
        if (leaf == false) 
            C[i]->traverse(); 
        cout << " " << keys[i]; 
    } 
  
    if (leaf == false) 
        C[i]->traverse(); 
} 
  
BTreeNode *BTreeNode::search(int k) 
{ 
    int i = 0; 
    while (i < n && k > keys[i]) 
        i++; 
    
    if (keys[i] == k) 
        return this; 
  
    if (leaf == true) 
        return NULL; 
  
    return C[i]->search(k); 
} 
  
void BTree::insert(int k) 
{ 

    if (root == NULL) 
    { 
        
        root = new BTreeNode(t, true); 
        root->keys[0] = k;   
        root->n = 1;  
    } 
    else 
    { 
      
        if (root->n == 2*t-1) 
        { 
            
            BTreeNode *s = new BTreeNode(t, false); 
              
            s->C[0] = root; 
              
            s->splitChild(0, root); 
  
            int i = 0; 
            if (s->keys[0] < k) 
                i++; 
            s->C[i]->insertNonFull(k); 
            
            root = s; 
        } 
        else  
            root->insertNonFull(k); 
    } 
} 
  

void BTreeNode::insertNonFull(int k) 
{ 
   
    int i = n-1; 
  
    if (leaf == true) 
    { 
        
        while (i >= 0 && keys[i] > k) 
        { 
            keys[i+1] = keys[i]; 
            i--; 
        } 
    
        keys[i+1] = k; 
        n = n+1; 
    } 
    else 
    {  
        while (i >= 0 && keys[i] > k) 
            i--; 
    
        if (C[i+1]->n == 2*t-1) 
        { 
            
            splitChild(i+1, C[i+1]); 
  
        
            if (keys[i+1] < k) 
                i++; 
        } 
        C[i+1]->insertNonFull(k); 
    } 
} 
  
void BTreeNode::splitChild(int i, BTreeNode *y) 
{ 
    
    BTreeNode *z = new BTreeNode(y->t, y->leaf); 
    z->n = t - 1; 
  

    for (int j = 0; j < t-1; j++) 
        z->keys[j] = y->keys[j+t]; 
  
    if (y->leaf == false) 
    { 
        for (int j = 0; j < t; j++) 
            z->C[j] = y->C[j+t]; 
    } 
   
    y->n = t - 1; 
     
    for (int j = n; j >= i+1; j--) 
        C[j+1] = C[j]; 
  
    C[i+1] = z; 
 
    for (int j = n-1; j >= i; j--) 
        keys[j+1] = keys[j]; 
  
    keys[i] = y->keys[t-1]; 
  
    n = n + 1; 
} 
  
int main() 
{ 	int ch, y, k, x;
	cout<<"Enter minimum degree of B-tree: ";
	cin>>y;
	BTree t(y);
	do {
		cout<<"\nEnter choice: 1.Insert 2.Traverse 3.Search 4.Exit\n";
		cin>>ch;
		switch(ch) {
			case 1: cout<<"Enter element to insert: ";
					cin>>x;
					t.insert(x);
					break;
			case 2: cout << "Traversal of the constucted tree is "; 
    				t.traverse(); 
    				cout<<endl;
    				break;
    		case 3: cout <<"Enter key to search: ";
    				cin>>k;
    				(t.search(k) != NULL)? cout << "Present\n" : cout << "Not Present\n"; 
    				break;
    		case 4: exit(0);
    		default: cout<<"Invalid choice!!\n";
					
		}
	} while(ch!=4);
  
    return 0; 
} 