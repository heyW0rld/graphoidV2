#ifndef LAB19_H
#define LAB19_H

//#include <stdlib.h>
//#include <time.h>
//#include <stdio.h>

//int wpchk(int w, int *wpts)
//{
//    int i = 0;
//    int flg = 0;
//    while (wpts[i] != -1)
//    {
//        if (wpts[i] == w){ flg = 1; }
//        i++;
//    }

//    if (flg == 0) { return 0; }
//    else return 1;
//}

//void m(){

////srand((unsigned)time(NULL));

//    //int prices[10][10];
//    int waypoint[11] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1 };
//    int way[11] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
//    int start = -1;
//    int end = -1;
//    int min;
//    int imin;

//        int prices[10][10] = {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //0
//                                0, 0, 2, 9, 8, 0, 0, 0, 0, 0, //1
//                                0, 2, 0, 3, 0, 20, 0, 0, 0, 0, //2
//                                0, 9, 3, 0, 7, 4, 0, 0, 0, 0, //3
//                                0, 8, 0, 7, 0, 11, 0, 0, 0, 0, //4
//                                0, 0, 20, 4, 11, 0, 0, 0, 0, 0, //5
//                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //6
//                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //7
//                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //8
//                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//9

////	printf("Enter № of start location:");
////	scanf("%i", &start);
////	printf("Enter № of finish location:");
////	scanf("%i", &end);
//    waypoint[0] = start;
//    int n = 0;
//    int w;
//    while (waypoint[n] != end)
//    {
//        min = 0;
//        w = waypoint[n];
//        for (int i = 0; i<10; i++)
//        {
//            if (((min == 0) || ((prices[w][i]<min) && (prices[w][i]>0))) && wpchk(i, waypoint) == 0) { min = prices[w][i]; imin = i; }
//        }
//        n++;
//        waypoint[n] = imin;
//    }

////	printf("\nThe way is:\n");
//    int i = 0;
//    while (waypoint[i] != -1)
//    {
////		printf("%i ", waypoint[i]);
//        i++;
//    }




//}



#endif // LAB19_H
