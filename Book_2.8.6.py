import sys

class TreeLevel:
    def __init__(self, level):
        self.level = level #An integer; the Erdos number of people in self.names
        self.names = [] #List of people with Erdos number self.level
        self.nextLevel = None
        
    def __str__(self):
        return "level={0}, names={1}".format(self.level, self.names)

    def __eq__(self,other):
        """Note: other must be a TreeLevel object"""
        if self.level == other.level and self.names == other.names:
            if self.nextLevel is None and other.nextLevel is None:
                return True
            elif self.nextLevel is None or other.nextLevel is None:
                #One has nextLevel None, the other doesn't
                return False
            else:
                return self.nextLevel == other.nextLevel
        else:
            return False

    def __contains__(self, item):
        """Since can make sure self.names will be sorted in the end,
            implement binary search for efficiency"""
        lowerBound = 0
        upperBound = len(self.names)
        while(True):
            if(lowerBound == upperBound): #If ROI (region of interest) becomes empty
                return False

            #Next probe should be in the middle of the ROI
            midIndex = (lowerBound + upperBound) // 2

            #Fetch item at that position
            itemAtMid = self.names[midIndex]

            #How does the probed item compare to the target?
            if itemAtMid == item: #Found it
                return True
            elif itemAtMid < item:
                lowerBound = midIndex + 1 #Use upper half of ROI next time
            elif itemAtMid > item:
                upperBound = midIndex #Use lower half of ROI next time

    def addName(self,nameString):
        self.names.append(nameString)

    def sortNames(self):
        self.names.sort()

    def printTree(self):
        print("  " * self.level + str(self.names))
        if self.nextLevel is not None:
            self.nextLevel.printTree()


''' Function integrated into acquireScenarioInput
def extractAuthorNames(string):
    output = []
    currentName = ""
    commaCount = 0
    i = 0
    while(i < len(string)):
        c = string[i]
        if(c == ','):
            commaCount += 1
            if(commaCount % 2 == 0):
                output.append(currentName) #an author name is complete, add it
                currentName = "" #reset currentName
                i += 2 #to skip the space after the comma separating author names
                continue
        if(c == ':'):
            output.append(currentName) 
            break #got all names, break
        currentName += c
        i+=1
    return output
'''


def acquireScenarioInput(p,n):
    paperDatabase = []
    targetNamesList = []
    nameDictionary = {"Erdos, P.":0}
    nameDictionaryNextIndex = 1
    
    for line in range(p): #Acquire paperDatabase
        string = sys.stdin.readline()
        tempNameList = []
        currentName = ""
        commaCount = 0
        i = 0
        while(i < len(string)): #Extract author names from string
            c = string[i]
            if(c == ','):
                commaCount += 1
                if(commaCount % 2 == 0):
                    #Since each name has format LastName, Initial., each
                    #second comma marks the end of an author's name
                    nameValue = nameDictionary.get(currentName)
                    if nameValue is not None:
                        tempNameList.append(nameValue)
                    else:
                        nameDictionary[currentName] = nameDictionaryNextIndex
                        tempNameList.append(nameDictionaryNextIndex) #an author name is complete, add it
                        nameDictionaryNextIndex += 1
                    currentName = "" #reset currentName
                    i += 2 #to skip the space after the comma separating author names
                    continue
            if(c == ':'):
                #The colon occurs before the paper title, so it also marks
                #the end of an author's name
                nameValue = nameDictionary.get(currentName)
                if nameValue is not None:
                    tempNameList.append(nameValue)
                else:
                    nameDictionary[currentName] = nameDictionaryNextIndex
                    tempNameList.append(nameDictionaryNextIndex) #an author name is complete, add it
                    nameDictionaryNextIndex += 1 
                break #got all names in this line, break
            currentName += c #Build currentName (a string)
            i+=1
            
        paperDatabase.append(tempNameList)
        
    for line in range(n): #Acquire targetNamesList
        tempString = sys.stdin.readline()
        targetNamesList.append(tempString[0:len(tempString)-1]) #Remove ending newline character
        
    return paperDatabase, targetNamesList, nameDictionary


def buildTreeV3(treeObj, paperDatabase, paperDatabaseCurrentSize, allNamesInTree):
    """Function avoids use of recursion to avoid exceeding Python's max
        recursion depth"""
    nextLevelCreated = False
    for name in treeObj.names:
        index = 0
        while(index < paperDatabaseCurrentSize): #Traverse paperDatabase
            if name in paperDatabase[index]:
                #Add info from this entry of paperDatabase into the tree
                if(nextLevelCreated == False): #Create the next level if it hasn't been done yet
                    treeObj.nextLevel = TreeLevel(treeObj.level + 1)
                    nextLevelCreated = True #Make sure the next level is only created once
                for authorName in paperDatabase[index]:
                    if(authorName == name):
                        continue
                    if authorName not in allNamesInTree:
                        treeObj.nextLevel.addName(authorName)
                        allNamesInTree.append(authorName)
                paperDatabase.pop(index)
                paperDatabaseCurrentSize -= 1
                index -= 1 #To counter the constant increment afterwards (after popping an item)
            index += 1

    if(nextLevelCreated):
        treeObj.nextLevel.sortNames()
        
    return nextLevelCreated, treeObj.nextLevel, paperDatabase, paperDatabaseCurrentSize, allNamesInTree


def returnErdosNumStringV3(treeLevelObj,targetNameValue):
    """Avoid recursion to avoid exceeding Python's max recursion depth.
        Takes advantage of TreeLevel's binary search __contains__ method
        (more efficient than the 'in' operator?)"""
    if targetNameValue in treeLevelObj:
        return str(treeLevelObj.level), treeLevelObj.nextLevel
    if treeLevelObj.nextLevel is not None:
        return None, treeLevelObj.nextLevel
    else:
        return "infinity", treeLevelObj.nextLevel 


def main():
    """paperDatabase: List of papers, each one with one or more authors;
        authors are represented by integers
       targetNamesList: List of author names for which their Erdos number
        is desired; authors are represented by strings
       nameDictionary: Allows conversion between integer representation
        and string representation of author names"""
    numCases = int(sys.stdin.readline())

    for scenarioNum in range(1,numCases+1):
        inputList = sys.stdin.readline().split(" ")
        p = int(inputList[0]) #Number of lines that will be in paperDatabase
        n = int(inputList[1]) #Number of lines that will be in targetNamesList

        paperDatabase, targetNamesList, nameDictionary = acquireScenarioInput(p,n)
        
        #for i in range(p): #For debugging
        #    print(paperDatabase[i])

        #Initialize variables for this scenario
        root = TreeLevel(0)
        root.addName(0) #0 is the integer that represents Erdos
        allNamesInTree = [0]

        #Build the tree of authors linked to Erdos
        continueBuildTree, treeObj, paperDatabase, paperDatabaseCurrentSize, allNamesInTree = buildTreeV3(root, paperDatabase, p, allNamesInTree)
        while(continueBuildTree == True):
            #Repeatedly call buildTreeV3 to avoid exceeding max recursion depth
            continueBuildTree, treeObj, paperDatabase, paperDatabaseCurrentSize, allNamesInTree = buildTreeV3(treeObj, paperDatabase, paperDatabaseCurrentSize, allNamesInTree)

        #root.printTree() #for debugging
            
        #Output
        print("Scenario {0}".format(scenarioNum))
        for name in targetNamesList:
            targetNameValue = nameDictionary.get(name)
            if targetNameValue is not None: #name exists in nameDictionary
                output, treeObj = returnErdosNumStringV3(root,targetNameValue)
                while(output is None):
                    output, treeObj = returnErdosNumStringV3(treeObj,targetNameValue)
                print(name, output)
            else: #name does not exist in nameDictionary
                print(name, "infinity")

    return 0

main()
