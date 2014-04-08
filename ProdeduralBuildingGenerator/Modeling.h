#ifndef __MODELING_H_INCLUDED__
#define __MODELING_H_INCLUDED__

//please insert all your 
#include	<iostream>
#include	<string>
#include	"Symbol.h"
#include	"ntree.hpp"
#include	"GNode.h"
#include	"tree.hh"
#include	<time.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<Windows.h>



using namespace std;


//all your functions can be declared here
tree<Symbol> modeling( vector< pair < string, vector<GNode>> >);
vector<Symbol> apply_rule ( Symbol &, GNode *);

//please do not write below this comment, thanks
#endif