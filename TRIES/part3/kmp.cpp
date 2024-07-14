#include <iostream>
#include <cstring>

// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps)
{
	int i = 1; int j =0;
	lps[0] = -1;

	while(i < M){
		if(pat[i] == pat[j]){
			lps[i] = lps[j];
		}
		else{
			lps[i] = j;
			while(j > 0 && pat[i] != pat[j]){
				j = lps[j];
			}
		}
		i++;j++;
	}
	lps[M] = j;
}

// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt)
{
	// printf("Found pattern at index %d \n", index_where_found);
	int i = 0; int j = 0;
	int* lps = new int[strlen(pat)+1];
	computeLPSArray(pat,strlen(pat)+1,lps);
	int n = strlen(txt);

	while(i < n){
		if(pat[j] == txt[i]){
			i++;j++;
			if(j == strlen(pat)){
				printf("Found pattern at index %d \n", int(i - strlen(pat)));
				j = lps[strlen(pat)];
			}
		}
		else{
			j = lps[j];
			if(j < 0){
			i++;
			j =0;
		}
		}
		
	}
	
}
