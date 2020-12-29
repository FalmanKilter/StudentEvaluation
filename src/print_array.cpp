//The function prints the input array into the console
//Allows double, integer and string types of vector data

#include <vector>
#include <iostream>

void print_array(std::vector<int>& a, int& l)

{
	for (int i = 0; i < l; i++)
	{
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

void print_array(std::vector<std::string>& a, int& l)
{
	for (int i = 0; i < l; i++)
	{
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

void print_array(std::vector<double>& a, int& l)
{
	for (int i = 0; i < l; i++)
	{
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}
