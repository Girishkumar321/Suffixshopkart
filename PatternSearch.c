#include "Suffix_tree.h"
#include "PatternSearch.h"
#include <stdio.h>

int* test2; // Pointer to store results
int ind = 0; // Index for tracking results

// Function to traverse an edge in the suffix tree and compare it with a given string
int traverseEdge(char *str, int idx, int start, int end, char* text)
{
    int k = 0;
    for (k = start; k <= end && str[idx] != '\0'; k++, idx++)
    {
        if (text[k] != str[idx])
            return -1; // Mismatch, return -1
    }
    if (str[idx] == '\0')
        return 1; // Exact match, return 1
    return 0; // Partial match, return 0
}

// Function to perform a recursive traversal to count leaf nodes in the suffix tree
int doTraversalToCountLeaf(SNode *n)
{
    if (n == NULL)
        return 0;
    if (n->suffixIndex > -1)
    {
        test2[ind++] = n->suffixIndex; // Store the suffix index in the results array
        return 1;
    }
    int count = 0;
    int i = 0;
    for (i = 0; i < MAX; i++)
    {
        if (n->children[i] != NULL)
        {
            count += doTraversalToCountLeaf(n->children[i]);
        }
    }
    return count;
}

// Function to count the number of leaf nodes in the suffix tree
int countLeaf(SNode *n)
{
    if (n == NULL)
        return 0;
    return doTraversalToCountLeaf(n);
}

// Function to perform a recursive traversal in the suffix tree to search for a string
int doTraversal(SNode *n, char* str, int idx, char* text)
{
    if (n == NULL)
    {
        return -1; // No match, return -1
    }
    int res = -1;
    if (n->start != -1)
    {
        res = traverseEdge(str, idx, n->start, *(n->end), text); // Compare the edge with the string
        if (res == -1)
            return -1; // Mismatch, return -1
        if (res == 1) 
        {
            if (n->suffixIndex > -1)
            {
                printf("\nOrder count: 1"); // Suffix found, print order count
                test2[ind++] = n->suffixIndex;
            }
            else
                printf("\nOrder count: %d", countLeaf(n)); // Count and print the number of leaf nodes
            return 1;
        }
    }
    idx = idx + edgeLength(n);
    if (n->children[str[idx]] != NULL)
        return doTraversal(n->children[str[idx]], str, idx, text);
    else
        return -1; // No match
}

// Function to check for a substring in the suffix tree and store the results
void checkForSubString(char* str, SNode* root, char* text, int* pos)
{
    test2 = pos; // Set the results array
    int res = doTraversal(root, str, 0, text); // Search for the substring
    test2[ind] = -1; // Mark the end of the results
    if (res == 1){
        ind = 0; // Reset the results index
    }
    else{
        printf("\n%s is NOT ordered yet\n", str); // String not found in the tree
    }
}
