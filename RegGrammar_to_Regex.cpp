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

string proccess_grammar(multimap<char, pair<string, char>>& grammar, char start, map<char, int>& last_use)
{
	static string res;
	//char sec_var;
	bool flag = false;
	int repeat;
	if (start == NULL) return res;
	auto itr = grammar.find(start);
	repeat = grammar.count(start);
	if (itr->second.first == "@") return res;
	last_use[start] = res.size();
	res += itr->second.first;
	if (start == itr->second.second)
	{
		res.insert(res.begin() + last_use[start], 1, '(');
		res += ")*";
		flag = true;
	}
	else proccess_grammar(grammar, itr->second.second, last_use);
	if (repeat > 2)
	{
		last_use[start] = res.size();
		res += "(";
	}
	for (int i = 1; i < repeat; i++)
	{
		//sec_var = itr->first;
		itr++;
		if (itr->second.first != "@")
		{
			if (i != 1) res += "+";
			/*if (!flag)
			{
				res.insert(res.begin() + last_use[start], 1, '(');
				res += '+';
				last_use[start] = res.size() - 2;
			}
			else last_use[start] = res.size();*/
			res += itr->second.first;
			proccess_grammar(grammar, itr->second.second, last_use);
		}
	}
	if (repeat > 2) res += ')';
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
	entry = proccess_grammar(grammar, 'S', last_use);
	cout << entry;
	return 0;
}