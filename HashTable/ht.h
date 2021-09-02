#ifndef HT_H
#define HT_H
#include <vector>
#include <iostream>
#include <cmath>

typedef size_t HASH_INDEX_T;

// Complete - Base Prober class
struct Prober {
    // Data members
    HASH_INDEX_T start_;     // initial hash location, h(k)
    HASH_INDEX_T m_;         // table size
    HASH_INDEX_T numProbes_; // probe attempts for statistic tracking
    static const HASH_INDEX_T npos = (HASH_INDEX_T)-1; // used to indicate probing failed
    void init(HASH_INDEX_T start, HASH_INDEX_T m) 
    {
        start_ = start;
        m_ = m;
        numProbes_ = 0;
    }
    HASH_INDEX_T next() {
        throw std::logic_error("Not implemented...should use derived class");
    }
};

// Almost Complete - Fill in the if statement below.
struct LinearProber : public Prober {

    HASH_INDEX_T next() 
    {
        // Complete the condition below that indicates failure
        // to find the key or an empty slot

        //if we went all the way around and still found nothing 
        if(numProbes_ == m_) {
            return npos; 
        }
        HASH_INDEX_T loc = (start_ + numProbes_) % m_;
        numProbes_++;
        return loc;
    }
};

// To be completed
struct QuadraticProber : public Prober {
    HASH_INDEX_T next() 
    {
        //where we start the quadratic value at
        
        // In quadratic probing with a prime table size,
        //  only m/2 probes are guaranteed before revisiting a 
        //  location (and potential cycle of locations)

        //if we have too many probes and go around agan 
        if(numProbes_ > m_/2) {
            return npos; 
        }
        // Add code here
        HASH_INDEX_T loc = (start_ + (numProbes_ * numProbes_)) % m_;
        numProbes_++;
        return loc;



    }
};


// Hash Table Interface
template<
    typename K, 
    typename V, 
    typename Prober = LinearProber,
    typename Hash = std::hash<K>, 
    typename KEqual = std::equal_to<K> >
class HashTable
{
public:
    // You should not (need to) change these
    typedef K KeyType;
    typedef V ValueType;
    typedef std::pair<KeyType, ValueType> ItemType;
    typedef Hash Hasher;
    struct HashItem {
        ItemType item;
        bool deleted;
        HashItem(const ItemType& newItem){
            item = newItem;
            deleted = false;
        }
    };

    /**
     * @brief Construct a new Hash Table object
     * 
     * @param resizeAlpha Loading factor threshold at which the table should resize
     * @param prober Probing object of type Prober
     * @param hash Hash functor that supports hash(key) and returns a HASH_INDEX_T
     * @param kequal Functor that checks equality of two KeyType objects
     */
    HashTable(
        //number of nodes that have ever existed (deleted or not)/capactity 
        double resizeAlpha = 0.4, 
        const Prober& prober = Prober(),
        const Hasher& hash = Hasher(), 
        const KEqual& kequal = KEqual());

    /**
     * @brief Destroy the Hash Table object and delete all remaining
     *         key,value pairs
     * 
     */
    ~HashTable();

    /**
     * @brief Returns true if the table has no non-deleted key,value pairs,
     *        and false otherwise
     * 
     */
    bool empty() const;

    /**
     * @brief Returns number of (non-deleted) key,value pairs in the table
     * 
     * @return size_t 
     */
    size_t size() const;

    /**
     * @brief Inserts a new item into the map, or, if an item with the
     *        given key already exists, it updates the Value of that item
     *        with the second value of the pair, p
     * 
     * @param p Pair to insert  
     * @throw std::logic_error If no free location can be found
     */
    void insert(const ItemType& p);

    /**
     * @brief Removes (marks as deleted) the item with the given key.  
     * Does nothing if an item with the given key does not exist.
     * 
     * @param key 
     */
    void remove(const KeyType& key);

    /**
     * @brief Finds an item with the given key and returns a pointer 
     * to the key,value pair
     * 
     * @param key 
     * @return ItemType const* nullptr is returned if the key does not exist
     */
    ItemType const * find(const KeyType& key) const;
    ItemType * find(const KeyType& key);

    /**
     * @brief Finds the value corresponding to the given key
     * 
     * @param key 
     * throw std::out_of_range if the key does not exist
     * @return ValueType Value associated with key
     */
    const ValueType& operator[](const KeyType& key) const;
    ValueType& operator[](const KeyType& key);

    // Debug / Performance functions
    void reportAll(std::ostream& out) const;
    void clearTotalProbes() { totalProbes_ = 0; }
    size_t totalProbes() const { return totalProbes_; }
private:
    /**
     * @brief Helper routine to find a given key
     * 
     * @param key 
     * @return HashItem* returns nullptr if key does not exist
     */
    HashItem * internalFind(const KeyType& key) const;
    /**
     * @brief Performs the probing sequence and returns the index
     * of the table location with the given key or the location where
     * key can be inserted (i.e. the index now contains nullptr) but is
     * available.
     * 
     * @param key 
     * @return returns npos is the key does not exist and
     * no free location is available
     */
    HASH_INDEX_T probe(const KeyType& key) const;

    // Constant to signify an invalid hash location is being returned
    static const HASH_INDEX_T npos = Prober::npos;

    /**
     * @brief Resizes the hash table replacing the old with a new
     * table of the next prime size given in CAPACITIES.  Must rehash
     * all non-deleted items while freeing all deleted items.
     * 
     * Must run in O(m) where m is the new table size
     * 
     * @throws std::logic_error if no more CAPACITIES exist
     */
    void resize();

    // Data members
    std::vector<HashItem*> table_; // actual hash table
    Hasher hash_;   
    KEqual kequal_;
    mutable Prober prober_;  // mutable allows const member functions to modify this member
    // debug/performance counters
    mutable size_t totalProbes_; // mutable allows const member functions to modify this member
    // prime capacities to be used when resizing/rehashing is needed
    static const HASH_INDEX_T CAPACITIES[];
    HASH_INDEX_T mIndex_;  // index to CAPACITIES
    double resizeAlpha_;

    size_t size_;
    size_t deleted;

    // ADD MORE DATA MEMBERS HERE, AS NECESSARY


};

// ----------------------------------------------------------------------------
//                           Hash Table Implementation
// ----------------------------------------------------------------------------

// Static array of prime table sizes
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
const HASH_INDEX_T HashTable<K,V,Prober,Hash,KEqual>::CAPACITIES[] =
    {
        11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877,
        205759, 411527, 823117, 1646237, 3292489, 6584983, 13169977, 26339969, 52679969,
        105359969, 210719881, 421439783, 842879579, 1685759167
    };


/**
     * @brief Construct a new Hash Table object
     * 
     * @param resizeAlpha Loading factor threshold at which the table should resize
     * @param prober Probing object of type Prober
     * @param hash Hash functor that supports hash(key) and returns a HASH_INDEX_T
     * @param kequal Functor that checks equality of two KeyType objects
     */
// To be completed
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
HashTable<K,V,Prober,Hash,KEqual>::HashTable(
    double resizeAlpha, const Prober& prober, const Hasher& hash, const KEqual& kequal)
       :  hash_(hash), kequal_(kequal), prober_(prober)
{
    // Initialize any other data members as necessary
    resizeAlpha_ = resizeAlpha;
    mIndex_ = 0;
    size_ = 0;
    deleted = 0;
    totalProbes_ = 0;
    table_.resize(CAPACITIES[mIndex_]);
    for(HASH_INDEX_T i=0; i < CAPACITIES[mIndex_]; i++){
        table_[i] = nullptr; 
    }
}


 /**
     * @brief Destroy the Hash Table object and delete all remaining
     *         key,value pairs
     * 
     */

// To be completed
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
HashTable<K,V,Prober,Hash,KEqual>::~HashTable()
{
    for(HASH_INDEX_T i=0; i < CAPACITIES[mIndex_]; i++){
        if(table_[i] != nullptr) {
            delete table_[i];
        }
    }

    //now need to delete data in the hashtable
}


 /**
     * @brief Returns true if the table has no non-deleted key,value pairs,
     *        and false otherwise
     * 
     */
// To be completed
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
bool HashTable<K,V,Prober,Hash,KEqual>::empty() const
{   
    //count = size of has table, not sure how to have that happen
    if(size_ == 0){
        return true;
    }
    return false;
    

}

// To be completed
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
size_t HashTable<K,V,Prober,Hash,KEqual>::size() const
{
    return size_;

}

// To be completed
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
void HashTable<K,V,Prober,Hash,KEqual>::insert(const ItemType& p)
{
    //resize if needed to
    //size + deleted??
    //size only increases when we need new + insert table 


    //find location

    //probe will give exact location 
    if((double(size_ + deleted)/CAPACITIES[mIndex_]) >= resizeAlpha_){
        //std::cout << "Resize function" << std::endl;
        resize();
       

    }

    if(size_ + deleted >= CAPACITIES[mIndex_]){
       throw std::logic_error("No free locations can be found"); 
    }


    size_t location = probe(p.first);

    if(location == npos){
        throw std::logic_error("Prober went in circle"); 
    }

    //if empty add to this 
    if(table_[location] == nullptr){
        //need to create item and set to this
        HashItem* newtitem = new HashItem(p);
        table_[location] = newtitem;
        size_++;
       // std::cout << p.first << " " << location << std::endl;
    }
    //if not empty but same key
    //do I need to do KEquil h
    else if(table_[location]->item.first == p.first){
        table_[location]->item.second = p.second;
        table_[location]->deleted = false;
    }
    //if we are adding to it
    else{
        //already has item must change values of them
        table_[location]->item = p;
        table_[location]->deleted = false;
    }
    return;

}

// To be completed
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
void HashTable<K,V,Prober,Hash,KEqual>::remove(const KeyType& key)
{   
    //if they key doesnt exist return it
    if(find(key) == nullptr){
        return;
    }

    //now if it is on the tree
    //finds, deletes the element and sets to nullptr
    HASH_INDEX_T h = this->probe(key);
    
    table_[h]->deleted = true;
    deleted ++;
    size_ --;
    return;

}


// Complete
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
typename HashTable<K,V,Prober,Hash,KEqual>::ItemType const * 
HashTable<K,V,Prober,Hash,KEqual>::find(const KeyType& key) const
{
    HASH_INDEX_T h = this->probe(key);
    if((npos == h) || nullptr == table_[h] ){
        return nullptr;
    }
    return &table_[h]->item;
}

// Complete
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
typename HashTable<K,V,Prober,Hash,KEqual>::ItemType * 
HashTable<K,V,Prober,Hash,KEqual>::find(const KeyType& key)
{
    HASH_INDEX_T h = this->probe(key);
    if((npos == h) || nullptr == table_[h] ){
        return nullptr;
    }
    return &table_[h]->item;
}

// Complete
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
const typename HashTable<K,V,Prober,Hash,KEqual>::ValueType& 
HashTable<K,V,Prober,Hash,KEqual>::operator[](const KeyType& key) const
{
    HashItem const * item = this->internalFind(key);
    if(item == nullptr) { throw std::out_of_range("Bad key"); }
    return item->value;
}

// Complete
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
typename HashTable<K,V,Prober,Hash,KEqual>::ValueType& 
HashTable<K,V,Prober,Hash,KEqual>::operator[](const KeyType& key)
{
    HashItem const * item = this->internalFind(key);
    if(item == nullptr) { throw std::out_of_range("Bad key"); }
    return item->value;
}

// Complete 
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
typename HashTable<K,V,Prober,Hash,KEqual>::HashItem* 
HashTable<K,V,Prober,Hash,KEqual>::internalFind(const KeyType& key) const
{
    HASH_INDEX_T h = this->probe(key);
    if((npos == h) || nullptr == table_[h] ){
        return nullptr;
    }
    return table_[h];
}


// To be completed
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
void HashTable<K,V,Prober,Hash,KEqual>::resize()
{
    //makes sure there is a larger size
    if( mIndex_ == sizeof(CAPACITIES)/sizeof(CAPACITIES[0])-1)
    {
        throw std::logic_error("Cannot resize further");
    }

    
    //increases size index
    mIndex_ += 1;
    //makes new table and sets all to blank
    std::vector<HashItem*> newTable;
    for(HASH_INDEX_T i=0; i < CAPACITIES[mIndex_]; i++){
        newTable.push_back(nullptr); 
    }


    //swaps the two 
    //now table_ is large and all blank, newtable holds other values
    table_.swap(newTable);


     int tempsize =  0;

    //adds other values in
    for(HASH_INDEX_T i = 0; i < CAPACITIES[mIndex_ - 1]; i++ ){
        //if value exists and not delited 
        if(newTable[i] != nullptr && newTable[i]->deleted == false){
           //if location for new entry is valid add it
           HASH_INDEX_T tempLocation =  probe(newTable[i]->item.first);
           if(tempLocation == npos){
               //throw error
           }
           else{
            table_[tempLocation] = newTable[i];
            tempsize ++;
           }
          
        }
        //delete the values so that storage is delted
        else if(newTable[i] != nullptr && newTable[i]->deleted == true){
            delete newTable[i];
        }
    }

    size_ = tempsize;
    deleted = 0;



    
}

// Almost complete
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
HASH_INDEX_T HashTable<K,V,Prober,Hash,KEqual>::probe(const KeyType& key) const
{
    HASH_INDEX_T h = hash_(key) % CAPACITIES[mIndex_];

    prober_.init(h, CAPACITIES[mIndex_]);

    HASH_INDEX_T loc = prober_.next(); 
    totalProbes_++;
    while(Prober::npos != loc)
    {   
        if(nullptr == table_[loc] ) {
            return loc;
        }

        // fill in the condition for this else if statement which should 
        // return 'loc' if the given key exists at this location

        //deleted part
        //if it has been delited not an avlible spot?

        //!table_[loc]->deleted && kequal_(key,table_[loc]->item.first)

        //if table location is not delited and the value is the same (exists in table)
        else if( !table_[loc]->deleted && kequal_(key,table_[loc]->item.first)) {
            return loc;
        }
        loc = prober_.next();
        totalProbes_++;
    }

    return npos;
}

// Complete
template<typename K, typename V, typename Prober, typename Hash, typename KEqual>
void HashTable<K, V, Prober, Hash, KEqual>::reportAll(std::ostream& out) const
{
	for(HASH_INDEX_T i = 0; i < CAPACITIES[mIndex_]; ++i)
	{
		if(table_[i] != nullptr)
		{
			out << "Bucket " << i << ": " << table_[i]->item.first << " " << table_[i]->item.second << std::endl;
		}
	}
}

#endif