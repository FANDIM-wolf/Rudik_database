#pragma once
#include "CData.h"
#include <vector>
#include <utility>
#include <string>
#include <fstream>
/*
Functions to  mantain  correct work of database

*/

std::string remove_spaces(std::string var) {
	std::string accurate_name;

	for (int i = 0; i <= var.size(); i++) {
		if (int(var[i]) != 32) {
			accurate_name += var[i];
		}
	}

	return accurate_name;
}


std::vector<Data> read_objects(std::string filename) {
	std::vector<Data> objects;
	std::ifstream file(filename);

	if (!file) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return objects;
	}

	std::string key, value;
	while (file >> key >> value) {
		objects.push_back({ key, value });
	}

	file.close();
	return objects;
}

void write_object(Data obj, std::string filename) {
	std::ofstream file(filename, std::ios_base::app);

	if (!file) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}

	file << obj.key << " " << obj.value << std::endl;

	file.close();
}

std::string find_value_by_key(std::vector<Data> objects, std::string key) {
	std::string key_instance;
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i].key == key) {
			return objects[i].value;
		}
	}
	return "34^8";
}

void print_all_values(std::vector<Data> objects, std::string key) {
	for (const auto& obj : objects) {
		std::cout <<"value" << obj.value << std::endl;
	}
	
}


std::string remove_extra_symbols(std::string s, std::string chars) {
	for (char c : chars) {
		s.erase(remove(s.begin(), s.end(), c), s.end());
	}
	return s;
}

void removeKeyValue(std::vector<Data> vec, std::string key, std::string value) {
	auto it = std::find_if(vec.begin(), vec.end(), [key, value](Data obj) {
		return obj.key == key && obj.value == value;
		});
	if (it != vec.end()) {
		vec.erase(it);
	}
}

void remove_file_data(std::string filename) {
	std::ofstream file;
	try {
		// Open the file in write mode to remove all data
		file.open(filename, std::ofstream::out | std::ofstream::trunc);
		file.close();
		
	}
	catch (std::exception const& e) {
		std::cerr << "An error occurred while removing data from " << filename << ": " << e.what() << std::endl;
	}
}
