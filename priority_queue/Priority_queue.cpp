#include "Priority_queue.hpp"

Priority_queue::const_reference Priority_queue::top() const
{
    return Heap_vec[0];
}

bool Priority_queue::empty() const
{
    return Heap_vec.size()==0;
}

Priority_queue::size_type Priority_queue::size() const
{
    return Heap_vec.size();
}

void Priority_queue::push(const value_type& value)
{
    Heap_vec.push_back(value);
    int push_index=Heap_vec.size()-1;
    int push_index_parent;
    while(push_index!=0)
    {
        push_index_parent=(push_index-1)/2;
        if(Heap_vec[push_index]>Heap_vec[push_index_parent])
        {
            std::swap(Heap_vec[push_index],Heap_vec[push_index_parent]);
            push_index=push_index_parent;
        }
        else
            break;
    }
    /*
    printf("DEBUG:");
    for(int i=0;i<=Heap_vec.size()-1;++i)
        printf("%.0lf ",Heap_vec[i]);
    printf("\n");
    */
}

void Priority_queue::pop()
{
    std::swap(Heap_vec.front(),Heap_vec.back());
    Heap_vec.erase(Heap_vec.end()-1);
    int pop_index=1;
    while(1)
    {
        if(pop_index*2+1<=Heap_vec.size())
            if(Heap_vec[pop_index*2-1]>Heap_vec[pop_index*2+1-1])
            {
                if(Heap_vec[pop_index-1]<Heap_vec[pop_index*2-1])
                {
                    std::swap(Heap_vec[pop_index-1],Heap_vec[pop_index*2-1]);
                    pop_index=pop_index*2;
                }
                else
                    break;
            }
            else
            {
                if(Heap_vec[pop_index-1]<Heap_vec[pop_index*2+1-1])
                {
                    std::swap(Heap_vec[pop_index-1],Heap_vec[pop_index*2+1-1]);
                    pop_index=pop_index*2+1;
                }
                else
                    break;
            }

        else if(pop_index*2<=Heap_vec.size())
            if(Heap_vec[pop_index-1]<Heap_vec[pop_index*2-1])
                {
                    std::swap(Heap_vec[pop_index-1],Heap_vec[pop_index*2-1]);
                    pop_index=pop_index*2;
                }
                else
                    break;
        else
            break;
    }
    
}

//TEST
// /*
// #include<iostream>
// int main(int argc, char const *argv[])
// {
//     Priority_queue pig;
//     double a[11]={0,5,1,2,8,4,65,4,7,5,38};
//     for(int i=1;i<=10;++i)
//     {
//         pig.push(a[i]);
//     }
//     while(!pig.empty())
//     {
//         printf("%.0lf ",pig.top());
//         pig.pop();
//     }
        

//     return 0;
// }
// */
