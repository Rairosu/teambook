###
### This script merges all '.cpp' files into "merged.txt"
###

import os

queue = [os.getcwd()]
que_head = 0
queue_len = 1

files = []

while que_head < queue_len:
    cur_location = queue[que_head]
    que_head += 1
    listdir = os.listdir(cur_location)
    for file_name in listdir:
        cur_file = cur_location + "/" + file_name
        if os.path.isdir(cur_file):
            queue.append(cur_file)
            queue_len += 1
        else:
            if '.cpp' in file_name:
                files.append(cur_file)

result = open("merged.txt", "w")

for i in files:
    cur_file = open(i, 'r')
    all_lines = cur_file.readlines()
    for j in all_lines:
        result.write(j)
    result.write('\n\n\n')

print('found %d files:' % len(files))
for i in files:
    print (" ", i)
