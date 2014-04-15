#!/usr/bin/python

import pdb
import logging
import sys
import argparse

class AutConfig:
    """
    A simple configuration container that lets us share config data across the involved classes.
    """
    def __init__(self, distance, noTranspositions):
        self.distance = distance # the Levenshtein distance threshold
        self.noTranspositions  = noTranspositions;
        self.bitVectorLength = self.distance*2 + 1
        self.zeroShift = self.distance # That means, for each bit vector representing a floor, the 0-index is at the zeroShift-th bit.

class State:
    """
    Represents one state of the deterministic Levenshtein automaton during construction.

    Note that we need this complex representation *only* during this computation step. Later, when we use the automaton, we can just use
    plain numbered states (with a bit of extra info on the final states).
    """

    def __init__(self, autConfig):
        self.conf = autConfig
        self.floors = [0 for i in range(self.conf.distance +1)]

        # transpositionFloors[i] is the one right below floors[i].
        self.transpositionFloors = [0 for i in range(self.conf.distance +1)]
        self.transitions = []

    def __eq__(self, other):
        return self.floors == other.floors and self.transpositionFloors == other.transpositionFloors

    def __hash__(self):
        return hash(tuple(self.floors + self.transpositionFloors))

    def getBitPos(self,x):
        return self.conf.zeroShift - x

    def getTrans(self, flooorIdx, x):
        return self.__getHelper(self.transpositionFloors[floorIdx], x)
        
    def get(self, floorIdx, x):
        return self.__getHelper(self.floors[floorIdx], x)

    def set(self, floorIdx, x, setTo):
        self.floors[floorIdx] = self.__setHelper(self.floors[floorIdx], x, setTo)

    def setTrans(self, floorIdx, x, setTo):
        self.__setHelper(self.transpositionFloors[floorIdx], x, setTo)

    def __setHelper(self, floor, x, setTo):
        """
        Takes a floor in the form of an integer representing a bit-vector. Changes a bit as specified, and returns the new floor.
        """
        bitPos = self.getBitPos(x)
        if(setTo):
            floor |= (1<<bitPos)
        else:
            floor &= ~(1<<bitPos)
        return floor

    def __getHelper(self, floor, x):
        bitPos = self.getBitPos(x)
        return (floor & (1<<bitPos) ) != 0
        
    
    def getFinalInfo(self):
        """
        Return a vector of numbers in [-1,0..distance] where the i-th number is the lowest floor whose i-th bit is set to 1.

        This means: if finalInfo[i] = 1, then the 1st floor is the lowest which has the i-th bit set.
        The info is used to deduce at run-time if we arrived at a final state, and what the Levenshtein distance for the match is.
        """
        finalInfo = [-1] * self.conf.bitVectorLength
        for floorIdx in range(self.conf.distance, -1, -1):
            width = floorIdx
            for pos in range(-width,width+1):
                if self.get(floorIdx, pos):
                    finalInfo[pos+self.conf.zeroShift] = floorIdx
        return finalInfo

    def getSuffixMatch(self):
        """
        In the special situation where we don't have any active states but on the topmost floor, a bit-vector equivalent to this topmost floor is returned. 0 otherwise.

        Example: Look at this triangular area (for threshold 2, ignoring transpositions), where only states on the topmost floor are active. So we don't have any Sigma-transitions
                 available - only horizontal transitions can be used.
                                           01101
                                            000
                                             0
                            
                 We return:  suffixMatch = 01101 .
        At run-time, during parallel traversal of the Levenshtein FSA and the dictionary FSA, we can use this info in the following way: Once we reach such a state, where onlz the topmost
        floor has active states, we don't continue with the regular parallel traversal - instead we trz to match a couple of different suffixes of the pattern from the current state in the
        dictionary automaton. We need the suffixMatch bit-vector to determine which suffixes exactly we have to test.
        """
        # If any but the topmost floor has active states, return 0.
        for floorIdx in range(self.conf.distance): # for all floors but the topmost
            if self.floors[floorIdx] != 0:
                return 0
        for floorIdx in range(1, self.conf.distance+1): # for all floors but the bottommost (which has no transpositionFloor)
            if self.transpositionFloors[floorIdx] != 0:
                return 0

        suffixMatch = self.floors[self.conf.distance]
        return suffixMatch
        

    def printState(self):
        for floorIdx in range(self.conf.distance, -1, -1):
            print "%s\t%s" % (floorIdx, self.bitString(self.floors[floorIdx], (self.conf.distance*2 +1)))
            if floorIdx > 0:
                print "%s\t%s" % ("T"+str(floorIdx), self.bitString(self.transpositionFloors[floorIdx], (self.conf.distance*2 +1)))

    def bitString(self, x, width):
        return ''.join([str( x >> i & 1 ) for i in range(width-1,-1,-1)])



class LevAut:
    """
    LevAut represents a deterministic Lev. automaton during the construction phase.
    """

    def __init__(self, autConfig):
        self.conf = autConfig
        self.states = []

    def addState(self, state):
        """
        Store a state and return its index in the arrray of states.
        """
        id = len(self.states)
        self.states.append(state)
        return id

    def getNrOfStates(self):
        return len(self.states)

    def dumpAut(self, debug=False):
        count = 0
        print "distance=%d" % self.conf.distance
        print "bitVectorLength=%d" % self.conf.bitVectorLength
        print "STATES_START"
        for state in self.states:
            print "%d\t%s\t%s\t%s" % (
                count, 
                ",".join([str(x) for x in state.transitions]),
                ",".join([str(x) for x in state.getFinalInfo()]),
                state.getSuffixMatch(),
                )
            if debug:
                state.printState()
                print "----"
            count += 1
        print "STATES_END"

    def dumpAutToCPP(self, debug=False):

        print "const size_t fsdict::AutData< %d >::bitVectorLength = %d;" % (self.conf.distance, self.conf.bitVectorLength)

        transitionStrings = [] # contains a comma-separated string for each single state
        for state in self.states:
            transitionStrings.append(",".join([str(x) for x in state.transitions]))
        sys.stdout.write("// The number of states per transition is 2^bitVectorLength . So, to retrieve the for state i and label n, use transitions[i* 2^bitVectorLength + n]\n")
        sys.stdout.write("const int    fsdict::AutData< %d >::transitions[] = {" % self.conf.distance)
        sys.stdout.write(",".join(transitionStrings))
        sys.stdout.write("};\n")

        finalInfoStrings = [] # contains a comma-separated string for each single state
        for state in self.states:
            finalInfoStrings.append(",".join([str(x) for x in state.getFinalInfo()]))
        sys.stdout.write("// There are bitVectorLength values per state. So, to retrieve the n-th value for state i, use finalInfo[bitVectorLength*i + n]\n")
        sys.stdout.write("const int    fsdict::AutData< %d >::finalInfo[] = {" % self.conf.distance)
        sys.stdout.write(",".join(finalInfoStrings))
        sys.stdout.write("};\n")

        sys.stdout.write("// There's one value (to be interpreted as bit-vector) per state. So, to retrieve the suffixMatch value for state i, use suffixMatch[i]\n")
        sys.stdout.write("const bits64 fsdict::AutData< %d >::suffixMatch[] = {" % self.conf.distance)
        sys.stdout.write(",".join([str(state.getSuffixMatch()) for state in self.states]))
        sys.stdout.write("};\n")


class MakeAut:
    """
    MakeAut provides thte logic to compute universal deterministic Levenshtein automata.
    """

    def __init__(self, autConfig):
        self.logger = logging.getLogger(__name__)
        self.conf = autConfig

    def normalizeState(self, state):
        for floorIdx in range(0, self.conf.distance): # not for upmost floor
            width = floorIdx
            for pos in range(-width,width+1):
                if state.get(floorIdx,pos):
                    state.set(floorIdx+1,pos-1,1)
                    state.set(floorIdx+1,pos,1)
                    state.set(floorIdx+1,pos+1,1)

    def compute(self):
        self.logger.debug("Start compute")

        levAut = LevAut(self.conf)
        # Maps states to an id. Used to find and retrieve equivalent states.
        uniqueStates = dict()
        workStack = []

        # add fail state with id -1 (not part of the actual automaton)
        failState = State(autConfig=self.conf)
        uniqueStates[failState] = -1

        # add root
        root = State(autConfig=self.conf)
        root.set(0,0,1)
        self.normalizeState(root)
        id = levAut.addState(root)
        uniqueStates[root] = id # add to the hash of unique states
        workStack.append(root) # add to the workStack, so it's processed below.
       
        while workStack:
            state = workStack.pop()
            #            state.printState()
            for transition in range(0,(2** self.conf.bitVectorLength)): # iterate over all possible bit vectors from 000..000 to 111..111
                self.logger.debug("transition is %s" % transition)
                nextState = self.getNextState(state, transition)

                if nextState in uniqueStates:
                    nextStateId = uniqueStates[nextState] # use the existing one instead
                    self.logger.debug("State already there: id=%s" % nextStateId)
                else:
                    nextStateId = levAut.addState(nextState)
                    uniqueStates[nextState] = nextStateId
                    workStack.append(nextState)
                    if levAut.getNrOfStates() % 100 == 0:
                        self.logger.info("Created %d states." % levAut.getNrOfStates())

                state.transitions.append(nextStateId)
                
        self.logger.info("Nr of states: %s" % len(levAut.states))
        count = 0
        return levAut





    def getNextState(self, state, transition):
#        pdb.set_trace()
        nextState = State(autConfig=self.conf)
        for floorIdx in range(0, self.conf.distance+1):
            width = floorIdx

            # match
            nextState.floors[floorIdx] |= state.floors[floorIdx] & (transition)

            if floorIdx < self.conf.distance:
                # substitute
                nextState.floors[floorIdx+1] |= state.floors[floorIdx]
                #insert
                nextState.floors[floorIdx+1] |= (state.floors[floorIdx] << 1)

            if floorIdx > 0 and not self.conf.noTranspositions:
                nextState.transpositionFloors[floorIdx] |= (state.floors[floorIdx-1] & (transition << 1))
                nextState.floors[floorIdx] |= (state.transpositionFloors[floorIdx] & (transition >> 1))
                
        self.normalizeState(nextState)
        return nextState
                    

def main():
    description = """
%(prog)s computes universal deterministic Levenshtein automata.
    """
    
    epilog = """
The universal Levenshtein automaton for distance k can be used to recognize, for a given pattern p, the set of 
strings s where the Levenshtein distance between p and s does not exceed k.

Those automata are universal in the sense that they don't depend on the pattern p: they are determined only by 
the distance threshold k and the set of edit operations you want to allow.

In the current implementation, this set of edit operations defaults to substitution, deletion, insertion and the 
transposition of two adjacent characters. Use the --no-transpositions flag to omit tanspositions.

You can use this script to build the Levenahtein automata you need offline, once. This script returns the 
transition table as static CPP arrays. You can simply paste it to your code base, and access them at runtime.
    """

    parser = argparse.ArgumentParser(description=description, epilog=epilog)
    parser.add_argument('distance', metavar='k', type=int,
                        help='The Lev distance threshold.')
    parser.add_argument('--no-transpositions', action="store_true", default=False,
                        help='Do not include tanspositions as atomic edit operation.')
    parser.add_argument('--debug', action="store_true", default=False,
                        help='Prints the resulting automaton in somewhat human-readable form.')
    args = parser.parse_args()

    logging.basicConfig(level=logging.INFO)
    distance = int(args.distance)
    autConfig = AutConfig(distance=args.distance, noTranspositions=args.no_transpositions)
    ma = MakeAut(autConfig=autConfig)
    levAut = ma.compute()
    if args.debug:
        levAut.dumpAut(debug=args.debug)
    else:
        levAut.dumpAutToCPP()


if __name__ == "__main__":
    main()
