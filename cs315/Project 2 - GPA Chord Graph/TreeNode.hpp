
#ifndef _TreeNode
#define _TreeNode
#include "EntityInstance.hpp"
class TreeNode {
public:
    TreeNode(): left(nullptr), right(nullptr) {
	    EntityInstance temp;
	    Pair p(" "," ");
	    temp.addAttribute(p);
	    data = temp;
    } 
    TreeNode( EntityInstance n ): left(nullptr), right(nullptr), data(n) {} 

    TreeNode *leftSubtree() { return left; }
    TreeNode *rightSubtree() { return right; }

    void leftSubtree( TreeNode *left ) { this->left = left; }
    void rightSubtree(TreeNode *right) { this->right = right; }

    EntityInstance& value() { return data; } 

private:
    TreeNode *left, *right;
    EntityInstance data;
};  

#endif
