//Creating a casino game -- 777 Slot Machine

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <limits>


using namespace std; 

//Function of the game
int play(int &initialMoney, int &bet);
int validateBet(int &initialMoney, int &bet);

//Declaring constant values
int const jackpot = 100, multiplier = 5, maxSlot = 7, minSlot = 1;

//Main game function
int main(){
    int initialMoney = 0, bet = 0, deposit = 0, ans;
    
    //Seeds random number generator 
    srand(static_cast<unsigned int>(time(0)));
    
    //Welcome message
    cout << "-----------------------------" << endl;
    cout << " Welcome to 777 Slot Machine " << endl;
    cout << "-----------------------------" << endl;

//Main game loop: continues until the player exits
do{
    //Display menu
    cout << "Do you want to play 777 Slot Machine? \n 1. Play \n 2. Deposit to wallet \n 3. View wallet balance \n 4. Exit the game \n \n";
    cin >> ans;
    
    //Validate menu input (1-4)
    while (cin.fail() || (ans < 1 || ans > 4)) {
            cout << "That is not a valid response! Please enter a number between 1 and 4.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter your choice: ";
            cin >> ans;
    }
    //Handle menu choice
    if (ans == 1){ //Play game
        //If bet is valid, play a round
        if (validateBet(initialMoney, bet) == 1) { // Check if a valid bet was placed
            play(initialMoney, bet);               // Only play if the bet was valid
        }
    }
    
    else if (ans == 2){ //Deposit a money
        cout << "Please enter a deposit: \n" ;
        cin >> deposit;
        
        //Validate deposit
        while(cin.fail() || deposit <= 0){
            cout << "That is not a valid response! Please enter a valid deposit \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter deposit: ";
            cin >> deposit;
        }   
        
        initialMoney += deposit; //Deposits money to initialMoney var
        cout << "Wallet balance: \n" << initialMoney << "\n \n"; //Show initialMoney balance
    }
    
    else if (ans == 3){ //View balance
        cout << "Wallet balance: \n" << initialMoney << endl;
        cout << "-----------------------------" << "\n \n" << endl;

    }
    else if(ans == 4){ //Exits the game
        cout << "Thanks for playing! \n";
    }
    
}

while(ans != 4);

    return 0; 
}

// Bet Validation Function
// Ensures the player enters a valid, affordable bet.
// Returns 1 for valid bet, 0 for invalid/insufficient funds.
int validateBet(int &initialMoney, int &bet){
        while (true) { 
            cout << "How much would you like to bet? \n";
            cin >> bet;
            
            if (cin.fail() || bet <= 0) {
                cout << "Invalid bet. Please enter a positive number.\n";
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                continue; // 
        }

        // Check if there is sufficient funds
            if (initialMoney == 0) {
                cout << "\nInsufficient balance. Your wallet is empty.\n";
                cout << "Please deposit money first to play.\n";
                return 0; // Indicate that a valid bet cannot be placed because wallet is empty
            } 
            
            else if (initialMoney >= bet) {
            // Bet is valid and affordable
            return 1; // Return 1 to indicate success: a valid bet is ready
            } 
            
            else {
            // initialMoney is not 0, but it's less than the bet
            cout << "\nInsufficient balance. Your current balance is: $" << initialMoney << "\n";
            cout << "Please enter a bet less than or equal to your balance.\n";
            continue; // Go back to the start of the loop to ask for a new bet
            }
        }
        return 0;
}

int play(int &initialMoney, int &bet){

    //Generate 3 random numbers from 1-7
    int num1 = (rand() % maxSlot) + minSlot;
    int num2 = (rand() % maxSlot) + minSlot;
    int num3 = (rand() % maxSlot) + minSlot;

    cout << "The result is: \n";
    cout << num1 << " " << num2 << " " << num3 << "\n";

    //Check if the 3 number has 1, 2, 3 7's to check if they won the game
    int seven_counts = 0;
    if (num1 == 7) seven_counts++;
    if (num2 == 7) seven_counts++;
    if (num3 == 7) seven_counts++;
    
    if(seven_counts == 3){
        cout << "You won the jackpot price of " << jackpot << "\n";
        initialMoney += 100;
        cout << "-----------------------------" << "\n \n" << endl;
    }
    else if (seven_counts == 2){
        cout << "You have won two 7's \n";
        initialMoney = initialMoney + (bet * multiplier);
        cout << "-----------------------------" << "\n \n" << endl;
    }
    else {
        cout << "Try your luck next time! \n";
        initialMoney -= bet;
        cout << "-----------------------------" << "\n \n" << endl;
    }

    return initialMoney;
}