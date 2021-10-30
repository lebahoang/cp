import sys
import re

def ss(file_object):
    rs = []
    for line in file_object:
        line = line.strip()
        if line == '': continue
        x = ''
        if line[0] == '-' or line[0] == '+':
            x = line[1:]
        else:
            x = line
        if re.match('^[0-9]+$', x):
            y = int(line)
            if y >= -1000000000 and y <= 1000000000:
                rs.append(int(line))
    return rs

        

#print ss(['124', '   +1', 'd3242  ', '++3', '345sdf345', 'dasd', '-1', '23.9' ])
def getIndexOfDay(day):
    arr = {
        'Mon': '0',
        'Tue': '1',
        'Wed': '2',
        'Thu': '3',
        'Fri': '4',
        'Sat': '5',
        'Sun': '6'
    }
    return arr[day]

def substract(a, b):
    rs = 0
    ha = int(a.split(' ')[0])
    ma = a.split(' ')[1].split('-')[1]
    ma = int(ma.split(':')[0])*60 + int(ma.split(':')[1])
    ha = ha*24*60 + ma 

    hb = int(b.split(' ')[0])
    mb = b.split(' ')[1].split('-')[0]
    mb = int(mb.split(':')[0])*60 + int(mb.split(':')[1])
    hb = hb*24*60 + mb

    rs = hb-ha
    return rs

def solution(S):
    meetings = []
    for meeting in S.split('\n'):
        day = meeting.split(' ')[0]
        ind = getIndexOfDay(day)
        meeting = ind + ' ' + meeting.split(' ')[1] 
        meetings.append(meeting)
    meetings.append('0 00:00-00:00')
    meetings.append('6 24:00')
    meetings = sorted(meetings)
    t = -1
    for i in xrange(len(meetings)-1):
        rs = substract(meetings[i], meetings[i+1])
        print meetings[i], meetings[i+1], rs
        if t == -1 or t < rs: t = rs
    
    return t

print solution('Sun 10:00-20:00\nFri 05:00-10:00\nFri 16:30-23:50\nSat 10:00-24:00\nSun 01:00-04:00\nSat 02:00-06:00\nTue 03:30-18:15\nTue 19:00-20:00\nWed 04:25-15:14\nWed 15:14-22:40\nThu 00:00-23:59\nMon 10:00-13:00\nMon 15:00-21:00')
print solution('Mon 01:00-23:00\nTue 01:00-23:00\nWed 01:00-23:00\nThu 01:00-23:00\nFri 01:00-23:00\nSat 01:00-23:00\nSun 01:00-21:00')