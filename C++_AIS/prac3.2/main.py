import json
import sys


def parse_json(filename: str) -> dict:
    with open(filename) as f:
        data = json.load(f)
    return data


rax = {"rax": [0, 1, 2, 3, 4, 5, 6, 7], "eax": [0, 1, 2, 3],
       "ax": [0, 1], "ah": [1], "al": [0]}
rbx = {"rbx": [0, 1, 2, 3, 4, 5, 6, 7], "ebx": [0, 1, 2, 3],
       "bx": [0, 1], "bh": [1], "bl": [0]}
rcx = {"rcx": [0, 1, 2, 3, 4, 5, 6, 7], "ecx": [0, 1, 2, 3],
       "cx": [0, 1], "ch": [1], "cl": [0]}
rdx = {"rdx": [0, 1, 2, 3, 4, 5, 6, 7], "edx": [0, 1, 2, 3],
       "dx": [0, 1], "dh": [1], "dl": [0]}
rsi = {"rsi": [0, 1, 2, 3, 4, 5, 6, 7], "esi": [0, 1, 2, 3], "si": [0, 1]}
rdi = {"rdi": [0, 1, 2, 3, 4, 5, 6, 7], "edi": [0, 1, 2, 3], "di": [0, 1]}
rbp = {"rbp": [0, 1, 2, 3, 4, 5, 6, 7], "ebp": [0, 1, 2, 3], "bp": [0, 1]}
rsp = {"rsp": [0, 1, 2, 3, 4, 5, 6, 7], "esp": [0, 1, 2, 3], "sp": [0, 1]}
r8 = {"r8": [0, 1, 2, 3, 4, 5, 6, 7], "r8d": [0, 1, 2, 3],
      "r8w": [0, 1], "r8b": [0]}
r9 = {"r9": [0, 1, 2, 3, 4, 5, 6, 7], "r9d": [
    0, 1, 2, 3], "r9w": [0, 1], "r9b": [0]}
r10 = {"r10": [0, 1, 2, 3, 4, 5, 6, 7], "r10d": [
    0, 1, 2, 3], "r10w": [0, 1], "r10b": [0]}
r11 = {"r11": [0, 1, 2, 3, 4, 5, 6, 7], "r11d": [
    0, 1, 2, 3], "r11w": [0, 1], "r11b": [0]}
r12 = {"r12": [0, 1, 2, 3, 4, 5, 6, 7], "r12d": [
    0, 1, 2, 3], "r12w": [0, 1], "r12b": [0]}
r13 = {"r13": [0, 1, 2, 3, 4, 5, 6, 7], "r13d": [
    0, 1, 2, 3], "r13w": [0, 1], "r13b": [0]}
r14 = {"r14": [0, 1, 2, 3, 4, 5, 6, 7], "r14d": [
    0, 1, 2, 3], "r14w": [0, 1], "r14b": [0]}
r15 = {"r15": [0, 1, 2, 3, 4, 5, 6, 7], "r15d": [
    0, 1, 2, 3], "r15w": [0, 1], "r15b": [0]}
rflags = {"rflags": [0, 1, 2, 3, 4, 5, 6, 7],
          "eflags": [0, 1, 2, 3], "flags": [0, 1]}

registers = {"rax": rax, "rbx": rbx, "rcx": rcx, "rdx": rdx, "rsi": rsi, "rdi": rdi, "rbp": rbp, "rsp": rsp,
             "r8": r8, "r9": r9, "r10": r10, "r11": r11, "r12": r12, "r13": r13, "r14": r14, "r15": r15, "rflags": rflags}


class TaintItem:
    def __init__(self, name: str, coverage: set):
        self.name = name
        self.coverage = set(sorted(coverage))

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, TaintItem):
            return NotImplemented
        return self.name == other.name and self.coverage == other.coverage

    def __str__(self) -> str:
        return f"{self.name}:{self.coverage}"


def from_reg(reg) -> TaintItem:
    if isinstance(reg, str):
        for k, v in registers.items():
            for reg_k, reg_v in v.items():
                if reg_k == reg:
                    return TaintItem(k, set(reg_v))
    elif isinstance(reg, list):
        reg_name = reg[0]
        for k, v in registers.items():
            for reg_k, reg_v in v.items():
                if reg_k == reg_name:
                    coverage = set()
                    for i in range(reg[1], reg[1]+reg[2]):
                        coverage.add(i)
                    return TaintItem(k, coverage)


def from_array(array: list) -> TaintItem:
    coverage = set()
    for i in range(array[0], array[0]+array[1]):
        coverage.add(i)
    return TaintItem("array", coverage)


def to_TaintItem(taint) -> TaintItem:
    if isinstance(taint, str):
        return from_reg(taint)
    elif isinstance(taint, list):
        if isinstance(taint[0], str):
            return from_reg(taint)
        else:
            return from_array(taint)


def to_list_taintItem(taint) -> list[TaintItem]:
    if isinstance(taint, list):
        return [to_TaintItem(t) for t in taint]
    else:
        return [to_TaintItem(taint)]


def contains(source: list[TaintItem], target: list[TaintItem]) -> bool:
    if source == [] or target == []:
        return False
    for target_item in target:
        for source_item in source:
            if source_item is None or target_item is None:
                continue
            if target_item.name == source_item.name:
                if not target_item.coverage.isdisjoint(source_item.coverage):
                    return True
    return False


def add_taint(curr_taint: list[TaintItem], taint: TaintItem):
    if taint is None:
        return
    if curr_taint == []:
        curr_taint.append(taint)
        return
    for item in curr_taint:
        if item.name == taint.name:
            item.coverage.update(taint.coverage)
            return
    curr_taint.append(taint)


def add_list_taint(curr_taint: list[TaintItem], taint: list[TaintItem]):
    for item in taint:
        add_taint(curr_taint, item)


def remove_taint(curr_taint: list[TaintItem], taint: TaintItem):
    for item in curr_taint:
        if item is None or taint is None:
            continue
        if item.name == taint.name:
            item.coverage.difference_update(taint.coverage)
            return


def remove_list_taint(curr_taint: list[TaintItem], taint: list[TaintItem]):
    for item in taint:
        remove_taint(curr_taint, item)


def from_taintItems(curr_taint: list[TaintItem]) -> list:
    temp_taint = curr_taint.copy()
    output = []
    for item in temp_taint:
        if item is None:
            continue
        if item.name == "array":
            sorted_coverage = sorted(item.coverage)
            # split with consecutive numbers
            if len(sorted_coverage) == 0:
                continue
            if len(sorted_coverage) == 1:
                output.append([sorted_coverage[0], 1])
                continue
            consecutive = []
            for index in range(1, len(sorted_coverage)):
                if sorted_coverage[index] - sorted_coverage[index-1] == 1:
                    consecutive.append(sorted_coverage[index-1])
                else:
                    consecutive.append(sorted_coverage[index-1])
                    output.append(
                        [min(consecutive), len(consecutive)])
                    consecutive = []
                if index == len(sorted_coverage)-1:
                    consecutive.append(sorted_coverage[index])
                    output.append(
                        [min(consecutive), len(consecutive)])

        elif registers.get(item.name) is not None:
            flag = False
            for reg_k, reg_v in registers[item.name].items():
                if item.coverage == set(reg_v):
                    output.append(reg_k)
                    flag = True
                    break
            if not flag:
                for reg_k, reg_v in registers[item.name].items():
                    if set(reg_v).issubset(item.coverage):
                        output.append(reg_k)
                        for i in reg_v:
                            item.coverage.remove(i)
                if item.coverage != set():
                    output.append(
                        [item.name, min(item.coverage), len(item.coverage)])

    return output


def to_output(curr_taint: list[TaintItem], step: int) -> dict:
    out_item = {}
    out_item["step"] = step
    out_item["answer"] = from_taintItems(curr_taint)
    return out_item


def taint(origin_data: dict, test_data: dict) -> list:
    output = []
    curr_taint = []
    flag = False
    for index, test_item in enumerate(test_data):
        if test_item["type"] == "source":
            tmp = to_list_taintItem(test_item["taint"])
            add_list_taint(curr_taint, tmp)
        elif index - 1 >= 0:
            if test_data[index - 1]["type"] == "source" and test_data[index - 1]["step"] == test_data[index]["step"]:
                output.append(to_output(curr_taint, test_item["step"]))
                flag = True
                continue
            fr = test_data[index - 1]["step"] - 1
            to = test_data[index]["step"] - 1
            if flag or fr + 1 == test_data[0]["step"]:
                fr += 1
                flag = False
            for i in range(fr, to + 1):
                item = origin_data[i]
                read_reg = to_list_taintItem(item["readRegs"])
                read_mem = to_list_taintItem(item["readMem"])
                wirte_reg = to_list_taintItem(item["writeRegs"])
                write_mem = to_list_taintItem(item["writtenMem"])
                if contains(read_reg, curr_taint) or contains(read_mem, curr_taint):
                    add_list_taint(curr_taint, wirte_reg)
                    add_list_taint(curr_taint, write_mem)
                elif item["text"].find("mov") != -1:
                    remove_list_taint(curr_taint, wirte_reg)
                    remove_list_taint(curr_taint, write_mem)
            output.append(to_output(curr_taint, test_item["step"]))
        else:
            output.append(to_output(curr_taint, test_item["step"]))
    return output


def main():
    if len(sys.argv) != 4:
        print(
            "Usage: python main.py [file.json] [file.tests.json] [file.out.json]")
        return
    origin_data = parse_json(sys.argv[1])
    test_data = parse_json(sys.argv[2])
    output = taint(origin_data, test_data)
    with open(sys.argv[3], "w") as f:
        f.write(json.dumps(output, indent=4))


if __name__ == '__main__':
    main()
