#include <iostream>
#include <random>
struct carta
{
    char seme;
    int numero;
};




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



int main(){
    carta mazzo[52];
    const char semi[4] = {'c', 'd', 'p', 'f'};
    int count = 0;
    for(int s = 0; s < 4; s++) {
        char currentSeme = semi[s];
    
        for(int n = 1; n <= 13; n++) {
            mazzo[count].seme = currentSeme;
            mazzo[count].numero = n;
            count++;
        }
    }

   
    shuffle_mazzo(mazzo, 52);
    stampa_mazzo(mazzo, 52);
    carta* mano1  =get_hand(mazzo, 7);
    stampa_mazzo(mano1, 7);


    return 0;
}