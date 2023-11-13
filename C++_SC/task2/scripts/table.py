import json
import sys

data = json.load(open(sys.argv[1]))

results = {}

for entry in data:
    key = (entry["L"], entry["T"])
    if key not in results:
        results[key] = []

    multiplier = entry["threads"]
    if key == (1.0, 1.0):
        time_multiplier = data[0]["time"] / entry["time"]
    else:
        time_multiplier = data[1]["time"] / entry["time"]

    error = entry["error"]
    time = entry["time"]
    results[key].append(
        {
            "threads": multiplier,
            "time": time,
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
        time = value["time"]
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
        time = value["time"]
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
