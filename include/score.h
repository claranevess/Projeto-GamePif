#ifndef SCORE_H
#define SCORE_H

#define MAX_SCORES 10
#define SCORE_FILE "scores.txt"

struct Score {
    int score;
    char name[50];
};

extern struct Score scores[MAX_SCORES];

void SaveScores();
void LoadScores();
void DrawTopScores();
void CheckNewScore();

#endif