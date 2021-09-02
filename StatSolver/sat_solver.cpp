#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

// Enum to represent Variable values and Clause values (results)
//  UNDEC = UNDECided, ZERO = 0/FALSE, ONE = 1/TRUE
enum TruthVal { UNDEC = -1, ZERO = 0, ONE = 1};
// Map from variable ID (always positive) to value
typedef std::map<int, TruthVal> VarValueMap;

// Variables (true or negated) that are part of a clause
typedef std::vector<int> Clause;
// All clauses in the CNF formula
typedef std::vector<Clause> ClauseList;

// Prototypes

/**
 * @brief Reads the CNF formula from a file
 * 
 * @param [in]  filename C string containing the filename
 * @param [out] numV Should be set to the number of variables the problem specified
 * @param [out] numC Should be set to the number of clauses the problem specified
 * @param [out] clauses List of clauses where each clause contains the integer list of literals
 * @return true if an error occurs
 * @return false if successful
 */
bool readCNFFile(char* filename,
                 size_t& numV,
                 size_t& numC,
                 ClauseList& clauses);

/**
 * @brief Main entry point of the sat solver
 * 
 * @param [in] v  Current variable ID to assign
 * @param [in] numV  Number of variables total
 * @param [in] varValues Map of variable IDs to TruthVal
 * @param [in] clauses List of clauses from the formula
 * @return true if a solution was found
 * @return false if a solution was not found
 */
bool satSolve(size_t v,
              size_t numV,
              VarValueMap& varValues,
              ClauseList& clauses);




// Feel free to add other prototypes below
//  (a function to evaluate the formula given a set of variable values would
//   likely be useful. It would return ONE=true if all the clauses were satisfied,
//   ZERO=false if any clause evaluated to false), and UNDEC if some clauses were
//   still UNDECIDED due to some variables not being set yet.  To help this task
//   we have provided a function evalClause() to evaluate a single clause.)

bool satSolveHelper(size_t v,
              size_t numV,
              VarValueMap& varValues,
              ClauseList& clauses);

//takes in list of clauses and number of clauses
TruthVal evalAll(VarValueMap& varValues, ClauseList& clauses, size_t v);


// To be completed
bool readCNFFile(char* filename,
                 size_t& numV,
                 size_t& numC,
                 ClauseList& clauses)
{
    // Add your code here
    ifstream ifile(filename);
    if(ifile.fail()) {
        cerr << "Couldn't open file" << endl;
        return 1;
    }

    //throw out all lines that start with c
    char firstchar = 'c';
    string line;
    while(firstchar == 'c'){
        getline(ifile, line);
        firstchar = line[0]; 
    }

    string collect;
    stringstream liness;
    liness.str(line);
    //now throw out next two words
    liness >> collect;
    liness >> collect;

    int coll;

    //set next characters to numV and numC
    liness >> coll;
    numV = coll;
    liness >> coll;
    numC = coll;
    int t = int(numC);

    for(int i = 0; i < t; i++){
        string line;
        getline(ifile, line);
        stringstream newline;
        newline.str(line);
        int temp;
        newline >> temp;
        Clause clauseList;
        while(temp != 0){
            clauseList.push_back(temp);
            newline >> temp;
        }
        clauses.push_back(clauseList);
    }
    return false;

}

// Complete - Debug routine
void printClauses(const ClauseList& clauses)
{
    // uses C++ 11 ranged loops
    for(const auto& myclause : clauses) {
        for(int varID : myclause) {
            cout << varID << " ";
        }
        cout << endl;
    }
}

// Complete - Evaluates a single clause
TruthVal evalClause(VarValueMap& varValues,
                    Clause& clause)
{
    bool atLeastOneUndecided = false;
    for( int varNum : clause)
    {
        // get value of indicated variable (using tertiary operator)
        TruthVal myVarValue = (varNum < 0) ? varValues[-varNum] : varValues[varNum];

        // check if this variable value makes the clause true
        if((varNum < 0 && myVarValue == ZERO) || (varNum > 0 && myVarValue == ONE)){
            // caluse is satisfied...no need to go further
            return ONE;
        }
        else if( myVarValue == UNDEC) {
            atLeastOneUndecided = true;
        }
    }
    // if clause is not true, we now check if it is undecided or false
    if(true == atLeastOneUndecided ) {
        return UNDEC;
    }
    // clause is false
    return ZERO;

}




/**
 * @brief Main entry point of the sat solver
 * 
 * @param [in] v  Current variable ID to assign
 * @param [in] numV  Number of variables total
 * @param [in] varValues Map of variable IDs to TruthVal
 * @param [in] clauses List of clauses from the formula
 * @return true if a solution was found
 * @return false if a solution was not found
 */
// To be completed - Main recursive backtracking search function
bool satSolve(size_t v,
              size_t numV,
              VarValueMap& varValues,
              ClauseList& clauses)
{

// var values is alreay made w all undecideds
    //varValues.find(1)->second = ZERO;
    //varValues.find(2)->second = ZERO;
    //varValues.find(3)->second = ONE;
    //varValues.find(4)->second = ZERO;
    return satSolveHelper(v, numV, varValues, clauses);
    

}

//helper fucntion 
bool satSolveHelper(size_t v, size_t numV, VarValueMap& varValues, ClauseList& clauses){

    //end case if all works return true and quit
    if(evalAll(varValues, clauses, v) == 1){
        return true;
    }
    //if it does not work return false
    if(evalAll(varValues, clauses, v) == 0){
        return false;
    }

    //now not all work something is wrong
    //work one varable at a time and then recurse
    //if variable is not assigned make it 1
    if(varValues.find(v)->second == UNDEC){
        varValues.find(v)->second = ZERO;
        //does this value work
        if(evalAll(varValues, clauses, v) == 1){
            return true;
        }
        if(v != numV && satSolveHelper(v + 1, numV, varValues, clauses)){
            return true;
        }
    }

    //if it was false make it true
    if(varValues.find(v)->second == ZERO){
        varValues.find(v)->second = ONE;
        if(evalAll(varValues, clauses, v) == 1){
            return true;
        }
        else if(v == numV){
            varValues.find(v)->second = UNDEC;
            return false;
        }
        
        else if(satSolveHelper(v + 1, numV, varValues, clauses)){
            return true;
        }
        else{
            varValues.find(v)->second = UNDEC;
            return false;
        }
        
    }

    //var was 0 and 1 and did not work
    //must go back 
    //reset to UNDEC
    return false;
}


//see if all clauses are correct
TruthVal evalAll(VarValueMap& varValues, ClauseList& clauses, size_t v){
    int size = clauses.size();
    for(int i =0; i < size; i++){
        if(evalClause(varValues, clauses[i]) == ZERO){
            return ZERO;
        }
        else if(evalClause(varValues, clauses[i]) == UNDEC){
            return UNDEC;
        }   
    }
    return ONE;

}


// Complete (though you can add temporary debugging code)
int main(int argc, char* argv[])
{
    if(argc < 3) {
        cerr << "Please provide the cnf and output filename" << endl;
        return 1;
    }
    size_t numVars, numClauses;
    ClauseList clauses;

    bool status = readCNFFile(argv[1],  numVars, numClauses, clauses);
    if(status) {
        cerr << "Exiting..." << endl;
        return 1;
    }
    printClauses(clauses);
    cout << endl << numVars << endl << numClauses << endl;


    
//#ifdef SATDEBUG
    printClauses(clauses);
//#endif

    // Declare the variable value map to track our assignment of values
    VarValueMap varValues;
    for(size_t i=1; i <= numVars; i++) {
        varValues.insert(make_pair(i, UNDEC));
    }

    // Attempt to find a solution (using Davis-Putnam backtracking algorithm)
    status = satSolve(1, numVars, varValues, clauses);

    // Output Results
    ofstream ofile(argv[2]);
    if(ofile.fail()) {
        cerr << "Couldn't open file " << argv[2] << endl;
        return 1;
    }

    if(status) {
        for(size_t i=1; i <= numVars; i++) {

            if(varValues[i] != UNDEC) {
                ofile << i << " =  " << varValues[i] << endl;
            }
        }
    }
    else {
        ofile << "No solution hasdfojaosd dafs" << endl;
    }
  
    cout << "values are in output file"

    ofile.close();
    return 0;
}
