#include<iostream>
using namespace std;
class queue
{
    int arr[20];
    int front;
    int  rear;
public:
    queue()
    {
        front = 0;
        rear = -1;
    }
    void enque(int num)
    {
        rear++;
        arr[rear]=num;
    }
    int deque()
    {
        int num;
        num=arr[front];
        front++;
        return num;
    }
    int is_empty()
    {
        if(rear+1==front)
            return 1;
        return 0;
    }
    int is_full()
    {
        if(rear>9)
            return 1;
        return 0;
    }
};
class Node
{
    string tCity;
    short code;
    int time;
    int fuel;
    Node *next;
public:
    Node()
    {
        next = NULL;
    }
    friend class flight_system;
    friend class CityNode;
};
class CityNode
{
    string fCity;
    Node *next1;
public:
    CityNode()
    {
        next1 = NULL;
    }
    friend class flight_system;
};
class flight_system
{
    int visited[10];
    int city_num;
    CityNode *arr[10];
    int ith_index,jth_index;
public:
    flight_system()
    {
        cout<<"enter the number of city. "<<endl;
        cin>>city_num;
        for(int i=0;i<city_num;i++)
        {
            arr[i] = new CityNode();
            cout<<"enter the name of the city. "<<endl;
            cin.ignore();
            cin>>arr[i]->fCity;
            visited[i]=0;
        }
    }
    int display_code(string s1)
    {
        for(int i=0;i<city_num;i++)
        {
            if(arr[i]->fCity==s1)
            {
                return i;
            }
        }
        return -1;
    }
    void display_airport_code()
    {
        cout<<"THE AIRPORT CODE for the entered CITY are. "<<endl;
        for(int i=0;i<city_num;i++)
        {
            cout<<i+1<<". "<<arr[i]->fCity<<". "<<"CODE : "<<i<<"."<<endl;
        }
    }
    void get_data()
    {
        char ch;
        Node *nnode;
        do
        {
            display_airport_code();
            cout<<"enter the code of the boarding city. "<<endl;
            cin>>ith_index;
            cout<<"enter the code of the destination city. "<<endl;
            cin>>jth_index;
            nnode = new Node();
            nnode->tCity = arr[jth_index]->fCity;
            nnode->code = jth_index;
            cout<<"enter the amount of fuel required to reach the destination. "<<endl;
            cin>>nnode->fuel;
            cout<<"enter the amount of time required to reach the destination. "<<endl;
            cin>>nnode->time;
            nnode->next = arr[ith_index]->next1;
            arr[ith_index]->next1=nnode;
            cout<<"do you want to enter more entries. "<<endl;
            cin>>ch;
        }while(ch=='y'||ch=='Y');
    }
    void display_data()
    {
        Node *temp;
        for(int i=0;i<city_num;i++)
        {
            cout<<arr[i]->fCity<<"-->\t";
            for(temp=arr[i]->next1;temp!=NULL;temp=temp->next)
            {
                cout<<temp->tCity<<"\t";
            }
            cout<<endl;
        }
    }
    void check_path()
    {
        string bcity,dcity;
        int ith_var;
        Node *temp;
        cout<<"enter the boarding city. "<<endl;
        cin>>bcity;
        cout<<"enter the destination city. "<<endl;
        cin>>dcity;
        ith_var=display_code(bcity);
        if(ith_var>=0)
        {
            for(temp=arr[ith_var]->next1;temp!=NULL;temp=temp->next)
            {
                if(temp->tCity==dcity)
                {
                    
                    cout<<"There exist a flight between "<<bcity<<" & "<<dcity<<" .\nThe information of the flight is as follows. "<<endl;
                    cout<<"FUEL : "<<temp->fuel<<"\nTIME : "<<temp->time<<"\nCITY CODE : "<<temp->code;
                    break;
                }
            }
        }
        else
        cout<<"The flight between these two paths does not exist. "<<endl;
    }

    void DFS(int num)
    {
        if(visited[num]==0)
        {
            cout<<arr[num]->fCity<<"\t";
            visited[num]=1;
            for(Node *temp=arr[num]->next1;temp!=NULL;temp=temp->next)
            {
                if(visited[temp->code]==0)
                    DFS(temp->code);
            }
        }
    }
    void BFS(int num)
    {
        queue q1;
        int u;
        int BFSarr[city_num];
        for(int i=0;i<city_num;i++)
        BFSarr[i]=0;
        cout<<num<<"\t";
        BFSarr[num]=1;
        q1.enque(num);
        while(!q1.is_empty())
        {
            u = q1.deque();
            for(Node *temp=arr[u]->next1;temp!=NULL;temp=temp->next)
            {
                if(BFSarr[temp->code]==0)
                {
                    cout<<temp->tCity<<"\t";
                    q1.enque(temp->code);
                    BFSarr[temp->code]=1;
                }
            }
        }
        
    }
    
};
int main()
{
    flight_system f1;
    int ch,code;
    string name;
    do {
        cout<<"\n1. ENTER FLIGHT INFO.\n2. DISPLAY ALL PATHS.\n3. DISPLAY ALL AIRPORT CODES.\n4. DISPLAY THE AIRPORT CODE OF A CITY.\n5. CHECKING IF PATH EXIST.\n6. DFS\n7. BFS.\n8. QUIT"<<endl;
        cin>>ch;
        switch (ch) {
            case 1:
                f1.get_data();
                break;
            case 2:
                f1.display_data();
                break;
            case 3:
                f1.display_airport_code();
                break;
            case 4:
                cout<<"enter the name of the city. "<<endl;
                cin>>name;
                code=f1.display_code(name);
                cout<<code;
                break;
            case 5:
                f1.check_path();
                break;
            case 6:
                f1.DFS(0);
                break;
            case 7:
                f1.BFS(0);
                break;
               
                
            default:
                break;
        }
        
    } while (ch!=7);
    
}
