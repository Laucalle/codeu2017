#include <iostream>
#include <math.h>
#include <vector>

class IslandCounter {
	std::vector< std::vector<bool> >  map;
	void collapse_island ( int i, int j) {
		if (!map[i][j]) return;

		map[i][j] = false;
		int end_row = std::min(i+1, (int) (map.size()-1));
		int init_row = std::max(i-1, 0);
		int end_col = std::min(j+1,(int) (map[i].size()-1));
		int init_col = std::max(j-1,0);

		for(int row = init_row; row <= end_row; row++) {
			for(int col = init_col; col <= end_col; col++) {
				if ((col == j || row == i) && !(col==j && row==i)) {
					collapse_island (row, col);
				}
			}
		}
		return;
	}
public:
	void SetMap(const std::vector< std::vector<bool> > &island_map){
		map=island_map;
	}
	int Count () {
		int island_counter = 0;
		
		if(!map.empty()){
			for( int i = 0; i < map.size(); i++) {
				for (int j = 0; j < map[i].size(); j++) {
					if (map[i][j]) {
						island_counter++;
						collapse_island (i, j);
					}
				}
			}
		}
		return island_counter;
	}
};

int main(){
	std::vector< std::vector<bool> > map{{0,0,0,0,1,1,1,0,1,0},
										 {0,0,0,0,1,0,0,0,1,0},
										 {0,0,1,1,1,1,1,0,1,1},
										 {0,0,1,0,0,0,0,0,1,0},
										 {0,0,1,0,1,0,0,0,0,0},
										 {0,0,0,0,1,0,1,0,1,0},
										 {0,1,0,0,1,0,1,0,1,0},
										 {1,1,0,0,1,1,1,0,0,0},
										 {0,1,0,1,1,0,1,0,1,0},
										 {0,0,0,0,1,0,1,0,1,0}};


	for(int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if(map[i][j]) std::cout << "x";
			else std::cout << " "; 
		}
		std::cout << std::endl;
	}
	IslandCounter ic;
	ic.SetMap(map);
	std::cout << ic.Count() << std::endl;
}
