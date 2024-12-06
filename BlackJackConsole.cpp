#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

struct Card {
    unsigned int value : 4;
    unsigned int mast : 2;
    unsigned int weight : 4;
};

#define SIZE 36

class Coloda {
    Card card[SIZE];
    int K = -1;

public:
    Coloda() {
        for (int i = 0; i < SIZE; i++) {
            card[i].value = i % 9;
            card[i].mast = i % 4;
            if (card[i].value >= 0 && card[i].value <= 4)
                card[i].weight = card[i].value + 6;
            else if (card[i].value == 8)
                card[i].weight = 11;
            else
                card[i].weight = card[i].value - 3;
        }
    }

    void PaintCard(bool comp, int value = 0, int mast = 0) {
        if (comp) {
            cout << " ----- \n";
            cout << "| *** |\n";
            cout << "| *** |\n";
            cout << "| *** |\n";
            cout << " ----- \n";
        }
        else {
            string mastSymbol[] = { "♥", "♦", "♣", "♠" };
            cout << " ----- \n";
            cout << "| " << mastSymbol[mast] << "   |\n";
            cout << "|  " << title[value] << "  |\n";
            cout << "|     |\n";
            cout << " ----- \n";
        }
    }

    bool GetCard(int& Player, int& Comp, char ans = 'y') {
        if (K + 2 >= SIZE) {
            cout << "Карты закончились!\n";
            return false;
        }

        K++;
        Player += card[K].weight;
        PaintCard(false, card[K].value, card[K].mast);

        K++;
        Comp += card[K].weight;
        PaintCard(true, card[K].value, card[K].mast);

        Proverka(Player, Comp, false);
        return true;
    }

    void Shuffle() {
        for (int i = 0; i < SIZE; i++) {
            int k = rand() % SIZE;
            swap(card[i], card[k]);
        }
    }

    void Proverka(int Player, int Comp, bool end) {
        if (end) {
            if (Player <= 21 && (Player > Comp || Comp > 21)) {
                cout << "\nPlayer wins! With " << Player << "\n";
                cout << "Comp loses! With " << Comp << "\n";
            }
            else if (Player > 21) {
                cout << "\nPlayer loses!\n";
                cout << "Comp has " << Comp << "\n";
            }
            else if (Comp <= 21 && (Comp > Player || Player > 21)) {
                cout << "\nComp wins! With " << Comp << "\n";
                cout << "Player loses! With " << Player << "\n";
            }
            else if (Comp > 21) {
                cout << "\nComp loses!\n";
                cout << "Player has " << Player << "\n";
            }
        }
        else {
            cout << "\nPlayer has: " << Player << "\n";
        }
    }

    void Play(int& Player, int& Comp) {
        char ans;
        cout << "\nPress 'q' to exit\n";
        do {
            cout << "\nContinue play and get one card? (y/n) -> ";
            cin >> ans;
            if (ans == 'y') {
                if (!GetCard(Player, Comp))
                    break;
            }
            else if (ans == 'n') {
                Proverka(Player, Comp, true);
                break;
            }
        } while (ans != 'q');
    }

    void PrintAll() {
        string mastSymbol[] = { "<3", "<>", "+", "*" }; // Hearts, Diamonds, Clubs, Spades
        for (int i = 0; i < SIZE; i++) {
            cout << title[card[i].value] << " " << mastSymbol[card[i].mast] << " " << card[i].weight << "\n";
        }
    }

private:
    string title[9] = { "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
};

int main() {

    Coloda k1;
    srand(static_cast<unsigned>(time(0)));
    k1.Shuffle();

    int Player = 0, Comp = 0;

    for (int i = 0; i < 2; i++)
        k1.GetCard(Player, Comp);

    k1.Play(Player, Comp);

    return 0;
}