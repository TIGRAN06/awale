#include <iostream>

#define SIZE12 12
#define SIZE6 6

struct Position {
    int cells24[2 * SIZE12];
    int cells12[2 * SIZE6];
    int computer_play;
    int seeds_player;
    int seeds_computer;
    int state;
};

void showGame(Position * pos) {
    if (pos->state) {
        std::cout << "Human Score " << pos->seeds_player << "\n" << std::endl;
        std::cout << "IA Score " << pos->seeds_computer << "\n" << std::endl;
        for (int i = 0; i < SIZE12; i++) {
            if (i == SIZE12 - 1) {
                std::cout << "_" << pos->cells24[i] << "_ \n";
            } else std::cout << "_" << pos->cells24[i] << "_ ";
        }
        for (int i = 0; i < SIZE12; i++) {
            std::cout << "_" << pos->cells24[2 * SIZE12 - 1 - i] << "_ ";
        }
        std::cout << "\n" << std::endl;
    } else {
        std::cout << "Human Score " << pos->seeds_player << "\n" << std::endl;
        std::cout << "IA Score " << pos->seeds_computer << "\n" << std::endl;
        for (int i = 0; i < SIZE6; i++) {
            if (i == SIZE6 - 1) {
                std::cout << "_" << pos->cells12[i] << "_ \n";
            } else std::cout << "_" << pos->cells12[i] << "_ ";
        }
        for (int i = 0; i < SIZE6; i++) {
            std::cout << "_" << pos->cells12[2 * SIZE6 - 1 - i] << "_ ";
        }
        std::cout << "\n" << std::endl;
    }
}

int validMove(Position * pos, int computer_play, int indexCells) {
    if(pos->state){
        if (computer_play) {
            return pos->cells24[2 * indexCells];
        }
        else {
            return pos->cells24[2 * indexCells + 1];
        }
    }
    else {
        if (computer_play) {
            return pos->cells12[2 * indexCells];
        }
        else {
            return pos->cells12[2 * indexCells + 1];
        }
    }
}

int playMove(Position * pos_next, Position * pos_current, int computer_play, int indexCells) {
    if (pos_current->state){
        int grainesCell;
        int indexIterator;
        int playedCell;
        int player = computer_play;
        pos_next->seeds_computer = pos_current->seeds_computer;
        pos_next->seeds_player = pos_current->seeds_player;
        pos_next->state = pos_current->state;
        pos_next->computer_play = !pos_current->computer_play;
        for (int i = 0; i < 2 * SIZE12; i++) {
            pos_next->cells24[i] = pos_current->cells24[i];
        }
        if (player) {
            grainesCell = pos_next->cells24[2 * indexCells ];
            indexIterator = 2 * indexCells ;
        }
        else {
            grainesCell = pos_next->cells24[2 * indexCells+1];
            indexIterator = 2 * indexCells+1;
        }
        playedCell = indexIterator;
        pos_next->cells24[indexIterator] = 0;
        indexIterator++;
        if (indexIterator == 2 * SIZE12) {
            indexIterator = 0;
        }
        for (int i = 0; i < grainesCell;) {
            if (indexIterator != playedCell) {
                pos_next->cells24[indexIterator] += 1;
                grainesCell--;
            }
            indexIterator++;
            if (indexIterator == 2 * SIZE12) {
                indexIterator = 0;
            }
        }
        if (indexIterator == 0){
            indexIterator= 2 * SIZE12 - 1;}
        else indexIterator--;
        if (computer_play) {
            while ((pos_next->cells24[indexIterator] == 3) | (pos_next->cells24[indexIterator] == 2)) {
                pos_next->seeds_computer += pos_next->cells24[indexIterator];
                pos_next->cells24[indexIterator] = 0;
                if (indexIterator == 0){
                    indexIterator= 2 * SIZE12 - 1;}
                else indexIterator--;
            }
        }
        else {
            while ((pos_next->cells24[indexIterator] == 3) | (pos_next->cells24[indexIterator] == 2)) {
                pos_next->seeds_player += pos_next->cells24[indexIterator];
                pos_next->cells24[indexIterator] = 0;
                if (indexIterator == 0){
                    indexIterator= 2 * SIZE12 - 1;}
                else indexIterator--;
            }
        }
        int cpt = 0;
        if (computer_play) {
            for (int i = 0; i < SIZE12; i++) {
                cpt += pos_next->cells24[2 * i + 1];
            }
        }
        else {
            for (int i = 0; i < SIZE12; i++) {
                cpt += pos_next->cells24[2 * i];
            }
        }

        if (cpt == 0){
            if (computer_play) {
                for (int i = 0; i < SIZE12; i++) {
                    pos_next->seeds_computer += pos_next->cells24[2 * i];
                    pos_next->cells24[2 * i]=0;
                }
            }
            else {
                for (int i = 0; i < SIZE12; i++) {
                    pos_next->seeds_player += pos_next->cells24[2 * i + 1];
                    pos_next->cells24[2 * i + 1]=0;
                }
            }
        }
        if(96 - pos_next->seeds_computer - pos_next->seeds_player <= 48){
            pos_next->state=0;
            for (int q = 0; q < SIZE12; q++){
                pos_next->cells12[q]= pos_next->cells24[2 * q] + pos_next->cells24[2 * q + 1];
            }
        }
        return 0;
    }
    else {
        int grainesCell;
        int indexIterator;
        int playedCell;
        int player = computer_play;
        pos_next->seeds_computer = pos_current->seeds_computer;
        pos_next->seeds_player = pos_current->seeds_player;
        pos_next->state = pos_current->state;
        pos_next->computer_play = !pos_current->computer_play;
        for (int i = 0; i < 2 * SIZE6; i++) {
            pos_next->cells12[i] = pos_current->cells12[i];
        }

        if (player) {
            grainesCell = pos_next->cells12[2 * indexCells];
            indexIterator = 2 * indexCells;
        }
        else {
            grainesCell = pos_next->cells12[2 * indexCells + 1];
            indexIterator = 2 * indexCells + 1;
        }
        playedCell = indexIterator;
        pos_next->cells12[indexIterator] = 0;
        indexIterator++;
        if (indexIterator == 2 * SIZE6) {
            indexIterator = 0;
        }
        for (int i = 0; i < grainesCell;) {
            if (indexIterator != playedCell) {
                pos_next->cells12[indexIterator] += 1;
                grainesCell--;
            }
            indexIterator++;
            if (indexIterator == 2 * SIZE6) {
                indexIterator = 0;
            }
        }
        if (indexIterator == 0){
            indexIterator= 2 * SIZE6 - 1;}
        else indexIterator--;
        if (computer_play) {
            while ((pos_next->cells12[indexIterator] == 3) | (pos_next->cells12[indexIterator] == 2)) {
                pos_next->seeds_computer += pos_next->cells12[indexIterator];
                pos_next->cells12[indexIterator] = 0;
                if (indexIterator == 0){
                    indexIterator= 2 * SIZE6 - 1;}
                else indexIterator--;
            }
        }
        else {
            while ((pos_next->cells12[indexIterator] == 3) | (pos_next->cells12[indexIterator] == 2)) {
                pos_next->seeds_player += pos_next->cells12[indexIterator];
                pos_next->cells12[indexIterator] = 0;
                if (indexIterator == 0){
                    indexIterator= 2 * SIZE6 - 1;}
                else indexIterator--;
            }
        }
        int cpt = 0;
        if (computer_play) {
            for (int i = 0; i < SIZE6; i++) {
                cpt += pos_next->cells12[2 * i + 1];
            }
        }
        else {
            for (int i = 0; i < SIZE6; i++) {
                cpt += pos_next->cells12[2 * i];
            }
        }
        if (cpt == 0){
            if (computer_play) {
                for (int i = 0; i < SIZE6; i++) {
                    pos_next->seeds_computer += pos_next->cells12[2 * i];
                    pos_next->cells12[2 * i]=0;
                }
            }
            else {
                for (int i = 0; i < SIZE6; i++) {
                    pos_next->seeds_player += pos_next->cells12[2 * i + 1];
                    pos_next->cells12[2 * i + 1]=0;
                }
            }
        }
        return 0;
    }
}

int evaluation(Position * pos, int computer_play, int depth) {
    return pos->seeds_computer - pos->seeds_player;
}

int finalPosition(Position * pos, int computer_play, int depth) {
    if (pos->state){
        int cpt = 0;
        if (computer_play) {
            for (int i = 0; i < SIZE12; i++) {
                cpt += pos->cells24[2 * i];
            }
        }
        else {
            for (int i = 0; i < SIZE12; i++) {
                cpt += pos->cells24[2 * i + 1];
            }
        }
        return (!cpt);
    }
    else {
        int cpt = 0;
        if (computer_play) {
            for (int i = 0; i < SIZE6; i++) {
                cpt += pos->cells12[2 * i];
            }
        }
        else {
            for (int i = 0; i < SIZE6; i++) {
                cpt += pos->cells12[2 * i + 1];
            }
        }
        return (!cpt);
    }
}

int minMaxValue(Position* pos_current, int computer_play, int depth, int depthMax, int alpha, int beta){
    if (pos_current->state) {
        int alphaLocal = alpha;
        int betaLocal = beta;
        int tab_values[SIZE12];
        if (computer_play) {
            for (int i = 0; i < SIZE12; i++) {
                tab_values[i] = INT32_MIN;
            }
        } else {
            for (int i = 0; i < SIZE12; i++) {
                tab_values[i] = INT32_MAX;
            }
        }
        Position pos_next;
        if (finalPosition(pos_current, computer_play, depth)) {
            if (pos_current->seeds_computer > 48) {
                return 96 + depthMax - depth;
            } else {
                if (pos_current->seeds_player > 48) {
                    return -96;
                } else {
                    if ((pos_current->seeds_computer == 48) & (pos_current->seeds_player == 48)) {
                        return 0;
                    }
                }
            }
        }
        if (depth == depthMax) {
            return evaluation(pos_current, computer_play, depth);
        }
        int value;
        if (computer_play) {
            value = INT32_MIN;
        } else {
            value = INT32_MAX;
        }
        if (depth == 0) {
            for (int i = 0; i < SIZE12; i++) {
                if (validMove(pos_current, computer_play, i)) {
                    playMove(&pos_next, pos_current, computer_play, i);
                    tab_values[i] = minMaxValue(&pos_next, !computer_play, depth + 1, depthMax, alphaLocal, betaLocal);
                    value = std::max(value, tab_values[i]);
                    if (value >= betaLocal) {
                        return value;
                    }
                    alphaLocal = std::max(alphaLocal, value);
                } else {
                    if (computer_play) {
                        tab_values[i] = -1000;
                    } else {
                        tab_values[i] = +1000;
                    }
                }
            }
            int indexMove = 0;
            if (computer_play) {
                for (int i = 1; i < SIZE12; i++) {
                    if (tab_values[i] > tab_values[indexMove]) {
                        indexMove = i;
                    }
                }
            } else {
                for (int i = 1; i < SIZE12; i++) {
                    if (tab_values[i] < tab_values[indexMove]) {
                        indexMove = i;
                    }
                }
            }
            return indexMove;
        } else {
            for (int i = 0; i < SIZE12; i++) {
                if (validMove(pos_current, computer_play, i)) {
                    playMove(&pos_next, pos_current, computer_play, i);
                    if (computer_play) {
                        tab_values[i] = minMaxValue(&pos_next, !computer_play, depth + 1, depthMax, alphaLocal, betaLocal);
                        value = std::max(value, tab_values[i]);
                        if (value >= betaLocal) {
                            return value;
                        }
                        alphaLocal = std::max(alphaLocal, value);
                    } else {
                        tab_values[i] = minMaxValue(&pos_next, !computer_play, depth + 1, depthMax, alphaLocal, betaLocal);
                        value = std::min(value, tab_values[i]);
                        if (alphaLocal >= value) {
                            return value;
                        }
                        betaLocal = std::min(betaLocal, value);
                    }
                } else {
                    if (computer_play) {
                        tab_values[i] = -1000;
                    } else {
                        tab_values[i] = +1000;
                    }
                }
            }
            return value;
        }
    }
    else {
        int alphaLocal = alpha;
        int betaLocal = beta;
        int tab_values[SIZE6];
        if (computer_play) {
            for (int i = 0; i < SIZE6; i++) {
                tab_values[i] = INT32_MIN;
            }
        } else {
            for (int i = 0; i < SIZE6; i++) {
                tab_values[i] = INT32_MAX;
            }
        }
        Position pos_next;
        if (finalPosition(pos_current, computer_play, depth)) {
            if (pos_current->seeds_computer > 48) {
                return 96 + depthMax - depth;
            } else {
                if (pos_current->seeds_player > 48) {
                    return -96;
                } else {
                    if ((pos_current->seeds_computer == 48) & (pos_current->seeds_player == 48)) {
                        return 0;
                    }
                }
            }
        }

        if (depth == depthMax) {
            return evaluation(pos_current, computer_play, depth);
        }

        int value;
        if (computer_play) {
            value = INT32_MIN;
        } else {
            value = INT32_MAX;
        }
        if (depth == 0) {
            for (int i = 0; i < SIZE6; i++) {
                if (validMove(pos_current, computer_play, i)) {
                    playMove(&pos_next, pos_current, computer_play, i);
                    tab_values[i] = minMaxValue(&pos_next, !computer_play, depth + 1, depthMax, alphaLocal, betaLocal);
                    value = std::max(value, tab_values[i]);
                    if (value >= betaLocal) {
                        return value;
                    }
                    alphaLocal = std::max(alphaLocal, value);
                } else {
                    if (computer_play) {
                        tab_values[i] = -1000;
                    } else {
                        tab_values[i] = +1000;
                    }
                }
            }
            int indexMove = 0;
            if (computer_play) {
                for (int i = 1; i < SIZE6; i++) {
                    if (tab_values[i] > tab_values[indexMove]) {
                        indexMove = i;
                    }
                }
            }
            else {
                for (int i = 1; i < SIZE6; i++) {
                    if (tab_values[i] < tab_values[indexMove]) {
                        indexMove = i;
                    }
                }
            }
            return indexMove;
        } else {
            for (int i = 0; i < SIZE6; i++) {
                if (validMove(pos_current, computer_play, i)) {
                    playMove(&pos_next, pos_current, computer_play, i);
                    if (computer_play) {
                        tab_values[i] = minMaxValue(&pos_next, !computer_play, depth + 1, depthMax, alphaLocal, betaLocal);
                        value = std::max(value, tab_values[i]);
                        if (value >= betaLocal) {
                            return value;
                        }
                        alphaLocal = std::max(alphaLocal, value);
                    } else {
                        tab_values[i] = minMaxValue(&pos_next, !computer_play, depth + 1, depthMax, alphaLocal, betaLocal);
                        value = std::min(value, tab_values[i]);
                        if (alphaLocal >= value) {
                            return value;
                        }
                        betaLocal = std::min(betaLocal, value);
                    }

                } else {
                    if (computer_play) {
                        tab_values[i] = -1000;
                    } else {
                        tab_values[i] = +1000;
                    }
                }
            }
            return value;
        }
    }
}

void HUMANplay(Position * pos_next, Position * pos_current) {
    int move = 0;
    int playedCell;
    while (!move) {
        std::cout << std::endl << "Please type number :";
        std::cin >> playedCell;
        move = validMove(pos_current, pos_current->computer_play, ((playedCell - 1) / 2));
    }
    playMove(pos_next, pos_current, pos_current->computer_play, ((playedCell - 1) / 2));
    showGame(pos_next);
}

void IAplay(Position * pos_next, Position * pos_current) {
    if (pos_current->state){
        int depth = 10;
        int cpt = 0;
        for (int i = 0; i < 2 * SIZE12; i++) {
            cpt += pos_current->cells24[i];
        }
        if (cpt < 54) {
            depth = 18;
        }
        else {
            if (cpt < 65) {
                depth = 12;
            }
            else {
                if (cpt < 70) {
                    depth = 11;
                }
                else {
                    if (cpt < 94) {
                        depth = 11;
                    }
                }
            }
        }
        int minMaxMove = minMaxValue(pos_current, pos_current->computer_play, 0, depth, INT32_MIN, INT32_MAX);
        std::cout << "IA PLAY #################### " << 2 * minMaxMove + 1 << " ####################" << std::endl;
        playMove(pos_next, pos_current, pos_current->computer_play, minMaxMove);
        showGame(pos_next);
    }
    else {
        int depth = 10;
        int cpt = 0;
        for (int i = 0; i < 2 * SIZE6; i++) {
            cpt += pos_current->cells12[i];
        }
        if (cpt < 54) {
            depth = 18;
        }
        else {
            if (cpt < 65) {
                depth = 12;
            }
            else {
                if (cpt < 70) {
                    depth = 11;
                }
                else {
                    if (cpt < 94) {
                        depth = 11;
                    }
                }
            }
        }
        int minMaxMove = minMaxValue(pos_current, pos_current->computer_play, 0, depth, INT32_MIN, INT32_MAX);
        std::cout << "IA PLAY #################### " << 2 * minMaxMove + 1 << " ####################" << std::endl;
        playMove(pos_next, pos_current, pos_current->computer_play, minMaxMove);
        showGame(pos_next);
    }
}

int main() {
    Position pos;
    Position new_pos;
    std::cout << "FIRST ?";
    std::cout << std::endl;
    std::cin >> pos.computer_play;
    pos.seeds_computer = 0;
    pos.state = 1;
    pos.seeds_player = 0;
    for (int i = 0; i < 2 * SIZE12; i++) {
        pos.cells24[i] = 4;

    }
    for (int i = 0; i < 2 * SIZE6; i++) {
        pos.cells12[i] = 0;

    }
    if (pos.computer_play) {
        while ((96 - pos.seeds_player - pos.seeds_computer) >= 8) {
            IAplay(&new_pos, &pos);
            if ((96 - new_pos.seeds_player - new_pos.seeds_computer) < 8) {
                break;
            }
            HUMANplay(&pos, &new_pos);
        }
    }
    else {
        while ((96 - pos.seeds_player - pos.seeds_computer) >= 8) {
            HUMANplay(&new_pos, &pos);
            if ((96 - new_pos.seeds_player - new_pos.seeds_computer) < 8) {
                break;
            }
            IAplay(&pos, &new_pos);
        }
    }

    return 0;
}
