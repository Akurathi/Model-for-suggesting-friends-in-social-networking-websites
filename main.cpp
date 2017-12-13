#include<bits/stdc++.h>

using namespace std;

bool sortbysec(const pair<int, pair<int,int> > &a,
               const pair<int, pair<int,int> > &b)
{
    return ((a.second).second > (b.second).second);
}

int main()
{
    ofstream myfile;
    myfile.open ("example1.txt");
    myfile << "The Randamised Graph is\n";
    int V, start, stop, source, n, edges, rangeStart, rangeEnd;
    vector < pair <int, int> >  adjlist[100001];
    float avg_deg;

    cout << "Enter the number of vertices in the graph : ";
    cin >> V;
    cout << "Enter the source vertex : ";
    cin >> source;
    cout<< "Enter the average degree: ";
    cin>>avg_deg;
    cout<<"Enter the range start and range end: ";
    cin>>rangeStart>>rangeEnd;
    edges = (int)(avg_deg * V)/2;
    map<pair<int,int>,int>m;
    cout<<"Edge number "<<edges<<endl;
    cout<<"Edges are: "<<endl;
    for(int i = 0; i < edges; i++)
    {
        srand (time(NULL));
        int random_number = -1;
        while(random_number == -1)
        {
            random_number =rand()%(V*V);
            if(m[make_pair(random_number/V,random_number%V)] || random_number/V == random_number%V)
                random_number = -1;
            else
            {
                int weight = rand()%(rangeEnd - rangeStart) + rangeStart;
                m[make_pair(random_number/V,random_number%V)] = 1;
                m[make_pair(random_number%V,random_number/V)] = 1;
                myfile << "LR_"<< random_number/V << "-> LR_"<< random_number%V << "[ label = \" "<< weight << " \" ];" << endl;
                myfile << "LR_"<< random_number%V << "-> LR_"<< random_number/V << "[ label = \""<< weight << "\" ];" << endl;
                cout<<random_number/V<<" - "<<random_number%V<<": "<<weight<<endl;
                adjlist[random_number/V].push_back(make_pair(random_number%V, weight) );
                adjlist[random_number%V].push_back(make_pair(random_number/V, weight) );

            }
        }
    }
    myfile.close();
    int s;
    cout<< "Enter Source Node" << endl;
    cin >> s ;
     vector<pair<int, int> >::iterator it;

    queue< pair<int, int> > q;
    set<int> dir_friends;

    for( it = adjlist[s].begin(); it != adjlist[s].end(); it++){
            q.push(make_pair(it->first,it->second));
            dir_friends.insert(it->first);
    }
    int d1, d2;
    int Threshold_min = 1;
    vector<pair <int, pair <int, int> > > destinationNodes;
    vector<pair <int, pair <int, int> > > :: iterator itt;
    map<int,int> node;
    int min_d = 1111, min_n = 1111;

    while(q.size()>0) {
      pair<int,int > p;
      p = q.front();

      q.pop();
      for(it = adjlist[p.first].begin();it!=adjlist[p.first].end();it++)
      {
                if( it->first != s){
              d1 = p.second;
              d2 = it->second;
              int dis = p.second + it->second;

              if( dis > Threshold_min)
              {

                  if(!node[it->first] && dir_friends.find(it->first)== dir_friends.end())
                  {
                      node[it->first] =1;
                      destinationNodes.push_back(make_pair(p.first, make_pair(it->first,dis) ));
                      ofstream myfile;
                      myfile.open ("example.txt");
                      myfile << "The Final Output is\n";

                      myfile << "LR_"<< s << "-> LR_"<< it->first << "[ label = \" "<< dis << " \" ];" << endl;
                      myfile.close();
                  }
              }
            }
      }
    }

    if(destinationNodes.size() == 0) {
        cout << "No mutual friends found "<< endl;
    }

    sort(destinationNodes.begin(), destinationNodes.end(), sortbysec);

    for(itt = destinationNodes.begin(); itt != destinationNodes.end(); itt++)
    {
        cout<< "the node  " << s << " and d " << (itt->second).first << " obtained by " << itt->first << " having weight as " << (itt->second).second << endl;
    }

    return 0;
}
