import json
import sys

data = json.load(open(sys.argv[1]))
time_name = "time"
process = 0
if sys.argv[2] == "mpi":
    time_name = "MPI time"
    process = int(sys.argv[3])

results = {}

for entry in data:
    if sys.argv[2] == "mpi":
        if entry["process"] != process:
            continue
    key = (entry["L"], entry["T"])
    if key not in results:
        results[key] = []

    multiplier = entry["threads"]
    if key == (1.0, 1.0):
        time_multiplier = data[0 + (process - 1) * 8][time_name] / entry[time_name]
    else:
        time_multiplier = data[1 + (process - 1) * 8][time_name] / entry[time_name]

    error = entry["error"]
    time = entry[time_name]
    results[key].append(
        {
            "threads": multiplier,
            time_name: time,
            "time_multiplier": time_multiplier,
            "error": error,
        }
    )

for key, values in results.items():
    L, T = key
    print(f"For L={L}, T={T}:")
    for value in values:
        threads = value["threads"]
        time_multiplier = value["time_multiplier"]
        error = value["error"]
        time = value[time_name]
        print(
            f"Threads: {threads}, Time: {time}, Error: {error}, Time Multiplier: {time_multiplier:.4f}"
        )
    print()


def format_as_latex(input_str):
    # Convert the input string to a float
    value = float(input_str)

    # Extract the mantissa and exponent from the scientific notation
    mantissa, exponent = f"{value:e}".split("e")

    # Format the result in LaTeX style
    formatted_str = f"$ {mantissa} * 10^{{{int(exponent)}}} $"

    return formatted_str


# for latex
for key, values in results.items():
    L, T = key
    print(f"For L={L}, T={T}:")
    for value in values:
        threads = value["threads"]
        time_multiplier = value["time_multiplier"]
        error = value["error"]
        time = value[time_name]
        if "128" in sys.argv[1]:
            print(
                f"{threads} & $128^3$ & {time} & {format_as_latex(error)} & {time_multiplier:.4f} \\\\"
            )
        else:
            print(
                f"{threads} & $256^3$ & {time} & {format_as_latex(error)} & {time_multiplier:.4f} \\\\"
            )
        print("\\hline")
    print()
