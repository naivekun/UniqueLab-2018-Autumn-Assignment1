#include"Unordered_map.hpp"

bool Unordered_map::empty() const
{
    return total_value_count==0;
}

Unordered_map::size_type Unordered_map::size() const
{
    return total_value_count;
}

int Unordered_map::hash_func(Unordered_map::key_type key)
{
    int hash_value=0;
    for(Unordered_map::key_type::iterator i=key.begin();i!=key.end();++i)
    {
        hash_value=hash_value*33+(int)(*i);
        while(hash_value<0)hash_value+=const_hash_value;
        hash_value%=const_hash_value;
    }
    return hash_value;
}

void Unordered_map::insert(const Unordered_map::value_type& value)
{
    int hash_value=hash_func(value.first);
    

    //查找重复
    if(hash_table[hash_value].first!=NULL)
    {
        struct LIST_NODE* find_index=hash_table[hash_value].first;
        while(find_index!=NULL)
        {
            if(find_index->key_data==value.first)
            {
                find_index->mapped_data==value.second;
                return;
            }
            find_index=find_index->next;
        }
    }

    if(hash_table[hash_value].key_data==value.first)
    {
        hash_table[hash_value].mapped_data=value.second;
        return;
    }
    

    //插入
    hash_table[hash_value].key_value_count+=1;
    total_value_count+=1;

    if(hash_table[hash_value].key_value_count>1)
    {
        struct LIST_NODE* list_ptr=hash_table[hash_value].first;
        struct LIST_NODE* insert_tmp=new LIST_NODE();
        if(hash_table[hash_value].key_value_count==2)
        {
            hash_table[hash_value].first=insert_tmp;
            insert_tmp->key_data=value.first;
            insert_tmp->mapped_data=value.second;
            return;
        }
        while(list_ptr->next!=NULL)
        {
            list_ptr=list_ptr->next;
        }
        list_ptr->next=insert_tmp;
        
        insert_tmp->key_data=value.first;
        insert_tmp->mapped_data=value.second;
    }
    else
    {
        //hash_table[hash_value].first=insert_tmp;
        hash_table[hash_value].key_data=value.first;
        hash_table[hash_value].mapped_data=value.second;
    }
    
}


void Unordered_map::delete_list(struct LIST_NODE* list_begin)
{
    struct LIST_NODE* delete_tmp=list_begin;
    struct LIST_NODE* delete_next;
    while(delete_tmp->next!=NULL)
    {
        delete_next=delete_tmp->next;
        delete delete_tmp;
        delete_tmp=delete_next;
    }
}

void Unordered_map::clear()
{
    for(int i=0;i<const_hash_value;++i)
    {
        delete_list(hash_table[i].first);
        hash_table[i].first=NULL;
        hash_table[i].key_value_count=0;
        hash_table[i].key_data="";
        hash_table[i].mapped_data=0;
    }
    total_value_count=0;
}

void Unordered_map::erase(const Unordered_map::key_type& key)
{
    int hash_value=hash_func(key);
    
    if(hash_table[hash_value].key_data==key)
    {
        total_value_count-=1;
        hash_table[hash_value].key_value_count-=1;
        struct LIST_NODE* erase_tmp=hash_table[hash_value].first;
        if(hash_table[hash_value].first!=NULL)
        {
            hash_table[hash_value].key_data=hash_table[hash_value].first->key_data;
            hash_table[hash_value].mapped_data=hash_table[hash_value].first->mapped_data;
            hash_table[hash_value].first=hash_table[hash_value].first->next;
            delete erase_tmp;
        }
        //delete hash_table[hash_value].first;
        
    }
    else
    {
        if(hash_table[hash_value].first==NULL)
            return;
        struct LIST_NODE* find_index=hash_table[hash_value].first;
        struct LIST_NODE* pre_index=NULL;
        while(find_index->key_data!=key)
        {
            pre_index=find_index;
            find_index=find_index->next;
            if(find_index==NULL)
                return;
        }
        total_value_count-=1;
        hash_table[hash_value].key_value_count-=1;
        //struct LIST_NODE* erase_tmp=find_index;
        if(find_index!=hash_table[hash_value].first)
            pre_index->next=find_index->next;
        else
            hash_table[hash_value].first=find_index->next;
        delete find_index;
        
    }
    //delete_list(hash_table[hash_value].first);
    //hash_table[hash_value].data="";
}

Unordered_map::mapped_type& Unordered_map::at(const Unordered_map::key_type& key)
{
    int hash_value=hash_func(key);
    if(hash_table[hash_value].key_data==key)
        return hash_table[hash_value].mapped_data;
    if(hash_table[hash_value].first!=NULL)
    {
        struct LIST_NODE* find_index=hash_table[hash_value].first;
        while(find_index->key_data!=key)
        {
            find_index=find_index->next;
        }
        return find_index->mapped_data;
    }
    else
    {
        
        return hash_table[hash_value].mapped_data;
    }
}

Unordered_map::size_type Unordered_map::count(const Unordered_map::key_type& key)
{
    int hash_value=hash_func(key);
    //return hash_table[hash_value].key_value_count>0?1:0;
    if(hash_table[hash_value].key_data==key)
    {
        return 1;
    }
    else if(hash_table[hash_value].first!=NULL)
    {
        struct LIST_NODE* count_index=hash_table[hash_value].first;
        while(count_index!=NULL)
        {
            if(count_index->key_data==key)
                return 1;
            count_index=count_index->next;
        }
    }
    return 0;
}


//TEST

#include<iostream>
#include<utility>
int main()
{
    Unordered_map pig;
    std::string s1[50]={
        "lalala",
        "kjnk",
        "sldnclaldkc",
        "sdlcnjsdnc",
        "jnjnjnc",
        "jnjnjncasd",
        "sldklksf",
        "ooooooo"
    };
    
    for(int i=0;i<=7;++i)
    {
        pig.insert(make_pair(s1[i],5.666*i));
    }
    for(int i=0;i<=7;++i)
    {
        std::cout<<pig.at(s1[i])<<std::endl;
    }
    pig.erase(s1[2]+"qqqqq");
    for(int i=0;i<=7;++i)
    {
        std::cout<<pig.count(s1[i])<<std::endl;
            //std::cout<<pig.at(s1[i])<<std::endl;
    }
    std::cout<<pig.size()<<std::endl;
    return 0;
}