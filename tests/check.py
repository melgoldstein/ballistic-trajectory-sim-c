import math, subprocess, sys
binary = sys.argv[1]
def run(drag):
    result = subprocess.run([binary], input=f"100 45 1 {drag}\n", text=True, capture_output=True, check=True)
    return list(map(float, result.stdout.splitlines()[1].split(',')))
vacuum = run(0)
assert abs(vacuum[1] - 10000 / 9.80665) < 0.2
assert run(0.01)[1] < vacuum[1]
assert subprocess.run([binary], input='-1 45 1 0', text=True, capture_output=True).returncode != 0
