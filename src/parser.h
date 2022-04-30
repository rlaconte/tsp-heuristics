#ifndef TP1_PARSER_H
#define TP1_PARSER_H

#include <bits/stdc++.h>
#include <cstdint>
#include <iostream>
#include "Grafos.h"

using namespace std;

Arista crearArista(string str);
// Parser PIDE MEMORIA CON NEW que el programador DEBE liberar
KGrafo* parser(string file);

#endif //TP1_PARSER_H
