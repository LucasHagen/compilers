import subprocess
from os import listdir
from os.path import isdir, join

def getTestCasesNames(dir):
    files = []
    for file in listdir(dir):
        if not isdir(file):
            files.append(file)
    return files

def readFile(dir, file):
    f = open(dir + file, "r")
    content = f.read()
    f.close()
    return content

def getTokens(dir, file):
    cmd = ['../main.out']
    input = readFile(dir, file).encode('utf-8')
    result = subprocess.run(cmd, stdout=subprocess.PIPE, input=input)
    return result.stdout.decode('utf-8')

def runTest(case_dir, gold_dir, file):
    tokens = getTokens(case_dir, file)
    gold = readFile(gold_dir, file)
    return tokens == gold

"""
=============================================
"""

dir = "./test_cases/"
dir_gold = "./test_golds/"
cases = getTestCasesNames(dir)
passed = []
invalid = []

print("Running tests...")
print("")
print("Individual Results:")

for test in cases:
    result = runTest(dir, dir_gold, test)

    if result:
        passed.append(test)
        print(' - ', test, ': ', "PASS", sep='')
    else:
        invalid.append(test)
        print(' - ', test, ': ', "ERROR", sep='')

if(len(invalid) == 0):
    final_result = "PASS"
else:
    final_result = "ERROR"

print("")
print("")
print("FINAL RESULT:", final_result)
print("")
