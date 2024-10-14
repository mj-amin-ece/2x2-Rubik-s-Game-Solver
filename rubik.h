#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<iomanip>

class Rubik
{
private:                                                                    //member variable
	std::vector<std::string> colors;                                        //to save  elements color of rubik
	std::vector<std::string> user_color;                                    //to save user colors for rubik 
	std::vector<size_t> numbers;                                            //to save elements of rubik
	                                                                        //member function
	void introduce();                                                       //show some information              
	void set_rubik();                                                       //get a rubik from user 
	void set_color();                                                       //save colors the rubik
	std::string which_color(const std::string& input_color);                //to recognition color
	void counter(const size_t& i);                                          //to check input rubik 
	void counter_color(const std::string& s);                               //to check input color rubik 

public: 
	Rubik();                                                                           //default constructor
	Rubik(const std::vector<size_t>& input_vector);                                    //constructor
	Rubik rotate(const size_t& face, size_t repeat, const std::string& rotate_name);   //Rotate rubik
	bool solve_check();                                                                //check rubik is solve or not
	void show_rubik_index();                                                           //show rubik elements
	void show_rubik_color();                                                           //show rubik  elements color

	bool operator==(Rubik A);                                                          //operator ==
};

enum class ansi_color_code : int {                      //color

	red = 101,
	green = 102,
	yellow = 103,
	blue = 104,
	white = 107,
	orange = 0,
};


template<ansi_color_code color, typename printable>      //save string for print each elements in color
std::string print_as_color(printable const& value);


