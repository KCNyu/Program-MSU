import json
import graphviz
import sys


def parse_json(filename: str) -> dict:
    with open(filename) as f:
        data = json.load(f)
    return data


def to_hex(address: int) -> str:
    if (isinstance(address, int)):
        return str(hex(address)[2:].upper().zfill(16))
    return address


def empty(dot: graphviz.Digraph, label: str) -> bool:
    node = "[label=\"{}\"".format(label)
    return dot.source.find(node) == -1


def empty_foregin(dot: graphviz.Digraph, address: str) -> bool:
    node = "\"{}\" [label=\"{}\"]".format(address, address)
    return dot.source.find(node) == -1


def empty_edge(dot: graphviz.Digraph, fr: str, to: str) -> bool:
    edge1 = "\"{}\" -> \"{}\"".format(fr, to)
    edge2 = "\"{}\" -> {}".format(fr, to)
    edge3 = "{} -> \"{}\"".format(fr, to)
    edge4 = "{} -> {}".format(fr, to)
    return dot.source.find(edge1) == -1 and dot.source.find(edge2) == -1 and dot.source.find(edge3) == -1 and dot.source.find(edge4) == -1


def add_node(dot: graphviz.Digraph, address: int, label: str) -> None:
    if empty(dot, label):
        return dot.node(to_hex(address), label, shape="box")


def add_foreign_node(dot: graphviz.Digraph, address: str) -> None:
    if empty_foregin(dot, address):
        return dot.node(address, address)


def add_edge(dot: graphviz.Digraph, dot_nodes: list, fr: int, to: int) -> None:
    fr_addr = to_hex(dot_nodes[fr])
    to_addr = to_hex(dot_nodes[to])

    if (fr >= 0 and to < len(dot_nodes) and empty_edge(dot, fr_addr, to_addr)):
        return dot.edge(fr_addr, to_addr)


def is_branch(value: dict) -> bool:
    return value.keys().__contains__('isBranch')


def is_foregin_branch(value: dict) -> bool:
    return value.keys().__contains__('isForeignBranch')


def gather_text(data: dict, fr: int, to: int) -> str:
    text = ""
    for i in range(fr, to - 1):
        text += data[i]['text'] + "\\n"
    text += data[to - 1]['text']
    return text


def create_label(data: dict, fr: int, to: int) -> str:
    label = to_hex(data[fr]['address'])
    return "{}\\n{}".format(label, gather_text(data, fr, to))


def traverse(data: dict, nodes: list) -> None:
    nodes.append(data[0]['address'])
    for index, value in enumerate(data):
        if is_branch(value):
            if(index < len(data) - 1):
                address = data[index + 1]['address']
                if address not in nodes:
                    nodes.append(address)
        if is_foregin_branch(value):
            address = value['foreignTargetName']
            if address not in nodes:
                nodes.append(address)
    nodes.append(data[len(data) - 1]['address'])


def create(data: dict, nodes: list, dot_nodes: list, dot: graphviz.Digraph) -> None:
    pre_index = 0
    node_index = 0
    flag = False
    out_addr = ""
    for cur_index, value in enumerate(data):
        addr = value['address']
        if nodes.__contains__(addr) and cur_index != 0:
            pre_addr = data[pre_index]['address']

            if cur_index == len(data) - 1:
                add_node(dot, pre_addr, create_label(
                    data, pre_index, cur_index + 1))
            else:
                add_node(dot, pre_addr, create_label(
                    data, pre_index, cur_index))

            dot_nodes.append(pre_addr)
            if node_index >= 1:
                add_edge(dot, dot_nodes, node_index - 1, node_index)
            node_index += 1
            pre_index = cur_index
            if (flag):
                add_foreign_node(dot, out_addr)
                dot_nodes.append(out_addr)
                if node_index >= 1:
                    add_edge(dot, dot_nodes, node_index - 1, node_index)
                node_index += 1
                flag = False

        if is_foregin_branch(value):
            out_addr = value['foreignTargetName']
            flag = True


def main():
    if len(sys.argv) != 3:
        print("Usage: python main.py <filename.json> <filename.dot>")
        return
    input = sys.argv[1]
    output = sys.argv[2]
    data = parse_json(input)
    nodes = []
    dot_nodes = []

    traverse(data, nodes)

    dot = graphviz.Digraph(
        input, filename=output, strict=True)
    create(data, nodes, dot_nodes, dot)

    dot.save()


if __name__ == '__main__':
    main()
