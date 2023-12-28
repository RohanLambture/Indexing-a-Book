Problem Description: Lexical Index Builder

Design a Lexical Index Builder system that processes a collection of chapters and builds a lexical index for the words in those chapters. The system should use a Red-Black Tree data structure to store and manage the words efficiently.

Classes and Functions:

1. HybridNode:
   - Represents a node in the Red-Black Tree.
   - Attributes:
     - `key`: Word associated with the node.
     - `element`: Chapter associated with the word.
     - `parent`: Pointer to the parent node.
     - `left_child`: Pointer to the left child node.
     - `right_child`: Pointer to the right child node.
     - `next_node`: Pointer to the next node in a linked list.
     - `colour`: Color of the node in the Red-Black Tree (either "red" or "black").

2. IndexEntry:
   - Represents an entry in the lexical index for a specific word.
   - Attributes:
     - `word`: The word for which the entry is created.
     - `chapter_word_counts`: A list of (chapter, word_count) tuples.
     - `last_chapter`: Keeps track of the last chapter in which the word occurred (for Most Recently Used functionality).
   - Functions:
     - `setWord(word_val)`: Set the word.
     - `getWord()`: Get the word.
     - `setChapterWordCounts(chapter_word_counts_val)`: Set the list of (chapter, word_count) tuples.
     - `getChapterWordCounts()`: Get the list of (chapter, word_count) tuples.
     - `setChapter(chapter)`: Set the last chapter.
     - `getChapter()`: Get the last chapter.
     - `add(chapter, count)`: Add the word count for a specific chapter.

3. RedBlackTree:
   - Implements a Red-Black Tree for efficient storage and retrieval of words.
   - Attributes:
     - `root`: Pointer to the root node.
   - Functions:
     - `leftRotate(node)`: Perform a left rotation around the given node.
     - `rightRotate(node)`: Perform a right rotation around the given node.
     - `insert(key, element)`: Insert a new node with the specified word and chapter.
     - `fixInsertion(node)`: Fix the Red-Black Tree properties after an insertion.
     - `deleteNode(key)`: Delete the node with the specified word.
     - `search(key)`: Search for a node with the specified word.
     - `inOrderSuccessor(node)`: Find the in-order successor of a given node.
     - `deleteFixup(node, parent)`: Fix the Red-Black Tree properties after a deletion.
     - `traverseUp(node)`: Traverse up the tree from the given node to the root.
     - `traverseDown(node, bit_sequence)`: Traverse down the tree based on the bit sequence.
     - `preOrderTraversal(node, depth)`: Perform pre-order traversal within a specified depth.
     - `getDepth(node)`: Get the depth of a node in the tree.
     - `blackheight(node)`: Calculate the black height of the Red-Black Tree.
     - `levelOrderTraversal()`: Perform level-order traversal of the Red-Black Tree.

4. Lexicon:
   - Manages the overall system for building the lexical index.
   - Attributes:
     - `red_black_tree`: An instance of the Red-Black Tree.
   - Functions:
     - `readChapters(chapter_names)`: Process words from a collection of chapters and update the Red-Black Tree and the IndexEntry list.
     - `buildIndex()`: Build the lexical index using the remaining words in the Red-Black Tree.

Constraints:

- The system should efficiently handle a large number of chapters and words.
- Words are case-insensitive.
- Punctuation at the end of words should be removed.
- The lexical index should not include words with a count of 0 for all chapters (pruning).
- The system should provide functionality to perform Red-Black Tree operations, traverse the tree, and build the index.
- The Lexicon class should serve as the interface for processing chapters and building the index.
