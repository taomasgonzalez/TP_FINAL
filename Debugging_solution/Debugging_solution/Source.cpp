#include <vector>
using namespace std;

int main(void) {


	vector<vector<int *>*> vector_de_vector_de_ints = vector<vector<int *>*>();
	vector_de_vector_de_ints.reserve(4);
	vector<vector<int *>*>::iterator it = vector_de_vector_de_ints.begin();
	vector<int *> al = vector<int*>();
	printf("%d\n", *(new int(1)));
	al.push_back(new int(1));
	al.push_back(new int(2));
	vector_de_vector_de_ints.insert(it, &al);

	printf("%d", *((vector_de_vector_de_ints[0])->at(0)));

	getchar();
	return 0;
}