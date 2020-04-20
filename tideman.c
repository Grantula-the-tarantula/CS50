#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

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
int comparator(const void *l, const void *r);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
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
    //Check the name of candidate and update ranks array to their preference
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //Take ranks array and create two-dimensional preferences array
    //Compares each value of ranks array to other values
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (ranks[i] != ranks[j])
            {
                preferences[ranks[i]][ranks[j]]++;

            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //Compare preferences[i][j] with preferences[j][i] and return winner/loser in pairs array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }

        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
// creating function to be used by quicksort algorithm
int comparator(const void *l, const void *r)
{
    //Get address of both candidates in pairs array
    pair *orderL = (pair *)l;
    pair *orderR = (pair *)r;

    //use r - l to give descending order
    return (preferences[orderR->winner][orderR->loser] - preferences[orderL->winner][orderL->loser]);

}
void sort_pairs(void)
{

    // Take input from comparator function and use in quicksort (descending order)
    qsort(pairs, pair_count, sizeof(pair), comparator);

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    //Adds edges to locked array in order of largest victory (from sorted pairs array)
    int check;

    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        //Check if this causes any cycles.  If it does change locked array at that position back to false and continue to print_winner

        // int counter = 0;

        // for (int j = 0; j < candidate_count; j++)
        // {
        //     for (int k = 0; k < candidate_count; k++)
        //     {
        //         if (locked[k][j] == false)
        //         {
        //             counter++;
        //         }

        //     }
        // }

        // if (counter < 3)
        // {
        //     locked[pairs[i].winner][pairs[i].loser] = false;
        // }


    }

    return;
}

// Print the winner of the election
void print_winner(void)
{

    //Search locked array for candidate with all column marked false

    int counter = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                counter++;
            }
        }

        //Prints name that is the source (problem assumes there is one source)
        if (counter == candidate_count)
        {
            printf("%s\n", candidates[i]);

        }
    }

    return;
}

