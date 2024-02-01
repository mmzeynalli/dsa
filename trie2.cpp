#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair

typedef long long ll;

class Node
{
public:

    string val;

    vector<Node*> children;

    Node(string x)
    {
        val = x;
    }

};

class Trie
{

public:

    Node *head;
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

        for(; i < min(rootVal.size(), input.size()); i++)
            if(rootVal.at(i) != input.at(i))
                return i;

        if(i == input.size()) return -1;

        return rootVal.size();

    }

    void insert(string x)
    {
        insert(head, x);
    }

    void insert (Node *&root, string x)
    {
        int repeat = findMatch(root->val, x);

        if(repeat == -1) return;
        else if(repeat == root->val.size())
        {
            if(root->children.size() == 0 && root->val.size() > 0)
            {
                root->val += x.substr(repeat);
                return;
            }

            for(int i = 0; i < root->children.size(); i++)
                if(x.at(repeat) == root->children[i]->val.at(0))
                {
                    insert(root->children[i], x.substr(repeat));
                    return;
                }

            root->children.pb(new Node(x));
        }
        else
        {
            Node* temp = new Node("");
            temp->val = root->val.substr(repeat); //take other part of root val

            temp->children = root->children; //shift tree

            root->children.resize(0);

            root->children.pb(temp);

            root->children.pb(new Node(x.substr(repeat)));

            root->val = x.substr(0, repeat);
        }
    }

    /* PRINT TREE */

    void printTree()
    {
        printTree(head);
    }

    void printTree(Node *&root)
    {
        cout << "PARENT = " << root->val <<endl;

        for(int i = 0; i < root->children.size(); i++)
            cout << i + 1 << ": " << root->children[i]->val << endl;

        for(int i = 0; i < root->children.size(); i++)
            printTree(root->children[i]);

    }


    /* LONGEST COMMONG SUBSTRING */

    vector<string> LCS(string s)
    {
        vector <string> v(1, "");
        string temp;

        for(int i = s.size() - 1; i >= 0; i--)
        {
            temp = LCS(head, s.substr(i));

            //cout << temp << endl;
            //cout << ans << endl;

            if(temp == "") continue;
            if(temp.size() > v[0].size())
            {
                v.resize(0);
                v.pb(temp);
            }
            else if(temp.size() == v[0].size())
                v.pb(temp);

        }

        if(v[0] == "") v[0] = "No common sequence.";

        sort(v.begin(), v.end());

        return v;
    }

    string LCS(Node *&root, string s)
    {
        int m = findMatch(root->val, s);

        if(m == -1) return s;
        if(m == 0 && root->val.size() > 0) return "";

        for(int i = 0; i < root->children.size(); i++)
            if(s.at(m) == root->children[i]->val.at(0))
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

        if(s.size() == 0) return 1;

        int m = findMatch(root->val, s);


        if(m == -1) return 1;
        if(m == 0 && root->val.size() > 0) return 0;

        for(int i = 0; i < root->children.size(); i++)
            if(s.at(m) == root->children[i]->val.at(0))
                return isSubStr(root->children[i], s.substr(m));


        return 0;
    }


    /* NUMBER OF DISTINCT SUBSTRINGS */

    int countSubStr(char x)
    {
        for(int i = 0; i < head->children.size(); i++)
            if(head->children[i]->val.at(0) == x)
                return countSubStr(head->children[i]);

        return 0;
    }

    int countSubStr(Node *&root)
    {
        return root->val.size() + getChildren(root);
    }

    int getChildren(Node*& root)
    {

        int sum = 0;
        for(int i = 0; i < root->children.size(); i++)
             sum += countSubStr(root->children[i]);

        return sum;
    }
};

int main()
{
    Trie t;

    string s;

    cin >> s;

    for(int i = s.size() - 1; i >= 0; i--)
        t.insert(s.substr(i));

    t.printTree();

    for(int i = 0; i < 26; i++)
        cout << t.countSubStr('a' + i) << ' ';

    return 0;
}
