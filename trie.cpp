#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;

class Node
{
public:

	string val;
	int len;

	vector<Node*> children;

	Node(string x)
	{
		val = x;
		len = val.size();
	}

};

class Trie
{

public:

	Node* head;
	int cnt;

	Trie()
	{
		head = new Node("");
		head->children.resize(0);
		cnt = 0;
	}

	/* INSERT */
	int findMatch(string rootVal, string input)
	{
		int i = 0;

		for (; i < min(rootVal.size(), input.size()); i++)
			if (rootVal.at(i) != input.at(i))
				return i;

		if (i == input.size()) return -1;

		return rootVal.size();

	}

	int insert(string x)
	{
		return insert(head, x);
	}

	int insert(Node *&root, string x)
	{
		int repeat = findMatch(root->val, x);

		if (repeat == -1) return 0;
		else if (repeat == root->val.size())
		{
			if (root->children.size() == 0 && root->val.size() > 0)
			{
				root->val += x.substr(repeat);
				root->len += x.substr(repeat).size();
				return x.substr(repeat).size();
			}
			
			for (int i = 0; i < root->children.size(); i++)
				if (x.at(repeat) == root->children[i]->val.at(0))
				{
					int l = insert(root->children[i], x.substr(repeat));
					root->len += l;
					return l;
				} 

			root->len += x.substr(repeat).size();
			root->children.pb(new Node(x.substr(repeat)));

			return x.substr(repeat).size();
		}
		else
		{
			Node* temp = new Node("");
			temp->val = root->val.substr(repeat); //take other part of root val

			temp->children = root->children; //shift tree
			temp->len = root->len - x.substr(0, repeat).size();

			root->children.resize(0);

			root->children.pb(temp);
			root->children.pb(new Node(x.substr(repeat)));

			root->val = x.substr(0, repeat);
			root->len = temp->len + root->val.size() + x.substr(repeat).size();

			return x.substr(repeat).size();
		}
	}

	/* SORTING */
	static bool cmp(Node* r1, Node* r2)
	{
		string s1 = r1->val, s2 = r2->val;

		return s1.compare(s2) < 0;
	}

	void sortChildren()
	{
		sortChildren(head);
	}

	void sortChildren(Node*& root)
	{
		sort(root->children.begin(), root->children.end(), cmp);

		for (int i = 0; i < root->children.size(); i++)
			sortChildren(root->children[i]);
	}

	/* i-th element */
	void ith_element(int x)
	{
		ith_element(head, x);
	}

	void ith_element(Node*& root, int x)
	{
		int next = root->val.size();

		if (x <= root->val.size())
		{
			cout << root->val.substr(0, x) << endl;
			return;
		}

		for (int i = 0; i < root->children.size(); i++)
		{
			next += root->children[i]->len;

			if (next >= x)
			{
				next -= root->children[i]->len;
				cout << root->val;
				ith_element(root->children[i], x - next);
				return;
			}
		}
	}

	/* PRINT TREE */

	void printTree()
	{
		printTree(head);
	}

	void printTree(Node *&root)
	{
		cout << "PARENT = " << root->val << endl;

		for (int i = 0; i < root->children.size(); i++)
			cout << i + 1 << ": " << root->children[i]->val << endl;

		for (int i = 0; i < root->children.size(); i++)
			printTree(root->children[i]);

	}

	bool isSuffix(Node*& root, string s)
	{
		if (root->children.size() == 0)
		{
			if (s.size() > root->val.size()) 
				return false;
			
			return 0 == root->val.compare(root->val.size() - s.size(), s.size(), s);
		}

		for (int i = 0; i < root->children.size(); i++)
			if (isSuffix(root->children[i], s)) return true;

		return false;
	}

	void printTree_v2(int len)
	{
		printTree_v2(head, len);
	}

	void printTree_v2(Node *&root, int len)
	{
		if(isSuffix(head, root->val) && root != head)
			cout << len - root->val.size() << endl;

		for (int i = 0; i < root->children.size(); i++)
			printTree_v2(root->children[i], len - root->val.size());
	}


	/* LONGEST COMMONG SUBSTRING */

	string LCS(string s)
	{
		string ans = "";
		string temp;

		for (int i = 0; i < s.size(); i++)
		{
			if (s.substr(i).size() <= ans.size()) break;

			temp = LCS(head, s.substr(i));

			if (temp == "") continue;
			if (temp.size() > ans.size()) ans = temp;
		}

		cout << ans << endl;

		return ans;
	}

	string LCS(Node *&root, string s)
	{
		int m = findMatch(root->val, s);

		if (m == -1) return s;
		if (m == 0 && root->val.size() > 0) return "";

		if(m == root->val.size())
			for (int i = 0; i < root->children.size(); i++)
				if (s.at(m) == root->children[i]->val.at(0))
					return s.substr(0, m) + LCS(root->children[i], s.substr(m));

		return s.substr(0, m);
	}


	/* CHECK IF GIVEN STRING IS SUBSTR OF TRIE */
	int isSubStr(string s)
	{
		return isSubStr(head, s);
	}

	int isSubStr(Node *&root, string s)
	{

		if (s.size() == 0) return 1;

		int m = findMatch(root->val, s);

		if (m == -1) return 1;
		if (m == 0 && root->val.size() > 0) return 0;

		for (int i = 0; i < root->children.size(); i++)
			if (s.at(m) == root->children[i]->val.at(0))
				return isSubStr(root->children[i], s.substr(m));


		return 0;
	}


	/* NUMBER OF DISTINCT SUBSTRINGS */
	/*
	int countSubStr(char x)
	{
		for (int i = 0; i < head->children.size(); i++)
			if (head->children[i]->val.at(0) == x)
				return head->children[i]->len;

		return 0;
	}

	int countSubStr(Node *&root)
	{
		return root->val.size() + getChildren(root);
	}

	int getChildren(Node*& root)
	{

		int sum = 0;
		for (int i = 0; i < root->children.size(); i++)
			sum += countSubStr(root->children[i]);

		return sum;
	}
	*/
};

int main()
{
	ll n, q;

	string txt, s;

	getline(cin, txt);

	Trie t;

	for (int i = txt.size() - 1; i >= 0; i--)
		t.insert(txt.substr(i));

	cin >> n;

	cin.ignore(10, '\n');
	
	while (n--)
	{
		getline(cin, s);

		if (t.isSubStr(s)) cout << "Y" << endl;
		else cout << "N" << endl;
	}
	
	return 0;
}
