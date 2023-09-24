from math import factorial

def next_mutation_char(diff_chars: int, max_changes: int, curr_seq: str, init_seq: str):
    index = len(curr_seq)

    if (diff_chars > max_changes): return
    if (index == len(init_seq)):
        print(curr_seq)
        return
    
    for char in "ACGT":
        if (char != init_seq[index] and diff_chars >= max_changes): continue
        curr_seq = curr_seq + char

        if (char != init_seq[index]): new_diff = 1
        else: new_diff = 0

        next_mutation_char(diff_chars + new_diff, max_changes, curr_seq, init_seq)
        curr_seq = curr_seq[:-1]

def request_test():
    data = input().split(" ")
    seq_length = int(data[0])
    max_changes = int(data[1])
    init_seq = input()

    return { "seq_length": seq_length, "max_changes": max_changes, "init_seq": init_seq }

def test_loop():
    test = request_test()
    curr_seq = ""

    possible = 0
    for test_i in range(test["max_changes"] + 1):
        possible = possible + (factorial(test["seq_length"]) // (factorial(test_i) * (factorial(test["seq_length"] - test_i))) * 3**test_i)
    print(possible)

    next_mutation_char(0, test["max_changes"], curr_seq, test["init_seq"])


if (__name__ == "__main__"):
    test_num = int(input())
    for i in range(test_num):
        test_loop()
    print()