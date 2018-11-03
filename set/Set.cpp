#include "Set.hpp"



bool Set::isred(struct Set::TREE_NODE* head)
{
    if(head==NULL)
        return false;
    if(head->color)
        return 1;
    return 0;
}


struct Set::TREE_NODE* Set::rotate_left(struct TREE_NODE* head)
{
    //printf("DEBUG[RL]:%lf\n",head->data);
    struct TREE_NODE* head_right=head->right;
    head->right=head_right->left;
    head_right->left=head;
    head_right->color=head->color;
    head->color=1;
    return head_right;
}

struct Set::TREE_NODE* Set::rotate_right(struct TREE_NODE* head)
{
    //printf("DEBUG[RR]:%lf\n",head->data);
    struct TREE_NODE* head_left=head->left;
    head->left=head_left->right;
    head_left->right=head;
    head_left->color=head->color;
    head->color=1;
    return head_left;
}

struct Set::TREE_NODE* Set::split_node(struct Set::TREE_NODE* head)
{
    //printf("DEBUG[SN]:%lf\n",head->data);
    head->color=!head->color;
    if(head->left!=NULL)
        head->left->color=!head->left->color;
    if(head->right!=NULL)
        head->right->color=!head->right->color;
    return head;
}

struct Set::TREE_NODE* Set::insert_into_tree(struct Set::TREE_NODE* head,Set::key_type key)
{
    if(head==NULL)
    {
        struct TREE_NODE* new_node=new TREE_NODE();
        new_node->data=key;
        new_node->color=1;
        total_data_count+=1;
        return new_node;
    }

    if(key==head->data);
    else if(key<head->data)
    {
        head->left=insert_into_tree(head->left,key);
    }
    else
    {
        head->right=insert_into_tree(head->right,key);
    }

    if(head->right!=NULL)
        if(head->right->color)
            head=rotate_left(head);
    if(head->left!=NULL&&head->left->left!=NULL)
        if(head->left->left->color&&head->left->color)
            head=rotate_right(head);
    if(head->left!=NULL&&head->right!=NULL)
        if(head->left->color&&head->right->color)
            head=split_node(head);
    
    return head;
}

void Set::clear_func(struct TREE_NODE* head)
{
    if(head==NULL)
        return;
    clear_func(head->left);
    clear_func(head->right);
    delete head;
}

void Set::clear()
{
    clear_func(root);
    total_data_count=0;
    root=NULL;
}

void Set::insert(const Set::key_type& key)
{
    
    root=insert_into_tree(root,key);
    if(root!=NULL)
        root->color=0;
}

bool Set::empty() const
{
    return total_data_count==0; 
}

Set::size_type Set::size() const
{
    return total_data_count;
}

struct Set::TREE_NODE* Set::fix_to_be_left(struct Set::TREE_NODE* head)
{
    if(head->right!=NULL)
        if(head->right->color)      //magic!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            head=rotate_left(head);
    if(head->left!=NULL&&head->left->left!=NULL)
        if(head->left->color&&head->left->left->color)
            head=rotate_right(head);
    if(head->left!=NULL&&head->right!=NULL)
        if(head->left->color&&head->right->color)
            split_node(head);
    return head;
}


struct Set::TREE_NODE* Set::move_red_left(struct Set::TREE_NODE* head)
{
    split_node(head);
    if(head->right!=NULL&&head->right->left!=NULL)
        if(head->right->left->color)
        {
            head->right=rotate_right(head->right);
            head=rotate_left(head);
            split_node(head);
        }
    return head;
}
struct Set::TREE_NODE* Set::delete_min(struct Set::TREE_NODE* head)
{
    if(head->left==NULL)
    {
        //DEBUG begin
        // if(head->right!=NULL)
        // {
        //     printf("FUCKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK\n");
        //     printf("YOU LOST %lf",head->right->data);
        // }

        //printf("DEBUG[DM]deleted!! : %lf\n",head->data);
        //DEBUG end
        delete head;
        total_data_count-=1;
        return NULL;
    }
    // if(head->left!=NULL&&head->left->left!=NULL)
    //     if((head->left->color==0)&&(head->left->left->color==0))
    // !!! SUPER-MAGIC-ERROR
    // !!! DO NOT USE CODE ABOVE
    if(!isred(head->left)&&head->left!=NULL&&!isred(head->left->left))
        head=move_red_left(head);
    head->left=delete_min(head->left);
    return fix_to_be_left(head);
}

Set::key_type Set::get_min(struct Set::TREE_NODE* head)
{
    struct TREE_NODE* find_index=head;
    while(find_index->left!=NULL)
    {
        find_index=find_index->left;
    }
    return find_index->data;
}

struct Set::TREE_NODE* Set::delete_main(struct Set::TREE_NODE* head,Set::key_type key)
{
    //printf("DEBUG[D1]Entering Node : %lf\n",head->data);//debug
    if(head==NULL)
        return NULL;
    if(key<head->data)
    {
        // if(head->left!=NULL&&head->left->left!=NULL)
        //     if((head->left->color==0)&&(head->left->left->color==0))
        // !!! SUPER-MAGIC-ERROR
        // !!! DO NOT USE CODE ABOVE
        if(!isred(head->left)&&head->left!=NULL&&!isred(head->left->left))
            head=move_red_left(head);
                
        head->left=delete_main(head->left,key);
    }
    else
    {
        if(head->left!=NULL)
            if(head->left->color)
                head=rotate_right(head);
        if(head->data==key&&head->right==NULL)
        {
            //printf("DEBUG[D2]deleted!! : %lf\n",head->data);
            delete head;
            total_data_count-=1;
            return NULL;
        }
        // if(head->right!=NULL&&head->right->left!=NULL)
        //     if((head->right->color==0)&&(head->right->left->color==0))
        // !!! SUPER-MAGIC-ERROR
        // !!! DO NOT USE CODE ABOVE
        if(!isred(head->right)&&head->right!=NULL&&!isred(head->right->left))
            head=move_red_left(head);  //different from ppt
        if(head->data==key)
        {
            head->data=get_min(head->right);
            head->right=delete_min(head->right);
        }
        else
        {
            head->right=delete_main(head->right,key);
        }
    }
    return fix_to_be_left(head);
}

Set::size_type Set::erase(const Set::key_type& key)
{
    int tmp=total_data_count;
    root=delete_main(root,key);
    if(root!=NULL)
        root->color=0;
    if(tmp==total_data_count)
        return 0;
    return 1;
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

//test

// void Set::debug(struct Set::TREE_NODE* head)
// {
//     if(head==NULL)
//         return;
//     debug(head->left);
//     printf("%lf\n",head->data);
//     debug(head->right);
// }

// #include<iostream>
// #include <set>
// #include <random>
// int main()
// {
//     // freopen("3.out","w",stdout);
//     std::set<double> std_set;
//     Set custom_set;
//     for (int i = 1; i != 100000; ++i) {
//         auto num = (long long)rand()*100000;
//         num %=i;
//         std_set.insert((double) i);
//         std_set.insert((double) (-i));
//         std_set.erase((double)(num));
//         custom_set.insert((double) i);
//         custom_set.insert((double) (-i));
//         custom_set.erase((double)(num));
//         if(custom_set.count(49))
//         {
//             printf("-----%d\n",i);
//         }
//         if(std_set.size()!=custom_set.size())
//         {
//             printf("%d %d\n",std_set.size(),custom_set.size());
//             printf("%d %lf\n",i,(double)num);
//             custom_set.debug(custom_set.root);
//             break;
//         }
            
//         //ASSERT_EQ(custom_set.count((double) i), std_set.count((double) i));
//         //ASSERT_EQ(custom_set.count((double) (-i)), std_set.count((double) (-i)));
//     }
//     //ASSERT_EQ(std_set.size(), custom_set.size());
//     printf("%d %d\n",std_set.size(),custom_set.size());
//     for (auto s:std_set) {
//         custom_set.erase(s);
//     }
//     //ASSERT_EQ(custom_set.size(), 0);
    
//     Set pig;
//     for(double i=1;i<=10;++i)
//         pig.insert(i*0.214);
//     //for(double i=1;i<=10;++i)
//         //std::cout<<pig.count(i*0.214)<<std::endl;
//     pig.clear();
//     for(double i=1;i<=10;++i)
//         pig.insert(i*0.214);
//     pig.erase(23333.23333);
        
//     // for(double i=1;i<=10;++i)
//     //     std::cout<<pig.count(i*0.214)<<std::endl;
    
//    std::default_random_engine e(810);
//     std::uniform_real_distribution<double> dis(0, 100);

//     std::set<double> std_set;
//     Set custom_set;

//     for (unsigned i = 0; i != 100; ++i) {
//         double num = dis(e);
//         std_set.insert(num);
//         custom_set.insert(num);
//         //printf("DEBUG[INS]:%lf\n",num);
//         // std::cout<<"Insert : "<<num<<std::endl;
//         // custom_set.debug(custom_set.root);
//         // std::cout<<"---------------------\n";
//     }


//     //ASSERT_EQ(std_set.size(), custom_set.size());
//     for (auto s: std_set) {
//         //printf("delete : %lf\n",s);
//         //custom_set.debug(custom_set.root);
//         //printf("DEBUG[DEL]:%lf\n",s);
//         //std::cout<<custom_set.count(s)<<std::endl;
//         custom_set.erase(s);
//         //std::cout<<"---------------------\n";
//     }
//     std::cout<<custom_set.size();

//     return 0;
// }

