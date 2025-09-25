#include<iostream>
using namespace std;

class ScoreTracker
{
    private:
    int noOfPlayers;
    int *scores;

    public:
    ScoreTracker(int size)
    {
        noOfPlayers = size;
        scores = new int[noOfPlayers];
        
    }

    ~ScoreTracker()
    {
        delete [] scores;
    }

    void getSocre()
    {
        for(int i=0; i<noOfPlayers; i++)
        {
            cout<<"Enter the score for player no."<<i+1<<" : ";
            cin>>scores[i];
            
        }
    }

    void showSocre()
    {
        for(int i=0; i<noOfPlayers; i++)
        {
            cout<<"Player no."<<i+1<<" score is : "<<scores[i]<<endl;
        }
    }
};

int main(){

    int players;
    cout<<"Enter the number of players : ";
    cin>>players;

    ScoreTracker *scores = new ScoreTracker(players);
    scores->getSocre();
    scores->showSocre();

    delete scores;


    return 0;
}
