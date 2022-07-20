#ifndef INCLUDES_H_
#define INCLUDES_H_

#define BLACK -1
#define WHITE 1

#define PVP 0
#define PVE 1

static int DEPTH = 0;

#define THREADS 4

#include <climits>
#include <thread>
#include <cstring>
#include <iostream>
#include <chrono>
#include <string>
#include <algorithm>
#include <deque>
#include <vector>
#include <ctime>
#include "Board.h"

std::thread threads[THREADS];

static Board playingBoard;
static int turn = WHITE;
static int mode = -1;
static int engineteam = 0;

#endif // INCLUDES_H_