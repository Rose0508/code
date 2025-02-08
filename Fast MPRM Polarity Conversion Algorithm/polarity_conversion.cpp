#include "common.h"
void find_left_individual(int i, long long front, long long tail, long long sum, struct node* head) {
	long long min = front;
	long long max = min + sum - 1;
	struct node* p = head;
	struct node* q = p->next;
	struct node* q1 = NULL;
	int flag = 0;
	while (max <= tail) {//����һ��Ѱ��
		while (p->next != NULL) {
			if (p->next->number >= min && p->next->number <= max) {//���ұ�ţ����Ƿ���ڶ�Ӧ��㣬���ҵ��˾�����ѭ����p->next�ǵ�һ����Ӧ��ŵĽ��
				flag = 1;
				break;
			}
			if (p->next->number > max) {//û�в��ҵ���p->next���µĽ��
				flag = 0;
				break;
			}
			p = p->next;
		}
		if (flag == 1) {//���ҵ���
			flag = 0;
			while (p->next != NULL && p->next->number <= max) {//maxΪ�������
				long long m = p->next->number + sum;//��Ϊ��Ӧ�������
				int flag1 = 0;
				while (q->next != NULL) {//�ӵ�ǰ�����һ����������ֱ����������m��������ҵ���m��ȵ�����������ظ�������Ҫɾ����û���ҵ���m��ȵ�������Ҫ���
					if (q->next->number == m) {//����ȡ��֮������ظ����Ҫɾ������
						struct node* q1 = q->next;
						q->next = q1->next;//ɾ����q->nextΪ�½ڵ�
						if (q1->next != NULL) {
							q1->next->front = q;
						}
						free(q1);
						q1 = NULL;
						flag1 = 1;
						break;
					}
					if (q->next->number > m) {//��ʱ����û���ҵ�����Ҫ�����
						struct node* q1 = (struct node*)malloc(sizeof(struct node));
						q1->number = m;
						q1->next = q->next;
						q->next->front = q1;
						q->next = q1;//��������
						q1->front = q;
						q = q->next;//Ҫ��¼q��λ�ã���֤����֤��ʱ��q->next��һ���µĵ㣬ִ��֮��q->next����Ϊ�½ڵ�
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
				if (p->next->next != NULL) {//p->next�Ѿ�������ɣ��ж�p->next->next�Ƿ����
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
void find_right_individual(int i, long long front, long long tail, long long sum, struct node* head) {//�ǵø�Ϊ������ǰ����
	//cout << "ִ��" << endl;
	long long min = front + sum;
	long long max = min + sum - 1;
	struct node* p = head;
	struct node* q = NULL;
	struct node* q1 = NULL;
	int flag = 0;
	while (max <= tail) {
		while (p->next != NULL) {
			//cout << 2 ;
			if (p->next->number >= min && p->next->number <= max) {//���ұ�ţ����Ƿ���ڶ�Ӧ��㣬���ҵ��˾�����ѭ����p->next�ǵ�һ����Ӧ��ŵĽ��
				flag = 1;
				break;
			}
			if (p->next->number > max) {//û�в��ҵ���p->next���µĽ��
				flag = 0;
				break;
			}
			p = p->next;
		}
		if (flag == 1) {//���ҵ���
			//q = p->next;//��ط�û��
			flag = 0;
			while (p->next != NULL && p->next->number <= max) {//maxΪ�������
				//cout << 3 ;
				//cout <<"bb"<< p->next->number << endl;
				q = p->next;//��ط�û��
				long long m = p->next->number - sum;//��Ϊ��Ӧ�����
				int flag1 = 0;
				while (q != head && q->front != head) {//�ӵ�ǰ�����һ����������ֱ����������m��������ҵ���m��ȵ�����������ظ�������Ҫɾ����û���ҵ���m��ȵ�������Ҫ���
					//cout << "kk" << q->front->number << endl;
					if (q != NULL && q->front != head && (q->front->number) == m) {//����ȡ��֮������ظ����Ҫɾ������
						//cout << p->next->number << "�ҵ���" << q->front->number << endl;
						struct node* q1 = q->front;
						if (q1 == p) {
							p = p->front;
							q->front = q1->front;//ɾ����q->frontΪ�½ڵ�
							q1->front->next = q;
							free(q1);
							q1 = NULL;
							flag1 = 1;
							//p = p->next;
						}
						else {
							q->front = q1->front;//ɾ����q->frontΪ�½ڵ�
							q1->front->next = q;
							free(q1);
							q1 = NULL;
							flag1 = 1;
						}
						break;
					}
					if (q->front->number < m) {//��ʱ����û���ҵ�����Ҫ�����
						struct node* q1 = (struct node*)malloc(sizeof(struct node));
						q1->number = m;
						//cout << p->next->number << "�����" << q1->number << endl;
						q1->next = q;
						q->front->next = q1;
						q1->front = q->front;
						q->front = q1;
						q = q->front;//Ҫ��¼q��λ�ã���֤����֤��ʱ��q->front��һ���µĵ㣬ִ��֮��q->next����Ϊ�½ڵ�
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
				if (p->next->next != NULL) {//p->next�Ѿ�������ɣ��ж�p->next->next�Ƿ����
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
	/*cout << "��ӡmmmm" << endl;
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
	//������Ϊ1ʱ����ȡ������
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
			if (p->next->number >= min && p->next->number <= max) {//�˴����Ż�
				//cout << 3;
				if (p->next->number >= min && p->next->number <= middle) {
					//cout << 4;
					m = p->next->number + sum;
					q2 = p->next;
					int flag1 = 0;
					while (q2->next != NULL) {
						//cout << "aaa" << q2->next->number << endl;
						if (q2->next->number == m) {//�ж�Ӧ�㣬�������
							flag1 = 1;
							//cout << p->next->number<< "�ҵ���" <<q2->next->number<< endl;
							break;
						}
						else if (q2->next->number > 0 && q2->next->number > m) {//�޶�Ӧ�㣬��Ҫɾ���˵㣬��Ӷ�Ӧ�㣬���ڶ�Ӧ���������
							struct node* q4 = (struct node*)malloc(sizeof(struct node));
							q4->number = m * (-1);
							//cout << "�����" << q4->number << endl;
							q2->next->front = q4;
							q4->next = q2->next;
							q2->next = q4;
							q4->front = q2;
							flag1 = 1;
							struct node* q5 = p->next;//ɾ���˵�
							flag2 = 1;
							p->next = q5->next;
							q5->next->front = p;
							free(q5);
							break;
						}
						else if (q2->next->number < 0 && ((q2->next->number) * (-1)) > m) {//�޶�Ӧ�㣬��Ҫɾ���˵㣬��Ӷ�Ӧ�㣬���ڶ�Ӧ���������
							struct node* q4 = (struct node*)malloc(sizeof(struct node));
							q4->number = m * (-1);
							//cout << "�����" << q4->number << endl;
							q2->next->front = q4;
							q4->next = q2->next;
							q2->next = q4;
							q4->front = q2;
							flag1 = 1;
							struct node* q5 = p->next;//ɾ���˵�
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
						struct node* q5 = p->next;//ɾ���˵�
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
						if (q3->front->number == m) {//�ж�Ӧ�㣬�������
							flag1 = 1;
							//cout << p->next->number<< "�ҵ���" << q3->front->number << endl;
							break;
						}
						else if (q3->front->number > 0 && q3->front->number < m) {//�޶�Ӧ�㣬��Ҫɾ���˵㣬��Ӷ�Ӧ�㣬���ڶ�Ӧ���������
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
							struct node* q5 = p->next;//ɾ���˵�
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
						else if (q3->front->number < 0 && (q3->front->number) * (-1) < m) {//�޶�Ӧ�㣬��Ҫɾ���˵㣬��Ӷ�Ӧ�㣬���ڶ�Ӧ���������
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
							struct node* q5 = p->next;//ɾ���˵�
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
						struct node* q5 = p->next;//ɾ���˵�
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
	//cout << "��ӡ" << endl;
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
void  polarity_conversion(int q1[], int q2[], struct node* head, int input){//q1�ǵ�ǰ���ԣ�q2��Ŀ�꼫��
	long long front = pow(2, input);
	long long tail = pow(2, input + 1) - 1;
	for (int j = 1; j <= input; j++) {
		//cout << j << endl;
		//cout << "ǰ" << endl;
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
				//cout << "ִ��changeǰ" << endl;
				//print_list(head);
				find_change_individual(j, front, tail, sum, head);
				//cout << "ִ��change��" << endl;
				//print_list(head);
			}
		}
		else {
			if ((q1[j] == 0 && q2[j] == 2) || (q1[j] == 2 && q2[j] == 0) || (q1[j] == 1 && q2[j] == 2)) {
				struct node* p = head;
				while (p != NULL && p->next != NULL) {
					if ((p->next->number) % 2 == 0) {//�ҵ�������������Ҫȡ���Ľ��
						if (p->next->next != NULL) {
							if (p->next->next->number == (p->next->number) + 1) {//˵��ת�������ظ������Ҫɾ��
								struct node* p1 = p->next->next;
								p->next->next = p1->next;
								if (p1->next != NULL) {
									p1->next->front = p->next;
								}
								free(p1);
								p = p->next;//��֤p->nextΪ�½��
							}
							else {//˵��ת�������ظ����,��Ҫ��ӽ��
								struct node* p1 = p->next->next;
								struct node* p2 = (struct node*)malloc(sizeof(struct node));
								p2->number = (p->next->number) + 1;
								p2->next = NULL;
								p2->next = p1;
								p1->front = p2;
								p->next->next = p2;
								p2->front = p->next;
								p = p->next->next;//��֤p->nextΪ�½��
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
							if (p->number == (p->next->number) - 1) {//֤��ת�������ظ���� ��ɾ��p
								//cout << p->next->number << "ɾ����" << p->number << endl;
								struct node* p1 = p;
								p = p->front;
								p1->next->front = p;
								p->next = p1->next;//p->nextΪ�½��
								p = p->next;
								free(p1);
							}
							else {//˵��ת�������ظ���㣬��Ҫ���
								struct node* p1 = (struct node*)malloc(sizeof(struct node));
								p1->number = p->next->number - 1;
								//cout << p->next->number << "�����" << p1->number << endl;
								p->next->front = p1;
								p1->next = p->next;
								p->next = p1;
								p1->front = p;
								p = p->next->next;//��֤p->nextΪ�½��
							}
						}
						else {
							struct node* p1 = (struct node*)malloc(sizeof(struct node));
							p1->number = p->next->number - 1;
							//cout << p->next->number << "�����" << p1->number << endl;
							p->next->front = p1;
							p1->next = p->next;
							p->next = p1;
							p1->front = p;
							p = p->next->next;//��֤p->nextΪ�½��
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
							if (p->next->next->number == p->next->number + 1) {//����ȡ�������ظ���㣬�������
								p = p->next->next;//��֤p->next��һ���½��
							}
							else {//���û������Ҫ��ӽ�㣬��ɾ���˽��;
								p->next->number = p->next->number + 1;
								p = p->next;//��֤p->next��һ���½��,���Ҳ���Ҫ���
							}
						}
						else {
							p->next->number = p->next->number + 1;
							p = p->next;//��֤p->next��һ���½��,���Ҳ���Ҫ���
						}
					}
					else {
						if (p != head) {
							if (p->number == p->next->number - 1) {//����ȡ�������ظ���㣬�������
								p = p->next;//��֤p->next��һ���½��
							}
							else {//���û������Ҫ��ӽ�㣬��ɾ���˽��;
								p->next->number = p->next->number - 1;
								p = p->next;//��֤p->next��һ���½��,���Ҳ���Ҫ���
							}
						}
						else {//��Ҫ��ӽ�㣬��ɾ���˽��
							p->next->number = p->next->number - 1;
							p = p->next;//��֤p->next��һ���½��,���Ҳ���Ҫ���
						}
					}
				}
			}

		}
		//cout << "��" << endl;
		//print_list(head);
	}
}