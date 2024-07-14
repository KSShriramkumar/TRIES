#include "trie.h"
#include <iostream>
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
	new_node->isWordEnd = false;

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
			if(i == n && curr->isWordEnd) return;
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
	curr->isWordEnd = true;
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
			if(i == n && curr->isWordEnd) return true;
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
void Trie::suggestionsRec(struct TrieNode* root,
					std::string currPrefix)
{	
	if(root && root->isWordEnd){std::cout << currPrefix << std::endl;}
	if(!isLastNode(root)){
		for(int i = 0; i < ALPHABET_SIZE; i++){
			if(root->children[i]){
				// std::cout << char(i + 'a') << " ";
				suggestionsRec(root->children[i],currPrefix + char(i + int('a')));
			}
			// std::cout << std::endl;
		}
	}
	


}

// print suggestions for given query prefix.
int Trie::printAutoSuggestions(TrieNode* root, const std::string query)
{
	int i(0), n(query.size());
	TrieNode* curr = root;
	while(curr != NULL && i < n){
		if(curr->children[query[i] - 'a']){
			curr = curr->children[query[i] - 'a'];
			i++;
		}
		else{
			if(i < n-1) return 0;
		}
		if(i == n && curr == NULL){
			if(curr->isWordEnd){return -1;}
			else return 0;
		}
	}
	// std::cout << search(curr,"lo") << std::endl;
	// std::cout << i <<":" <<query << std::endl;
	suggestionsRec(curr,query);
	return 1;
}
