#pragma once
#ifndef POLARITY_CONVERSION_H
#define POLARITY_CONVERSION_H
extern void find_left_individual(int i, long long front, long long tail, long long sum, struct node* head);
extern void find_right_individual(int i, long long  front, long long tail, long long sum, struct node* head);
extern void find_change_individual(int i, long long  front, long long tail, long long sum, struct node* head);
extern void polarity_conversion(int q1[], int q2[], struct node* head, int input);
#endif
