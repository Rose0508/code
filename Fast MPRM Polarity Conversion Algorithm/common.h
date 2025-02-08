#pragma once
#include <iostream>
#include <ctime>
#include<fstream>
#include<stdio.h>
#include<queue>
#include<stdlib.h>
#include "compression_encoding.h"
#include"polarity_conversion.h"
#include"generate_initial_population.h"
struct individual {
	long long number;
	char leftflag;
	char rightflag;
	struct individual* left;
	struct individual* right;
};
struct node {
	int number;
	struct node* front;
	struct node* next;
};
struct individual_node {
	int polarity[50];
	struct individual_node* next;
};
extern void print_list(struct node* head);
extern void put_polarity_helper(struct individual* head, int path[], int len);
extern void put_polarity(struct individual* head);
using namespace std;