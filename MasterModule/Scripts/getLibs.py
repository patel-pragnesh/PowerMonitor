#!/bin/env python
## getLibs.py for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule/Scripts
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Wed Apr 22 22:08:26 2015 alexis mestag
## Last update Wed Apr 22 22:20:31 2015 alexis mestag
##

import  re
import  subprocess
import  sys

def     main():
    binary = sys.argv[1]
    out = subprocess.check_output(['ldd', binary])
    out = out.decode('ascii')
    lines = [line.strip() for line in out.split('\n')]
    for line in lines:
        m = re.match(r'^.*? => (?P<lib>.*?) \(.*?\)$', line)
        if (m):
            print(m.group('lib'))

if (__name__ == '__main__'):
    ret = main()
    exit(ret)
