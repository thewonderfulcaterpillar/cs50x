#include <cs50.h>
#include <stdio.h>
#include <string.h>
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// array should be cleared before used, methink


// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool hasCycle(int winner,int loser);
void print_winner(void);

int main(int argc, string argv[])
{
    for (int i = 0;i<MAX;i++){
        for (int j=0;j<MAX;j++){
            preferences[i][j]=0;
        }
    }
    // Check for invalid usage

    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0;i<candidate_count;i++){
        if (strcmp(name,candidates[i])==0){
            ranks[rank]=i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i=0;i<candidate_count-1;i++){
        for (int j = i+1;j<candidate_count;j++){
            int winner=ranks[i];
            int loser=ranks[j];
            preferences[winner][loser]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i<candidate_count;i++){
        for (int j =i+1; j<candidate_count;j++){
            if (i!=j){
                if (preferences[i][j]>preferences[j][i]){
                    pair ijpair;
                    ijpair.winner=i;
                    ijpair.loser=j;
                    pairs[pair_count]=ijpair;
                    pair_count++;
                }
                else if (preferences[i][j]<preferences[j][i]){
                    pair ijpair;
                    ijpair.winner=j;
                    ijpair.loser=i;
                    pairs[pair_count]=ijpair;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    bool changed=true;
    int j=0;
    while (changed==true){
        changed=false;
        for (int i = 1; i<pair_count-j;i++){
            pair ijpair=pairs[i];
            pair ijpair2=pairs[i-1];
            if (preferences[ijpair.winner][ijpair.loser]>preferences[ijpair2.winner][ijpair2.loser]){
                pair temp=pairs[i-1];
                pairs[i-1]=pairs[i];
                pairs[i]=temp;
                changed=true;}
        }
        j+=1;
    }
    return;
}
bool hasCycle(int winner,int loser){
    if (winner==loser){
        return true;
    }
    for (int i =0;i<candidate_count;i++){
        if (loser!=i && locked[loser][i]){
            if(hasCycle(winner,i)){
                return true;
            };
        }
    }
    return false;

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0 ; i < pair_count;i++){
        pair ijpair=pairs[i];
        if (!hasCycle(ijpair.winner,ijpair.loser)){
            locked[ijpair.winner][ijpair.loser]=true;
        }

    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int hasEdge[candidate_count];
    for (int i = 0; i<candidate_count;i++){
        hasEdge[i]=0;
    }
    for (int i = 0; i<candidate_count;i++){
        for (int j = 0;j<candidate_count;j++){
            if (i!=j){
                if (locked[i][j]){
                    hasEdge[j]+=1;
                }
            }
        }
    }
    for (int i = 0;i<candidate_count;i++){
        if (hasEdge[i]==0){
            printf("%s\n",candidates[i]);
        }
    }
    return;
}