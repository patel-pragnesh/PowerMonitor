#!/bin/env python
## genReadings.py for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Tue Jul  7 19:12:22 2015 alexis mestag
## Last update Tue Jul  7 23:09:01 2015 alexis mestag
##

import  copy
import  datetime
import  math

class   SlaveModule:
    def __init__(self, pk, name, polling):
        self.pk = pk
        self.name = name
        self.polling = polling

def     main():
    ret = 0
    end = datetime.datetime.now()
    beg = end - datetime.timedelta(days=60)
    modules = {SlaveModule(1, 'TV', 1800)                  : lambda x: 1,
               SlaveModule(2, 'Frigo', 900)                : lambda x: 5,
               SlaveModule(3, 'Lave-vaisselle', 3600)      : lambda x: 3,
    }
    readings = list()
    readingId = 1
    for m, f in modules.items():
        tmp = copy.deepcopy(beg)
        inc = datetime.timedelta(seconds=m.polling)
        while (tmp < end):
            tstamp = int(tmp.timestamp())
            readings.append('({}, {}, {}, {}, {})'.format(readingId, m.pk, tstamp, 2, f(tstamp)))
            tmp += inc
            readingId += 1
    toPrint = ',\n'.join(readings) + ';'
    print(toPrint)
    return (0)

if (__name__ == '__main__'):
    exit(main())
