#include<tuple>
#include <stack>
#include <vector>
#include<iostream>
#include <string>

#include "BinSearchTree.hpp"
#include "TreeNode.hpp"



TreeNode *BinSearchTree::local_insert( TreeNode *root, EntityInstance v ) 
{
	//std::cout<< 1 << std::endl;
	if( root == nullptr )
		return new TreeNode( v );
	if( root->value().id.compare( v.getAttributes().at(0).stringValue()) < 0 )
		root->rightSubtree( local_insert( root->rightSubtree(), v ) );
	else
		root->leftSubtree( local_insert( root->leftSubtree(), v ) );
	return root;
}

bool BinSearchTree::find( TreeNode *root, std::string v )
{
	if( root == nullptr )
	{
		//std::cout << "NULL";
		return false;
	}
	if( root->value().id.compare( v ) < 0 )
	{
		//std::cout << "LEFT  ";
		return find( root->rightSubtree(), v );
	}
        else if( root->value().id.compare( v ) > 0 )
	{
		//std::cout << "RIGHT";
                return find( root->leftSubtree(), v );
	}
	else
		return true;
}
void BinSearchTree::inorderDump( TreeNode *root )
{
        if( root == nullptr )
        {
                return;
        }
        else
        {
                inorderDump( root->leftSubtree() );
                root->value().print();
		inorderDump( root->rightSubtree() );
        }
}
void BinSearchTree::inorderDump()
{
        inorderDump( root );
}

int BinSearchTree::size( TreeNode *root )
{
	if( root == nullptr )
	{
		return 0;
	}
	else
	{
		return 1 + size( root->leftSubtree() ) + size( root->rightSubtree() );
	}
}

void BinSearchTree::insert(EntityInstance v) 
{
	if( ! find(v.getAttributes().at(0).stringValue()) )
		root = local_insert( root, v );
}

bool BinSearchTree::find( std::string v )
{
	return find( root, v );
}
/*
bool BinSearchTree::iterFind( int v )
{
	TreeNode *temp = root;
	while( temp != nullptr )
	{
		if( temp->value() < v )
		{
			temp = temp->rightSubtree();
		}
		else if( temp->value() > v )
		{
			temp = temp->leftSubtree();
		}
		else
		{
			return true;
		}

	}
	return false;
}
*/
int BinSearchTree::size()
{	
	return size( root );
}


void BinSearchTree::deleteEntireTree(TreeNode *root)
{
	if( root == nullptr )
	{
		return;
	}

	deleteEntireTree( root->leftSubtree() );
	deleteEntireTree( root->rightSubtree() );
	std::free( root );
	
}

std::vector<std::tuple<double,double>> BinSearchTree::intersection (TreeNode *root1, TreeNode *root2)
{
	std::stack<TreeNode *> s1, s2;
	 std::vector<std::tuple<double,double>> intersect;
	 std::tuple<double,double> t1;
	 int i = 0;
	while (1)
    	{
                if (root1)
        	{
            		s1.push(root1);
            		root1 = root1->leftSubtree();
        	}

                else if (root2)
        	{
            		s2.push(root2);
            		root2 = root2->leftSubtree();
        	}

        	else if (!s1.empty() && !s2.empty())
        	{
            		root1 = s1.top();
            		root2 = s2.top();

            		if (root1->value().id.compare(root2->value().id) == 0)
            		{
				t1 = std::make_tuple( std::stod(root1->value().getAttributes().at(1).stringValue()),
						std::stod(root2->value().getAttributes().at(1).stringValue()));
				intersect.push_back(t1);
			//	std::cout<<std::get<0>(t1)<<std::endl;
        	        	s1.pop();
               			s2.pop();

               	 		root1 = root1->rightSubtree();
               	 		root2 = root2->rightSubtree();
            		}

            		else if ((root1->value().id.compare(root2->value().id) < 0))
            		{
                		s1.pop();
                		root1 = root1->rightSubtree();

                		root2 = NULL;
            		}
            		else if ((root1->value().id.compare(root2->value().id) > 0))
            		{
                		s2.pop();
                		root2 = root2->rightSubtree();
                		root1 = NULL;
            		}
        	}

        	else  break;
    	}
	return intersect;

}

std::vector<std::tuple<double,double>> BinSearchTree::intersection (BinSearchTree *bst)
{
        return intersection( root, bst->root);
}



BinSearchTree::~BinSearchTree()
{
	deleteEntireTree( root );
}

