#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"
#include "stdbool.h"
#include "math.h"
#include "windows.h"

//Programmer: Abhinav Sharma

typedef struct enemy_Node{
    int enemy_health;
    int enemy_gold;
}
enemy_Node;

typedef struct Tree_Node
{
    int health_stats;
    int gold_at_node;
    int level_of_node;
    bool enemy_status;
    struct Tree_Node * left;
    struct Tree_Node * right;
}
Tree_Node;

int node_count = 0, number_of_iterations_of_game = 0, userHealth = 100, userGold = 100;  //Global variables for health and gold of user, and level tracker
int maxUserHealth = INT_MIN, maxUserGold = INT_MIN; //

bool isPrime(int n);

enemy_Node* arrEnemy[5];    //To stores enemy details

Tree_Node* rootNode;    // Root Node of Tree

//Array of enemy funciton definition
void initialise_Enemy_Array();

//Initialises nodes of tree with data and returns the pointer to the nodes 
Tree_Node* initialise_Tree_Node()
{
    int health = rand() % 50 + 1;
    int gold  = rand() % 101 + 0;
    int level = 0;

    bool p_enemy_status = false;

    Tree_Node *rn = malloc(sizeof(Tree_Node));
    rn->enemy_status = p_enemy_status;
    rn->gold_at_node = gold;
    rn->health_stats = health;
    rn->level_of_node = level;
    rn->left = NULL;
    rn->right = NULL;

    return rn;
}
//Function to initialise the tree definition
void initialise_Tree();

//Function to display End message if NULL is encountered definition
void endMessageIfNULL();

//Function to display End message if health less than or equals to zero definition
void endMessageIfHealthZeroOrLessThanZero();

//Function to display Print message indicating enemy has appeared
void enemyHasAppearedMessage();

//Function to display gold status of User at the moment
void displayGoldCoins();

//Function to display health status of User at the moment
void displayHealth();

//Tree Traversal Method based on user Input Definition
void TreeTraversalByUser(Tree_Node* node, int level, char choice);

//Inorder traversal for tree Definition
void inorder_traversal(Tree_Node* node, Tree_Node** arr);

//Tree Nodes Deletion Method Definition
void deleteTree();

int main()
{
    printf("\t\t Welcome to TreePaths \t\t\n\n\n");
    
    int choice = -1;
    
    do
    {
        for (int i = 0; i < 2; ++i)
                Beep(500, 1000);

        printf("\t\t Press 1 to start the game \t\t\n");
        printf("\t\t Press 0 to exit \t\t\n");
        printf("\t\t Enter your choice: ");
        scanf("%d", &choice);

        printf("\n\n");    
            
        switch (choice)
        {
            case 1:
                initialise_Enemy_Array();
                initialise_Tree();
                Beep(523, 500);
                number_of_iterations_of_game++;
                TreeTraversalByUser(rootNode, 0, 's');
                break;
            
            case 0:
                printf("\t\t Exiting game... \t\t\n\n");
                for (int i = 0; i < 2; ++i)
                    Beep(500, 1000);
                break;

            default:
                printf("\t\t Please enter correct option number! \t\t\n");
                for (int i = 0; i < 2; ++i)
                    Beep(500, 200);
                break;
        }

        //Deleting the old tree
        if (choice == 1)    deleteTree();
        
        if (choice == 0 && number_of_iterations_of_game == 0)
        {
            maxUserHealth = 0, maxUserGold = 0;
        }
        else if (choice == 0 && number_of_iterations_of_game > 0)
        {    
            maxUserHealth = max(userHealth, maxUserHealth), maxUserGold = max(maxUserGold, userGold);
            userHealth = 100, userGold = 100;
            node_count = 0;
        }
        else if (choice == 1)
        {
            maxUserHealth = max(userHealth, maxUserHealth), maxUserGold = max(maxUserGold, userGold);
            userHealth = 100, userGold = 100;
            node_count = 0;
        }

    } while (choice != 0);
        
        //File handling 
        FILE *fileptr = fopen("scoreCard.txt", "w");

        fprintf(fileptr, "Number of games played in total: %d\nMaximum Gold at the End: %d\n\n", number_of_iterations_of_game, maxUserGold);
        
        fclose(fileptr);

    return 0;
}

//Checks if number is prime or not. Used for level checking and enemy presence
bool isPrime(int n)
{
    int num = sqrt(n);

    for (int i = 2; i <= num; ++i)
    {
        if (n % i == 0) return false;
    }

    return true;
}



//Initialises the tree or creates it
void initialise_Tree()
{
    rootNode = initialise_Tree_Node();

    rootNode->left = initialise_Tree_Node();
    rootNode->right = initialise_Tree_Node();

    rootNode->left->left = initialise_Tree_Node();
    rootNode->left->right = initialise_Tree_Node();
    rootNode->right->left = initialise_Tree_Node();

    rootNode->left->left->left = initialise_Tree_Node();
    rootNode->left->left->right = initialise_Tree_Node();
    rootNode->left->right->left = initialise_Tree_Node();
    rootNode->right->left->left = initialise_Tree_Node();
    rootNode->right->left->right = initialise_Tree_Node();
    
    rootNode->left->left->right->left = initialise_Tree_Node();
    rootNode->left->left->right->right = initialise_Tree_Node();
    rootNode->left->right->left->right = initialise_Tree_Node();
    rootNode->right->left->right->left = initialise_Tree_Node();


    rootNode->left->left->right->left->left = initialise_Tree_Node();
    rootNode->left->left->right->right->right = initialise_Tree_Node();
    rootNode->right->left->right->left->left = initialise_Tree_Node();
    rootNode->right->left->right->left->right = initialise_Tree_Node();
}

//Array of enemy funciton
void initialise_Enemy_Array()
{
    for (int i = 0; i < 5; ++i)
    {
        enemy_Node *n1 = malloc(sizeof(enemy_Node));
        n1->enemy_gold = rand() % 1000 + 1;
        n1->enemy_health = rand() % 50 + 30;
        arrEnemy[i] = n1;
    }    
}

//End message if NULL is encountered
void endMessageIfNULL()
{
    printf("\n\n");
    printf("\t\t You have reached the END!!! \t\t\n");
    printf("\t\t Your health at the END: %d \t\t\n", userHealth);
    printf("\t\t Your gold at the END: %d \t\t\n\n", userGold);
}

//End message if health less than or equals to zero
void endMessageIfHealthZeroOrLessThanZero()
{
    printf("\t\t You DIED!!! \t\t\n\n");
}

//Print message indicating enemy has appeared
void enemyHasAppearedMessage()
{
    printf("\t\t Enemy has appeared! \t\t\n\n");
}

//Function to display gold status of User at the moment
void displayGoldCoins()
{
    printf("\t\t Player Gold coins: %d \t\t\n\n", userGold);
}

//Function to display health status of User at the moment
void displayHealth()
{
    printf("\t\t Player Health: %d \t\t\n\n", userHealth);
}

//Tree Traversal Method based on user Input
void TreeTraversalByUser(Tree_Node* node, int level, char choice)
{
    Beep(523, 500);
    if (node == NULL)
    {
        endMessageIfNULL();
        return;
    }
    
    if (isPrime(level) && (choice == 'L') && (level != 2))
    {
        node->enemy_status = true;
        int ene_index = rand() % 5;
        node->health_stats = ((arrEnemy[ene_index]->enemy_health) * (-1));
        node->gold_at_node = ((arrEnemy[ene_index]->enemy_gold));
        enemyHasAppearedMessage();
    }

    userHealth += node->health_stats;
    userGold += node->gold_at_node;

    if (userHealth <= 0)
    {
        endMessageIfHealthZeroOrLessThanZero();
        return;
    }
    else
    {   
        if (node->enemy_status == true)
        {
            printf("\t\t You defeated the enemy!!! \t\t\n");
            printf("\t\t You gained Gold Coins, but lost Health!!! \t\t\n\n");
            displayHealth();
            displayGoldCoins();
        }
        else{
            printf("\t\t You gained Gold Coins and Health!!! \t\t\n\n");
            displayHealth();
            displayGoldCoins();
        }

        //
        char ch1 = '\0', ch2 = '\0';
        while (ch2 != 'L' && ch2 != 'R')
        {
            printf("\t\t Press 'L' to go Left, 'R' to go right: ");
            scanf("%c", &ch1);
            scanf("%c", &ch2);
        }

        printf("\n");
        if (ch2 == 'L')
        {
            TreeTraversalByUser(node->left, level + 1, ch2);
        }
        else if (ch2 == 'R') {
            TreeTraversalByUser(node->right, level + 1, ch2);
        }
    }
}

//Inorder traversal for tree
void inorder_traversal(Tree_Node* node, Tree_Node** arr)
{   
    if (node == NULL)
    {
        return;
    }
    
    inorder_traversal(node->left, arr);
    arr[node_count++] = node;
    inorder_traversal(node->right, arr);
}

//Tree Nodes Deletion Method Definition
void deleteTree()
{
    Tree_Node* arr[20];

    inorder_traversal(rootNode, arr);

    for (int i = 0; i < node_count; ++i)
    {
        Tree_Node* n1 = arr[i];
        free(n1);
    }
}