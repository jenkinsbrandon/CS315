


import functools
import copy

class DFA:
	def __init__(self, transitionFunction, initialState, finalStates, stateSet):
		self.delta = transitionFunction	
		self.q0 = initialState
		self.F = finalStates
		self.Q = stateSet
	def deltaHat(self, state, inputString):
		for a in inputString: 
			state = self.delta[state][a]
		return state
	def inLanguage(self, inputString):
		return self.deltaHat(self.q0, inputString) in self.F
	# comments: 
	# 	* python dictionary keys must be immutable
	#	* it is a KeyError to extract an entry using a non-existent key

class NFA: 
	def __init__(self, transitionFunction, initialState, finalStates):
		self.delta = transitionFunction	
		self.q0 = initialState
		self.F = set(finalStates)
	def deltaHat(self, state, inputString):
		"""deltaHat is smart enough to return the empty set if no transition is defined."""
		states = set([state])
		for a in inputString: 
			newStates = set([])
			for state in states: 
				try: 
					newStates = newStates | self.delta[state][a]
				except KeyError: pass
			states = newStates
		return states
	def inLanguage(self, inputString):
                
		return(len(self.deltaHat(self.q0, inputString) & self.F) > 0)
	def alphabet(self):
		"""Returns the NFA's input alphabet, generated on the fly."""
		Sigma = functools.reduce(lambda a,b:set(a)|set(b), [x.keys() for x in self.delta.values()])
		return Sigma
	def states(self):
		"""Returns the NFA's set of states, generated on the fly."""
		Q = set([self.q0]) | set(self.delta.keys()) | reduce(lambda a,b:a|b, reduce(lambda a,b:a+b, [x.values() for x in self.delta.values()]))	# {q0, all states with outgoing arrows, all with incoming arrows}
		return Q

def convertNFAtoDFA(N):
	"""Converts the input NFA into a DFA.  
	
	The output DFA has a state for every *reachable* subset of states in the input NFA.  
	In the worst case, there will be an exponential increase in the number of states.
	"""
	q0 = frozenset([N.q0])	# frozensets are hashable, so can key the delta dictionary
	Q = set([q0])
	unprocessedQ = Q.copy()	# unprocessedQ tracks states for which delta is not yet defined
	delta = {}
	F = []
	Sigma = N.alphabet()
	
	while len(unprocessedQ) > 0: 
		qSet = unprocessedQ.pop()
		delta[qSet] = {}
		for a in Sigma: 
			nextStates = functools.reduce(lambda x,y: x|y, [N.deltaHat(q,a) for q in qSet])
			nextStates = frozenset(nextStates)
			delta[qSet][a] = nextStates
			if not nextStates in Q: 
				Q.add(nextStates)
				unprocessedQ.add(nextStates)
			
	for qSet in Q: 
		if len(qSet & N.F) > 0: 
			F.append(qSet)
	M = DFA(delta, q0, F, Q)
	return M

def Count(M, n):
    tempSet = set(M.F)

    dfaDict = dict()
    curStateDict = dict()
    nextStateDict = dict()
    
    for q in M.Q:
        q = frozenset(q)
        s = {q}
        s = frozenset(s)
        
        nextStateDict.update({q:0})
                
        if s.issubset(tempSet):
            curStateDict.update({q:1})
        else:
            curStateDict.update({q:0})

            #JUST FOR SAFETY MEASURES
        if( s.issubset(M.Q)):
            dfaDict.update( {q: {str(0):M.delta[q][str(0)],
                             str(1):M.delta[q][str(1)] ,
                             str(2):M.delta[q][str(2)] ,
                             str(3):M.delta[q][str(3)] ,
                             str(4):M.delta[q][str(4)] ,
                             str(5):M.delta[q][str(5)] ,
                             str(6):M.delta[q][str(6)] ,
                             str(7):M.delta[q][str(7)] ,
                             str(8):M.delta[q][str(8)] ,
                             str(9):M.delta[q][str(9)]}}  )
            
        else:
            print('Could not find state in DFA...exiting')
            exit()
        
    count = 0
    while count < (n):
    
        for k,v in dfaDict.items():
            num = 0
        
            for sym in ['0','1','2','3','4','5','6','7','8','9']:
                num = num + curStateDict[ v[ sym ] ]

            #end for loop
                
            nextStateDict.update( { k : num } )
        #end for loop
            
        curStateDict.clear()
        curStateDict = copy.deepcopy(nextStateDict)
        count = count + 1
    #end while loop
        
    return(nextStateDict[M.q0])


        
def main():
    delta = {
     'A': { '0' : set (['AA', 'A']), '1' : set (['AA', 'B']),
             '2' : set (['AA', 'C']), '3' : set (['AA', 'D']), 
             '4' : set (['AA', 'E']), '5' : set (['AA', 'F']),
             '6' : set (['AA', 'G']), '7' : set (['AA', 'A']), 
             '8' : set (['AA', 'B']), '9' : set (['AA', 'C'])},
     'AA': { '0' : set (['AA']), '1' : set (['BB']),
             '2' : set (['CC']), '3' : set (['DD']), 
             '4' : set (['EE']), '5' : set (['FF']),
             '6' : set (['GG']), '7' : set (['AA']), 
             '8' : set (['BB']), '9' : set (['CC'])},
     'B': { '0' : set (['BB', 'D']), '1' : set (['BB', 'E']),
             '2' : set (['BB', 'F']), '3' : set (['BB', 'G']), 
             '4' : set (['BB', 'A']), '5' : set (['BB', 'B']),
             '6' : set (['BB', 'C']), '7' : set (['BB', 'D']), 
             '8' : set (['BB', 'E']), '9' : set (['BB', 'F'])},
     'BB': { '0' : set (['DD']), '1' : set (['EE']),
             '2' : set (['FF']), '3' : set (['GG']), 
             '4' : set (['AA']), '5' : set (['BB']),
             '6' : set (['CC']), '7' : set (['DD']), 
             '8' : set (['EE']), '9' : set (['FF'])},
     'C': { '0' : set (['CC', 'G']), '1' : set (['CC', 'A']),
             '2' : set (['CC', 'B']), '3' : set (['CC', 'C']), 
             '4' : set (['CC', 'D']), '5' : set (['CC', 'E']),
             '6' : set (['CC', 'F']), '7' : set (['CC', 'G']), 
             '8' : set (['CC', 'A']), '9' : set (['CC', 'B'])},
     'CC': { '0' : set (['GG']), '1' : set (['AA']),
             '2' : set (['BB']), '3' : set (['CC']), 
             '4' : set (['DD']), '5' : set (['EE']),
             '6' : set (['FF']), '7' : set (['GG']), 
             '8' : set (['AA']), '9' : set (['BB'])},
     'D': { '0' : set (['DD', 'C']), '1' : set (['DD', 'D']),
             '2' : set (['DD', 'E']), '3' : set (['DD', 'F']), 
             '4' : set (['DD', 'G']), '5' : set (['DD', 'A']),
             '6' : set (['DD', 'B']), '7' : set (['DD', 'C']), 
             '8' : set (['DD', 'D']), '9' : set (['DD', 'E'])},
     'DD': { '0' : set (['CC']), '1' : set (['DD']),
             '2' : set (['EE']), '3' : set (['FF']), 
             '4' : set (['GG']), '5' : set (['AA']),
             '6' : set (['BB']), '7' : set (['CC']), 
             '8' : set (['DD']), '9' : set (['EE'])},
     'E': { '0' : set (['EE', 'F']), '1' : set (['EE', 'G']),
             '2' : set (['EE', 'A']), '3' : set (['EE', 'B']), 
             '4' : set (['EE', 'C']), '5' : set (['EE', 'D']),
             '6' : set (['EE', 'E']), '7' : set (['EE', 'F']), 
             '8' : set (['EE', 'G']), '9' : set (['EE', 'A'])},
     'EE': { '0' : set (['FF']), '1' : set (['GG']),
             '2' : set (['AA']), '3' : set (['BB']), 
             '4' : set (['CC']), '5' : set (['DD']),
             '6' : set (['EE']), '7' : set (['FF']), 
             '8' : set (['GG']), '9' : set (['AA'])},
     'F': { '0' : set (['FF', 'B']), '1' : set (['FF', 'C']),
             '2' : set (['FF', 'D']), '3' : set (['FF', 'E']), 
             '4' : set (['FF', 'F']), '5' : set (['FF', 'G']),
             '6' : set (['FF', 'A']), '7' : set (['FF', 'B']), 
             '8' : set (['FF', 'C']), '9' : set (['FF', 'D'])},
     'FF': { '0' : set (['BB']), '1' : set (['CC']),
             '2' : set (['DD']), '3' : set (['EE']), 
             '4' : set (['FF']), '5' : set (['GG']),
             '6' : set (['AA']), '7' : set (['BB']), 
             '8' : set (['CC']), '9' : set (['DD'])},
     'G': { '0' : set (['GG', 'E']), '1' : set (['GG', 'F']),
             '2' : set (['GG', 'G']), '3' : set (['GG', 'A']), 
             '4' : set (['GG', 'B']), '5' : set (['GG', 'C']),
             '6' : set (['GG', 'D']), '7' : set (['GG', 'E']), 
             '8' : set (['GG', 'F']), '9' : set (['GG', 'G'])},
     'GG': { '0' : set (['EE']), '1' : set (['FF']),
             '2' : set (['GG']), '3' : set (['AA']), 
             '4' : set (['BB']), '5' : set (['CC']),
             '6' : set (['DD']), '7' : set (['EE']), 
             '8' : set (['FF']), '9' : set (['GG'])},
              
     'H' : {'0' : set (['K']),'1' : set (['B','BB','J']), '2' : set (['C','J']), '3' : set (['D','J']), 
             '4' : set (['E','J']), '5' : set (['F','J']),
             '6' : set (['G','J']), '7' : set (['I','J']), 
             '8' : set (['B','J']), '9' : set (['C','J'])},
     'I': { '0' : set (['AA', 'A']), '1' : set (['AA', 'B']),
             '2' : set (['AA', 'C']), '3' : set (['AA', 'D']),
             '4' : set (['AA', 'E']), '5' : set (['AA', 'F']),
             '6' : set (['AA', 'G']), '7' : set (['AA', 'A']), 
             '8' : set (['AA', 'B']), '9' : set (['AA', 'C'])},
     'J': {'0' : set (['AA']),'1' : set (['BB']), '2' : set (['CC']), '3' : set (['DD']), 
             '4' : set (['EE']), '5' : set (['FF']),
             '6' : set (['GG']), '7' : set (['AA']), 
             '8' : set (['BB']), '9' : set (['CC'])},
              
     'K': {'0' : set (['L']),'1' : set (['L']), '2' : set (['L']), '3' : set (['L']), 
             '4' : set (['L']), '5' : set (['L']),
             '6' : set (['L']), '7' : set (['L']), 
             '8' : set (['L']), '9' : set (['L'])},
     'L': {'0' : set (['L']),'1' : set (['L']), '2' : set (['L']), '3' : set (['L']), 
             '4' : set (['L']), '5' : set (['L']),
             '6' : set (['L']), '7' : set (['L']), 
             '8' : set (['L']), '9' : set (['L'])}
              }

    N = NFA(delta, 'H', ['A', 'AA', 'I', 'K'])

    print ('122', N.inLanguage('122'))
    print ('133', N.inLanguage('133'))



    M = convertNFAtoDFA(N)


    print ('100', M.inLanguage('100'))
    print ('121', M.inLanguage('121'))
    print ('122', M.inLanguage('122'))
    print ('133', M.inLanguage('133'))
    print ('10', M.inLanguage('10'))
    print ('21', M.inLanguage('21'))
    print ('27', M.inLanguage('27'))
    print ('41', M.inLanguage('41'))
    print ('7', M.inLanguage('7'))
    #print ('741842607938866199443579680083706254648829519399268', M.inLanguage('741842607938866199443579680083706254648829519399268'))
    
    while True:
        print("")
        print("This program will take as input k, where k is the number of digits in an integer.")
        print("It will then output the number of integers of length k that are weakly divisible by 7")
        print("")

        length = input("Enter k: ")
        k = int(length)

        print( "Number of integers: " + str(Count(M, k)) )
   


main()
