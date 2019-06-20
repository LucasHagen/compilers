import subprocess
import csv
import re
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

def getResult(main_exe, sim_exe, dir, file):
    cmd = [main_exe]
    sim_cmd = [sim_exe, script_path + "/../ilocsim.py", "-x", "--data", "10000", "--stack", "20000", "-m"]
    input = readFile(dir, file).encode('utf-8')
    try:
        result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, input=input, timeout=2)
        if result.returncode == 0:
            result2 = subprocess.run(sim_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, input=result.stdout, timeout=2)
            return result2.stdout.decode('utf-8')
    except:
        return None
    return None

def isValid(result, gold):
    result_map = extractMemory(result)
    gold_map   = extractMemory(gold)

    for k,v in gold_map.items():
        if not (k in result_map) or result_map[k] != v:
            return False

    return True

mem_re = re.compile("(\\d{8}) (-?\\d+)")
def extractMemory(output):
    result = {}
    matches = mem_re.findall(output)
    for match in matches:
        result[match[0]] = match[1]

    return result


"""
    ==========    MAIN SCRIPT    ==========
"""

script_path = Path(__file__).parent.absolute().as_posix()
main_exe = script_path + "/../etapa6"
sim_exe = "python3"
dir = script_path + "/test_cases"
gold_dir = script_path + "/test_golds"
cases = getTestCasesNames(dir)
passed = []
invalid = []

cases.sort()

if (not isfile(main_exe)):
    print("ERROR! Executable does not exist or is in wrong directory!")
    print("Try running 'make'")
    exit()

print("Running tests...")
print("")
print("Tests:")

for test in cases:
    gold = readFile(gold_dir, test)

    if not gold:
        print(' - ', test, ': ', "GOLD NOT FOUND", sep='')
    else:
        result = getResult(main_exe, sim_exe, dir, test)
        if result != None and isValid(result, gold):
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

exit(len(invalid))
