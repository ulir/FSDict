const int LevDEA::lev2data[] = {2,30,27,0,11,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,11,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,11,3,11,2,11,2,15,2,11,0,11,0,11,0,17,0,15,0,15,0,17,0,27,0,11,0,-1,-1,2,5,-1,-1,2,5,-1,-1,2,5,-1,-1,2,5,15,3,-1,-1,2,5,-1,-1,2,5,-1,-1,2,5,-1,-1,2,5,15,3,11,2,13,2,17,2,11,0,11,0,11,0,17,0,15,0,15,0,17,0,27,0,11,0,-1,-1,-1,-1,2,4,2,4,-1,-1,-1,-1,2,4,2,4,1,4,-1,-1,-1,-1,2,4,2,4,-1,-1,-1,-1,2,4,2,4,1,4,15,2,15,2,20,2,12,0,11,0,12,0,18,0,15,0,16,0,18,0,27,0,11,0,-1,-1,2,5,2,4,11,4,-1,-1,2,5,2,4,11,4,1,4,-1,-1,2,5,2,4,11,4,-1,-1,2,5,2,4,11,4,1,4,15,2,17,2,20,2,12,0,11,0,12,0,18,0,15,0,16,0,18,0,28,0,11,0,-1,-1,-1,-1,-1,-1,-1,-1,2,3,2,3,2,3,2,3,11,3,-1,-1,-1,-1,-1,-1,-1,-1,2,3,2,3,2,3,2,3,11,3,1,3,1,3,1,3,11,0,13,0,13,0,19,0,17,0,17,0,19,0,28,0,11,0,-1,-1,2,5,-1,-1,2,5,2,3,6,3,2,3,6,3,15,3,-1,-1,2,5,-1,-1,2,5,2,3,6,3,2,3,6,3,15,3,1,3,24,3,24,3,11,0,13,0,13,0,19,0,17,0,17,0,19,0,28,0,11,0,-1,-1,-1,-1,2,4,2,4,2,3,2,3,11,3,11,3,1,4,-1,-1,-1,-1,2,4,2,4,2,3,2,3,11,3,11,3,1,4,1,3,1,3,27,3,12,0,13,0,14,0,19,0,17,0,18,0,19,0,28,0,11,0,-1,-1,2,5,2,4,11,4,2,3,6,3,11,3,15,3,1,4,-1,-1,2,5,2,4,11,4,2,3,6,3,11,3,15,3,1,4,1,3,24,3,27,3,12,0,13,0,14,0,19,0,17,0,18,0,19,0,29,0,15,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,11,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,15,2,11,2,11,2,15,2,15,0,15,0,15,0,17,0,20,0,20,0,20,0,29,0,15,0,-1,-1,2,5,-1,-1,2,5,-1,-1,2,5,-1,-1,2,5,15,3,2,2,4,2,2,2,4,2,2,2,4,2,2,2,4,2,17,2,11,2,13,2,17,2,15,0,15,0,15,0,17,0,20,0,20,0,20,0,29,0,15,0,-1,-1,-1,-1,2,4,2,4,-1,-1,-1,-1,2,4,2,4,1,4,2,2,2,2,6,2,6,2,2,2,2,2,6,2,6,2,20,2,15,2,15,2,20,2,16,0,15,0,16,0,18,0,20,0,21,0,21,0,29,0,15,0,-1,-1,2,5,2,4,11,4,-1,-1,2,5,2,4,11,4,1,4,2,2,4,2,6,2,8,2,2,2,4,2,6,2,8,2,20,2,15,2,17,2,20,2,16,0,15,0,16,0,18,0,20,0,21,0,21,0,29,0,15,0,-1,-1,-1,-1,-1,-1,-1,-1,2,3,2,3,2,3,2,3,11,3,2,2,2,2,2,2,2,2,11,2,11,2,11,2,11,2,15,2,1,3,1,3,1,3,15,0,17,0,17,0,19,0,20,0,20,0,22,0,29,0,15,0,-1,-1,2,5,-1,-1,2,5,2,3,6,3,2,3,6,3,15,3,2,2,4,2,2,2,4,2,11,2,13,2,11,2,13,2,17,2,1,3,24,3,24,3,15,0,17,0,17,0,19,0,20,0,20,0,22,0,29,0,15,0,-1,-1,-1,-1,2,4,2,4,2,3,2,3,11,3,11,3,1,4,2,2,2,2,6,2,6,2,11,2,11,2,15,2,15,2,20,2,1,3,1,3,27,3,16,0,17,0,18,0,19,0,20,0,21,0,22,0,29,0,15,0,-1,-1,2,5,2,4,11,4,2,3,6,3,11,3,15,3,1,4,2,2,4,2,6,2,8,2,11,2,13,2,15,2,17,2,20,2,1,3,24,3,27,3,16,0,17,0,18,0,19,0,20,0,21,0,22,0,0,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,8,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,8,1,15,1,15,1,17,1,1,1,1,1,1,1,24,1,1,1,1,1,24,1,0,1,1,1,2,1,3,1,2,1,3,1,2,1,3,1,2,1,3,1,9,1,2,1,3,1,2,1,3,1,2,1,3,1,2,1,3,1,9,1,15,1,16,1,18,1,1,1,1,1,1,1,24,1,1,1,1,1,24,1,0,1,1,1,2,1,2,1,4,1,4,1,2,1,2,1,4,1,4,1,10,1,2,1,2,1,4,1,4,1,2,1,2,1,4,1,4,1,10,1,17,1,17,1,19,1,23,1,1,1,23,1,25,1,1,1,23,1,25,1,0,1,1,1,2,1,3,1,4,1,5,1,2,1,3,1,4,1,5,1,10,1,2,1,3,1,4,1,5,1,2,1,3,1,4,1,5,1,10,1,17,1,18,1,19,1,23,1,1,1,23,1,25,1,1,1,23,1,25,1,0,1,1,1,2,1,2,1,2,1,2,1,6,1,6,1,6,1,6,1,8,1,2,1,2,1,2,1,2,1,6,1,6,1,6,1,6,1,8,1,20,1,20,1,20,1,1,1,24,1,24,1,26,1,24,1,24,1,26,1,0,1,1,1,2,1,3,1,2,1,3,1,6,1,7,1,6,1,7,1,9,1,2,1,3,1,2,1,3,1,6,1,7,1,6,1,7,1,9,1,20,1,21,1,21,1,1,1,24,1,24,1,26,1,24,1,24,1,26,1,0,1,1,1,2,1,2,1,4,1,4,1,6,1,6,1,8,1,8,1,10,1,2,1,2,1,4,1,4,1,6,1,6,1,8,1,8,1,10,1,20,1,20,1,22,1,23,1,24,1,25,1,26,1,24,1,25,1,26,1,0,1,1,1,2,1,3,1,4,1,5,1,6,1,7,1,8,1,9,1,10,1,2,1,3,1,4,1,5,1,6,1,7,1,8,1,9,1,10,1,20,1,21,1,22,1,23,1,24,1,25,1,26,1,24,1,25,1,26,1,0,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,8,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,17,1,15,1,15,1,17,1,1,1,1,1,1,1,24,1,27,1,27,1,27,1,0,1,1,1,2,1,3,1,2,1,3,1,2,1,3,1,2,1,3,1,9,1,11,1,12,1,11,1,12,1,11,1,12,1,11,1,12,1,18,1,15,1,16,1,18,1,1,1,1,1,1,1,24,1,27,1,27,1,27,1,0,1,1,1,2,1,2,1,4,1,4,1,2,1,2,1,4,1,4,1,10,1,11,1,11,1,13,1,13,1,11,1,11,1,13,1,13,1,19,1,17,1,17,1,19,1,23,1,1,1,23,1,25,1,27,1,28,1,28,1,0,1,1,1,2,1,3,1,4,1,5,1,2,1,3,1,4,1,5,1,10,1,11,1,12,1,13,1,14,1,11,1,12,1,13,1,14,1,19,1,17,1,18,1,19,1,23,1,1,1,23,1,25,1,27,1,28,1,28,1,0,1,1,1,2,1,2,1,2,1,2,1,6,1,6,1,6,1,6,1,8,1,11,1,11,1,11,1,11,1,15,1,15,1,15,1,15,1,17,1,20,1,20,1,20,1,1,1,24,1,24,1,26,1,27,1,27,1,29,1,0,1,1,1,2,1,3,1,2,1,3,1,6,1,7,1,6,1,7,1,9,1,11,1,12,1,11,1,12,1,15,1,16,1,15,1,16,1,18,1,20,1,21,1,21,1,1,1,24,1,24,1,26,1,27,1,27,1,29,1,0,1,1,1,2,1,2,1,4,1,4,1,6,1,6,1,8,1,8,1,10,1,11,1,11,1,13,1,13,1,15,1,15,1,17,1,17,1,19,1,20,1,20,1,22,1,23,1,24,1,25,1,26,1,27,1,28,1,29,1,0,1,1,1,2,1,3,1,4,1,5,1,6,1,7,1,8,1,9,1,10,1,11,1,12,1,13,1,14,1,15,1,16,1,17,1,18,1,19,1,20,1,21,1,22,1,23,1,24,1,25,1,26,1,27,1,28,1,29,1,27,0,11,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,11,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,11,3,11,2,11,2,15,2,11,0,11,0,11,0,17,0,15,0,15,0,17,0,27,0,11,0,-1,-1,-1,-1,2,4,2,4,-1,-1,-1,-1,2,4,2,4,1,4,-1,-1,-1,-1,2,4,2,4,-1,-1,-1,-1,2,4,2,4,1,4,15,2,15,2,20,2,12,0,11,0,12,0,18,0,15,0,16,0,18,0,28,0,11,0,-1,-1,-1,-1,-1,-1,-1,-1,2,3,2,3,2,3,2,3,11,3,-1,-1,-1,-1,-1,-1,-1,-1,2,3,2,3,2,3,2,3,11,3,1,3,1,3,1,3,11,0,13,0,13,0,19,0,17,0,17,0,19,0,28,0,11,0,-1,-1,-1,-1,2,4,2,4,2,3,2,3,11,3,11,3,1,4,-1,-1,-1,-1,2,4,2,4,2,3,2,3,11,3,11,3,1,4,1,3,1,3,27,3,12,0,13,0,14,0,19,0,17,0,18,0,19,0,29,0,15,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,11,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,15,2,11,2,11,2,15,2,15,0,15,0,15,0,17,0,20,0,20,0,20,0,29,0,15,0,-1,-1,-1,-1,2,4,2,4,-1,-1,-1,-1,2,4,2,4,1,4,2,2,2,2,6,2,6,2,2,2,2,2,6,2,6,2,20,2,15,2,15,2,20,2,16,0,15,0,16,0,18,0,20,0,21,0,21,0,29,0,15,0,-1,-1,-1,-1,-1,-1,-1,-1,2,3,2,3,2,3,2,3,11,3,2,2,2,2,2,2,2,2,11,2,11,2,11,2,11,2,15,2,1,3,1,3,1,3,15,0,17,0,17,0,19,0,20,0,20,0,22,0,29,0,15,0,-1,-1,-1,-1,2,4,2,4,2,3,2,3,11,3,11,3,1,4,2,2,2,2,6,2,6,2,11,2,11,2,15,2,15,2,20,2,1,3,1,3,27,3,16,0,17,0,18,0,19,0,20,0,21,0,22,0,0,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,8,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,8,1,15,1,15,1,17,1,1,1,1,1,1,1,24,1,1,1,1,1,24,1,0,1,1,1,2,1,2,1,4,1,4,1,2,1,2,1,4,1,4,1,10,1,2,1,2,1,4,1,4,1,2,1,2,1,4,1,4,1,10,1,17,1,17,1,19,1,23,1,1,1,23,1,25,1,1,1,23,1,25,1,0,1,1,1,2,1,2,1,2,1,2,1,6,1,6,1,6,1,6,1,8,1,2,1,2,1,2,1,2,1,6,1,6,1,6,1,6,1,8,1,20,1,20,1,20,1,1,1,24,1,24,1,26,1,24,1,24,1,26,1,0,1,1,1,2,1,2,1,4,1,4,1,6,1,6,1,8,1,8,1,10,1,2,1,2,1,4,1,4,1,6,1,6,1,8,1,8,1,10,1,20,1,20,1,22,1,23,1,24,1,25,1,26,1,24,1,25,1,26,1,0,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,8,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,17,1,15,1,15,1,17,1,1,1,1,1,1,1,24,1,27,1,27,1,27,1,0,1,1,1,2,1,2,1,4,1,4,1,2,1,2,1,4,1,4,1,10,1,11,1,11,1,13,1,13,1,11,1,11,1,13,1,13,1,19,1,17,1,17,1,19,1,23,1,1,1,23,1,25,1,27,1,28,1,28,1,0,1,1,1,2,1,2,1,2,1,2,1,6,1,6,1,6,1,6,1,8,1,11,1,11,1,11,1,11,1,15,1,15,1,15,1,15,1,17,1,20,1,20,1,20,1,1,1,24,1,24,1,26,1,27,1,27,1,29,1,0,1,1,1,2,1,2,1,4,1,4,1,6,1,6,1,8,1,8,1,10,1,11,1,11,1,13,1,13,1,15,1,15,1,17,1,17,1,19,1,20,1,20,1,22,1,23,1,24,1,25,1,26,1,27,1,28,1,29,1,27,0,11,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,3,11,2,-1,-1,11,2,11,0,11,0,11,0,17,0,15,0,15,0,17,0,28,0,11,0,-1,-1,-1,-1,-1,-1,-1,-1,2,3,-1,-1,2,3,-1,-1,2,3,-1,-1,-1,-1,-1,-1,-1,-1,2,3,-1,-1,2,3,-1,-1,2,3,1,3,-1,-1,1,3,11,0,13,0,13,0,19,0,17,0,17,0,19,0,29,0,15,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,3,2,2,-1,-1,2,2,-1,-1,2,2,-1,-1,2,2,-1,-1,11,2,11,2,-1,-1,11,2,15,0,15,0,15,0,17,0,20,0,20,0,20,0,29,0,15,0,-1,-1,-1,-1,-1,-1,-1,-1,2,3,-1,-1,2,3,-1,-1,2,3,2,2,-1,-1,2,2,-1,-1,11,2,-1,-1,11,2,-1,-1,11,2,1,3,-1,-1,1,3,15,0,17,0,17,0,19,0,20,0,20,0,22,0,0,1,1,1,2,1,-1,-1,2,1,-1,-1,2,1,-1,-1,2,1,-1,-1,6,1,2,1,-1,-1,2,1,-1,-1,2,1,-1,-1,2,1,-1,-1,6,1,15,1,-1,-1,15,1,1,1,1,1,1,1,24,1,1,1,1,1,24,1,0,1,1,1,2,1,-1,-1,2,1,-1,-1,6,1,-1,-1,6,1,-1,-1,6,1,2,1,-1,-1,2,1,-1,-1,6,1,-1,-1,6,1,-1,-1,6,1,20,1,-1,-1,20,1,1,1,24,1,24,1,26,1,24,1,24,1,26,1,0,1,1,1,2,1,-1,-1,2,1,-1,-1,2,1,-1,-1,2,1,-1,-1,6,1,11,1,-1,-1,11,1,-1,-1,11,1,-1,-1,11,1,-1,-1,15,1,15,1,-1,-1,15,1,1,1,1,1,1,1,24,1,27,1,27,1,27,1,0,1,1,1,2,1,-1,-1,2,1,-1,-1,6,1,-1,-1,6,1,-1,-1,6,1,11,1,-1,-1,11,1,-1,-1,15,1,-1,-1,15,1,-1,-1,15,1,20,1,-1,-1,20,1,1,1,24,1,24,1,26,1,27,1,27,1,29,1,27,0,11,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,2,-1,-1,-1,-1,-1,-1,11,0,-1,-1,15,0,15,0,-1,-1,15,0,29,0,15,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,2,-1,-1,-1,-1,-1,-1,2,2,-1,-1,-1,-1,-1,-1,-1,-1,2,2,-1,-1,-1,-1,-1,-1,15,0,-1,-1,15,0,20,0,-1,-1,20,0,0,1,1,1,2,1,-1,-1,-1,-1,-1,-1,2,1,-1,-1,-1,-1,-1,-1,-1,-1,2,1,-1,-1,-1,-1,-1,-1,2,1,-1,-1,-1,-1,-1,-1,-1,-1,11,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,1,1,1,1,-1,-1,1,1,0,1,1,1,2,1,-1,-1,-1,-1,-1,-1,2,1,-1,-1,-1,-1,-1,-1,-1,-1,11,1,-1,-1,-1,-1,-1,-1,11,1,-1,-1,-1,-1,-1,-1,-1,-1,11,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,1,1,27,1,-1,-1,27,1,27,0,11,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,11,0,-1,-1,-1,-1,0,1,1,1,2,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,1,0,2,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,-1,2,-1,2,-1,2,2,-1,2,-1,2,-1,2,-1,2,2,-1,2,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,-1,-1,-1,2,-1,1,-1,-1,2,-1,-1,-1,2,-1,1,2,-1,1,2,-1,2,2,-1,2,2,2,-1,-1,-1,-1,-1,2,-1,-1,-1,-1,-1,-1,-1,-1,2,-1,-1,-1,-1,1,-1,-1,-1,2,-1,1,2,-1,1,1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,0,1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};