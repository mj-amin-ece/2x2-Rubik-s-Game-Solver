#include"rubik.h"
#include "graph.h"

void solve_rubik();

int main()
{
	solve_rubik();

	system("pause");
	return 0;
}

void solve_rubik()
{
	try
	{
		while (true)
		{
			Rubik input_rubik{};
			Graph solution{ input_rubik };
			std::string  user_answer;
			char ch;
			std::cout << "-------------------------------------------------------------------------------" << std::endl;
			std::cout << "Search method (BFS/DLS/IDS/BI) : ";
			std::cin >> user_answer;
			if (user_answer == "BI")
				solution.show_solution_bidirectional();
			else if (user_answer == "BFS")
				solution.show_solution_BFS();
			else if (user_answer == "IDS")
				solution.show_solution_IDS();
			else if (user_answer == "DLS")
				solution.show_solution_DLS();
			else
				throw std::invalid_argument("input search method wrong");

			
			std::cout << "do you want to try another Rubik? (y/n): ";
			std::cin >> ch;
			if (ch == 'y')
				continue;
			else if (ch == 'n')
				break;
			else
				throw std::invalid_argument("wrong input");
		}
		std::cout << "ok,see you!" << std::endl;
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << std::endl << e.what() << std::endl;
	}
	
}
