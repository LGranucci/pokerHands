#include <iostream>
#include <random>
#include <bits/stdc++.h>
struct carta
{
    char seme;
    int numero;
};
//Asso vale 14
bool compareCarta(carta i1, carta i2)
{
    return (i1.numero> i2.numero);
}


int get_random_card(int l, int u){
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(l, u);

    // Generate a random number
    int random_number = dis(gen);
    return random_number;
}

void stampa_mazzo(carta* mazzo,  int len){
    for (int i = 0; i < len; i++)
    {
        std::cout<<mazzo[i].numero<< " di "<< mazzo[i].seme <<std::endl;
    }
     std::cout<<"------------------------------"<<std::endl;
    std::cout<<"fine stampa mazzo"<<std::endl;
    std::cout<<"------------------------------"<<std::endl;
    return;
}

bool scalaCheck(carta* mano, int len, bool* colore){
    int conto = 1;
    bool asso = false;  
    int contoSeme = 1;
    char semeAsso = ' ';
    for(int i = 1; i < len; i++){
        if (mano[i - 1].numero == mano[i].numero - 1){
            conto++;
            if(mano[i - 1].seme == mano[i].seme){
                contoSeme++;
            }
            else{
                contoSeme = 0;
            }
        }
        else{
            contoSeme = 0;
        }
        if(mano[i].numero == 2 && asso){
            conto++;
            if(mano[i].seme == semeAsso){
                contoSeme++;
            }
        }
        if(mano[i].numero == 14){
            asso = true;
            semeAsso = mano[i].seme;
        }
        if(conto == 5){
            if(contoSeme >= 5)
                *colore = true;
            return true;
        }
    }
    return false;
}


bool flushCheck(carta* mano, int len, const char* semi){
    int vSemi[4] = {0, 0, 0, 0};
    //estremamente brute-force;
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < 4; j++){
            if(mano[i].seme == semi[j]){
                vSemi[j]++;
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if(vSemi[i] >= 5){
            return true;
        }
    }
    return false;
    
}


//per mischiare, scambia index di mazzo per 200 volte
void shuffle_mazzo(carta* mazzo, int len){
    
    const int NUM_SHUFFLE = 200;
    for (int i = 0; i < NUM_SHUFFLE; i++)
    {
        int index1 = get_random_card(0, 51);
        int index2 = get_random_card(0, 51);
        carta aux;
        //exchanges two cards
        aux.numero = mazzo[index1].numero;
        aux.seme = mazzo[index1].seme;
        mazzo[index1].numero = mazzo[index2].numero;
        mazzo[index1].seme = mazzo[index2].seme;
        mazzo[index2].numero = aux.numero;
        mazzo[index2].seme = aux.seme;
    }
    
    
}

carta* get_hand(carta* mazzo, int num){
    carta* mano = new carta[num];
    for (int i = 0; i < num; i++)
    {
        mano[i].numero = mazzo[i].numero;
        mano[i].seme = mazzo[i].seme; 
    }

    return mano; 
}

//[0, 1, 2, 2 , 3]
//[ , ]



int main(){
    carta mazzo[52];
    const char semi[4] = {'c', 'd', 'p', 'f'};
    int count = 0;
    for(int s = 0; s < 4; s++) {
        char currentSeme = semi[s];
    
        for(int n = 2; n <= 14; n++) {
            mazzo[count].seme = currentSeme;
            mazzo[count].numero = n;
            count++;
        }
    }
    
   
    shuffle_mazzo(mazzo, 52);
    stampa_mazzo(mazzo, 52);
    carta* mano1  =get_hand(mazzo, 7);
    stampa_mazzo(mano1, 7);
    std::sort(mano1, mano1 + 7, compareCarta);
    stampa_mazzo(mano1, 7);
    bool colore = false;
    std::cout<<scalaCheck(mazzo, 7, &colore);
    if(colore){
        std::cout<<"colore!";
    }
    std::cout<<std::endl;

    std::cout<<flushCheck(mazzo, 7, semi)<<std::endl;
    return 0;
}