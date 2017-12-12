#include <bits/stdc++.h>

using namespace std;

int main(){

	vector < pair <int, int> >  adjlist[100001];
	int a, b, d1, d2,flag = 0, count1= 0,flagPrev=0, Node=0, sourceNode,destinationNode,weight;
	char c;
    FILE* fptr;
    fptr = fopen("example1.txt", "r");
	if (fptr != NULL)
	{
		while((c=fgetc(fptr))!=EOF)
        {
             a = c -'0';
            if(a >=0 && a <= 9){
                    flagPrev = flag;
                    flag = 1;
                if( flagPrev == 0){
                        Node = a;
                        count1++;
                }
                if( flagPrev == 1){
                        Node = (Node*10)+a;
                }


            }
            if(!(a >=0 && a <= 9)){
                flagPrev = flag;
                flag = 0;
            }
            if((flagPrev == 1) && (flag == 0)){
                   if((count1 % 3) == 1 ){
                    sourceNode = Node;
                    flag = 0;
                }
                if((count1 % 3) == 2){
                    destinationNode = Node;
                    flag = 0;
                }
                if((count1 % 3) == 0){
                    weight = Node;
                    flag = 0;
                    cout << "Source is " << sourceNode << " Destination is " << destinationNode << " weight is " << weight << endl;
                    adjlist[sourceNode].push_back( make_pair(destinationNode,weight) );
                    adjlist[destinationNode].push_back( make_pair(sourceNode,weight) );
                }
                flagPrev = 0;
}

        }
         fclose(fptr);
    }
    else
		cout << "Unable to open file";

    int s;
    cout<< "Enter Source Node" << endl;
    cin >> s ;
     vector<pair<int, int> >::iterator it;

    queue< pair<int, int> > q;

    for( it = adjlist[s].begin(); it != adjlist[s].end(); it++){
            q.push(make_pair(it->first,it->second));
    }
    //int d1, d2;
    int Threshold_min = 1;
    vector<pair <int, int> > destinationNodes;
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

                  if(!node[it->first] )
                  {
                      node[it->first] =1;
                      cout<< "the node  " << s << " and d " << it->first << " obtained by " << p.first << " having weight as " << dis << endl;
                      destinationNodes.push_back( make_pair(it->first,dis) );
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

    return 0;
}
