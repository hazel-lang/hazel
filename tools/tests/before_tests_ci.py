r"""
    This script essentially `copies` the entire folder of Hazel and into a new directory that is used solely by 
    CMake during CI. 
    It removes all instances of `static`, `inline`, `extern` or any other keywords that might result in internal 
    linkage and thus break Hazel's C Compiler Tests. 
    With this internal linkage, it is IMPOSSIBLE to externally test a method used in the compiler. An example for 
    this would be `lexer_next()` or `lexer_next_n()` which _need_ to be inlined and statically linked for performance reasons.
"""

import os 
import shutil
ospd = os.path.dirname
# Navigate to root folder
# ../../../
ROOT = ospd(ospd(ospd(os.path.abspath(__file__))))
SOURCEROOT = os.path.join(ROOT, 'hazel')
# The `HazelInternalTests` folder will be created by this script
DESTINATIONROOT = os.path.join(ROOT, 'HazelInternalTests')

# Acceptable directories to remove external linkage
# We cannot remove it globally as it affects CSTL as well - and results in the `multiple definitions` error
ACCEPTABLE_REMOVEABLE_DIRS = (
    'compiler',
)

def main():
    # List of all folders that this script has created
    MKDIRS = [] 
    copied = 0
    for root, _, files in os.walk(SOURCEROOT):
        if '.git' in root:
            continue
        destroot = root.replace(SOURCEROOT, DESTINATIONROOT)

        if destroot not in MKDIRS:
            try:
                os.mkdir(destroot)
            except FileExistsError:
                pass
            MKDIRS.append(destroot)

        for file in files:
            # CMakeLists.txt is not required to be copied
            # TODO(jasmcaus): Maybe change this?
            if not file.endswith(('.c', '.cpp', '.h', '.hpp')):
                continue

            filepath = os.path.join(root, file)
            destpath = os.path.join(destroot, file)
            # We don't need the `main.c` file that comes with Hazel (that's used to build the Static/Shared library and 
            # because of internal linkage, we cannot test certain methods of the Compiler)
            # So, we rename `maininternaltests.c` to `main.c` only inside this testing context
            if file.endswith('main.c'):
                continue

            if(file.endswith('hazel.h')):
                destpath = os.path.join(destroot, 'HazelInternalTests.h')
            
            if(file.endswith('maininternaltests.c')):
                destpath = os.path.join(destroot, 'main.c')

            # print(filepath)
            print(f"[INFO] Copying {destpath}")

            # Copy contents
            shutil.copy(filepath, destpath)
            copied += 1

            # Replace static, inline, extern ...
            with open(destpath) as f:
                s = f.read()

                s = s.replace('hazel', 'HazelInternalTests')
                s = s.replace('HazelInternalTests Language', 'Hazel Language')
                s = s.replace('hazel.h', 'HazelInternalTests.h')

                if root.endswith(ACCEPTABLE_REMOVEABLE_DIRS):
                    s = s.replace('static inline ', '')
                    s = s.replace('static ', '')
                    s = s.replace('inline ', '')
                    s = s.replace('extern ', '')
                    s = s.replace('"C" {', 'extern "C" {')

                s = s.replace('// "C"', '// extern "C"')
            f.close()

            # Write the changes back to disk
            with open(destpath, 'w') as f:
                f.write(s)

    print(f'\n[INFO] Copied {copied} source files from Hazel.')

if __name__ == '__main__':
    main()