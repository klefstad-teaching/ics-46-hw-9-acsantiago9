#include "ladder.h"

void error(string word1, string word2, string msg) {
	cout << "Error: " << word1 << msg << word2 << endl;
}

bool edit_distance_within(const std::string &str1, const std::string &str2, int d) {

	if (str1 == str2)
		return 1;
	
	int str1_len = str1.size();
	int str2_len = str2.size();

	if (abs(str1_len - str2_len) > d)
		return 0;

	vector<int> prev(str2_len + 1, 0);
	vector<int> curr(str2_len + 1, 0);

	for (int i = 0; i <= str2_len; ++i) {
		prev[i] = i;
	}

	for (int i = 1; i <= str1_len; ++i) {
		curr[0] = i;
		for (int j = 1; j <= str2_len; ++j) {
			if (str1[i - 1] == str2[j - 1])
				curr[j] = prev[j - 1];
			else {
				int prev_min = min(prev[j], prev[j - 1]);
				curr[j] = 1 + min(curr[j - 1], prev_min);
			}
		}
		prev = curr;
	}
    return curr[str2_len] <= d;
}

bool is_adjacent(const string &word1, const string& word2) {
	return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string &end_word, const set<string> &word_list) {
	if (begin_word != end_word && find(word_list.begin(), word_list.end(), end_word) != word_list.end()) {
		queue<vector<string>> ladder_queue;
		set<string> visited;
		ladder_queue.push({begin_word});
		visited.insert(begin_word);
		while (!ladder_queue.empty()) {
			vector<string> ladder = ladder_queue.front();
			ladder_queue.pop();
			string last_word = ladder.back();
			for (string word : word_list) {
				if (visited.count(word) == 0 && is_adjacent(last_word, word)) {
					visited.insert(word);
					vector<string> new_ladder = ladder;
					new_ladder.push_back(word);
					if (word == end_word) {
						return new_ladder;
					}
					ladder_queue.push(new_ladder);
				}
			}
		}
	}
	return vector<string>();
}

void load_words(set<string> &word_list, const string &file_name) {
	ifstream file(file_name);
	if (file.is_open()) {
		for (string s; file >> s;)
			word_list.insert(s);
	} else
		cout << "Error: file is not accessed" << endl;
}

void print_word_ladder(const vector<string> &ladder) {
	if (ladder.size() > 0) {
		cout << "Word ladder found: ";
		for (string s : ladder)
			cout << s << " ";
	}
	else
		cout << "No word ladder found.";
	cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
	my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
	my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}