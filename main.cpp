//
// Project 4
// Created by Gabe Scott on 2019-03-27.
//

#include <iostream>
using namespace std;

class Tree
{
    friend void operator<< (ostream& s, Tree& t);         //prints parent array
protected:
    int* parentArray;
    int size;
    int root;
    
public:
    Tree();                     // Default Constructor
    Tree(int numNodes);         // Non-Default const
    Tree(Tree& data);         // copy const
    ~Tree();                    // destructor
    void LCA(int a, int b);          // Least common Ancestor
    int Parent(int node);           // Get the parents of node i
    void Children(int node);        // Prints as well as returns an array.
    int* ChildrenArray(int node);   // Same as Children() but returns an array instead of prints
    void Siblings(int node);            // get the siblings of node i
    void Root();                     // get the root of the tree
    void setRoot(int rootNode);
    void setParent(int node, int parent);
    void nodesAtLevel(int level);        // give the nodes at level i
    void Level(int node);               // print the level of node i
    int returnLevel(int node);       // same as Level() but returns an int instead of void. I use this is LCA().
    void height();                   // print the height of the tree
    void Preorder();                 // give the preorder traversal of the tree
    void Preorder(int node);
};

Tree::Tree()                        // default constructor
{
    parentArray = new int[0];
    size = 0;
    root = -1;
}

Tree::Tree(int numNodes)            // Non default constructor
{
    parentArray = new int[numNodes];
    size = numNodes;
}

Tree::Tree(Tree& data)            // Copy constructor
{
    parentArray = new int[data.size];
    size = data.size;
    root = data.root;
    
    // iterate through parentArray and copy each element over
    for (int i=0; i<data.size; i++)
    {
        parentArray[i] = data.parentArray[i];
    }
}

Tree::~Tree()                   // destructor
{
    if (parentArray != NULL)
        delete[] parentArray;
    parentArray = NULL;
    size = 0;
    //root = NULL;
}

int Tree::Parent(int node)          // returns the parent of a given node
{
    return parentArray[node];
}

void Tree::Children(int node)       // Method prints children of a given node.
{
    for (int i=0; i<size; i++)
    {
        if (parentArray[i] == node)
        {
            cout << i << "  ";
        }
    }
    cout << endl;
}

int* Tree::ChildrenArray(int node)    //Method is same as Children() except that it returns an array and doesn't print
{
    // create an array of children that will have -1 if not a child and a different value if a valid child
    int* childrenArray = new int[size];
    for (int i=0; i < size; i++)
    {
        childrenArray[i] = -1;
    }
    
    // iterate through parent array and if it matches the input node, input it into the childrenArray
    for (int i=0; i<size; i++)
    {
        if (parentArray[i] == node)
        {
            childrenArray[i] = i;
        }
    }
    return childrenArray;
}

void Tree::Siblings(int node)           // prints the nodes at same level as input node
{
    int parent = Parent(node);
    for (int i=0; i<size; i++)
    {
        if (Parent(i) == parent && i != node)
        {
            cout << i << " ";
        }
    }
    cout << endl;
}

void Tree::Root()                   // returns Root of the tree
{
    for (int i=0; i<size; i++)
    {
        if (parentArray[i] == -1)
        {
            cout << i;
        }
    }
    cout << endl;
}

void Tree::nodesAtLevel(int level)          // Prints all nodes at any given level
{
    // create Array containing level of each Node
    int* nodeLevels = new int[size];
    // iterate through parentArray and get level of each node
    int lvlCounter= 0;
    int currNode = 0;
    for (int i=0; i<size; i++)
    {
        // start at node i in array
        currNode = i;
        // go through parent array from one node to the next, with the next being its parent. Stop when current node is -1 because we're at the root of the tree
        lvlCounter = 0;         // starting at 0 b/c it will add an extra count on the step from the root to -1
        while (currNode != -1)
        {
            currNode = parentArray[currNode];
            lvlCounter++;
            // the counter will be the level for the node we started on
        }
        // add level to Array containing the level of each node
        nodeLevels[i] = lvlCounter;
    }
    // now iterate through nodeLevels array and cout the nodes that have level of input
    for (int i=0; i<size; i++)
    {
        if (nodeLevels[i] == level)
        {
            cout << i << " ";
        }
    }
    cout << endl;
}

void Tree::Level(int node)              // Gives level of input node
{
    // create Array containing level of each Node
    int* nodeLevels = new int[size];
    // iterate through parentArray and get level of each node
    int lvlCounter= 0;
    int currNode = 0;
    for (int i=0; i<size; i++)
    {
        // start at node i in array
        currNode = i;
        // go through parent array from one node to the next, with the next being its parent. Stop when current node is -1 because we're at the root of the tree
        lvlCounter = 0;         // starting at 0 b/c it will add an extra count on the step from the root to -1
        while (currNode != -1)
        {
            currNode = parentArray[currNode];
            lvlCounter++;
            // the counter will be the level for the node we started on
        }
        // add level to Array containing the level of each node
        nodeLevels[i] = lvlCounter;
    }
    cout << nodeLevels[node] << endl;
}

int Tree::returnLevel(int node)     // This method is same as Level() but returns an int instead of void/cout. For use with method LCA()
{
        // create Array containing level of each Node
        int* nodeLevels = new int[size];
        // iterate through parentArray and get level of each node
        int lvlCounter= 0;
        int currNode = 0;
        for (int i=0; i<size; i++)
        {
            // start at node i in array
            currNode = i;
            // go through parent array from one node to the next, with the next being its parent. Stop when current node is -1 because we're at the root of the tree
            lvlCounter = 0;         // starting at 0 b/c it will add an extra count on the step from the root to -1
            while (currNode != -1)
            {
                currNode = parentArray[currNode];
                lvlCounter++;
                // the counter will be the level for the node we started on
            }
            // add level to Array containing the level of each node
            nodeLevels[i] = lvlCounter;
        }
        return nodeLevels[node];
}

// Prints height of the tree by creating an array that contains the level for each node. Then prints the highest of those levels.
void Tree::height()
{
    // create Array containing level of each Node
    int* nodeLevels = new int[size];
    // iterate through parentArray and get level of each node
    int lvlCounter= 0;
    int currNode = 0;
    for (int i=0; i<size; i++)
    {
        // start at node i in array
        currNode = i;
        // go through parent array from one node to the next, with the next being its parent. Stop when current node is -1 because we're at the root of the tree
        lvlCounter = 0;         // starting at 0 b/c it will add an extra count on the step from the root to -1
        while (currNode != -1)
        {
            currNode = parentArray[currNode];
            lvlCounter++;
            // the counter will be the level for the node we started on
        }
        // add level to Array containing the level of each node
        nodeLevels[i] = lvlCounter;
    }
    // Now go through nodeLevels array and find the maximum level. This will be the height of the tree.
    int maxLevel = 0;
    for (int i = 0; i<size; i++)
    {
        if (nodeLevels[i] > maxLevel)
        {
            maxLevel = nodeLevels[i];
        }
    }
    cout << maxLevel << endl;
}


void Tree::LCA(int a, int b)            // prints the least common ancestor of the two input nodes
{
    //if A == B print parent
    if (a == b)
    {
        cout << Parent(a) << endl;;
        return;
    }
    // lowest will be node with the highest level, or equal to highest level. (Lowest as in lower on the tree when looking at it)
    int lowest;
    int highest;
    if (returnLevel(a) >= returnLevel(b))
    {
        lowest = a;
        highest = b;
    }
    else
    {
        lowest = b;
        highest = a;
    }
    int ancestor = -1;
    // setting two new variables to lowest and highest so we can manipulate them without losing original lowest and highest
    int currLow = lowest;
    int currHigh = highest;
    // this will loop the number of times of the level of the highest of the two nodes
    for (int i=0; i<(returnLevel(highest)); i++)
    {
        // this will loop the number of times of the level of the lowest of the two nodes
        for (int j=0; j< ((returnLevel(lowest))); j++)
        {
            // resetting lowest on first iteration of for loop each time
            if (j == 0)
                currLow = lowest;
            // move currLow up the chain to its parent
            currLow = Parent(currLow);
            // if currLow matches currHigh, we've found our ancestor. set and break out of loop.
            if (currLow == currHigh)
            {
                ancestor = currLow;
                break;
            }
        }
        // if ancestor isn't -1, we already have it, break loop.
        if (ancestor != -1)
            break;
        else
        {
            // otherwise, move currHigh up the chain to its parent
            currHigh = Parent(currHigh);
        }
    }
    cout << ancestor << endl;
}

void operator<< (ostream& s, Tree& t)           // Overloaded ostream operator
{
    for (int i=0; i<t.size; i++)
    {
        cout << i << ": " << t.parentArray[i] << "  ";
    }
    cout << endl;
}

void Tree::setParent(int node, int parent)
{
    parentArray[node] = parent;
}

void Tree::setRoot(int rootNode)
{
    root = rootNode;
    parentArray[rootNode] = -1;
}


void Tree::Preorder()           //Preoder recursion. Prints root then Calls Preorder(node) on the root
{
    cout << root << " ";
    Preorder(root);
}

void Tree::Preorder(int node)       // Recursive function that prints nodes in preoder fashion
{
    //calls ChildrenArray on input node, then prints input node, then calls itself on that node
    int* childArray = ChildrenArray(node);
    for (int i=0; i<this->size; i++)
    {
        // if childArray value is not -1, print it then call this function again on that node
        if (childArray[i] != -1)
        {
            cout << childArray[i] << " ";
            Preorder(childArray[i]);
        }
    }
}

int main()
{
    Tree* myTree;
    int numNodes, node, parent;
    
    cin >> numNodes;
    myTree = new Tree(numNodes);
    for (int i=0; i<numNodes; i++)
    {
        cin >> node >> parent;
        (*myTree).setParent(node, parent);
        if (parent == -1)
        {
            (*myTree).setRoot(node);
        }
    }
    cout << "The tree that we just read is:" << endl;
    cout << *myTree;
    cout << endl;
    
    Tree* newTree = new Tree(*myTree);
    cout << "The tree that we just copied is: " << endl;
    cout << *newTree;
    cout << endl;
    
    
    cout << "The root of the tree is: ";
    (*myTree).Root();
    cout << endl;
    
    cout << "The least common ancestor of nodes 3 and 8 is: ";
    (*myTree).LCA(3,8);
    cout << endl;
    
    cout << "The least common ancestor of nodes 13 and 8 is: ";
    (*myTree).LCA(13,8);
    cout << endl;
    
    cout << "The least common ancestor of nodes 13 and 11 is: ";
    (*myTree).LCA(13,11);
    cout << endl;
    
    cout << "The children of node 12 is/are: " << endl;
    (*myTree).Children (12);
    
    cout << "The children of node 10 is/are: " << endl;
    (*myTree).Children (10);
    
    cout << "The siblings of node 3 is/are: " << endl;
    (*myTree).Siblings (3);
    
    cout << "The siblings of node 12 is/are: " << endl;
    (*myTree).Siblings (12);
    
    cout << "The nodes at level 3 is/are: " << endl;
    (*myTree).nodesAtLevel (3);
    
    cout << "The height of the tree is: " ;
    (*myTree).height();
    cout << endl;
    
    cout << "The level of node 3 in the tree is: " ;
    (*myTree).Level(3);
    cout<< endl;
    cout << "The level of node 12 in the tree is: ";
    (*myTree).Level(12);
    cout << endl;
    
    
    cout << "The preorder traversal of the tree is/are: " << endl;
    (*myTree).Preorder();
    cout << endl;
    
    delete myTree;
    delete newTree;
}


