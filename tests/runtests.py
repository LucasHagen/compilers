import subprocess
from pathlib import Path
from os import listdir
from os.path import isdir, isfile

def getTestCasesNames(dir):
    files = []
    for file in listdir(dir):
        if not isdir(file):
            files.append(file)
    return files

def readFile(dir, file):
    f = open(dir + "/" + file, "r")
    content = f.read()
    f.close()
    return content

def getTokens(main_exe, dir, file):
    cmd = [main_exe]
    input = readFile(dir, file).encode('utf-8')
    result = subprocess.run(cmd, stdout=subprocess.PIPE, input=input)
    return result.stdout.decode('utf-8')

def runTest(main_exe, case_dir, gold_dir, file):
    tokens = getTokens(main_exe, case_dir, file)
    gold = readFile(gold_dir, file)
    return tokens == gold

"""
    ==========    MAIN SCRIPT    ==========
"""

script_path = Path(__file__).parent.absolute().as_posix()
main_exe = script_path + "/../main.out"
dir = script_path + "/test_cases"
dir_gold = script_path + "/test_golds"
cases = getTestCasesNames(dir)
passed = []
invalid = []

cases.sort()

if (not isfile(main_exe)):
    print("ERROR! main.out does not exist or is in wrong directory!")
    print("Try running 'make'")
    exit()

print("Running tests...")
print("")
print("Individual Results:")

for test in cases:
    result = runTest(main_exe, dir, dir_gold, test)

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
