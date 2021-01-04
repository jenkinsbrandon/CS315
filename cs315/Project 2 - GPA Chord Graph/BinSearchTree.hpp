#ifndef BINSEARCHTREE_HPP
#define BINSEARCHTREE_HPP

#include<stdlib.h>
#include <string>
#include "TreeNode.hpp"

class BinSearchTree {
public:
    void insert( EntityInstance v ); 
    bool find( std::string v );
    //bool iterFind( std::string v );
    int size();
    void inorderDump();
    std::vector<std::tuple<double,double>> intersection(BinSearchTree *bst);

    ~BinSearchTree();
private:
    TreeNode *local_insert( TreeNode *, EntityInstance );
    bool find( TreeNode *, std::string );
    int size( TreeNode * );
    void deleteEntireTree(TreeNode *root);
    void inorderDump( TreeNode * );

    std::vector<std::tuple<double,double>> intersection (TreeNode *root1, TreeNode *root2);
    TreeNode *root;
   
};

#endif
