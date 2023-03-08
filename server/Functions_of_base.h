#pragma once
#include "CData.h"
#include <vector>
#include "Tool_functions.h"
#include <utility>
#include <sstream>
#include <string>

//create data base , file contains list
void method_CREATE(std::string request_to_base, SOCKET sock_of_current_user) {

	int position_of_command_start = request_to_base.find("(");
	int position_of_command_end = request_to_base.find(")");
	std::string name_of_var = request_to_base.substr(position_of_command_start + 1, (position_of_command_end - position_of_command_start) - 1);
	std::string chars = "() ,";
	name_of_var = remove_extra_symbols(name_of_var ,chars);//remove spaces
	std::cout << name_of_var << std::endl;
	std::string name_of_base = name_of_var;
	std::cout << "name of base" << name_of_base << std::endl;
	std::ofstream outfile;
	outfile.open(name_of_base + ".txt");

	//outfile << "my text here!" << std::endl;
	
	outfile.close();
	std::string msgSent = "Database " + name_of_var + " was created .";
	send(sock_of_current_user, msgSent.c_str(), msgSent.size() + 1, 0);

}

// put object in method 
void method_SET(std::string request_to_base, SOCKET sock_of_current_user) {

	int counter_of_commas = 0;
	std::string  name_of_key, name_of_value;
	//carve name of base
	int position_of_command_start = request_to_base.find("(");
	int position_of_command_end = request_to_base.find(",");
	std::string name_of_var = request_to_base.substr(position_of_command_start + 1, (position_of_command_end - position_of_command_start) - 1);
	std::string chars = "() ,";
	name_of_var = remove_extra_symbols(name_of_var,chars);//remove spaces
	std::cout <<"Name of base: " << name_of_var << std::endl;
	std::string path = name_of_var+".txt";
	//***
	// carve name of key and value
	for (int i = 0; i <= request_to_base.size(); i++) {
		if (request_to_base[i] == ',')
		{
			counter_of_commas++;
		}
		if (counter_of_commas == 1 && ( request_to_base[i] != '(' || request_to_base[i] != '=' || request_to_base[i] != ')' || request_to_base[i] != ';' || request_to_base[i] != ',' )) {
			name_of_key += request_to_base[i];
		}
		if (counter_of_commas == 2 && (request_to_base[i] != '(' || request_to_base[i] != '=' || request_to_base[i] != ')' || request_to_base[i] != ';' || request_to_base[i] != ',' )) {
			name_of_value += request_to_base[i];
		}
	}
	

	//***
	
	//remove extra symbols in value and key 
	name_of_key = remove_extra_symbols(name_of_key , chars);
	name_of_value = remove_extra_symbols(name_of_value , chars);

	std::cout << "key:  " << name_of_key <<"value :" <<name_of_value<< std::endl;
	// create object with key and value 
	Data data;
	data.key = name_of_key;
	data.value = name_of_value;
	// write down object in file
	write_object(data, path);


	

}


// put object in method 
void method_GET(std::string request_to_base, SOCKET sock_of_current_user) {

	int counter_of_commas = 0;
	// current_key and current_value are needed for further loop
	std::string  name_of_key, name_of_value , current_key , current_value; 
	//carve name of base
	int position_of_command_start = request_to_base.find("(");
	int position_of_command_end = request_to_base.find(",");
	std::string name_of_var = request_to_base.substr(position_of_command_start + 1, (position_of_command_end - position_of_command_start) - 1);
	std::string chars = "() ,";
	name_of_var = remove_extra_symbols(name_of_var , chars);//remove spaces
	std::cout << "Name of base: " << name_of_var << std::endl;
	std::string path = name_of_var + ".txt";
	//***
	// carve name of key and value
	//for (int i = 0; i <= request_to_base.size(); i++) {
	//	if (request_to_base[i] == ',')
	//	{
	//		counter_of_commas++;
	//	}
	//	if (counter_of_commas == 1 && (request_to_base[i] != '(' || request_to_base[i] != '=' || request_to_base[i] != ')' || request_to_base[i] != ';' || request_to_base[i] != ',')) {
	//		name_of_key += request_to_base[i];
	//	}
		
	//}
	
	std::stringstream ss(request_to_base);
	std::string token;

	// Splitting the string using the delimiter ',' and skipping the first value
	std::getline(ss, token, ',');
	std::getline(ss, token, ';');

	//***
	//remove spaces of data 
	
	name_of_key = token;
	
	name_of_key = remove_extra_symbols(name_of_key,chars);
	

	std::cout << "key:" << name_of_key  << std::endl;
	// create object with key and value 
	//Data data;
	//data.key = name_of_key;
	std::vector<Data> objects = read_objects(path);
	name_of_value = find_value_by_key(objects, name_of_key);
	print_all_values(objects, name_of_key);
	std::cout << "value: " << name_of_value << std::endl;
	
	send(sock_of_current_user, name_of_value.c_str(), name_of_value.size() + 1, 0);
	




}