#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*

Department of Computer Engineering has student's club named 'Pinnacle Club'
Students of second, third and final year of department can be granted membership on
request. Similarly, one may cancel the membership of club. First node is reserved for
president of club and last node is reserved for the secretary of the club. Write C
program to maintain club member ‘s information using singly linked list. Store student
PRN and Name. Write functions to:
a) Add and delete the members as well as president
    or even secretary.
b) Compute total number of members of club
c) Display members
d) sorting of two linked list
e) merging of two linked list
f) Reversing using three pointers

1. Input at least five nodes.
2. Insert an element at all positions .
3. Delete an element from all positions.

*/


struct node{
    int prn;
    char name[10];
    struct node* next;
};


struct node* create_node(int prn,const char* name){
        struct node *newme = (struct node *)malloc(sizeof(struct node));
        newme->prn=prn;
        strcpy(newme->name,name);
        newme->next=NULL;
        return newme;
};

struct node* clublist=NULL;
struct node* h=NULL;

void add(int prn, const char* name)
{

    struct node* x=create_node(prn,name);
    struct node* t=h->next;
    h->next=x;
    x->next=t;
    h=h->next;
};


void delete( int prn){
    struct node* temp=clublist;

    while(temp->next!=NULL){
        if (temp->next->prn==prn){
            struct node* d=temp->next->next;
            free(temp->next);
            temp->next=d;
        }
        else temp=temp->next;
    }
};


int count(){
    struct node* temp=clublist;
    int cnt=0;
    while(temp!=NULL){
        cnt++;
        temp=temp->next;
    }
    return cnt;
};


void display(struct node* head)
{
    struct node* temp=head;
    while(temp!=NULL){
        printf("%d\t",temp->prn);
        printf("%s\n",temp->name);
        temp=temp->next;
    }
};
struct node* merge(struct node* list1, struct node* list2){
   struct node dummy;
    struct node* tail = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->prn <= list2->prn) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }

    if (list1 != NULL) {
        tail->next = list1;
    }
    if (list2 != NULL) {
        tail->next = list2;
    }

    return dummy.next;
};

struct node* sort(struct node* head){
    if (head==NULL || head->next==NULL){
        return head;
    }

    struct node* t=NULL;
    struct node* slow=head;
    struct node* fast=head;

    while(  fast!=NULL && fast->next!=NULL){
        t=slow;
        slow=slow->next;
        fast=fast->next->next;
    }

    t->next=NULL;

    struct node* l1=sort(head);
    struct node* l2=sort(slow);

    return merge(l1,l2);
    
};




struct node* reverseList(struct node* head){
        struct node* curr=head;
        struct node* prev=NULL;
        struct node* future=NULL;

        while(curr!=NULL){
            future=curr->next;
            curr->next=prev;
            prev=curr;
            curr=future;
        }

       head=prev;
       return head;
};



int main()
{

    clublist = create_node(1001, "president");
    clublist->next = create_node(300, "secretary");
    h = clublist;

    add(101, "first");
    add(104, "second");
    add(111, "third");
    add(305, "fourth");
    add(105, "fifth");

    printf("\nInitial members:\n");
       
    display(clublist);
 
    delete(104);

    printf("\nAfter deleting member with roll number 104:\n");
   
    display(clublist);


    printf("\nTotal members in the club: %d\n", count());

   
    printf("\nAfter sorting members by roll number:\n");
    clublist = sort(clublist);  // Add this line
display(clublist);

    struct node *t1 = create_node(108, "mergeone");
    t1->next = create_node(109, "mergefour");
    struct node *t2 = create_node(106, "mergetwo");
    t2->next = create_node(112, "mergethree");

   
   
    printf("\nAfter merging two lists:\n");
    struct node* merged = merge(t1, t2);
    display(merged);

    printf("\nAfter reversing the list:\n");
    display(reverseList(clublist));
   

    return 0;
}
