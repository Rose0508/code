#include "common.h"
void compression_encoding(char** a, struct node* head, int input, int count) {
	struct node* p = head;
	queue<long long>que;
	for (int i = 0; i < count; i++) {
		if (!que.empty()) {
			cout << "╤сап╥г©у" << endl;
		}
		long long k = 1;
		if (a[i][0] == '0') {
			que.push(k * 2);
		}
		else if (a[i][0] == '1') {
			que.push(k * 2 + 1);
		}
		else if (a[i][0] == '-') {
			que.push(k * 2);
			que.push(k * 2 + 1);
		}
		for (int j = 1; j < input; j++) {
			int m = 1;
			int sum = que.size();
			while (m <= sum) {
				long long n = que.front();
				if (a[i][j] == '0') {
					que.push(n * 2);
				}
				else if (a[i][j] == '1') {
					que.push(n * 2 + 1);
				}
				else if (a[i][j] == '-') {
					que.push(n * 2);
					que.push(n * 2 + 1);
				}
				que.pop();
				m++;
			}
		}
		p = head;
		while (!que.empty()) {
			long long n1 = que.front();
			long long n = n1;
			int flag = 0;
			while (p->next != NULL) {
				if (p->next->number == n) {
					flag = 1;
					p = p->next;
					break;
				}
				else if (p->next->number > n) {
					struct node* p3 = (struct node*)malloc(sizeof(struct node));
					p3->front = p;
					p3->next = p->next;
					p3->number = n;
					p->next->front = p3;
					p->next = p3;
					flag = 1;
					p = p->next;
					break;
				}
				p = p->next;
			}
			if (flag == 0) {
				struct node* p3 = (struct node*)malloc(sizeof(struct node));
				p3->front = p;
				p3->next = NULL;
				p3->number = n;
				p->next = p3;
				p = p->next;
			}
			que.pop();
		}
	}
}