import sys

longest_row_number, longest_row_length = 0, 0
every_row_dict = []

def scan(input_file, length):
    global longest_row_number, longest_row_length 

    def error():
        raise Exception("bad input")

    # check startingline + 500 isnt eof
    byte_count = 0 
    row_number = 0
    while byte_count < length :
        row = input_file.readline()
        byte_count += len(row)
        if byte_count > length or row == "":
            return
        curr_char = 0
        row_length = 0
        row_dict = []
        while curr_char < len(row):
            def scan_digits(curr_char):
                curr_char += 1
                while row[curr_char].isdigit():
                    curr_char += 1
                return curr_char
            if row[curr_char] == "\n":
                break

            while row[curr_char] == " ":
                curr_char += 1
            if row[curr_char] == "<":
                curr_char += 1
                while row[curr_char] == " ":
                    curr_char += 1
            else:
                error()
                
            if row[curr_char] == "\"":
                beginning_char = curr_char
                curr_char += 1
                end_char = row.find("\"", curr_char)
                if end_char - curr_char < 255 and end_char != -1:
                    row_dict.append(("STRING", row[curr_char: end_char]))
                    curr_char = end_char + 1
                else:
                    error()

            elif (row[curr_char] == "1" or row[curr_char] == "0") and (row[curr_char + 1] == " " or row[curr_char + 1] == ">"):
                row_dict.append(("BOOL", row[curr_char]))
                curr_char += 1
            
            elif row[curr_char] == "+" or row[curr_char] == "-" or row[curr_char].isdigit():
                beginning_char = curr_char
                curr_char = scan_digits(curr_char)
                row_dict.append(("INTEGER", row[beginning_char:curr_char]))
                if row[curr_char] == ".":
                    curr_char = scan_digits(curr_char)
                    row_dict[row_length] = ("FLOAT", row[beginning_char:curr_char])
            
            elif row[curr_char] == ".":
                beginning_char = curr_char
                curr_char = scan_digits(curr_char)
                row_dict.append(("FLOAT", row[beginning_char:curr_char]))

            elif row[curr_char] != ">":
                beginning_char = curr_char
                curr_char += 1
                end_char = row.find(" ", curr_char)
                end_char2 = row.find(">", curr_char)
                if end_char > end_char2:
                    end_char = end_char2
                if end_char == -1:
                    end_char = end_char2
                if end_char - curr_char < 255 and end_char != -1:
                    curr_char = end_char
                    row_dict.append(("STRING", row[beginning_char:curr_char]))
                else:
                    error()
            else:
                row_dict.append(("EMPTY", "<>"))

            while row[curr_char] == " ":
                curr_char += 1

            if row[curr_char] == ">":
                curr_char += 1
                row_length += 1
            else:
                error()
        every_row_dict.append(row_dict)
        if row_length > longest_row_length:
            longest_row_number = row_number
            longest_row_length = row_length
            
        row_number += 1


                
x = 0
missing_index = False
col_index = False
col_type = False
file_name = ""
starting_pos = 0
num_bytes = -1
while x < len(sys.argv):
    flag = sys.argv[x]

    if flag == "-f":
        x += 1
        file_name = sys.argv[x]

    elif flag == "-from":
        x += 1
        starting_pos = sys.argv[x]

    elif flag == "-len":
        x += 1
        num_bytes = sys.argv[x]

    elif flag == "-print_col_type":
        x += 1
        col_num = int(sys.argv[x])
        col_type = True

    elif flag == "-print_col_idx":
        x += 1
        col_num = int(sys.argv[x])
        x += 1
        row_num = int(sys.argv[x])
        col_index = True

    elif flag == "-is_missing_idx":
        x += 1
        col_num = int(sys.argv[x])
        x += 1
        row_num = int(sys.argv[x])
        missing_index = True
    x += 1
if file_name == "":
    raise Exception("expected file input")

f = open(file_name)
f.seek(starting_pos)
scan(f, num_bytes)

# To do, add row checking
if missing_index:
    if col_num >= longest_row_length:
        print("True")
    else:
        print("{} {}".format(every_row_dict[longest_row_number][col_num][0], every_row_dict[row_num][col_num][0]))
        print(every_row_dict[longest_row_number][col_num] != every_row_dict[row_num][col_num])

if col_index:
    if col_num < longest_row_length:
        if len(every_row_dict[row_num]) <= col_num:
            print("<>")
        elif every_row_dict[longest_row_number][col_num][0] == every_row_dict[row_num][col_num][0]:
            print(every_row_dict[row_num][col_num][1])
        else:
            print("<>")
    else:
        raise Exception("column index is out of bounds")

if col_type:
    if col_num > longest_row_length:
        raise Exception("column index is out of bounds")
    else:
        print(every_row_dict[longest_row_number][col_num][0])