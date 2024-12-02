#include <bits/stdc++.h>
#include "BK_Tree.hpp" // Include the necessary header file
using namespace std;

BkNode rootNode; // Declare the root node of the BK-Tree
BkNode BK_Tree[BMAX]; // Declare an array to store BK-Tree nodes
int ptr; // Declare a pointer to keep track of the current node

// Function to create a new BK-Tree node with a given string
BkNode createNode(string s)
{
    BkNode n;
    n.word = s;
    for (int i = 0; i < 2 * LEN; i++)
        n.next[i] = 0;
    return n;
}

// Function to calculate the edit distance between two strings s1 and s2
int editDistance(string s1, string s2)
{
    int n = s1.length(), m = s2.length();
    int dp[n + 1][m + 1];

    // Initialize the dynamic programming matrix
    for (int i = 0; i <= n; i++)
        dp[i][0] = i;
    for (int i = 0; i <= m; i++)
        dp[0][i] = i;

    // Compute the edit distance using dynamic programming
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] != s2[j - 1])
            {
                dp[i][j] = min(1 + dp[i - 1][j], 1 + dp[i][j - 1]);
                dp[i][j] = min(dp[i][j], 1 + dp[i - 1][j - 1]);
            }
            else
                dp[i][j] = dp[i - 1][j - 1];
        }
    }
    return dp[n][m];
}

// Function to add a node to the BK-Tree
void addNode(BkNode &rootNode, BkNode &currentNode)
{
    if (rootNode.word == "")
    {
        rootNode = currentNode; // If the root node is empty, set it to the current node
        return;
    }

    int d = editDistance(rootNode.word, currentNode.word); // Calculate the edit distance
    if (BK_Tree[rootNode.next[d]].word == "")
    {
        ptr++;
        BK_Tree[ptr] = currentNode;
        rootNode.next[d] = ptr;
    }
    else
        addNode(BK_Tree[rootNode.next[d]], currentNode); // Recursively add the node
}

// Function to get similar words to a given string in the BK-Tree
vector<string> getSimilarWords(BkNode &rootNode, string s)
{
    vector<string> similarWords;
    if (rootNode.word == "")
        return similarWords;

    int d = editDistance(rootNode.word, s); // Calculate the edit distance
    if (d <= TOL)
        similarWords.push_back(rootNode.word);

    int x = max(0, d - TOL);
    while (x <= d + TOL)
    {
        vector<string> temp = getSimilarWords(BK_Tree[rootNode.next[x]], s); // Recursively search for similar words
        for (int i = 0; i < temp.size(); i++)
            similarWords.push_back(temp[i]);
        x++;
    }
    return similarWords;
}

// Function to return a pointer to the root node of the BK-Tree
BkNode* ReturnBNode(){
    return &rootNode;
}
