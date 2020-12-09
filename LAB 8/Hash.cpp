#include<iostream>
#include<string.h>
using namespace std;

class Hash {
    int n,sum,tableSize,initialPos,temp;
    char enteredWord[30],enteredMeaning[30];

    struct data{
        char word[30];
        char meaning[30];
    }d[10];

    public:
        Hash(int noOfEle){
            n = noOfEle;
            int flag = 1,nearestPrime = n;
            while(flag){
                flag = 0;
                nearestPrime++;
                for(int i=2;i<=n/2;i++){
                    if(nearestPrime%i==0){
                        flag = 1;
                    }
                }
            }

            tableSize = nearestPrime;
            
            for(int i=0;i<tableSize;i++){
                strcpy(d[i].word,"\0");
                strcpy(d[i].meaning,"\0");
            }

        }

        void insertWord(){
            for(int i=0;i<n;i++){
                cout<<"Enter word "<<(i+1)<<": ";
                cin>>enteredWord;
                cout<<"Enter meaning "<<(i+1)<<": ";
                cin>>enteredMeaning;
                cout<<"\n";

                sum = 0;

                for(int i=0;i<strlen(enteredWord);i++){
                    sum += enteredWord[i];
                }

                initialPos = (sum/strlen(enteredWord))%tableSize;
                temp = initialPos;

                while(1){
                    if(!strcmp(d[temp].word,"\0")){
                        cout<<"Inserted at "<<temp<<"\n\n";
                        strcpy(d[temp].word,enteredWord);
                        strcpy(d[temp].meaning,enteredMeaning);
                        break;
                    }

                    temp = (temp+1)%tableSize;

                    if(temp == initialPos){
                        cout<<"Cannot insert\n";
                        break;
                    }
                }

            }
        }

        void deleteWord(){
            cout<<"Enter word to be deleted: ";
            cin>>enteredWord;

            sum = 0;

            for(int i=0;i<strlen(enteredWord);i++){
                sum += enteredWord[i];
            }

            initialPos = (sum/strlen(enteredWord))%tableSize;
            temp = initialPos;

            while(1){
                if(!strcmp(d[temp].word,enteredWord)){
                    strcpy(d[temp].word,"\0");
                    strcpy(d[temp].meaning,"\0");
                    break; 
                }

                temp = (temp+1)%tableSize;

                if(temp == initialPos){
                    cout<<"Word not found\n";
                    break;
                }

            }
        }

        void searchWord(){
            cout<<"Enter word to be searched: ";
            cin>>enteredWord;

            sum = 0;

            for(int i=0;i<strlen(enteredWord);i++){
                sum += enteredWord[i];
            }

            initialPos = (sum/strlen(enteredWord))%tableSize;
            temp = initialPos;

            while(1){
                if(!strcmp(d[temp].word,enteredWord)){
                    cout<<"Meaning of "<<enteredWord<<" : "<<d[temp].meaning;
                    break; 
                }

                temp = (temp+1)%tableSize;

                if(temp == initialPos){
                    cout<<"Word not found\n";
                    break;
                }

            }

        }

        void display(){
            for(int i=0;i<tableSize;i++){
                cout<<"Position "<<(i+1);
                cout<<" : Word - "<<d[i].word;
                cout<<" Meaning - "<<d[i].meaning;
                cout<<"\n";
            }
        }
};

int main() {
    int choice,n;
    cout<<"****Insertion****\n";
    cout<<"Enter number of words in dictionary: ";
    cin>>n;
    cout<<"\n";
    Hash h(n);
    h.insertWord();
    h.display();

    while(1){
        cout<<"\n\n1)Delete Word\n2)Search Word\n3)Exit\nEnter choice: ";
        cin>>choice;

        switch(choice){
            case 1: h.deleteWord();
                    cout<<"\n";
                    h.display();
                    break;
            case 2: h.searchWord();
                    break;
            case 3: exit(0);
        }
    }
}
