#include "Game.h"

Game::Game()
{
	srand(time(NULL));
}
void Game::play()
{
	hero = Hero::getInstance();
    ChamberNode* start = prepareMap(hero);

    chambersTransitionFunction(start, hero);
}

ChamberNode* Game::prepareMap(Hero *hero) {
    //przygotowanie pokoji
    StartingRoom* r0 = new StartingRoom(hero);
    MonsterRoom* r1 = new MonsterRoom(hero);
    TrapRoom* r2 = new TrapRoom(hero);
    TraderRoom* r3 = new TraderRoom(hero);
    EmptyRoom* r4 = new EmptyRoom(hero);
    TreasureRoom* r5 = new TreasureRoom(hero);
    HealthRoom* r6 = new HealthRoom(hero);
    TreasureRoom* r7 = new TreasureRoom(hero);
    MonsterRoom* r8 = new MonsterRoom(hero);
    MonsterRoom* r9 = new MonsterRoom(hero);
    TrapRoom* r10 = new TrapRoom(hero);
    TraderRoom* r11 = new TraderRoom(hero);
    PotionRoom* r12 = new PotionRoom(hero);
    HealthRoom* r13 = new HealthRoom(hero);
    TraderRoom* r14 = new TraderRoom(hero);
    BossChamber* r15 = new BossChamber(hero);

    //stworzenie node'ów z pokojami
    ChamberNode* start = new ChamberNode(r0);
    ChamberNode* n1 = new ChamberNode(r1);
    ChamberNode* n2 = new ChamberNode(r2);
    ChamberNode* n3 = new ChamberNode(r3);
    ChamberNode* n4 = new ChamberNode(r4);
    ChamberNode* n5 = new ChamberNode(r5);
    ChamberNode* n6 = new ChamberNode(r6);
    ChamberNode* n7 = new ChamberNode(r7);
    ChamberNode* n8 = new ChamberNode(r8);
    ChamberNode* n9 = new ChamberNode(r9);
    ChamberNode* n10 = new ChamberNode(r10);
    ChamberNode* n11 = new ChamberNode(r11);
    ChamberNode* n12 = new ChamberNode(r12);
    ChamberNode* n13 = new ChamberNode(r13);
    ChamberNode* n14 = new ChamberNode(r14);
    ChamberNode* boss = new ChamberNode(r15);

    //podpięcie przejść w lewo i w prawo dla pokojów
    start->option1 = n1;
    start->option2 = n2;
    n1->option1 = n3;
    n1->option2 = n4;
    n2->option1 = n4;
    n2->option2 = n5;
    n3->option1 = n6;
    n4->option1 = n7;
    n4->option2 = n8;
    n5->option1 = n9;
    n6->option1 = n10;
    n7->option1 = n10;
    n8->option1 = n11;
    n9->option1 = n11;
    n9->option2 = n12;
    n10->option1 = n13;
    n11->option1 = n13;
    n12->option1 = n14;
    n13->option1 = boss;
    n14->option1 = boss;

    return start;
}

void Game::chambersTransitionFunction(ChamberNode *start, Hero *h)
{
    ChamberNode* curr = start;

    while (true) {
        curr->current->takeAction(h);

        if (h->getcurrentHealth() == 0)
            break;

        cout << endl;

        if (curr->option1 == nullptr)
            break;
        else if (curr->option2 == nullptr) {
            cout << "There is only one way out of this room..." << endl;
            cout << "Type L or R to go next" << endl;

            char choice;
            cin >> choice;
            while (choice != 'L' && choice != 'R') {
                cout << "Character not recognized, please retype" << endl;
                cin >> choice;
            }

            curr = curr->option1;
        }
        else {
            cout << "You see two passages - which way do you want to go?" << endl;
            cout << "[L] left" << endl;
            cout << "[R] right" << endl;

            char choice;
            cin >> choice;
            while (choice != 'L' && choice != 'R') {
                cout << "Character not recognized, please retype" << endl;
                cin >> choice;
            }

            if (choice == 'L')
                curr = curr->option1;
            else
                curr = curr->option2;
        }

        cout << endl;
    }
}

Game::~Game()
{
	delete hero;
}
