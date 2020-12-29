/*The program takes in information about students in class:
* their names, midterm, finals and homework grades,
* calculates their final grade:
* final grade = 0.4 * midterm grade + 0.4 * final grade + 0.2 * average homework grade
* returns lists of students who passed and who failed the course given a passing grade.
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "useful.h"
#include <list>
#include <cassert>

// define student structure
struct student
{
	std::string name = " ";
	double final_grade;
};													

// caculate average grade for homework
double average(const std::vector<double>& a, const int& la)
{
	double sum = 0;
	for (int i = 0; i < la; ++i)
	{
		sum += a[i];
	}

	return sum/la;
}

// read single student info
std::istream& read_student_info(std::istream& is, student& stdnt)
{

	display_message("Enter new student's info (Last name, midterm grade, finals grade, grades for homework, terminate input with Ctrl + Z: ");
	double midterm;
	double finals;

	std::cin >> stdnt.name >> midterm >> finals;

	std::vector<double> homework;

	if (is)
	{

		double grade;

		while (std::cin >> grade)
		{
			homework.push_back(grade);
		}

		std::cin.clear();
	}

	typedef std::vector<double>::size_type vec_size;
	vec_size s = homework.size();

	double average_grade;
		
	if (s == 0)
	{
		average_grade = 0;
	}
	else 
	{
		average_grade = average(homework, s);
	}

	stdnt.final_grade = 0.4 * finals + 0.4 * midterm + 0.2 * average_grade;

	return is;
}

// comparator to sort alphabetically 
bool compare_names(const student& x, const student& y)
{
	return x.name < y.name;
}

// fancy 'passed' header
void display_passed()
{
	std::cout << "**********" << std::endl;
	std::cout << "* PASSED *" << std::endl;
	std::cout << "**********" << std::endl;
}

// fancy 'failed' header
void display_failed()
{
	std::cout << "**********" << std::endl;
	std::cout << "* FAILED *" << std::endl;
	std::cout << "**********" << std::endl;
}

// print student names along with their grades
void print_students(std::list<student>& a, const int& max_len)
{

	for (std::list<student>::iterator iter = a.begin(); iter != a.end(); ++iter)
	{
		std::cout << iter->name << std::string(max_len + 1 - iter->name.size(), ' ');		
		std::cout << iter->final_grade << std::endl;
	}

}

// evaluate student for passing the course
std::list<student> eval_class(std::list<student> &all, double &pass)
{
	std::list<student> failed;
	std::list<student>::iterator iter = all.begin();

	while(iter != all.end())
		{
		if (iter->final_grade < pass)
		{
			failed.push_back(*iter);
			iter=all.erase(iter);
		}
		else
			++iter;
	}

	return failed;
}

int main()
{
	
	student new_student;											// create new student
	std::list<student> new_class;									// create new class of students
	std::string::size_type max_len = 0;

	while (read_student_info(std::cin, new_student))
	{
		max_len = std::max(new_student.name.size(), max_len);		// determine the longest name in class
		new_class.push_back(new_student);							// store new student in new class
	}

	std::cin.clear();
	
	new_class.sort(compare_names);									// sort alphabetically

	// print_students(new_class, max_len);
	double pass_grade;												// define passing grade and prompt for it

	display_message("Enter passing grade: ");
	std::cin >> pass_grade;

	assert(pass_grade >= 0);										// passing grade is only positive

	std::list<student> failed = eval_class(new_class, pass_grade);	// evaluate students for passing

	display_passed();
	print_students(new_class, max_len);

	std::cout << std::endl;

	display_failed();
	print_students(failed, max_len);

	return 0;
}