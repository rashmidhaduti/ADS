#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
        int key;
        Node **forward;
        Node(int, int);
};

Node::Node(int key, int level){
    this->key = key;
    forward = new Node*[level+1];
    memset(forward, 0, sizeof(Node*)*(level+1));
}

class SkipList 
{ 
    int MAXLVL; 
    float P; 
    int level; 
    Node *header;

    public: 
        SkipList(int); 
        int randomLevel(); 
        Node* createNode(int, int); 
        void insertElement(int); 
        void deleteElement(int);
        void searchElement(int);
        void displayList(); 
}; 

SkipList::SkipList(int MAXLVL) 
{ 
    this->MAXLVL = MAXLVL; 
    this->P = P; 
    level = 0; 

    header = new Node(-1, MAXLVL); 
} 

int SkipList::randomLevel() 
{ 
    return (int)rand() % MAXLVL;
} 

Node* SkipList::createNode(int key, int rlevel) 
{ 
    Node *n = new Node(key, rlevel); 
    return n; 
}

void SkipList::insertElement(int key){
    Node* current = header;
    int rlevel = randomLevel();
    Node* prev = NULL;
    Node* n = createNode(key, rlevel);

    if(rlevel>level){
        level = rlevel;
    }

    for (int i = level; i >= 0; i--) 
    { 
        while(current->forward[i] != NULL && current->forward[i]->key <= key){
            current = current->forward[i];
        }
        if(rlevel >= i && current->key != key){
            n->forward[i] = current->forward[i];
            current->forward[i] = n;
        }
    }

}

void SkipList::searchElement(int key){
    Node* current = header;

    for(int i=level;i>=0;i--){
        while(current->forward[i] && current->forward[i]->key<key){
            current = current->forward[i];
        }
    }

    current = current->forward[0];

    if(current && current->key==key){
        cout<<"Found\n";
    }
    else
        cout<<"Not found\n";
}

void SkipList::deleteElement(int key){
    Node* current = header;
    Node* update[MAXLVL+1];
    memset(update, 0, sizeof(Node*)*(MAXLVL+1)); 

    for(int i=level;i>=0;i--){
        while(current->forward[i] && current->forward[i]->key<key){
            current = current->forward[i];
        }
        update[i] = current;
    }   

    current = current->forward[0];
     
    if(current != NULL and current->key == key){
        for(int i=0;i<=level;i++){ 
            if(update[i]->forward[i] != current) 
                break; 
            update[i]->forward[i] = current->forward[i]; 
        } 
    }

    while(level>0 && header->forward[level] == 0) 
        level--; 
}

void SkipList::displayList() 
{ 
    cout<<"\n*****SKIP LIST*****"<<"\n"; 
    for (int i=0;i<=level;i++) 
    { 
        Node *node = header->forward[i]; 
        cout << "Level " << i << ": "; 
        while (node != NULL) 
        { 
            cout << node->key<<" "; 
            node = node->forward[i]; 
        } 
        cout << "\n"; 
    } 
}

int main() 
{ 
    SkipList lst(3); 
    int choice,ele;
    do{
        cout<<"\n1)INSERT\n2)DELETE\n3)SEARCH\n4)EXIT\nENTER CHOICE: ";
        cin>>choice;
        switch(choice){
            case 1: cout<<"Enter element: ";
                    cin>>ele;
                    lst.insertElement(ele);
                    lst.displayList();
                    break;
            case 2: cout<<"Enter element: ";
                    cin>>ele;
                    lst.deleteElement(ele);
                    lst.displayList();
                    break;
            case 3: cout<<"Enter element: ";
                    cin>>ele;
                    lst.searchElement(ele);
                    break;
            case 4: exit(0);
            		break;
            default: cout<<"Enter valid choice \n";
        }
    }while(1);
}
