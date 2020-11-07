from fuzzing.fuzzer import FuzzExecutor
import math
import random
import subprocess
import time
import os.path
from tempfile import mkstemp
from collections import Counter
from shutil import copyfile

# Files to use as initial input seed.
file_list = ["../../example/1.caff"]

# List of applications to test.
apps_under_test = ["./test.out"]


fuzz_factor = 50  # 250
num_tests = 8000

def fuzzer():
    """Fuzzing apps."""
    stat_counter = Counter()
    for cnt in range(num_tests):
        file_choice = random.choice(file_list)
        app = random.choice(apps_under_test)
        app_name = app.split('/')[-1]
        file_name = file_choice.split('/')[-1]

        buf = bytearray(open(os.path.abspath(file_choice), 'rb').read())

        # Charlie Miller's fuzzer code:
        num_writes = random.randrange(math.ceil((float(len(buf)) / fuzz_factor))) + 1

        for _ in range(num_writes):
            r_byte = random.randrange(256)
            rn = random.randrange(len(buf))
            buf[rn] = r_byte
        # end of Charlie Miller's code

        fd, fuzz_output = mkstemp()
        with open(fuzz_output, 'wb') as f:
            f.write(buf)
        process = subprocess.Popen([app, fuzz_output])

        time.sleep(1)
        crashed = process.poll()
        if crashed:
            print("Process crashed ({} <- {})".format(app, file_choice))
            copyfile(fuzz_output, "fuzz" + str(cnt))
            stat_counter[(app_name, 'failed')] += 1
        else:
            process.terminate()
            stat_counter[(app_name, 'succeeded')] += 1
    return stat_counter

def main():
    #lf = LoggerFactory(package_name='.', config_file='log_config.yaml')
    #lf.initialize()
    stats = fuzzer()
    print(stats)

main()
