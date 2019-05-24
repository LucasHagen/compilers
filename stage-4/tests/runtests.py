import subprocess
import csv
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
    content = None

    if isfile(dir + "/" + file):
        f = open(dir + "/" + file, "r")
        content = f.read()
        f.close()

    return content

def getResultCode(main_exe, dir, file):
    cmd = [main_exe]
    input = readFile(dir, file).encode('utf-8')
    result = subprocess.run(cmd, stdout=subprocess.PIPE, input=input)
    return result.returncode

def getGoldCodes(csv_path):
    result = {}
    with open(csv_path) as csvfile:
        reader = csv.DictReader(csvfile)

        for row in reader:
            result[row['test']] = int(row['result'])

    return result

"""
    ==========    MAIN SCRIPT    ==========
"""

script_path = Path(__file__).parent.absolute().as_posix()
main_exe = script_path + "/../etapa4"
dir = script_path + "/test_cases"
cases = getTestCasesNames(dir)
golds = getGoldCodes(script_path + "/gold.csv")
passed = []
invalid = []

cases.sort()

if (not isfile(main_exe)):
    print("ERROR! Executable does not exist or is in wrong directory!")
    print("Try running 'make'")
    exit()

print("Running tests...")
print("")
print("Errors:")

for test in cases:
    if not test in golds:
        print(' - ', test, ': ', "GOLD NOT FOUND", sep='')
    else:
        result = int(getResultCode(main_exe, dir, test))
        if result == golds[test]:
            passed.append(test)
            # print(' - ', test, ': ', "PASS", sep='')
        else:
            invalid.append(test)
            print(' - ', test, ': ', "ERROR: (expected: ", golds[test], ", found: ", result, ")", sep='')

if(len(invalid) == 0):
    final_result = "PASS"
else:
    final_result = "ERROR"

print("")
print("")
print("FINAL RESULT:", final_result)
print("")

exit(len(invalid))
