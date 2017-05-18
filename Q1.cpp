#include <vector>
#include <string>

// when both strings are empty, they are considered permutations
bool is_permutation(const std::string& str1, const std::string& str2){
	bool out = false;
	
	if(str1.size()==str2.size()){
		
		std::vector<bool> check(str1.size(),true); // check this initialization
		bool found = false;
		int j = 0;
		out = true;

		for(int i = 0; i<str1.size() && out; i++) {
			found = false;
			j = 0;
			
			while(!found && j<str2.size()) {
				if(check[j]) {
					found = str1[i]==str2[j];
					check[j] = !found;
				}
				j++;
			}
			out = found;
		}
	} 

	return out;
}
