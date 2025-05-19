"""
This is an automated version file generator

it is build for managing software versions and their history, as well as planning releases

it adds git-tags for every version

version are build the following way: [major].[minor].[patch] [flag]

for example:
    1.0.2 --alpha
    3.6.12
    ...

the flag can be:
    --alpha     (for alpha releases -> unstable) Versions for in-house testing
    --beta      (for beta releases -> unstable) Versions for in-community testing
    --pre       (for prereleases -> stable) Versions for last second changes
    [none]      (for releases -> stable) Versions for official releases

"""

 # Copyright 2025 Leon Rieger
 # 
 # Licensed under the Apache License, Version 2.0 (the "License");
 # you may not use this file except in compliance with the License.
 # You may obtain a copy of the License at
 # 
 #     http://www.apache.org/licenses/LICENSE-2.0
 # 
 # Unless required by applicable law or agreed to in writing, software
 # distributed under the License is distributed on an "AS IS" BASIS,
 # WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 # See the License for the specific language governing permissions and
 # limitations under the License.
 #

#import subprocess
import time
import os

available_flags = ["", "--pre", "--beta", "--alpha"]

def log(logText: str)-> None:
    logText = logText.replace("\n","[PARAGRAPH]")
    currentTimeandDate = time.strftime("[ %Y-%m-%d | %H:%M:%S UTC%z ]",time.localtime(time.time()))
    logTEXT = "\n"+currentTimeandDate+ "\t"+logText
    if os.path.isfile("version-file-generator-assets\\history.txt"):
        with open("version-file-generator-assets\\history.txt", "a") as logFile:
            logFile.write(logTEXT)
    else:
        logTEXT = ["version history\n","date and time\tinfo",logTEXT]
        with open("version-file-generator-assets\\history.txt", "w") as logFile:
            logFile.writelines(logTEXT)

with open("version-file-generator-assets\\current_state.txt", "r") as file:
    content = file.readline().split("    ")
    version_major = int(content[0])
    version_minor = int(content[1])
    version_patch = int(content[2])
    version_flag = content[3]

print("Version Generator")
print('Type "major" to update the major version')
print('Type "minor" to update the minor version')
print('Type "patch" to update the patch release')
print('Type "flag" to add a new flag to the version')

input_text = input(">>> ")
if input_text=="major":
    version_major += 1
elif input_text=="minor":
    version_minor += 1
elif input_text=="patch":
    version_patch += 1
elif input_text=="flag":
    pass
else:
    print("invalid_input")
