#include "Set.hpp"

Set::Set()
{
    root=new Set::TREE_NODE();
}

Set::size_type Set::count(const Set::key_type& key)
{
    struct TREE_NODE* current_node=root;
    while(current_node!=NULL)
    {
        if(current_node->data==key)
            return 1;
        else if(current_node->data>key)
            current_node=current_node->left;
        else
            current_node=current_node->right;
    }
    return 0;
}

struct Set::TREE_NODE* Set::rotate_left(struct TREE_NODE* head)
{
    struct TREE_NODE* head_right=head->right;
    head->right=head_right->left;
    head_right->left=head;
    head_right->color=head->color;
    head->color=1;
    return head_right;
}

struct Set::TREE_NODE* Set::rotate_right(struct TREE_NODE* head)
{
    struct TREE_NODE* head_left=head->left;
    head->left=head_left->right;
    head_left->right=head;
    head_left->color=head->color;
    head->color=1;
    return head_left;
}

void Set::split_node(struct Set::TREE_NODE* head)
{
    head->color=!head->color;
    head->left->color=!head->left->color;
    head->right->color=!head->right->color;
}

