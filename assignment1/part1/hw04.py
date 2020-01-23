import sys

longest_row_number, longest_row_length = 0, 0
every_row_array = []

def error():
    raise Exception("bad input")

def parserow(curr_row):
    curr_char = 0 
    row_length = 0
    row_array = []
    while curr_char < len(curr_row):
        def scan_digits(curr_char):
            curr_char += 1
            while curr_row[curr_char].isdigit():
                curr_char += 1
            return curr_char
        if curr_row[curr_char] == "\n":
            break

        while curr_row[curr_char] == " ":
            curr_char += 1
        if curr_row[curr_char] == "<":
            curr_char += 1
            while curr_row[curr_char] == " ":
                curr_char += 1
        else:
            error()
            
        if curr_row[curr_char] == "\"":
            beginning_char = curr_char
            curr_char += 1
            end_char = curr_row.find("\"", curr_char)
            if end_char - curr_char < 255 and end_char != -1:
                row_array.append(("STRING", row[curr_char: end_char]))
                curr_char = end_char + 1
            else:
                error()

        elif (curr_row[curr_char] == "1" or curr_row[curr_char] == "0") and (curr_row[curr_char + 1] == " " or curr_row[curr_char + 1] == ">"):
            row_array.append(("BOOL", curr_row[curr_char]))
            curr_char += 1
        
        elif curr_row[curr_char] == "+" or curr_row[curr_char] == "-" or curr_row[curr_char].isdigit():
            beginning_char = curr_char
            curr_char = scan_digits(curr_char)
            row_array.append(("INTEGER", curr_row[beginning_char:curr_char]))
            if curr_row[curr_char] == ".":
                curr_char = scan_digits(curr_char)
                row_array[row_length] = ("FLOAT", curr_row[beginning_char:curr_char])
        
        elif curr_row[curr_char] == ".":
            beginning_char = curr_char
            curr_char = scan_digits(curr_char)
            row_array.append(("FLOAT", curr_row[beginning_char:curr_char]))

        elif curr_row[curr_char] != ">":
            beginning_char = curr_char
            curr_char += 1
            end_char = curr_row.find(" ", curr_char)
            end_char2 = curr_row.find(">", curr_char)
            if end_char > end_char2:
                end_char = end_char2
            if end_char == -1:
                end_char = end_char2
            if end_char - curr_char < 255 and end_char != -1:
                curr_char = end_char
                row_array.append(("STRING", curr_row[beginning_char:curr_char]))
            else:
                error()
        else:
            row_array.append(("EMPTY", "<>"))

        while curr_row[curr_char] == " ":
            curr_char += 1

        if curr_row[curr_char] == ">":
            curr_char += 1
            row_length += 1
        else:
            error()
    return (row_length, row_array)

def scan(input_file, length):
    global longest_row_number, longest_row_length 

    # check startingline + 500 isnt eof
    byte_count = 0 
    row_number = 0
    while byte_count < length :
        if row_number > 500:
            break
        row = input_file.readline()
        byte_count += len(row)
        if byte_count > length or row == "":
            return
        row_length, row_array = parserow(row)
        every_row_array.append(row_array)
        if row_length > longest_row_length:
            longest_row_number = row_number
            longest_row_length = row_length
            
        row_number += 1
    return row_number


                
x = 0
missing_index = False
col_index = False
col_type = False
file_name = ""
starting_pos = 0
row_num = 0
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
        input_col_num = int(sys.argv[x])
        col_type = True

    elif flag == "-print_col_idx":
        x += 1
        input_col_num = int(sys.argv[x])
        x += 1
        input_row_num = int(sys.argv[x])
        col_index = True

    elif flag == "-is_missing_idx":
        x += 1
        input_col_num = int(sys.argv[x])
        x += 1
        input_row_num = int(sys.argv[x])
        missing_index = True
    x += 1
if file_name == "":
    raise Exception("expected file input")

f = open(file_name)
print(int (starting_pos))
f.seek(int (starting_pos), 0)
if starting_pos != 0:
    f.readline()
row_number = scan(f, num_bytes)

while input_row_num > row_number:
    every_row_array.append(f.readline())
    row_number += 1

if input_row_num == row_number:
    line_checking = f.readline()
    print(line_checking)
    if line_checking == "":
        raise Exception("Row index is out of bounds")
    row_array = parserow(line_checking)[1]
    every_row_array.append(row_array)


# To do, add row checking
if missing_index:
    if input_col_num >= longest_row_length:
        print("True")
    else:
        print("{} {}".format(every_row_array[longest_row_number][input_col_num][0], every_row_array[input_row_num][input_col_num][0]))
        print(every_row_array[longest_row_number][input_col_num] != every_row_array[input_row_num][input_col_num])

if col_index:
    if input_col_num < longest_row_length:
        if len(every_row_array[input_row_num]) <= input_col_num:
            print("<>")
        elif every_row_array[longest_row_number][input_col_num][0] == every_row_array[input_row_num][input_col_num][0]:
            print(every_row_array[input_row_num][input_col_num][1])
        else:
            print("<>")
    else:
        raise Exception("column index is out of bounds")

if col_type:
    if input_col_num > longest_row_length:
        raise Exception("column index is out of bounds")
    else:
        print(every_row_array[longest_row_number][input_col_num][0])