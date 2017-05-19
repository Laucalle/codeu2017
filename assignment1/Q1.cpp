#include <vector>
#include <string>
#include <cctype> // toupper function

// when both strings are empty, they are considered permutations
bool is_permutation(const std::string& str1, const std::string& str2){
	bool is_permutation = false;
	
	if(str1.size()==str2.size()){
		
		std::vector<bool> check(str1.size(),true); // check this initialization
		bool found = false;
		is_permutation = true;

		for(int i = 0; i<str1.size() && is_permutation; i++) {
			found = false;
			
			for(int j=0; !found && j<str2.size(); j++) {
				if(check[j] && toupper(str1[i])==toupper(str2[j])) {
					found = true;
					check[j] = false;
				}
				
			}
			is_permutation = found;
		}
	} 

	return is_permutation;
}
