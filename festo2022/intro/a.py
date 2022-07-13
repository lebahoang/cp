# Username, ID, Access Key, First Login Time
from hashlib import shake_128

from sqlalchemy import false

def get_login_time(x):
    y = x.split(':')
    return (int(y[0]), int(y[1]))
with open('./office_database.txt') as f:
    s1 = 0
    s2 = 0
    s3 = 0
    users = []
    for l in f.readlines():
        f1 = f2 = f2 = False
        x = l.strip().split(',')
        user = x[0]
        uid = x[1]
        int_uid = int(uid)
        access_key = int(x[2])
        login_time = get_login_time(x[3])

        if uid.find('814') != -1:
            s1 += int_uid
            f1 = True
        if (access_key & (1 << 3)) != 0:
            s2 += int_uid
            f2 = True
        if login_time[0] < 7 or (login_time[0] == 7 and login_time[1] < 14):
            s3 += int_uid
            f3 = True
        if f1 and f2 and f3:
            users.append(user)
    print(s1)
    print(s2)
    print(s3)
    print(users)