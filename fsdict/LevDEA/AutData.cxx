#ifndef AUTDATA_CXX
#define AUTDATA_CXX AUTDATA_CXX

#include "./AutData.h"


const size_t fsdict::AutData< 0 >::bitVectorLength = 1;
const int    fsdict::AutData< 0 >::transitions[] = {-1,0};
const int    fsdict::AutData< 0 >::finalInfo[] = {0};
const fsdict::bits64 fsdict::AutData< 0 >::suffixMatch[] = {1};

const size_t fsdict::AutData< 1 >::bitVectorLength = 3;
const int    fsdict::AutData< 1 >::transitions[] = {1,2,0,3,1,2,0,3,-1,-1,5,5,8,8,1,1,-1,4,5,6,1,7,1,7,1,2,0,3,1,2,0,3,-1,4,-1,4,-1,4,-1,4,-1,-1,5,5,-1,-1,5,5,-1,4,5,6,-1,4,5,6,-1,4,5,6,8,9,1,7,-1,-1,-1,-1,8,8,8,8,-1,4,-1,4,8,9,8,9};
const int    fsdict::AutData< 1 >::finalInfo[] = {1,0,1,1,1,-1,1,1,1,1,0,1,-1,-1,1,-1,1,-1,-1,1,1,1,1,1,1,-1,-1,1,-1,1};
const fsdict::bits64 fsdict::AutData< 1 >::suffixMatch[] = {0,6,0,0,1,2,3,7,4,5};

const size_t fsdict::AutData< 2 >::bitVectorLength = 5;

const int    fsdict::AutData< 2 >::transitions[] = {1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,59,59,87,87,13,13,90,90,44,44,92,92,19,19,95,95,59,59,87,87,13,13,90,90,44,44,92,92,19,19,95,95,59,60,87,88,13,89,90,91,44,45,92,93,19,94,95,96,59,60,87,88,13,89,90,91,44,45,92,93,19,94,95,96,9,10,11,12,13,14,15,16,1,2,17,18,19,20,21,22,9,10,11,12,13,14,15,16,1,2,17,18,19,20,21,22,9,10,11,12,13,14,15,16,1,2,17,18,19,20,21,22,9,10,11,12,13,14,15,16,1,2,17,18,19,20,21,22,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,-1,-1,65,65,53,53,67,67,55,55,69,69,57,57,71,71,61,61,74,74,63,63,76,76,39,39,41,41,59,59,9,9,-1,52,65,66,67,68,67,68,55,56,69,70,71,72,71,72,61,62,74,75,76,77,76,77,39,40,41,42,9,73,9,73,67,78,79,80,67,78,79,80,71,81,82,83,71,81,82,83,76,84,85,86,76,84,85,86,9,10,27,28,9,10,27,28,67,78,79,80,67,78,79,80,71,81,82,83,71,81,82,83,76,84,85,86,76,84,85,86,9,10,27,28,9,10,27,28,57,57,97,97,99,99,101,101,57,57,97,97,99,99,101,101,59,59,87,87,103,103,105,105,59,59,87,87,103,103,105,105,57,58,97,98,99,100,101,102,57,58,97,98,99,100,101,102,59,60,87,88,103,104,105,106,59,60,87,88,103,104,105,106,71,81,107,108,99,109,110,111,71,81,107,108,99,109,110,111,9,10,11,12,103,112,113,114,9,10,11,12,103,112,113,114,71,81,107,108,99,109,110,111,71,81,107,108,99,109,110,111,9,10,11,12,103,112,113,114,9,10,11,12,103,112,113,114,9,10,11,12,13,14,15,16,23,24,25,26,19,20,21,22,9,10,11,12,13,14,15,16,23,24,25,26,19,20,21,22,9,10,11,12,13,14,15,16,23,24,25,26,19,20,21,22,9,10,11,12,13,14,15,16,23,24,25,26,19,20,21,22,59,59,87,87,13,13,90,90,44,44,92,92,19,19,95,95,59,59,87,87,13,13,90,90,44,44,92,92,19,19,95,95,59,60,87,88,13,89,90,91,44,45,92,93,19,94,95,96,59,60,87,88,13,89,90,91,44,45,92,93,19,94,95,96,9,10,11,12,13,14,15,16,23,24,25,26,19,20,21,22,9,10,11,12,13,14,15,16,23,24,25,26,19,20,21,22,9,10,11,12,13,14,15,16,23,24,25,26,19,20,21,22,9,10,11,12,13,14,15,16,23,24,25,26,19,20,21,22,39,39,41,41,48,48,29,29,44,44,23,23,50,50,35,35,39,39,41,41,48,48,29,29,44,44,23,23,50,50,35,35,39,40,41,42,29,43,29,43,44,45,23,46,35,47,35,47,39,40,41,42,29,43,29,43,44,45,23,46,35,47,35,47,9,10,27,28,29,30,31,32,23,24,33,34,35,36,37,38,9,10,27,28,29,30,31,32,23,24,33,34,35,36,37,38,9,10,27,28,29,30,31,32,23,24,33,34,35,36,37,38,9,10,27,28,29,30,31,32,23,24,33,34,35,36,37,38,67,78,79,80,67,78,79,80,71,81,82,83,71,81,82,83,76,84,85,86,76,84,85,86,9,10,27,28,9,10,27,28,67,78,79,80,67,78,79,80,71,81,82,83,71,81,82,83,76,84,85,86,76,84,85,86,9,10,27,28,9,10,27,28,-1,-1,65,65,53,53,67,67,55,55,69,69,57,57,71,71,39,39,41,41,59,59,9,9,39,39,41,41,59,59,9,9,-1,52,65,66,67,68,67,68,55,56,69,70,71,72,71,72,39,40,41,42,9,73,9,73,39,40,41,42,9,73,9,73,67,78,79,80,67,78,79,80,71,81,82,83,71,81,82,83,9,10,27,28,9,10,27,28,9,10,27,28,9,10,27,28,67,78,79,80,67,78,79,80,71,81,82,83,71,81,82,83,9,10,27,28,9,10,27,28,9,10,27,28,9,10,27,28,9,10,27,28,29,30,31,32,23,24,33,34,35,36,37,38,9,10,27,28,29,30,31,32,23,24,33,34,35,36,37,38,9,10,27,28,29,30,31,32,23,24,33,34,35,36,37,38,9,10,27,28,29,30,31,32,23,24,33,34,35,36,37,38,39,39,41,41,48,48,29,29,44,44,23,23,50,50,35,35,39,39,41,41,48,48,29,29,44,44,23,23,50,50,35,35,39,40,41,42,29,43,29,43,44,45,23,46,35,47,35,47,39,40,41,42,29,43,29,43,44,45,23,46,35,47,35,47,9,10,27,28,29,30,31,32,23,24,33,34,35,36,37,38,9,10,27,28,29,30,31,32,23,24,33,34,35,36,37,38,9,10,27,28,29,30,31,32,23,24,33,34,35,36,37,38,9,10,27,28,29,30,31,32,23,24,33,34,35,36,37,38,-1,-1,-1,-1,-1,-1,-1,-1,55,55,55,55,55,55,55,55,61,61,61,61,61,61,61,61,39,39,39,39,39,39,39,39,-1,52,-1,52,-1,52,-1,52,55,56,55,56,55,56,55,56,61,62,61,62,61,62,61,62,39,40,39,40,39,40,39,40,-1,-1,65,65,-1,-1,65,65,55,55,69,69,55,55,69,69,61,61,74,74,61,61,74,74,39,39,41,41,39,39,41,41,-1,52,65,66,-1,52,65,66,55,56,69,70,55,56,69,70,61,62,74,75,61,62,74,75,39,40,41,42,39,40,41,42,-1,52,65,66,53,54,67,68,55,56,69,70,57,58,71,72,39,40,41,42,59,60,9,73,39,40,41,42,59,60,9,73,39,39,39,39,48,48,48,48,44,44,44,44,50,50,50,50,39,39,39,39,48,48,48,48,44,44,44,44,50,50,50,50,39,40,39,40,48,49,48,49,44,45,44,45,50,51,50,51,39,40,39,40,48,49,48,49,44,45,44,45,50,51,50,51,39,40,41,42,48,49,29,43,44,45,23,46,50,51,35,47,39,40,41,42,48,49,29,43,44,45,23,46,50,51,35,47,39,40,41,42,48,49,29,43,44,45,23,46,50,51,35,47,39,40,41,42,48,49,29,43,44,45,23,46,50,51,35,47,-1,-1,-1,-1,53,53,53,53,55,55,55,55,57,57,57,57,39,39,39,39,59,59,59,59,39,39,39,39,59,59,59,59,-1,52,-1,52,53,54,53,54,55,56,55,56,57,58,57,58,39,40,39,40,59,60,59,60,39,40,39,40,59,60,59,60,39,39,39,39,48,48,48,48,44,44,44,44,50,50,50,50,39,39,39,39,48,48,48,48,44,44,44,44,50,50,50,50,39,40,39,40,48,49,48,49,44,45,44,45,50,51,50,51,39,40,39,40,48,49,48,49,44,45,44,45,50,51,50,51,-1,52,-1,52,-1,52,-1,52,-1,52,-1,52,-1,52,-1,52,-1,52,-1,52,-1,52,-1,52,-1,52,-1,52,-1,52,-1,52,-1,-1,-1,-1,53,53,53,53,-1,-1,-1,-1,53,53,53,53,-1,-1,-1,-1,53,53,53,53,-1,-1,-1,-1,53,53,53,53,-1,52,-1,52,53,54,53,54,-1,52,-1,52,53,54,53,54,-1,52,-1,52,53,54,53,54,-1,52,-1,52,53,54,53,54,-1,-1,-1,-1,-1,-1,-1,-1,55,55,55,55,55,55,55,55,-1,-1,-1,-1,-1,-1,-1,-1,55,55,55,55,55,55,55,55,-1,52,-1,52,-1,52,-1,52,55,56,55,56,55,56,55,56,-1,52,-1,52,-1,52,-1,52,55,56,55,56,55,56,55,56,-1,-1,-1,-1,53,53,53,53,55,55,55,55,57,57,57,57,-1,-1,-1,-1,53,53,53,53,55,55,55,55,57,57,57,57,-1,52,-1,52,53,54,53,54,55,56,55,56,57,58,57,58,-1,52,-1,52,53,54,53,54,55,56,55,56,57,58,57,58,-1,-1,-1,-1,53,53,53,53,55,55,55,55,57,57,57,57,61,61,61,61,63,63,63,63,39,39,39,39,59,59,59,59,-1,52,-1,52,53,54,53,54,55,56,55,56,57,58,57,58,61,62,61,62,63,64,63,64,39,40,39,40,59,60,59,60,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,-1,52,-1,52,-1,52,-1,52,-1,52,-1,52,-1,52,-1,52,61,62,61,62,61,62,61,62,61,62,61,62,61,62,61,62,-1,-1,-1,-1,53,53,53,53,-1,-1,-1,-1,53,53,53,53,61,61,61,61,63,63,63,63,61,61,61,61,63,63,63,63,-1,52,-1,52,53,54,53,54,-1,52,-1,52,53,54,53,54,61,62,61,62,63,64,63,64,61,62,61,62,63,64,63,64,-1,-1,65,65,-1,-1,65,65,-1,-1,65,65,-1,-1,65,65,-1,-1,65,65,-1,-1,65,65,-1,-1,65,65,-1,-1,65,65,-1,52,65,66,-1,52,65,66,-1,52,65,66,-1,52,65,66,-1,52,65,66,-1,52,65,66,-1,52,65,66,-1,52,65,66,-1,-1,65,65,53,53,67,67,-1,-1,65,65,53,53,67,67,-1,-1,65,65,53,53,67,67,-1,-1,65,65,53,53,67,67,-1,52,65,66,53,54,67,68,-1,52,65,66,53,54,67,68,-1,52,65,66,53,54,67,68,-1,52,65,66,53,54,67,68,-1,-1,65,65,-1,-1,65,65,55,55,69,69,55,55,69,69,-1,-1,65,65,-1,-1,65,65,55,55,69,69,55,55,69,69,-1,52,65,66,-1,52,65,66,55,56,69,70,55,56,69,70,-1,52,65,66,-1,52,65,66,55,56,69,70,55,56,69,70,-1,-1,65,65,53,53,67,67,55,55,69,69,57,57,71,71,-1,-1,65,65,53,53,67,67,55,55,69,69,57,57,71,71,-1,52,65,66,53,54,67,68,55,56,69,70,57,58,71,72,-1,52,65,66,53,54,67,68,55,56,69,70,57,58,71,72,-1,52,65,66,53,54,67,68,55,56,69,70,57,58,71,72,61,62,74,75,63,64,76,77,39,40,41,42,59,60,9,73,-1,-1,65,65,-1,-1,65,65,-1,-1,65,65,-1,-1,65,65,61,61,74,74,61,61,74,74,61,61,74,74,61,61,74,74,-1,52,65,66,-1,52,65,66,-1,52,65,66,-1,52,65,66,61,62,74,75,61,62,74,75,61,62,74,75,61,62,74,75,-1,-1,65,65,53,53,67,67,-1,-1,65,65,53,53,67,67,61,61,74,74,63,63,76,76,61,61,74,74,63,63,76,76,-1,52,65,66,53,54,67,68,-1,52,65,66,53,54,67,68,61,62,74,75,63,64,76,77,61,62,74,75,63,64,76,77,-1,52,65,66,67,68,67,68,-1,52,65,66,67,68,67,68,-1,52,65,66,67,68,67,68,-1,52,65,66,67,68,67,68,67,78,79,80,67,78,79,80,67,78,79,80,67,78,79,80,67,78,79,80,67,78,79,80,67,78,79,80,67,78,79,80,67,78,79,80,67,78,79,80,67,78,79,80,67,78,79,80,67,78,79,80,67,78,79,80,67,78,79,80,67,78,79,80,-1,52,65,66,67,68,67,68,55,56,69,70,71,72,71,72,-1,52,65,66,67,68,67,68,55,56,69,70,71,72,71,72,67,78,79,80,67,78,79,80,71,81,82,83,71,81,82,83,67,78,79,80,67,78,79,80,71,81,82,83,71,81,82,83,67,78,79,80,67,78,79,80,71,81,82,83,71,81,82,83,67,78,79,80,67,78,79,80,71,81,82,83,71,81,82,83,-1,52,65,66,67,68,67,68,-1,52,65,66,67,68,67,68,61,62,74,75,76,77,76,77,61,62,74,75,76,77,76,77,67,78,79,80,67,78,79,80,67,78,79,80,67,78,79,80,76,84,85,86,76,84,85,86,76,84,85,86,76,84,85,86,67,78,79,80,67,78,79,80,67,78,79,80,67,78,79,80,76,84,85,86,76,84,85,86,76,84,85,86,76,84,85,86,-1,-1,65,65,53,53,67,67,57,57,71,71,57,57,71,71,61,61,74,74,63,63,76,76,59,59,9,9,59,59,9,9,-1,52,65,66,53,54,67,68,57,58,71,72,57,58,71,72,61,62,74,75,63,64,76,77,59,60,9,73,59,60,9,73,57,58,97,98,99,100,101,102,57,58,97,98,99,100,101,102,59,60,87,88,103,104,105,106,59,60,87,88,103,104,105,106,57,57,97,97,99,99,101,101,57,57,97,97,99,99,101,101,59,59,87,87,103,103,105,105,59,59,87,87,103,103,105,105,57,58,97,98,99,100,101,102,57,58,97,98,99,100,101,102,59,60,87,88,103,104,105,106,59,60,87,88,103,104,105,106,39,39,41,41,48,48,29,29,44,44,23,23,50,50,35,35,39,39,41,41,48,48,29,29,44,44,23,23,50,50,35,35,39,40,41,42,48,49,29,43,44,45,23,46,50,51,35,47,39,40,41,42,48,49,29,43,44,45,23,46,50,51,35,47,59,60,87,88,13,89,90,91,44,45,92,93,19,94,95,96,59,60,87,88,13,89,90,91,44,45,92,93,19,94,95,96,59,59,87,87,13,13,90,90,44,44,92,92,19,19,95,95,59,59,87,87,13,13,90,90,44,44,92,92,19,19,95,95,59,60,87,88,13,89,90,91,44,45,92,93,19,94,95,96,59,60,87,88,13,89,90,91,44,45,92,93,19,94,95,96,-1,-1,65,65,53,53,67,67,57,57,71,71,57,57,71,71,-1,-1,65,65,53,53,67,67,57,57,71,71,57,57,71,71,-1,52,65,66,53,54,67,68,57,58,71,72,57,58,71,72,-1,52,65,66,53,54,67,68,57,58,71,72,57,58,71,72,57,57,97,97,99,99,101,101,57,57,97,97,99,99,101,101,57,57,97,97,99,99,101,101,57,57,97,97,99,99,101,101,57,58,97,98,99,100,101,102,57,58,97,98,99,100,101,102,57,58,97,98,99,100,101,102,57,58,97,98,99,100,101,102,57,57,97,97,99,99,101,101,57,57,97,97,99,99,101,101,57,57,97,97,99,99,101,101,57,57,97,97,99,99,101,101,57,58,97,98,99,100,101,102,57,58,97,98,99,100,101,102,57,58,97,98,99,100,101,102,57,58,97,98,99,100,101,102,57,57,97,97,99,99,101,101,57,57,97,97,99,99,101,101,59,59,87,87,103,103,105,105,59,59,87,87,103,103,105,105,57,58,97,98,99,100,101,102,57,58,97,98,99,100,101,102,59,60,87,88,103,104,105,106,59,60,87,88,103,104,105,106,57,57,97,97,99,99,101,101,57,57,97,97,99,99,101,101,59,59,87,87,103,103,105,105,59,59,87,87,103,103,105,105,57,58,97,98,99,100,101,102,57,58,97,98,99,100,101,102,59,60,87,88,103,104,105,106,59,60,87,88,103,104,105,106,67,78,79,80,67,78,79,80,71,81,82,83,71,81,82,83,67,78,79,80,67,78,79,80,71,81,82,83,71,81,82,83,67,78,79,80,67,78,79,80,71,81,82,83,71,81,82,83,67,78,79,80,67,78,79,80,71,81,82,83,71,81,82,83,57,58,97,98,99,100,101,102,57,58,97,98,99,100,101,102,57,58,97,98,99,100,101,102,57,58,97,98,99,100,101,102,71,81,107,108,99,109,110,111,71,81,107,108,99,109,110,111,71,81,107,108,99,109,110,111,71,81,107,108,99,109,110,111,71,81,107,108,99,109,110,111,71,81,107,108,99,109,110,111,71,81,107,108,99,109,110,111,71,81,107,108,99,109,110,111,57,58,97,98,99,100,101,102,57,58,97,98,99,100,101,102,59,60,87,88,103,104,105,106,59,60,87,88,103,104,105,106,71,81,107,108,99,109,110,111,71,81,107,108,99,109,110,111,9,10,11,12,103,112,113,114,9,10,11,12,103,112,113,114,71,81,107,108,99,109,110,111,71,81,107,108,99,109,110,111,9,10,11,12,103,112,113,114,9,10,11,12,103,112,113,114};

const int    fsdict::AutData< 2 >::finalInfo[] = {2,1,0,1,2,2,1,1,2,-1,2,1,1,2,2,2,1,1,1,2,2,1,1,1,2,2,1,0,1,2,2,1,0,1,2,2,1,0,1,2,2,1,0,1,2,2,2,2,2,-1,2,2,2,2,2,2,2,2,1,2,2,2,2,1,2,2,2,1,2,-1,2,2,1,2,2,2,2,1,1,2,2,2,1,1,2,2,1,1,1,2,2,1,1,1,2,2,1,1,2,-1,2,1,1,2,2,2,1,1,1,2,2,1,1,1,2,2,1,2,2,-1,2,1,2,2,2,2,1,2,1,2,2,1,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,2,-1,2,2,2,2,2,2,2,2,1,2,2,2,2,1,2,2,1,2,1,2,2,1,2,1,2,2,1,2,2,-1,2,1,2,2,2,2,1,2,1,2,2,1,2,1,2,2,2,-1,-1,-1,2,2,-1,-1,2,2,2,-1,2,-1,2,2,-1,2,2,2,2,2,2,2,2,1,2,-1,-1,2,1,2,-1,2,2,1,2,2,2,2,1,2,2,2,2,2,2,-1,-1,2,2,2,-1,2,2,1,2,-1,-1,2,1,2,-1,2,-1,-1,-1,-1,2,-1,-1,2,-1,-1,-1,-1,2,-1,2,-1,2,-1,-1,-1,-1,2,-1,-1,2,-1,2,2,-1,-1,-1,2,2,-1,2,2,2,2,-1,-1,2,2,2,-1,2,2,-1,-1,-1,-1,2,-1,-1,-1,2,2,-1,2,-1,-1,2,-1,2,-1,2,-1,-1,-1,2,-1,-1,-1,-1,2,2,-1,-1,2,2,-1,-1,-1,2,2,2,-1,2,-1,2,-1,-1,2,-1,2,2,-1,2,2,2,-1,-1,2,2,2,2,2,2,2,2,2,2,-1,-1,2,-1,2,-1,-1,2,2,2,-1,2,2,-1,2,-1,2,2,2,-1,-1,2,2,2,-1,-1,2,1,2,-1,-1,2,1,2,-1,2,2,2,2,-1,2,2,1,2,-1,2,2,1,2,2,-1,2,2,2,2,-1,2,1,2,2,-1,2,1,2,2,2,2,2,-1,2,2,2,2,2,2,2,1,2,2,2,2,1,2,-1,2,2,1,2,2,2,1,2,2,-1,2,1,2,2,2,2,1,1,2,2,2,1,1,2,-1,2,1,1,2,2,-1,2,2,2,-1,-1,2,2,2,2,-1,2,1,2,-1,-1,2,1,2,2,-1,2,1,2,-1,-1,2,1,2,2,2,2,1,2,-1,2,2,1,2,2,2,2,1,2,-1,2,2,1,2,2,-1,2,2,1,2,-1,2,2,1,2,-1,2,1,2,2,-1,2,1,1,2,-1,2,1,1,2,2,2,1,2,2,2,2,1,1,2,2,2,1,1,2};

const fsdict::bits64 fsdict::AutData< 2 >::suffixMatch[] = {0,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,24,25,26,27,0,0,0,0,0,0,0,0,0,1,4,5,8,9,12,13,28,29,16,17,20,21,2,3,6,7,10,11,14,15,31,18,19,22,23,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};



#endif