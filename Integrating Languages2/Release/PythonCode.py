import re
import string

def CountItem(): # counts the amount of recurring items on the list
 text = open("GroceryList.txt", "r") 
  
 fruitD = dict()
  
 for line in text:
   
    line = line.strip()
  
    line = line.lower()
   
    words = line.split(" ")
     
    for word in words:
        
        if word in fruitD:
           
            fruitD[word] = fruitD[word] + 1
        else:
           
            fruitD[word] = 1
  
 for key in list(fruitD.keys()):
    print(key, ":", fruitD[key])

def ItemSearch(v): #searches user input
 text = open("GroceryList.txt", "r")

 userInput=v
 upperUserInput = userInput.capitalize()
 
 data = text.read()

 searchItemCount = data.count(upperUserInput)
 print("This is what was found for your search of "+v)
 print(v,": ", searchItemCount)
 return 100;


def writeToFile(): # write to file 
  text = open("GroceryList.txt", "r") 
  writeText = open("frequency.dat","w")

  fruitD = dict()
  
  for line in text:
   
    line = line.strip()
  
    line = line.lower()
   
    words = line.split(" ")
     
    for word in words:
        
        if word in fruitD:
           
            fruitD[word] = fruitD[word] + 1
        else:
           
            fruitD[word] = 1
  
  for key in list(fruitD.keys()):
   writeText.write('%s %s\n' % (key,fruitD[key]))
  writeText.cloes()

