
// data structure to build single linked lists. Last element's next
// next pointer should be NULL
template <typename T>
struct cell{
	T data;
	cell *next;
};

// precondition: init is a single linked list, NULL terminated
// If k is greater or equal to the size of the list, a NULL 
// pointer is returned, indicating that kth element to last 
// does not exist
// If k is negative (invalid input), a NULL pointer is returned
template <typename T>
cell<T>* kToLast(cell<T>* init, int k){

	cell<T>* advanced, *kth;
	advanced = init;
	int i;
	for(i=0; i<=k && advanced!=NULL; i++){
		advanced = advanced->next;
	}
	if(advanced == NULL && i-1 == k) return init;
	else if(advanced==NULL) return advanced;
	kth = init;
	while( advanced != NULL){
		advanced = advanced->next;
		kth = kth->next;
	}
	return kth;
}
