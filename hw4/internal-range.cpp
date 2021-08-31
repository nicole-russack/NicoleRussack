#include "internal-range.h"
#include <iostream>
using namespace std;



int sumInternalRange(Node * root, int depth, int min, int max){

    if(root == NULL){
        return 0;
    }
    //if we are done the depth must be one
    //at the bottom
   else if(depth == 1){
       if(root->key >= min && root->key <= max){
           return 1;
       }
       else{
           return 0;
       }

    }
    //this is if it is 0 and nothing works
    else if(depth == 0){
        return 0;
    }
    //then we are at a node with nothing in it
    else if(root->left == NULL && root->right == NULL){
        if(root->key >= min && root->key <= max){
           return 1;
       }
       else{
           return 0;
       }
    }
    //we need to do the same thing on the right node
    else if(root->left == NULL){
        if(root->key >= min && root->key <= max){
            return sumInternalRange(root -> right, depth - 1, min, max) + 1;

       }
       else{
           return sumInternalRange(root -> right, depth - 1, min, max);
       }
        
    }
    //must do the same thing on the left node
    else if(root->right == NULL){
        if(root->key >= min && root->key <= max){
            return 1 + sumInternalRange(root -> left, depth - 1, min, max);
       }
       else{
           return sumInternalRange(root -> left, depth - 1, min, max);
       }
        
    }
    //node has both left and right nodes 
    else{
        if(root->key >= min && root->key <= max){
            return 1 + sumInternalRange(root -> left, depth - 1, min, max) +  sumInternalRange(root -> right, depth - 1, min, max);

       }
       else{
        return sumInternalRange(root -> left, depth - 1, min, max) +  sumInternalRange(root -> right, depth - 1, min, max);

       }
    }

}

// You may add any prototypes of helper functions here