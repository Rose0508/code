#include "common.h"
void find_left_individual(int i, long long front, long long tail, long long sum, struct node* head) {
	long long min = front;
	long long max = min + sum - 1;
	struct node* p = head;
	struct node* q = p->next;
	struct node* q1 = NULL;
	int flag = 0;
	while (max <= tail) {//在这一层寻找
		while (p->next != NULL) {
			if (p->next->number >= min && p->next->number <= max) {//查找编号，看是否存在对应结点，查找到了就跳出循环，p->next是第一个对应编号的结点
				flag = 1;
				break;
			}
			if (p->next->number > max) {//没有查找到，p->next是新的结点
				flag = 0;
				break;
			}
			p = p->next;
		}
		if (flag == 1) {//查找到了
			flag = 0;
			while (p->next != NULL && p->next->number <= max) {//max为最大结点编号
				long long m = p->next->number + sum;//此为对应最大结点编号
				int flag1 = 0;
				while (q->next != NULL) {//从当前项的下一项向后遍历，直到遍历到比m大的项，如果找到与m相等的项则代表有重复的项需要删除，没有找到与m相等的项则需要添加
					if (q->next->number == m) {//代表取反之后产生重复项，需要删除此项
						struct node* q1 = q->next;
						q->next = q1->next;//删除，q->next为新节点
						if (q1->next != NULL) {
							q1->next->front = q;
						}
						free(q1);
						q1 = NULL;
						flag1 = 1;
						break;
					}
					if (q->next->number > m) {//此时代表没有找到，需要添加项
						struct node* q1 = (struct node*)malloc(sizeof(struct node));
						q1->number = m;
						q1->next = q->next;
						q->next->front = q1;
						q->next = q1;//插入新项
						q1->front = q;
						q = q->next;//要记录q的位置，保证在验证的时候q->next是一个新的点，执行之后q->next依旧为新节点
						flag1 = 1;
						break;
					}
					q = q->next;
				}
				if (flag1 == 0) {
					struct node* q1 = (struct node*)malloc(sizeof(struct node));
					q1->number = m;
					q1->next = NULL;
					q->next = q1;
					q1->front = q;
					q = q->next;
				}
				if (p == NULL || p->next == NULL) {
					break;
				}
				if (p->next->next != NULL) {//p->next已经讨论完成，判断p->next->next是否存在
					p = p->next;
				}
				else {
					break;
				}
			}
		}
		min = min + sum * 2;
		max = min + sum - 1;
	}
}
void find_right_individual(int i, long long front, long long tail, long long sum, struct node* head) {//记得改为减，向前查找
	//cout << "执行" << endl;
	long long min = front + sum;
	long long max = min + sum - 1;
	struct node* p = head;
	struct node* q = NULL;
	struct node* q1 = NULL;
	int flag = 0;
	while (max <= tail) {
		while (p->next != NULL) {
			//cout << 2 ;
			if (p->next->number >= min && p->next->number <= max) {//查找编号，看是否存在对应结点，查找到了就跳出循环，p->next是第一个对应编号的结点
				flag = 1;
				break;
			}
			if (p->next->number > max) {//没有查找到，p->next是新的结点
				flag = 0;
				break;
			}
			p = p->next;
		}
		if (flag == 1) {//查找到了
			//q = p->next;//这地方没错
			flag = 0;
			while (p->next != NULL && p->next->number <= max) {//max为最大结点编号
				//cout << 3 ;
				//cout <<"bb"<< p->next->number << endl;
				q = p->next;//这地方没错
				long long m = p->next->number - sum;//此为对应结点编号
				int flag1 = 0;
				while (q != head && q->front != head) {//从当前项的下一项向后遍历，直到遍历到比m大的项，如果找到与m相等的项则代表有重复的项需要删除，没有找到与m相等的项则需要添加
					//cout << "kk" << q->front->number << endl;
					if (q != NULL && q->front != head && (q->front->number) == m) {//代表取反之后产生重复项，需要删除此项
						//cout << p->next->number << "找到了" << q->front->number << endl;
						struct node* q1 = q->front;
						if (q1 == p) {
							p = p->front;
							q->front = q1->front;//删除，q->front为新节点
							q1->front->next = q;
							free(q1);
							q1 = NULL;
							flag1 = 1;
							//p = p->next;
						}
						else {
							q->front = q1->front;//删除，q->front为新节点
							q1->front->next = q;
							free(q1);
							q1 = NULL;
							flag1 = 1;
						}
						break;
					}
					if (q->front->number < m) {//此时代表没有找到，需要添加项
						struct node* q1 = (struct node*)malloc(sizeof(struct node));
						q1->number = m;
						//cout << p->next->number << "添加了" << q1->number << endl;
						q1->next = q;
						q->front->next = q1;
						q1->front = q->front;
						q->front = q1;
						q = q->front;//要记录q的位置，保证在验证的时候q->front是一个新的点，执行之后q->next依旧为新节点
						if (q1->front == p) {
							p = p->next;
						}
						flag1 = 1;
						break;
					}
					q = q->front;
				}
				if (flag1 == 0) {
					/*cout << "kk" << endl;
					if (q->front == head) {
						cout << "bbbbbb" << endl;
					}*/
					struct node* q1 = (struct node*)malloc(sizeof(struct node));
					q1->number = m;
					q1->next = q;
					q->front = q1;
					q1->front = head;
					head->next = q1;
					//q = q->front;
					if (p == head) {
						p = p->next;
					}
					//cout << head->next->number <<endl;
				}
				if (p == NULL || p->next == NULL) {
					break;
				}
				if (p->next->next != NULL) {//p->next已经讨论完成，判断p->next->next是否存在
					p = p->next;
				}
				else {
					break;
				}
			}
		}
		min = min + sum * 2;
		max = min + sum - 1;
	}
	/*cout << "打印mmmm" << endl;
	p = head;
	cout << "sum" << sum << endl;
	while (p->next != NULL) {
		if (p->next->number < 0) {
			p->next->number = (p->next->number) * (-1);
		}
		cout << p->next->number << " ";
		p = p->next;
	}
	cout << "ok" << endl;*/

}
void find_change_individual(int i, long long front, long long tail, long long sum, struct node* head) {
	//当极性为1时进行取反操作
	struct node* p = head;
	long long min = front;
	long long middle = min + sum - 1;
	long long max = min + sum * 2 - 1;
	long long m;
	struct node* q2 = NULL;
	struct node* q3 = NULL;
	while (p->next != NULL) {
		//cout << 4;
		//cout <<"gg"<< p->next->number<<endl;
		int flag2 = 0;
		//cout << 1;
		if (p->next->number > 0) {
			//cout << 2;
			//cout <<"ok"<<" "<< p->next->number << " " << min <<" "<<middle<< " " << max;
			if (p->next->number >= min && p->next->number <= max) {//此处可优化
				//cout << 3;
				if (p->next->number >= min && p->next->number <= middle) {
					//cout << 4;
					m = p->next->number + sum;
					q2 = p->next;
					int flag1 = 0;
					while (q2->next != NULL) {
						//cout << "aaa" << q2->next->number << endl;
						if (q2->next->number == m) {//有对应点，无需操作
							flag1 = 1;
							//cout << p->next->number<< "找到了" <<q2->next->number<< endl;
							break;
						}
						else if (q2->next->number > 0 && q2->next->number > m) {//无对应点，需要删除此点，添加对应点，并在对应点上做标记
							struct node* q4 = (struct node*)malloc(sizeof(struct node));
							q4->number = m * (-1);
							//cout << "添加了" << q4->number << endl;
							q2->next->front = q4;
							q4->next = q2->next;
							q2->next = q4;
							q4->front = q2;
							flag1 = 1;
							struct node* q5 = p->next;//删除此点
							flag2 = 1;
							p->next = q5->next;
							q5->next->front = p;
							free(q5);
							break;
						}
						else if (q2->next->number < 0 && ((q2->next->number) * (-1)) > m) {//无对应点，需要删除此点，添加对应点，并在对应点上做标记
							struct node* q4 = (struct node*)malloc(sizeof(struct node));
							q4->number = m * (-1);
							//cout << "添加了" << q4->number << endl;
							q2->next->front = q4;
							q4->next = q2->next;
							q2->next = q4;
							q4->front = q2;
							flag1 = 1;
							struct node* q5 = p->next;//删除此点
							flag2 = 1;
							p->next = q5->next;
							q5->next->front = p;
							free(q5);
							break;
						}
						q2 = q2->next;
					}
					if (flag1 == 0) {
						struct node* q4 = (struct node*)malloc(sizeof(struct node));
						q4->number = m * (-1);
						q2->next = q4;
						q4->front = q2;
						q4->next = NULL;
						struct node* q5 = p->next;//删除此点
						flag2 = 1;
						p->next = q5->next;
						q5->next->front = p;
						free(q5);
					}
				}
				else if (p->next->number > middle && p->next->number <= max) {
					//cout << 5;
					m = p->next->number - sum;
					q3 = p->next;
					int flag1 = 0;
					while (q3->front != head) {
						//cout <<m<< "ddd" << q3->front->number << endl;
						if (q3->front->number == m) {//有对应点，无需操作
							flag1 = 1;
							//cout << p->next->number<< "找到了" << q3->front->number << endl;
							break;
						}
						else if (q3->front->number > 0 && q3->front->number < m) {//无对应点，需要删除此点，添加对应点，并在对应点上做标记
							//cout << p->next->number << endl;
							struct node* q4 = (struct node*)malloc(sizeof(struct node));
							q4->number = m * (-1);
							q3->front->next = q4;
							q4->front = q3->front;
							q4->next = q3;
							q3->front = q4;
							flag1 = 1;
							if (q4->front == p) {
								p = p->next;
							}
							struct node* q5 = p->next;//删除此点
							flag2 = 1;
							if (q5->next != NULL) {
								p->next = q5->next;
								q5->next->front = p;
							}
							else {
								p->next = NULL;
								//cout << "gggg" << endl;
							}
							free(q5);
							break;
						}
						else if (q3->front->number < 0 && (q3->front->number) * (-1) < m) {//无对应点，需要删除此点，添加对应点，并在对应点上做标记
							struct node* q4 = (struct node*)malloc(sizeof(struct node));
							q4->number = m * (-1);
							q3->front->next = q4;
							q4->front = q3->front;
							q4->next = q3;
							q3->front = q4;
							flag1 = 1;
							if (q4->front == p) {
								p = p->next;
							}
							struct node* q5 = p->next;//删除此点
							flag2 = 1;
							if (q5->next != NULL) {
								p->next = q5->next;
								q5->next->front = p;
							}
							else {
								p->next = NULL;
								//cout << "gggg" << endl;
							}
							free(q5);
							break;
						}
						q3 = q3->front;
					}
					if (flag1 == 0) {
						struct node* q4 = (struct node*)malloc(sizeof(struct node));
						q4->number = m * (-1);
						q3->front = q4;
						q4->next = q3;
						head->next = q4;
						q4->front = head;
						if (q4->front == p) {
							p = p->next;
						}
						struct node* q5 = p->next;//删除此点
						flag2 = 1;
						if (q5->next != NULL) {
							p->next = q5->next;
							q5->next->front = p;
						}
						else {
							p->next = NULL;
							//cout << "gggg" << endl;
						}
						free(q5);
					}
					else {
						flag1 = 0;
					}
				}

			}
			else if (p->next->number > max) {
				// cout << "mmmm" << p->next->number << endl;
				min = min + sum * 2;
				max = max + sum * 2;
				middle = middle + sum * 2;
				flag2 = 1;
			}
		}
		//cout << "kk" << max << " " << p->number;
		if (flag2 == 0) {
			p = p->next;
		}
		else {
			flag2 = 0;
		}
	}
	//cout << "打印" << endl;
	p = head;
	while (p->next != NULL) {
		if (p->next->number < 0) {
			p->next->number = (p->next->number) * (-1);
		}
		//cout << p->next->number << " ";
		p = p->next;

	}
	//cout << "\n";
}
void  polarity_conversion(int q1[], int q2[], struct node* head, int input){//q1是当前极性，q2是目标极性
	long long front = pow(2, input);
	long long tail = pow(2, input + 1) - 1;
	for (int j = 1; j <= input; j++) {
		//cout << j << endl;
		//cout << "前" << endl;
		//print_list(head);
		if (j < input) {
			int n = input - j;
			long long sum = pow(2, n);
			if ((q1[j] == 0 && q2[j] == 2) || (q1[j] == 2 && q2[j] == 0) || (q1[j] == 1 && q2[j] == 2)) {
				find_left_individual(j, front, tail, sum, head);
			}
			else if ((q1[j] == 0 && q2[j] == 1) || (q1[j] == 1 && q2[j] == 0) || (q1[j] == 2 && q2[j] == 1)) {
				find_right_individual(j, front, tail, sum, head);
			}
			if ((q1[j] == 1 && q2[j] == 2) || (q1[j] == 2 && q2[j] == 1)) {
				//cout << "执行change前" << endl;
				//print_list(head);
				find_change_individual(j, front, tail, sum, head);
				//cout << "执行change后" << endl;
				//print_list(head);
			}
		}
		else {
			if ((q1[j] == 0 && q2[j] == 2) || (q1[j] == 2 && q2[j] == 0) || (q1[j] == 1 && q2[j] == 2)) {
				struct node* p = head;
				while (p != NULL && p->next != NULL) {
					if ((p->next->number) % 2 == 0) {//找到了满足条件需要取反的结点
						if (p->next->next != NULL) {
							if (p->next->next->number == (p->next->number) + 1) {//说明转换后有重复结点需要删除
								struct node* p1 = p->next->next;
								p->next->next = p1->next;
								if (p1->next != NULL) {
									p1->next->front = p->next;
								}
								free(p1);
								p = p->next;//保证p->next为新结点
							}
							else {//说明转换后无重复结点,需要添加结点
								struct node* p1 = p->next->next;
								struct node* p2 = (struct node*)malloc(sizeof(struct node));
								p2->number = (p->next->number) + 1;
								p2->next = NULL;
								p2->next = p1;
								p1->front = p2;
								p->next->next = p2;
								p2->front = p->next;
								p = p->next->next;//保证p->next为新结点
							}
						}
						else {
							struct node* p3 = (struct node*)malloc(sizeof(struct node));
							p3->number = (p->next->number) + 1;
							p3->next = NULL;
							p->next->next = p3;
							p3->front = p->next;
							p = p->next->next;
						}
					}
					else {
						p = p->next;
					}
				}
			}
			else if ((q1[j] == 0 && q2[j] == 1) || (q1[j] == 1 && q2[j] == 0) || (q1[j] == 2 && q2[j] == 1)) {
				struct node* p = head;
				while (p != NULL && p->next != NULL) {
					//cout << p->next->number << endl;
					if ((p->next->number) % 2 != 0) {
						if (p != head) {
							if (p->number == (p->next->number) - 1) {//证明转换后有重复结点 需删除p
								//cout << p->next->number << "删除了" << p->number << endl;
								struct node* p1 = p;
								p = p->front;
								p1->next->front = p;
								p->next = p1->next;//p->next为新结点
								p = p->next;
								free(p1);
							}
							else {//说明转换后无重复结点，需要添加
								struct node* p1 = (struct node*)malloc(sizeof(struct node));
								p1->number = p->next->number - 1;
								//cout << p->next->number << "添加了" << p1->number << endl;
								p->next->front = p1;
								p1->next = p->next;
								p->next = p1;
								p1->front = p;
								p = p->next->next;//保证p->next为新结点
							}
						}
						else {
							struct node* p1 = (struct node*)malloc(sizeof(struct node));
							p1->number = p->next->number - 1;
							//cout << p->next->number << "添加了" << p1->number << endl;
							p->next->front = p1;
							p1->next = p->next;
							p->next = p1;
							p1->front = p;
							p = p->next->next;//保证p->next为新结点
						}
					}
					else {
						p = p->next;
					}
				}
			}
			if ((q1[j] == 1 && q2[j] == 2) || (q1[j] == 2 && q2[j] == 1)) {
				struct node* p = head;
				while (p != NULL && p->next != NULL) {
					if ((p->next->number) % 2 == 0) {
						if (p->next->next != NULL) {
							if (p->next->next->number == p->next->number + 1) {//代表取反后有重复结点，无需操作
								p = p->next->next;//保证p->next是一个新结点
							}
							else {//如果没有则需要添加结点，并删除此结点;
								p->next->number = p->next->number + 1;
								p = p->next;//保证p->next是一个新结点,并且不需要标记
							}
						}
						else {
							p->next->number = p->next->number + 1;
							p = p->next;//保证p->next是一个新结点,并且不需要标记
						}
					}
					else {
						if (p != head) {
							if (p->number == p->next->number - 1) {//代表取反后有重复结点，无需操作
								p = p->next;//保证p->next是一个新结点
							}
							else {//如果没有则需要添加结点，并删除此结点;
								p->next->number = p->next->number - 1;
								p = p->next;//保证p->next是一个新结点,并且不需要标记
							}
						}
						else {//需要添加结点，并删除此结点
							p->next->number = p->next->number - 1;
							p = p->next;//保证p->next是一个新结点,并且不需要标记
						}
					}
				}
			}

		}
		//cout << "后" << endl;
		//print_list(head);
	}
}