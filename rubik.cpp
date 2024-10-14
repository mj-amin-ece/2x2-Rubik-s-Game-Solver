#include "rubik.h"

std::vector<std::string> user_color_r(6);       //save user input color

Rubik::Rubik()                                  //default constructor
{
	colors = std::vector<std::string>(24);      //initialize colors
	user_color = user_color_r;                  //initialize user colors
	set_rubik();                                //get a rubik
	set_color();                                //save elements color of rubik 
}

Rubik::Rubik(const std::vector<size_t>& input_vector)              //constructor
{
	if (input_vector.size() != 24)                                 //number of inputs elements must be 24 
		throw std::invalid_argument("wrong size input vector");

	colors = std::vector<std::string>(24);                         //initialize colors     
	user_color = user_color_r;                                     //initialize user colors
	numbers = input_vector;                                        //sava input rubik
	for (size_t i{ 1 }; i < 7; i++)                                //check input rubix 
		counter(i);
}

void Rubik::set_rubik()                     //get a rubik from user                                    
{
	introduce();                            //show some information

	std::cout << "for enter elements for each face put space between them and end of each face press enter and go to next face" << std::endl;
	std::cout << "enter your numbers in range 1 to 6" << std::endl;
	
	size_t input{};   

	for (size_t i = 0; i < 6; i++)          //get 6 face
	{
		std::cout << "face " << i+1 << " :" << std::endl;

		for (size_t i = 0; i < 4; i++)  
		{  
			std::cin >> input;              //get a elements of face

			if (input > 0 && input < 7)     //check the range of input
				numbers.push_back(input);   //save elements of rubik
			else 
				throw std::invalid_argument("out of the range number please replace it");
		}
	}
	for (size_t i{ 1 }; i < 7; i++)         //check input rubix 
		counter(i);
	user_color = user_color_r;              //save user colors
	set_color();                            //save elements color of rubik 
	std::cout <<  std::endl;
	show_rubik_color();
}

void Rubik::introduce()                     //show some information   
{
	std::cout << "Hi!" << std::endl;
	std::cout << "introduce colors " << std::endl;
	std::cout << std::setw(15) << "green -> g" << std::endl;
	std::cout << std::setw(15) << "white -> w" << std::endl;
	std::cout << std::setw(15) << "orange -> o" << std::endl;
	std::cout << std::setw(16) << "yellow -> y " << std::endl;
	std::cout << std::setw(16) << "blue -> b " << std::endl;
	std::cout << std::setw(15) << "red -> r" << std::endl;
	std::cout << "-------------------------------------------------------------------------------" << std::endl;
	Rubik introduce{ std::vector<size_t>{1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6 } };
	introduce.show_rubik_index();
	std::cout << "chose your color for each face (g/w/o/y/b/r) " << std::endl;
	for (size_t i{}; i < 6; i++)                  //get user colors
	{
		std::cout << "face " << i + 1 << " : ";
		std::cin >> user_color_r[i];
		std::cout << std::endl;
	}
	introduce.user_color = user_color_r;         //save user color
	introduce.show_rubik_color();                //show rubik 
	std::cout << "-------------------------------------------------------------------------------" << std::endl;
	std::cout << "we have four search methods here " << std::endl;
	std::cout << std::setw(15) << "Breadth-ﬁrst search -> BFS" << std::endl;
	std::cout << std::setw(15) << "Depth-limited search -> DLS" << std::endl;
	std::cout << std::setw(15) << "Iterative-deepening search -> IDS" << std::endl;
	std::cout << std::setw(15) << "Bidirectional -> BI" << std::endl << std::endl;
	std::cout << "thanks for your attention " << std::endl;
	std::cout << "programed by Mohammad Javad Amin" << std::endl;
	std::cout << "spring 2020" << std::endl ;
	std::cout << "-------------------------------------------------------------------------------" << std::endl;
}

void Rubik::set_color()        
{
	for (size_t i{ 1 }; i < 7; i++)      //check rubik is valid or not
		counter(i);
	for (size_t i{}; i < 6; i++)         //check rubik is valid or not
		counter_color(user_color[i]);

	for (size_t i{}; i < 24; i++)        //set color for rubik elements
	{
		if (numbers[i] == 1)
			colors[i] = which_color(user_color[0]);
		else if (numbers[i] == 2)
			colors[i] = which_color(user_color[1]);
		else if (numbers[i] == 3)
			colors[i] = which_color(user_color[2]);
		else if (numbers[i] == 4)
			colors[i] = which_color(user_color[3]);
		else if (numbers[i] == 5)
			colors[i] = which_color(user_color[4]);
		else if (numbers[i] == 6)
			colors[i] = which_color(user_color[5]);
		else
			throw std::invalid_argument("out of the range number please replace it");
	}
}

std::string  Rubik::which_color(const std::string& input_color)    //to recognition color and save it
{
	if (input_color == "g")
		return print_as_color<ansi_color_code::green>("g");
	else if (input_color == "r")
		return print_as_color<ansi_color_code::red>("r");
	else if (input_color == "w")
		return print_as_color<ansi_color_code::white>("w");
	else if (input_color == "y")
		return print_as_color<ansi_color_code::yellow>("y");
	else if (input_color == "b")
		return print_as_color<ansi_color_code::blue>("b");
	else if (input_color == "o")
		return print_as_color<ansi_color_code::orange>("o");
	else
		throw std::invalid_argument("wrong input color from user ");
}

void Rubik::counter(const size_t& i)   //check rubik is valid or not(check number of each rubik element)
{
	size_t count{};                    //counter

	for (size_t j = 0; j < 24; j++)    //count each element in rubik
		if(!(numbers[j]-i))
			count++;

	if (count < 4)                     //number of each must be 4 else it's incrroct
	{
		std::ostringstream oss{};
		oss << "Numbers of " << i << " less than 4 , it must be 4" << std::endl;
		throw std::invalid_argument(oss.str());
	}
	if (count > 4)
	{
		std::ostringstream oss{};
		oss << "Numbers of " << i << " bigger than 4 , it must be 4" << std::endl;
		throw std::invalid_argument(oss.str());
	}
}

void Rubik::counter_color(const std::string& s)     //to check input color rubik 
{
	size_t count{};                   //counter

	for (size_t j = 0; j < 6; j++)    //count each input color  from user
		if (s == user_color[j])
			count++;

	if (count < 1)                     //number of each color be 1 else it's incrroct
	{
		std::ostringstream oss{};
		oss << "Numbers of color " << s << " less than 1 , it must be 1" << std::endl;
		throw std::invalid_argument(oss.str());
	}
	if (count > 1)
	{
		std::ostringstream oss{};
		oss << "Numbers of color " << s << " bigger than 1 , it must be 1" << std::endl;
		throw std::invalid_argument(oss.str());
	}
}

Rubik Rubik::rotate(const size_t& face, size_t repeat,const std::string& rotate_name)
{
	repeat %= 4;                                    //number of times to rotate a face

	std::vector<size_t> numbers_new{ numbers };     //for save element of changed rubik

	if (rotate_name == "clockwise")                 //rotation is clockwise
	{
		for (size_t i{ 1 }; i <= repeat; i++)       //each time rotation
		{
			std::vector<size_t>temp_face{};         //for save face elements

			for (size_t i = face * 4; i < (face + 1) * 4; i++)
				temp_face.push_back(numbers_new[i]);//save face elements

			size_t index{ face * 4 };

			//new element of face  after rotation                                  
			numbers_new[index] = temp_face[2];
			numbers_new[index + 1] = temp_face[0];
			numbers_new[index + 2] = temp_face[3];
			numbers_new[index + 3] = temp_face[1];

			std::vector<size_t> temp{ numbers_new };

			if (face == 0)                          //face 0 rotate colokwise
			{ 
				//face 1
				numbers_new[4] = temp[8];
				numbers_new[5] = temp[9];
				//face 2
				numbers_new[8] = temp[12];
				numbers_new[9] = temp[13];
				//face 3
				numbers_new[12] = temp[23];
				numbers_new[13] = temp[22];
				//face 5
				numbers_new[23] = temp[4];
				numbers_new[22] = temp[5];
			}
			else if (face == 1)                     //face 1 rotate colokwise
			{
				//face0
				numbers_new[0] = temp[20];
				numbers_new[2] = temp[22];
				//face2
				numbers_new[8] = temp[0];
				numbers_new[10] = temp[2];
				//face 4
				numbers_new[16] = temp[8];
				numbers_new[18] = temp[10];
				//face 5
				numbers_new[20] = temp[16];
				numbers_new[22] = temp[18];
			}

			else if (face == 2)                    //face 2 rotate colokwise
			{
				//face 0
				numbers_new[2] = temp[7];
				numbers_new[3] = temp[5];
				//face 1
				numbers_new[5] = temp[16];
				numbers_new[7] = temp[17];
				//face 3
				numbers_new[12] = temp[2];
				numbers_new[14] = temp[3];
				//face 4
				numbers_new[16] = temp[14];
				numbers_new[17] = temp[12];
			}

			else if (face == 3)                   //face 3 rotate colokwise
			{
				//face 0
				numbers_new[1] = temp[9];
				numbers_new[3] = temp[11];
				//face 2
				numbers_new[9] = temp[17];
				numbers_new[11] = temp[19];
				//face 4
				numbers_new[17] = temp[21];
				numbers_new[19] = temp[23];
				//face 5
				numbers_new[21] = temp[1];
				numbers_new[23] = temp[3];
			}

			else if (face == 4)                  //face 4 rotate colokwise
			{
				//face 1
				numbers_new[6] = temp[21];
				numbers_new[7] = temp[20];
				//face 2
				numbers_new[10] = temp[6];
				numbers_new[11] = temp[7];
				//face 3
				numbers_new[14] = temp[10];
				numbers_new[15] = temp[11];
				//face 5
				numbers_new[20] = temp[15];
				numbers_new[21] = temp[14];
			}

			else if (face == 5)                 //face 5 rotate colokwise
			{
				//face 0
				numbers_new[0] = temp[13];
				numbers_new[1] = temp[15];
				//face 1
				numbers_new[4] = temp[1];
				numbers_new[6] = temp[0];
				//face 3
				numbers_new[15] = temp[18];
				numbers_new[13] = temp[19];
				//face 4
				numbers_new[18] = temp[4];
				numbers_new[19] = temp[6];
			}
		}
	}
	else if (rotate_name == "anticlockwise")     //rotation is anticlockwise
		return Rubik{ rotate(face, 4 - repeat, "clockwise") };
	else
		throw std::invalid_argument("wrong name rotate");

	return Rubik{ numbers_new };                 //return rubik after rotation
}

bool Rubik::solve_check()                      //check rubik is solve or not
{ 
	bool check_flag{ true };                    //to show rubik is solved or not

	set_color();                                //save element colors of rubik 

	for (size_t i = 0; i < 24; i += 4)          //check each face of rubik has same elements or not 
	{
		if (colors[i] == colors[i + 1] && colors[i + 1] == colors[i + 2] && colors[i + 2] == colors[i + 3])
			continue;
		else
		{
			check_flag = false;
			break;
		}
	}

	return check_flag;                     
}

void Rubik::show_rubik_index()                  //show elements of the rubik
{
	std::cout << "Rubik's cube interal indexing is" << std::endl << std::endl;
	std::cout << std::setw(29) << "+--------+" << std::endl;
	for (size_t i{}; i < 4; i += 2)
		std::cout << std::setw(20) << "|" << std::setw(3) << numbers[i] << std::setw(3) << numbers[i + 1] << std::setw(3) << "|" << std::endl;
	std::cout << std::setw(20) << "+--------+" << "--------+" << "--------+" << std::endl;
	std::cout << std::setw(11) << "|" << std::setw(3) << numbers[4] << std::setw(3) << numbers[5] << std::setw(3) << "|";
	std::cout << std::setw(3) << numbers[8] << std::setw(3) << numbers[9] << std::setw(3) << "|";
	std::cout << std::setw(3) << numbers[12] << std::setw(3) << numbers[13] << std::setw(3) << "|" << std::endl;
	std::cout << std::setw(11) << "|" << std::setw(3) << numbers[6] << std::setw(3) << numbers[7] << std::setw(3) << "|";
	std::cout << std::setw(3) << numbers[10] << std::setw(3) << numbers[11] << std::setw(3) << "|";
	std::cout << std::setw(3) << numbers[14] << std::setw(3) << numbers[15] << std::setw(3) << "|" << std::endl;
	std::cout << std::setw(20) << "+--------+" << "--------+" << "--------+" << std::endl;
	for (size_t i{ 16 }; i < 20; i += 2)
		std::cout << std::setw(20) << "|" << std::setw(3) << numbers[i] << std::setw(3) << numbers[i + 1] << std::setw(3) << "|" << std::endl;
	std::cout << std::setw(29) << "+--------+" << std::endl;
	for (size_t i{ 20 }; i < 24; i += 2)
		std::cout << std::setw(20) << "|" << std::setw(3) << numbers[i] << std::setw(3) << numbers[i + 1] << std::setw(3) << "|" << std::endl;
	std::cout << std::setw(29) << "+--------+" << std::endl;
}

void Rubik::show_rubik_color()             //show elements color of the rubik
{
	set_color();

	std::cout << "Rubik's cube interal colors is" << std::endl << std::endl;
	std::cout << std::setw(29) << "+--------+" << std::endl;
	for (size_t i{}; i < 4; i += 2)
		std::cout << std::setw(20) << "|" << std::setw(15) << colors[i] << std::setw(15) << colors[i + 1] << std::setw(3) << "|" << std::endl;
	std::cout << std::setw(20) << "+--------+" << "--------+" << "--------+" << std::endl;
	std::cout << std::setw(11) << "|" << std::setw(15) << colors[4] << std::setw(15) << colors[5] << std::setw(3) << "|";
	std::cout << std::setw(15) << colors[8] << std::setw(15) << colors[9] << std::setw(3) << "|";
	std::cout << std::setw(15) << colors[12] << std::setw(15) << colors[13] << std::setw(3) << "|" << std::endl;
	std::cout << std::setw(11) << "|" << std::setw(15) << colors[6] << std::setw(15) << colors[7] << std::setw(3) << "|";
	std::cout << std::setw(15) << colors[10] << std::setw(15) << colors[11] << std::setw(3) << "|";
	std::cout << std::setw(15) << colors[14] << std::setw(15) << colors[15] << std::setw(3) << "|" << std::endl;
	std::cout << std::setw(20) << "+--------+" << "--------+" << "--------+" << std::endl;
	for (size_t i{ 16 }; i < 20; i += 2)
		std::cout << std::setw(20) << "|" << std::setw(15) << colors[i] << std::setw(15) << colors[i + 1] << std::setw(3) << "|" << std::endl;
	std::cout << std::setw(29) << "+--------+" << std::endl;
	for (size_t i{ 20 }; i < 24; i += 2)
		std::cout << std::setw(20) << "|" << std::setw(15) << colors[i] << std::setw(15) << colors[i + 1] << std::setw(3) << "|" << std::endl;
	std::cout << std::setw(29) << "+--------+" << std::endl;
}

bool Rubik::operator==(Rubik A)         //operator ==
{
	set_color();                        //save element colors of rubiks 
	A.set_color();                      //compare two rubiks
	if (colors == A.colors)
		return true;
	else
		return false;
}

template<ansi_color_code color, typename printable>
inline std::string print_as_color(printable const& value)    //save string for print each elements in color
{
	std::stringstream sstr{};
	if (color == ansi_color_code::orange)
		sstr << "  \033[48;2;255;165;0m" << value << "\033[0m";
	else
		sstr << "\033[1;" << static_cast<int>(color) << "m" << value << "\033[0m";
	return sstr.str();
}
