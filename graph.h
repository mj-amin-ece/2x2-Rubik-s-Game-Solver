#pragma once
#include<cmath>
#include<array>
#include"rubik.h"

class Graph
{
private:
	std::vector<Rubik> rubiks;    //rubiks
	size_t limit{};               //depth limit
	int limit_temp{};             //depth limit for DLS algorithm
	size_t size{};                 //size of nodes

	std::vector<std::string>rubik_rotations{ "" };    //to save rubik rotations
	std::vector<std::string>solution_rubik_rotations{ "" }; //to save solutions rubik rotations
	std::vector<std::string>solution_rubik_rotations_bidirectional{}; //to save solutions rubik rotations in bidirectional algotithm

	bool new_nodes_BFS();                                      //new nodes for each limit in BFS algorithm
	void save_solution(size_t limit_graph, size_t index_node); //for save Rotations for solve rubik
	void new_nodes_bidirectional(const bool& flag);            //new nodes for each limit in bidirectional algorithm
	void save_solution_bidirectional(Graph& Target, const std::array<int, 2>& find);//save rotations to how to solve rubik
	std::array<int, 2> chek_bidirectional(Graph& Target);//check we solved rubik or not
	void bidirectional();                                                  //solve rubiks with BFS algorithm 
	bool DLS(size_t l, Rubik B);         //DLS algorithm
	bool new_nodes_dls(Rubik A);        //new nodes for each limit in DLS algorithm
public:
	Graph(const Rubik& A);                     //constructors
	void show_solution_BFS();                  //solution with BFS algorithm
	void show_solution_bidirectional();        //solution with bidirectional algorithm
	void show_solution_DLS();                  //solution with DLS algorithm
	void show_solution_IDS();                  //solution with IDS algorithm
	size_t getlimit();                         //get depth limit
	size_t getsize();                          //get number of nodes 
	Rubik operator[](const size_t& i);         //operator []
};

size_t number_of_node(int x);   //number of nodes in each limit in BFS algoritm
