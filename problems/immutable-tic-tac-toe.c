#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef const uint32_t Index;

typedef const enum {
    E = '\0',
    X = 'X',
    O = 'O',
} PlayerKind;

typedef const struct {
    PlayerKind players[2];
    Index turn;
    PlayerKind field[9];
} Game;

Game insert(Game game, Index idx) {
    #define CELL(i) [i] = idx == i ? game.players[0] : game.field[i]
    return (Game) {
        .players = {game.players[1], game.players[0]},
        .field = {
            CELL(0), CELL(1), CELL(2),
            CELL(3), CELL(4), CELL(5),
            CELL(6), CELL(7), CELL(8),
        },
        .turn = game.turn + 1,
    };
    #undef CELL
}

bool game_over(Game game) {
    PlayerKind c = game.players[1];
    if (game.field[0] == c && game.field[1] == c && game.field[2] == c)
        return true;
    if (game.field[3] == c && game.field[4] == c && game.field[5] == c)
        return true;
    if (game.field[6] == c && game.field[7] == c && game.field[8] == c)
        return true;

    if (game.field[0] == c && game.field[3] == c && game.field[6] == c)
        return true;
    if (game.field[1] == c && game.field[4] == c && game.field[7] == c)
        return true;
    if (game.field[2] == c && game.field[5] == c && game.field[8] == c)
        return true;

    if (game.field[0] == c && game.field[4] == c && game.field[8] == c)
        return true;
    if (game.field[2] == c && game.field[4] == c && game.field[6] == c)
        return true;

    return false;
}

typedef const enum {
    STATE_GOING,
    STATE_DRAW,
    STATE_X = 'X',
    STATE_O = 'O',
} State;

typedef const struct {
    State state;
    Game game;
} GameState;

GameState step(GameState state, Index idx) {
    if (state.state) return state;

    Game new = insert(state.game, idx);
    return game_over(new) ?
        (GameState){
            .state = (State)new.players[1],
            .game = new,
        }: new.turn >= 9 ?
            (GameState){
                .state = STATE_DRAW,
                .game = new,
            }:
            (GameState){
                .state = STATE_GOING,
                .game = new,
            };
}

uint32_t io(Game game) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char c = game.field[i * 3 + j];
            printf(" %c", c == E ? '1' + i * 3 + j : c);
        }
        printf("\n");
    }

    while (true) {
        printf("------- %c: ", game.players[0]);
        char buffer[10] = {0};
        fgets(buffer, 10, stdin);
        uint32_t idx = (buffer[0] - '0') - 1;
        if (idx <= 8 && !game.field[idx]) {
            return idx;
        }
        printf("try again\n");
    }
}

GameState game(GameState state) {
    if (state.state) return state;
    Index idx = io(state.game);
    GameState new = step(state, idx);
    return game(new);
}

int main(void) {
    GameState state = {
        .game.players = {X, O},
    };
    GameState over = game(state);
    if (over.state == STATE_DRAW) {
        printf("Draw!\n");
    } else if (over.state == STATE_O) {
        printf("O Won!\n");
    } else if (over.state == STATE_X) {
        printf("X Won!\n");
    }
}
