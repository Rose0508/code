#pragma once
#ifndef GENERATE_INITIAL_POPULATION_H
#define GENERATE_INITIAL_POPULATION_H
extern struct individual_node* generate_initial_population(int input, int popsize);
extern void put_popsize(struct individual_node* head, int input);
extern void initialization_individual_node(struct individual_node* p);
#endif
