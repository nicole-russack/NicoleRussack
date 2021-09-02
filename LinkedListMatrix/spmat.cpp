#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include "spmat.h"
using namespace std;

#ifdef SPARSE_DEBUG
#include "spmat-debug.h"    
// global instance of the debug helper
SparseMatrixDebugHelper debug;
#endif


// Define and initialize the constant static member npos here
const size_t SparseMatrix::npos = (size_t) - 1;


// ----------------------------------------------------------------------------
// ------------------ Coord struct Implementation -----------------------------
// ----------------------------------------------------------------------------

// Constructor
// COMPLETE 
SparseMatrix::Coord::Coord(size_t row, size_t col) :
    r(row), c(col)
{
}

// operator[] accessors
// To be completed - Must adhere it requirements in the .h
/**
         * @brief Allows r and c member to be access with array
         *  indices 0 and 1, respectively.  May facilitate 
         *  more generic access to each member.
         * 
         * @param index 0 = row, 1 = column
         * @return size_t& reference to r or c member
         * @throw std::out_of_range if index is 2 or more
         */
size_t& SparseMatrix::Coord::operator[](size_t index) {

if(index == 0){
    return r;
}
else if(index == 1){
    return c;
}
else{
    throw std::out_of_range("index is not 0 or 1");

}

}

size_t const& SparseMatrix::Coord::operator[](size_t index) const {
if(index == 0){
    return r;
}
else if(index == 1){
    return c;
}
else{
    throw std::out_of_range("index is not 0 or 1");

}

}


/**
* @brief Compares two Coord objects
* 
* @param rhs right hand side operand
* @return true if the Coord objects are equal (not equal) for operator == (!=) 
* @return false otherwise
*/

// operator== comparison function
// To be completed - Must adhere it requirements in the .h
bool SparseMatrix::Coord::operator==(const Coord& rhs) const
{ 
   if((*this)[0] == rhs[0] && (*this)[1] == rhs[1]){
       return true;
   }
   else{
       return false;
   }
}


// operator != comparison function
// COMPLETE
bool SparseMatrix::Coord::operator!=(const Coord& rhs) const
{
    return !operator==(rhs);
}

// ----------------------------------------------------------------------------
// ------------------ SparseItem struct Implementation ------------------------
// ----------------------------------------------------------------------------

// Constructor
// COMPLETE 
SparseMatrix::SparseItem::SparseItem(Coord coord, double v)
{
    this->val = v;
    this->coord = coord;
    this->prev[ROW] = this->prev[COL] = nullptr;
    this->next[ROW] = this->next[COL] = nullptr;
}

// ----------------------------------------------------------------------------
// ----------------- SparseMatrix class Implementation ------------------------
// ----------------------------------------------------------------------------

// Constructor
// To be completed - Must adhere to requirements in the .h
    /**
     * @brief Intializes an n x n sparse matrix that is emtpy (all values of 0)
     * 
     * @param n 
     * @throws std::invalid_argument if n is 0
     */
SparseMatrix::SparseMatrix(size_t n) : 
    /* Add code as needed */ n_(n)
{
    if(0U == n_) {
        throw std::invalid_argument("n must be greater than 0");
    }
    /* Add code as needed */
    //
        lists_[0] = new SparseItem *[n];
        lists_[1] = new SparseItem *[n];

        for(size_t i =0; i < n; i++){
            lists_[0][i] = nullptr;
            lists_[1][i] = nullptr;
        }
        //ew SparseItem** lists_[0] = [n];
        //new SparseItem** lists_[1][n];


    //}

}

// Destructor
// To be completed 
SparseMatrix::~SparseMatrix() 
{

for(size_t i = 0; i < n_; i++){
if(lists_[0][i] == nullptr){
    continue;
}
else{
SparseItem* item = lists_[0][i];
while(item->next[0] != nullptr){
    SparseItem* temp = item;
    item = item->next[0];
    delete temp;

}
delete item;
}
}

delete[] lists_[0];
delete[] lists_[1];


}

// COMPLETE
SparseMatrix::SparseItem* SparseMatrix::createSparseItem(const SparseMatrix::Coord& coord, double val)
{
    SparseItem* ptr = new SparseItem(coord, val);
#ifdef SPARSE_DEBUG    
    debug.addItem(ptr);
#endif
    return ptr;
}

// COMPLETE
SparseMatrix::SparseItem* SparseMatrix::lowerBound(size_t list, Coord target_coord ) const
{
    SparseItem* head = this->lists_[list][target_coord[list]];
    size_t target_index = target_coord[1-list];

    if(head == nullptr) {
        return nullptr;
    }
    else if( head->coord[1-list] > target_index ) {
        return nullptr;
    }
    else {
        while(  head->next[list] != nullptr && 
                head->next[list]->coord[1-list] <= target_index  ) 
        {
            head = head->next[list];
        }
        return head;        
    }
}


// COMPLETED
double SparseMatrix::get(const Coord& coord) const
{
    if(coord[ROW] < 0 || coord[ROW] >= n_ || coord[COL] < 0 || coord[COL] >= n_ ){
        throw std::invalid_argument("Bad coordinates");
    }
    SparseItem* head = lowerBound(ROW, coord );
    if(nullptr == head || head->coord[COL] != coord[COL]){
        return 0;
    }
    return head->val;
}

// COMPLETED
void SparseMatrix::print(std::ostream &os) const
{
    os << setprecision(7);
    for(size_t r = 0; r < this->n_; r++) {
        SparseItem* ptr = this->lists_[ROW][r];
        size_t col = 0;
        while(ptr != NULL) {
            while(col < ptr->coord[COL]) {
                os << setw(8) << 0;
                col++;
            }
            os << setw(8) << ptr->val;
            col++;
            ptr = ptr->next[ROW];
        }
        while(col < this->n_) {
            os << setw(8) << 0;
            col++;
        }
        os << endl;
    }
}


    /**
     * @brief Removes node from any lists it is a member of and abstracts freeing
     *        of the memory    
     * 
     * @param node  node to delete
     * @throws std::invalid_argument if node is nullptr
     */
// To be completed - Must adhere it requirements in the .h
void SparseMatrix::deleteNode(SparseItem* node)
{
    if(nullptr == node){
        throw std::invalid_argument("argument must not be null");
    }
    /* Add necessary code to update all other pointers */
    /* Note: calling delete is provided for you below  */

    //for colloms, repreat for rows but with 1
    //add more comments for understanding
    //if does not have previous value 
    if(node->prev[0] == nullptr){
        // no prev but has next
        if(node->next[0] != nullptr ){
            lists_[0][node->coord[0]] = node->next[0];
            (node->next[0]) -> prev[0] = nullptr;
        }
        // no prev or next
        else{
            lists_[0][node->coord[0]] = nullptr;
        }
        
     }
     // has previous value
     else{
         //has previous value but no next
         if(node->next[0] == nullptr){
             (node->prev[0]) -> next[0] = nullptr;
         }
         else{
             //has previous value and next value
             (node->prev[0]) -> next[0] = node->next[0];
             (node->next[0])->prev[0] = node->prev[0];

         }
     }

        if(node->prev[1] == nullptr){
        // no prev but has next
        if(node->next[1] != nullptr ){
            lists_[1][node->coord[1]] = node->next[1];
            (node->next[1]) -> prev[1] = nullptr;
        }
        // no prev or next
        else{
            lists_[1][node->coord[1]] = nullptr;
        }
        
     }
     // has previous value
     else{
         //has previous value but no next
         if(node->next[1] == nullptr){
             (node->prev[1]) -> next[1] = nullptr;
         }
         else{
             //has previous value and next value
             (node->prev[1]) -> next[1] = node->next[1];
             (node->next[1])->prev[1] = node->prev[1];

         }
     }
    
    /* This code should not be altered and should end this function */
#ifdef SPARSE_DEBUG    
    debug.deleteItem(node);
#endif
    delete node;
}


   /**
     * @brief If the cell at the given coordinates does not exist (i.e. it is 
     * currently 0), create and insert the new cell provided the value
     * is not zero.  If the cell at the given coordinates does exists, 
     * update its value unless the value is 0 in which case the cell 
     * should be removed from the lists. Attempting to set a non-existent
     * cell (i.e. that is already implicitly 0) with an explicit value of 0
     * should simply have no effect.  
     * 
     * @note Must run in O(|r| + |c|) where |r| and |c| are the length of the 
     * items in the lists in the row and column dimension and not O(n)  
     * 
     * @param coord Coordinates of the cell to set. Index 0 is the row and 
     *              index 1 is the column
     * @param val Value to set the cell (0 indicates removal of the cell)
     * @throw std::out_of_range if either coordinate is not between 0 and n-1
     */

// To be completed - Must adhere it requirements in the .h

// 1- check if the coordinate row/col is within bountary. if not throw error
// if it is in the boundary - find the cooridnate in a given row
// if cannot find --> lowerbound returns null --> and value is not 0 then create the cell
// if cell dne and not setting to 0
// must create using create sparse item then set values 
void SparseMatrix::set(const Coord& coord, double val)
{
// check if the row/col is within boundary 
if(coord[0] > n_ || coord[0] < 0 || coord[1] > n_ || coord[1] < 0){
     throw std::out_of_range("must be between 0 and n");
}

// finds value = to or cloest to colom indes
SparseItem* close_col = lowerBound(0, coord);
SparseItem* close_row = lowerBound(1, coord);

// if clest colum index = the right one it exists
if(close_col != NULL && close_row != NULL){
if(close_col->coord[0] == coord[0] && close_col->coord[1] == coord[1]){
    // if val is not 0 set to val
    if(val != 0){
        close_col->val = val;

    }
     //if val is 0 delete coordnate 
    else{
        
        deleteNode(close_col);

    }
    return;
}
    
}
// if cell dne and set to 0 then return
if(val == 0){
        return;
 }

// Cell DNE and value is not 0
// Need to create a cell and set its value


//create item
SparseItem* new_item =createSparseItem(coord, val);

//add to colum 
//if colum is empty
if(lists_[0][coord[0]] == nullptr){
  //  cout << "done this" << endl;
    lists_[0][coord[0]] = new_item;
    new_item-> next[0] = nullptr;
    new_item -> prev[0] = nullptr;
}
//if colum is not empty
else{
    // if new item is the first on the list 
    // will alwyas have an item after bc if row was empty would be caught in first 
    if(close_col == NULL){
        //cout << "here" << endl;
        SparseItem* temp = lists_[0][coord[0]];
        lists_[0][coord[0]] = new_item;
        new_item->next[0] = temp;
       
        new_item->prev[0] = nullptr;
        
        temp->prev[0] = new_item;
        
    }

    // if what we are adding is last on the lisgt 
    else if(close_col->next[0] == nullptr){
         //cout << "here????" << endl;
        close_col->next[0] = new_item;
        new_item ->next[0] = nullptr;
        new_item ->prev[0] = close_col;

    }

    //what we are adding is in the middle
    else{
        // cout << "this" << endl;
        SparseItem* temp = close_col->next[0];
        close_col->next[0] = new_item;
        new_item->next[0] = temp;
        (new_item->next[0])->prev[0] = new_item;
        new_item->prev[0] = close_col;

    }

}


//add to row 
//if row is empty
if(lists_[1][coord[1]] == nullptr){
    lists_[1][coord[1]] = new_item;
    new_item-> next[1] = nullptr;
    new_item -> prev[1] = nullptr;
}
//if row is not empty
else{
    // if new item is the first on the list 
    // will alwyas have an item after bc if row was empty would be caught in first 
    if(close_row == NULL){
        SparseItem* temp = lists_[1][coord[1]];
        lists_[1][coord[1]] = new_item;
        new_item->next[1] = temp;
        new_item->prev[1] = nullptr;
        temp->prev[1] = new_item;
    }

    // if what we are adding is last on the list 
   else if(close_row->next[1] == nullptr){
        close_row->next[1] = new_item;
        new_item ->next[1] = nullptr;
        new_item ->prev[1] = close_row;

    }

    //what we are adding is in the middle
    else{
        SparseItem* temp = close_row->next[1];
        close_row->next[1] = new_item;
        new_item->next[1] = temp;
        (new_item->next[1])->prev[1] = new_item;
        new_item->prev[1] = close_row;

    }

}



 //  Leave these as the last lines of this function 
#ifdef SPARSE_DEBUG    
    try {
        debug.checkConsistency(this);
    }
    catch (std::logic_error& e) {
        cerr << e.what();
    }
#endif 
}

// To be completed - Must adhere it requirements in the .h
//   Be sure to meet the run-time requirements

/**
     * @brief Returns the sum of a given row or column (i.e. dimension). 
     * 
     * @note Must run in O(k) where k is the length of the 
     * items in the specified dimension's list and not O(n)
     * 
     * @param coord Coordinate range to iterate over. The coordinates must 
     * contain exactly 1 value equal to SparseMatrix::npos representing the 
     * dimension to iterate over.  
     * @return double Sum of the given dimension
     * @throw std::invalid_argument if one coordinate value is not
     * SparseMatrix::npos
     * @throw std::out_of_range if the other coordinate is not
     *  between 0 and n-1
     */
double SparseMatrix::sumDim(const Coord& coord) const
{
//sets sum to 0
double sum = 0;
if(coord[COL] > n_ && coord[ROW] > n_){
    throw std::invalid_argument("both values cannot be npos");
}
if(coord[COL] > n_ && coord[ROW] < 0){
    throw std::out_of_range("ROW val is less than 0");

}
if(coord[ROW] > n_ && coord[COL] < 0){
    throw std::out_of_range("COL val is less than 0");

}

//we are working with rows
if(coord[COL] > coord[ROW]){
//if row is emptry return 0;
if(lists_[ROW][coord[ROW]] == nullptr){
    return 0;
}
else{
    //row is not empty
    SparseItem* item = lists_[ROW][coord[ROW]];
    sum += item-> val;
    while(item -> next[ROW] != nullptr){
        item = item->next[ROW];
        sum += item->val;
    }
}
}
// now working with col
else{
    //if col is emptry return 0;
if(lists_[COL][coord[COL]] == nullptr){
    return 0;
}
else{
    //row is not empty
    SparseItem* item = lists_[COL][coord[COL]];
    sum += item-> val;
    while(item -> next[COL] != nullptr){
        item = item->next[COL];
        sum += item->val;
    }
}
}
return sum;
}


   /**
     * @brief  Copies the source row or column to the destination row or 
     * column
     * 
     * @note Must run in O(max(k1,k2)^2) where k1 and k2 are the length of the 
     * items in the lists in the src and dest dimension and not O(n)  
     * 
     * @param srcCoord Coordinate of the source range to copy.
     * The coordinates must contain exactly 1 value equal to 
     * SparseMatrix::npos representing the dimension to iterate over. 
     * @param destCoord Coordinate of the destination range.
     * The coordinates must contain exactly 1 value equal to 
     * SparseMatrix::npos representing the dimension to iterate over. 
     * @throw std::invalid_argument if one coordinate value in either the
     * source or destination coordinates is not SparseMatrix::npos
     * @throw std::out_of_range if the other coordinate in either the
     * source or destination coordinates is not between 0 and n-1
     */

// To be completed - Must adhere it requirements in the .h
//   Be sure to meet the run-time requirements
void SparseMatrix::copyDim(const Coord& srcCoord, const Coord& dstCoord)
{
    if(srcCoord[ROW] < n_ && srcCoord[COL] < n_){
        throw std::invalid_argument("only one argument can be npos");
    }
    if(dstCoord[ROW] < n_ && dstCoord[COL] < n_){
        throw std::invalid_argument("only one argument can be npos");
    }
    if(dstCoord[ROW] < dstCoord[COL]){
        if(dstCoord[ROW] < 0 || dstCoord[ROW] >= n_){
            throw std::out_of_range("other argument is not in range");
        }
    }
    else if(dstCoord[ROW] > dstCoord[COL]){
        if(dstCoord[COL] < 0 || dstCoord[COL] >= n_){
            throw std::out_of_range("other argument is not in range");
        }
    }
    if(srcCoord[ROW] < srcCoord[COL]){
        if(srcCoord[ROW] < 0 || srcCoord[ROW] >= n_){
            throw std::out_of_range("other argument is not in range");
        }
    }
    else if(srcCoord[ROW] > srcCoord[COL]){
        if(srcCoord[COL] < 0 || srcCoord[COL] >= n_){
            throw std::out_of_range("other argument is not in range");
        }
    }
//col to col
if(srcCoord[ROW] > srcCoord[COL] && dstCoord[ROW] > dstCoord[COL]){
    //if same col to same col return
    if( srcCoord[COL] == dstCoord[COL]){
        return;
    }
    //if it is emptry to begin with return 
    // clear col or row 
    if(lists_[COL][dstCoord[COL]]!= nullptr){
        SparseItem* item = lists_[COL][dstCoord[COL]];
        SparseItem* temp; 
        while(item->next[COL] != nullptr){
            temp = item->next[COL];
            deleteNode(item);
            item = temp;
        }
        deleteNode(item);

    }


// add to col or row

if(lists_[COL][srcCoord[COL]]== nullptr){
    return;
}
else{
    SparseItem* item = lists_[COL][srcCoord[COL]];
    while(item->next[COL] != nullptr){
        Coord temp;
        temp[COL] = dstCoord[COL];
        temp[ROW] =  item->coord[ROW];
        set(temp,item->val);
        item = item->next[COL];

    }
        Coord temp;
        temp[COL] = dstCoord[COL];
        temp[ROW] =  item->coord[ROW];
        set(temp,item->val);
       //set([dstCoord[COL], item->coord[ROW]],item->val);

}


}

else if(srcCoord[ROW] < srcCoord[COL] && dstCoord[ROW] < dstCoord[COL]){
    //if same col to same col return
    if( srcCoord[ROW] == dstCoord[ROW]){
        return;
    }
    //if it is emptry to begin with return 
    // clear col or row 
    if(lists_[ROW][dstCoord[ROW]]!= nullptr){
        SparseItem* item = lists_[ROW][dstCoord[ROW]];
        SparseItem* temp; 
        while(item->next[ROW] != nullptr){
            temp = item->next[ROW];
            deleteNode(item);
            item = temp;
        }
        deleteNode(item);

    }


// add to col or row

if(lists_[ROW][srcCoord[ROW]]== nullptr){
    return;
}
else{
    SparseItem* item = lists_[ROW][srcCoord[ROW]];
    while(item->next[ROW] != nullptr){
        Coord temp;
        temp[ROW] = dstCoord[ROW];
        temp[COL] = item->coord[COL];
        set(temp,item->val);
        item = item->next[ROW];

    }
        Coord temp;
        temp[ROW] = dstCoord[ROW];
        temp[COL] = item->coord[COL];
        set(temp,item->val);
       //set([dstCoord[COL], item->coord[ROW]],item->val);

}


}

// this is row(sorce) to col (destination)
else if ((srcCoord[ROW] < srcCoord[COL] && dstCoord[ROW] > dstCoord[COL])){
    // deletes all of the values in the colum
    
    double keepval = 0;
    int keepy;
   
    if(lists_[COL][dstCoord[COL]]!= nullptr){
        SparseItem* item = lists_[COL][dstCoord[COL]];
        SparseItem* temp; 
        while(item->next[COL] != nullptr){
            // if there is an overlap stores the overlap in a temp
            if(item->coord[0] == srcCoord[ROW]){
               keepval = item->val;
               keepx = item->coord[0];
               keepy = item->coord[1];
           }
            temp = item->next[COL];
            deleteNode(item);
            item = temp;
        }
        if(item->coord[0] == srcCoord[ROW]){
               keepval = item->val;
               keepx = item->coord[0];
               keepy = item->coord[1];
           }
        deleteNode(item);

    }
    
    // destination col is cleared and overlap is stored in temp var
    
   if(lists_[ROW][srcCoord[ROW]]== nullptr && keepval != 0){
    Coord temps;
    temps[0] = keepy;
    temps[1] =  dstCoord[COL];
    set(temps,keepval);
    return;
}
if(lists_[ROW][srcCoord[ROW]]== nullptr){
    return;

}
else{
    SparseItem* item = lists_[ROW][srcCoord[ROW]];
    while(item->next[ROW] != nullptr){
        Coord temps;
        temps[0] = item->coord[1];
        temps[1] =  dstCoord[COL];
        set(temps,item->val);
        item = item->next[ROW];

    }
        Coord temps;
        temps[0] = item->coord[1];
        temps[1] =  dstCoord[COL];
        set(temps,item->val);
        if(keepval != 0){
            Coord temps;
            temps[0] = keepy;
            temps[1] =  dstCoord[COL];
            set(temps,keepval);
        }

}

    
}

// finnaly col to Row
else{

    double keepval = 0;
    int keepx;
    int keepy;
    if(lists_[ROW][dstCoord[ROW]]!= nullptr){
        SparseItem* item = lists_[ROW][dstCoord[ROW]];
        SparseItem* temp; 
        while(item->next[ROW] != nullptr){
            // if there is an overlap stores the overlap in a temp
            if(item->coord[1] == srcCoord[COL]){
               keepval = item->val;
               keepx = item->coord[1];
               keepy = item->coord[0];
           }
            temp = item->next[ROW];
            deleteNode(item);
            item = temp;
        }
        if(item->coord[1] == srcCoord[COL]){
               keepval = item->val;
               keepx = item->coord[1];
               keepy = item->coord[0];
           }
        deleteNode(item);

    }
    
    // destination col is cleared and overlap is stored in temp var
    
   if(lists_[COL][srcCoord[COL]]== nullptr && keepval != 0){
    Coord temps;
    temps[1] = keepy;
    temps[0] =  dstCoord[ROW];
    set(temps,keepval);
    return;
}
if(lists_[COL][srcCoord[COL]]== nullptr){
    return;

}
else{
    SparseItem* item = lists_[COL][srcCoord[COL]];
    while(item->next[COL] != nullptr){
        Coord temps;
        temps[1] = item->coord[0];
        temps[0] =  dstCoord[ROW];
        set(temps,item->val);
        item = item->next[COL];

    }
        Coord temps;
        temps[1] = item->coord[0];
        temps[0] =  dstCoord[ROW];
        set(temps,item->val);
        if(keepval != 0){
            Coord temps;
            temps[1] = keepy;
            temps[0] =  dstCoord[ROW];
            set(temps,keepval);
        }

}
    

}



#ifdef SPARSE_DEBUG    
    try {
        debug.checkConsistency(this);
    }
    catch (std::logic_error& e) {
        cerr << e.what();
    }
#endif
 }

