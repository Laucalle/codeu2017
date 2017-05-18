
// data structure to build single linked lists. Last element's next
// next pointer should be NULL
template <typename T>
struct cell{
	T data;
	cell *next;
};

// precondition: init is a single linked list, NULL terminated
// If k is greater than the size of the list, a NULL pointer is 
// returned, indicating that kth element to last does not exist
// If k is negative (invalid input), a NULL pointer is returned
template <typename T>
cell<T>* kToLast(cell<T>* init, int k){

	cell<T>* advanced, *out;
	advanced = init;
	for(int i=0; i<=k && advanced!=NULL; i++){
		advanced = advanced->next;
	}
	if(advanced==NULL) return advanced;
	out = init;
	while( advanced != NULL){
		advanced = advanced->next;
		out = out->next;
	}
	return out;
}
