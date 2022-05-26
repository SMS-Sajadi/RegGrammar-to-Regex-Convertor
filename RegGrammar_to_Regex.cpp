#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;

void init_last_use(map<char, int>& a, multimap<char, pair<string, char>> grammar)
{
	for (auto x : grammar) a.insert(make_pair(x.first, -1));
}

void remove_trap(multimap<char, pair<string, char>>& grammar)
{
	vector< multimap<char, pair<string, char>>::iterator> temp;
	bool flag = true;
	int cnt;
	while (flag)
	{
		cnt = 0;
		for (auto itr = grammar.begin(); itr != grammar.end(); itr++)
		{
			if (grammar.find(itr->second.second) == grammar.end() && itr->second.second != NULL)
			{
				temp.push_back(itr);
				cnt++;
			}
		}
		if (cnt == 0) flag = false;
		else flag == true;
		for (auto x : temp) grammar.erase(x);
		temp.clear();
	}
}

string proccess_grammar(multimap<char, pair<string, char>>& grammar, char start)
{
	static string res;
	auto itr = grammar.find(start);
	res += itr->second.first;
	return res;
}

int main()
{
	multimap<char, pair<string, char>> grammar;
	map<char, int> last_use;
	string entry;
	while (cin >> entry)
	{
		if (entry == "~") break;
		if (isupper(entry[entry.size() - 1]))
		{
			grammar.insert(make_pair(entry[0], make_pair(entry.substr(2, entry.size() - 3), entry[entry.size() - 1])));
		}
		else
		{
			grammar.insert(make_pair(entry[0], make_pair(entry.substr(2, entry.size()), NULL)));
		}
	}
	remove_trap(grammar);
	init_last_use(last_use, grammar);
	entry = proccess_grammar(grammar, 'S');
	cout << entry;
	return 0;
}