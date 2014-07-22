#!/usr/bin/python3.2
'''
Python-Digital-Rain v1.0
========================
Simple project that tries to simulate the digital rain effect on screen (terminal).

Environment:
------------
OS:        Linux (required)
Python:    v3.2 (required)
Modules:    curses, random, time (all standard modules)

Usage:
------
Launches python-digital-rain-v1.py from terminal or from GUI interface. Don't try to
use it inside a development interface, it would fail. The script tries to display a full
terminal-sized rain, don't resize the window while running!

author: Steve De Jongh (stdj79@gmail.com)

'''

import curses,random,time

class Rain(object):
    '''
    Screen usage class.
    '''
    def __init__(self):
        self.objects = []   # Will contain the list of all objects falling on the screen
        
    def start(self):
        '''
        Lauches curses process and define basics attributes for the class
        '''
        self.xCornerUL = 0              
        self.yCornerUL = 0
        self.window = curses.initscr()          # initialize the curses working area (full terminal)
        curses.curs_set(0)                      # hide cursor
        curses.start_color()                    # start using colors
        
        curses.init_pair(1, curses.COLOR_GREEN, curses.COLOR_BLACK) # Green on Black
        
        self.xCornerLR = self.window.getmaxyx()[1] -1   # Lower-Right corner
        self.yCornerLR = self.window.getmaxyx()[0] -1   # X and Y
        
    def stop(self):
        '''
        Stops curses process
        '''
        curses.endwin()             
        
    def addChar(self,ch,x=0,y=0,options=0):
        '''
        Print the give character (ascii), in the curses matrix, for give x and y values
        '''
        intCh = ord(ch)
        self.window.addch(y,x,intCh,options)
        
    def apply(self):
        '''
        Display the screen
        '''
        self.window.refresh()
        
    def cls(self):
        '''
        Clear the screen
        '''
        self.window.clear()
        
    def startGoutte(self,length=8):
        '''
        Initialise a new object
        '''
        startX = random.randint(self.xCornerUL,self.xCornerLR)  # random X position
        speed = random.randint(5,10)                            # random falling speed (1 is faster, max 100)
        newGoutte = Goutte(length,speed)            # Create the new object
        self.objects.append(newGoutte)              # Add object to the list
        newGoutte.start(startX, self.yCornerUL)     # Starts the object
        
    def draw(self):
        '''
        Updates the screen matrix, sets chars and colors.
        '''
        
        # Making a 'blank' screen, clearscreen is faster but makes the display blinking (ugly!)
        for y in range(self.yCornerUL,self.yCornerLR):
            for x in range(self.xCornerUL,self.xCornerLR):
                self.addChar(" ", x, y)
                
        # Draw each object on screen
        for goutte in self.objects:
            for py in range(self.yCornerUL,self.yCornerLR):
                if py in goutte.points.keys():
                    first = max(goutte.points.keys())
                    second = first - 1
                    last = min(goutte.points.keys())
                    
                    if py == first:     # The lowest element (the first of the object) is the brightest
                        self.window.attron(curses.A_BOLD)
                        self.addChar(goutte.points[py], goutte.x, py)
                        self.window.attroff(curses.A_BOLD)
                    elif py == second:  # Some emphasis for the second element
                        self.window.attron(curses.A_BOLD)
                        self.addChar(goutte.points[py], goutte.x, py,curses.color_pair(goutte.color))
                        self.window.attroff(curses.A_BOLD)
                    else:               # Standard display for the rest
                        self.addChar(goutte.points[py], goutte.x, py,curses.color_pair(goutte.color))
        self.apply()
        
    def run(self):
        '''
        Main object method ... the real engine of the screen.
        '''
        self.start()        # Starts working
        while 1:
            if len(self.objects) > 0:       # If something to display ...
                for goutte in self.objects:
                    if min(goutte.points.keys()) <= self.yCornerLR:     # If the object isn't below the display area, let's move it down
                        goutte.down()
                    else:
                        self.objects.remove(goutte)                     # The object is under the screen, remove it
                        goutte.stop()
            test = random.randint(1,10)                                 # Random number... will there be a new object ?
            if test > 8:                                                # roughly 20% to get a new object
                lmax = self.yCornerLR - self.yCornerUL -2               # Max length of the object
                lmin = lmax//2                                          # Min length of the object
                lgoutte = random.randint(lmin,lmax)                     # Length of the object between lmin and lmax
                self.startGoutte(lgoutte)                               # Create the object
            self.draw()                             # Let's make the matrix
            time.sleep(0.02)                        # Wait a bit before next iteration
        self.stop()
        
class Goutte(object):
    '''
    Defines the moving object
    '''
    def __init__(self,length=8,speed=100):
        self.length = length        
        self.allchars = "abcdefghijklmnopqrstuvwxyz0123456789"      # All chard that can be used to draw the object
        self.speed = speed                                          
        self.points = {}        # Will contain all 'points' of the object
        self.loop = 0           # state of the object
        self.color = 1          # color (cannot be anything else at this time)
        
    def setchar(self):
        return self.allchars[random.randint(0,len(self.allchars)-1)]    # get randomchar from self.allchars
        
    def start(self,x,y):
        self.x = x
        self.starty = y
        self.posy = y
        self.char = self.setchar()
        
        # Defines all characters of the object
        for a in range(0,self.length):
            py = y - a
            self.points[py] = self.setchar()
            
    def down(self):
        '''
        Used to move the object downward
        '''
        test = self.loop/self.speed     # If test == 1 => let's move
        if test == 1:
            self.posy = self.posy + 1
            newdic = {}
            for py in self.points:
                newpy = py + 1
                newdic[newpy] = self.setchar()
                self.points = newdic
            self.loop = 0
        self.loop = self.loop + 1
        
    def stop(self):
        '''
        Delete all attached attributes, faster garbage collection ? (not sure if it works in any way) 
        '''
        del self.allchars
        del self.x
        del self.starty
        del self.posy
        del self.char
        del self.points
        del self.loop
        del self.speed
            

# MAIN PROGRAM
screen = Rain()
screen.run()
screen.stop()
