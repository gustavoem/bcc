import sys
import re
import copy

class Clause:
    def __init__ (self, left_var, right_vars):
        """Default Constructor
        """
        self.implication = left_var
        self.predicates = right_vars

    def concluded (self):
        """Returns true if the implication is true in the clause
        """
        if self.predicates == []:
            return True
        return False

    def to_str (self):
        """Returns the clause representation in s as a string
        """
        s = str (self.implication) 
        
        if (self.predicates is not []):
            s += " :- "
            for p in self.predicates:
                s += str (p) + ", "
        return s

    def has_premise (self, p):
        """Returns true if clause has premise p
        """
        if p in self.predicates:
            return True
        else:
            return False

    def assume_truth (self, p):
        """Removes p from the premises assuming that p is true
        """
        if (self.has_premise (p)):
            self.predicates.remove (p)

    
    def implication (self):
        """Returns the implication symbol of the clause
        """
        return self.left_var


agenda = []
inferred = {}
KB = []
filename = input ()
f = open (filename, 'r')
for line in f:
    if ":-" in line:
        [left_part, right_part] = re.split (":-", line)
    else:
        [left_part, right_part] = [line, ""] 
    
    # remove non-symbol from left part
    left_part = re.sub ("\W+", "", left_part) 

    # remove split borders
    right_vars = re.split ("\W+", right_part)
    right_vars = [s for s in right_vars if  s != ""]

    #print ("left_part: " + left_part + "|")
    #print ("right_part: " + "".join (right_vars) + "|")
    
    inferred[left_part] = False
    for var in right_vars:
        inferred[var] = False

    new_clause = Clause (left_part, right_vars)
    if (new_clause.concluded ()):
        agenda.append (left_part)
    KB.append (new_clause)
f.close ()


print ("Concluded: ")
while  len(agenda) is not 0:
    p = agenda.pop ()
    #print ("\n" + p + " => ")
    if not (inferred[p]):
        inferred[p] = True
        for clause in KB:
            if (clause.has_premise (p)):
                clause.assume_truth (p)
                #print ("    " + clause.to_str ())
                if (clause.concluded ()):
                    implication = clause.implication
                    print (implication)
                    agenda.append (implication)
