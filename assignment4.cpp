#include <iostream>
#include <math.h>
#include <vector>

class IslandCounter{
	void collapse_island(std::vector< std::vector<bool> > &map, int i, int j){
		if(!map[i][j]) return;

		map[i][j] = false;
		collapse_island( map, std::min(i+1, (int) (map.size()-1)), j);
		collapse_island( map, std::max(i-1, 0), j);
		collapse_island( map, i, std::min(j+1,(int) (map[i].size()-1)));
		collapse_island( map, i, std::max(j-1,0));
		
		return;
	}
public:
	int Count(std::vector< std::vector<bool> > map){
		int island_counter = 0;
		for( int i=0; i<map.size(); i++) {
			for (int j = 0; j < map[i].size(); j++) {
				if( map[i][j]){
					island_counter++;
					collapse_island( map, i, j);
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


	for(int i=0; i<map.size(); i++){
		for (int j = 0; j<map[i].size(); j++){
			if(map[i][j]) std::cout << "x";
			else std::cout << " "; 
		}
		std::cout << std::endl;
	}
	IslandCounter ic;
	std::cout << ic.Count(map) << std::endl;
}