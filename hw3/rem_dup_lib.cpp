#include <iostream>
#include "rem_dup_lib.h"
using namespace std;

// Add your implementations below

void removeConsecutive(Item* head){
    if(head == NULL){
        return;
    }
    if(head->next == NULL){
        return;
    }
    else{
        if(head->next == NULL){
        return;
        }
        if(head->val == (head->next)->val){
            if(head->next->next == NULL){
               delete head->next;
                head->next = NULL;
                return;
            }
            Item* temp = head->next->next;
            delete head->next;
            head->next = temp;
            removeConsecutive(head);

        }

    }
    removeConsecutive(head->next);


}







Item* concatenate(Item* head1, Item* head2){
if(head1 == NULL && head2 != NULL){
    Item *newItem = new Item(head2->val, concatenate(head1, head2->next));
    return(newItem);

}
else if(head1 == NULL && head2 == NULL){
    Item* newItem = NULL;
    return newItem;
}
else{
    Item *newItem = new Item(head1->val, concatenate(head1 -> next, head2));
    return(newItem);

}


/*
if(head1 == NULL && head2 == NULL){
    Item *newItem = NULL;
    return(newItem);
}
else if((head1->next == NULL || head1 == NULL) && (head2->next == NULL || head2 == NULL)){
    Item *newItem = new Item(head1->val, NULL);
    return(newItem);

}
else if(head1-> next == NULL || head1 == NULL){
    Item *newItem1 = new Item(head1->val, head2);
    Item *newItem = new Item(head2->val, concatenate(head2->next, head1));
    return(newItem);
}
else{
    Item *newItem = new Item(head1->val, concatenate(head1->next, head2));
    return(newItem);

}*/


}


