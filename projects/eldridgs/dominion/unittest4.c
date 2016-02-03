#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define Random rand

int checkGetCost (int cardNum) {

    int r = getCost(cardNum);

    int i;
    if ( cardNum = curse){
       i = 0;
    }
    else if ( cardNum = estate) {
        i = 2;
    }
    else if ( cardNum = duchy){
        i = 5;
    }
    else if ( cardNum = province){
        i = 8;
    }
    else if ( cardNum = copper){
        i = 0;
    }
    else if ( cardNum = silver){
        i = 3;
    }
    else if ( cardNum = gold){
        i = 6;
    }
    else if ( cardNum = adventurer){
        i = 6;
    }
    else if ( cardNum = council_room){
        i = 5;
    }
    else if ( cardNum = feast){
        i = 4;
    }
    else if ( cardNum = gardens){
        i = 4;
    }
    else if ( cardNum = mine){
        i = 5;
    }
    else if ( cardNum = remodel){
        i = 4;
    }
    else if ( cardNum = smithy){
        i = 4;
    }
    else if ( cardNum = village){
        i = 3;
    }
    else if ( cardNum = baron){
        i = 4;
    }
    else if ( cardNum = great_hall){
        i = 3;
    }
    else if ( cardNum = minion){
        i = 5;
    }
    else if ( cardNum = steward){
        i = 3;
    }
    else if ( cardNum = tribute){
        i = 5;
    }
    else if ( cardNum = ambassador){
        i = 3;
    }
    else if ( cardNum = cutpurse){
        i = 4;
    }
    else if ( cardNum = embargo){
        i = 2;
    }
    else if ( cardNum = outpost){
        i = 5;
    }
    else if ( cardNum = salvager){
        i = 4;
    }
    else if ( cardNum = sea_hag){
        i = 4;
    }
    else if ( cardNum = treasure_map){
        i = 4;
    }

    assert (r == i);
}

int main () {
    int x;
    //test 1000 times
    for (x=0; x < 1000; x++){
        int cardCostCard = floor(Random() * 27);
        int i;
        int cardNum;

            if (cardCostCard == 0){
                cardNum = curse;
            }
            else if (cardCostCard == 1){
                cardNum = estate;
            }
            else if (cardCostCard == 2){
                cardNum = duchy;
            }
            else if (cardCostCard == 3){
                cardNum = province;
            }
            else if (cardCostCard == 4){
                cardNum = copper;
            }
            else if (cardCostCard == 5){
                cardNum = silver;
            }
            else if (cardCostCard == 6){
                cardNum = gold;
            }
            else if (cardCostCard == 7){
                cardNum = adventurer;
            }
            else if (cardCostCard == 8){
                cardNum = council_room;
            }
            else if (cardCostCard == 9){
                cardNum = feast;
            }
            else if (cardCostCard == 10){
                cardNum = gardens;
            }
            else if (cardCostCard == 11){
                cardNum = mine;
            }
            else if (cardCostCard == 12){
                cardNum = remodel;
            }
            else if (cardCostCard == 13){
                cardNum = smithy;
            }
            else if (cardCostCard == 14){
                cardNum = village;
            }
            else if (cardCostCard == 15){
                cardNum = baron;
            }
            else if (cardCostCard == 16){
                cardNum = great_hall;
            }
            else if (cardCostCard == 17){
                cardNum = minion;
            }
            else if (cardCostCard == 18){
                cardNum = steward;
            }
            else if (cardCostCard == 19){
                cardNum = tribute;
            }
            else if (cardCostCard == 20){
                cardNum = ambassador;
            }
            else if (cardCostCard == 21){
                cardNum = cutpurse;
            }
            else if (cardCostCard == 22){
                cardNum = embargo;
            }
            else if (cardCostCard == 23){
                cardNum = outpost;
            }
            else if (cardCostCard == 24){
                cardNum = salvager;
            }
            else if (cardCostCard == 25){
                cardNum = sea_hag;
            }
            else if (cardCostCard == 26){
                cardNum = treasure_map;
            }

        checkGetCost(cardNum);
    }
    return 0;
}
