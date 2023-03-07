#pragma once
#include "CData.h"

std::string remove_spaces(std::string var) {
	std::string accurate_name;

	for (int i = 0; i <= var.size(); i++) {
		if (int(var[i]) != 32) {
			accurate_name += var[i];
		}
	}

	return accurate_name;
}


//create data base , file contains list
void method_CREATE(std::string request_to_base, SOCKET sock_of_current_user) {

	int position_of_command_start = request_to_base.find("(");
	int position_of_command_end = request_to_base.find(")");
	std::string name_of_var = request_to_base.substr(position_of_command_start + 1, (position_of_command_end - position_of_command_start) - 1);
	//name_of_var = remove_spaces(name_of_var);//remove spaces
	std::cout << name_of_var << std::endl;
	std::string name_of_base = name_of_var;
	std::cout << "name of base" << name_of_base << std::endl;
	std::ofstream outfile;
	outfile.open(name_of_base + ".dat");

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
	name_of_var = remove_spaces(name_of_var);//remove spaces
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
	//remove spaces of data 
	name_of_key = remove_spaces(name_of_key);
	name_of_value = remove_spaces(name_of_value);
	std::cout << "key:  " << name_of_key <<"value :" <<name_of_value<< std::endl;
	// create object with key and value 
	Data data;
	data.key = name_of_key;
	data.value = name_of_value;
	// write down object in file
	std::ofstream file;
	file.open(path , std::ios::app );
	

	if (!file.is_open()) {
		std::string msgSent = "Database " + name_of_var + " was not open .";
		send(sock_of_current_user, msgSent.c_str(), msgSent.size() + 1, 0);

	}
	else {
		file.write((char*)&data, sizeof(Data));
		std::string msgSent =  "1";
		send(sock_of_current_user, msgSent.c_str(), msgSent.size() + 1, 0);
	}
	file.close();


	

}