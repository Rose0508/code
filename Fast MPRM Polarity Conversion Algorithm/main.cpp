#include"common.h"
int input = 0, output = 0;
long long num = 0;
int summ = 0;
char** a;
int rows = 1000;
int cols = 50;
void put_polarity_helper(struct individual* head, int path[], int len) {
	if (!head) {
		return;
	}
	if (head->number % 2 == 0) {
		path[len] = 0;
		len++;
	}
	else {
		path[len] = 1;
		len++;
	}
	if (head->leftflag == 0 && head->rightflag == 0) {
		for (int i = 0; i < len; i++) {
			printf("%d", path[i]);
		}
		summ++;
		printf("\n");
	}
	else {
		put_polarity_helper(head->left, path, len);
		put_polarity_helper(head->right, path, len);
	}
}
void put_polarity(struct individual* head) {
	int path[1000];
	put_polarity_helper(head, path, 0);
}
void bubbleSort(int arr[], int n) {
	int i, j;
	for (i = 1; i <= n - 1; i++) {                 
		for (j = 1; j <= n - i; j++) {             
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
void free_individual_node(struct individual_node* head) {
	struct individual_node* p = head;
	struct individual_node* p1;
	while (p != NULL) {
		p1 = p->next;
		free(p);
		p = p1;
	}
}
void printArray(int arr[], int size) {
	int i;
	for (i = 1; i <= size; i++) {               
		printf("%d ", arr[i]);
	}
	printf("\n");
}
void print_list(struct node* head) {
	struct node* p = head->next;
	while (p != NULL) {
		p = p->next;
	}
}
void count_New_nodes(struct node* head) {
	struct node* p = head->next;
	int sum2 = 0;
	while (p != NULL) {
		sum2++;
		p = p->next;
	}
}
void clear_New_node_List(struct node* head) {
	struct node* current = head;
	struct node* next;

	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}

	head = NULL;
}
int main() {
	a = (char**)malloc(rows * sizeof(char*));
	for (int i = 0; i < rows; i++) {
		a[i] = (char*)malloc(cols * sizeof(char));
	}
	int iLineIndex = 0;
	const int MAX_LINE_LEN = 512;
	static char szLineData[MAX_LINE_LEN];
	int count = 0;
	ifstream infile;
	string path;
	cout << "Please enter the file path of the circuit (the circuit file should be in .txt format): ";
	cin >> path;
	infile.open(path);
	if (!infile) {
		cout << "Please check if the file path or file format is correct." << endl;
		return 0;
	}
	while (!infile.eof())
	{
		infile.getline(szLineData, MAX_LINE_LEN);
		++iLineIndex;
		if (iLineIndex == 1) {
			int i = 3;
			while (szLineData[i] != '\0') {
				input = input * 10;
				input = input + int(szLineData[i]) - 48;
				i++;
			}
		}
		else if (iLineIndex == 2) {
			int i = 3;
			while (szLineData[i] != '\0') {
				output = output * 10;
				output = output + int(szLineData[i]) - 48;
				i++;
			}

		}
		else if (iLineIndex == 5) {
			int i = 3;
			while (szLineData[i] != '\0') {
				num = num * 10;
				num = num + int(szLineData[i]) - 48;
				i++;
			}
			num = num + 5;
		}
		else if (iLineIndex > 5 && iLineIndex < num + 1) {
			if (int(szLineData[input + 1]) - 48 == 1) {
				for (int j = 0; j < input; j++) {
					a[count][j] = szLineData[j];
				}
				count++;
			}
		}

	}
	infile.close();
	int popsize;
	int	G;
	int polarity[100];
	for (int i = 1; i <= input; i++) {
		polarity[i] = 2;
	}
	cout << "Start executing MPCA" << endl;
	popsize;
	cout << "Please enter the number of polarity conversions (100 or 1000): ";
	cin >> popsize;
	cout << "\n";
	struct individual_node* head0 = generate_initial_population(input, popsize);
	cout << "Randomly generate "<< popsize <<" polarities for polarity conversion testing." << endl;
	cout << "Perform 10 repeated experiments on this test and calculate the time required for each experiment:" << endl;
	for (int r = 1; r <= 10; r++) {
		struct node* New_head = (struct node*)malloc(sizeof(struct node));
		New_head->front = NULL;
		New_head->next = NULL;
		New_head->number = 1;
		compression_encoding(a, New_head, input, count);
		double duration_New;
		clock_t start_New, finish_New;
		struct individual_node* New_p = head0;
		start_New = clock();
		while (New_p->next != NULL) {
			if (New_p == head0) {
				polarity_conversion(polarity, New_p->next->polarity, New_head, input);
			}
			else {
				polarity_conversion(New_p->polarity, New_p->next->polarity, New_head, input);
			}
			New_p = New_p->next;
		}
		finish_New = clock();
		duration_New = (double)(finish_New - start_New) / CLOCKS_PER_SEC;
		cout << "The runtime of MPCA for the "<<r<<" experiment is : " << duration_New << endl;
		clear_New_node_List(New_head);
	}
	cout << "Since the polarity used for each experiment is randomly generated, the results may have some bias." << endl;
	free_individual_node(head0);
	return 0;
}