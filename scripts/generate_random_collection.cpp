// Copyright 2012 Francisco Claude. All Rights Reserved.

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

void save_file(string dir, int id, char *content, int len) {
	char *path = new char[dir.length() + 100];
	sprintf(path, "%s/%06d.txt", dir.c_str(), id);
	ofstream out(path);
	out.write(content, len);
	out.close();
}

int main(int argc, char **argv) {
	if (argc != 6) {
		cout << "usage: " << argv[0] << " <alphabet> <length base> <reps> <edits> <output folder>" << endl;
		return 0;
	}
	string alphabet = string(argv[1]);
	int len_base = atoi(argv[2]);
	int reps = atoi(argv[3]);
	int edits = atoi(argv[4]);
	string out_folder = string(argv[5]);

	int id = 0;
	srand(time(NULL));
	char *base = new char[len_base];
	for (int i = 0; i < len_base; i++) {
		base[i] = alphabet[rand() % alphabet.length()];
	}
	save_file(out_folder, id, base, len_base);
	id++;

	char *new_text = new char[len_base];
	for (int j = 0; j < reps; j++) {
		for (int i = 0; i < len_base; i++)
			new_text[i] = base[i];
		for (int i = 0; i < edits; i++) {
			int pos = rand() % len_base;
			while (new_text[pos] == base[pos]) {
				new_text[pos] = alphabet[rand() % alphabet.length()];
			}
		}
		save_file(out_folder, id, new_text, len_base);
		id++;
	}
	delete [] new_text;
	delete [] base;
	return 0;
}