#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;
    

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO

    int counter = 0; // delete later
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    virtual bool isLeftChild(AVLNode<Key,Value>* n1);
    virtual bool isZigZag(AVLNode<Key,Value>* n1);
    virtual void rotateLeft(AVLNode<Key,Value>* n1);
    virtual void rotateRight(AVLNode<Key,Value>* n1);
    virtual void insertFix(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    virtual void removeFix(AVLNode<Key,Value>* n1, int diff);
    virtual AVLNode<Key, Value>* getPredecessor(AVLNode<Key,Value>* n1);


    // Add helper functions here


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    //If empty tree => set n as root, b(n) = 0, done!
    if(this -> root_ == NULL){
        // Node<Key,Value>* newt = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        AVLNode<Key, Value>* root = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        root->setLeft(NULL);
        root->setRight(NULL);
        root->setParent(NULL);

        this -> root_ = root;
        //char b = 0;  
        return;
    }

    //walk tree and insert node into the right place 
    //want an AVL temp to point at the node
   //  AVLNode<Key, Value>* current = new AVLNode<Key, Value>(root_->getKey(), root_->getValue(), NULL);

    AVLNode<Key, Value>* current = static_cast< AVLNode<Key,Value>* >(this->root_);
    //AVLNode<Key, Value>* current = root;
    //current->setLeft(tempt->getLeft());
   // current->setRight(tempt->getRight());

    AVLNode<Key, Value>* currentParent = NULL;
    while(current != NULL){

        //if the item exists and this is it set the new value to it
        if(new_item.first == current ->getKey()){
            return;
        }

        else if(new_item.first > current->getKey()){
            currentParent = current;
            current = current -> getRight();
        }
        else{
            currentParent = current;
            current = current -> getLeft();
        }
    }

    //now current is NULL in the right place
    //see if it left or right child
    //set to that place 

    
    if(new_item.first < currentParent->getKey()){
        AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, currentParent);
        currentParent->setLeft(newNode);
        newNode->setRight(NULL);
        newNode->setLeft(NULL);
        newNode->setBalance(char(0));

        insertFix(currentParent, newNode);
        return;
        //currentParent->updateBalance(char(-1));

        /*
        if(currentParent -> getBalance() == char(1)){
            currentParent->setBalance(char(0));
            return;
        }
        else{
            insertFix(currentParent, newNode);
            return;

        }*/
    }
    else{
        AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, currentParent);
        currentParent->setRight(newNode);
        newNode->setRight(NULL);
        newNode->setLeft(NULL);
        newNode->setBalance(char(0));
        //currentParent->updateBalance(char(1));
        if(currentParent -> getBalance() == char(-1)){
            currentParent->setBalance(char(0));
            return;
        }
        else{
            insertFix(currentParent, newNode);
            return;

        }
    }
    
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    if (this->counter == 95) {
        std::cout << "hi" << std::endl;
    }
    this->counter++;

    //must first find it
    AVLNode<Key, Value>* current = static_cast< AVLNode<Key,Value>* >(this->root_);
    AVLNode<Key, Value>* RemovalNode = NULL;

    //walk tree to find the correct node
    while(current != NULL){
        if(current->getKey() == key){
            RemovalNode = current;
            break;
        }
        if(current->getKey() < key){
            current = current->getRight();
        }
        else{
            current = current->getLeft();
        }
    }

    //error if node does not exist
    if(RemovalNode == NULL){
        std::cout << "Node does not exist " << std::endl;
        return;
    }

    //if node has 0 children remove it + continue
    if(RemovalNode->getLeft() == NULL && RemovalNode->getRight() == NULL){
        if(RemovalNode->getParent() == NULL){
            this->root_ = NULL;
            delete RemovalNode;
            return;
        }
        else if(isLeftChild(RemovalNode)){
            RemovalNode->getParent()->setLeft(NULL);
            AVLNode<Key, Value>* parent = RemovalNode->getParent();
            delete RemovalNode;
            removeFix(parent, 1);
            return;

        }
        else{
            RemovalNode->getParent()->setRight(NULL);
            AVLNode<Key, Value>* parent = RemovalNode->getParent();
            delete RemovalNode;
            removeFix(parent, -1);
            return;
        }
    }

    //if node has 1 child promote it
    //only has right node 
     if(RemovalNode->getLeft() == NULL){
         if(RemovalNode->getParent() == NULL){
             this->root_ = RemovalNode->getRight();
             RemovalNode->getRight()->setParent(NULL);
             AVLNode<Key, Value>* parent = RemovalNode->getParent();
             delete RemovalNode;
             removeFix(parent, -1);
             return;

         }
         else if(isLeftChild(RemovalNode)){
             RemovalNode->getParent()->setLeft(RemovalNode->getRight());
             RemovalNode->getRight()->setParent(RemovalNode->getParent());
             AVLNode<Key, Value>* parent = RemovalNode->getParent();
             delete RemovalNode;
             removeFix(parent, 1);
             return;
         }
         else{
             RemovalNode->getParent()->setRight(RemovalNode->getRight());
             RemovalNode->getRight()->setParent(RemovalNode->getParent());
             AVLNode<Key, Value>* parent = RemovalNode->getParent();
             delete RemovalNode;
             removeFix(parent, -1);
             return;

         }

     }
     else if(RemovalNode->getRight() == NULL){
         if(RemovalNode->getParent() == NULL){
             this->root_ = RemovalNode->getLeft();
             RemovalNode->getLeft()->setParent(NULL);
             AVLNode<Key, Value>* parent = RemovalNode->getParent();
             delete RemovalNode;
             removeFix(parent, 1);
             return;

         }
         if(isLeftChild(RemovalNode)){
             RemovalNode->getParent()->setLeft(RemovalNode->getLeft());
             RemovalNode->getLeft()->setParent(RemovalNode->getParent());
             AVLNode<Key, Value>* parent = RemovalNode->getParent();
             delete RemovalNode;
             removeFix(parent, 1);
             return;
         }
         else{
             RemovalNode->getParent()->setRight(RemovalNode->getLeft());
             RemovalNode->getLeft()->setParent(RemovalNode->getParent());
             AVLNode<Key, Value>* parent = RemovalNode->getParent();
             delete RemovalNode;
             removeFix(parent, -1);
             return;

         }

     }

     //now if the node has 2 children 
     //swap positions with predecessor 

    AVLNode<Key,Value>* predo = getPredecessor(RemovalNode);
    nodeSwap(RemovalNode, predo);

    if(RemovalNode->getLeft() == NULL && RemovalNode->getRight() == NULL){  
        if(isLeftChild(RemovalNode)){
            RemovalNode ->getParent()->setLeft(NULL);
            AVLNode<Key, Value>* parent = RemovalNode->getParent();
            delete RemovalNode;
            removeFix(parent, 1);
        }
        else{
            RemovalNode ->getParent()->setRight(NULL);
            AVLNode<Key, Value>* parent = RemovalNode->getParent();
            delete RemovalNode;
            removeFix(parent, -1);
        }        
        return;
     }

        else if(RemovalNode->getRight() == NULL){
                //check if found is left child
                if(isLeftChild(RemovalNode)){
                    //set founds parent left child to founds right child
                    RemovalNode->getParent()->setLeft(RemovalNode->getLeft());
                    //right child parent is founds parent
                    RemovalNode->getLeft()->setParent(RemovalNode->getParent());
                    AVLNode<Key, Value>* parent = RemovalNode->getParent();
                    delete RemovalNode;
                    removeFix(parent, 1);
                }
                else{
                    RemovalNode->getParent()->setRight(RemovalNode->getLeft());
                    //right child parent is founds parent
                    RemovalNode->getLeft()->setParent(RemovalNode->getParent());
                    AVLNode<Key, Value>* parent = RemovalNode->getParent();
                    delete RemovalNode;
                    removeFix(parent, -1);
                

                }

                //delete RemovalNode;

                return;



}

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}




template<class Key, class Value>
bool AVLTree<Key, Value>::isLeftChild( AVLNode<Key,Value>* n1)
{
    if(n1 == NULL){
        return false;
    }
    else if(n1->getParent() == NULL){
        return false;
    }
    else if(n1->getParent()->getLeft() == n1){
        return true;
    }
    else{
        return false;
    }
}


//take in grandparent(2 or -2) then see if it is a ZigZag
template<class Key, class Value>
bool AVLTree<Key, Value>::isZigZag( AVLNode<Key,Value>* n1)
{
    //we know that the grandparent is not ballanced(2)
    //check if it is a zigzag on the left
    //techencaly 2 ways that it can be a zigzag

    //Left right or Right left
    //start at grandparent 0 if -2 go left if +2 go right
    //maybe make two functions for this we will seeeeee
    //we go right
    if(n1->getBalance() == 2){
        //now left ->zigzag
        if(n1->getRight()->getBalance() == -1){
            return true;
        }


    }
    //we go right
    else if(n1 ->getBalance() == -2){
        //then go left ->zigzag
        if(n1->getLeft()->getBalance() == 1){
            return true;
        }

    }
    return false;


}


//virtual void rotateLeft(AVLNode<Key,Value>* n1);
template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight( AVLNode<Key,Value>* n1){
    //does not adjust the balance values

    //start with grandparent (Z based on slides)

    //make temps of everything to make it easier
    AVLNode<Key, Value>* z = n1;
    AVLNode<Key, Value>* y = n1->getLeft();
    //AVLNode<Key, Value>* d = n1->getRight();
    AVLNode<Key, Value>* x = n1->getLeft()->getLeft();
    AVLNode<Key, Value>* c = n1->getLeft()->getRight();
    AVLNode<Key, Value>* ParentParent = n1->getParent();


    //set zs left or right to Y (new root)
    if(ParentParent != NULL){
        if(isLeftChild(z)){
        ParentParent->setLeft(y);
    }
    else{
        ParentParent->setRight(y);
    }
    y->setParent(ParentParent);
    }
    else{
        this -> root_ = y;
        y->setParent(NULL);
    }

    //y is now the head of this node 
    //y getLeft is done

    //now set y->right to z
    y->setRight(z);
    z->setParent(y);

    //z get right is the same 
    //set z left to c
    z->setLeft(c);
    if(c != NULL){
        c->setParent(z);
    }


    y->setLeft(x);
    if(x != NULL){
        x->setParent(y);
    }
    

    return;
   

    
}




template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft( AVLNode<Key,Value>* n1){
     std::cout << "Rotated lefttt" << std::endl;
    //start with grandparent (Z based on slides)

    //make temps of everything to make it easier
    AVLNode<Key, Value>* x = n1;
    AVLNode<Key, Value>* y = n1->getRight();
    AVLNode<Key, Value>* b = n1->getRight()->getLeft();
    //AVLNode<Key, Value>* z = n1->getRight()->getRight();
    //AVLNode<Key, Value> c = n1->getLeft()->getRight();
    AVLNode<Key, Value>* ParecntParent = n1->getParent();


    //set xs left or right to Y (new root)
    if(ParecntParent != NULL){
        if(isLeftChild(n1)){
        ParecntParent->setLeft(y);
    }
    else{
        ParecntParent->setRight(y);
    }
    y->setParent(ParecntParent);
    }
    else{
       this -> root_ = y;
        y->setParent(NULL);
    }
   

    //y is now the head of this node 
    //y getLeft is done

    //now set y->right to z
    //z left and right are already done


    //set y left to x
    y->setLeft(x);
    x->setParent(y);

    //set x right to b
    x->setRight(b);
    if(b != NULL){
        b->setParent(x);

    }
    
    
}


//assume n1 - parent, n2 - child are all balanced
//need g to be ballanced
//recurse
template<class Key, class Value>
void AVLTree<Key, Value>::insertFix( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2){
     std::cout << "at start ********" << std::endl;
//update granparents value 


//what if grandparent is NULL
//will always have a parent

//if grandparent is NULL then the grandparent is ballanced
if(n1 == NULL){
    if(n2->getBalance() == 1 || n2->getBalance() == -1){
        return;
    }
    else if(n2->getBalance() == 2){
        //rotateLeft(n2);
        return;
    }
    else if(n2->getBalance() == 2){
        //rotateRight(n2);
        return;
    }

}

else if(isLeftChild(n2)){
    n1->updateBalance(char(-1));
}
//if left child
else{
    n1->updateBalance(char(1));
}

if(n1->getBalance() == char(0)){
    return;
}
else if(n1->getBalance() == 1 || n1->getBalance() == -1){
    insertFix(n1->getParent(), n1);
}
//it is not ballanced we need to see if we zig or zig zag

//left leaning 
else if(n1->getBalance() == -2){
    if(isZigZag(n1)){
        std::cout << "Is ZigZag 2" << std::endl;
        AVLNode<Key, Value>* g = n1;
        AVLNode<Key, Value>* p = n2;
        AVLNode<Key, Value>* n = n2->getRight();
        rotateLeft(n2);
        rotateRight(n1);
        if(n->getBalance() == -1){
            p->setBalance(0);
            g->setBalance(1);
            n->setBalance(0);

        }
        else if(n->getBalance() == 1){
            p->setBalance(-1);
            g->setBalance(0);
            n->setBalance(0);

        }
        else if(n->getBalance() == 0){
            p->setBalance(0);
            g->setBalance(0);
            n->setBalance(0);

        }
        return;

    }
    else{
        std::cout << "GOT HEREEEEE ********" << std::endl;
        rotateRight(n1);
        n2->setBalance(0);
        n1->setBalance(0);
    }
    return;


}
//now assume right leaning 
else if(n1->getBalance() == 2){
    if(isZigZag(n1)){
        std::cout << "Is ZigZag 1" << std::endl;
        AVLNode<Key, Value>* g = n1;
        AVLNode<Key, Value>* p = n2;
        AVLNode<Key, Value>* n = n2->getLeft();

        rotateRight(n2);
        rotateLeft(n1);
        if(n->getBalance() == 0){
            p->setBalance(0);
            g->setBalance(0);
            n->setBalance(0);

        }
        else if(n->getBalance() == -1){
            g->setBalance(0);
            p->setBalance(1);
            n->setBalance(0);

        }
        else if(n->getBalance() == 1){
            p->setBalance(0);
            g->setBalance(-1);
            n->setBalance(0);

        }
        return;

    }
    else{
        std::cout << "GOT HEREEEEE ~~~~~~~~~~~~~~~~~" << std::endl;
        rotateLeft(n1);
        n1->setBalance(0);
        n2->setBalance(0);
    }
    return;


}



}



template<class Key, class Value>
void AVLTree<Key, Value>::removeFix( AVLNode<Key,Value>* n1, int diff){
    if(n1 == NULL){
        return;
    }
    int balance = n1->getBalance() + diff;
    //n1->updateBalance(diff);
    if(balance == -2){
        AVLNode<Key, Value>* c = n1->getLeft();
        AVLNode<Key, Value>* p = n1->getParent();
        bool wasLeft = isLeftChild(n1);

        if(c->getBalance() == -1){
            rotateRight(n1);
            n1->setBalance(0);
            c->setBalance(0);
            if(isLeftChild(n1)){
                removeFix(p, 1);
            }
            else{
                removeFix(p, -1);
            }
            return;

        }
        else if(c->getBalance() == 1){
            AVLNode<Key, Value>* g = c->getRight();
            rotateLeft(c);
            rotateRight(n1);
            if(g->getBalance() == 1){
                n1->setBalance(0);
                c->setBalance(-1);
                g->setBalance(0);

            }
            else if(g->getBalance() == 0){
                n1->setBalance(0);
                c->setBalance(0);
                g->setBalance(0);
                
            }
            else if(g->getBalance() == -1){
                n1->setBalance(1);
                c->setBalance(0);
                g->setBalance(0);
                
            }
            //error is right here
            //should come bafck at 782 but it does 783
            if(wasLeft){
                removeFix(p, 1);
            }
            else{
                removeFix(p, -1);
            }
            return;




        }
        else if(c->getBalance() == 0){
            rotateRight(n1);
            n1->setBalance(-1);
            c->setBalance(1);
            return;

        }

    }
    else if(balance == 2){
        AVLNode<Key, Value>* c = n1->getRight();
        AVLNode<Key, Value>* p = n1->getParent();
        bool wasLeft = isLeftChild(n1);
        if(c->getBalance() == 1){
            rotateLeft(n1);
            n1->setBalance(0);
            c->setBalance(0);
            if(isLeftChild(n1)){
                removeFix(p, 1);
            }
            else{
                removeFix(p, -1);
            }
            return;

        }
        else if(c->getBalance() == -1){
            AVLNode<Key, Value>* g = c->getLeft();
            rotateRight(c);
            rotateLeft(n1);
            if(g->getBalance() == -1){
                n1->setBalance(0);
                c->setBalance(1);
                g->setBalance(0);

            }
            else if(g->getBalance() == 0){
                n1->setBalance(0);
                c->setBalance(0);
                g->setBalance(0);
                
            }
            else if(g->getBalance() == 1){
                n1->setBalance(-1);
                c->setBalance(0);
                g->setBalance(0);
                
            }
            if(wasLeft){
                removeFix(p, 1);
            }
            else{
                removeFix(p, -1);
            }
            return;
        }
        else if(c->getBalance() == 0){
            rotateLeft(n1);
            n1->setBalance(1);
            c->setBalance(-1);
            return;
            

        }


        
    }
    else if(balance == 0){
        AVLNode<Key, Value>* p = n1->getParent();
        n1->setBalance(0);
        if(isLeftChild(n1)){
                removeFix(p, 1);
            }
        else{
                removeFix(p, -1);
            }
        return;
    }
    else if(balance == 1){
        n1->setBalance(1);
        return;
    }
    else if(balance == -1){
        n1->setBalance(-1);
        return;
    }
    return;
}



// virtual void getPredecessor(AVLNode<Key,Value>* n1)
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::getPredecessor( AVLNode<Key,Value>* n1){


    AVLNode<Key, Value>* it = n1;
    if(it->getLeft() == NULL){

    while(it->getParent() != NULL){
        if(it->getParent()->getRight() == it){
            return it->getParent();
            }
        else{
            it = it->getParent();
            }
        }
        return NULL;
    }
    it = it ->getLeft();
    while(it -> getRight() != NULL){
        it = it -> getRight();
    }
    return it;


    
}

#endif
