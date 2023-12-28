#include <bits/stdc++.h>
using namespace std;

string toLowerCase(const std::string &input)
{
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

class HybridNode
{
public:
    string key;              // Word
    string element;          // Chapter
    HybridNode *parent;      // Parent node
    HybridNode *left_child;  // Left child node
    HybridNode *right_child; // Right child node
    HybridNode *next_node;   // Next node in the linked list
    string color = "black";  // Color of the node

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}
};


class IndexEntry
{
private:
    string word;
    vector<pair<string, int>> chapter_word_counts; // List of (chapter, word_count) tuples

    //for MRU function
    string last_chapter;

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val)
    { // Set the word
        word = word_val;
    }

    string getWord() 
    { // Get the word
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val)
    { // Set the list of (chapter, word_count) tuples
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts()
    { // Get the list of (chapter, word_count) tuples
        return chapter_word_counts;
    }

    //for MRU
    void setChapter(string chapter){
        this->last_chapter=chapter;
    }

    string getChapter(){
        // this->last_chapter=chapter;
        return last_chapter;

    }

    void add(string chapter, int count)
    {
        for (int i = 0; i < chapter_word_counts.size(); i++)
        {
            if (chapter_word_counts[i].first == chapter)
            {
                chapter_word_counts[i].second += count;
                return;
            }
        }
        this->chapter_word_counts.push_back({chapter, count});
    }
};

vector<IndexEntry *> Histogram;

class RedBlackTree
{
private:
    HybridNode *root; // Root node

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode *getRoot()
    {
        return root; // Return the root node
    }

    void setRoot(HybridNode *node)
    {
        root = node; // Set the root node
    }
    void leftRotate(HybridNode *node)
    {
        HybridNode *right_child = node->right_child;
        node->right_child = right_child->left_child;
        if (right_child->left_child)
        {
            right_child->left_child->parent = node;
        }
        right_child->parent = node->parent;
        if (!node->parent)
        {
            root = right_child;
        }
        else if (node == node->parent->left_child)
        {
            node->parent->left_child = right_child;
        }
        else
        {
            node->parent->right_child = right_child;
        }
        right_child->left_child = node;
        node->parent = right_child;
    }

    void rightRotate(HybridNode *node)
    {
        HybridNode *left_child = node->left_child;
        node->left_child = left_child->right_child;
        if (left_child->right_child)
        {
            left_child->right_child->parent = node;
        }

        left_child->parent = node->parent;
        if (!node->parent)
        {
            root = left_child;
        }
        else if (node == node->parent->left_child)
        {
            node->parent->left_child = left_child;
        }
        else
        {
            node->parent->right_child = left_child;
        }

        left_child->right_child = node;
        node->parent = left_child;
    }

    HybridNode *insert(string key, string element)
    {
        HybridNode *new_node = new HybridNode(key, element);
        if (!root)
        {
            root = new_node;
            root->color = "black";
            return root;
        }
        else
        {
            HybridNode *current = root;
            HybridNode *parent = nullptr;
            while (current)
            {
                parent = current;
                if (key < current->key)
                {
                    current = current->left_child;
                }
                else if (key > current->key)
                {
                    current = current->right_child;
                }
                else
                {
                    return NULL;
                }
            }
            new_node->parent = parent;
            if (key < parent->key)
            {
                parent->left_child = new_node;
            }
            else
            {
                parent->right_child = new_node;
            }
            new_node->color = "red";
            fixInsertion(new_node);
            return new_node;
        }
    }

    void fixInsertion(HybridNode *node)
    {
        while (node != root && node->parent->color == "red")
        {
            if (node->parent == node->parent->parent->left_child)
            {
                HybridNode *uncle = node->parent->parent->right_child;
                if (uncle && uncle->color == "red")
                {
                    node->parent->color = "black";
                    uncle->color = "black";
                    node->parent->parent->color = "red";
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->right_child)
                    {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = "black";
                    node->parent->parent->color = "red";
                    rightRotate(node->parent->parent);
                }
            }
            else
            {
                HybridNode *uncle = node->parent->parent->left_child; 
                if (uncle && uncle->color == "red")
                {
                    node->parent->color = "black";
                    uncle->color = "black";
                    node->parent->parent->color = "red";
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->left_child)
                    {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = "black";
                    node->parent->parent->color = "red";
                    leftRotate(node->parent->parent);
                }
            }
        }
        root->color = "black";
    }
   
    bool deleteNode(string key)
    {
        HybridNode *nodeToDelete = search(key);
        if (nodeToDelete == nullptr)
        {
            return 0;
        }

        HybridNode *replacement;
        if (nodeToDelete->left_child == nullptr || nodeToDelete->right_child == nullptr)
        {
            replacement = nodeToDelete;
        }
        else
        {
            replacement = inOrderSuccessor(nodeToDelete);
        }

        HybridNode *child = (replacement->left_child != nullptr) ? replacement->left_child : replacement->right_child;

        if (child != nullptr)
        {
            child->parent = replacement->parent;
        }

        if (replacement->parent == nullptr)
        {
            root = child;
        }
        else if (replacement == replacement->parent->left_child)
        {
            replacement->parent->left_child = child;
        }
        else
        {
            replacement->parent->right_child = child;
        }

        if (replacement != nodeToDelete)
        {
            nodeToDelete->key = replacement->key;
            nodeToDelete->element = replacement->element;
        }

        if (replacement->color == "black")
        {
            deleteFixup(child, replacement->parent);
        }

        delete replacement;
        return true;
    }

    HybridNode *search(string key)
    {
        HybridNode *node = root;

        while (node != nullptr)
        {
            if (key == node->key)
            {
                return node;
            }
            else if (key < node->key)
            {
                node = node->left_child;
            }
            else
            {
                node = node->right_child;
            }
        }
        return nullptr;
    }

    HybridNode *inOrderSuccessor(HybridNode *node)
    {
        HybridNode *current = node->right_child;
        while (current->left_child != nullptr)
        {
            current = current->left_child;
        }
        return current;
    }

    void deleteFixup(HybridNode *node, HybridNode *parent)
    {
        while (node != root && (node == nullptr || node->color == "black"))
        {
            if (node == parent->left_child)
            {
                HybridNode *sibling = parent->right_child;
                if (sibling->color == "red")
                {
                    sibling->color = "black";
                    parent->color = "red";
                    leftRotate(parent);
                    sibling = parent->right_child;
                }
                if ((sibling->left_child == nullptr || sibling->left_child->color == "black") &&
                    (sibling->right_child == nullptr || sibling->right_child->color == "black"))
                {
                    sibling->color = "red";
                    node = parent;
                    parent = node->parent;
                }
                else
                {
                    if (sibling->right_child == nullptr || sibling->right_child->color == "black")
                    {
                        sibling->left_child->color = "black";
                        sibling->color = "red";
                        rightRotate(sibling);
                        sibling = parent->right_child;
                    }
                    sibling->color = parent->color;
                    parent->color = "black";
                    sibling->right_child->color = "black";
                    leftRotate(parent);
                    node = root;
                }
            }
            else
            {
                HybridNode *sibling = parent->left_child;
                if (sibling->color == "red")
                {
                    sibling->color = "black";
                    parent->color = "red";
                    rightRotate(parent);
                    sibling = parent->left_child;
                }
                if ((sibling->right_child == nullptr || sibling->right_child->color == "black") &&
                    (sibling->left_child == nullptr || sibling->left_child->color == "black"))
                {
                    sibling->color = "red";
                    node = parent;
                    parent = node->parent;
                }
                else
                {
                    if (sibling->left_child == nullptr || sibling->left_child->color == "black")
                    {
                        sibling->right_child->color = "black";
                        sibling->color = "red";
                        leftRotate(sibling);
                        sibling = parent->left_child;
                    }
                    sibling->color = parent->color;
                    parent->color = "black";
                    sibling->left_child->color = "black";
                    rightRotate(parent);
                    node = root;
                }
            }
        }

        if (node != nullptr)
        {
            node->color = "black";
        }
    }
    
    vector<HybridNode *> traverseUp(HybridNode *node)
    {
        // Traverse up the tree from the given node to the root
        // Return the vector of nodes in the path
        vector<HybridNode *> answer;
        HybridNode *travel = node;
        while (travel != NULL)
        {
            answer.push_back(travel);
            travel = travel->parent;
        }
        return answer;
    }

    vector<HybridNode *> traverseDown(HybridNode *node, string bit_sequence)
    {
        // Traverse down the tree based on the bit sequence
        // Return the vector of nodes in the path
        HybridNode *start = node;
        vector<HybridNode *> answer;
        for (int k = 0; k < bit_sequence.size(); k++)
        {
            if (start == NULL)
                break;
            answer.push_back(start);
            if (bit_sequence[k] == '1')
            {
                if(start->left_child!=NULL)
                    start = start->left_child;
                else
                    break;
            }
            else
            {
                if(start->right_child!=NULL)
                    start = start->right_child;
                else
                    break;
                // start = start->right_child;
            }
        }
        return answer;
    }

    vector<HybridNode*>& findAnswer(HybridNode* root,vector<HybridNode*>&answer,int depth){
        if(root==NULL || depth==-1){
            return answer;
        }
        answer.push_back(root);
        findAnswer(root->left_child,answer,depth-1);
        findAnswer(root->right_child,answer,depth-1);
    }

    vector<HybridNode *> preOrderTraversal(HybridNode *node, int depth)
    {
        // Perform pre-order traversal staying within specified depth
        // cout<<getDepth(node);
        int count=depth-getDepth(node);
        vector<HybridNode*>answer;

        return findAnswer(node,answer,count);
    }

    int getDepth(HybridNode* node){
        int depth=0;
        HybridNode* temp=node;
        while(temp->parent!=NULL){
            depth++;
            temp=temp->parent;
        }
        return depth;
    }

    void check(HybridNode* vertex, int count){
        if(vertex == NULL){
            cout<<count<<" ";
            return;
        }
        if(vertex->color=="black"){
            check(vertex->left_child,count+1);
            check(vertex->right_child,count+1);
        }
        else{
            check(vertex->left_child,count);
            check(vertex->right_child,count);
        }
    }

    int blackheight(HybridNode *node)
    {
        // Implement blackheight
        // int temp=0;
        // check(node,temp);
        int count = 0;
        HybridNode *travel = root;
        while (travel)
        {
            if (travel->color == "black")
            {
                count++;
            }
            travel = travel->left_child;
        }
        return count;
    }

    void inorderIndex(vector<IndexEntry>&temp,HybridNode* root){
        if(root==NULL)
            return;
        inorderIndex(temp,root->left_child);
        // IndexEntry* dup;
        for(auto &it:Histogram){
            if(it->getWord()==root->key){
                temp.push_back(*it);
                break;
            }
        }
        inorderIndex(temp,root->right_child);
    }

    void levelOrderTraversal()
    {
        queue<HybridNode*> q;
        q.push(root);
        q.push(NULL);

        while (!q.empty())
        {
            HybridNode *temp = q.front();
            q.pop();

            if (temp == NULL)
            {
                cout << endl;
                if (!q.empty())
                {
                    q.push(NULL);
                }
            }
            else
            {
                cout << temp->key << "," << temp->color << "  ";
                if (temp->left_child)
                {
                    q.push(temp->left_child);
                }

                if (temp->right_child)
                {
                    q.push(temp->right_child);
                }
            }
        }
    }
};


class Lexicon
{
private:
    RedBlackTree red_black_tree; // Red-Black Tree

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree)
    { // Set the Red-Black Tree
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree()
    { // Get the Red-Black Tree
        return red_black_tree;
    }

    void readChapters(vector<string> chapter_names)
    {
        // Process words from a chapter and update the Red-Black Tree
        // chapter_names is a vector of chapter names

        //punctuation ---- last se sab remove kar de and start ke space remove karne h(ie null string )
        vector<string> NewChapters;
        for (auto it : chapter_names)
        {
            string chapter = it;
            for (int i = 0; i < 4; i++)
            {
                chapter.pop_back();
            }
            NewChapters.push_back(chapter);
        }
        for (int i = 0; i < chapter_names.size(); i++)
        {
            fstream fin;
            fin.open(chapter_names[i], ios::in);
            string line;
            while (getline(fin, line))
            {
                string word;
                stringstream s(line);
                while (getline(s, word, ' '))
                {
                    if(word=="")
                        continue;
                    string newWord = toLowerCase(word);
                    while(((int)newWord.back()<97 ||  (int)newWord.back()>122) ){
                        if((int)word.back()!=39){
                            newWord.pop_back();
                            // cout << newWord <<" ";
                        }
                        
                    }
                    // cout << newWord <<" ";
                    // cout << endl;
                    // cout << "out of loop" << endl;
                    
                    red_black_tree.insert(newWord, NewChapters[i]);

                    bool flag = true;
                    for (int k = 0; k < Histogram.size(); k++)
                    {
                        
                        if (Histogram[k]->getWord() == newWord)
                        {
                            // cout << " 111" ;
                            Histogram[k]->add(NewChapters[i], 1);
                            Histogram[k]->setChapter(NewChapters[i]);
                            flag = false;
                            break;
                        }
                    }
                    if (flag)
                    {
                        IndexEntry *newEntry = new IndexEntry(newWord);
                        for (auto &it : NewChapters)
                        {
                            newEntry->add(it, 0);
                        }
                        newEntry->add(NewChapters[i], 1);
                        newEntry->setChapter(NewChapters[i]);
                        Histogram.push_back(newEntry);
                    }
                }
            }
        }
        // pruning
        for (auto &it : Histogram)
        {
            bool flag = true;
            for (auto i : it->getChapterWordCounts())
            {
                if (i.second == 0)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                red_black_tree.deleteNode(it->getWord());
        }
    }

    vector<IndexEntry> buildIndex()
    {

        // Build the index using the remaining words in the Red-Black Tree
        vector<IndexEntry> answer;
        red_black_tree.inorderIndex(answer,red_black_tree.getRoot());
        return answer;
    }
};