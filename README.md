Crafted By-

1)Girish Kumar
2)Satyam Kumar 
3)Ashutosh Singh 



--- Welcome to Grocery Management System ---

To compile the code, use the following command:

g++ Suffix_tree.c PatternSearch.c main.cpp bloom.cpp BK_Tree.cpp

The project has two ends:

Buyer End:
- This is where the buyer enters their name.
- The buyer can list the items they need.
- Auto-correct feature is available, powered by BK-Tree.

Seller End:
- This is where the seller adds items to the inventory.
- The seller can search the order list and generate a full receipt.
- Features include a unique item list using a Bloom Filter and fast search using a Suffix Tree.

Warnings:
- After entering each item name as a buyer, press Enter.
- Avoid using item names that are subsets of each other.
- Ensure that names are between 1 and 99 characters in length.
