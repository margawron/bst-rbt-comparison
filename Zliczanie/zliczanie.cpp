
#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include <vector>
#include <string.h>

#include "binary_tree.h"
#include "binary_tree.cpp"
#include "Word.h"


void read_arguments(int argc, char * argv[], std::string & input_name, std::string & bst_output, std::string & rbt_output)	// funkcja odczytuj�ca argumenty z main'a 
{// �ancuch znak�w b�d� przekazywa�y dane po przez referencje(brak const)

	const std::string INPUT_LABEL = "-i";	// zmienne przechowywuj�ce etykiety plik�w
	const std::string BST_LABEL = "-bst";
	const std::string RBT_LABEL = "-rbt";
	for (int i = 1; i < argc; i++) {
		if (argv[i] == INPUT_LABEL)		// je�eli aktualny argument to etykieta grafu
			input_name = argv[i + 1];		// nast�pny argument to nazwa pliku z grafem(przekazane po przez referencje)
		if (argv[i] == BST_LABEL)		// je�eli aktualny argument to etykieta wez��w
			bst_output = argv[i + 1];		// kolejny argument to nazwa pliku z wezlami(przekazane po przez referencje)
		if (argv[i] == RBT_LABEL)	// je�eli aktualny argument to etykieta wyniki
			rbt_output = argv[i + 1];			// kolejny argument to nazwa pliku do kt�rego b�d� zapisywane wyniki
	}
	if (argc == 1 || input_name == "" || bst_output == "" || rbt_output == "")
	{
		std::cout << "Parametry" << "\n";
		std::cout << "-i [nazwa pliku wejsciowego]" << "\n";
		std::cout << "-bst [nazwa pliku wyjsciowego z drzewa binarnego]" << "\n";
		std::cout << "-rbt [nazwa pliku wyjsciowego z drzewa czerwono-czarnego]" << "\n";
		std::cout << "Przykladowe uzycie :" << "\n";
		std::cout << "<program> -g input.txt -bst bst_output.txt -rbt rbt_output.txt" << "\n";
	}
}



std::string sanitize(const std::string & text)
{
	std::string tmp;
	for (char f : text)
	{
		if (f >= 65 && f <= 90)
		{
			tmp.push_back(f + ' ');
		}
		else if ((f >= 97 && f < 122) || f == 45)
		{
			tmp.push_back(f);
		}
	}
	return tmp;
}



int main(int argc, char *argv[])
{
	std::string input_file_name, bst_output_filename, rbt_output_filename;
	read_arguments(argc, argv, input_file_name, bst_output_filename, rbt_output_filename);

	binary_tree<Word> bst{};
	unsigned int words = 0;

	std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>> clocks;

	std::fstream input_file_bst(input_file_name, std::ios::in);
	if (input_file_bst.good())
	{
		std::string in;
		auto timer1_before = std::chrono::high_resolution_clock::now();
		while (input_file_bst >> in)
		{
			std::string tmp = sanitize(in);
			if (tmp.empty())
				continue;
			clocks.push_back(std::chrono::high_resolution_clock::now());
			auto return_val = bst.insert(Word(tmp));
			clocks.push_back(std::chrono::high_resolution_clock::now());

			return_val->data++;
			words++;
		}
		auto timer1_after = std::chrono::high_resolution_clock::now();
		std::cout << "Elapsed time in miliseconds " << std::chrono::duration_cast<std::chrono::milliseconds>(timer1_after - timer1_before).count() << "\n";
		input_file_bst.close();
	}

	long long bst_insertion_only_nanoseconds = 0;
	long long longest_insertion_time = 0;
	for (int i = 0; i < clocks.size(); i += 2)
	{
		auto insertion_time = std::chrono::duration_cast<std::chrono::nanoseconds>(clocks[i + 1] - clocks[i]).count();
		bst_insertion_only_nanoseconds += insertion_time;
		if (longest_insertion_time < insertion_time)
			longest_insertion_time = insertion_time;
	}
	if (words!=0){
		std::cout << "Average time of insertion into implemented binary search tree is " << bst_insertion_only_nanoseconds / words << " nanoseconds\n";
	}
	std::cout << "Longest insertion time in binary search tree is " << longest_insertion_time << " nanoseconds \\ " << longest_insertion_time / 1000000 << " miliseconds\n";
	clocks.clear();


	std::fstream output_bst(bst_output_filename, std::ios::out);
	if (output_bst.good())
	{
		output_bst << "Found " << words << " words.\n";
		bst.output_tree(output_bst);
		output_bst.close();
	}


	std::fstream input_file_rbt(input_file_name, std::ios::in);
	words = 0;


	std::map<std::string, int> red_black_tree{};
	if (input_file_rbt.good())
	{
		std::string in;
		auto timer2_before = std::chrono::high_resolution_clock::now();

		while (input_file_rbt >> in)
		{
			std::string tmp = sanitize(in);
			if (tmp.empty())
				continue;
			clocks.push_back(std::chrono::high_resolution_clock::now());
			red_black_tree[tmp]++;
			clocks.push_back(std::chrono::high_resolution_clock::now());
			words++;
		}
		auto timer2_after = std::chrono::high_resolution_clock::now();
		std::cout << "Elapsed time in miliseconds " << std::chrono::duration_cast<std::chrono::milliseconds>(timer2_after - timer2_before).count() << "\n";
		input_file_rbt.close();
	}

	long long rbt_insertion_only_nanoseconds = 0;
	longest_insertion_time = 0;
	for (int i = 0; i < clocks.size(); i += 2)
	{
		auto insertion_time = std::chrono::duration_cast<std::chrono::nanoseconds>(clocks[i + 1] - clocks[i]).count();
		rbt_insertion_only_nanoseconds += insertion_time;
		if (longest_insertion_time < insertion_time)
			longest_insertion_time = insertion_time;
	}
	if (words!=0){
		std::cout << "Average time of insertion into implemented red black tree is " << rbt_insertion_only_nanoseconds / words << " nanoseconds\n";
	}
	std::cout << "Longest insertion time in red black tree is " << longest_insertion_time << " nanoseconds \\ " << longest_insertion_time / 1000000 << " miliseconds\n" ;
	clocks.clear();
	clocks.shrink_to_fit();

	std::fstream output_rbt(rbt_output_filename, std::ios::out);
	if (output_rbt.good())
	{
		output_rbt << "Found " << words << " words\n";
		for (const auto & f : red_black_tree)
		{
			output_rbt << f.first << " : " << f.second << "\n";
		}
		output_rbt.close();
	}


	return 0;
}