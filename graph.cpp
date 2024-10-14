#include "graph.h"


Graph::Graph(const Rubik& A)    //constructors
{
	rubiks.push_back(A);        //save input rubik
	size = rubiks.size();       //save size of nodes
	limit = 0;                  //depth limits 
}

bool Graph::new_nodes_BFS()     //new nodes for each limit in BFS algorithm
{
	size_t numer_of_new_nodes{ static_cast<size_t>(std::pow(12,limit)) };  //number of total nodes in this limit
	bool find_solve{ false };                                              //for show find solution

	for (size_t i = size - numer_of_new_nodes; i < size; i++)              //creat new nodes
	{
		if (rubiks[i].solve_check())                                       //check rubik is solve or not
		{
			limit--;
			find_solve = true;
			break;
		}

		for (size_t j = 0; j < 12; j++)                                   //rotate rubik to crate new nodes
		{
			std::ostringstream oss{};

			if (j / 6 == 0)                                               //rotate clockwise
			{
				rubiks.push_back(rubiks[i].rotate(j % 6, 1, "clockwise"));//save new nodes
				oss << "face " << (j % 6) + 1 << "->  clockwise";        
				rubik_rotations.push_back(oss.str());                     //save rotations
			}
			if (j / 6 == 1)                                               //rotate anticlockwise
			{
				rubiks.push_back(rubiks[i].rotate(j % 6, 1, "anticlockwise"));//save new nodes
				oss << "face " << (j % 6) + 1 << "-> anticlockwise";
				rubik_rotations.push_back(oss.str());                    //save rotations
			}
			if (rubiks[rubiks.size() - 1].solve_check())                //check rubik is solve or not
			{
				find_solve = true;
				break;
			}
		}
		if (find_solve)
			break;
	}

	size = rubiks.size();                                        //save size of nodes
	limit++;

	return find_solve;
}

void Graph::save_solution(size_t limit_graph, size_t index_node)  //for save Rotations for solve rubik
{
	if (limit_graph == 1)
		solution_rubik_rotations[0] = rubik_rotations[size - 1];
	else
	{
		size_t index{ ((index_node - number_of_node(limit_graph - 1)) / 12) + number_of_node(limit_graph - 2) };

		solution_rubik_rotations.push_back(rubik_rotations[index + 1]);
		save_solution(limit_graph - 1, index);
	}
}

void Graph::show_solution_BFS()                                 //solution with BFS algorithm
{
	char ch;                                                    //for input answer user 
	std::cout << "-------------------------------------------------------------------------------" << std::endl;
	if (rubiks[0].solve_check())                                //chech rubik is solved or not
		std::cout << std::endl << std::endl << "you give me a solved rubik, why? !!" << std::endl;
	else                                                       
	{
		while (!new_nodes_BFS()) {};                              //solve rubiks with BFS algorithm
		save_solution(getlimit(), getsize() - 1);               //save rotations to how to solve rubik

		for (int i = solution_rubik_rotations.size() - 1; i >= 0; i--)   //show rotations to how to solve rubik
		{
			std::cout << "step " << solution_rubik_rotations.size() - i << " : ";
			std::cout << solution_rubik_rotations[static_cast<size_t>(i)] << std::endl;;
		}
		std::cout << "-------------------------------------------------------------------------------" << std::endl;
		std::cout << "do you want to show limit and numbers of nodes? (y/n): ";
	
		std::cin >> ch;                        //user answer

		if (ch == 'y')                         //print limit and number of nodes
		{
			std::cout << "depth limit : " << getlimit() << std::endl;
			std::cout << "node : " << getsize() - 1 << std::endl;
		}
		else if (ch == 'n')
			std::cout << "ok" << std::endl;
		else
			throw std::invalid_argument("wrong input");
		std::cout << "-------------------------------------------------------------------------------" << std::endl;
	}

	std::cout << "do you want to show rubik? (y/n): ";

	std::cin >> ch;                          //user answer

	if (ch == 'y')                           //show rubik
		rubiks[size - 1].show_rubik_color();
	else if (ch == 'n')
		std::cout << "ok" << std::endl;
	else
		throw std::invalid_argument("wrong input");
	std::cout << "-------------------------------------------------------------------------------" << std::endl;
}

size_t Graph::getlimit()             //get depth limit
{
	return limit;
}

size_t Graph::getsize()             //get size of nodes
{
	return size;
}

void Graph::new_nodes_bidirectional(const bool& flag) //new nodes for each limit in bidirectional algorithm
{
	size_t numer_of_new_nodes{ static_cast<size_t>(std::pow(12,limit)) }; //number of total nodes in this limit

	for (size_t i = size - numer_of_new_nodes; i < size; i++)       //creat new nodes
	{
		for (size_t j = 0; j < 12; j++)                             //rotate rubik to crate new nodes
		{
			std::ostringstream oss{};

			if (j / 6 == 0)                                         //rotate clockwise
			{
				rubiks.push_back(rubiks[i].rotate(j % 6, 1, "clockwise")); //save new nodes
				if (flag)                                                  //change gole or input rubik
					oss << "face " << (j % 6) + 1 << "-> anticlockwise";
				else
					oss << "face " << (j % 6) + 1 << "-> clockwise";
				rubik_rotations.push_back(oss.str());                      //save rotations
			}
			if (j / 6 == 1)                                                       //rotate anticlockwise
			{
				rubiks.push_back(rubiks[i].rotate(j % 6, 1, "anticlockwise"));    //save new nodes
				if (flag)                                                         //change gole or input rubik
					oss << "face " << (j % 6) + 1 << "-> clockwise";
				else
					oss << "face " << (j % 6) + 1 << "-> anticlockwise";
				rubik_rotations.push_back(oss.str());                            //save rotations
			}
		}
	}
	size = rubiks.size();                                                    //save size of nodes
	limit++;
}

void Graph::save_solution_bidirectional(Graph& Target, const std::array<int, 2>& find) //save rotations to how to solve rubik
{
	save_solution(getlimit(), find[1]);    //node input side  and save rotations
	Target.save_solution(getlimit(), find[0]);  //node gole side and save rotations

	for (int i = solution_rubik_rotations.size() - 1; i >= 0; i--)    //save rotations to how to solve rubik
	{
		if (solution_rubik_rotations[i] != "")
			solution_rubik_rotations_bidirectional.push_back(solution_rubik_rotations[i]);
	}
	for (size_t i = 0; i < Target.solution_rubik_rotations.size(); i++)
	{
		solution_rubik_rotations_bidirectional.push_back(Target.solution_rubik_rotations[i]);
	}
}

std::array<int, 2> Graph::chek_bidirectional(Graph& Target)  //check we solved rubik or not 
{
	std::array<int, 2> find{ -1,-1 };              //to show find solution or not and save node in both side 

	for (size_t i = number_of_node(limit - 1); i <= number_of_node(limit); i++)
	{
		for (size_t j = number_of_node(limit - 1); j <= number_of_node(limit); j++)
		{
			if (rubiks[j] == Target.rubiks[i])
			{
				find[0] = static_cast<int>(i);    //save node from gola side
				find[1] = static_cast<int>(j);    //save node from input side
				break;
			}
		}
	}
	return find;
}

void Graph::bidirectional()           //solve rubiks with bidirectional algorithm
{
	Graph Target{ Rubik { std::vector<size_t>{1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6 } } };  //goal rubik
	std::array<int, 2> find{ -1,-1 };              //to show find solution or not and save node in both side

	while (true)                                  //solve rubiks with BFS algorithm
	{
		Target.new_nodes_bidirectional(true);
		new_nodes_bidirectional(false);
		find = chek_bidirectional(Target);
		if (find[0] >= 0)
			break;
	}
	size = find[1] + 1;                         //number nodes inputs side
	Target.size = find[0] + 1;                  //number node goal side
	save_solution_bidirectional(Target, find); //save rotations to how to solve rubik
}

void Graph::show_solution_bidirectional()    //solution with bidirectional algorithm
{
	std::cout << "-------------------------------------------------------------------------------" << std::endl;
	char ch;
	if (rubiks[0].solve_check())                   //check rubik is solved or not
		std::cout << std::endl << std::endl << "you give me a solved rubik, why? !!" << std::endl;
	else
	{
		bidirectional();                      //solve rubiks with bidirectional algorithm

		for (size_t i = 0; i < solution_rubik_rotations_bidirectional.size(); i++)  //show rotations to how to solve rubik
		{
			std::cout << "step " << i + 1 << " : ";
			std::cout << solution_rubik_rotations_bidirectional[i] << std::endl;;
		}
		std::cout << "-------------------------------------------------------------------------------" << std::endl;
		std::cout << "do you want to show limit ? (y/n): ";
		
		std::cin >> ch;     //user answer

		if (ch == 'y')     //show depth limit
		{
			std::cout << "depth limit : " << getlimit() << std::endl;
		}
		else if (ch == 'n')
			std::cout << "ok" << std::endl;
		else
			throw std::invalid_argument("wrong input");
		std::cout << "-------------------------------------------------------------------------------" << std::endl;
			
	}

	std::cout << "do you want to show rubik? (y/n): ";
	std::cin >> ch;       //user answer

	Rubik gole{ std::vector<size_t>{1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6 } };

	if (ch == 'y')   //show rubik goal
		gole.show_rubik_color();
	else if (ch == 'n')
		std::cout << "ok" << std::endl;
	else
		throw std::invalid_argument("wrong input");
	std::cout << "-------------------------------------------------------------------------------" << std::endl;
}

bool Graph::DLS(size_t li , Rubik input)     //DLS algorithm
{
	if (input.solve_check())     //check rubik is solved or not
		return true;

	if (li == 0)
	{
		bool find_solve{ false };   //to show we find solution or not

		limit_temp++;               //back to upper limit

		if (input.solve_check())   //check rubik is solved or not
			find_solve = true;

		return find_solve;
	}
	else 
		return new_nodes_dls(input);
}

bool Graph::new_nodes_dls(Rubik A)    //new nodes for each limit in DLS algorithm
{
	size_t numer_of_new_nodes{ 12 };   //number of new nodes 
	bool find_solve{ false };    //to show we find solution or not

	for (size_t j = 0; j < numer_of_new_nodes; j++)   //rotate rubik to crate new nodes
	{
		std::ostringstream oss{};
		
		if (j / 6 == 0)                    //rotate clockwise
		{
			rubiks.push_back(A.rotate(j % 6, 1, "clockwise")); //save new nodes
			oss << "face " << (j % 6) + 1 << "->  clockwise";  
			rubik_rotations.push_back(oss.str());  //save rotations
		}
		if (j / 6 == 1)                     //rotate anticlockwise
		{
			rubiks.push_back(A.rotate(j % 6, 1, "anticlockwise"));  //save new nodes
			oss << "face " << (j % 6) + 1 << "-> anticlockwise";   
			rubik_rotations.push_back(oss.str());          //save rotations
		}

		find_solve = DLS(--limit_temp, rubiks[rubiks.size() - 1]);  //do down  depth limit
		
		if (find_solve)  
			break;
		else
			rubik_rotations.pop_back(); //if it not our solution so clear this rotation
	}
	size = rubiks.size();  //save size of nodes
	limit_temp++;

	return find_solve;
}

void Graph::show_solution_DLS()        //solution with IDS algorithm
{
	std::cout << "-------------------------------------------------------------------------------" << std::endl;
	char ch;        //user answer
	std::cout << "do you want enter depth limit (y/n) :";
	std::cin >> ch;
	if (ch == 'y')  //get limit from user
	{
		std::cout << "please enter depth limit search : ";
		std::cin >> limit;
	}
	else if(ch=='n')
		limit = 8;                         //depth limit search 
	else
		throw std::invalid_argument("wrong input");
	std::cout << "-------------------------------------------------------------------------------" << std::endl;

	limit_temp = limit;
	rubik_rotations = {};
	if (DLS(limit, rubiks[0]))     //solve rubiks with DLS algorithm
	{
		for (size_t i{}; i < rubik_rotations.size(); i++)  //show rotations to how to solve rubik
		{
			std::cout << "step " << i + 1 << " : ";
			std::cout << rubik_rotations[i] << std::endl;;
		}

		std::cout << "-------------------------------------------------------------------------------" << std::endl;
		std::cout << "do you want to show limit and numbers of nodes? (y/n): ";

		std::cin >> ch;                        //user answer

		if (ch == 'y')                         //print limit and number of nodes
		{
			std::cout << "depth limit : " << getlimit() << std::endl;
			std::cout << "node : " << getsize() - 1 << std::endl;
		}
		else if (ch == 'n')
			std::cout << "ok" << std::endl;
		else
			throw std::invalid_argument("wrong input");

		std::cout << "-------------------------------------------------------------------------------" << std::endl;
		std::cout << "do you want to show rubik? (y/n): ";

		std::cin >> ch;                          //user answer

		if (ch == 'y')                           //show rubik
			rubiks[size - 1].show_rubik_color();
		else if (ch == 'n')
			std::cout << "ok" << std::endl;
		else
			throw std::invalid_argument("wrong input");
		std::cout << "-------------------------------------------------------------------------------" << std::endl;

	}
	else
	{
		std::cout << "can not find solutin in depth limit " << limit << std::endl;
		std::cout << "-------------------------------------------------------------------------------" << std::endl;
	}
}

void Graph::show_solution_IDS()      //solution with IDS algorithm
{
	char ch;        //user answer
	bool flag{ true };  //show we find solution or not
	std::cout << "-------------------------------------------------------------------------------" << std::endl;
	size_t max_limit{};
	std::cout << "do you want enter maximum depth limit (y/n) :";
	std::cin >> ch;
	if (ch == 'y')   //get max limit from user
	{
		std::cout << "please enter maximum depth limit search : ";
		std::cin >> max_limit;
	}
	else if (ch == 'n')
		max_limit = 10;                         //max depth limit search 
	else
		throw std::invalid_argument("wrong input");
	std::cout << "-------------------------------------------------------------------------------" << std::endl;
	while (true)    //solve rubiks with IDS algorithm
	{                              //start new graph each depth limit
		Rubik input = rubiks[0];   //save input rubik
		rubiks = {};
		rubik_rotations = {};
		limit_temp = limit;
		rubiks.push_back(input);
		if (DLS(limit, rubiks[0]))  //chech we find solution or not in DLS algorithm
			break;
		limit++;           //increasing limit
		if (limit > max_limit)
		{
			std::cout << "can not find solutin in depth limit " << max_limit << std::endl;
			std::cout << "-------------------------------------------------------------------------------" << std::endl;
			flag = false;
			break;
		}
	}
	if (flag)   //if we find solution
	{
		for (size_t i{}; i < rubik_rotations.size(); i++)  //show rotations to how to solve rubik
		{
			std::cout << "step " << i + 1 << " : ";
			std::cout << rubik_rotations[i] << std::endl;;
		}
		std::cout << "-------------------------------------------------------------------------------" << std::endl;
		char ch;        //user answer
		std::cout << "do you want to show limit and numbers of nodes? (y/n): ";

		std::cin >> ch;                        //user answer

		if (ch == 'y')                         //print limit and number of nodes
		{
			std::cout << "depth limit : " << getlimit() << std::endl;
			std::cout << "node : " << getsize() - 1 << std::endl;
		}
		else if (ch == 'n')
			std::cout << "ok" << std::endl;
		else
			throw std::invalid_argument("wrong input");
		std::cout << "-------------------------------------------------------------------------------" << std::endl;

		std::cout << "do you want to show rubik? (y/n): ";

		std::cin >> ch;                          //user answer

		if (ch == 'y')                           //show rubik
			rubiks[size - 1].show_rubik_color();
		else if (ch == 'n')
			std::cout << "ok" << std::endl;
		else
			throw std::invalid_argument("wrong input");
		std::cout << "-------------------------------------------------------------------------------" << std::endl;
	}
	
}


Rubik Graph::operator[](const size_t& i)   //operator []
{
	return rubiks[i];
}

size_t number_of_node(int x)         //number of nodes in each limit in BFS algoritm
{
	if (x < 0)
		return 0;
	else
		return static_cast<size_t>((std::pow(12, x + 1) - 1) / 11) - 1;
}
