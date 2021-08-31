#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "huffman.h"
using namespace std;

// Complete

struct AlphaStrComp {
    bool operator()(pair<set<string>, int> lhs, pair <set<string>, int> rhs) 
	{ // Uses string's built in operator< 
	  // to do lexicographic (alphabetical) comparison
	  return lhs.second < rhs.second; 
	}
  };

RawTextVector AsciiHexIO::read(const char* filename)
{
    RawTextVector text;
    ifstream ifile(filename);
    if(ifile.fail()){
        throw std::invalid_argument("Bad input filename");
    }
    while(!ifile.fail()) {
        char c;
        string word;
        for(int i=0; i < 4; i++){
            ifile >> c;
            if(ifile.fail()){
                if(i > 0) {
                    throw std::runtime_error(
                        "Bad file format...did not find multiple of 4 hex characters");
                }
                else {
                    break; // normal exit
                }
            }
            else {
                word += c;
            }
        }
        if(word.size() == 4) {
            text.push_back(word);
        }
    }
    ifile.close();
    return text;
}

// Complete
void AsciiHexIO::write(const char* filename, const RawTextVector&  text)
{
    const size_t NUM_WORDS_PER_LINE = 8;
    ofstream ofile(filename);
    if(ofile.fail()){
        throw std::runtime_error("Unable to open output file");
    }
    size_t i = 0;
    for( const auto & word : text ){
        ofile << word;
        if(i % NUM_WORDS_PER_LINE != NUM_WORDS_PER_LINE-1 ){
            ofile << " ";
        }
        else {
            ofile << endl;
        }
        i++;
    }
    ofile.close();
}

// Complete
void AsciiHuffmanIo::writeCodedText(
    const char* filename, 
    const CompressedData& inText, 
    const CodeKeyMap& code)
{
    ofstream ofile(filename);
    ofile << code.size() << endl;
    // copy from map to vector so we can sort
    typedef pair<string,string> StrStrPair;
    vector< StrStrPair > codesToSort(code.begin(), code.end());
    std::sort(
        codesToSort.begin(), codesToSort.end(), 
        [] (const StrStrPair& s1, const StrStrPair& s2) -> bool
            { return (s1.first.size() < s2.first.size()) ||
                     (s1.first.size() == s2.first.size() && s1.first < s2.first); } );
    for(const auto& pair : codesToSort) {
        ofile << pair.first << " " << pair.second << endl;
    }
    ofile << inText << endl;
    ofile.close();
}


 /**
     * @brief Reads a compressed file outputting its code/key map and 
     *        compressed data sequence
     * 
     * @param filename name of file to read
     * @param outText string of the compressed sequence of 0s and 1s
     * @param code map of Huffman codes to their original symbols 
     *        (i.e. "100" => "006d")
     */
// To be completed 
void AsciiHuffmanIo::readCodedText(
    const char* filename, 
    CompressedData& outText, 
    CodeKeyMap& code)
{
    // clear old contents of the output parameters that this function
    // should fill in
    code.clear();
    outText.clear();

    // Complete the code below
    ifstream ifile(filename);
    if(ifile.fail()){
        throw runtime_error("Cannot open file");
    }
    int num_lines;
    ifile >> num_lines;
    string line;
    getline(ifile, line);
    for(int i = 0; i < num_lines; i++){
        string line;
        stringstream ss_line;
        getline(ifile, line);
        ss_line.str(line);
        string key;
        string codes;
        ss_line >> key;
        ss_line >> codes;
        code.insert(make_pair(key, codes));

    }
    stringstream ss_line;
    getline(ifile, line);
    ss_line.str(line);
    ss_line >> outText;
    }




// To be completed
/**
     * @brief Compresses a RawTextVector and outputs the compressed sequence 
     *        along with the code/key mapping
     * 
     * @param [in] inText input sequence to be compressed (strings representing 
     *                    the hex of an UTF-16 character)
     * @param [out] outText compressed string of 1s and 0s
     * @param [out] codes code to key mapping
     */
void HuffmanCoder::compress(
    const RawTextVector& inText, 
    CompressedData& outText, 
    CodeKeyMap& codes)
{
    // Clear old contents of the output parameters that this function should fill in
    codes.clear();
    outText.clear();

    //make a frequecny map 
    map<string, string> Haffman;
    map<string, int> frequency_map;
    //for each item in inText
    for(int i =0; i < int(inText.size()); i++){
        //if on map increase frequency
        if(frequency_map.find(inText[i]) != frequency_map.end()){
            frequency_map.find(inText[i])->second += 1;
        }
        //if not on map add to map
        else{
            frequency_map.insert(make_pair(inText[i], 1));
            Haffman.insert(make_pair(inText[i], ""));
        }
    }
    
    //make heap of pairs
    Heap<pair <set<string>, int> , AlphaStrComp > min_queue(2);
    //add all item to this heap
    for(map<string, int>::iterator it = frequency_map.begin(); it != frequency_map.end(); ++it){
       set<string> temp;
       temp.insert(it->first);
       min_queue.push(make_pair(temp, it->second));

    }



    //make min queue for the item and add each one to it
    //for as long as we can do this
    // continue untill there is just one, each time it takes one away (two gone adds one)
    while(min_queue.size() > 1){

    //gets top and puts it in values
    int temp_frq_1 = min_queue.top().second;
    set<string> temp_items_1 = min_queue.top().first;
    min_queue.pop();

    //add 0 to all elements of first pop
    for(set<string>::iterator it = temp_items_1.begin(); it != temp_items_1.end(); ++it){
        (Haffman.find(*it) -> second) = "0" + Haffman.find(*it) -> second;
    }

    //gets next one and puts it in value
    int temp_frq_2 = min_queue.top().second;
    set<string> temp_items_2 = min_queue.top().first;
    min_queue.pop();

    //add 1 to all elements of second pop
    for(set<string>::iterator it = temp_items_2.begin(); it != temp_items_2.end(); ++it){
        (Haffman.find(*it) -> second) = "1" + Haffman.find(*it) -> second;
    }


    //combines and adds to heap
    temp_items_1.insert(temp_items_2.begin(), temp_items_2.end());
    int to_add_frq = temp_frq_1 + temp_frq_2;
    min_queue.push(make_pair(temp_items_1, to_add_frq));

    }
    //now creating outText
    for(int i =0; i < int(inText.size()); i++){
        outText+= Haffman.find(inText[i])->second;
    }

//set Haffman to code
    for(map<string, string>::iterator it = Haffman.begin(); it != Haffman.end(); ++it){
        codes.insert(make_pair(it->second, it->first));

        }


    

}

// To be completed

    /**
     * @brief Decompresses a compressed sequence (string of 1s and 0s) to the 
     * original sequence of symbols
     * 
     * @param [in] inText compressed string of 1s and 0s
     * @param [in] codes code to key mapping
     * @param [out] outText output sequence of strings representing the hex 
     *                      of UTF-16 characters
     */
    
void HuffmanCoder::decompress(
    const CompressedData& inText, 
    const CodeKeyMap& codes, 
    RawTextVector& outText)
{
    // Clear old contents of the output parameter
    outText.clear();
    // Add your code here
    string inputCode;

    // create the decompressed text by reading one char at a time and, 
    // since Huffman codes are prefix codes, once the string matches 
    // a key in the code map, just substitute the word and start again

    char next_didget;
    string check;
    stringstream input_Text;
    input_Text.str(inText);
    string total;
    while(input_Text >> next_didget){
        total = total + next_didget;
        if(codes.find(total) != codes.end()){
            outText.push_back(codes.find(total)->second);
            total = "";
        }



    }

}

// Complete
double HuffmanCoder::ratio(const RawTextVector& inText, const CompressedData& outText, const CodeKeyMap& codes)
{
    // 2 bytes per entry
    double rawSize = 2 * inText.size(); 
    // each character in outText is a bit so convert to bytes
    double compressedSize = (outText.size() + 7) / 8; 
    for(const auto& pair : codes) {
        compressedSize += 2 + pair.first.size()+1; // 2 bytes for 16-bit val + string of 1,0 + null char
    }
    cout << "Original size (bytes): " << rawSize << endl;
 
    cout << "Compressed size (bytes): " << compressedSize << endl;
    double compressionRatio = rawSize / compressedSize;
    cout << "Compression ratio: " << setprecision(2) << fixed << compressionRatio << endl;
    return compressionRatio;
}
