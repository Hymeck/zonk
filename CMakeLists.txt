cmake_minimum_required(VERSION 3.17)
project(zonk C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(zonk
        src/client.console/main.c src/core/score.c src/core/score.h src/core/shared.h src/core/dice.c src/core/dice.h src/core/zonk.h src/client.console/presenter.c src/client.console/presenter.h src/core/score_evaluation.c src/core/score_evaluation.h)
