#include "trie.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
void PrintTrie(struct TrieNode* root){

	TrieNode* curr = root;
		for(int i = 0; i < ALPHABET_SIZE; i++){
			if(root->children[i]){std::cout << char(i + int('a')) << " ";}
		}
		std::cout << std::endl;

}
Trie::Trie()
{
	root = NULL;
}

// Returns new trie node (initialized to NULLs)
struct TrieNode* Trie::getNode(void)
{
	TrieNode* new_node = new TrieNode;

	for(int i = 0; i < ALPHABET_SIZE; i++){
		new_node->children[i] = NULL;
	}
	

	return new_node; 

}

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void Trie::insert(struct TrieNode* root, const std::string key)
{
	// std::cout << key << std::endl;
	TrieNode* curr = root;
	int i = 0;
	int n = key.size();
	while(curr != NULL && i < n){
		// std::cout << i <<":"; PrintTrie(curr);
		if(curr->children[key[i] - 'a']){
			// std::cout << key[i] << " ";
			curr = curr->children[key[i] - 'a'];
			i++;
			if(i == n && curr->noWordEnd){
				curr->noWordEnd++;
				return;
			} 
		}
		else{
			break;
		}
	}
	// std::cout << std::endl;
	// std::cout << key << ":"<<i << std::endl;
	for(int j = i; j < n; j++){
		curr->children[key[j] - 'a'] = getNode();
		curr = curr->children[key[j] - 'a'];		
	}
	curr->noWordEnd++;
	// std::cout << std::endl;
	return;
}

bool Trie::search(struct TrieNode *root, std::string key)
{
	int i = 0; 
	int n = key.size();

	TrieNode* curr = root;
	while(curr != NULL && i < n){
		if(curr->children[key[i] - 'a']){
			curr = curr->children[key[i] - 'a'];
			i++;
			if(i == n && (curr->noWordEnd != 0)){return true;}
		}
		else{
			break;
		}
	}
	return false;
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool Trie::isLastNode(struct TrieNode* root)
{
	for(int i = 0; i < ALPHABET_SIZE; i++){
		if(root->children[i]) return false;
	}
	return true;
}


// Recursive function to print auto-suggestions for given
// node.
std::pair<int,std::vector<std::string>> Trie::suggestionsRec(struct TrieNode* root,
					std::string currPrefix)
{	
	int score = 0;
	std::vector<std::string> temp;
	std::pair<int,std::vector<std::string>> curr;
	if(root && (root->noWordEnd > 0)){
		score = root->noWordEnd;
		temp.push_back(currPrefix);
		// curr = std::make_pair(score,temp);
	}
	if(!isLastNode(root)){
		// std::cout << "HI" << std::endl;
		for(int i = 0; i < ALPHABET_SIZE; i++){
			if(root->children[i]){
				// std::cout << char(i + 'a') << " ";
				curr = suggestionsRec(root->children[i],currPrefix + char(i + int('a')));
				if(curr.first > score){
					score = curr.first;
					temp = curr.second;
				}
				else if(curr.first == score){
					std::vector<std::string> merged(temp.size() + curr.second.size());
					// std::cout << "dis" << std::endl;
					std::merge(temp.begin(),temp.end(),curr.second.begin(),curr.second.end(),merged.begin());
					// std::cout << "no" << std::endl;
					temp = merged;
				}
			}
			// std::cout << std::endl;
		}
	}

	return std::make_pair(score,temp);
	


}

// print suggestions for given query prefix.
int Trie::printAutoSuggestions(TrieNode* root, const std::string query)
{
	int i(0), n(query.size());

	std::stringstream ss(query);
	std::string prev,cur,temp;
	ss>>prev;
	while(ss >> cur){temp = prev;prev = cur;}
	prev = temp;
	
	std::string new_query = std::string(prev + "{" + cur.substr(0,cur.size()-1));
	// std::cout << new_query << std::endl;
	n = new_query.size();
	// std::cout << "HI" << n << std::endl;
	TrieNode* curr = root;
	while(curr != NULL && i < n){
		// std::cout << "HI" << curr << i << std::endl;
		if(curr->children[new_query[i] - 'a']){
			curr = curr->children[new_query[i] - 'a'];
			i++;
		}
		else{
			if(i < n) return 0;
		}

		if(i == n && curr == NULL){
			if(curr->noWordEnd > 0){return -1;}
			else return 0;
		}
	}
	// std::cout << search(curr,"lo") << std::endl;
	// std::cout << i <<":" <<query << std::endl;
	std::cout << "HI" << std::endl;
	std::pair<int,std::vector<std::string>> temp_pr = suggestionsRec(curr,new_query);
	std::cout << "HI" << std::endl;
	if(temp_pr.first == 0) return 0;
	for(int i = 0; i < temp_pr.second.size(); i++){
		for(int j = 0; j < temp_pr.second[i].size();j++){
		if(temp_pr.second[i][j] == '{') std::cout << temp_pr.second[i].substr(j+1) << std::endl;
		}
	}
	// std::cout << temp_pr.second << std::endl;
	return 1;
}

// Process the file "lorem.txt" to insert the words in lorem.txt and store the relevant context as needed.
void Trie::processContext()
{
	std::ifstream lorem("lorem.txt");
	std::string curr;
	std::string prev;
	std::string temp;
	lorem >> prev;
	while(lorem >> curr ){

		// std::cout << prev <<"{"<<curr << std::endl;
		temp = prev + "{" + curr;
		prev = curr;
		insert(root,temp);
	}
	// std::cout << search(root,"boi{hi");

}
