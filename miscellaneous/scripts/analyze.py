#!/usr/bin/python2.7

# Framework for parsing httpd.log file
# Author: Arch1t3ct

class Log:
    def __init__(self, date, time, ip, username, dest, port, method, page, PC, result):
        self.date = date
        self.time = time
        self.ip = ip
        self.username = username
        self.destination = dest
        self.port = port
        self.method = method
        self.page = page
        self.PC = PC
        self.result = result

logs = []
filename = "httpd.log"
f = open(filename, 'r')
for line in f:
    info = line.split(' ')
    logs.append(Log(info[0], info[1], info[2], info[3], info[4], info[5], info[6], info[7], info[8], info[9]))

#known users
logged = {}

for log in logs:
    if log.page == '/docs.cfm':
        if log.username in logged:
            logged[log.username] += 1
        else:
            logged[log.username] = 1

maxi = 0
for user in logged:
    if logged[user] > maxi:
        maxi = logged[user]
        #print("New max: {} : {}".format(user, logged[user]))


