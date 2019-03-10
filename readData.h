//
//  readData.h
//  Assignment2
//
//  Created by JIHUI LIANG on 26/1/19.
//  Copyright © 2019 JIHUI LIANG. All rights reserved.
//

#ifndef readData_h
#define readData_h

#include <stdio.h>
#include "List.h"
#include "Graph.h"
#include "ListStr.h"

List getCollection(void);
int converturl(char *buffer);

Graph getGraph(List L);

List get2Collection(void);
void adjust(char *str);

#endif /* readData_h */
