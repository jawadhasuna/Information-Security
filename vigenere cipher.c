#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <string>
#include <cctype>
using namespace std;
// Function to compute the GCD of two numbers
int computeGCD(int a, int b) {
 return b == 0 ? a : computeGCD(b, a % b);
// Function to find repeated sequences and their distances
map<int, int> kasiskiExamination(const string &ciphertext, int seqLength = 3) {
 map<string, vector<int>> sequencePositions;
 map<int, int> gcdFrequency;
 for (size_t i = 0; i < ciphertext.length() - seqLength + 1; i++) {
 string seq = ciphertext.substr(i, seqLength);
 sequencePositions[seq].push_back(i);
 }
 for (auto &pair : sequencePositions) {
 vector<int> positions = pair.second;
 if (positions.size() > 1) {
 vector<int> distances;
 for (size_t i = 1; i < positions.size(); i++) {
 distances.push_back(positions[i] - positions[i - 1]);
 }
 int overallGCD = distances[0];
 for (size_t i = 1; i < distances.size(); i++) {
 overallGCD = computeGCD(overallGCD, distances[i]);
 }
 if (overallGCD > 1) {
 gcdFrequency[overallGCD]++;
 }
 }
 }
 return gcdFrequency;
}
// Function to split cipher text into groups based on key length
vector<string> splitCipherText(const string &ciphertext, int keyLength) {
 vector<string> groups(keyLength, "");
 for (size_t i = 0; i < ciphertext.length(); i++) {
 groups[i % keyLength] += ciphertext[i];
 }
 return groups;
}
// Function to perform frequency analysis and guess the key
char findMostFrequentChar(const string &text) {
 map<char, int> freq;
 for (char c : text) {
 freq[c]++;
 }
 char mostFrequent = 'A';
 int maxFreq = 0;
 for (auto &pair : freq) {
 if (pair.second > maxFreq) {
 mostFrequent = pair.first;
 maxFreq = pair.second;
 }
 }
 return mostFrequent;
}
// Function to determine key from frequency analysis
string determineKey(vector<string> groups) {
 string key = "";
 for (string &group : groups) {
 char mostFrequent = findMostFrequentChar(group);
 char keyChar = ((mostFrequent - 'A') - ('E' - 'A') + 26) % 26 + 'A';
 key += keyChar;
 }
 return key;
}
int main() {
 string cipherText = 
"uvxtqdvfhfoxngipdgpjxesnpiljhwesibwafrzoclmsshsdgwbqcguocuhtdvcpzdhwttoceoeqzxdoij"
 
"ccuvpuogfihfrxohwfwcusgosieituciisqscpebpuigfcuuvxttxfzsuvtdcjsgtdckffhpbazgtmsrussuce"
 
"jqhgcrvghjbvgwgthdogdnspejpoqtehdqwrtwcjbiffcfhifqwocapuxfgthkxssafghmoctadcwafwc"
 
"usgosiniauwrbgibbsuvtoohfztdhxpbdgqjsftohporcflihscffpuwdooeqzxdoijcctocegtsjxdshfueq"
 
"weujkpwezcjxwamztbfcicluvtjbiffcfhlpfztocevdxgtsjxdshbbsbdemwrbhxpbhbftqfdwwsfripih"
 
"ffhptiisxohtsbtuhwjgzoclmsshsljzaisaqmdvwcuvteshjucbbsnocbutnscucudcbqiiffcfhlpfztohxs"
 "amoheskfzdqatohportysrvhxpbdgwcusgosibdemwrbhxpbh";
 transform(cipherText.begin(), cipherText.end(), cipherText.begin(), ::toupper);
 map<int, int> gcdFrequencies = kasiskiExamination(cipherText, 3);
 int probableKeyLength = 0;
 int maxFrequency = 0;
 for (auto &entry : gcdFrequencies) {
 if (entry.second > maxFrequency) {
 maxFrequency = entry.second;
 probableKeyLength = entry.first;
 }
 }
 cout << "\nEstimated Key Length: " << probableKeyLength << endl;
 vector<string> groups = splitCipherText(cipherText, probableKeyLength);
 string key = determineKey(groups);
 cout << "\nEstimated Key: " << key << endl;
 return 0;
}
